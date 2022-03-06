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

#ifndef _ODTV_STATISTICSIMPL_H_INCLUDED_
#define _ODTV_STATISTICSIMPL_H_INCLUDED_

#include "TvStatistics.h"

#define ODTV_MATERIAL_ADDITIONAL_SIZE 251
#define ODTV_LAYER_ADDITIONAL_SIZE 204
#define ODTV_VISUALSTYLE_ADDITIONAL_SIZE 307
#define ODTV_HIGHLIGHTSTYLE_ADDITIONAL_SIZE 160
#define ODTV_SOLIDBACKGROUND_ADDITIONAL_SIZE 311
#define ODTV_GRADIENTBACKGROUND_ADDITIONAL_SIZE 343
#define ODTV_IMAGEBACKGROUND_ADDITIONAL_SIZE 351
#define ODTV_LINETYPE_ADDITIONAL_SIZE 352
#define ODTV_TEXTSTYLE_ADDITIONAL_SIZE 208
#define ODTV_RASTERIMAGE_ADDITIONAL_SIZE 369
#define ODTV_GSDEVICE_ADDITIONAL_SIZE 533
#define ODTV_GSVIEW_ADDITIONAL_SIZE 284

#define ODTV_ENHCHUNK_SIZE 48

#define ODTV_ARRAY_ADDITIONAL_SIZE 16

/** \details
Defines the block statistics about the count of objects in this block
*/
class OdTvGeometryStatisticImpl : public OdTvGeometryStatistic
{
public:

  /** \details
  Constructor
  */
  OdTvGeometryStatisticImpl() : OdTvGeometryStatistic() {};

  /** \details
  Increase the counter of the objects for the specified type
  */
  void increaseCount(Types type, OdUInt64 n = 1);

  /** \details
  Returns the data array
  */
  const OdUInt64Array& getCountArray();

  /** \details
  Increase the counter of the objects size
  */
  void increaseObjectsSize(unsigned int uiObjectSize);

  /** \details
  Copy the data
  */
  static void copy(OdTvGeometryStatistic* pStaticstic, const OdUInt64Array& counts, const OdUInt64 objectsSize);
};

/** \details
An interface class that provides the statistics for database objects counting.
*/
class OdTvDatabaseStatisticImpl : public OdTvDatabaseStatistic
{
public:

  /** \details
  Constructor
  */
  OdTvDatabaseStatisticImpl() : OdTvDatabaseStatistic() {};

  /** \details
  Increase the counter of the objects for the specified type
  */
  void increaseCount(Types type, OdUInt64 n = 1);

  /** \details
  Returns the data array
  */
  const OdUInt64Array& getCountArray();

  /** \details
  Increase the counter of the objects size
  */
  void increaseObjectsSize(unsigned int uiObjectSize);

  /** \details
  Increase the counter of the database initial size
  */
   void increaseInitialSize(unsigned int uiInitialSize);

   /** \details
  Increase the counter of the attributes size
   */
  void increaseAttributesSize(unsigned int uiAttributesSize);

  /** \details
  Copy the data
  */
  static void copy(OdTvDatabaseStatistic* pStaticstic, const OdUInt64Array& counts, const OdUInt64 objectsSize, const OdUInt64 initialSize, const OdUInt64 attributesSize);
};

#endif //_ODTV_STATISTICSIMPL_H_INCLUDED_
