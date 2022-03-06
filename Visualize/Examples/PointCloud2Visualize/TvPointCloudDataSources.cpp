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

#include "OdaCommon.h"
#include "TvPointCloudDataSources.h"
#include <fstream>
#include <limits>
#include <iosfwd>
#include "OdDToStr.h"


OdStringArray split(const OdString& src, const OdString& separator)
{
  OdStringArray res;

  OdString currentStr = src;
  int pos = 0;
  while ((pos = currentStr.find(separator)) != -1)
  {
    OdString subStr = currentStr.left(pos);
    res.push_back(subStr);

    currentStr = currentStr.right(currentStr.getLength() - (pos + 1));
  }
  res.push_back(currentStr);

  return res;
}

double convertStringToDouble(OdString str)
{
  if (str.find(',') >= 0)
    str.replace(',', '.');
  return odStrToD(str);
}

//***************************************************************************//
// 'OdTvSourcePointPtsIterator' methods implementation
//***************************************************************************//

OdTvSourcePointPtsIterator::OdTvSourcePointPtsIterator(TextStreamPtr pPtsFile, std::streampos pointsOffset, OdUInt64 pointsCount, ODCOLORREF defColor)
  : OdTvSourcePointBaseIterator(pPtsFile, pointsOffset, pointsCount, defColor)
{
  start();
}

void OdTvSourcePointPtsIterator::start()
{
  m_pFile->seekg(m_pointsOffset);
  m_pointsRead = 0;
}

bool OdTvSourcePointPtsIterator::done() const
{
  if (m_pointsRead == m_pointsCount)
    return true;

  return false;
}

bool OdTvSourcePointPtsIterator::getPoint(OdSourcePoint& point)
{
  std::string line;
  std::getline(*m_pFile, line);

  ++m_pointsRead;

  if (line.empty())
  {
    point.m_color = ODRGBA(ODGETRED(m_iDefColor), ODGETGREEN(m_iDefColor), ODGETBLUE(m_iDefColor), 255);
    return false;
  }

  OdString odLine(line.c_str());
  OdStringArray params = split(odLine, " ");
  point.m_coord.x = convertStringToDouble(params[0]);
  point.m_coord.y = convertStringToDouble(params[1]);
  point.m_coord.z = convertStringToDouble(params[2]);

  if (params.size() < 7)
  {
    if (params.size() > 3)
    {
      point.m_intensity = odStrToF(params[3]);
    }

    point.m_color = ODRGBA(ODGETRED(m_iDefColor), ODGETGREEN(m_iDefColor), ODGETBLUE(m_iDefColor), 255);
  }
  else
  {
    point.m_intensity = odStrToF(params[3]);

    OdUInt16 r, g, b;
    r = odStrToInt(params[4]);
    g = odStrToInt(params[5]);
    b = odStrToInt(params[6]);

    point.m_color = ODRGBA(r, g, b, 255);
  }

  return true;
}

//***************************************************************************//
// 'OdTvSourcePointXyzIterator' methods implementation
//***************************************************************************//

OdTvSourcePointXyzIterator::OdTvSourcePointXyzIterator(TextStreamPtr pXyzFile, std::streampos pointsOffset, OdUInt64 pointsCount
  , const OdString& separator, const OdArray<int>& xyzIndexes, const OdArray<int>& rgbIndexes, ODCOLORREF defColor)
  : OdTvSourcePointBaseIterator(pXyzFile, pointsOffset, pointsCount, defColor)
  , m_separator(separator), m_xyzIndexes(xyzIndexes), m_rgbIndexes(rgbIndexes)
{
  start();
}

void OdTvSourcePointXyzIterator::start()
{
  m_pFile->seekg(m_pointsOffset);
  m_pointsRead = 0;
}

bool OdTvSourcePointXyzIterator::done() const
{
  if (m_pFile->eof())
    return true;

  return false;
}

bool OdTvSourcePointXyzIterator::getPoint(OdSourcePoint& point)
{
  std::string line;
  std::getline(*m_pFile, line);

  ++m_pointsRead;

  if (line.empty())
  {
    point.m_color = ODRGBA(ODGETRED(m_iDefColor), ODGETGREEN(m_iDefColor), ODGETBLUE(m_iDefColor), 255);
    return false;
  }

  OdString odLine(line.c_str());
  OdStringArray params = split(odLine, m_separator);
  int paramSz = params.size();
  if (paramSz < 3)
    return false;

  if (m_xyzIndexes.size() == 3)
  {
    int xInd = m_xyzIndexes[0], yInd = m_xyzIndexes[1], zInd = m_xyzIndexes[2];
    if (xInd < paramSz) point.m_coord.x = convertStringToDouble(params[xInd]);
    if (yInd < paramSz) point.m_coord.y = convertStringToDouble(params[yInd]);
    if (zInd < paramSz) point.m_coord.z = convertStringToDouble(params[zInd]);
  }
  else
  {
    point.m_coord.x = convertStringToDouble(params[0]);
    point.m_coord.y = convertStringToDouble(params[1]);
    point.m_coord.z = convertStringToDouble(params[2]);
  }

  if (paramSz < 6)
  {
    point.m_color = ODRGBA(ODGETRED(m_iDefColor), ODGETGREEN(m_iDefColor), ODGETBLUE(m_iDefColor), 255);
    return true;
  }

  if (m_rgbIndexes.size() == 3)
  {
    int rInd = m_rgbIndexes[0], gInd = m_rgbIndexes[1], bInd = m_rgbIndexes[2];
    OdUInt16 r = 0, g = 0, b = 0;
    if (rInd < paramSz) r = odStrToInt(params[rInd]);
    if (gInd < paramSz) g = odStrToInt(params[gInd]);
    if (bInd < paramSz) b = odStrToInt(params[bInd]);
    point.m_color = ODRGBA(r, g, b, 255);
  }
  else
  {
    OdUInt16 r = 0, g = 0, b = 0;
    r = odStrToInt(params[paramSz - 3]);
    g = odStrToInt(params[paramSz - 2]);
    b = odStrToInt(params[paramSz - 1]);
    point.m_color = ODRGBA(r, g, b, 255);
  }

  return true;
}

//***************************************************************************//
// 'OdTvPointCloudDataSource' methods implementation
//***************************************************************************//
OdTvPointCloudDataSource::OdTvPointCloudDataSource(const OdString& filePath, Units unit)
  : m_pointsCount(0), m_unit(unit), m_filePath(filePath)
{
  OdString fileExt = m_filePath.right(3);
  fileExt.makeUpper();

  m_bIsXyz = !fileExt.compare(OD_T("XYZ"));

  OdResult res = open(filePath);
  if (res != eOk)
  {
    throw OdError_CantOpenFile(filePath);
  }
}

OdTvPointCloudDataSource::OdTvPointCloudDataSource(const OdString& filePath, const OdString& separator, OdUInt32 skipLines, const OdArray<int>& xyzIndexes
  , const OdArray<int>& rgbIndexes, ODCOLORREF defColor, Units unit /*= kMeter*/) : m_pointsCount(0), m_unit(unit), m_filePath(filePath)
{
  m_separator = separator;
  m_xyzIndexes = xyzIndexes;
  m_rgbIndexes = rgbIndexes;

  m_iDefColor = defColor;

  OdString fileExt = m_filePath.right(3);
  fileExt.makeUpper();

  m_bIsXyz = !fileExt.compare(OD_T("XYZ"));

  OdResult res = open(filePath, skipLines);
  if (res != eOk)
  {
    throw OdError_CantOpenFile(filePath);
  }
}

OdUInt64 OdTvPointCloudDataSource::pointsCount() const
{
  return m_pointsCount;
}

OdPointCloudDataSource::Units OdTvPointCloudDataSource::getUnits() const
{
  return m_unit;
}

OdSourcePointIteratorPtr OdTvPointCloudDataSource::newSourcePointIterator() const
{
  if(!m_bIsXyz)
    return new OdTvSourcePointPtsIterator(m_pPointCloudFile, m_pointsOffset, m_pointsCount, m_iDefColor);
  else
    return new OdTvSourcePointXyzIterator(m_pPointCloudFile, m_pointsOffset, m_pointsCount, m_separator, m_xyzIndexes, m_rgbIndexes, m_iDefColor);
}

OdResult OdTvPointCloudDataSource::open(const OdString& filePath, OdUInt32 skipLine /*= 0*/)
{
  if (!odrxSystemServices()->accessFile(filePath, Oda::kFileRead))
    return eCantOpenFile;

  m_filePath = filePath;
  OdUInt64 iFileSize = getFileSize();

  m_pPointCloudFile = new std::fstream((const char*)filePath);

  if(!m_bIsXyz)
  {
    *m_pPointCloudFile >> m_pointsCount;
    m_pPointCloudFile->ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
  }
  else
  {
    size_t offset = 0;
    while (skipLine)
    {
      std::string line;
      std::getline(*m_pPointCloudFile, line);
      offset += line.size() + 1;
      skipLine--;
    }

    const int linesForRead = 40;
    int readLines = 0;
    size_t charCnt = 0;
    while (readLines < linesForRead)
    {
      if (m_pPointCloudFile->eof())
        break;
      std::string line;
      std::getline(*m_pPointCloudFile, line);
      charCnt += line.size() + 1;
      readLines++;
    }

    // get approximate count of lines
    int averageLineSize = double( charCnt / readLines );
    m_pointsCount = iFileSize / averageLineSize;

    // return iterator to start of file
    m_pPointCloudFile->clear();
    m_pPointCloudFile->seekg(offset, std::ios::beg);
  }

  m_pointsOffset = m_pPointCloudFile->tellg();

  return eOk;
}

OdUInt64 OdTvPointCloudDataSource::getFileSize()
{
  std::fstream stream((const char*)m_filePath);
  std::streampos fileSizeStart = stream.tellg();
  stream.seekg(0, std::ios::end);
  std::streampos fileSizeEnd = stream.tellg();

  return fileSizeEnd - fileSizeStart;
}

