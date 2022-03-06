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

// IfcBuildingStorey.h: interface for the OdIfcBuildingStorey class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_BUILDINGSTOREY_H_
#define _IFC_BUILDINGSTOREY_H_

#include "IfcSpatialStructureElement.h"

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details 
  A class that implements storing handling data about a building storey. A building storey instance represents vertically bound spaces aggregated horizontally.
  */
  class IFCGEOM_EXPORT OdIfcBuildingStorey : public OdIfcSpatialStructureElement
  {
    ODRX_DECLARE_MEMBERS(OdIfcBuildingStorey);

  public:

    /** \details 
    Composes the building storey object.
    \param pFile [in] A raw pointer to an OdIfcFile object.
    */
    virtual void compose();
  };
  SMARTPTR(OdIfcBuildingStorey)

}

#endif // _IFC_BUILDINGSTOREY_H_

