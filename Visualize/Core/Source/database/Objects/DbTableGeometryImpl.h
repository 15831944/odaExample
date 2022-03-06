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

#ifndef _ODDTABLEGEOMETRYIMPL_INCLUDED_
#define _ODDTABLEGEOMETRYIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbTableGeometry.h"

#include "DbObjectImpl.h"

/** Description:

  This represents a cell content's geometric data.
  This class was introduced in AutoCAD 2008.
*/

class OdCellGeometryData
{
public:
  OdGeVector3d m_distToTopLeft; // distance to top left content
  OdGeVector3d m_distToAttachmentPoint; // distance to attachment point

  double  m_widthContent; // without rotation and gap
  double  m_heightContent; // without rotation and gap
  double  m_width; // with rotation 
  double  m_height; // with rotation  
  OdInt32 m_index;

  OdCellGeometryData() : m_widthContent(0.0)
    , m_heightContent(0.0)
    , m_width(0.0)
    , m_height(0.0)
    , m_index(0) {}

  void dwgIn(OdTvDbDwgFiler* pFiler);
  void dwgOut(OdTvDbDwgFiler* pFiler) const;
  void dxfIn(OdTvDbDxfFiler* pFiler);
  void dxfOut(OdTvDbDxfFiler* pFiler) const;

};

typedef OdArray<OdCellGeometryData> OdCellGeometryDataArray;

/** Description:
 
  This represents a table cell's geometry.
  This class was introduced in AutoCAD 2008.
*/

class OdCellGeometry
{
public:
  OdInt32 m_flag;
  double  m_widthWithGap; // init horizontal gap * 2.0 
  double  m_heigthWithGap; // init vertical gap * 2.0
  OdTvDbObjectId m_objId;
  OdInt32 m_amContents; // number of elements in m_geomData (amount contents)
  OdCellGeometryDataArray m_geomData; // This represents geometric data, one instance per cell content.

  OdCellGeometry() : m_flag(0)
    , m_widthWithGap(0.0)
    , m_heigthWithGap(0.0)
    , m_amContents(0) {}

  void dxfInCell(OdTvDbDxfFiler* pFiler);
  void dxfOutCell(OdTvDbDxfFiler* pFiler);
};

typedef OdArray<OdCellGeometry> OdRowGeometry;
typedef OdArray<OdRowGeometry> OdTableGeometry;

class OdTvDbTableGeometryImpl : public OdTvDbObjectImpl
{
public:
  static OdTvDbTableGeometryImpl* getImpl(const OdTvDbTableGeometry *pObj)
  { return (OdTvDbTableGeometryImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdInt32 m_rows;
  OdInt32 m_columns;
  OdTableGeometry m_table;
public:
  OdTvDbTableGeometryImpl() : m_rows(0)
    , m_columns(0)
  {}

  friend class OdTvDbTableGeometry;
};

#endif // _ODDTABLEGEOMETRYIMPL_INCLUDED_
