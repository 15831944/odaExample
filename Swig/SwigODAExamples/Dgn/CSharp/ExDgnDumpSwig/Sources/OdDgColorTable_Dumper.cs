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
using Teigha.Core;
using Teigha.TG;

namespace ExDgnDumpSwigMgd
{
  class OdDgColorTable_Dumper : OdRxObject_Dumper
  {
    public override void dump(OdRxObject pObject)
    {
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().StartTransaction();
      OdDgColorTable element = (OdDgColorTable)pObject;
      startDescription(element);
      for (int i = 0; i < 256; i++)
      {
        uint color = element.lookupRGB((uint)i);
        Int32 red = (int)color & 0xff;// ODGETRED(color);
        Int32 green = (int)(color >> 8) & 0xff;
        Int32 blue = (int)(color >> 16) & 0xff;

        //sprintf(name, "Color %i - %i, %i, %i", i, red, green, blue);
        writeFieldValue(string.Format("Color {0} - {1}, {2}, {3}", i, red, green, blue), element.lookupRGB((uint)i) /*OdUInt32( i )*/ );
      }
      finishDescription();
      MemoryManager.GetMemoryManager().StopTransaction(mTr);
    }
    public override String getClassName()
    {
      return "OdDgColorTable";
    }
  }
}