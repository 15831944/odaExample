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

#ifndef _DAI_SELECT_H_
#define _DAI_SELECT_H_

#include "daiPrimitive.h"
#include "daiObjectId.h"
#include "daiTCKind.h"
#include "RxDictionary.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class OdSpfFilerBase;
  class NamedType;
  class Aggr;
  class AttributeDataBlock;
  class SelectType;
  class Enum;


  class DAI_EXPORT SelectTypeProvider
  {
  public:
    const OdDAI::SelectType* getSchemaType() const;

  protected:
    virtual ~SelectTypeProvider();
    void  initSchemaType(const OdRxDictionaryPtr& types, const char* enumName);
    void  uninitSchemaType();
    const OdDAI::SelectType* getSchemaTypeByName(const OdRxDictionaryPtr& types, const char* enumName);

  private:
    const OdDAI::SelectType* m_selectType = nullptr;
  };
}

namespace OdDAI {

  /** \details
  Base class that implements the base functionality for working with the EXPRESS SCHEMA of the &quot;Select&quot; data type.
  */
  class DAI_EXPORT Select
  {
  public:

 
    /** \details
    Creates a new &quot;Select&quot; value as a copy of an existing one (copy constructor).
    \param other [in] Another value to be copied.
    */
    Select(const Select &other);

    /** \details
    Creates a new &quot;Select&quot; value.
    */
    Select(const OdDAI::SelectType* selectType = nullptr);

    /**
    Destroys the &quot;Select&quot; value.
    */
    ~Select();

    /** \details
    The assignment operator for the &quot;Select&quot; value.
    \param other [in] Another value (right-hand operand of the assignment operation).
    \returns Returns a reference to the &quot;Select&quot; value after the assignment operation is done.
    \remarks 
    The operator makes a deep copy of underlying data of the right-hand operand and assigns it to this &quot;Select&quot; value. 
    */
    Select& operator = (const Select &other);

    /** \details
    The equality operator for the &quot;Select&quot; value.
    \param other [in] other value (right-hand operand of the equality operator).
    \returns Returns true if other equals to this, or false in other case.
    */
    bool operator== (const Select& other) const;
    
    /** \details
    The inequality operator for the &quot;Select&quot; value.
    \param other [in] other value (right-hand operand of the inequality operator).
    \returns Returns true if other not equals to this, or false in other case.
    */
    bool operator!= (const Select& other) const;

    /** \details
    The less operator for the &quot;Select&quot; value.
    \param other [in] other value (right-hand operand of the less operator).
    \returns Returns true if other greater than this, or false in other case.
    */
    bool operator < (const Select& other) const;

    /** \details
    Determines whether receiver of the value is set into the &quot;Select&quot; instance.
    \returns Returns 1 if the receiver for the value has been set.
    */
    int exists() const;


    /** \details
    Destructs the underlying object, unsets the determinant, and sets the value type to <link OdTCKind::tkNull, tkNull>.
    */
    void nullify();

    /** \details
    Retrieves the type of the underlying object.
    \returns Returns the type of the &quot;Select&quot; type's underlying value.
    */
    OdTCKind kind() const;

    void _d(long determinant) ;

    long _d() const;


    /** \details
    Retrieves the name of the current underlying type.
    \returns Returns an ANSI string that contains the name of the underlying type.
    */
    const OdAnsiString& underlyingTypeName() const;

    /** \details
    Sets a new name of the underlying type. 
    \param typeName [in] An ANSI string that contains the new name.
    \returns Returns false if the new type name is incorrect for the &quot;Select&quot; data type.
    */
    bool underlyingTypeName(OdAnsiString typeName);


    /** \details
    Sets a new name underlying type.
    \param newType [in] contains the new type.
    \returns Returns false if the new type is incorrect for the &quot;Select&quot; data type.
    */
    bool setUnderlyingType(const NamedType* newType);

    /** \details
    Retrieves the current underlying class description.
    \returns Returns a pointer that contains the description of the underlying class.
    */
    const NamedType* type() const;


    /** \details
    Sets a new value throw a AttributeDataBlock.
    \param val [in] A block with new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setADB(const OdDAI::AttributeDataBlock& dataBlock);

    /** \details 
    Sets a new value represented as an object identifier.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setHandle(OdDAIObjectId val);
    
    /** \details 
    Sets a new value represented with an unsigned 32-bit integer.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setInt32(int val);
    
    /** \details 
    Sets a new value represented with a boolean value.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setBool(bool val);

    /** \details
    Sets a new value represented with a OdDAI::Boolean value.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setBoolean(const Boolean &val);
    
    /** \details 
    Sets a new value represented with a double value.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setDouble(double val);
    
    /** \details 
    Sets a new value represented with an ANSI string.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setString(const OdAnsiString &val);
    
    /** \details 
    Sets a new value represented with a binary value.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setBINARY(BINARY &val);
    
    /** \details 
    Sets a new value represented with a logical value.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setLogical(const Logical &val);
    
    /** \details 
    Sets a new value represented with an array of unsigned 32-bit integers.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setInt32Array(const OdArray<int> &val);
    
    /** \details 
    Sets a new value represented with an array of object identifiers.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setHandleArray(const OdArray<OdDAIObjectId> &val);
    
    /** \details 
    Sets a new value represented with an array of double values.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setDoubleArray(const OdArray<double> &val);

    /** \details
    Sets a new value represented with a unsigned long value into underlying enumeration instance.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    \remarks
    This method can be used together with early-bound enumeration values, but is not recommended in
    late-bound way of working as same numerical index values of enumeration types may have different
    meanings in different EXPRESS schemas.
    */
    bool setEnum(unsigned long val);

    /** \details
    Sets a new value represented by OdAnsiString value into underlying enumeration instance.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setEnum(const OdAnsiString &val);

    /** \details
    Sets a new value represented by OdDAI::EnumValueInfo into underlying enumeration instance.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setEnum(const OdDAI::EnumValueInfo &val);

    /** \details
    Sets a new value represented by OdDAI::Enum* into underlying enumeration instance.
    \param val [in] A new value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    \remarks
    Enumeration types of val enumeration instance and select's underlying enumeration instance
    must be the same in the scope of same EXPRESS schema.
    */
    bool setEnum(const OdDAI::Enum *val);

    /** \details
    Sets a new value represented with an aggregation.
    \param val [in] A new nested value.
    \returns Returns true if the value was successfully set; otherwise, the method returns false.
    */
    bool setAggr(Aggr *val);

    /** \details
    Retrieves the current value as a ADB.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully put to ADB and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getADB(OdDAI::AttributeDataBlock& dataBlock) const;


    /** \details
    Retrieves the current value as an unsigned 32-bit integer value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getInt32(int &ret) const;
    
    /** \details 
    Retrieves the current value as a double value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getDouble(double &ret) const;
    
    /** \details 
    Retrieves the current value as a boolean value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getBool(bool &ret) const;

    /** \details
    Retrieves the current value as a boolean value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getBoolean(Boolean &ret) const;
    
    /** \details 
    Retrieves the current value as an ANSI string.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getString(OdAnsiString &ret) const;

    /** \details
    Retrieves the current value as constant pointer to null-terminated string.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getString(const char* &ret) const;
    
    /** \details 
    Retrieves the current value as an object identifier.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getHandle(OdDAIObjectId &res) const;
    
    /** \details 
    Retrieves the current value as an object identifier.
    \returns Returns the current value converted into an object identifier.
    */
    OdDAIObjectId getHandle() const;

	  /** \details
	  Retrieves the current handle of object identifier.
	  \returns Returns the current value converted into OdDbHandle.
    \remarks 
    The handle returned by the method is read-only.
	  */
	  const OdDbHandle& getHandleId() const;
    
    /** \details 
    Retrieves the current value as a logical value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */    
    bool getLogical(Logical &ret) const;
    
    /** \details 
    Retrieves the current value as a binary value.
    \param res [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getBINARY(OdAnsiString &res) const;
    
    /** \details 
    Retrieves the current value as an array of unsigned 32-bit integer values.
    \param res [out] A placeholder for the array to be filled and returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getInt32Array(OdArray<int> &res) const;
    
    /** \details 
    Retrieves the current value as an array of object identifiers.
    \param res [out] A placeholder for the array to be filled and returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getHandleArray(OdArray<OdDAIObjectId> &res) const;
    
    /** \details 
    Retrieves the current value as an array of double values.
    \param res [out] A placeholder for the array to be filled and returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getDoubleArray(OdArray<double> &res) const;
    
    /** \details 
    Retrieves the current value as a binary value.
    \param res [out] A placeholder for the raw pointer that refers to the binary data. This pointer is returned to a calling subroutine.
    \returns Returns true if the value is successfully converted and the raw pointer is returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getBINARY(char* &res) const;

    /** \details
    Retrieves the current value as pointer to underlying enumeration instance.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getEnum(OdDAI::Enum* &ret) const;

    /** \details
    Retrieves the current value as pointer to constant char that holds underlying enumeration string value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getEnum(const char* &ret) const;

    /** \details
    Retrieves the current value into OdDAI::EnumValueInfo that holds underlying enumeration string value.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getEnum(OdDAI::EnumValueInfo &ret) const;

    /** \details
    Retrieves the current value as a pointer to Aggr.
    \param ret [out] A placeholder for the value to be returned to a calling subroutine.
    \returns Returns true if the value was successfully converted and returned to a calling subroutine; otherwise, the method returns false.
    */
    bool getAggr(Aggr* &ret) const;

    const OdDAI::SelectType* getSchemaType() const;

//DOM-IGNORE-BEGIN
  protected:

    bool setUnderlyingType_internal(const OdDAI::NamedType* newType);

    bool kindPreset(OdTCKind  newKind);

    template<class TValue>
    bool valueSet(OdTCKind  newKind, const TValue& setFrom, TValue& setTo);

    const OdDAI::NamedType* findTypeByKind(OdTCKind testKind);

    /** \details
    Destructs the underlying object.
    */
    void reset();

    /** \details
      Sets the specific underlying type enum for the stored handle.
    */
    bool setHandleD(const OdDAIObjectId& val);

    /** \details
      Sets handle during document loading.
    */
    void setHandleOnLoad(const OdDAIObjectId& val);

    /** \details
      Reload handle after document loading.
    */
    void refreshSelectHandle();

    /** \details
      Unsets the discriminant of the derived type.
    */
    void unset();

    /** \details
      Reads typed value from the file which is assigned to the rdFiler.
    */
    OdResult readTypedField(const OdAnsiString &typeDef, OdSpfFilerBase *rdFiler);

    /** \details
      Writes typed value into the file which is assigned to the wrFiler.
    */
    OdResult writeTypedField(OdSpfFilerBase *wrFiler) const;

  
  protected:
    const OdDAI::SelectType* m_selectType; // This is for checking available types/type paths
    const OdDAI::NamedType* m_underlyingType;

    union {
      OdUInt64            m_hndl;
      int                 m_int;
      bool                m_bool;
      double              m_dbl;
      void*               m_ptr;
      unsigned long       m_ulong;
    };

    friend class OdSpfFilerBase;
//DOM-IGNORE-END

  };

}

namespace OdDAI { namespace Utils { template <> inline const OdDAI::Select& getUnset<OdDAI::Select>() { static OdDAI::Select selectUnset; return selectUnset; } } }
namespace OdDAI { namespace Utils { inline bool isUnset(const  OdDAI::Select& value) { return value.exists() == 0; } } }


#endif // _DAI_SELECT_H_
