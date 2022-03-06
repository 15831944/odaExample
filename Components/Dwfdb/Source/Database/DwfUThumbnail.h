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

#ifndef _DWFUTHUMBNAIL_INCLUDED_
#define _DWFUTHUMBNAIL_INCLUDED_

#include "DwfUGeomBase.h"
#include "Gi/GiRasterImage.h"

namespace DWFCore
{
  class DWFString;
  class DWFInputStream;
}

class DwfUThumbnail : public DwfUGeomBase
{
  OdBinaryData m_thumbnail; 
  OdGiRasterImagePtr m_pThumbnail;
protected:
  virtual DWFCore::DWFString requestedResourceType();

  virtual OdResult proceed6stream(DWFCore::DWFInputStream& stream);
  virtual OdResult proceedXstream(DWFCore::DWFInputStream& stream, WT_File& wtFile);
  virtual OdResult proceed55stream(DWFCore::DWFInputStream& stream);

public:
  DwfUThumbnail(OdString password, OdString layoutName);

  OdGiRasterImagePtr getThumbnail();
  bool getThumbnail(OdBinaryData& data);

  virtual ~DwfUThumbnail() {}
};

#endif // _DWFUTHUMBNAIL_INCLUDED_
