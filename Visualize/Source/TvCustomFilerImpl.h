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

#ifndef _ODTV_CUSTOMFILERIMPL_H_INCLUDED_
#define _ODTV_CUSTOMFILERIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdPlatformStreamer.h"
#include "DbFiler.h"

//Visualize SDK
#include "TvDatabase.h"
#include "TvFactoryImpl.h"

/** \details
This class implements I/O of the some type of the data to the VSF file as bytes
*/
bool useLowerPrecision(OdTvVSFExportOptions& options);

/** \details
This structure implements the normal vector with float components
*/
struct OdFloatNormal
{
  OdFloatNormal();
  OdFloatNormal(float x, float y, float z);
  OdFloatNormal(const OdGeVector3d& other);
  OdFloatNormal& operator=(const OdFloatNormal& other);
  OdGeVector3d toVector();

  float x;
  float y;
  float z;
};

/** \details
This class implements I/O of the some type of the data to the VSF file as bytes
*/
class OdTvBytesFiler
{
public:
  /** \details
  Writes the specified 3D point value as float to the Filer object.
  \param pFiler [in]  Filer object
  \param pt     [in]  Point for write
  */
  static void   wrPointAsFloats(OdTvcFiler* pFiler, const OdTvPoint& pt);

  /** \details
  Writes the specified 3D point value as float to the Filer object.
  \param pFiler [in]  Filer object
  \param pt     [in]  Point for write
  */
  static void   wrPointAsFloats(OdTvDbDwgFiler* pFiler, const OdTvPoint& pt);

  /** \details
  Read the 3D point value (which was written as floats) from the Filer object.
  \param pFiler [in]  Filer object
  */
  static OdTvPoint rdPointFromFloats(OdTvcFiler* pFiler);

  /** \details
Read the 3D point value (which was written as floats) from the Filer object.
\param pFiler [in]  Filer object
*/
  static OdTvPoint rdPointFromFloats(OdTvDbDwgFiler* pFiler);

};

/** \details
This class implements I/O of the some type of the data to the VSF file with compression
*/
class OdTvCompressionFiler
{
public:
  OdTvCompressionFiler(OdTvDbDwgFiler* pDwgFiler, const OdTvVSFExportOptions& options);

  //writePointArray assumes size already wrote
  void writePoints(const OdTvPoint* data, OdUInt32 size);
  
  //readPointArray assumes size already wrote and array allocated
  void readPoints(OdTvPoint* data, OdUInt32 size);

  void writeDoubleArray(const double* data, OdUInt32 size);
  void readDoubleArray(double* data, OdUInt32 size);

  void writeNormals(const OdGeVector3dArray& data);
  void readNormals(OdGeVector3dArray& data);

private:
  bool checkPointsCompressionSupport();
  bool checkArraySize(OdUInt32 size);

private:
  OdTvVSFExportOptions m_options;
  OdTvDbDwgFiler* m_pFiler;
  OdTvcFiler*   m_pTvcFiler;

};


#include "TD_PackPop.h"

#endif //_ODTV_CUSTOMFILERIMPL_H_INCLUDED_

