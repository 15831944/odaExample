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
using System.Linq;
using System.Windows.Controls;

namespace WpfVisualizeViewer.ModelBrowser
{
    public class IntTextBox : TextBox
    {
        public IntTextBox()
        {
            ToolTip = "Allowed symbols: '0-9'";
            MaxLength = 8;
        }

        protected override void OnTextChanged(TextChangedEventArgs e)
        {
            int sel = SelectionStart;
            base.OnTextChanged(e);
            string oldTxt = Text;
            Text = new String(Text.Where(c => Char.IsDigit(c)).ToArray());
            this.SelectionStart = oldTxt != Text ? sel - 1 : sel;
        }
    }

    public class DoubleTextBox : TextBox
    {
        public DoubleTextBox()
        {
            ToolTip = "Allowed symbols: '0-9', '.' and ','";
            MaxLength = 8;
        }

        protected override void OnTextChanged(TextChangedEventArgs e)
        {
            int sel = SelectionStart;
            base.OnTextChanged(e);
            string oldTxt = Text;
            Text = new String(Text.Where(c => Char.IsDigit(c) || c == ',' || c == '.').ToArray());
            if (Text.Contains('.'))
            {
                Text.Replace('.', ',');
            }
            if (sel > 0)
                this.SelectionStart = oldTxt != Text ? sel - 1 : sel;
        }
    }
}
