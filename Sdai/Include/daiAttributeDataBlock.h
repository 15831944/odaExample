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

#ifndef _SDAI_ATTTRIBUTE_DATA_BLOCK_VALUE_H
#define _SDAI_ATTTRIBUTE_DATA_BLOCK_VALUE_H

#include "OdaCommon.h"
#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

#include "OdArray.h"
#include "daiPrimitive.h"
#include "daiADB_Value.h"

#include "sdai.h"

#define STL_USING_VECTOR
#define STL_USING_STRING
#include "OdaSTL.h"


/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  A class that holdes path of the select data.
  */
  class DAI_EXPORT SafePathHolder
  { 
  public:

    /** \details
    Creates a new empty path holder.
    */
    SafePathHolder();

    /** \details
    Constructor copy. Creates a new empty path holder and init data from rightValue.
    \param rightValue [in] path holder to copy from.
    */
    SafePathHolder(const SafePathHolder& rightValue);

    /** \details
    Destroys path holder.
    */
    ~SafePathHolder();

    /** \details
      Compare two path holders.
      \param rightValue [in] path holder to compare.
      \returns true if equal, and false otherwise.
    */
    bool operator== (const SafePathHolder& rightValue) const;

    /** \details
      Copy one path holder to another.
      \param rightValue [in] path holder to copy from.
      \returns the reference to itself.
    */
    SafePathHolder& operator=(const SafePathHolder& rightValue);

    /** \details
      Provides a path array.
      \param typeNameNumber [out] count items at provided array.
      \returns the row pointer to the array, can return nullptr if the path is empty.
    */
    const SdaiString* getPath(SdaiInteger& typeNameNumber) const;

    /** \details
      Sets a path array.
      \param typeNameNumber [in] count of array items.
      \param typeNameVector [in] array of pathes.
    */
    void putPath(SdaiInteger typeNameNumber, SdaiString* typeNameVector);

    /** \details
      Sets a path array. 
      \param typeNameNumber [in] original type path, should looks like:"type1/type2/type3".
    */
    void putPath(const std::string& typeNameVector);


    /** \details
      Append additional value to array of type pathes.
      \param addeValue [in] original type path, should looks like:"type1/type2/type3".
    */
    void add(const SdaiString addeValue);

    /** \details
      Remove all data, clear all buffers. 
    */
    void clearAll();

    /** \details
      Reserve buffer by size
      \param addeValue [in] size of buffer.
    */
    void reserve(const size_t& count);

    //DOM-IGNORE-BEGIN
  private:
    // need for SdaiString row array providing
    std::vector<SdaiString> m_pathes;
    //DOM-IGNORE-END
  };
}

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  Class of attribute data block should used for simple select data moving/coping/editing.
  */
  class DAI_EXPORT AttributeDataBlock
  {
  public:
    /** \details
    Creates a new empty instance of attribute data block.
    */
    AttributeDataBlock();

    /** \details
    Constructor copy. Creates a new empty instance of attribute data block and init data from the right value.
    \param rightValue [in] Attribute Data Block to copy from.
    */
    AttributeDataBlock(const AttributeDataBlock& rightValue);
    
    /** \details
      Compare two attribute data block.
      \param rightValue [in] other attribute data block to compare.
      \returns true if equal, and false otherwise.
    */
    bool operator== (const AttributeDataBlock& rightValue) const;

    /** \details
      Copy one attribute data block to another.
      \param rightValue [in] attribute data block to copy from.
      \returns the reference to itself.
    */
    AttributeDataBlock& operator=(const AttributeDataBlock& rightValue);

    /** \details
      Translate internal data to string.
      \returns the internal data represented as a string.
    */
    OdString toString() const;

    /** \details
      Clear all data.
    */
    void unset();


    /** \details
      Gets value type path. If the attribute data block contains OdDAIObjectId, 
      the function returns the type name of this application instance.
      \param getFrom [in] attribute data block to get type path from.
      \returns the specified type path.
    */
    static SdaiString getValueSpecifiedTypePath(const AttributeDataBlock& getFrom);

    //DOM-IGNORE-BEGIN
  public:
    ADB_Value       value;
    SafePathHolder  typePath;
    //DOM-IGNORE-END
  };


}

#endif
