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
#ifndef TVIDATABASEINFO_H
#define TVIDATABASEINFO_H

#include "OdaCommon.h"
#include "TvVisualizeFiler.h"

/** \details
class for storing the information about the opened file
*/
class TviDatabaseInfo : public OdTvFilerTimeProfiling
{
public:

  enum Type
  {
    kFromFile = 0,
    kImport = 1
  };

  TviDatabaseInfo() : m_iLoadTime(0), m_iVectorizingTime(0), m_iTvCreationTime(0), m_iFirstUpdateTime(0), m_type(kFromFile) {}
  ~TviDatabaseInfo() {}

  // returns the time of file loading (in milliseconds)
  virtual OdInt64 getImportTime() const { return m_iLoadTime; }

  // returns the total vectorizing time (in milliseconds)
  virtual OdInt64 getVectorizingTime() const { return m_iVectorizingTime; }

  // returns the total tv calling time (in milliseconds)
  virtual OdInt64 getTvTime() const { return m_iTvCreationTime; }

  // return the time of calling (in milliseconds)
  OdInt64 getFirstUpdateTime() const { return m_iFirstUpdateTime; }

  OdInt64 getTotalTime() const { return m_iLoadTime + m_iVectorizingTime + m_iFirstUpdateTime; }

  // set the type
  Type getType() const { return m_type; }

  //set file path
  OdString getFilePath() const { return m_strPath; }

  // set the time of file loading (in milliseconds)
  virtual void setImportTime(OdInt64 time) { m_iLoadTime = time; }

  // set the time of vectorizing (in milliseconds)
  virtual void setVectorizingTime(OdInt64 time) { m_iVectorizingTime = time; }

  // set the time of calling (in milliseconds)
  virtual void setTvTime(OdInt64 time) { m_iTvCreationTime = time; }

  // set the time of calling (in milliseconds)
  void setFirstUpdateTime(OdInt64 time) { m_iFirstUpdateTime = time; }

  // set the type
  void setType(Type type) { m_type = type; }

  //set file path
  void setFilePath(const OdString& path) { m_strPath = path; }
private:

  OdInt64   m_iLoadTime;
  OdInt64   m_iVectorizingTime;
  OdInt64   m_iTvCreationTime;
  OdInt64   m_iFirstUpdateTime;
  Type      m_type;
  OdString  m_strPath;
};


#endif // TVIDATABASEINFO_H
