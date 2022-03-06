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

#ifndef __TNW_PROPERTY_ATTRIBUTE_H__
#define __TNW_PROPERTY_ATTRIBUTE_H__

#include "NwAttribute.h"

class OdNwProperty;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwProperty object pointers.
*/
typedef OdSmartPtr<OdNwProperty> OdNwPropertyPtr;

/** \details
  This class represents an attribute with set of properties having different value's types.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPropertyAttribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwPropertyAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwPropertyAttribute
    class.
  */
  OdNwPropertyAttribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPropertyAttribute();

public:
  /** \details
    Gets the properties of the attribute as array.
    
    \param aProperties [out] OdArray with smart pointers to properties.

    \returns eOk if the operation is successful, or an appropriate error code otherwise.
  */
  OdResult getProperties(OdArray<OdNwPropertyPtr>& aProperties);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwPropertyAttribute object pointers.
*/
typedef OdSmartPtr<OdNwPropertyAttribute> OdNwPropertyAttributePtr;

#endif //__TNW_PROPERTY_ATTRIBUTE_H__
