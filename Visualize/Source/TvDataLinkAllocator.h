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

#ifndef _ODTV_DATALINKALLOCATOR_H_INCLUDED_
#define _ODTV_DATALINKALLOCATOR_H_INCLUDED_

#include "TD_PackPush.h"
#include "ThreadsCounter.h"
#include "OdArray.h"
#define STL_USING_MAP
#define STL_USING_ALGORITHM
#include "OdaSTL.h"

/** \details
Chunk object for the pool allocator

\remarks
When the chunk is not free, this memory can be used by the user, otherwise the
'm_pNext' field contains the address of the next free chunk (NULL if it is a last free chunk). 'm_nHeapBlockId' contains
an index of the block where this chunk is placed
*/
struct OdTvChunk
{
  OdTvChunk*        m_pNext;             //pointer to the next 'free' chunk
  unsigned int      m_nAllocBlockId;     //index of object in the allocator's block
};

class OdTvChunksBlock;

/** \details
This is the pool allocator object
*/
class OdTvLinkPoolAllocator
{
public:
  /** \details
  Constructor
  */
  OdTvLinkPoolAllocator(size_t nChunkSize, unsigned int nChucksPerBlock);

  /** \details
  Destructor
  */
  ~OdTvLinkPoolAllocator();

  /** \details
  Allocate memory
  */
  void *allocate(size_t size, bool bLock);

  /** \details
  Deallocate memory
  */
  void deallocate(OdTvChunk* pChunk, OdTvChunksBlock* pChunkOwnersBlock, bool bLock);

  /** \details
  Returns the size of allocated memory
  */
  OdUInt64 getAllocatedMemorySize();

private:

  /** \details
  Allocate memory without mutex
  */
  void* allocateNoLock(size_t size);

  /** \details
  Deallocate memory without mutex
  */
  void deallocateNoLock(OdTvChunk* pChunk, OdTvChunksBlock* pChunkOwnersBlock);

  /** \details
  Add new chunk's block
  */
  void addChunksBlock(OdTvChunksBlock*& pTopOfTheList, OdTvChunksBlock& pBlock);

  /** \details
  Remove chunk's block
  */
  void removeChunksBlock(OdTvChunksBlock*& pTopOfTheList, OdTvChunksBlock& pChunkBlockToRemove);

private:
  OdMutexPtr        m_mt;                       //mutex for working in MT mode
  OdTvChunksBlock*  m_pChunksBlocks;            //pointer to the chunks blocks (start of the list)
  OdTvChunksBlock*  m_pFullFilledChunksBlocks;  //pointer to the start of the list of fullfilled (at least once) blocks
  unsigned int      m_nChunksPerBlock;          //number of chunks in a block
  unsigned int      m_nChunkSize;               //size of the requested chunk
};
typedef OdArray<OdTvLinkPoolAllocator*, OdMemoryAllocator<OdTvLinkPoolAllocator*> > OdTvLinkPoolAllocatorArray;
typedef std::map<unsigned, OdTvLinkPoolAllocator*>  OdTvLinkThreadToPoolAllocatorMap;


/** \details
Block of the chunk objects for the pool allocator
*/
class OdTvChunksBlock
{
public:

  friend class OdTvLinkPoolAllocator;

  /** \details
  Constructor
  */
  OdTvChunksBlock(OdTvLinkPoolAllocator& a, unsigned int nChunkSize, unsigned int nChunksPerBlock)
    : m_parentAllocator(a), m_pNext(NULL), m_pPrev(NULL), m_nChunkSize(nChunkSize), m_nChunksPerBlock(nChunksPerBlock)
  {
    initBlock();
  }

  /** \details
  Destructor
  */
  ~OdTvChunksBlock() {}

  /** \details
  New operator (realy not used)
  */
  void* operator new(size_t size) { return ::odrxAlloc(size); }

  /** \details
  Delete operator
  */
  void operator delete (void* p) { ::odrxFree(p); }

  /** \details
  Method which creates a new block of chunks
  */
  static OdTvChunksBlock* create(OdTvLinkPoolAllocator& a, size_t nChunkSize, unsigned int nChunksPerBlock);

  /** \details
  Allocate new chunk (nBytes should be always the same and eqaul to nBytes / N, where nBytes is from 'create' and N is number of chunk in blocks)
  */
  void* alloc(size_t nBytes);

  /** \details
  Deallocate chunks
  */
  bool dealloc(OdTvChunk* pChunk);

  /** \details
  Returns the parent allocator
  */
  OdTvLinkPoolAllocator& allocator() { return m_parentAllocator; }

  /** \details
  Returns the number of free chunks
  */
  unsigned int numAvailable() const
  {
    return m_nAvailable;
  }

  /** \details
  Returns true if the block not contains any allocated blocks
  */
  bool empty() const
  {
    return m_nAvailable == m_nChunksPerBlock;
  }

protected:
  /** \details
  Initialize block
  */
  void initBlock();

  /** \details
  Returns the pointer to the first chunk
  */
  void* getFirstChunk();

private:
  OdTvLinkPoolAllocator& m_parentAllocator;   //parent's allocator object (important for MT mode where we have separate pools for different threads)
  OdTvChunksBlock*  m_pNext;                  //pointer to the next block (Doubly linked list)
  OdTvChunksBlock*  m_pPrev;                  //pointer to the previous block (Doubly linked list)
  OdTvChunk*        m_pFreeChunk;             //first free chunk
  unsigned int      m_nChunkSize;             //size of the requested chunk
  unsigned int      m_nChunksPerBlock;        //number of chunks per block
  unsigned int      m_nAvailable;             //number of free blocks
};

/** \details
This is the pool allocator object for using in MT
*/
class OdTvLinkPoolAllocatorMT
{
public:
  /** \details
  Constructor
  */
  OdTvLinkPoolAllocatorMT(size_t nChunkSize);

  /** \details
  Destructor
  */
  ~OdTvLinkPoolAllocatorMT();

  /** \details
  Allocate memory
  */
  void *allocate(size_t size);

  /** \details
  Deallocate memory
  */
  void deallocate(OdTvChunk* pChunk);

  /** \details
  Returns the size of allocated memory
  */
  OdUInt64 getAllocatedMemorySize() const;

private:

  /** \details
  Tries to find thread pool
  */
  OdTvLinkPoolAllocator* findHeap(unsigned threadId) const;


private:
  OdTvLinkPoolAllocatorArray m_allocators;            //all allocators (main and threads allocators)
  OdTvLinkThreadToPoolAllocatorMap m_threadToPools;   //map for thread and pools
  OdTvLinkPoolAllocator* m_pMainAllocator;            //main alocator (for ST mode)
  mutable OdMutex m_mt;                               //mutex 
  unsigned int m_nChunkSize;                          //size of the requested chunk
  OdVolatile m_bHasThreadPools;                       //indicator about the presence of the thread pools
};

#include "TD_PackPop.h"


#endif // _ODTV_DATALINKALLOCATOR_H_INCLUDED_

