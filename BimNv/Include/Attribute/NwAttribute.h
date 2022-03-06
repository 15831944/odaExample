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

#ifndef __TNW_ATTRIBUTE_H__
#define __TNW_ATTRIBUTE_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"

/** \details
  This class represents a base class for model item's attributes.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwAttribute : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwAttribute
    class.
  */
  OdNwAttribute();

  /** \details
    Constructor for objects of the OdNwAttribute class. Creates a new
    OdNwAttribute object for the specified item.

    \param pImpl [in] Item to create a OdNwAttribute object for.
  */
  explicit OdNwAttribute(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwAttribute();

public:
  /** \details
    Returns the flag that this attribute is internal.
  
    \returns True if attribute is for internal using, or false if not.
  */
  bool isInternal() const;

  /** \details
    Returns the flag that this attribute is render.
    
    \returns True if attribute is involved in rendering, or false if not.
  */
  bool isRenderAttribute() const;

  /** \details
    Returns the display name for the type of the attribute.
    
    \returns Display name for the type of the attribute.
    
    \remarks
    Display name is derrived from the type in the original design application.
  */
  OdString getClassDisplayName() const;

  /** \details
    Returns the name of the type of the attribute.
    
    \returns Name of the type of the attribute.
    
    \remarks
    Name is derrived from the type in the original design application.
  */
  OdString getClassName() const;

  /** \details
    Returns the end-user supplied name for the attribute.
    
    \returns End-user supplied name for the attribute.
    
    \remarks
    DisplayName can be empty.
  */
  OdString getDisplayName() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwAttribute object pointers.
*/
typedef OdSmartPtr<OdNwAttribute> OdNwAttributePtr;

#endif //__TNW_ATTRIBUTE_H__
