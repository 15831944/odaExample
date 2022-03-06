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

#ifndef _OD_DB_SHHISTORY_IMPL_
#define _OD_DB_SHHISTORY_IMPL_

#include "DbSystemInternals.h"
#include "ShHistory/DbShHistory.h"
#include "ShHistory/DbShHistoryNode.h"
#include "ShHistory/DbShPrimitive.h"
#include "DbObjectImpl.h"
#include "DbEvalGraph.h"


class OdDbShHistoryImpl : public OdDbObjectImpl
{
  static OdDbShHistoryImpl* getImpl(const OdDbShHistory *pObj)
  { return (OdDbShHistoryImpl*)OdDbSystemInternals::getImpl(pObj);}

  OdDbObjectId m_IdEvalGraph;
  OdInt32 m_nVersionMajor;
  OdInt32 m_nVersionMinor;
  OdDbEvalNodeId m_iNumNodes; //don't rely on it (SRC-1150, SRC-1166)! removeNode/addNode may mess it up
  bool    m_bRecHistory;
  bool    m_bShowHistory;
  OdDbShHistoryNodePtrArray arrHistNodes;//We have to keep it for NONDBRO historyNodes.

  friend class OdDbShHistory;

  inline OdResult addNode(OdDbShHistoryNodePtr pNode);
  inline OdResult addPrimitiveNode(OdDbShPrimitivePtr pNode);
  inline void     setDefaultParams(OdDbDatabase* pDatabase, OdDbShHistoryNode* pNode);
public:
  OdDbShHistoryImpl() : m_nVersionMajor(OdDb::kDHL_CURRENT)
                      , m_nVersionMinor(OdDb::kMRelease1)
                      , m_iNumNodes(0)
                      , m_bRecHistory(false)
                      , m_bShowHistory(false){}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void clearHistory();
  virtual OdResult purgeGraph();
  virtual OdResult getGraph(OdDbObjectId &);
  
  virtual OdResult createBox(double dXLen, double dYLen, double dZLen/*, BODY*&*/);
  //virtual OdResult createBrep(OdCmColor const &, OdDbObjectId,void *)
  virtual OdResult createFrustum(double dHeight, double dXRadius, double dYRadius, double dTopXRadius/*, BODY*&*/);
  virtual OdResult createSphere(double dRadius/*, BODY * &*/);
  virtual OdResult createTorus(double dMajorRadius, double dMinorRadius/*, BODY * &*/);
  virtual OdResult createWedge(double dXLen, double dYLen, double dZLen/*, BODY * &*/);
  virtual OdResult createPyramid(double dHeight, int iSides, double dRadius, double dTopRadius/*, BODY * &*/);

  virtual OdResult setSubentColor( const OdDbSubentId &subentId, const OdCmColor &color );
  virtual OdResult setSubentMaterial( const OdDbSubentId &subentId, OdDbObjectId matId );

  virtual OdResult createLoftedSolid(OdDbEntityPtrArray& crossSections, OdDbEntityPtrArray& guideCurves, OdDbEntity* pPathCurve, OdDbLoftOptions& loftOpt/*, BODY*&*/);
  virtual OdResult createRevolvedSolid(OdDbEntity* pRevolveCurve, const OdGePoint3d& axisPoint, const OdGeVector3d& axisDir, double dAngleOfRevolution, double dStartAngle, OdDbRevolveOptions& revolveOpt/*, BODY*&*/);
  virtual OdResult createSweptSolid(OdDbEntity* pSweepCurve, OdDbEntity* pPathCurve, const OdGeVector3d& directioVector, OdDbSweepOptions& sweepOpt/*, BODY * &*/);

  virtual OdResult booleanOper( OdDbShHistory* pSecondEll, OdDb::BoolOperType operation);
  //virtual OdResult booleanOper(ENTITY *, ENTITY * , BoolOperType, OdDbShHistory *, BODY * &)

  virtual OdResult postInDatabase(OdDbObjectId& objId, OdDbDatabase* pDatabase);
  virtual OdResult subTransformBy( const OdGeMatrix3d& xform );
  virtual OdResult filletEdges(const OdArray<OdDbSubentId *> &edgeSubentIds, const OdGeDoubleArray& radius, const OdGeDoubleArray& startSetback, const OdGeDoubleArray& endSetback);
  virtual OdResult chamferEdges(const OdArray<OdDbSubentId*>& edgeSubentIds, const OdDbSubentId & baseFaceSubentId, double baseDist, double otherDist);
  //static bool isComplexIndex(class OdDbSubentId)
  //OdResult addPostrioMappers(BODY *, BodySubentIds *)
  //static void addPrimitiveIndex(OdDbSubentId &,int)
  
  //virtual OdResult chamferEdges(OdDbShSubents &, OdDbShSubents &, double, double, BODY * &, OdDbObjectId &)
  //void cleanupSubentDisplayHistory()
  //void clonePersSubentNamingData(DbAssocPersSubentManagerCloner *)
  //void collectPersSubentNamingData(OdIntArray &, OdIntArray &)
  //virtual OdResult convertToBrepAtSubentPaths(OdDbFullSubentPathArray& paths, BODY*& pBody);


  //virtual OdResult createLoftedSolid(OdDbLoftProfileDataArray &, OdDbLoftProfileDataArray &, OdDbLoftProfileData *, OdDbLoftOptions &, BODY*&)
  //virtual OdResult deleteAtLeafNode(OdDbFullSubentPathArray const &, BODY * &)
  //virtual OdResult deleteSubentPaths(OdGsMarkerArray const &, BODY * &)
  //virtual OdResult filletEdges(OdDbShSubents &, OdGeDoubleArray const &, OdGeDoubleArray const &, OdGeDoubleArray const &, BODY * &, OdDbObjectId &)
  //void getAllPrimitiveIndices(OdGsMarkerArray &)
  //unsigned long getFirstSourceId()  

  //virtual OdResult getGripEntityUCS(void const *, OdGeVector3d &, OdGePoint3d &, OdGeVector3d &)
  //virtual OdResult getGripPoints(OdDbGripDataPtrArray &, double, int, OdGeVector3d const &, int)
  //virtual OdResult getGripPointsAtSubentPath(OdGsMarker, OdDbGripDataPtrArray &, double, int, OdGeVector3d const &, int)
  //virtual OdResult getGsMarkersAtSubentPath(OdDbFullSubentPath const &, OdGsMarkerArray &, BODY *)
  //virtual OdResult getGsMarkersFromStepId(OdDbFullSubentPath const &, OdGsMarkerArray &, BODY *)
  //virtual OdResult getNodeAtSubentPath(OdDbSubentId const & OpenMode, OdDbShHistoryNode * &)
  //unsigned long AcDbShHistory::getSinkId(void)
  //virtual OdResult getSubentClassId(OdGsMarker, struct _GUID *)
  //virtual OdResult getSubentDisplay(OdDbShSubents &, OdDbShSubentDisplayData &, bool)
  //virtual OdResult getSubentPathGeomExtents(OdGsMarker, OdDbExtents &)
  //virtual OdResult getSubentPathsAtGsMarker(unsigned long, OdGsMarker, OdGePoint3d const &, OdGeMatrix3d const &, int &, OdDbFullSubentPath * &, int, OdDbObjectId *)
  //void gripStatus(GripStat)
  //bool hasMaterialMapper()
  //bool hasProxies()
  //void* internalSubentPtr(OdDbSubentId const &)
  //bool isEmpty()
  //bool isEvaluable()
  //virtual OdResult moveGripPointsAt(OdDbVoidPtrArray const &, OdGeVector3d const &, int, BODY * &)
  //virtual OdResult moveGripPointsAtSubentPaths(OdGsMarkerArray const &, OdDbVoidPtrArray const &, OdGeVector3d const &, int, BODY * &)
  //virtual OdResult openGraph(OpenMode, OdDbEvalGraph * &)
  //class OdDbShHistory & operator=(OdDbShHistory const &)
  
  //static int primitiveIndex(class OdDbSubentId)
  //virtual int primitiveIndexAtStepId(unsigned int)
  //
  //OdResult reevaluate(BODY * &, bool, OdDbShEvaluateCallback *)
  //OdResult reevaluateAllPrimitiveNodes(bool)
  //OdResult replaceDisplayNodesAfterBreps()
  //OdResult resolveSubents(OdDbShSubents &)
  //virtual OdResult setColor(OdCmColor &)
  //virtual OdResult setMaterial(OdDbObjectId)
  //OdResult setSubentDisplay(OdDbShSubents &, OdDbShSubentDisplayData const &, BODY * &)
  //virtual bool showEntityLevelGrips()
  //static void stripPrimitiveIndex(class OdDbSubentId &)
  //virtual void subentGripStatus(GripStat, OdDbFullSubentPath const &)
  //OdDbEntity *subentPtr(OdDbFullSubentPath const &)
  //virtual void subViewportDraw(OdGiViewportDraw *)
  //virtual OdResult transformSubentPathsBy(const OdDbFullSubentPathArray &paths, OdGeMatrix3d const &, BODY * &)
  //virtual OdResult tweakLeafNode(OdDbFullSubentPathArray const &, bool, OdGeMatrix3d const &, int, int, int, char const *, BODY * &)
  //virtual int AcDbShHistory::worldDraw(OdGiWorldDraw *, OdGsMarkerArray*)
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
};

#endif
