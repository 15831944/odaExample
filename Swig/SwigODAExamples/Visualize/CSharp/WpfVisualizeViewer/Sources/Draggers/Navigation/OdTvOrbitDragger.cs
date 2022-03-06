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
using System.Drawing;
using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer
{
    public class OdTvOrbitDragger : OdTvDragger
    {
        private Cursor _orbitCursor = Cursors.Default;
        // last clicked or moved point (WCS)
        private OdGePoint3d _prevPt = null;
        // center of scene
        private OdGePoint3d _center = null;
        // mouse move to rotation angle conversion coefficient
        private double _coef = 16d;

        private new MemoryManager MM = MemoryManager.GetMemoryManager();

        public OdTvOrbitDragger(OdTvGsDeviceId tvDeviceId, OdTvModelId tvDraggersModelId)
            : base(tvDeviceId, tvDraggersModelId)
        {
            Bitmap bitmap = new Bitmap(new Bitmap("Images/Navigation/orbit.png"), 20, 20);
            IntPtr handle = bitmap.GetHicon();
            _orbitCursor = new Cursor(handle);
        }

        public override DraggerResult NextPoint(int x, int y)
        {
            if (State == DraggerState.Waiting || TvView == null)
                return DraggerResult.NothingToDo;

            // calculate click point in WCS
            OdGePoint3d pt = ToEyeToWorld(x, y);
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = TvView.openObject();
            // transfer point to the eye coordinate system
            _prevPt = view.viewingMatrix() * pt;

            // calculate mouse move to rotation angle conversion coefficient in base of viewport dc size
            OdGePoint2d pt1 = new OdGePoint2d();
            OdGePoint2d pt2 = new OdGePoint2d();
            view.viewDcCorners(pt1, pt2);
            pt2.x -= pt1.x;
            pt2.y -= pt1.y;
            double r = Math.Min(pt2.x, pt2.y);
            _coef = r;

            // here we should to remember the extents since we want to rotate the scene about this point

            OdGeBoundBlock3d extents = new OdGeBoundBlock3d();
            view.viewExtents(extents);
            _center = extents.center();
            _center.transformBy(view.eyeToWorldMatrix());

            MM.StopTransaction(mtr);

            return DraggerResult.NothingToDo;
        }

        public override DraggerResult Drag(int x, int y)
        {
            if (State == DraggerState.Waiting || TvView == null)
                return DraggerResult.NothingToDo;

            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = TvView.openObject();

            // calculate click point in WCS
            OdGePoint3d pt = ToEyeToWorld(x, y);

            // transfer point to the eye coordinate system
            OdGePoint3d ptView = view.viewingMatrix() * pt;

            // calculate the angles for the rotation about appropriate axes
            double distX = ptView.x - _prevPt.x; // around vertical
            double distY = ptView.y - _prevPt.y; // around horizontal

            distX *= -Math.PI / _coef;
            distY *= Math.PI / _coef;

            // perform camera orbiting
            OdGeVector3d target = view.target().asVector();
            OdGeVector3d delta = _center.asVector() - target;
            delta.transformBy(view.viewingMatrix());

            // the rotation should be performed around the center of the extents.
            // That's why at first we should move the camera with purpose make target equal to the center of the extents.
            // Then we should perform the rotation and finally we should to move the camera in opposite direction
            view.dolly(delta);
            view.orbit(distY, distX);
            view.dolly(-delta);

            // set orbit for view
            OdTvGsView wcsView = WCS == null ? null : WCS.GetWcsViewId().openObject(OpenMode.kForWrite);
            if (wcsView != null)
            {
                OdGeVector3d targetWcs = wcsView.target().asVector();
                // center of wcs minus target wcs
                OdGeVector3d deltaWcs = -targetWcs;
                deltaWcs.transformBy(wcsView.viewingMatrix());

                wcsView.dolly(deltaWcs);
                wcsView.orbit(distY, distX);
                wcsView.dolly(-deltaWcs);
            }

            // store previous click point
            _prevPt = ptView;

            MM.StopTransaction(mtr);

            return DraggerResult.NeedUpdateView;
        }

        public override DraggerResult NextPointUp(int x, int y)
        {
            return Reset();
        }

        public override bool UpdateCursor()
        {
            CurrentCursor = State == DraggerState.Finishing ? LasAppActiveCursor : _orbitCursor;
            return true;
        }

        public override bool CanFinish()
        {
            return true;
        }
    }
}
