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

#ifndef _ODTV_GRID_H_INCLUDED_
#define _ODTV_GRID_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"


/** \details
  This is an interface class for manipulating Visualize grid geometry data.
  \sa
  <link tv_geometry_grids, Work with Grids>
*/
class ODTV_EXPORT OdTvGridData : public OdTvIObject
{
public:

  /** \details
    Grid types.
  */
  enum Type
  {
    kQuadratic       = 0, // A quadratic grid.
    kRadial          = 1  // A radial grid.
  };

  /** \details
    Grid styles.
  */  
  enum Style
  {
    kLines   = 0,  // A grid with lines.
    kCrosses = 1  // A grid with crosses (currently only points are supported).
  };

  /** \details
    Sets the grid parameters.
    
    \param origin       [in] An origin grid point.
    \param firstPoint   [in] A first point of the grid.
    \param secondPoint  [in] A second point of the grid.
    \param firstCount   [in] A quantity of units after the first grid point along the first axis.
    \param secondCount  [in] A quantity of units after the second grid point along the second axis.
    \param type         [in] A grid type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter values are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdTvPoint& origin, const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, OdInt32 firstCount, OdInt32 secondCount, const Type type) = 0;

  /** \details
    Retrieves current grid parameters.
    
    \param origin       [out] A placeholder for the origin grid point.
    \param firstPoint   [out] A placeholder for the first point of the grid.
    \param secondPoint  [out] A placeholder for the second point of the grid.
    \param firstCount   [out] A placeholder for the quantity of units after the first grid point.
    \param secondCount  [out] A placeholder for the quantity of units after the second grid point.
    \param type         [out] A placeholder for the grid type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter values are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdTvPoint& origin, OdTvPoint& firstPoint, OdTvPoint& secondPoint, OdInt32& firstCount, OdInt32& secondCount, Type& type) const = 0;

  /** \details
    Sets the origin point of the grid.
    
    \param origin [in] An origin grid point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOrigin(const OdTvPoint& origin) = 0;

  /** \details
    Retrieves the origin point of the grid.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvPoint, OdTvPoint> class that represents the current origin point.
    \remarks
    If the rc parameter is not null and the origin point is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPoint getOrigin(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the first point of the grid.
    
    \param firstPoint [in] A first grid point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified first point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFirstPoint(const OdTvPoint& firstPoint) = 0;

  /** \details
    Retrieves the first point of the grid.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvPoint, OdTvPoint> class that represents the current first point.
    \remarks
    If the rc parameter is not null and the first point is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPoint getFirstPoint(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the second point of the grid.
    
    \param secondPoint [in] A second grid point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified second point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSecondPoint(const OdTvPoint& secondPoint) = 0;

  /** \details
    Retrieves the second point of the grid.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvPoint, OdTvPoint> class that represents the current second point.
    \remarks
    If the rc parameter is not null and the second point is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPoint getSecondPoint(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the quantity of grid units along the first axis.
    
    \param firstCount [in] A quantity of grid units.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified units quantity is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFirstCount(OdInt32 firstCount) = 0;

  /** \details
    Retrieves the quantity of grid units along the first axis.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of grid units along the first axis.
    \remarks
    If the rc parameter is not null and the units quantity is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdInt32 getFirstCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the quantity of grid units along the second axis.
    
    \param secondCount [in] A quantity of grid units.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified units quantity is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSecondCount(OdInt32 secondCount) = 0;

  /** \details
    Retrieves the quantity of grid units along the second axis.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of grid units along the second axis.
    \remarks
    If the rc parameter is not null and the units quantity is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdInt32 getSecondCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the grid type.
    
    \param type [in] A new grid type to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified grid type value is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setType(const Type type) = 0;

  /** \details
    Retrieves the current grid type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the grid type.
    \remarks
    If the rc parameter is not null and the grid type is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual Type getType(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the grid style.
    
    \param type [in] A new grid style to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified grid style value is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStyle(const Style type) = 0;

  /** \details
    Retrieves the current grid style.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the grid style.
    \remarks
    If the rc parameter is not null and the grid style is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual Style getStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the size of the grid crosses.
    
    \param size [in] A new cross size in measurement units.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified cross size value is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCrossesSize(OdInt8 size) = 0;

  /** \details
    Retrieves the current cross size of the grid.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current size of the grid crosses in measurement units.
    \remarks
    If the rc parameter is not null and the cross size is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdInt8 getCrossesSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets minor parameters of the grid.
    
    \param isEnable   [in] A flag that determines whether the grid is visible.
    \param minorColor [in] A grid color.
    \param xDivide    [in] A divide value for the X axis.
    \param yDivide    [in] A divide value for the Y axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified minor grid parameters are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMinorGridParams(bool isEnable, const OdTvColorDef& minorColor, OdInt32 xDivide = 2, OdInt32 yDivide = 2) = 0;

  /** \details
    Retrieves minor parameters of the grid.
    
    \param isEnable   [out] A placeholder for the flag that determines whether the grid is visible.
    \param minorColor [out] A placeholder for the grid color.
    \param xDivide    [out] A placeholder for the divide value for the X axis.
    \param yDivide    [out] A placeholder for the divide value for the Y axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the current minor grid parameters are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getMinorGridParams(bool& isEnable, OdTvColorDef& minorColor, OdInt32& xDivide, OdInt32& yDivide) const = 0;

  /** \details
    Sets a minimal draw area for the grid cells. If the cell area is bigger than this value, it is drawn.
    The draw area rate is specified in thousandths of a percent.
    
    \param cellAreaRate [in] A cell draw area rate.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified draw area is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMinDrawCellArea(double cellAreaRate) = 0;

  /** \details
    Retrieves the current minimal draw area of the grid cells. If the cell area is bigger than this value, it is drawn.
    The draw area rate is specified in thousandths of a percent.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current draw area of the grid cells in thousandths of a percent.
    \remarks
    If the rc parameter is not null and the draw area value is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getMinDrawCellArea(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvGridData, OdTvGridData> object.
*/
typedef OdTvSmartPtr<OdTvGridData> OdTvGridDataPtr;

#endif // _ODTV_GRID_H_INCLUDED_
