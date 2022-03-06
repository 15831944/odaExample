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

#ifndef _IFC_ALIGNMENT_BUILDER_H
#define _IFC_ALIGNMENT_BUILDER_H

#include "IfcBuilder.h"

#include "Ge/GePolyline2d.h"

class IfcAlignmentBuilder : public IfcBuilder
{
public:


protected:

  OdIfc::OdIfcEntityPtr m_alignment;
  OdIfc::OdIfcEntityPtr m_alignmentCurve;

  OdGeCurve2dPtrArray m_segments;
  OdIfc::OdIfcEntityPtr m_alignmentHorizontal;

  OdAnsiString m_name;

  static OdSmartPtr<IfcAlignmentBuilder> createObject(ExIfcModelFiller *filler, const OdAnsiString &name);

  OdIfc::OdIfcEntityPtr appendIfcAlignment();
  OdIfc::OdIfcEntityPtr createAlignmentHorizontalSegment(const char *predefinedType);

public:

  ODRX_DECLARE_MEMBERS(IfcAlignmentBuilder);

  OdIfc::OdIfcEntityPtr alignmentCurve() { return m_alignmentCurve; };
  OdIfc::OdIfcEntityPtr alignment() { return m_alignment; };

  OdIfc::OdIfcEntityPtr appendHorizontalAlignment(const OdGeCurve2dPtrArray &segments);

  friend class ExIfcModelFiller;
};
typedef OdSmartPtr<IfcAlignmentBuilder> IfcAlignmentBuilderPtr;

#endif // _IFC_ALIGNMENT_BUILDER_H
