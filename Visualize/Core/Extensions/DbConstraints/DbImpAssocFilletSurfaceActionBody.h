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
#ifndef DbImpAssocFilletSurfaceActionBody_INCLUDED_
#define DbImpAssocFilletSurfaceActionBody_INCLUDED_ /*!DOM*/

#include "DbImpAssocExtrudedSurfaceActionBody.h"
#include "DbBlendOptions.h"

#include "TD_PackPush.h"

//enum FilletTrimMode {
//  kTrimNone = 0,
//  kTrimFirst = 1,
//  kTrimSecond = 2,
//  kTrimBoth = 3
//};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
This class represents the custom implementation of the action body based on ImpAssocAnnotationActionBody.

Library: Source code provided.
<group Contraint_Classes>
*/

class DBCONSTRAINTS_EXPORT OdTvDbImpAssocFilletSurfaceActionBody : public OdTvDbImpAssocSurfaceActionBody// OdTvDbImpAssocAnnotationActionBody
{
public:
  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbImpAssocFilletSurfaceActionBody();

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocFilletSurfaceActionBody();

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Reads the .dxf file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
  Writes the .dxf file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  /** \details
  Returns a pointer to the array of parameters for writing.
  */
  //const OdTvDbSmartCenterMarkParametersPtr parameters() const;
  //OdTvDbSmartCenterMarkParametersPtr& parameters();

  //virtual void composeForLoad(OdTvDbObject *pObject, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(OdTvDbObjectId parentActionId);

  /// <summary><para> 
  /// Set radius of the resulting surface
  /// </para><para>
  OdResult setRadius(OdTvDbAssocActionPtr pAction, OdDouble dRadius, const OdString& expression,
    const OdString& evaluatorId);

  /// <summary><para> 
  /// Get radius of the resulting surface
  /// </para><para>
  OdDouble radius(const OdTvDbAssocActionPtr pAction, OdString& expression , OdString& evaluatorId ) const;

private:
  OdUInt16 m_unknownInt16_0;
  OdInt16 m_unknownInt16;
  OdGePoint2d m_point1;
  OdGePoint2d m_point2;
};

#include "TD_PackPop.h"

#endif
