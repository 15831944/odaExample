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
// External renderer arrays manager.

#ifndef ODTRRNDEXTERNALARRAYSMANAGER
#define ODTRRNDEXTERNALARRAYSMANAGER

#include "TD_PackPush.h"

#include "../TrVisMetafileStream.h"

/** \details
    <group ExRender_Windows_Classes> 
*/
class OdTrRndExternalArraysManager
{
  public:
    struct ExamArrayEntry
    {
      const void *m_pData;
      OdUInt32 m_uSizeElems;
    };
  public:
    // Check does arrays manager supports extending without recreation.
    virtual bool examSupportExtending() const { return true; }
    // Initialize (create) array.
    virtual void examInitializeArray(OdTrVisArrayWrapper &wrapArray, const ExamArrayEntry *pElem, OdUInt32 nElems, OdTrVisArrayWrapper::DataSize dataTypeSize) const = 0;
    // Extend exist array.
    virtual void examExtendArray(OdTrVisArrayWrapper &wrapArray, const ExamArrayEntry *pElem, OdUInt32 nElems) const = 0;
    // Truncate exist array.
    virtual void examTruncateArray(OdTrVisArrayWrapper &wrapArray, OdUInt32 uSizeElems) const = 0;
    // Recreate array (will be called instead of Extend/Truncate in case if SupportExtending false).
    virtual void examRecreateArray(OdTrVisArrayWrapper &wrapArray, const ExamArrayEntry *pElem, OdUInt32 nElems) const = 0;
    // Delete (free) exist array.
    virtual void examFreeArray(OdTrVisArrayWrapper &wrapArray) const = 0;
    // Returns true in case if array data can be accessed.
    virtual bool examSupportAccess() const { return true; }
    // Returns pointer to array data if this is supported.
    virtual const void *examAccessArray(const OdTrVisArrayWrapper &wrapArray, bool bLock = true) const = 0;
};

/** \details
    <group ExRender_Windows_Classes>
*/
class OdTrRndSystemExternalArraysManager : public OdTrRndExternalArraysManager
{
  protected:
    static OdUInt32 examTotalSize(const ExamArrayEntry *pElem, OdUInt32 nElems)
    { OdUInt32 counter = 0;
      for (OdUInt32 nElem = 0; nElem < nElems; nElem++)
        counter += pElem->m_uSizeElems;
      return counter;
    }
  public:
    // Initialize (create) array.
    virtual void examInitializeArray(OdTrVisArrayWrapper &wrapArray, const ExamArrayEntry *pElem, OdUInt32 nElems, OdTrVisArrayWrapper::DataSize dataTypeSize) const
    { if (nElems == 1)
        wrapArray.setArray(wrapArray.type(), pElem->m_pData, pElem->m_uSizeElems, dataTypeSize);
      else
      { // Optimized concatenation of multiple input arrays.
        wrapArray.clearArray();
        const size_t dataSize = size_t(examTotalSize(pElem, nElems)) << dataTypeSize;
        wrapArray.m_pData = ::odrxAlloc(dataSize);
        if (wrapArray.m_pData == NULL)
          throw OdError(eOutOfMemory);
        size_t curPtr = 0;
        for (OdUInt32 nArray = 0; nArray < nElems; nArray++)
          ::memcpy((OdUInt8*)wrapArray.m_pData + curPtr, pElem[nArray].m_pData, size_t(pElem[nArray].m_uSizeElems) << dataTypeSize),
          curPtr += size_t(pElem[nArray].m_uSizeElems) << dataTypeSize;
        wrapArray.m_uSize = OdUInt32(dataSize >> dataTypeSize); wrapArray.m_uData = dataTypeSize;
      }
    }
    // Extend exist array.
    virtual void examExtendArray(OdTrVisArrayWrapper &wrapArray, const ExamArrayEntry *pElem, OdUInt32 nElems) const
    {
      if (nElems == 1)
        wrapArray.concatArray(pElem->m_pData, pElem->m_uSizeElems, wrapArray.dataSize());
      else
      { // Optimized concatenation of multiple input arrays.
        const size_t dataSize = size_t(examTotalSize(pElem, nElems)) << wrapArray.dataSize();
        wrapArray.m_pData = ::odrxRealloc(wrapArray.m_pData, dataSize + wrapArray.arraySize(), wrapArray.arraySize());
        if (wrapArray.m_pData == NULL)
          throw OdError(eOutOfMemory);
        size_t curPtr = wrapArray.dataSize();
        for (OdUInt32 nArray = 0; nArray < nElems; nArray++)
          ::memcpy((OdUInt8 *)wrapArray.m_pData + curPtr, pElem[nArray].m_pData, size_t(pElem[nArray].m_uSizeElems) << wrapArray.dataSize()),
          curPtr += size_t(pElem[nArray].m_uSizeElems) << wrapArray.dataSize();
        wrapArray.m_uSize += OdUInt32(dataSize >> wrapArray.dataSize());
      }
    }
    // Truncate exist array.
    virtual void examTruncateArray(OdTrVisArrayWrapper &wrapArray, OdUInt32 uSizeElems) const
    {
      wrapArray.truncateArray(uSizeElems, wrapArray.dataSize());
    }
    // Recreate array (will be called instead of Extend/Truncate in case if SupportExtending false).
    virtual void examRecreateArray(OdTrVisArrayWrapper &wrapArray, const ExamArrayEntry *pElem, OdUInt32 nElems) const
    { const OdTrVisArrayWrapper::DataSize ds = wrapArray.dataSize();
      examFreeArray(wrapArray);
      examInitializeArray(wrapArray, pElem, nElems, ds);
    }
    // Delete (free) exist array.
    virtual void examFreeArray(OdTrVisArrayWrapper &wrapArray) const
    {
      wrapArray.clearArray();
    }
    // Returns pointer to array data if this is supported.
    virtual const void *examAccessArray(const OdTrVisArrayWrapper &wrapArray, bool bLock = true) const
    {
      return (bLock) ? wrapArray.m_pData : NULL;
    }
};

#include "TD_PackPop.h"

#endif // ODTRRNDEXTERNALARRAYSMANAGER
