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
using System.Windows.Threading;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer
{
    public class OdTvCaret
    {
        private DispatcherTimer _timer;
        private bool _caretIsShown = false;
        private OdTvGeometryDataId _caretTextData = null;
        private OdTvGsDeviceId _devId;

        public OdTvCaret(ref OdTvGeometryDataId id, OdTvGsDeviceId devId)
        {
            _caretTextData = id;
            _devId = devId;
            _timer = new DispatcherTimer();
            _timer.Tick += new EventHandler(UpdateCaret);
            _timer.Interval = new TimeSpan(0, 0, 0, 0, 400);
            _timer.Start();
        }

        public void Stop()
        {
            _timer.Stop();
        }

        private void UpdateCaret(object sender, EventArgs e)
        {
            if (_caretTextData != null)
            {
                MemoryTransaction mtr = MemoryManager.GetMemoryManager().StartTransaction();
                // Get text data for caret symbol editing
                OdTvTextData pCaretText = _caretTextData.openAsText();

                // Edit caret symbol
                if (!_caretIsShown)
                {
                    pCaretText.setString("|");
                    _caretIsShown = true;
                }
                else
                {
                    pCaretText.setString("");
                    _caretIsShown = false;
                }

                _devId.openObject().update();

                MemoryManager.GetMemoryManager().StopTransaction(mtr);
            }
        }
    }
}