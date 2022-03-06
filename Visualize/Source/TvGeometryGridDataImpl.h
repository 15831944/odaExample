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


#ifndef _ODTV_ENTITYGEOMETRYGRIDDATA_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRYGRIDDATA_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGeometryDataImpl.h"
#include "TvGeometryGridData.h"

#include "GiCommonDraw.h"

/** \details
This class implements the background grid geometry data
*/
class OdTvGridDataImpl : public OdTvGeometryDataImpl
{
public:
  OdTvGridDataImpl(): m_minCellAreaRate(1.), m_crossSize(2), m_style(OdTvGridData::kLines), m_bSubGridEnabled(false), m_xDivide(1), m_yDivide(1),
                      m_firstPoint(0.,0.,0.), m_secondPoint(0.,0.,0.), m_firstCount(0), m_secondCount(0), m_type(OdTvGridData::kQuadratic)
                      , m_bIsCalibrated(false) {};
  OdTvGridDataImpl(const OdTvPoint& origin, const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, OdInt32 firstCount, OdInt32 secondCount, const OdTvGridData::Type type);
  virtual ~OdTvGridDataImpl() {};

  // set methods
  OdTvResult set(const OdTvPoint& origin, const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, OdInt32 firstCount, OdInt32 secondCount, const OdTvGridData::Type type);
  OdTvResult setOrigin(const OdTvPoint& origin);
  OdTvResult setFirstPoint(const OdTvPoint& firstPoint);
  OdTvResult setSecondPoint(const OdTvPoint& secondPoint);
  OdTvResult setFirstCount(OdInt32 firstCount);
  OdTvResult setSecondCount(OdInt32 secondCount);
  OdTvResult setType(const OdTvGridData::Type type);
  OdTvResult setStyle(const OdTvGridData::Style style);
  OdTvResult setCrossesSize(OdInt8 crossSize);
  OdTvResult setSubGrid(bool isEnable, const OdTvColorDef& subGridColor, OdInt32 xDivide, OdInt32 yDivide);
  OdTvResult setMinDrawCellArea(double cellAreaRate);

  // get methods
  OdTvResult get(OdTvPoint& origin, OdTvPoint& firstPoint, OdTvPoint& secondPoint, OdInt32& firstCount, OdInt32& secondCount, OdTvGridData::Type& type) const;
  OdTvPoint getOrigin(OdTvResult* rc = NULL) const;
  OdTvPoint getFirstPoint(OdTvResult* rc = NULL) const;
  OdTvPoint getSecondPoint(OdTvResult* rc = NULL) const;
  OdInt32 getFirstCount(OdTvResult* rc = NULL) const;
  OdInt32 getSecondCount(OdTvResult* rc = NULL) const;
  OdTvGridData::Type getType(OdTvResult* rc = NULL) const;
  OdTvGridData::Style getStyle(OdTvResult* rc = NULL) const;
  OdInt8 getCrossesSize(OdTvResult* rc = NULL) const;
  OdTvResult getSubGridParams(bool& isEnable, OdTvColorDef& subGridColor, OdInt32& xDivide, OdInt32& yDivide) const;
  double getMinDrawCellArea(OdTvResult* rc = NULL) const;;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                    entityGeometryDataType() const { return Grid; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawView(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kNone; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual void                              setSelectability(const OdTvSelectabilityDef& selectability);
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

private:
  void getMinAndMaxCornersOfScreen(const OdGiViewportDraw* pViewportDraw, double& xMin, double& xMax, double& yMin, double& yMax) const;

  void drawFinLines(OdGiWorldDraw* pWorldDraw) const;
  void drawInfLines(OdGiViewportDraw* pViewportDraw, double xMin, double xMax, double yMin, double yMax) const;

  void drawFinCrosses(OdGiWorldDraw* pWorldDraw) const;
  void drawInfCrosses(OdGiViewportDraw* pViewportDraw, double xMin, double xMax, double yMin, double yMax) const;

  void drawFinCircRadialGrid(OdGiWorldDraw* pWorldDraw) const;
  void drawInfCircRadialGrid(OdGiViewportDraw* pViewportDraw, double xMin, double xMax, double yMin, double yMax) const;

  void drawFinCrossRadialGrid(OdGiWorldDraw* pWorldDraw) const;
  void drawInfCrossRadialGrid(OdGiViewportDraw* pViewportDraw, double xMin, double xMax, double yMin, double yMax) const;

  void getDivide(OdInt32& xDivide, OdInt32& yDivide) const;
  bool checkInfParams() const;
  void drawLinesFromArr(OdGiWorldDraw* pWorldDraw, const OdTvPointArray pntArr) const;
  void drawLinesFromArr(OdGiViewportDraw* pViewportDraw, const OdTvPointArray pntArr) const;
private:
  OdTvPoint m_origin;
  OdTvPoint m_firstPoint;
  OdTvPoint m_secondPoint;
  OdInt32 m_firstCount;
  OdInt32 m_secondCount;
  OdTvGridData::Type m_type;
  OdTvGridData::Style m_style;
  OdInt8 m_crossSize;

  bool m_bSubGridEnabled;
  OdTvColorDef m_subGridColor;
  OdInt32 m_xDivide;
  OdInt32 m_yDivide;

  double m_minCellAreaRate;

  bool m_bIsCalibrated;
};

typedef OdTvSmartPtrInternal<OdTvGridDataImpl> OdTvGridDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGridData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvGridDataWrapper : public OdTvGridData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvGridData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Sets the grid parameters
  */
  virtual OdTvResult set(const OdTvPoint& origin, const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, OdInt32 firstCount, OdInt32 secondCount, const Type type);

  /** \details
  Returns the grid parameters
  */
  virtual OdTvResult get(OdTvPoint& origin, OdTvPoint& firstPoint, OdTvPoint& secondPoint, OdInt32& firstCount, OdInt32& secondCount, Type& type) const;

  /** \details
  Sets the origin point
  */
  virtual OdTvResult setOrigin(const OdTvPoint& origin);

  /** \details
  Returns the origin point
  */
  virtual OdTvPoint getOrigin(OdTvResult* rc = NULL) const;

  /** \details
  Sets the first point
  */
  virtual OdTvResult setFirstPoint(const OdTvPoint& firstPoint);

  /** \details
  Returns the first point
  */
  virtual OdTvPoint getFirstPoint(OdTvResult* rc = NULL) const;

  /** \details
  Sets the second point
  */
  virtual OdTvResult setSecondPoint(const OdTvPoint& secondPoint);

  /** \details
  Returns the second point
  */
  virtual OdTvPoint getSecondPoint(OdTvResult* rc = NULL) const;

  /** \details
  Sets the count of units along first axis
  */
  virtual OdTvResult setFirstCount(OdInt32 firstCount);

  /** \details
  Returns the count of units along first axis
  */
  virtual OdInt32 getFirstCount(OdTvResult* rc = NULL) const;

  /** \details
  Sets the count of units along second axis
  */
  virtual OdTvResult setSecondCount(OdInt32 secondCount);

  /** \details
  Returns the count of units along second axis
  */
  virtual OdInt32 getSecondCount(OdTvResult* rc = NULL) const;

  /** \details
  Sets the type of grid
  */
  virtual OdTvResult setType(const Type type);

  /** \details
  Returns the type of grid
  */
  virtual Type getType(OdTvResult* rc = NULL) const;

  /** \details
  Sets the style of Grid
  */
  virtual OdTvResult setStyle(const Style style);

  /** \details
  Returns the style of Grid
  */
  virtual Style getStyle(OdTvResult* rc = NULL) const;

  /** \details
  Sets the cross size
  */
  virtual OdTvResult setCrossesSize(OdInt8 size);

  /** \details
  Returns the size of cross
  */
  virtual OdInt8 getCrossesSize(OdTvResult* rc = NULL) const;

  /** \details
  Sets the minor grid
  */
  virtual OdTvResult setMinorGridParams(bool isEnabled, const OdTvColorDef& minorColor, OdInt32 xDivide = 2, OdInt32 yDivide = 2);

  /** \details
  Returns the minor grid parameters
  */
  virtual OdTvResult getMinorGridParams(bool& isEnable, OdTvColorDef& minorColor, OdInt32& xDivide, OdInt32& yDivide) const;

  /** \details
  Sets the minimal area of the grid cell when it is still drawn (in thousandths of a percent)
  */
  virtual OdTvResult setMinDrawCellArea(double cellAreaRate);

  /** \details
  Returns the minimal area of the grid cell when it is still drawn (in thousandths of a percent)
  */
  virtual double getMinDrawCellArea(OdTvResult* rc = NULL) const;

};

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYGEOMETRYGRIDDATA_H_INCLUDED_

