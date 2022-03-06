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

#ifndef _BFC_UTILS_H
#define _BFC_UTILS_H

#include "BcfCommon.h"
#include "StringArray.h"

#include <cstdint>

#include "BcfUnset.h"

/** \details
Contains declarations related to working with BCF files content.
*/
class TiXmlElement;

namespace OdBcf {

  class OdBcfTimeStamp;
  typedef OdSmartPtr<OdBcfTimeStamp> OdBcfTimeStampPtr;

  class OdBcfElement;

  /** \details
  Contains declarations related to utilities related to working with BCF files content.
  */
  namespace Utils
  {

    /** \details
    Checks if the specified string is equal to the &quot;true&quot; or &quot;1&quot;.
    \param value [in] A string probably containing a boolean value.
    \returns true if the string is equal to one of the values mentioned above; otherwise, the method returns false.
    */
    bool parseBool(const OdString &value);

    /** \details
    Converts a boolean value to a string.
    \param value [in] A boolean value to be converted.
    \returns The string &quot;true&quot; if the specified boolean equals true; otherwise, the method returns the string &quot;false&quot;.
    */
    const OdString& boolToString(bool value);

    /** \details
    Formats a specified path to a file according to the curren`t platform.
    \param dir [in] A string containing the path to the file.
    \returns A string containing the formatted path.
    \remarks
    The function ensures that there is a separator on the end of the path.
    */
    BCF_EXPORT OdString formatDir(const OdString &dir);

    /** \details
    Creates an empty directory.
    \param dir [in] A string that contains the path to the new directory.
    \returns 0 if the directory was successfully created; otherwise, the method returns an appropriate error code.
    */
    BCF_EXPORT int createDir(const OdString &dir);

    /** \details
    Retrieves the local time and the system time zone.
    \returns A smart pointer to the created <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains information about local time and time zone.
    */
    OdBcfTimeStampPtr getCurrentTime();

    /** \details
    Adds a new text child to a specified XML structure.
    \param pParent [in] A raw pointer to the parent of the new element.
    \param name    [in] A string that contains the name of the new element.
    \param value   [in] A string that contains the value of the new element.
    \returns eOk if the element was successfully created; otherwise, the method returns an appropriate error code.
    */
    OdResult createTextChild(TiXmlElement *pParent, const char *name, const char *value);

#define CREATE_TEXT_CHILD(pParent, Name, Value)                                        \
                                                                                       \
if(OdResult pParent##Res = OdBcf::Utils::createTextChild(pParent, Name, Value))        \
{                                                                                      \
  return pParent##Res;                                                                 \
}

    /** \details
    Adds a newly constructed child to a specified XML structure.
    \param pParent [in] A raw pointer to the parent of the new element.
    \param name    [in] A string that contains the name of the new element.
    \param pValue  [in] A raw pointer to an <link OdBcf::OdBcfElement, object> that is responsible for creating of the new element value.
    \returns eOk if the element was successfully created; otherwise, the method returns an appropriate error code.
    */
    OdResult createConstructedChild(TiXmlElement *pParent, const char *name, const OdBcfElement *pValue);

#define CREATE_CONSTRUCTED_CHILD(pParent, Name, Value)                                 \
                                                                                       \
if(OdResult pParent##Res = OdBcf::Utils::createConstructedChild(pParent, Name, Value)) \
{                                                                                      \
  return pParent##Res;                                                                 \
}

#define VALIDATE_SIMPLE_FIELD(Field)                                                   \
                                                                                       \
if(OdBcf::Utils::isUnset(Field))                                                       \
{                                                                                      \
  return false;                                                                        \
}

#define VALIDATE_UNREQUIRED_CONSTRUCTED_FIELD(Field)                                   \
                                                                                       \
if(!OdBcf::Utils::isUnset(Field))                                                      \
{                                                                                      \
  if(Field->validate() == false)                                                       \
  {                                                                                    \
    return false;                                                                      \
  }                                                                                    \
}

#define VALIDATE_REQUIRED_CONSTRUCTED_FIELD(Field)                                     \
                                                                                       \
if(!OdBcf::Utils::isUnset(Field))                                                      \
{                                                                                      \
  if(Field->validate() == false)                                                       \
  {                                                                                    \
    return false;                                                                      \
  }                                                                                    \
}                                                                                      \
else                                                                                   \
{                                                                                      \
  return false;                                                                        \
}

#define VALIDATE_UNREQUIRED_CONSTRUCTED_COLLECTION(Collection)                         \
                                                                                       \
for(const auto& element : Collection)                                                  \
{                                                                                      \
  VALIDATE_UNREQUIRED_CONSTRUCTED_FIELD(element);                                      \
}

#define VALIDATE_REQUIRED_CONSTRUCTED_COLLECTION(Collection)                           \
                                                                                       \
VALIDATE_UNREQUIRED_CONSTRUCTED_COLLECTION(Collection);                                \
if(Collection.size() == 0)                                                             \
{                                                                                      \
  return false;                                                                        \
}

  } //namespace Utils

} //namespace OdBcf

#endif // _BFC_UTILS_H
