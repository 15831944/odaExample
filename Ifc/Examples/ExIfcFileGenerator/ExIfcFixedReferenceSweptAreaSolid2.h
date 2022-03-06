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

// ExIfcFixedReferenceSweptAreaSolid2.h: interface for the ExIfcFixedReferenceSweptAreaSolid2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODA_EXIFCFIXEDREFERENCESWEPTAREASOLID2_H_INCLUDED_)
#define ODA_EXIFCFIXEDREFERENCESWEPTAREASOLID2_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcRepresentationBuilder.h"

class ExIfcFixedReferenceSweptAreaSolid2 : public IfcRepresentationAdapter
{
public:
  ExIfcFixedReferenceSweptAreaSolid2(const OdGeMatrix3d& objectPlacement, double overallWidth, double overallDepth, double webThickness, double flangeThickness, double curveScale);

private:
  double m_overallWidth;
  double m_overallDepth;
  double m_webThickness;
  double m_flangeThickness;
  double m_curveScale;

  virtual OdIfc::OdIfcEntityPtr subProcess();
};

#endif // !defined(ODA_EXIFCFIXEDREFERENCESWEPTAREASOLID2_H_INCLUDED_)

