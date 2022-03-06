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

#ifndef _ARRAYREAD_H_
#define _ARRAYREAD_H_

#include "DbFiler.h"
#include "Ge/GePoint2d.h"
#include "Ge/GeVector2d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeVector3d.h"
//#error
namespace OdDbRdArray
{
  // Note: Direct using of arr.resize(pFiler->rdInt32())
  //       produce memory allocation error in case of invalid size value.
  //       So read data in parts to get exception with invalid data.
  //
  //  Example:
  //  Instead of
  //  m_Bulges.resize(numBulges); // Out of Memory exception may happen
  //  for (i = 0; i < numBulges; i++)
  //  {
  //    pBulges[i] = pFiler->rdDouble();
  //  }
  //  Use
  //  OdDbRdArray::rdArray<OdDbRdArray::Double>(pFiler, numBulges, m_Bulges);

  // Custom read
  //  Instead of
  //  m_Bulges.resize(numBulges); // Out of Memory exception may happen
  //  for (i = 0; i < numBulges; i++)
  //  {
  //    pBulges[i] = pFiler->rdDouble();
  //    if( fabs( pBulges[i] ) >= 1.0e16)
  //      pBulges[i] = 0;
  //  }
  //  Use
  //  namespace OdPolyline
  //  {
  //    struct Bulge
  //    {
  //      static void read(OdDbDwgFiler* pFiler, double& val)
  //      {
  //        val = pFiler->rdDouble();
  //        if (fabs(val) >= 1.0e16)
  //          val = 0;
  //      }
  //      static void write(OdDbDwgFiler* pFiler, const double& val)
  //      {
  //        pFiler->wrDouble(val);
  //      }
  //    };
  //  }
  // ...
  //  OdDbRdArray::rdArray<OdPolyline::Bulge>(pFiler, numBulges, m_Bulges);
  //
  // Below find implementations of read/write functions for
  // OdInt8, OdInt16, Odint32, double, OdGePoint2d, OdGeVector2d, OdGePoint3d, OdGeVector3d

#define ODA_ARRREAD_PAGESIZE 0xffff



//////////////////////////////////////////////////////////////////
  template< class R, class A>
  inline void rdArray(OdDbDwgFiler* pFiler, OdUInt32 nSize, A& arr)
  {
    if (pFiler->filerType() != OdDbFiler::kFileFiler)
    {
      arr.resize(nSize);
      typename A::iterator pCurr = arr.begin();
      for (unsigned i = 0; i < nSize; ++i)
      {
        R::read(pFiler, *pCurr++);
      }
    }
    else
    {
      arr.resize(0);
      OdUInt32 nPagedSize = 0, nIndex = 0;
      do
      {
        nPagedSize = odmin(nPagedSize + ODA_ARRREAD_PAGESIZE, nSize);
        arr.resize(nPagedSize);
        typename A::iterator pCurr = arr.begin() + nIndex;
        for (; nIndex < nPagedSize; ++nIndex)
        {
          R::read(pFiler, *pCurr++);
        }
      } while (nPagedSize < nSize);
    }
  }

  template< class R, class A>
  inline void wrArray(OdDbDwgFiler* pFiler, const A& arr)
  {
    typename A::const_iterator pCurr = arr.begin();
    unsigned long i = arr.size();

    while (i--)
      R::write(pFiler, *pCurr++);
  }

  ////////////////////////////////////////////////////////
  struct Int8
  {
    static void read(OdDbDwgFiler* pFiler, OdInt8& val)
    {
      val = pFiler->rdInt8();
    }
    static void write(OdDbDwgFiler* pFiler, const OdInt8& val)
    {
      pFiler->wrInt8(val);
    }
  };
  ////////////////////////////////////////////////////////
  struct Int16
  {
    static void read(OdDbDwgFiler* pFiler, OdInt16& val)
    {
      val = pFiler->rdInt16();
    }
    static void write(OdDbDwgFiler* pFiler, const OdInt16& val)
    {
      pFiler->wrInt16(val);
    }
  };
  ////////////////////////////////////////////////////////
  struct Int32
  {
    static void read(OdDbDwgFiler* pFiler, OdInt32& val)
    {
      val = pFiler->rdInt32();
    }
    static void write(OdDbDwgFiler* pFiler, const OdInt32& val)
    {
      pFiler->wrInt32(val);
    }
  };
  ////////////////////////////////////////////////////////
  struct Double
  {
    static void read(OdDbDwgFiler* pFiler, double& val)
    {
      val = pFiler->rdDouble();
    }
    static void write(OdDbDwgFiler* pFiler, const double& val)
    {
      pFiler->wrDouble(val);
    }
  };
  /*
  ////////////////////////////////////////////////////////
  struct Point2d
  {
    static void read(OdDbDwgFiler* pFiler, OdGePoint2d& val)
    {
      val = pFiler->rdPoint2d();
    }
    static void write(OdDbDwgFiler* pFiler, const OdGePoint2d& val)
    {
      pFiler->wrPoint2d(val);
    }
  };
  ////////////////////////////////////////////////////////
  struct Vector2d
  {
    static void read(OdDbDwgFiler* pFiler, OdGeVector2d& val)
    {
      val = pFiler->rdVector2d();
    }
    static void write(OdDbDwgFiler* pFiler, const OdGeVector2d& val)
    {
      pFiler->wrVector2d(val);
    }
  };
  ////////////////////////////////////////////////////////
  struct Point3d
  {
    static void read(OdDbDwgFiler* pFiler, OdGePoint3d& val)
    {
      val = pFiler->rdPoint3d();
    }
    static void write(OdDbDwgFiler* pFiler, const OdGePoint3d& val)
    {
      pFiler->wrPoint3d(val);
    }
  };
  ////////////////////////////////////////////////////////
  struct Vector3d
  {
    static void read(OdDbDwgFiler* pFiler, OdGeVector3d& val)
    {
       val = pFiler->rdVector3d();
    }
    static void write(OdDbDwgFiler* pFiler, const OdGeVector3d& val)
    {
       pFiler->wrVector3d(val);
    }
  };
  */
}
#endif //_ARRAYREAD_H_
