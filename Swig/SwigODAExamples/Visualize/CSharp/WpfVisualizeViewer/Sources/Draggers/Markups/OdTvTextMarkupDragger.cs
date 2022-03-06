/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

using System;
using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.Misc;

namespace WpfVisualizeViewer
{
    public class OdTvTextMarkupDragger : OdTvMarkupDragger
    {
        private bool _isSuccess = false;
        // first and last click
        private OdGePoint3d _firstPoint;
        // local state of the dragger
        private bool _isPressed = false;
        // need to control the ::start called first time or not
        private bool _justCreatedObject = true;

        // temporary geometry
        private OdTvEntityId _entityId = null;
        private OdTvGeometryDataId _textFoldId = null;
        private OdTvGeometryDataId _textId = null;
        private OdTvGeometryDataId _caretId = null;
        private OdTvCaret _caret = null;

        private bool _isNeedStartTextInput;

        private static int NumOfTxtmarkup = 0;

        public OdTvTextMarkupDragger(OdTvGsDeviceId deviceId, OdTvModelId markupModelId)
            : base(deviceId, markupModelId)
        {
            NeedFreeDrag = true;

            MemoryTransaction mTr = MM.StartTransaction();
            // create main entity
            OdTvModel pModel = markupModelId.openObject(OpenMode.kForWrite);
            _entityId = FindMarkupEntity(NameOfMarkupTempEntity, true);
            OdTvEntity entity;
            if(_entityId != null)
                entity = _entityId.openObject(OpenMode.kForWrite);
            else
            {
                _entityId = pModel.appendEntity(NameOfMarkupTempEntity);
                entity = _entityId.openObject(OpenMode.kForWrite);
                entity.setColor(MarkupColor);
            }

            // crate circle subEntity if not exist
            _textFoldId = FindSubEntity(entity.getGeometryDataIterator(), NameOfMarkupCloudFold);
            if (_textFoldId == null)
                _textFoldId = entity.appendSubEntity(NameOfMarkupCloudFold);
            OdTvEntity textFold = _textFoldId.openAsSubEntity(OpenMode.kForWrite);

            // create text style
            OdTvModel draggerModel = TvDraggerModelId.openObject(OpenMode.kForWrite);
            OdTvTextStyleId txtStyleId = FindTextStyle(draggerModel.getDatabase().openObject().getTextStylesIterator(), NameOfMarkupTextStyle);
            if (txtStyleId == null)
            {
                txtStyleId = draggerModel.getDatabase().openObject(OpenMode.kForWrite).createTextStyle(NameOfMarkupTextStyle);
                txtStyleId.openObject(OpenMode.kForWrite).setFont("Calibri", false, false, 0, 0);
            }

            // set text style to the entity
            textFold.setTextStyle(new OdTvTextStyleDef(txtStyleId));
            // clear instruction text for new text input
            _isNeedStartTextInput = true;

            MM.StopTransaction(mTr);
        }

        ~OdTvTextMarkupDragger()
        {
            if (!_isSuccess && _textId != null)
            {
                MemoryTransaction mtr = MM.StartTransaction();
                _textFoldId.openAsSubEntity(OpenMode.kForWrite).removeGeometryData(_textId);
                MM.StopTransaction(mtr);
            }
        }

        public override DraggerResult Start(OdTvDragger prevDragger, int activeView, Cursor cursor, TvWpfViewWCS wcs)
        {
            TvActiveViewport = activeView;
            DraggerResult res = DraggerResult.NothingToDo;

            // create temporary geometry
            if (!_justCreatedObject)
            {
                UpdateFrame(true);
                res = DraggerResult.NeedUpdateView;
            }

            res = res | base.Start(prevDragger, activeView, cursor, wcs);

            // add dragger model to the view
            AddDraggersModelToView();

            if (!_justCreatedObject)
                State = DraggerState.Working;

            _justCreatedObject = false;

            return res;
        }

        public override DraggerResult NextPoint(int x, int y)
        {
            if (!CheckDragger())
                return DraggerResult.NothingToDo;

            if (!_isPressed)
            {
                _isPressed = true;
                // remember first click
                _firstPoint = ToEyeToWorld(x, y);

                UpdateFrame(true);

                return DraggerResult.NeedUpdateView;
            }

            //Finish
            State = DraggerState.Waiting;
            return DraggerResult.NeedUFinishDragger;
        }

        public override bool ProcessEnter()
        {
            if (_textId != null)
            {
                MemoryTransaction mtr = MM.StartTransaction();

                // Clear row for text input from information
                if (_isNeedStartTextInput)
                    GetActiveRow().openAsText().setString("");

                // Move point for row adding
                // Find direction for point moving
                OdGeVector3d dir = -TvView.openObject().upVector();
                MoveFirstPoint(dir);

                AddText(_textId, _firstPoint, "");

                UpdateFrame(false);

                MM.StopTransaction(mtr);
            }

            return false;
        }

        public override DraggerResult ProcessBackspace()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGeometryDataId curRowId = GetActiveRow();
            if (curRowId != null)
            {
                OdTvTextData pCurRow = curRowId.openAsText();
                if (pCurRow.getString().Length > 0) // If there are symbols in row, remove last
                {
                    string text = pCurRow.getString();
                    text = text.Remove(text.Length - 1);
                    pCurRow.setString(text);
                    UpdateFrame(false);

                    return DraggerResult.NeedUpdateView;
                }
                else // Else, remove row and move point to the previous row
                {
                    if (GetPrevRow() != null)
                    {
                        RemoveGeometryData(ref _textId, ref curRowId);

                        // Move text point to the previous row
                        // Find direction for point moving
                        OdGeVector3d dir = TvView.openObject().upVector();
                        MoveFirstPoint(dir);
                        UpdateFrame(false);

                        return DraggerResult.NeedUpdateView;
                    }

                }
            }

            MM.StopTransaction(mtr);

            return DraggerResult.NothingToDo;
        }

        public override DraggerResult ProcessText(string text)
        {
            UpdateFrame(false, text);

            return DraggerResult.NeedUpdateView;
        }

        public override OdTvDragger Finish(out DraggerResult rc)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            // If there was no text input, remove row with instruction
            if (_isNeedStartTextInput)
                RemoveGeometryData(ref _textFoldId, ref _textId);
            if (_textId != null)
            {
                // Remove empty rows
                OdTvGeometryDataIterator pIter = _textId.openAsSubEntity(OpenMode.kForWrite).getGeometryDataIterator();
                while (!pIter.done())
                {
                    OdTvGeometryDataId rowId = pIter.getGeometryData();
                    pIter.step();

                    if (rowId.openAsText().getString() == "")
                        RemoveGeometryData(ref _textId, ref rowId);
                }

                // If m_frameId has no sub geometries, remove it
                if (GetSubGeometryDataCount(ref _textId) == 0)
                    RemoveGeometryData(ref _textFoldId, ref _textId);
                else // Else, make text bold
                {
                    _isSuccess = true;
                    _textId.openAsSubEntity(OpenMode.kForWrite).setLineWeight(LineWeight);
                }
            }

            if (_caretId != null)
            {
                _caret.Stop();
                RemoveGeometryData(ref _textFoldId, ref _caretId);
            }

            State = DraggerState.Waiting;

            // Need update view
            DraggerResult rcFinish;
            OdTvDragger retFinish = base.Finish(out rcFinish);

            rc = rcFinish | DraggerResult.NeedUpdateView;

            MM.StopTransaction(mtr);

            return retFinish;
        }


        public override bool UpdateCursor()
        {
            CurrentCursor = State == DraggerState.Finishing ? LasAppActiveCursor : Cursors.Cross;
            return true;
        }

        private void UpdateFrame(bool isNeedCreate, string text = "")
        {
            if (TvView == null)
                return;

            MemoryTransaction mtr = MM.StartTransaction();

            if (isNeedCreate)
            {
                // create new text subentity
                _textId = _textFoldId.openAsSubEntity(OpenMode.kForWrite).appendSubEntity("TextMarkup" + NumOfTxtmarkup++);
                if (_textId != null)
                    AddText(_textId, _firstPoint, "Enter text");
            }
            else
            {
                if (_textId != null || text.Length > 0)
                {
                    OdTvGeometryDataId geometryDataId = GetActiveRow();

                    if (geometryDataId != null)
                    {
                        OdTvTextData pText = geometryDataId.openAsText();
                        if (_isNeedStartTextInput) // Remove information if need
                        {
                            pText.setString("");
                            // Create caret and row for caret
                            _caretId = AddText(_textFoldId, _firstPoint, "");
                            UpdateCaretpos();
                            _caret = new OdTvCaret(ref _caretId, TvDeviceId);
                            _isNeedStartTextInput = false;
                        }
                        // Update string
                        string newStr = text.Length != 0 ? pText.getString() + text : pText.getString();
                        pText.setString(newStr);
                        UpdateCaretpos();
                    }
                }
            }

            MM.StopTransaction(mtr);
        }

        private void UpdateCaretpos()
        {
            if (_textId == null || _caretId == null || TvView == null)
                return;

            MemoryTransaction mtr = MM.StartTransaction();

            OdGePoint3d pos = null;
            OdTvTextData pCaret = _caretId.openAsText();

            OdTvTextData pCurRow = GetActiveRow().openAsText();
            // Get bounding points of curent row
            OdTvPointArray points = new OdTvPointArray();
            pCurRow.getBoundingPoints(points);

            pos = GetActiveRow().openAsText().getAlignmentPoint();

            // Get direction for moving text point to caret position as current text row direction
            OdGeVector3d dir = points[3] - points[2];

            // Scale distance
            OdGeMatrix3d projMatr = TvView.openObject().projectionMatrix();
            double movingScale = 1d;
            if (!projMatr.GetItem(1, 1).Equals(0d))
                movingScale = 1d / projMatr.GetItem(1, 1);

            // Create additional offset for distance between last letter in row and caret
            OdGeVector3d additionalDir = new OdGeVector3d(dir);
            if (!dir.length().Equals(0d))
                additionalDir.normalize();
            additionalDir *= (movingScale * MarkupCaretTranslation);

            // Move point from text start to place for caret
            OdGeVector3d vec = dir + additionalDir;
            OdGeMatrix3d matr = new OdGeMatrix3d();
            matr.setTranslation(vec);
            pos.setToProduct(matr, pos);
            pCaret.setAlignmentPoint(pos);

            MM.StopTransaction(mtr);
        }

        private OdTvGeometryDataId AddText(OdTvGeometryDataId geomId, OdGePoint3d pos, string text)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGeometryDataId textId = geomId.openAsSubEntity(OpenMode.kForWrite).appendText(pos, text);
            OdTvGsView view = TvView.openObject();

            //get eye to world matrix
            OdGeMatrix3d eyeToWorld = view.eyeToWorldMatrix();
            //get eye direction
            OdGeVector3d eyeDir = view.position() - view.target();
            //calculate rotation angle
            OdGeVector3d xDir = new OdGeVector3d(1, 0, 0);
            OdGeVector3d direction = eyeToWorld * xDir;
            direction.transformBy(OdGeMatrix3d.worldToPlane(eyeDir));

            // find the angle between XAxis and direction
            double angle = -Math.Atan2(-direction.y, direction.x);
            if (!xDir.rotateBy(angle, new OdGeVector3d(0, 0, 1)).isEqualTo(direction))
            {
                MessageBox.Show("Wrong parameters!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                angle += Math.PI;
                MM.StopTransaction(mtr);
                return textId;
            }

            // Rotate text
            OdTvTextData pText = textId.openAsText();
            pText.setNormal(eyeDir);
            pText.setRotation(angle);

            // Scale text size
            double textSize = MarkupTextSize;
            OdGeMatrix3d projMatr = view.projectionMatrix();
            double textScale = 1d;
            if (!projMatr.GetItem(1, 1).Equals(0))
                textScale = 1d / projMatr.GetItem(1, 1);

            pText.setTextSize(textSize * textScale);

            MM.StopTransaction(mtr);

            return textId;
        }

        private void MoveFirstPoint(OdGeVector3d dir)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            // Move point for row adding
            OdTvTextStyleId textStyle = FindTextStyle(TvDraggerModelId.openObject().getDatabase().openObject().getTextStylesIterator(), NameOfMarkupTextStyle);
            if (textStyle != null && TvView != null)
                dir *= (MarkupLineSpacing * (double)TvView.openObject().fieldHeight());
            OdGeMatrix3d matr = new OdGeMatrix3d();
            matr.setTranslation(dir);
            _firstPoint.setToProduct(matr, _firstPoint);
            MM.StopTransaction(mtr);
        }

        private OdTvTextStyleId FindTextStyle(OdTvTextStylesIterator pIt, string name)
        {
            OdTvTextStyleId id = null;

            while (!pIt.done())
            {
                if (pIt.getTextStyle().openObject().getName() == name)
                {
                    id = pIt.getTextStyle();
                    break;
                }
                pIt.step();
            }

            return id;
        }

        private OdTvGeometryDataId GetActiveRow()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryDataId id = null;
            if (_textId != null)
            {
                OdTvEntity txt = _textId.openAsSubEntity(OpenMode.kForWrite);
                OdTvGeometryDataIterator geomIter = txt.getGeometryDataIterator();
                while (!geomIter.done())
                {
                    id = geomIter.getGeometryData();
                    geomIter.step();
                }
            }
            MM.StopTransaction(mtr);
            return id;
        }

        private OdTvGeometryDataId GetPrevRow()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGeometryDataId curId = null, prevId = null;
            if (_textId != null)
            {
                OdTvEntity pTxt = _textId.openAsSubEntity(OpenMode.kForWrite);
                OdTvGeometryDataIterator geomIter = pTxt.getGeometryDataIterator();
                // Get first row
                if (!geomIter.done())
                {
                    curId = geomIter.getGeometryData();
                    geomIter.step();
                }
                // Go through the iterator and get last and previous rows
                while (!geomIter.done())
                {
                    prevId = curId;
                    curId = geomIter.getGeometryData();
                    geomIter.step();
                }
            }

            MM.StopTransaction(mtr);

            return prevId;
        }

        uint GetSubGeometryDataCount(ref OdTvGeometryDataId id)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryDataIterator pIter = id.openAsSubEntity(OpenMode.kForWrite).getGeometryDataIterator();
            uint counter = 0;
            while (!pIter.done())
            {
                counter++;
                pIter.step();
            }

            MM.StopTransaction(mtr);
            return counter;
        }
    }
}
