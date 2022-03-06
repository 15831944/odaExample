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

#ifndef DbImpAssocViewLabelActionParam_INCLUDED_
#define DbImpAssocViewLabelActionParam_INCLUDED_ /*!DOM*/

#include "DbAssocViewLabelActionParam.h"
#include "DbImpAssocActionParam.h"

#include "TD_PackPush.h"

/** \details
  This class implements the view label action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class SYNERGYOBJDPW_EXPORT OdDbImpAssocViewLabelActionParam : public OdDbImpAssocObjectActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdDbImpAssocViewLabelActionParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdDbImpAssocViewLabelActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler, OdDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdDbDwgFiler* pFiler, OdDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler, OdDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdDbDxfFiler* pFiler, OdDbObjectId objectId) const;

protected:

  OdGeVector2d  m_vLabelOffset;         // 
  OdGeVector2d  m_vInit;                // Not saved to file: use to return the original value of the vector m_vNormal after the call
                                        //                    setAttachmentPointOverride (AcDbModelDocViewStyle::kBelowView, true)
  OdUInt16      m_nPropertyOverrides;   // contains flags LabelOverridesProperty
  OdUInt8       m_nAttachPoint;         // 0 - attachmentPoint() = OdDbModelDocViewStyle::kAboveView
                                        // 1 - attachmentPoint() = OdDbModelDocViewStyle::kBelowView

  friend class OdDbAssocViewLabelActionParam;
};

#include "TD_PackPop.h"

#endif // DbImpAssocViewLabelActionParam_INCLUDED_
