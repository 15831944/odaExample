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

#ifndef __NWTEXTUREBUF_H__
#define __NWTEXTUREBUF_H__

#include "OdBinaryData.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdGiRasterImage;
typedef OdSmartPtr<OdGiRasterImage> OdGiRasterImagePtr;

class OdNwEmbeddedFile
{
public:
  OdNwEmbeddedFile(const OdString& appName, const OdString& type, const OdBinaryData& data);
  ~OdNwEmbeddedFile() = default;
  OdNwEmbeddedFile(const OdNwEmbeddedFile& other);
  OdNwEmbeddedFile& operator=(const OdNwEmbeddedFile& other);

public:
  inline const OdBinaryData& getBinData() const { return m_aBinData; }
  inline const OdString& getAppName() const { return m_appName; }
  inline const OdString& getType() const { return m_type; }

  //if m_aBinData contain buffer of image - then it's possible to get GiRasterImage with this buffer
  OdGiRasterImagePtr getRasterImage() const;

private:
  OdString m_appName;
  OdString m_type;
  OdBinaryData m_aBinData;
};

typedef std::shared_ptr<OdNwEmbeddedFile> OdNwEmbeddedFilePtr;

#endif //__NWTEXTUREBUF_H__
