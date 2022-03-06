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

#ifndef _ODDbDETAILSYMBOLIMPL_INCLUDED_
#define _ODDbDETAILSYMBOLIMPL_INCLUDED_

#include "DbDetailSymbol.h"
#include "DbDetailViewStyle.h"
#include "DbViewSymbolImpl.h"

class OdDbDetailSymbolImpl : public OdDbViewSymbolImpl
{
public:
  static OdDbDetailSymbolImpl* getImpl(const OdDbDetailSymbol* pObj)
  { 
    return (OdDbDetailSymbolImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbDetailSymbolImpl();
protected:
  friend class OdDbDetailSymbol;

  // OdDbViewSymbolImpl methods :
  virtual OdResult getIdentifier(OdString& sName) const;
  virtual OdResult setIdentifier(const OdString& sName);

  OdDbDetailSymbol::BoundaryType m_boundaryType;
  OdDbDetailViewStyle::ModelEdge m_modelEdgeType;
  OdGePoint3d m_origin;
  OdGeVector2d m_boundarySize;
  OdString m_sIdentifier; // A
  OdDbDetailSymbol::OverriddenProperty m_overridenProperty; // 0
  bool m_displayIdentifier; // true // is not saved
  OdGePoint3d m_modelEdgeOrigin;
  double m_owningViewScale;
  double m_detailViewScale;
  OdGeVector3d m_indentifierPositionOffset; // -8.770595741368879 8.280052019541898 0.0
  OdGeVector3d m_modelEdgeDirection; // 1.0 8.326673E-017 0.0
  //OdGeVector3d m_direction; // 1.0 0.0 0.0
};

#endif // _ODDbDETAILSYMBOLIMPL_INCLUDED_
