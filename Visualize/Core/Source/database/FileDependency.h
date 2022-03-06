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

#ifndef _FileDependency_Included
#define _FileDependency_Included

#include "OdString.h"
class OdTvDbObjectImpl;
class OdTvDbDatabase;
class OdTvDbObject;

namespace OdDb
{
  class TOOLKIT_EXPORT TvFileDependency
  {
    bool m_bDependencyCreated;
    OdString m_strFilePath;
    OdString m_strFeature;
  public:
    TvFileDependency(const OdString& feature);
    void setFileName(const OdString&, OdTvDbDatabase*, bool updateDependencies = true);
    operator const OdString() const {return m_strFilePath;}
    void subClose(OdTvDbDatabase*);
    void subErase(bool erasing, OdTvDbDatabase*);
    bool isDependencyCreated() const {return m_bDependencyCreated;}
  };
}
#endif
