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

#ifndef _OD_ODPOINTCLOUDPTSDATASOURCE_H_
#define _OD_ODPOINTCLOUDPTSDATASOURCE_H_

#include "TD_PackPush.h"
#include "RcsFileServices/RxRcsFileServices.h"

#define STL_USING_STREAM
#include "OdaSTL.h"

#include <fstream>

typedef OdSharedPtr<std::fstream> TextStreamPtr;

class OdTvSourcePointBaseIterator : public OdSourcePointIterator
{
public:
  OdTvSourcePointBaseIterator(TextStreamPtr pFile, std::streampos pointsOffset, OdUInt64 pointsCount, ODCOLORREF defColor)
    : m_pFile(pFile), m_pointsOffset(pointsOffset), m_pointsCount(pointsCount), m_iDefColor(defColor)
  {}

  virtual ~OdTvSourcePointBaseIterator() {}

  virtual void start() = 0;
  virtual bool done() const = 0;

  virtual bool getPoint(OdSourcePoint& point) = 0;

 protected:
  TextStreamPtr  m_pFile;
  OdUInt64       m_pointsCount;
  std::streampos m_pointsOffset;

  OdUInt64       m_pointsRead;

  ODCOLORREF     m_iDefColor;
};

class OdTvSourcePointPtsIterator : public OdTvSourcePointBaseIterator
{
public:
  OdTvSourcePointPtsIterator(TextStreamPtr pPtsFile, std::streampos pointsOffset, OdUInt64 pointsCount, ODCOLORREF defColor);

  virtual void start();
  virtual bool done() const;

  virtual bool getPoint(OdSourcePoint& point);
};

class OdTvSourcePointXyzIterator : public OdTvSourcePointBaseIterator
{
public:
  OdTvSourcePointXyzIterator(TextStreamPtr pXyzFile, std::streampos pointsOffset, OdUInt64 pointsCount, const OdString& separator
    , const OdArray<int>& xyzIndexes, const OdArray<int>& rgbIndexes, ODCOLORREF defColor);

  virtual void start();
  virtual bool done() const;

  virtual bool getPoint(OdSourcePoint& point);

private:
  OdString m_separator;
  OdArray<int> m_xyzIndexes;
  OdArray<int> m_rgbIndexes;
};

class OdTvPointCloudDataSource : public OdPointCloudDataSource
{
public:

  OdTvPointCloudDataSource(const OdString& filePath, Units unit = kMeter);

  OdTvPointCloudDataSource(const OdString& filePath, const OdString& separator, OdUInt32 skipLines, const OdArray<int>& xyzIndexes
    , const OdArray<int>& rgbIndexes, ODCOLORREF defColor, Units unit = kMeter);

  virtual OdUInt64 pointsCount() const;

  virtual Units getUnits() const;

  virtual OdSourcePointIteratorPtr newSourcePointIterator() const;

private:
  OdResult open(const OdString& filePath, OdUInt32 skipLine = 0);
  OdUInt64 getFileSize();

  OdString       m_filePath;
  TextStreamPtr  m_pPointCloudFile;

  OdUInt64       m_pointsCount;
  std::streampos m_pointsOffset;

  Units          m_unit;

  bool m_bIsXyz;
  OdString m_separator;
  OdArray<int> m_xyzIndexes;
  OdArray<int> m_rgbIndexes;

  ODCOLORREF m_iDefColor;
};

#include "TD_PackPop.h"

#endif //#ifndef _OD_ODPOINTCLOUDPTSDATASOURCE_H_
