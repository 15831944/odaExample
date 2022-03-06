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

// OdIfcClassesDictionary.h: interface for the OdIfcClassesDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODA_ODIFCCLASSESDICTIONARY_H_INCLUDED_)
#define ODA_ODIFCCLASSESDICTIONARY_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STL_USING_MAP

#include "OdaSTL.h"
#include "RxObject.h"
#include "IfcBuildOptions.h"

/**\details 
A class that provides functionality for working with class dictionaries.
*/
class IFCCORE_EXPORT OdIfcClassesDictionary : public OdRxObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcClassesDictionary);
  //DOM-IGNORE-END
  
public:
  
  /** \details 
  Retrieves access to an element from the dictionary with the specified position.
  \param id [in] An index value that determines the position in the dictionary.
  \returns Returns a smart pointer to the dictionary element allocated at the specified position.
  \remarks 
  If the specified position is incorrect (for example, when the index value is equal to or greater than the quantity of elements), 
  the method returns a NULL smart pointer (smart pointer object's method isNull() returns true).
  */
  virtual OdRxObjectPtr getAt(OdUInt32 id) const;
  
  /** \details 
  Sets a new element to the dictionary at the specified position.
  \param id       [in] An index value that determines the position in the dictionary.
  \param pObject  [in] A raw pointer to a new element that should be set at the position in the dictionary.
  \returns Returns a smart pointer to the dictionary element allocated at the specified position.
  \remarks 
  If the specified position is incorrect (for example, when the index value is equal to or greater than the quantity of elements), 
  the method returns a NULL smart pointer (smart pointer object's method isNull() returns true).
  */
  virtual OdRxObjectPtr putAt(OdUInt32 id, OdRxObject* pObject);
  
  /** \details 
  Removes the element at the specified position from the dictionary.
  \param id [in] An index value that determines the position in the dictionary.
  \returns Returns a smart pointer to the dictionary element removed from the specified position.
  \remarks 
  If the specified position is incorrect (for example, when the index value is equal to or greater than the quantity of elements), 
  the method returns a NULL smart pointer (smart pointer object's method isNull() returns true).
  */
  virtual OdRxObjectPtr remove(OdUInt32 id);
  
  /** \details 
  Retrieves whether the dictionary contains an element with the specified position.
  \param id [in] An index value that determines the position in the dictionary.
  \returns Returns true if the dictionary contains an element with the specified position; otherwise, the method returns false.
  */
  virtual bool has(OdUInt32 id) const;
  
  /** \details 
  Retrieves the quantity of dictionary elements.
  \returns Returns the quantity of dictionary elements.
  */
  virtual OdUInt32 numEntries() const;

//DOM-IGNORE-BEGIN
private:
  typedef std::map<OdUInt32, OdRxClassPtr> _clsDict;
  _clsDict m_dict;
//DOM-IGNORE-END
};

#endif // !defined(ODA_ODIFCCLASSESDICTIONARY_H_INCLUDED_)

