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

#ifndef _ODTV_TRAITSDEFIMPL_H_INCLUDED_
#define _ODTV_TRAITSDEFIMPL_H_INCLUDED_

#include "TD_PackPush.h"

// TD_DB
#include "DbObjectId.h"
#include "CmColorBase.h"
#include "CmEntityColorArray.h"
#include "Ge/GeVector3dArray.h"
#include "Int32Array.h"
#include "DbStubPtrArray.h"
#include "UInt8Array.h"
#include "CmTransparencyArray.h"
#include "CmColor.h"
#include "GiLightTraits.h"

//TV
#include "TvTraitsDef.h"
#include "TvLight.h"
#include "Ge/GeVector2dArray.h"
#include "Gs/GsFiler.h"
#include "TvMaterial.h"
#include "TvMaterialImpl.h"
#include "TvDatabase.h"
#include "GiFill.h"


/** \details
Internal enum for OdTvSelectabilityDef
*/
enum Selectability
{
  kGeometries = 1,
  kFaces = 2,
  kEdges = 4,
  kVertices = 8,         // NOT IMPLEMENTED YET
  kInherited = 16 //only for internal using
};


/** \details
Internal enum for OdTvColorDef
*/
enum ColorMethod
{
  kByNone = 0,
  kByColor = 1,
  kByIndex = 2,
  kByLayer = 3,
  kByBlock = 4,
};

/** \details
This class implements specifics of tv color rendition.
This implementation is very familar to OdDgCmEntityColor and uses
kByDgnIndex for the indexed colors
*/
class OdTvCmEntityColor : public OdCmEntityColor
{
public:

  OdTvCmEntityColor()
    : OdCmEntityColor(){}
  
  OdTvCmEntityColor(
    const OdCmEntityColor & color)
    : OdCmEntityColor(color){}

  OdTvCmEntityColor& operator =(
    const OdCmEntityColor& color)
  {
    *((OdCmEntityColor*)this) = color;
    return *this;
  }

  bool operator ==(
    const OdCmEntityColor& color) const
  {
    return OdCmEntityColor::operator == (color);
  }

  bool operator ==(
    const OdTvCmEntityColor& color) const
  {
    return *((OdCmEntityColor*)this) == *((OdCmEntityColor*)&color);
  }

  bool operator !=(
    const OdCmEntityColor& color) const
  {
    return OdCmEntityColor::operator != (color);
  }

  bool operator !=(
    const OdTvCmEntityColor& color) const
  {
    return *((OdCmEntityColor*)this) != *((OdCmEntityColor*)&color);
  }

  void setColorIndex(OdInt16 colorIndex);

  static void setColorIndex(OdUInt32* rgbm, OdInt16 colorIndex);
};


/** \details
This class implements the wrapper over  OdCmEntityColorArray (in the realiaty the OdTvCmEntityColorArray)
which allows to control and manage the contains of the array via specific ways
*/
class OdTvColorArrayStorage
{
  OdCmEntityColorArray  m_colors;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvColorArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;
  bool                    isHasNotEmpty() const;
  void                    setPhysicalLength(OdInt32 nSize);

  // get
  OdTvCmEntityColor      colorAt(OdUInt32 ind) const;
  const OdCmEntityColor*  asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  static void             readEx(OdTvDbDwgFiler* pFiler, OdCmEntityColor* colors, OdUInt32 nColors, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  static void             writeEx(OdTvDbDwgFiler* pFiler, const OdCmEntityColor* colors, OdUInt32 nColors, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvColorDef* colors, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvColorDef& color, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvRGBColorDef* colors, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvRGBColorDef& color, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors, bool bOnlyEmpty = false);

  bool setAt(OdInt32 id, const OdTvRGBColorDef& color);

  OdUInt64 getSizeOfDynamicData() const;
};


/** \details
This class implements the wrapper over  OdGeVector3dArray
which allows to control and manage the contains of the array via specific ways
*/
class OdTvVector3dArrayStorage
{
  OdGeVector3dArray     m_vectors;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvVector3dArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  // get
  OdGeVector3d            vectorAt(OdUInt32 ind) const;
  const OdGeVector3d*     asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGeVector3d* vectors, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGeVector3d& vector, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGeVector3d& vector, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGeVector3d* vectors, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

private:
  // specific for write/read vectors method (sometimes can write less data)
  void wrVector(OdTvDbDwgFiler* pFiler, const OdGeVector3d& p) const;
  void rdNormal(OdTvDbDwgFiler* pFiler, OdTvVector& p);
};

/** \details
This class implements the wrapper over  OdGeVector2dArray
which allows to control and manage the contains of the array via specific ways
*/
class OdTvVector2dArrayStorage
{
  OdGeVector2dArray     m_vectors;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvVector2dArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  // get
  OdGeVector2d            vectorAt(OdUInt32 ind) const;
  const OdGeVector2d*     asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGeVector2d* vectors, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGeVector2d& vector, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGeVector2d& vector, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGeVector2d* vectors, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

private:
  // specific for write/read vectors method (sometimes can write less data)
  void wrVector(OdTvDbDwgFiler* pFiler, const OdGeVector2d& p) const;
  void rdNormal(OdTvDbDwgFiler* pFiler, OdTvVector2d& p);
};

/** \details
This class implements the wrapper over OdGePoint3dArray
which allows to control and manage the contains of the array via specific ways
*/
class OdTvPoint2dAs3dArrayStorage
{
  OdGePoint3dArray      m_points;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvPoint2dAs3dArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  // get
  OdGePoint3d            pointAt(OdUInt32 ind) const;
  const OdGePoint3d*     asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGePoint3d* points, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGePoint3d& point, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGePoint3d& point, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGePoint3d* points, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

private:
  // specific for write/read points method (sometimes can write less data)
  void wrPoint(OdTvDbDwgFiler* pFiler, const OdTvPoint& p) const;
  void rdPoint(OdTvDbDwgFiler* pFiler, OdTvPoint& p);
};

/** \details
This class implements the wrapper over OdGePoint2dArray
which allows to control and manage the contains of the array via specific ways
*/
class OdTvPoint2dArrayStorage
{
  OdGePoint2dArray      m_points;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvPoint2dArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  // get
  OdGePoint2d            pointAt(OdUInt32 ind) const;
  const OdGePoint2d*     asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGePoint2d* points, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdGePoint2d& point, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGePoint2d& point, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdGePoint2d* points, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

private:
  // specific for write/read points method (sometimes can write less data)
  void wrPoint(OdTvDbDwgFiler* pFiler, const OdTvPoint2d& p) const;
  void rdPoint(OdTvDbDwgFiler* pFiler, OdTvPoint2d& p);
};

/** \details
This class implements the wrapper over OdDbStubPtrArray
which allows to control and manage the contains of the array via specific ways
*/
class OdTvStubArrayStorage
{
  OdDbStubPtrArray      m_stubs;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvStubArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  // get
  OdDbStub*               stubAt(OdUInt32 ind) const;
  OdDbStub**              asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, OdDbStub** stubs, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, OdDbStub* stub, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, OdDbStub* stub, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, OdDbStub** stubs, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

};

/** \details
This class implements the wrapper over OdUInt8Array FOR STORING OdUInt8 values
which allows to control and manage the contains of the array via specific ways
*/
class OdTvUInt8ArrayStorage
{
  OdUInt8Array      m_values;
  OdInt32Array      m_emptyIndexes;

public:
  OdTvUInt8ArrayStorage() {}

  // some simple basic methods
  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  // get
  OdUInt8                 valueAt(OdUInt32 ind) const;
  const OdUInt8*          asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  static void             readEx(OdTvDbDwgFiler* pFiler, OdUInt8* pValues, OdUInt32 nValues, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  static void             writeEx(OdTvDbDwgFiler* pFiler, const OdUInt8* pValues, OdUInt32 nValues, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvVisibilityDef* values, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvVisibilityDef& val, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& val, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* values, bool bOnlyEmpty = false);

  bool setViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvTransparencyDef* values, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvTransparencyDef& val, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

};

/** \details
This class implements the wrapper over  OdCmTransparencyArray
which allows to control and manage the contains of the array via specific ways
*/
class OdTvTransparencyArrayStorage
{
  OdCmTransparencyArray m_transparency;
  OdInt32Array          m_emptyIndexes;

public:
  OdTvTransparencyArrayStorage() {};

  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  //get
  OdCmTransparency        transparencyAt(OdUInt32 ind) const;
  const OdCmTransparency* asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvTransparencyDef* transparencies, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvTransparencyDef& transparency, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef& transparency, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef* transparencies, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

};

/** \details
This class implements the wrapper over  OdGiMapper
which allows to control and manage the contains of the array via specific ways
*/
class OdGiMapperArrayStorage
{
  OdGiMapperArray       m_mappers;
  OdInt32Array          m_emptyIndexes;

public:
  OdGiMapperArrayStorage() {};

  void                    init(OdInt32 nSize);
  void                    clear();
  OdUInt32                size() const;
  OdUInt32                emptySize() const;
  bool                    isEmpty() const;
  bool                    isFirstEmpty() const;

  //get
  OdTvMapperDef           mapperAt(OdUInt32 ind) const;
  const OdGiMapper*       asArrayPtr() const;

  // empty (none) indexes stuff
  OdUInt32                initEmptyIndexes();
  void                    resetEmptyIndexes();

  // read/write
  void                    read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void                    write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  // set
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvMapperDef* mappers, bool bOnlyEmpty = false);
  bool setViaList(OdInt32 nCount, const OdInt32* indexes, const OdTvMapperDef& mapper, bool bOnlyEmpty = false);

  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef& mapper, bool bOnlyEmpty = false);
  bool setViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef* mappers, bool bOnlyEmpty = false);

  OdUInt64 getSizeOfDynamicData() const;

  // specific for write/read mapper method (sometimes can write less data)
  static void wrMapper(OdTvDbDwgFiler* pFiler, const OdGiMapper& p);
  static void rdMapper(OdTvDbDwgFiler* pFiler, OdGiMapper& p);
  static bool isDefault(const OdGiMapper& mapper);
  static void setDefault(OdGiMapper& mapper);
};


/** \details
This class implements the accessor to the non-public part of 'OdTvSelectabilityDef'

\remarks
This class is for the internal using only
*/
class OdTvSelectabilityAccess : public OdTvSelectabilityDef
{
public:

  /** \details
  Set the selectability is inherited
  */
  static void setInherited(OdTvSelectabilityDef* pDef, bool bVal)
  {
    SETBIT((static_cast<OdTvSelectabilityAccess*>(pDef))->m_data, kInherited, bVal);
  }

  /** \details
  Get the selectability is inherited
  */
  static bool getInherited(const OdTvSelectabilityDef* pDef)
  {
    return GETBIT((static_cast<const OdTvSelectabilityAccess*>(pDef))->m_data, kInherited);
  }

  /** \details
  Set the selectability value
  */
  static void setValue(OdTvSelectabilityDef* pDef, OdUInt8 val)
  {
    (static_cast<OdTvSelectabilityAccess*>(pDef))->m_data = val;
  }

  /** \details
  Get the selectability value
  */
  static OdUInt8 getValue(const OdTvSelectabilityDef* pDef)
  {
    return (static_cast<const OdTvSelectabilityAccess*>(pDef))->m_data;
  }
};


/** \details
Get data from OdTvDbObjectId and write in OdTvLinetypeDef
*/
OdTvLinetypeDef getLinetypeFromDbId(OdTvDbObjectId id, OdTvDbDatabase* pDb);

/** \details
Get OdTvDbObjectId from OdTvLinetypeDef
*/
OdTvDbObjectId getDbIdFromLinetype(const OdTvLinetypeDef& linetype, OdTvDbDatabase* pDb);

/** \details
Get data from OdTvDbObjectId and write in OdTvLinetypeDef
*/
OdTvLayerDef getLayerFromDbId(OdTvDbObjectId id, OdTvDbDatabase* pDb);

/** \details
Get OdTvDbObjectId from OdTvLayerDef
*/
OdTvDbObjectId getDbIdFromLayer(const OdTvLayerDef& linetype, OdTvDbDatabase* pDb);

/** \details
Get tv cm entity color from tv color definition
*/
OdTvCmEntityColor getTvCmEntityColorFromDef(const OdTvColorDef& color);

/** \details
Get tv cm entity color from tv rgb color definition
*/
OdTvCmEntityColor getTvCmEntityColorFromRGBDef(const OdTvRGBColorDef& color);

/** \details
Get tv color definition from tv cm entity color
*/
OdTvColorDef getTvColorDefFromCmColor(const OdTvCmEntityColor& cmColor);

/** \details
Get tv rgb color definition from tv cm entity color
*/
OdTvRGBColorDef getTvColorRGBDefFromCmColor(const OdTvCmEntityColor& cmColor);

/** \details
Get cm color definition from tv color def
*/
OdTvCmColor getCmColorFromDef(const OdTvColorDef& color);

/** \details
Get tv color def definition from cm color
*/
OdTvColorDef getTvColorDefFromCm(const OdTvCmColor& cmColor);

/** \details
Get cm entity color definition from tv color def
*/
OdCmEntityColor getCmEntityColorFromDef(const OdTvColorDef& color);

/** \details
Get cm entity color definition from tv rgb color def
*/
OdCmEntityColor getCmEntityColorFromDef(const OdTvRGBColorDef& color);

/** \details
Get tv color def definition from cm entity color
*/
OdTvColorDef getTvColorDefFromCm(const OdCmEntityColor& cmColor);

/** \details
Get OdDb::LineWeight from lineweight definition
*/
OdDb::LineWeight getOdDbLineWeightFromDef(const OdTvLineWeightDef& lw);

/** \details
Get tv lineweight definition from db lineweight
*/
OdTvLineWeightDef getTvLineWeightDefFromDbLineWeight(const OdDb::LineWeight& dbLw);

/** \details
Get OdCmTransparency from OdTrfTransparencyDef
*/
OdCmTransparency getCmTransparencyFromDef(const OdTvTransparencyDef& transparency);

/** \details
Get OdTrfTransparencyDef from OdCmTransparency
*/
OdTvTransparencyDef getOdTvTransparencyDefFromCmTransparency(const OdCmTransparency& transparency);

/** \details
Get invisible bool from OdTvVisibilityDef
*/
OdUInt8 getUIntFromOdTvVisibilityDef(const OdTvVisibilityDef& visDef);

/** \details
Get OdTvVisibilityDef from visibility bool
*/
OdTvVisibilityDef getOdTvVisibilityDefFromBool(bool bVisible);

/** \details
Get OdTvVisibilityDef from visibility OdUInt8
*/
OdTvVisibilityDef getOdTvVisibilityDefFromOdUint8(OdUInt8 visibility);

/** \details
Get data from OdTvDbObjectId and write in OdTvTextStyleDef
*/
OdTvTextStyleDef getTextStyleFromDbId(OdTvDbObjectId id, OdTvDbDatabase * pDb);

/** \details
Get OdTvDbObjectId from OdTvTextStyleDef
*/
OdTvDbObjectId getDbIdFromTextStyle(const OdTvTextStyleDef& textStyle, OdTvDbDatabase* pDb);

/** \details
Get data from OdTvDbObjectId and write in OdTvMaterialDef
*/
OdTvMaterialDef getMaterialFromDbId(OdTvDbObjectId id, OdTvDbDatabase * pDb);

/** \details
Get OdTvDbObjectId from OdTvMaterialDef
*/
OdTvDbObjectId getDbIdFromMaterial(const OdTvMaterialDef& material, OdTvDbDatabase* pDb);

/** \details
Get data from OdGiMapper and write in OdTvMapper
*/
OdTvTextureMapper getTvMapperFromGiMapper(const OdGiMapper& giMapper);

/** \details
Get data from OdTvMapper and write in OdGiMapper
*/
OdGiMapper getGiMapperFromTvMapper(const OdTvTextureMapper& tvMapper);

/** \details
Get data from OdTvMapperDef and write in OdGiMapper

\remarks
OdTvMapperDef is created by operator new, use delete after using mapper
*/
OdGiMapper* getGiMapperPtrFromTvMapperDef(const OdTvMapperDef& tvMapper);

/** \details
Get data from OdTvMapperDef and write in OdGiMapper
*/
OdGiMapper getGiMapperFromTvMapperDef(const OdTvMapperDef& tvMapper);

/** \details
Get data from OdGiMapper and write in OdTvMapper
*/
OdTvMapperDef getTvMapperDefFromGiMapper(const OdGiMapper& giMapper);

/** \details
Get OdGiLightAttenuation from OdTvShadowParameters
*/
OdGiLightAttenuation getOdGiLightAttenuationFromOdTv(const OdTvLightAttenuation& lightAttenuation);

/** \details
Get OdTvLightAttenuation from OdGiLightAttenuation
*/
OdTvLightAttenuation getOdTvLightAttenuationFromOdGi(const OdGiLightAttenuation& giLightAttenuation);

/** \details
Get OdGiShadowParameters from OdTvShadowParameters
*/
OdGiShadowParameters getOdGiShadowParametersFromOdTv( const OdTvShadowParameters& params );

/** \details
Get OdTvShadowParameters from OdGiShadowParameters
*/
OdTvShadowParameters getOdTvShadowParametersFromOdGi( const OdGiShadowParameters& params );

/** \details
Set data to OdGiHatchPatternPtr from OdTvHatchPatternDef.
*/
void setTvHatchPatternDefDataToGiHatchPattern(OdGiHatchPatternPtr& pHatchPattern, const OdTvHatchPatternDef& def);

/** \details
Set data to OdTvHatchPatternDef from OdGiHatchPatternPtr.
*/
void setGiHatchPatternDataToTvHatchPatternDef(OdTvHatchPatternDef& def, const OdGiHatchPatternPtr& pHatchPattern, OdTvResult* rc = NULL);

#include "TD_PackPop.h"

#endif //_ODTV_TRAITSDEFIMPL_H_INCLUDED_

