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

#ifndef _IDARRAYREAD_H_
#define _IDARRAYREAD_H_

namespace OdTvDbId
{
  // Note: Direct using of ids.resize(pFiler->rdInt32())
  //       produce memory allocation error in case of invalid size value.
  //       So read data in parts to get exception with invalid data.
#define ODA_IDREAD_PAGESIZE 0xffff


  
//////////////////////////////////////////////////////////////////
// This is workaround for MSVC 6 bug: http://support.microsoft.com/kb/240871
// "If all the template parameters are not used in function arguments or return type
//  of a template function, the template functions are not overloaded correctly."
// ODA defect 5270

#if (defined (_MSC_VER) && _MSC_VER == 1200)
  #define TEMPLATE_FUNC_RET_TYPE  R*
  #define TEMPLATE_FUNC_RETURN    return 0;
#else
  #define TEMPLATE_FUNC_RET_TYPE  void
  #define TEMPLATE_FUNC_RETURN
#endif

  template< class R, class A> 
  inline TEMPLATE_FUNC_RET_TYPE rdArray(OdTvDbDwgFiler* pFiler, A& ids, bool bSkipDuplicates = false)
  {
    OdUInt32 nIdsSize = pFiler->rdInt32();
    if (pFiler->filerType() != OdTvDbFiler::kFileFiler)
    {
      ids.resize(nIdsSize);
      typename A::iterator pCurr = ids.begin();
      for (unsigned i = 0; i < nIdsSize; ++i)
      {
        OdTvDbObjectId id = R::read(pFiler);
        *pCurr++ = id;
      }
    }
    else
    {
      ids.resize(0);
      OdUInt32 nIdsPagedSize = 0, nIndex = 0;
      if (!bSkipDuplicates)
      {
        do
        {
          nIdsPagedSize = odmin(nIdsPagedSize + ODA_IDREAD_PAGESIZE, nIdsSize);
          ids.reserve(nIdsPagedSize);
          for ( ; nIndex < nIdsPagedSize; ++nIndex)
          {
            OdTvDbObjectId id = R::read(pFiler);
            if (!id.isNull())
              ids.append(id);
          }
        }
        while (nIdsPagedSize < nIdsSize);
      }
      else
      {
        do
        {
          nIdsPagedSize = odmin(nIdsPagedSize + ODA_IDREAD_PAGESIZE, nIdsSize);
          ids.reserve(nIdsPagedSize);
          for ( ; nIndex < nIdsPagedSize; ++nIndex)
          {
            OdTvDbObjectId id = R::read(pFiler);
            if (!id.isNull() && !ids.contains(id))
              ids.append(id);
          }
        }
        while (nIdsPagedSize < nIdsSize);
      }
    }
    TEMPLATE_FUNC_RETURN
  }
  
  template< class R, class A> 
  inline TEMPLATE_FUNC_RET_TYPE wrArray(OdTvDbDwgFiler* pFiler, const A& ids)
  {
    typename A::const_iterator pCurr = ids.begin();
    unsigned long i = ids.size();

    if ( pFiler->filerType() != OdTvDbFiler::kFileFiler )
    {
      pFiler->wrInt32(ids.size());
      while ( i-- )
        R::write(pFiler, *pCurr++);
    }
    else
    {
      unsigned long count = 0;
      while ( i-- )
      {
        if ( !pCurr->isErased() )
        {
          R::write(pFiler, *pCurr);
          count++;
        }
        ++pCurr;
      }
      pFiler->wrInt32(count);
    }
    TEMPLATE_FUNC_RETURN
  }
  
  struct HardPointer
  {
    static OdTvDbObjectId read( OdTvDbDwgFiler* pFiler )
    {
      return pFiler->rdHardPointerId();
    }
    static void write( OdTvDbDwgFiler* pFiler, const OdTvDbObjectId& id )
    {
      pFiler->wrHardPointerId( id );
    }
  };
  struct SoftPointer
  {
    static OdTvDbObjectId read( OdTvDbDwgFiler* pFiler )
    {
      return pFiler->rdSoftPointerId();
    }
    static void write( OdTvDbDwgFiler* pFiler, const OdTvDbObjectId& id )
    {
      pFiler->wrSoftPointerId( id );
    }
  };
  struct HardOwner
  {
    static OdTvDbObjectId read( OdTvDbDwgFiler* pFiler )
    {
      return pFiler->rdHardOwnershipId();
    }
    static void write( OdTvDbDwgFiler* pFiler, const OdTvDbObjectId& id )
    {
      pFiler->wrHardOwnershipId( id );
    }
  };
  struct SoftOwner
  {
    static OdTvDbObjectId read( OdTvDbDwgFiler* pFiler )
    {
      return pFiler->rdSoftOwnershipId();
    }
    static void write( OdTvDbDwgFiler* pFiler, const OdTvDbObjectId& id )
    {
      pFiler->wrSoftOwnershipId( id );
    }
  };
}

#endif //_IDARRAYREAD_H_
