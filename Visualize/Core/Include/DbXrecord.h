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




#ifndef ODDB_XRECORD_H
#define ODDB_XRECORD_H /*!DOM*/

#include "TD_PackPush.h"

//#define ODDB_XRECORD_CLASS          "OdTvDbXrecord"

#include "DbObject.h"
#include "DbFiler.h"
#include "DwgDeclareMembers.h"

class OdTvDbXrecordIteratorImpl;

/** \details
    This class implements Iterators for the data lists in OdTvDbXrecord instances.  

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbXrecordIterator : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbXrecordIterator);

  /** \details
    Sets this Iterator object to reference the first ResBuf structure in the XRecord data list.
     
    \remarks
    Allows multiple traversals of the data list.
  */
    void start();

  /** \details
    Returns true if and only if the traversal is complete.
  */
    bool done() const;
 
  /** \details
    Sets this Iterator object to reference the next ResBuf structure in the XRecord data list.

    \returns
    Returns true if and only if not at the end of the list.
  */
   bool next();
  
  /** \details
    Returns the restype field of the current ResBuf structure in the XRecord data list.
  */
  int curRestype() const;
  
  /** \details
    Returns a copy of the current ResBuf structure in the XRecord data list.
    \param pDb [in]  Pointer to the OdTvDbDatabase used for Object ID resolution when this XRecord object is not database resident.
  */
  OdTvResBufPtr getCurResbuf(OdTvDbDatabase* pDb = 0) const;
protected:
  OdTvDbXrecordIterator(
    OdTvDbXrecordIteratorImpl* pIterImpl);
  OdTvDbXrecordIteratorImpl* m_pImpl;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbXrecordIterator object pointers.
*/
typedef OdSmartPtr<OdTvDbXrecordIterator> OdTvDbXrecordIteratorPtr;


/** \details
    This class implements XRecord objects in an OdTvDbDatabase, container objects
    used attach arbitrary data to other OdDb objects.

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbXrecord : public OdTvDbObject
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbXrecord);

  OdTvDbXrecord();

  /** \details
    Returns a copy of the ResBuf list owned by the XRecord object.

    \param pDb [in]  Pointer to the OdTvDbDatabase used for Object ID resolution when this XRecord object is not database resident.
    \param pStatus [in]  Pointer an OdResult to receive the status. 
    
    \remarks
    If pStatus != NULL, returns eOk if successful, or an appropriate error code if not.
  */
  OdTvResBufPtr rbChain(
    OdTvDbDatabase* pDb = 0, 
    OdResult* pStatus = 0) const;

  /** \details
    Returns an Iterator object that can be used to traverse this XRecord object.


    \remarks
    This method can be faster than using rbChain()

    \param pDb [in]  Pointer to the OdTvDbDatabase used for Object ID resolution when this XRecord object is not database resident.
  */
  OdTvDbXrecordIteratorPtr newIterator(
    OdTvDbDatabase* pDb = 0) const;

  /** \details
    Sets the data in this XRecord object to the data in the specified ResBuf chain. 
    \param pDb [in]  Pointer to the OdTvDbDatabase used for Object ID resolution when this XRecord object is not database resident.
    \param pRb [in]  Pointer to the first ResBuf in the ResBuf chain.
  */
  OdResult setFromRbChain(const OdTvResBuf* pRb, OdTvDbDatabase* pDb = 0);
  
  /** \details
    Appends the data in the specified ResBuf chain to the data in this XRecord.

    \param pRb [in]  Pointer to the first ResBuf in the ResBuf chain.
    \param pDb [in]  Pointer to the OdTvDbDatabase used for Object ID resolution when this XRecord object is not database resident.
  */
  OdResult appendRbChain(
    const OdTvResBuf* pRb, 
    OdTvDbDatabase* pDb = 0);

  /** \details
    Returns true if and only if this XRecord object is set to translate 
    data chain Object IDs during subDeepClone() and subWblockClone() operations.
  */
  bool isXlateReferences() const;

  /** \details
    Controls if this XRecord object is to translate 
    data chain Object IDs during subDeepClone() and subWblockClone() operations.

    \param xlateReferences [in]  Translate references, if and only if true. 
  */
  void setXlateReferences(
    bool isXlateReferences);
  
  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;
  
  /** \details
      Returns the merge style for this XRecord object (DXF 280).
  */
  virtual OdDb::DuplicateRecordCloning mergeStyle() const;

   /** \details
      Sets the merge style for this XRecord object (DXF 280).
      
      \param mergeStyle [in]  Merge style.
   */
  virtual void setMergeStyle(
    OdDb::DuplicateRecordCloning mergeStyle);
  
 /* virtual OdResult subGetClassID(
    void* pClsid) const;*/

  enum
  {
    kOpenExisting     = 0,
    kCreateIfNotFound = 1
  };

  /** \details
    Opens for writing the specified XRecord object of the specified OdTvDbObject. 
    
    \param creationFlag [in]  Creation flag. 
    \param pObject [in]  Pointer to the Object.
    \param key [in]  XRecord key.
    \param mergeStyle [in]  Merge style.
    
    \returns
    Returns a SmartPointer to the opened XRecord, or NULL if the specified XRecord object
    does not exist and creationFlag == kOpenExisting. 
    \remarks
    creationFlag must be one of the following:
    
    <table>
    Name                  Value
    kOpenExisting         0
    kCreateIfNotFound     1
    </table>
    
  */
  static OdTvDbXrecordPtr open(OdTvDbObject* pObject, const OdString &key,
    int creationFlag = kOpenExisting,
    OdDb::DuplicateRecordCloning mergeStyle = OdDb::kDrcIgnore);

  /** \details
    Opens for writing the specified XRecord object of the specified OdTvDbObject. 
    
    \param creationFlag [in]  Creation flag. 
    \param pObject [in]  Pointer to the Object.
    \param keys [in]  Array of XRecord keys defining the path to the XRecord.
    \param mergeStyle [in]  Merge style.
    
    \returns
    Returns a SmartPointer to the opened XRecord, or NULL if the specified XRecord object
    does not exist and creationFlag == kOpenExisting. 
    \remarks
    creationFlag must be one of the following:
    
    <table>
    Name                  Value
    kOpenExisting         0
    kCreateIfNotFound     1
    </table>
    
  */
  static OdTvDbXrecordPtr open(OdTvDbObject* pObject, const OdArray<OdString> &keys,
    int creationFlag = kOpenExisting,
    OdDb::DuplicateRecordCloning mergeStyle = OdDb::kDrcIgnore);
};

#include "TD_PackPop.h"

#endif //ODDB_XRECORD_H

