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

#ifndef _IFC_API_UTILS_H
#define _IFC_API_UTILS_H

#include "IfcBuildOptions.h"
#include "daiObjectId.h"

class OdIfcFile;

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  class OdIfcEntity;
  
  /** \details
  Contains declarations related to working with IFC files content.
  */
  namespace Utils
  {
    /** \details
    Assigns a generated global identifier to the &quot;GlobalId&quot; attribute  of an entity derived from an IfcRoot object.
    \param pInst [in] A raw pointer to the IFC entity instance.
    \returns true if the attribute &quot;GlobalId&quot; was successfully assigned; otherwise the method returns false.
    */
    bool IFCCORE_EXPORT assignGlobalId(OdIfcEntity *pInst);

    /** \details
    Retrieves identifiers (represented with the <link OdDAIObjectIds, OdDAIObjectIds> object) 
    of default IfcGeometricRepresentationContext instances, 
    which are necessary to get the geometrical representation of a model of the specified IFC file.
    \param pIfcFile [in] A raw pointer to an <link OdIfcFile, OdIfcFile> object that keeps the IFC model.
    \param onlyBody [in] A flag that determines that only sub-contexts with the &quot;Body&quot; identifiers are selected (if it is equal to true). 
    \returns 
     An <link OdDAIObjectIds, array of OdDAIObjectId> instances, which contain identifiers 
     that refer to geometric representation context objects; if nothing was selected, the method returns an empty array.
    */
    OdDAIObjectIds IFCCORE_EXPORT getDefaultRepresentationContextsSelection(const OdIfcFile *pIfcFile, bool onlyBody = true);

    /** \details
    Retrieves identifiers (represented with the <link OdDAIObjectIds, OdDAIObjectIds> object) 
    of all IfcGeometricRepresentationContext instances in a model of the specified IFC file.
    \param pIfcFile [in] A raw pointer to an <link OdIfcFile, OdIfcFile> object that keeps the IFC model.
    \returns 
     An <link OdDAIObjectIds, array of OdDAIObjectId> instances, which contain identifiers 
     that refer to geometric representation context objects; if nothing was selected, the method returns an empty array.
    */
    OdDAIObjectIds IFCCORE_EXPORT getAllRepresentationContexts(const OdIfcFile *pIfcFile);
  }
}

#endif // _IFC_API_UTILS_H
