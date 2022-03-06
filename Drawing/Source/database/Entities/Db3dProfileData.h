/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2020, Open Design Alliance (the "Alliance"). 
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
//   Open Design Alliance Copyright (C) 2002-2020 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef DB3DPROFILEDATA_H__
#define DB3DPROFILEDATA_H__

#include "RxObject.h"
#include "OdAutoPtr.h"

#include "DbGeomRef.h"
#include "DbCompoundObjectId.h"
#include "Db3dProfile.h"

#include "TD_PackPush.h"

class OdDbEntity;
class OdDb3dProfile;

enum eDb3dProfileEntType
{
  eUnknownType = 0,
  eDefaultType = 1,
  eEdgeType = 2,
  ePolylineEdgeType = 3,
  eVertexType = 4,
  eFaceType = 5,
};

class OdDb3dProfileData : public OdRxObject
{
public:

  ODRX_DECLARE_MEMBERS(OdDb3dProfileData);
  ODRX_HEAP_OPERATORS();

  OdDb3dProfileData();

  virtual ~OdDb3dProfileData();

  OdDbEntity* entity();

  void setEntity(OdDbEntity* pEnt, bool isOwnerOfEntity);

  OdDbObjectId originalEntityId();

  void setOriginalEntityId(OdDbObjectId objectId);

  void resetEntity();

  void set(OdDbEntity* pEnt, OdDbFullSubentPath path, bool isOwnerOfEntity);

  OdDbFullSubentPathArray getSubentPathArray();

  OdDbFullSubentPathArray setSubentPathArray(OdDbFullSubentPathArray& subEnts);

  OdDbFullSubentPathArray getFaceSubentPathArray();

  OdDbFullSubentPathArray setFaceSubentPathArray(OdDbFullSubentPathArray& subEnts);

  OdResult getVertexRef(OdDbVertexRef& pVertexRef) const;

  OdResult getPathRef(OdDbPathRef* pVertexRef);

  eDb3dProfileEntType profileType() const;

  bool isClosed(const OdGeTol& tol = OdGeContext::gTol);

  bool isSubent() const;

  bool isFace() const;

  bool isEdge() const;

  bool isPolylineEdge() const;

  bool isPlanar();

  bool isVertex();

  void resetProfileType();

  void nullify();

  void copyFrom(const OdRxObject*);

  OdResult convertProfile(bool explodeMultiFaceRegions, bool convertSurfaceToEdges,
    bool nonPlanarOnly, bool outerLoopOnly,
    OdArray<OdDb3dProfile*>& convertedProfileArr) const;

  OdResult convertToRegion();

  OdResult convertProfileFace(bool nonPlanarOnly, bool outerLoopOnly, bool bMergeEnts, OdArray<OdDb3dProfileData*> aConvertedProfileArr);

  static OdResult join(OdDb3dProfileData* pThisProfile, OdDb3dProfileData* pProfile, bool bMergeEdges, bool bMergeCurves, bool bNeedToReverseOrSwap, bool bPrepareForMerging);

  static OdResult mergeProfileData(OdArray<OdDb3dProfileData*> aProfileData, bool bMergeEdges, bool bMergeCurves, OdArray<OdDb3dProfileData*>& aProfileDataResult);

  static OdDb3dProfile* getProfileData(const OdArray<OdDbPathRef>& profileData);

  static OdDbCurvePtr joinCurves(OdDbCurve* pCurve1, OdDbCurve* pCurve2, bool bSwapJoin, bool isReverseSecondCurve);

  static OdGeCurve3d* convertToGeCurve(const OdDbCurve* pCurve);

  OdDb3dProfileData& operator =(const OdDb3dProfileData& src);
private:
  int planarity();
  OdDb::Planarity planarity(OdGePlane& plane);
  void listInit();

public:
  OdArray<OdDb3dProfileDataPtr> m_aJoinedProfileDatas;
  OdDbFullSubentPathArray m_aSubEnts;
  OdDbFullSubentPathArray m_aFaceSubEnts;
  OdDbEntityPtr m_pEntity;
  OdDbObjectId m_oCreatedEntId;
  OdInt8 m_bIsClosed;
  OdInt8 m_bIsPlanar;
  eDb3dProfileEntType m_eProfileType;
  bool m_bIsOwnerOfEntity;
};

typedef OdSmartPtr<OdDb3dProfileData> OdDb3dProfileDataPtr;

#include "TD_PackPop.h"
#endif // DB3DPROFILEDATA_H__

