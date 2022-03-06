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

#ifndef __NWCOMPONENTIMPL_INCLUDED__
#define __NWCOMPONENTIMPL_INCLUDED__

#include "NwComponent.h"
#include "OdArray.h"
#include "NwObjectImpl.h"
#include "NwGeometryMesh.h"

class OdNwGraphicAppearance;
typedef OdSmartPtr<OdNwGraphicAppearance> OdNwGraphicAppearancePtr;

class OdNwComponentImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwComponent)
public:
  OdNwComponentImpl();
  virtual ~OdNwComponentImpl();
  ODRX_DECLARE_MEMBERS(OdNwComponentImpl);

  static OdNwComponentImpl* getImpl(const OdNwComponent* pNwComponent);
  static OdNwComponentImpl* getImpl(const OdRxObject* pRxComponent);

public:
  //public implementation's getting methods
  OdResult getFragments(OdNwObjectIdArray& aFragments) const;
  bool isHidden() const;
  OdUInt8 getPrimitives() const;
  OdNwObjectId getMaterialId() const;
  OdNwObjectId getOriginalMaterialId() const;
  OdResult getTransparency(float& tr) const;
  OdResult getLowBound(OdGePoint3d& lb) const;
  OdResult getHighBound(OdGePoint3d& hb) const;
  OdUInt32 getFragmentCount() const;
  OdNwObjectId findFragmentGeometry(OdUInt32 fragmentIdx) const;

public:
  //public implementation's setting methods
  OdNwObjectId addFragmentGeometry(const OdNwObjectId& geometryId, OdResult* pResult);
  OdNwObjectId addFragmentGeometryCircle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal, OdResult* pResult);
  OdNwObjectId addFragmentGeometryPolyline(const OdGePoint3dArray& points, OdResult* pResult);
  OdNwObjectId addFragmentGeometryShell(const OdGePoint3dArray& pVertexList, const OdGeVector3dArray& pNormalList, const OdArray<OdNwTriangleIndexes>& pFaceList, OdResult* pResult);
  OdNwObjectId addFragmentGeometrySnapPoint(const OdGePoint3d& point, OdResult* pResult);
  OdResult addFragment(const OdNwObjectId& fragId);
  OdResult setMaterial(const OdNwObjectId& materialId);
  OdResult setAmbient(const OdNwColor& clr);
  OdResult setDiffuse(const OdNwColor& clr);
  OdResult setSpecular(const OdNwColor& clr);
  OdResult setEmissive(const OdNwColor& clr);
  OdResult setShininess(float val);
  OdResult setTransparency(float val);
  OdResult setInternalTexture(const OdString& txtPath, OdGiRasterImagePtr pTxtImage, const OdGeMatrix3d* pMappingTransform);
  OdResult setExternalTexture(const OdString& txtPath, const OdGeMatrix3d* pMappingTransform);
protected:
  template<typename T, typename graphMatSetter, typename nwMatSetter>
  OdResult setMaterailValue(T param, graphMatSetter pGrMatSetter, nwMatSetter pNwMatSetter);
  template<typename appearanceSetter, class ...Args>
  OdResult setTextureData(appearanceSetter pGrAppSetter, Args ...args);
  OdResult lockMaterials(OdNwObjectPtr& pOriginalMat, OdNwObjectPtr& pMat);

public:
  const OdNwObjectIdArray& getFragments() const;
  OdNwGraphicAppearancePtr getGraphicAppearance() const;

private:
  OdNwObjectIdArray m_aFragments;
  mutable OdNwObjectId m_materialId;
  mutable OdNwObjectId m_originalMaterialId;
};

typedef OdSmartPtr<OdNwComponentImpl> OdNwComponentImplPtr;

#endif //__NWCOMPONENTIMPL_INCLUDED__
