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

#ifndef __NWTEXTUREMAPPER_INCLUDED__
#define __NWTEXTUREMAPPER_INCLUDED__

#include "NwExport.h"
#include "NwModelUnits.h"
#include <tuple>
#include "Ge/GeMatrix3d.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdNwEmbeddedFile;
typedef std::weak_ptr<OdNwEmbeddedFile> OdNwEmbeddedFileWeakPtr;
class OdNwPropertyImpl;

class NWDBEXPORT OdNwTextureMapper
{
public:
  OdNwTextureMapper();
  ~OdNwTextureMapper() = default;

public:
  const OdString& getPath() const;
  const OdString& getOriginalPath() const;
  inline bool isRealWorldScaleXInit() { return m_pRealWorldScaleXProp; }
  inline bool isRealWorldScaleYInit() { return m_pRealWorldScaleYProp; }
  inline bool isRealWorldOffsetXInit() { return m_pRealWorldOffsetXProp; }
  inline bool isRealWorldOffsetYInit() { return m_pRealWorldOffsetYProp; }
  inline bool isScaleUInit() { return m_pScaleUProp; }
  inline bool isScaleVInit() { return m_pScaleVProp; }
  inline bool isOffsetUInit() { return m_pOffsetUProp; }
  inline bool isOffsetVInit() { return m_pOffsetVProp; }
  inline bool isAngleWInit() { return m_pAngleWProp; }
  double getRealWorldScaleX() const;
  double getRealWorldScaleY() const;
  NwModelUnits::Enum getScaleXUnit() const;
  NwModelUnits::Enum getScaleYUnit() const;
  double getRealWorldOffsetX() const;
  double getRealWorldOffsetY() const;
  NwModelUnits::Enum getOffsetXUnit() const;
  NwModelUnits::Enum getOffsetYUnit() const;
  double getScaleU() const;
  double getScaleV() const;
  double getOffsetU() const;
  double getOffsetV() const;
  OdUInt32 getAngleW() const;
  OdNwEmbeddedFileWeakPtr getEmbeddedTexture() const;
  bool hasTextureBuf() const;
  OdGeMatrix3d getTransform(NwModelUnits::Enum desiredUnits);

public:
  void setPath(const OdString& val);
  void setOriginalPath(const OdString& val);
  void setRealWorldScaleX(OdNwPropertyImpl* pProp);
  void setRealWorldScaleY(OdNwPropertyImpl* pProp);
  void setRealWorldOffsetX(OdNwPropertyImpl* pProp);
  void setRealWorldOffsetY(OdNwPropertyImpl* pProp);
  void setScaleU(OdNwPropertyImpl* pProp);
  void setScaleV(OdNwPropertyImpl* pProp);
  void setOffsetU(OdNwPropertyImpl* pProp);
  void setOffsetV(OdNwPropertyImpl* pProp);
  void setAngleW(OdNwPropertyImpl* pProp);
  void setEmbeddedTexture(OdNwEmbeddedFileWeakPtr pTxtBuf);

  void setDefault();

private:
  //absolute path; is empty if while parsing file by path is not find
  OdString m_Path;
  OdString m_originalPath;
  OdNwPropertyImpl* m_pRealWorldScaleXProp;
  OdNwPropertyImpl* m_pRealWorldScaleYProp;
  OdNwPropertyImpl* m_pRealWorldOffsetXProp;
  OdNwPropertyImpl* m_pRealWorldOffsetYProp;
  OdNwPropertyImpl* m_pScaleUProp;
  OdNwPropertyImpl* m_pScaleVProp;
  OdNwPropertyImpl* m_pOffsetUProp;
  OdNwPropertyImpl* m_pOffsetVProp;
  OdNwPropertyImpl* m_pAngleWProp;
  OdNwEmbeddedFileWeakPtr m_pEmbeddedTexture;
  //VAS: tuple with texture mapper transform:
  //0 - true if transform already initialize
  //1 - units for which transform now initialize
  //2 - GeMatrix value with mapping transform, where [0][0] and [1][1] - scales, and [0][3] and [1][3] - offsets. other elements is zero
  std::tuple<bool, NwModelUnits::Enum, OdGeMatrix3d> m_transform;
};

#endif //__NWTEXTUREMAPPER_INCLUDED__
