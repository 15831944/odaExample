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

#ifndef _PRCBASEGEOMETRY_INCLUDED_
#define _PRCBASEGEOMETRY_INCLUDED_ 
 

#include "PrcAttributeData.h"
#include "PrcName.h"

/** \details
<group PRC_Base_Classes>
Class stores base PRC geometry information.
*/
class PRC_TOOLKIT OdPrcBaseGeometry
{
private:
  void     initData();
  void     deleteData();
  struct   Data;
  Data    *m_pData;
  Data    *getData();
public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcBaseGeometry)
  //DOM-IGNORE-END

  /** \details 
  Destroys the base PRC geometry information object.
  */
  ~OdPrcBaseGeometry();
  
  /** \details 
  Sets a new value of the base information flag.
  The base information flag determines whether an entity has base geometry information. If it is equal to true, the information is available; if such information is not available the flag is equal to false.
  
  \param value [in] A new value of the base information flag.
  */
  void setBaseInformation(bool value);
  
  /** \details 
  Returns the current value of the base information flag.
  The base information flag determines whether an entity has base geometry information. If it is equal to true, the information is available; if such information is not available the flag is equal to false.
  */
  bool hasBaseInformation() const;
  
  /** \details 
  Returns current attribute data associated with the PRC geometry. 
  The attribute data is returned as a reference to an OdPrcAttributeData object, therefore it can be used to set a new value of the geometry attribute data. 
  */
  OdPrcAttributeData &attributeData();
  
  /** \details
  Returns current attribute data associated with the PRC geometry.
  If the geometry has no base information (base information flag is equal to false), throws an eNullObjectPointer exception.
  */
  const OdPrcAttributeData &attributeData() const;
  
  /** \details
  Returns the current name of the PRC geometry.
  The name is returned as a reference to an OdPrcName object, therefore it can be used to set a new value of the geometry name.
  */
  OdPrcName &name();
  
  /** \details
  Returns the current name of the PRC geometry.
  If the geometry has no base information (base information flag is equal to false), throws an eNullObjectPointer exception.
  */
  const OdPrcName &name() const;
  
  /** \details
  Sets a new identifier for the geometry.
  The identifier is used to refer to the geometry in the original CAD application and should not be used for referencing geometry in the PRC entity.
  
  \param value [in] A new identifier value to be set.
  */
  void setIdentifier(OdUInt32 value);
  
  /** \details
  Returns the current value of the geometry identifier.
  Identifier is used to refer to the geometry in the original CAD application and should not be used for referencing geometry in the PRC entity.
  If the geometry has no base information (base information flag is equal to false), throws eNullObjectPointer exception.
  */
  OdUInt32 identifier() const;
};

#endif // _PRCBASEGEOMETRY_INCLUDED_

