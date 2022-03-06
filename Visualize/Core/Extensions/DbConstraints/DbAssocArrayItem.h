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

#ifndef DbAssocArrayItem_INCLUDED_
#define DbAssocArrayItem_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAssocGlobal.h" 
#include "RxObjectImpl.h"

#include "TD_PackPush.h"

/** \details
  This class represents the item locator for an array of associated parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbItemLocator
{
public:
  /** \details
    Declares the index type.
  */
  enum IndexType 
  { 
      kItemIndex
    , kRowIndex
    , kLevelIndex
  };
  
  /** \details
    Constructors create an instance of this class.
  */
  OdTvDbItemLocator();
  
  OdTvDbItemLocator(int itemIndex, int rowIndex, int levelIndex);
  
  OdTvDbItemLocator(const OdTvDbItemLocator& other);

  /** \details
    Returns an item for a given index.
  */
  int operator [](IndexType i) const;
  
  /** \details
    Assigns a given locator for this locator.
  */
  OdTvDbItemLocator& operator =(const OdTvDbItemLocator& other);
  
  /** \details
    Substracts a given locator from this locator.
  */
  OdTvDbItemLocator  operator -(const OdTvDbItemLocator& other) const;
  
  /** \details
    Adds a given locator to this locator.
  */
  OdTvDbItemLocator  operator +(const OdTvDbItemLocator& other) const;
  
  /** \details
    Checks whether this locator equals to a given locator.
  */
  bool operator ==(const OdTvDbItemLocator& other) const;
  
  /** \details
    Checks whether this locator unequals to a given locator.
  */
  bool operator !=(const OdTvDbItemLocator& other) const;
  
  /** \details
    Checks whether this locator less than a given locator.
  */
  bool operator <(const OdTvDbItemLocator& other) const;

  /** \details
    Checks whether this locator more than a given locator.
  */
  bool operator >(const OdTvDbItemLocator& other) const;

  /** \details
    Compares two locators.
  */
  int compareWith(const OdTvDbItemLocator& other) const;

private:
  /*!DOM*/
  int m_Indices[3];
};

/** \details
  This class represents an item of the array of associated parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocArrayItem : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocArrayItem);

  /** \details
    Constructors create an instance of this class.
  */
  OdTvDbAssocArrayItem();
  OdTvDbAssocArrayItem(OdTvDbItemLocator& locator, const OdGeMatrix3d& transform);
  static OdSmartPtr<OdTvDbAssocArrayItem> createObject(OdTvDbItemLocator& locator, const OdGeMatrix3d& transform);
  static OdSmartPtr<OdTvDbAssocArrayItem> createObject(const OdTvDbAssocArrayItem *pItem, OdTvDbObjectId modifyBodyId);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocArrayItem();

  /** \details
    Gets the transformation matrix.
  */
  OdResult getTransform(OdGeMatrix3d& transform, bool bCompounded = true) const;
  
  /** \details
    Checks whether the transformation is relative.
  */
  bool hasRelativeTransform() const;

  /** \details
    Transforms the item.
  */
  OdResult transformBy(const OdGeMatrix3d& transform);

  /** \details
    Sets the default transformation matrix.
  */
  OdResult setDefaultTransform(const OdGeMatrix3d& transform);

  /** \details
    Sets the erase status.
  */
  OdResult setErased(bool bErased);

  /** \details
    Checks the erase status.
  */
  bool isErased() const;

  /** \details
    Returns the item locator.
  */
  const OdTvDbItemLocator& locator() const;

  /** \details
    Returns an object ID of the entity provider.
  */
  const OdTvDbObjectId& entityProvider() const;

  /** \details
    Sets the entity provider using a given object ID.
  */
  void setEntityProvider(OdTvDbObjectId provider);

  /** \details
    Copies the content of a given object to one.
  */
  virtual void copyFrom(const OdRxObject* other);

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

private:
  /*!DOM*/
  OdTvDbAssocArrayItem(const OdTvDbAssocArrayItem& other); // disabled Copy constructor

protected:
  friend class OdTvDbImpAssocArrayItem;
  class OdTvDbImpAssocArrayItem* m_pImpl;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocArrayItem class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocArrayItem> OdTvDbAssocArrayItemPtr;

#include "TD_PackPop.h"

#endif
