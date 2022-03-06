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

#ifndef _PRCCONTENTSINGLEATTRIBUTE_INCLUDED_
#define _PRCCONTENTSINGLEATTRIBUTE_INCLUDED_ 
 

#include "PrcAttributeEntry.h"
#include "OdTimeStamp.h"

/** \details 
<group PRC_Miscellaneous_Classes> 

Class representing an attribute with its data.
*/
class PRC_TOOLKIT OdPrcContentSingleAttribute
{
private:
  OdPrcAttributeEntry m_AttributeEntry;
  OdUInt8             m_type;
  union
  {
    OdInt32   int32_data;
    double    double_data;
    OdUInt32  uint32_data;
    OdString *pStr_data;
  } m_data;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcContentSingleAttribute)
  //DOM-IGNORE-END
  
  /** \details
  Returns the current attribute title.
  The title is returned as a reference to an OdPrcAttributeEntry object, therefore it can be used to set a new title.
  */
  OdPrcAttributeEntry &attributeEntry();
  
  /** \details
  Returns the current attribute title.
  */
  const OdPrcAttributeEntry &attributeEntry() const;

  /** \details
  The copy constructor. 
  
  \param source [in] An original OdPrcContentSingleAttribute object to be copied.
  */
  OdPrcContentSingleAttribute(const OdPrcContentSingleAttribute &source);
  
  /** \details
  Destroys the attribute and its data.
  */
  ~OdPrcContentSingleAttribute(void);

  /** \details
  The assignment operator. 

  \param source [in] An OdPrcContentSingleAttribute object to be assigned to the attribute.
  \returns Returns a reference to the attribute object. 
 */
  OdPrcContentSingleAttribute& operator= (const OdPrcContentSingleAttribute &source);

  /** \details
  Sets new 32-bit integer data of the attribute.
 
  \param data [in] New data to be set.
  */
  void setData (OdInt32 data);

  /** \details
  Sets new double data of the attribute.
  
  \param data [in] A double value.
  */
  void setData (double data);

  /** \details
  Sets new date and time data of the attribute.
 
  \param data [in] New data to be set.
  */
  void setData (const OdTimeStamp &data);

  /** \details
  Sets new unsigned 32-bit integer data of the attribute.
 
  \param data [in] New data to be set.
  */
  void setData(OdUInt32 data);

  /** \details
  Sets new string data of the attribute.
 
  \param data [in] New data to be set.
  */
  void setData (const OdString &data);

  /** \details
  Clears data and type of the attribute.
  */
  void empty(void);

  /** \details
  Returns the current attribute data type.
  */
  EPRCModellerAttributeType getType() const;

  /** \details
  Returns the current value of the attribute as a 32-bit integer.
  */
  OdInt32 getDataInt32() const;

  /** \details
  Returns the current value of the attribute as a double.
  */
  double getDataDouble() const;

  /** \details
  Returns the current value of the attribute as an unsigned 32-bit integer.
  */
  OdUInt32 getDataUInt32() const;

  /** \details
  Returns the current value of the attribute as a date and time.
  */
  OdTimeStamp getDataTime() const;

  /** \details
  Returns the current value of the attribute as a string.
  */
  const OdString& getDataStr() const;
};

typedef  OdArray<OdPrcContentSingleAttribute> OdPrcContentSingleAttributeArray;

#endif // _PRCCONTENTSINGLEATTRIBUTE_INCLUDED_

