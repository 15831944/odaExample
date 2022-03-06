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
#ifndef _IFC_GIAUXDATA_H_
#define _IFC_GIAUXDATA_H_

#include "GiDefaultContext.h"
#include "IfcFile.h"

#include "IfcBuildOptions.h"

#include "TD_PackPush.h"

class OdGiAuxDataForIfc;

/** \details
This template class is a specialization of the OdSmartPtr class for OdGiAuxDataForIfc object pointers.
*/
typedef OdSmartPtr<OdGiAuxDataForIfc> OdGiAuxDataForIfcPtr;

/** \details
    This class defines the operations and properties that are used in the
    vectorization of an OdIfcFile.
*/
class IFCCORE_EXPORT OdGiAuxDataForIfc : public OdGiAuxiliaryData
{
public:

  ODRX_DECLARE_MEMBERS(OdGiAuxDataForIfc);

  OdGiAuxDataForIfc();

  virtual OdGiLayerOverridesPtr getLevelOverrides() const;

  virtual void setLevelOverrides(const OdGiLayerOverridesPtr& pLevelOverrides);

  OdIfc::OdIfcEntityPtr currentRepresentationItem()
  {
    return m_pCurrentRepresentationItem;
  }

  void setCurrentRepresentationItem(OdIfc::OdIfcEntity *representationItem)
  {
    m_pCurrentRepresentationItem = representationItem;
  }

private:

  OdIfc::OdIfcEntity *m_pCurrentRepresentationItem;
  
};

#include "TD_PackPop.h"

#endif // _IFC_GIAUXDATA_H_
