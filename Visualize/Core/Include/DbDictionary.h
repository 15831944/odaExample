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




#ifndef _ODDBDICTIONARY_INCLUDED_
#define _ODDBDICTIONARY_INCLUDED_

#include "TD_PackPush.h"

#include "RxIterator.h"
#include "RxDefs.h"
#include "DbObject.h"
#include "DwgDeclareMembers.h"

class OdTvDbDictionaryImpl;
class OdTvDbObjectId;
class OdString;

/** \details
    This class implements Iterator objects that traverse entries in OdTvDbDictionary objects in an OdTvDbDatabase instance.
    
    Corresponding C++ library: TD_Db
    
    \remarks
    An OdTvDbDictionaryIterator maintains a "current position" within the entries
    of the associated dictionary, and can provide access to the key value and object at the
    current position.

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDictionaryIterator : public OdRxIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbDictionaryIterator);

  virtual ~OdTvDbDictionaryIterator() {}

  /** \details
      Returns the name (key) of the dictionary entry currently referenced
      by this Iterator object.
  */
  virtual OdString name() const = 0;

  /** \details
      Opens the dictionary entry currently referenced by this Iterator object.    

      \param mode [in]  Mode in which to open the object.

      \returns
      Returns a SmartPointer to the opened object.
  */
  virtual OdTvDbObjectPtr getObject(
    OdDb::OpenMode openMode = OdDb::kForRead) = 0;

  /** \details
      Returns the Object ID of the dictionary entry currently referenced by
      this Iterator object.
  */
  virtual OdTvDbObjectId objectId() const = 0;

  /** \details
      Sets the current position of this Iterator to the dictionary entry containing the
      specified ObjectId.

      \param objectId [in]  Object ID of item to which the current position will be set.

      \returns
      Returns true if and only if the current position was set to the specified item.
  */
  virtual bool setPosition(
    OdTvDbObjectId objectId) = 0;

  /** \details
      Opens the dictionary entry currently referenced by this Iterator object in OdDb::kForRead mode.

      \returns
      Returns a SmartPointer to the opened object.
  */
  virtual OdRxObjectPtr object() const;

protected:
  
  OdTvDbDictionaryIterator() {}
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbDictionaryIterator object pointers..
*/
typedef OdSmartPtr<OdTvDbDictionaryIterator> OdTvDbDictionaryIteratorPtr;

/** \details
    This class implements database -resident object dictionaries.
    
    \remarks
    
    * Each instance of OdTvDbDictionary is a single container object, in which
       entries are searched, added, modified, and deleted.  
    * Each OdTvDbDictionary entry associates a unique name (key) string with a unique OdTvDbObject.
    * Anonymous names are signified by specifying a name starting with an asterisk; e.g., *U. 
       A unique name (also starting with an asterisk) will be constructed for the entry.
    * Entry names honor the rules of Symbol names:
      * Names may be any length.
      * Names are case-insensitve.
      * Names may not contain any of the following characters: | * \ : ; < > ? " , equals.

    \sa
    OdTvDbDictionaryIterator
    
    Corresponding C++ library: TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDictionary : public OdTvDbObject
{
  DWGMAP_DECLARE_MEMBERS(OdTvDbDictionary);

protected:
  OdTvDbDictionary();

public:
  /** \details
    Returns the OdTvDbObject associated with the specified name (key) in this Dictionary object.

    \param name [in]  Entry name.
    \param mode [in]  Mode in which to open the object.
 
    \remarks
    Opens the associated OdTvDbObject in the specified mode.
    
    Returns a null SmartPointer if the specified entry could not be opened.
  */
  OdTvDbObjectPtr getAt(
    const OdString& name, 
    OdDb::OpenMode mode) const;
  
  /** \details
    Returns the OdTvDbObject associated with the specified name (key) in this Dictionary object.

    \param name [in]  Entry name.
    \param pStatus [out]  Receives eOk if successful, or an appropriate error code if not.

    \remarks
    Opens the associated OdTvDbObject in the specified mode.
    
    Returns a null Object ID if the specified entry could not be opened.
  */
  OdTvDbObjectId getAt(
    const OdString& name, 
    OdResult* pStatus = 0) const;

  /** \details
    Returns the entry name (key) of the specified object in this Dictionary object.

    \param objectId [in]  Object ID.
    
    \remarks
    Returns an empty string if objectId is not in this Dictionary object.
  */
  OdString nameAt(
    const OdTvDbObjectId& objectId) const;

  /** \details
    Returns true if and only if this Dictionary object has an entry with the specified name (key).

    \param name [in]  Entry name.
  */
  bool has(
    const OdString& name) const;
    
  /** \details
    Returns true if and only if this Dictionary object has an entry with the specified Object ID.

    \param objectId [in]  Object ID.
  */
  bool has(
    const OdTvDbObjectId& objectId) const;

  /** \details
    Returns the number of entries in this Dictionary object.
  */
  OdUInt32 numEntries() const;

  /** \details
    Removes the entry with the specified name (key) from this Dictionary object, and returns
    the Object ID of the removed entry.

    \param name [in]  Entry name.
    
    \remarks
    Only the dictionary entry is removed; the associated object remains in the database without an owner. 
    The dictionary is removed as a persistent reactor on the associated object. 
  */
  OdTvDbObjectId remove(
    const OdString& name);
    
  /** \details
    Removes the entry with the specified Object ID from this Dictionary object, and returns
    the Object ID of the removed entry.

    \param name [in]  Entry name.
    \param objectId [in]  Object ID.
    
    \remarks
    Only the dictionary entry is removed; the associated object remains in the database without an owner. 
    The dictionary is removed as a persistent reactor on the associated object. 
  */
  void remove(
    const OdTvDbObjectId& objectId);

  /** \details
    Changes the name (key) of the specified entry in this Dictionary object.

    \param oldName [in]  Name of entry to change.
    \param newName [in]  New name for the entry.

    \returns
    Returns true and only if the entry name was successfully changed.
  */
  bool setName(
    const OdString& oldName, 
    const OdString& newName);

  /** \details
    Sets the value for the specified entry in this Dictionary object.

    \returns
    Returns the Object ID of the newly added entry.
    
    If an entry the specified name exists in the dictionary, it is
    erased, and a new entry created.

    If an entry for this name does not exist in this dictionary, 
    a new entry is created. 

    \param name [in]  Name of entry to be changed.
    \param newValue [in]  Database object to be added.
  */
  OdTvDbObjectId setAt(
    const OdString& name, 
    OdTvDbObject* newValue);

  /** \details
    Returns true if and only if this Dictionary object is the hard owner of its elements.
     
    \remarks
    Hard ownership protects the elements from purge. Soft ownership does not. 
  */
  bool isTreatElementsAsHard() const;

  /** \details
    Sets the hard ownership property for this Dictionary object.

    \param hard [in]  Controls ownership.

    \remarks
    Hard ownership protects the elements from purge. Soft ownership does not. 
  */
  void setTreatElementsAsHard(
    bool doIt);

  /** \details
    Returns a new interator that can be used to traverse the entries in this Dictionary object.

    \param iterType [in]  Type of Iterator.

    \remarks
    The Iterator type can be one of the following:

    <table>
    Name                      Description
    OdRx::kDictCollated       Traverses the entries in the order they were added to the dictionary.
    OdRx::kDictSorted         Traverses the entries in alphabetical order by key value.
    </table>
  */
  OdTvDbDictionaryIteratorPtr newIterator(
    OdRx::DictIterType iterType = OdRx::kDictCollated) const;

  enum 
  { 
    kMaxSuggestNameSize = 2049 
  };
  /** \details
    Returns a string suitable to be used as dictionary Key for this dictionary object.
    The string is unique for this dictionary object and is as close to file name as possible.

    \param strFilePath [in]  File path.
    \param nMaxLength [in]  Maximum length of name generated.
  */
  OdString suggestName(const OdString& strFilePath, const int nMaxLength = kMaxSuggestNameSize) const;

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  /** \details
      Returns the merge style for this dictionary object.
  */
  virtual OdDb::DuplicateRecordCloning mergeStyle() const;

  /** \details
      Sets the merge style for this dictionary object.
      
      \param mergeStyle [in]  Merge style.
  */
  virtual void setMergeStyle(
    OdDb::DuplicateRecordCloning mergeStyle);

  virtual void goodbye(
    const OdTvDbObject* pObject);

  virtual void erased(
    const OdTvDbObject* pObject, 
    bool erasing = true);

  /*virtual OdResult subGetClassID(
    void* pClsid) const;*/

  virtual void applyPartialUndo(
    OdTvDbDwgFiler* pFiler,
    OdRxClass* pClass);

  virtual void subClose();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbDictionary object pointers.
*/
typedef OdSmartPtr<OdTvDbDictionary> OdTvDbDictionaryPtr;

#include "TD_PackPop.h"

#endif

