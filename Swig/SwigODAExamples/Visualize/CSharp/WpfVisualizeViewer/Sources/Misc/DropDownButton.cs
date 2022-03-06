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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Media.Animation;

namespace WpfVisualizeViewer.Misc
{
    public class DropDownButton : ToggleButton
    {
        // *** Dependency Properties ***

        public static readonly DependencyProperty DropDownProperty = DependencyProperty.Register("DropDown", typeof(ContextMenu), typeof(DropDownButton), new UIPropertyMetadata(null));

        // *** Constructors ***

        public DropDownButton()
        {
            // Bind the ToogleButton.IsChecked property to the drop-down's IsOpen property

            Binding binding = new Binding("DropDown.IsOpen");
            binding.Source = this;
            this.SetBinding(IsCheckedProperty, binding);
        }

        // *** Properties ***

        public ContextMenu DropDown
        {
            get
            {
                return (ContextMenu)GetValue(DropDownProperty);
            }
            set
            {
                SetValue(DropDownProperty, value);
            }
        }

        // *** Overridden Methods ***

        protected override void OnClick()
        {
            if (DropDown != null)
            {
                // If there is a drop-down assigned to this button, then position and display it
                DropDown.PlacementTarget = this;
                DropDown.Placement = PlacementMode.Bottom;

                DoubleAnimation buttonAnimation = new DoubleAnimation();
                buttonAnimation.From = 0;
                buttonAnimation.To = 200;
                buttonAnimation.Duration = TimeSpan.FromSeconds(0.25);
                DropDown.BeginAnimation(WidthProperty, buttonAnimation);

                DropDown.IsOpen = true;
            }
        }
    }

}
