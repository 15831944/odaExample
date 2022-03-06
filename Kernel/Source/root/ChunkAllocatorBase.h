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

#ifndef _CHUNKALLOCATORBASE_H_
#define _CHUNKALLOCATORBASE_H_

#include "OdaCommon.h"
#include "ThreadsCounter.h"

#ifdef free   // defined in \microsoft visual studio 8\vc\include\crtdbg.h 
  #undef free  
#endif

#ifdef _DEBUG
//#define CHECK_MEM_BLOCK_VALIDITY
#endif

#if (OD_SIZEOF_PTR != 4) || defined(TD_STRICT_ALIGNMENT)// 64bit OS or Platforms with strict alignment
static const unsigned int ALIGNMENT_SHIFT = 3;
static const unsigned int ALIGNMENT_MASK = 0x7;
#else
static const unsigned int ALIGNMENT_SHIFT = 2;
static const unsigned int ALIGNMENT_MASK = 0x3;
#endif
#define alignedSize(requestedSize) ((requestedSize & ALIGNMENT_MASK ? ((requestedSize & ~ALIGNMENT_MASK) + ALIGNMENT_MASK + 1) : requestedSize))


template <class TChunk>
class TMemBlock
{
public:
#ifdef TD_STRICT_ALIGNMENT
    void* getData() { return (void*)( reinterpret_cast<char*>(this) + alignedSize(sizeof(TMemBlock))); }
#else
    void* getData() { return (void*)(this + 1); }
#endif
    TChunk* chunk() { return m_chunk; }
    void setChunk(TChunk* pChunk) { m_chunk = pChunk; }

#ifdef CHECK_MEM_BLOCK_VALIDITY
    bool isValid() const { return m_dummyCheck == 123; }
    void init(int iIndex) { m_dummyCheck = 123; m_iIndex = iIndex; }
#endif

protected:
    TMemBlock(): m_chunk(NULL)
#ifdef CHECK_MEM_BLOCK_VALIDITY
        , m_dummyCheck(123), m_iIndex(0)
#endif
    {}

protected:
#ifdef CHECK_MEM_BLOCK_VALIDITY
    int m_dummyCheck;
    int m_iIndex;
#endif
    TChunk* m_chunk;
};

static const unsigned cDefaultChunkSize = 100*1024;

///////////////////////////////////////////////////////////////////////////////
// General purpose allocator
///////////////////////////////////////////////////////////////////////////////
struct CChunk;
class ChunkAllocator;

struct CChunk
{
public:
   class MemBlock: public TMemBlock<CChunk>
   {
   public:
   };

#ifdef TD_STRICT_ALIGNMENT
   static const size_t s_cOVERHEAD = alignedSize(sizeof(MemBlock));
#else
   static const size_t s_cOVERHEAD = sizeof(MemBlock);
#endif
public:
    CChunk(ChunkAllocator& a, size_t nBytes): m_alloc(a), m_next(NULL), m_prev(NULL)
    {
      m_nChunkSize = static_cast<int>(nBytes);
      init();
    }
    ~CChunk()
    {
    }

    ChunkAllocator& allocator() { return m_alloc; }

    void* operator new(size_t size)
    {
      return ::odrxAlloc(size);
    }

    void operator delete (void* p)
    {
      ::odrxFree(p);
    }

    static CChunk* create(ChunkAllocator& a, size_t nBytes)
    {
      ODA_ASSERT(nBytes == alignedSize(nBytes));
#ifdef TD_STRICT_ALIGNMENT
      void* pMem = ::odrxAlloc(alignedSize(sizeof(CChunk)) + nBytes);
#else
      void* pMem = ::odrxAlloc(sizeof(CChunk) + nBytes);
#endif
      return ::new (pMem) CChunk(a, nBytes);
    }

    size_t numAvailable() const
    {
      return m_nAvailable;
    }
#ifdef TD_STRICT_ALIGNMENT
    char* getData() { return reinterpret_cast<char*>(this) + alignedSize(sizeof(CChunk)); }
#else
    char* getData() { return reinterpret_cast<char*> (this + 1); }
#endif

    char* alloc(size_t nBytes)
    {
      ODA_ASSERT(nBytes <= numAvailable());
      ODA_ASSERT(m_pFirstAvailable);
      ++m_nAllocatedBlocks;
      char* pRes = reinterpret_cast<char*>(m_pFirstAvailable->getData());
#ifdef TD_STRICT_ALIGNMENT
      ODA_ASSERT((OdIntPtr)pRes%8 == 0);
      ODA_ASSERT(nBytes == alignedSize(nBytes));
#endif
      if(m_nAvailable > nBytes + s_cOVERHEAD)
      {
          //shift pointer to the next block
          m_pFirstAvailable = reinterpret_cast<MemBlock*>(pRes + nBytes);
          m_pFirstAvailable->setChunk(this);
          m_nAvailable -= nBytes + s_cOVERHEAD;
      }
      else
      {
          m_pFirstAvailable = 0;
          m_nAvailable = 0;
      }
      return pRes;
    }

    bool freeBlock()
    {
      ++m_nDeallocatedBlocks;
      if (m_nDeallocatedBlocks == m_nAllocatedBlocks)
      {
        init();
        return true;
      }
      return false;
    }
    friend class ChunkAllocator;

protected:
    void init()
    {
      m_nAllocatedBlocks = m_nDeallocatedBlocks = 0;
      m_pFirstAvailable = reinterpret_cast<MemBlock*>(getData());
      m_pFirstAvailable->setChunk(this);
      m_nAvailable = m_nChunkSize - s_cOVERHEAD;
    }
private:
    ChunkAllocator& m_alloc;
    CChunk* m_next;
    CChunk* m_prev;
    MemBlock* m_pFirstAvailable;
    size_t m_nAvailable;
    int m_nChunkSize;
    int m_nAllocatedBlocks;
    int m_nDeallocatedBlocks;
    //when m_nDeallocatedBlocks == m_nAllocatedBlocks && m_nAllocatedBlocks != 0,
    //we can use the chunk again from beginning
};

class BaseChunkAllocator
{
public:
  BaseChunkAllocator(): m_threadId(0){}
  unsigned threadId() const { return m_threadId; }
  void setThreadId(unsigned id)
  {
    ODA_ASSERT(id ? m_threadId == 0 : m_threadId);
    m_threadId = id;
  }
protected:
  unsigned m_threadId;
  OdMutexPtr m_mt;
};

class ChunkAllocator: public BaseChunkAllocator
{
public:
#ifdef TD_STRICT_ALIGNMENT
  ChunkAllocator(int nChunkSize = alignedSize(cDefaultChunkSize - sizeof(CChunk)))
#else
  ChunkAllocator(int nChunkSize = cDefaultChunkSize - sizeof(CChunk))
#endif
    : m_chunks(NULL)
    , m_nChunkSize((size_t)nChunkSize)
  {
  }

  ~ChunkAllocator()
  {
    TD_AUTOLOCK_P_DEF(m_mt);
    for(CChunk* itb = m_chunks; itb; )
    {
      CChunk* p = itb;
      itb = itb->m_next;
      delete p;
    }
  }

  int numChunks()
  {
    TD_AUTOLOCK_P_DEF(m_mt);
    int count = 0;
    for(CChunk* pChunk = m_chunks; pChunk; pChunk = pChunk->m_next, ++count);
    return count;
  }

  void* alloc(int nBytes, bool bLock)
  {
    if(bLock)
    {
      TD_AUTOLOCK_P(m_mt.get());
      return allocNoLock((size_t)nBytes);
    }
    return allocNoLock((size_t)nBytes);
  }

  bool release(CChunk::MemBlock* pBlock, bool bLock)
  {
    if(!pBlock)
      return false;
    if(bLock)
    {
      TD_AUTOLOCK_P(m_mt.get());
      return releaseBlockInChunkNoLock(pBlock->chunk());
    }
    return releaseBlockInChunkNoLock(pBlock->chunk());
  }

  void* allocNoLock(size_t nBytes)
  {
    nBytes = alignedSize(nBytes);
    if(nBytes > m_nChunkSize)
      return addChunk(nBytes, nBytes);
    CChunk* pChunk = m_chunks;
  if(!pChunk || nBytes > pChunk->numAvailable())
      return addChunk(m_nChunkSize, nBytes);
    return pChunk->alloc(nBytes);
  }

  bool releaseBlockInChunkNoLock(CChunk* pChunk)
  {
    if(pChunk->freeBlock())
    {
      removeChunk(pChunk);
      delete pChunk;
      return true;
    }
    return false;
  }

  bool isEmpty()
  {
    if(odThreadsCounter())
    {
      TD_AUTOLOCK_P(m_mt.get());
      return !m_chunks;
    }
    return !m_chunks;
  }

private:
  //nBytesToAlloc does not include MemBlock overhead
  char* addChunk(size_t nBytesInChunk, size_t nBytesToAlloc)
  {
    ODA_ASSERT(nBytesToAlloc == alignedSize(nBytesToAlloc));
    if(nBytesToAlloc + CChunk::s_cOVERHEAD > nBytesInChunk)
        nBytesInChunk = nBytesToAlloc + CChunk::s_cOVERHEAD;

    nBytesInChunk = alignedSize(nBytesInChunk);
  ODA_ASSERT(nBytesInChunk >= nBytesToAlloc + CChunk::s_cOVERHEAD);
    CChunk* pChunk = CChunk::create(*this, nBytesInChunk);
  char* res = pChunk->alloc(nBytesToAlloc);
    prepend(pChunk);
    return res;
  }
  
  void prepend(CChunk* pChunk)
  {
    pChunk->m_next = m_chunks;
    if(m_chunks)
        m_chunks->m_prev = pChunk;
    m_chunks = pChunk;
  }

  CChunk* removeChunk(CChunk* pChunk)
  {
    CChunk* pNext = pChunk->m_next;
    if(pChunk == m_chunks)
    {
      m_chunks = pNext;
      if(pNext)
        pNext->m_prev = NULL;
    }
    else
    {
      if(pChunk->m_prev)
          pChunk->m_prev->m_next = pNext;
      if(pNext)
          pChunk->m_next->m_prev = pChunk->m_prev;
    }
    return pNext;
  }
private:
  CChunk* m_chunks;
  size_t m_nChunkSize;
};

#endif // _CHUNKALLOCATORBASE_H_
