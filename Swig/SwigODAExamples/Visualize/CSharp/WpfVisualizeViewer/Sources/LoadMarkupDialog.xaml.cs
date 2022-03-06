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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.Dialogs
{
    /// <summary>
    /// Interaction logic for LoadMarkupDialog.xaml
    /// </summary>
    public partial class LoadMarkupDialog : Window
    {
        private OdTvModelId _markupModelId;
        private OdTvGsViewId _viewId;
        private OdTvWpfView _wpfView;

        private MemoryManager MM = MemoryManager.GetMemoryManager();

        private TvListNode _currentNode;

        public LoadMarkupDialog(OdTvModelId markupModelId, OdTvGsViewId viewId, OdTvWpfView wpfView)
        {
            InitializeComponent();
            this.Owner = App.Current.MainWindow;
            _markupModelId = markupModelId;
            _viewId = viewId;
            _wpfView = wpfView;
            FillList();
        }

        private void FillList()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvEntitiesIterator it = _markupModelId.openObject().getEntitiesIterator();
            while (!it.done())
            {
                OdTvEntityId enId = it.getEntity();
                if (enId.openObject().getUserData(OdTvWpfView.AppTvId) != null)
                    List.Items.Add(new TvListNode(enId));

                it.step();
            }

            MM.StopTransaction(mtr);
        }

        private void ButtonLoad_OnClick(object sender, RoutedEventArgs e)
        {
            if (_currentNode == null)
                return;

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvEntitiesIterator pEnIt = _markupModelId.openObject().getEntitiesIterator();
            while (!pEnIt.done())
            {
                OdTvEntityId entId = pEnIt.getEntity();
                OdTvEntity pEnt = entId.openObject(OpenMode.kForWrite);
                if (entId.IsEqual(_currentNode.EntityId))
                {
                    OdTvUserData usrData = pEnt.getUserData(OdTvWpfView.AppTvId);
                    OdTvByteUserData res = new OdTvByteUserData(OdTvUserData.getCPtr(usrData).Handle, false);
                    IntPtr ptr = res.getData();
                    SaveTvViewParams viewParams = (SaveTvViewParams)Marshal.PtrToStructure(ptr, typeof(SaveTvViewParams));

                    // fill active and wcs view params from binary user data
                    OdTvExtendedView exView = _wpfView.GetActiveTvExtendedView();
                    if (exView != null)
                    {
                        exView.setView(new OdGePoint3d(viewParams.PositionX, viewParams.PositionY, viewParams.PositionZ),
                            new OdGePoint3d(viewParams.TargetX, viewParams.TargetY, viewParams.TargetZ),
                            new OdGeVector3d(viewParams.UpVectorX, viewParams.UpVectorY, viewParams.UpVectorZ),
                            viewParams.Width, viewParams.Height, (OdTvGsView.Projection)viewParams.Projection);
                        exView.setRenderMode((OdTvGsView.RenderMode)viewParams.RenderMode);
                        _wpfView.SetAnimation(exView.getAnimation());
                    }
                    else
                    {
                        OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
                        if (view != null)
                        {
                            view.setView(
                                new OdGePoint3d(viewParams.PositionX, viewParams.PositionY, viewParams.PositionZ),
                                new OdGePoint3d(viewParams.TargetX, viewParams.TargetY, viewParams.TargetZ),
                                new OdGeVector3d(viewParams.UpVectorX, viewParams.UpVectorY, viewParams.UpVectorZ),
                                viewParams.Width, viewParams.Height, (OdTvGsView.Projection) viewParams.Projection);
                            view.setMode((OdTvGsView.RenderMode) viewParams.RenderMode);
                        }
                    }
                    pEnt.setVisibility(new OdTvVisibilityDef(true));
                }
                else
                    pEnt.setVisibility(new OdTvVisibilityDef(false));
                pEnIt.step();
            }

            DialogResult = true;

            MM.StopTransaction(mtr);
        }

        private void ButtonDelete_OnClick(object sender, RoutedEventArgs e)
        {
            if (_currentNode == null)
                return;

            MemoryTransaction mtr = MM.StartTransaction();
            _markupModelId.openObject(OpenMode.kForWrite).removeEntity(_currentNode.EntityId);
            List.Items.Remove(_currentNode);
            _currentNode = null;
            MM.StopTransaction(mtr);
        }

        private void OnSelectedItem(object sender, MouseButtonEventArgs e)
        {
            _currentNode = sender as TvListNode;
        }

        private class TvListNode : ListViewItem
        {
            public OdTvEntityId EntityId { get; private set; }

            public TvListNode(OdTvEntityId id)
            {
                EntityId = id;
                MemoryTransaction mrt = MemoryManager.GetMemoryManager().StartTransaction();
                Content = id.openObject().getName();
                MemoryManager.GetMemoryManager().StopTransaction(mrt);
            }
        }
    }
}
