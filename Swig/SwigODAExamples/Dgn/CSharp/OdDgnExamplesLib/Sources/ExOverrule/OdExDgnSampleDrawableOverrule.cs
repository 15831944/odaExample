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

using Teigha.Core;
using Teigha.TG;

namespace OdDgnExamplesMgdLib.ExOverrule
{
  public class OdExDgnSampleDrawableOverrule : OdGiDrawableOverrule
  {
    public override bool worldDraw(OdGiDrawable pSubject, OdGiWorldDraw wd)
    {
      // skip rendering any element having this overruling
      OdGiGeometry geom = wd.geometry();
      OdGiSubEntityTraits traits = wd.subEntityTraits();
      wd.subEntityTraits().setTrueColor(new OdCmEntityColor(192, 32, 255));
      //wd.subEntityTraits().setFillType(OdGiFillType.kOdGiFillAlways);
      //wd.subEntityTraits().setColor((ushort)OdCmEntityColor.ACIcolorMethod.kACIBlue);
      OdDgArc3d arc = (OdDgArc3d)pSubject;
      if (arc != null)
      {
        OdGePoint3d pt1 = arc.getOrigin();
        //OdGePoint3d pt2 = pt1;
        //pt2.set(pt1.x + arc.getPrimaryAxis(), pt1.y, pt1.z);
        geom.circle(pt1, arc.getPrimaryAxis(), arc.getNormal());
      }
      return true;
    }
  };
}