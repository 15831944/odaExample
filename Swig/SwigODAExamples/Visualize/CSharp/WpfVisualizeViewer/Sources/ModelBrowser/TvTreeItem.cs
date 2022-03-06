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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser
{
    public class TvTreeItem : TreeViewItem
    {
        private TextBlock _textBlock = null;

        public TvNodeData NodeData;

        public bool PerSession { get; set; }

        public TvTreeItem(string name, BitmapImage img, TvTreeItem parent, TvNodeData nodeData, OdTvWpfMainWindowModel vm)
        {
            Margin = new Thickness(0, 4, 0, 4);
            PerSession = true;
            this.DataContext = vm;
            NodeData = nodeData;
            StackPanel panel = new StackPanel() { Orientation = Orientation.Horizontal };
            //Image newImg = new Image
            //{
            //    Source = img,
            //    Width = 13,
            //    Height = 13
            //};
            //panel.Children.Add(newImg);
            _textBlock = new TextBlock()
            {
                Text = " " + name,
                FontSize = 13,
                FontFamily = new FontFamily("Open Sans"),
                Foreground = new SolidColorBrush(new Color() { A = 255, R = 40, G = 53, B = 147 })
            };
            panel.Children.Add(_textBlock);
            this.Header = panel;

            if (parent != null)
                parent.Items.Add(this);

            if (NodeData.Type == TvBrowserItemType.Models || NodeData.Type == TvBrowserItemType.Entity
                || NodeData.Type == TvBrowserItemType.Geometry)
            {
                ContextMenu = new ContextMenu();
                if (NodeData.Type == TvBrowserItemType.Entity || NodeData.Type == TvBrowserItemType.Geometry)
                {
                    AddContextMenuItem("Isolate", App.Current.Resources["MbIsolateImg"] as BitmapImage, new Size(16, 12));
                    AddContextMenuItem("Hide", App.Current.Resources["MbHideImg"] as BitmapImage, new Size(17, 12));
                }
                else
                    AddContextMenuItem("Unisolate", App.Current.Resources["MbUnisoImg"] as BitmapImage, new Size(17, 11));
            }

            this.Selected += TvTreeItem_Selected;
        }

        private void TvTreeItem_Selected(object sender, RoutedEventArgs e)
        {
            var vm = (OdTvWpfMainWindowModel)DataContext;
            if (IsSelected && vm != null)
                vm.ItemClickCommand.Execute(sender);
        }

        private void AddContextMenuItem(string header, BitmapImage img, Size size)
        {
            MenuItem item = new MenuItem() { Header = header };
            Image ico = new Image
            {
                Source = img,
                Width = size.Width,
                Height = size.Height
            };
            item.Icon = ico;
            item.Click += MenuItem_Click;
            if (ContextMenu != null)
                ContextMenu.Items.Add(item);
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            MenuItem itm = sender as MenuItem;
            if (itm == null)
                return;

            MemoryTransaction mtr = MemoryManager.GetMemoryManager().StartTransaction();

            switch (itm.Header.ToString())
            {
                case "Unisolate":
                    if (NodeData != null && NodeData.ModelId != null && !NodeData.ModelId.isNull())
                        NodeData.ModelId.openObject(OpenMode.kForWrite).unIsolate();
                    break;
                case "Isolate":
                    {
                        OdTvModelId id = FindParentModel();
                        OdTvModel model = id.openObject(OpenMode.kForWrite);
                        if (NodeData.EntityId != null)
                            model.isolate(NodeData.EntityId, PerSession);
                        else if (NodeData.SubEntId != null)
                            model.isolate(NodeData.SubEntId, PerSession);
                        else if (NodeData.GeomId != null)
                            model.isolate(NodeData.GeomId, PerSession);
                        break;
                    }
                case "Hide":
                    {
                        OdTvModelId id = FindParentModel();
                        OdTvModel model = id.openObject(OpenMode.kForWrite);
                        if (NodeData.EntityId != null)
                            model.hide(NodeData.EntityId, PerSession);
                        else if (NodeData.SubEntId != null)
                            model.hide(NodeData.SubEntId, PerSession);
                        else if (NodeData.GeomId != null)
                            model.hide(NodeData.GeomId, PerSession);
                        break;
                    }
            }

            if (NodeData != null && NodeData.DeviceId != null && !NodeData.DeviceId.isNull())
                NodeData.DeviceId.openObject().update();

            MemoryManager.GetMemoryManager().StopTransaction(mtr);
        }

        private OdTvModelId FindParentModel()
        {
            OdTvModelId id = null;
            TvTreeItem itm = Parent as TvTreeItem;
            id = itm.NodeData.ModelId;
            if (id == null)
                id = itm.FindParentModel();
            return id;
        }

        public void SetBold(bool isBold = true)
        {
            if (isBold)
                _textBlock.SetValue(TextBlock.FontWeightProperty, FontWeights.Bold);
            else
                _textBlock.SetValue(TextBlock.FontWeightProperty, FontWeights.Normal);
        }
    }
}
