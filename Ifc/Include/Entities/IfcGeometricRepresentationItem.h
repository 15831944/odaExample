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

// IfcGeometricRepresentationItem.h: interface for the OdIfcGeometricRepresentationItem class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_GEOMETRICREPRESENTATIONITEM_H_
#define _IFC_GEOMETRICREPRESENTATIONITEM_H_

#include "IfcRepresentationItem.h"
#include "IfcBodyVariant.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details 
  The class that implements work with geometry representation items for IFC SDK.
  */
  class IFCGEOM_EXPORT OdIfcGeometricRepresentationItem : public OdIfcRepresentationItem
  {
    ODRX_DECLARE_MEMBERS(OdIfcGeometricRepresentationItem);

  public:
    /** \details 
    Retrieves the body container.
    \returns An instance of the <link OdIfc::OdIfcBodyVariant, OdIfcBodyVariant> class that represents the body container.
    */
    virtual OdIfcBodyVariant bodyContainer() const;
  };
  
  /** \details
  A data type that represents a smart pointer to an <link OdIfc::OdIfcGeometricRepresentationItem, OdIfcGeometricRepresentationItem> object.
  */
  SMARTPTR(OdIfcGeometricRepresentationItem);

}

#endif // _IFC_GEOMETRICREPRESENTATIONITEM_H_

