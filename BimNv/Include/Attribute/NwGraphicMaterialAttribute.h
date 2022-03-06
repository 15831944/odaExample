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

#ifndef __TNW_GRAPHIC_MATERIAL_ATTRIBUTE_H__
#define __TNW_GRAPHIC_MATERIAL_ATTRIBUTE_H__

#include "NwAttribute.h"

class OdNwGraphicJsonBundle;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGraphicJsonBundle object pointers.
*/
typedef OdSmartPtr<OdNwGraphicJsonBundle> OdNwGraphicJsonBundlePtr;

/** \details
  This class represents an attribute with graphic material which represented as set of properties in JSON.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGraphicMaterialAttribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGraphicMaterialAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwGraphicMaterialAttribute object.
  */
  OdNwGraphicMaterialAttribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGraphicMaterialAttribute();

public:
  /** \details
    Returns a graphic JSON object with material's properties.

    \returns Smart pointer to the OdNwGraphicJsonBundle object, or an empty
    smart pointer if the object does not exist.
  */
  OdNwGraphicJsonBundlePtr getGraphicJson() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGraphicMaterialAttribute object pointers.
*/
typedef OdSmartPtr<OdNwGraphicMaterialAttribute> OdNwGraphicMaterialAttributePtr;

#endif //__TNW_GRAPHIC_MATERIAL_ATTRIBUTE_H__
