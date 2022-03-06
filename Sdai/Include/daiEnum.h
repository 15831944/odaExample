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

#ifndef _DAI_ENUM_H_
#define _DAI_ENUM_H_

#include "OdaCommon.h"

#include "OdAnsiString.h"
#include "daiUtils/daiUnset.h"
#include "RxDictionary.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  class EnumerationType;

  class DAI_EXPORT EnumItemTypeProvider
  {
  public:
    const OdDAI::EnumerationType* getSchemaType() const;
    
  protected:
    virtual ~EnumItemTypeProvider();
    void  initSchemaType(const OdRxDictionaryPtr& types, const char* enumName);
    void  uninitSchemaType();
    const OdDAI::EnumerationType* getSchemaTypeByName(const OdRxDictionaryPtr& types, const char* enumName);

  private:
    const OdDAI::EnumerationType* m_enumerationType = nullptr;
  };
}

namespace OdDAI
{

  /** \details 
  A class that implements the EXPRESS ENUMERATION data type within IFC Standard Data Access Interface (SDAI).
  */
  class DAI_EXPORT Enum
  {
  public:

    Enum(const OdDAI::EnumerationType* enumerationType);
    Enum();

  public:

    /** \details
    Retrieves if Enum instance has assigned value.
    \returns Returns true if Enum instance has assigned value; otherwise returns false.
    */
    bool exists() const;

    /** \details
    Makes Enum instance unset.
    */
    void nullify();

    /** \details
    Retrieves underlying enumeration type definition.
    \returns Returns pointer to underlying EnumerationType object.  
    */
    const OdDAI::EnumerationType* getSchemaType() const;

    /** \details
    Retrieves the index of currently assigned enumeration value.
    \returns Returns an integer index of currently assigned enumeration value.
    */
    int getIntValue() const;

    /** \details
    Assigns value for Enum instance by provided index.
    \returns Returns true if provided index can be assigned to Enum instance and was successfully assigned, otherwise returns false.
    */
    bool setIntValue(int newValue);

    /** \details
    Retrieves current enumeration value as string.
    \returns Returns pointer to string that represents currently assigned enumeration value.
    */
    const char* getTextValue() const;

    /** \details
    Assigns value for Enum instance by provided string.
    \returns Returns true if provided string can be assigned to Enum instance and was successfully assigned, otherwise returns false.
    */
    bool setTextValue(const char * newValue);

    /** \details
    In case insensitive way assigns value for Enum instance by provided string.
    \returns Returns true if provided string can be assigned to Enum instance and was successfully assigned, otherwise returns false.
    */
    bool setTextValueCaseInsensitive(const char * newValue);

    bool operator== (const Enum& other) const;
    bool operator< (const Enum& other) const;
    bool operator!=(const Enum& other) const;

  private:
    const OdDAI::EnumerationType* m_enumerationType;
    int m_value;
  };

}

namespace OdDAI { namespace Utils { template <> inline const OdDAI::Enum& getUnset<OdDAI::Enum>() { static OdDAI::Enum enumUnset; return enumUnset; } } }
namespace OdDAI { namespace Utils { inline bool isUnset(const  OdDAI::Enum& value) { return !value.exists(); } } }

#endif


