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

#ifndef __TNW_TRANSFORM_ATTRIBUTE_H__
#define __TNW_TRANSFORM_ATTRIBUTE_H__

#include "NwAttribute.h"

class OdGeMatrix3d;

/** \details
  This class represents a transformation attribute.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwTransformAttribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwTransformAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwTransformAttribute
    class.
  */
  OdNwTransformAttribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwTransformAttribute();

public:
  /** \details
    Returns the transformation matrix of attribute.

    \returns OdGeMatrix3d object with transformation matrix of model item.
  */
  OdGeMatrix3d getTransform() const;

  /** \details
    Returns the flag that this transformation is reversed.
    
    \returns True if transformation matrix is reversed, or false if not.
  */
  bool isReverse() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwTransformAttribute object pointers.
*/
typedef OdSmartPtr<OdNwTransformAttribute> OdNwTransformAttributePtr;

#endif //__TNW_TRANSFORM_ATTRIBUTE_H__
