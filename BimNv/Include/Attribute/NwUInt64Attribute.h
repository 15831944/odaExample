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

#ifndef __TNW_UINT64_ATTRIBUTE_H__
#define __TNW_UINT64_ATTRIBUTE_H__

#include "NwAttribute.h"

/** \details
  This class represents an attribute with UInt64 value.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwUInt64Attribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwUInt64Attribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwUInt64Attribute
    class.
  */
  OdNwUInt64Attribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwUInt64Attribute();

public:
  /** \details
    Returns the UInt64 value of attibute.
    
    \returns OdUInt64 with attribute value.
  */
  OdUInt64 getValue() const;

  /** \details
    Checks whether the attribute is a stable ID.

    \returns true if the attribute is a stable ID, or false otherwise.

    \remarks
    if attribute is stable id then uint64 stable id can be gets by method OdUInt64 OdNwUInt64Attribute::getValue() const.
  */
  bool isStableId() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwUInt64Attribute object pointers.
*/
typedef OdSmartPtr<OdNwUInt64Attribute> OdNwUInt64AttributePtr;

#endif //__TNW_UINT64_ATTRIBUTE_H__
