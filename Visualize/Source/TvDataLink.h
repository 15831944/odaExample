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


#ifndef _ODTV_DATALINK_H_INCLUDED_
#define _ODTV_DATALINK_H_INCLUDED_

#include "TD_PackPush.h"
#include "GiWorldDraw.h"
#include "ChunkAllocator.h"
#include "TvGeometryData.h"
#include "TvInterfaceWrappers.h"
#include "TvDataLinkAllocator.h"

void newDataLink();
void deleteDataLink();


/** \details
This class implements the child of OdTvIObject with the default implementation
of the reference counter
*/
class OdTvIObjectImpl : public OdTvIObject
{

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Default constructor for this class.
  */
  OdTvIObjectImpl()
  : m_nRefCounter(1)
  {}

  /** \details
  The virtual destructor for this class.
  */
  virtual ~OdTvIObjectImpl() {}

  /** \details
  Declares the method incrementing the reference counter in objects derived from this class.
  */
  virtual void addRef()
  {
    ++m_nRefCounter;
  }

  /** \details
  Declares the method decrementing the reference counter in objects derived from this class.
  */
  virtual void release()
  {
    if (m_nRefCounter == 1)
    {
      delete this;
    }
    else
      --m_nRefCounter;
  }
  /** \details
  Returns the value of the reference counter, that is, the number of references to an instance of this class.
  */
  virtual long numRefs() const
  {
    return m_nRefCounter;
  }

protected:
  // reference counter
  unsigned int                m_nRefCounter;

};


/** \details
This is the data link object
*/
class OdTvDataLink
{
  /** \details
     Default constructor prohibited.
  */
  OdTvDataLink() {}

  /** \details
      Copy constructor prohibited.
  */
  OdTvDataLink(const OdTvDataLink&);

  /** \details
      Assignment operator prohibited.
  */
  OdTvDataLink& operator = (const OdTvDataLink&);

  /** \details
  Constructor with data prohibited for external use.
  */
  OdTvDataLink(OdTvIObject* pData, int blockId) : m_pData(pData), m_nRefCounter(1), m_nAllocBlockId(blockId) {}

public:
  /** \details
  New operator (realy not used)
  */
  void* operator new(size_t size);

  /** \details
  Delete operator
  */
  void  operator delete(void* p);

  /** \details
  Create object
  */
  static OdTvDataLink* create(OdTvIObject* pData);

  /** \details
  Destructor
  */
  ~OdTvDataLink() { }

  /** \details
    Declares the method incrementing the reference counter in objects derived from this class.
  */
  void addRef()
  {
    ++m_nRefCounter;
  }

  /** \details
    Declares the method decrementing the reference counter in objects derived from this class.
  */
  void release()
  {
    if (m_nRefCounter == 1)
    {
      delete this;
    }
    else
      --m_nRefCounter;
  }

  /** \details
    Returns the value of the reference counter, that is, the number of references to an instance of this class.
  */
  long numRefs() const { return m_nRefCounter; }

  /** \details
    Checks that the linked data is valid.
  */
  bool isDataValid() const { return m_pData != NULL; }

  /** \details
    Free the data link.
  */
  void freeData() { m_pData = NULL; }

  /** \details
    Get the pointer to the linked object
  */
  OdTvIObject* getData() { return m_pData; }

  /** \details
  Return the value of memory, which all all links takes up.
  */
  static OdUInt64 getChunksSize(OdTvResult* rc = NULL);

protected:

  /** \details
  Own allocator
  */
  static OdTvLinkPoolAllocatorMT s_aAlloc;

private:

  OdTvIObject*      m_pData;         //pointer to the object
  unsigned int      m_nRefCounter;   //reference counter
  unsigned int      m_nAllocBlockId; //index of object in the allocator's block
};


/** \details
This class implements the accessor to the linked interface Id object
*/
template <class T>
class OdTvLinkIdAccess : public OdTvLinkId
{
public:
  static void objectSet(OdTvLinkId* pId, T* pReference)
  {
    if (pId)
    {
      //decrease ref counter for the current link
      void* pCurLink = (static_cast<OdTvLinkIdAccess*>(pId))->m_pLink;
      if (pCurLink)
      {
        OdTvDataLink* pLinkThis = static_cast<OdTvDataLink*>(pCurLink);
        if (pLinkThis)
          pLinkThis->release();
      }

      if (pReference)
      {
        OdTvDataLink* pLink = pReference->getLink();
        if (pLink)
          pLink->addRef();

        (static_cast<OdTvLinkIdAccess*>(pId))->m_pLink = pLink;
      }
      else
      {
        (static_cast<OdTvLinkIdAccess*>(pId))->m_pLink = NULL;
        (static_cast<OdTvLinkIdAccess*>(pId))->m_pMiscIdData = NULL;
      }
    }
  }

  static void miscDataSet(OdTvLinkId* pId, void* pMiscData)
  {
    if (pId)
      (static_cast<OdTvLinkIdAccess*>(pId))->m_pMiscIdData = pMiscData;
  }

  static T* objectGet(const OdTvLinkId* pId)
  {
    if (!pId)
      return NULL;

    const OdTvLinkIdAccess* pIdAccess = static_cast<const OdTvLinkIdAccess*>(pId);
    if (pIdAccess->m_pLink)
    {
      OdTvDataLink* pLink = static_cast<OdTvDataLink*>(pIdAccess->m_pLink);
      if (pLink && pLink->isDataValid())
        return static_cast<T*>(pLink->getData()); // here we always have data since we already check it via 'isDataValid()'
    }
    return NULL;
  }

  static void* miscDataGet(const OdTvLinkId* pId)
  {
    if (!pId)
      return NULL;

    const OdTvLinkIdAccess* pIdAccess = static_cast<const OdTvLinkIdAccess*>(pId);

    return pIdAccess->m_pMiscIdData;
  }
};


#endif //_ODTV_DATALINK_H_INCLUDED_
