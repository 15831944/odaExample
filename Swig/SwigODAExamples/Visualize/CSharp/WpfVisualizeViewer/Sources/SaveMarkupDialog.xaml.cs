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
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;
using MessageBox = System.Windows.Forms.MessageBox;

namespace WpfVisualizeViewer.Dialogs
{
    public struct SaveTvViewParams
    {
        public double PositionX;
        public double PositionY;
        public double PositionZ;
        public double TargetX;
        public double TargetY;
        public double TargetZ;
        public double UpVectorX;
        public double UpVectorY;
        public double UpVectorZ;
        public uint Projection;
        public uint RenderMode;
        public double Width;
        public double Height;

        public void SetPosition(OdGePoint3d pnt)
        {
            PositionX = pnt.x;
            PositionY = pnt.y;
            PositionZ = pnt.z;
        }

        public void SetTarget(OdGePoint3d pnt)
        {
            TargetX = pnt.x;
            TargetY = pnt.y;
            TargetZ = pnt.z;
        }

        public void SetUpVector(OdGeVector3d vec)
        {
            UpVectorX = vec.x;
            UpVectorY = vec.y;
            UpVectorZ = vec.z;
        }

        public void SetProjection(OdTvGsView.Projection proj)
        {
            Projection = (uint) proj;
        }

        public void SetRenderMode(OdTvGsView.RenderMode mode)
        {
            RenderMode = (uint) mode;
        }

        public void SetSize(double width, double height)
        {
            Width = width;
            Height = height;
        }
    }

    /// <summary>
    /// Interaction logic for SaveMarkupDialog.xaml
    /// </summary>
    public partial class SaveMarkupDialog : Window
    {
        private OdTvModelId _markupModelId;
        private OdTvEntityId _curEntityId;
        private OdTvGsViewId _viewId;
        private string _oldName;
        private string _newName;

        private MemoryManager MM = MemoryManager.GetMemoryManager();

        public SaveMarkupDialog(OdTvModelId markupModel, OdTvEntityId activeEntityId, OdTvGsViewId viewId)
        {
            InitializeComponent();
            this.Owner = App.Current.MainWindow;
            _markupModelId = markupModel;
            _curEntityId = activeEntityId;
            _viewId = viewId;

            MemoryTransaction mtr = MM.StartTransaction();

            _oldName = _curEntityId.openObject().getName();
            txtBox.Text = _oldName == OdTvMarkupDragger.NameOfMarkupTempEntity ? "" : _oldName;

            MM.StopTransaction(mtr);
        }

        private void ButtonCancel_OnClick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void OkBtn_OnClick(object sender, RoutedEventArgs e)
        {
            _newName = txtBox.Text;

            // check correct input
            var regexItem = new Regex("^[a-zA-Z0-9]*$");
            if (_newName.Length == 0 || !regexItem.IsMatch(_newName))
            {
                MessageBox.Show("Please enter the correct text using \nthe following characters: A-Z, a-z, 0-9.",
                    "Invalid input", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txtBox.Text = "";
                return;
            }

            if (IsHaveSameName())
            {
                MessageBox.Show("Name already exist.\nPlease enter another name.", "Invalid input",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txtBox.Text = "";
                return;
            }

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvEntity pEn = _curEntityId.openObject(OpenMode.kForWrite);
            pEn.setName(_newName);

            OdTvGsView view = _viewId.openObject();
            if (view == null)
            {
                MM.StopTransaction(mtr);
                return;
            }

            SaveTvViewParams tvViewParam = new SaveTvViewParams();
            tvViewParam.SetPosition(view.position());
            tvViewParam.SetTarget(view.target());
            tvViewParam.SetUpVector(view.upVector());
            tvViewParam.SetProjection(view.isPerspective() ? OdTvGsView.Projection.kPerspective
                : OdTvGsView.Projection.kParallel);
            tvViewParam.SetRenderMode(view.mode());
            tvViewParam.SetSize(view.fieldWidth(), view.fieldHeight());

            // append user data
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(tvViewParam));
            Marshal.StructureToPtr(tvViewParam, ptr, false);
            int size = Marshal.SizeOf(typeof(SaveTvViewParams));
            OdTvByteUserData data = new OdTvByteUserData(ptr, (uint)size, OdTvByteUserData.Ownership.kCopyOwn, true);
            pEn.appendUserData(data, OdTvWpfView.AppTvId);
            Marshal.FreeHGlobal(ptr);

            // Write userdata to geometry, this is need for correct removing markups
            OdTvGeometryDataIterator pItF = pEn.getGeometryDataIterator();
            // folders
            while (!pItF.done())
            {
                OdTvEntity pSubEn = pItF.getGeometryData().openAsSubEntity();
                OdTvGeometryDataIterator pIt2 = pSubEn.getGeometryDataIterator();
                // objects
                while (!pIt2.done())
                {
                    OdTvEntity pObj = pIt2.getGeometryData().openAsSubEntity(OpenMode.kForWrite);
                    IntPtr ptr2 = Marshal.AllocHGlobal(sizeof(byte));
                    Marshal.WriteByte(ptr2, 1);
                    OdTvByteUserData bdata = new OdTvByteUserData(ptr2, sizeof(byte), OdTvByteUserData.Ownership.kCopyOwn, true);
                    pObj.appendUserData(bdata, OdTvWpfView.AppTvId);
                    Marshal.FreeHGlobal(ptr2);

                    pIt2.step();
                }
                pItF.step();
            }

            MM.StopTransaction(mtr);

            DialogResult = true;
        }

        private bool IsHaveSameName()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (_newName == OdTvMarkupDragger.NameOfMarkupTempEntity)
            {
                MM.StopTransaction(mtr);
                return true;
            }

            OdTvEntitiesIterator it = _markupModelId.openObject().getEntitiesIterator();
            while (!it.done())
            {
                if (it.getEntity().openObject().getName() == _newName &&
                    !it.getEntity().IsEqual(_curEntityId))
                {
                    MM.StopTransaction(mtr);
                    return true;
                }
                it.step();
            }

            return false;
        }

        private void SaveMarkupDialog_OnContentRendered(object sender, EventArgs e)
        {
            txtBox.Focus();
            txtBox.SelectAll();
        }
    }
}
