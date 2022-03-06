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

#ifndef _PRCATTRIBUTE_INCLUDED_
#define _PRCATTRIBUTE_INCLUDED_ 
 

#include "PrcAttributeEntry.h"
#include "PrcContentSingleAttribute.h"

/** \details
<group PRC_Datatypes_Classes> 

Structure stores special data for writing to an attribute. Special data can be read only by an external application. 
To determine the application of the read data, a default application ID is used, which is stored in the file structure the attribute belongs to.
The custom application ID can be reset.
*/
struct PRC_TOOLKIT OdPrcAttributeExternal
{
  /** \details
  External attribute data default constructor.
  \param entryName [in] An attribute entry name to create.
  \param data [in] The special data to set.
  */
  OdPrcAttributeExternal ();

  /** \details
  External attribute data default constructor.
  \param entryName [in] An attribute entry name to create.
  \param data [in] The special data to set.
  */
  OdPrcAttributeExternal (const OdString &entryName, OdInt32 data);

  /** \details
  Returns whether the special data stored in the structure is valid.
  \returns
  Returns true if the data is valid or returns false in the other case.
  */
  bool isValid(void) const;

  /** \details 
  Attribute entry name.*/
  OdString  entryName;
  /** \details 
  Attribute special data.*/
  OdInt32       data;  
  /** \details 
  Flag indicating whether application ID for the attributer is the same as the application ID for the parent file structure.*/
  bool          useSameAppIDAsFileStructure;
  /** \details 
  Identifier for part 1.*/
  OdInt32       IDPart1;
  /** \details 
  Identifier for part 2.*/
  OdInt32       IDPart2;
  /** \details 
  Identifier for part 3.*/
  OdInt32       IDPart3;
  /** \details 
  Identifier for part 4.*/
  OdInt32       IDPart4; 
};

/** \details 
<group PRC_Datatypes_Classes> 

Class representing a repository for attribute data: title and variable number of key-value pairs.
*/
class PRC_TOOLKIT OdPrcAttribute
{
private:
  OdPrcContentSingleAttributeArray  m_ContentSingleAttribute;
  OdPrcAttributeEntry               m_AttributeEntry;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcAttribute)
  //DOM-IGNORE-END

  /** \details
    Returns the current array of single attributes.
    The array of single attributes is returned as a reference to an array of OdPrcContentSingleAttribute objects, therefore it can be used to set a new single attribute array.
  */
  OdPrcContentSingleAttributeArray &contentSingleAttribute();

  /** \details
    Returns the current array of single attributes.
  */
  const OdPrcContentSingleAttributeArray &contentSingleAttribute() const;

  /** \details
    Returns the current attribute entry.
    \returns 
    The attribute entry is returned as a reference to an OdPrcAttributeEntry object, therefore it can be used to set a new entry.
  */
  OdPrcAttributeEntry &attributeEntry();

  /** \details
    Returns the current attribute entry.
  */
  const OdPrcAttributeEntry &attributeEntry() const;

  /** \details
    Sets a new value of the reserved attribute.
    \param data [in] A new value for the reserved attribute.
  */  
  void setReservedAttribute(const OdPrcAttributeExternal &data);

  /** \details
    Returns the current type of PRC object.
  */
  OdUInt32 prcType() const;

  /** \details 
  Creates the attribute title and sets its text.
  \param attrTitle [in] A attribute entry that represents the new title to be set.
  */
  void SetTitle (const OdPrcAttributeEntry &attrTitle);

  /** \details 
  Add pair data to the attribute. Pair data contains an attribute title and data. 
  \param attrPair [in] A pair data to be added.
  */
  void AddDataPair (const OdPrcContentSingleAttribute &attrPair);

  /** \details 
  Clears the attribute. 
  \remarks 
  The method flushes the array of data fields stored in the attribute.
  */
  void ClearAttribute (void);
};
  
typedef OdArray<OdPrcAttribute> OdPrcAttributeArray;

#endif // _PRCATTRIBUTE_INCLUDED_

