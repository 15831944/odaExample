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

#ifndef _PRCATTRIBUTEENTRY_INCLUDED_
#define _PRCATTRIBUTEENTRY_INCLUDED_ 
 

/** \details 
<group PRC_Miscellaneous_Classes> 

Class representing a repository for an attribute title. A title can be represented as a string (user defined title) or as an integer value (predefined title).
*/
class PRC_TOOLKIT OdPrcAttributeEntry
{
private:
  OdUInt32  m_titleInt;
  OdString  m_titleStr;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcAttributeEntry)
  //DOM-IGNORE-END

  /** \details
  Copy constructor of an attribute title.
  \param source [in] An attribute title instance to copy from.
  */
  OdPrcAttributeEntry(const OdPrcAttributeEntry &source);

  /** \details 
    Returns the current value of the predefined title flag. 
    Predefined title flag is equal to true if the title is predefined and represented as an integer value. If the title is user defined and represented as a string value, flag is equal to false. 
  */ 
  bool titleIsInteger() const;
  
  /** \details
    Sets a new value of the user defined attribute title.

    \param title [in] A new title value to be set.
  */
  void setData (const OdString &title);

  /** \details
    Sets a new value of the predefined attribute title.

    \param titleIdx [in] A new title value to be set.
  */
  void setData (EPRCAttributeEntry titleIdx);
  
  /** \details
    Returns the current value of a user defined attribute title.
  */ 
  OdString getTitle() const;
  
  /** \details
    Returns the current value (index) of the predefined attribute title.
    Method returns EPRCAttributeEntryNotSet if the index for predefined attribute title is not used.
  */ 
  EPRCAttributeEntry getIndex() const;

  /** \details
  The assignment operator.

  \param source [in] An EPRCAttributeEntry object to be assigned to the attribute entry.
  \returns Returns a reference to the attribute entry object.
  */
  OdPrcAttributeEntry& operator= (const OdPrcAttributeEntry &source);
};

#endif // _PRCATTRIBUTEENTRY_INCLUDED_

