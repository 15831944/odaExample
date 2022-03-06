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

#ifndef DbAssocPersSubentManagerImpl_INCLUDED_
#define DbAssocPersSubentManagerImpl_INCLUDED_ /* {Secret} */

#include "TD_PackPush.h"
#include "DbAssocPersSubentManager.h"
#include "DbPersSubentManagerImpl.h"
#include "DbObjectImpl.h"

/** Description:
  This class represents the custom imlementation of the persistent subentity manager.

  Library: Source *code* provided.
  {group:Contraint_Classes} 
*/


using namespace OdDbHistoryInternal;

class OdDbAssocPersSubentManagerImpl : public OdDbObjectImpl
{
  std::map <int, int> m_mapAcisDataType;// =//TODO Not all AcisDataType added to map
  //{ 
  //  { kSurfaceExtrude_CMark, kArrFirstSurfaceExtrude_CMark },
  //  { kPlaneSurface_CLine, kArrSolidExtrude_CLCM },
  //  { kPlaneSurface_CLine56, kArrPlaneSurface_CLine56 },
  //  { kSolidExtrude_CLCM, kArrSolidExtrude_CLCM },
  //  { kSolidBox_CLine, kArrSolidBox_CLine },
  //  { kExtendCL, kArrExtendCL },
  //  { kExtrudeSurface_TopOrBottom_CLine, kArrExtrudeSurface_CLine }, // 16 for plane surface. See EXTEND_2CL.dwg
  //  { kExtrudeSurface_Side_CLine, kArrExtrudeSurface_CLine }
  //} ;

  static OdDbAssocPersSubentManagerImpl* getImpl(const OdDbAssocPersSubentManager *pObj)
  { 
    return (OdDbAssocPersSubentManagerImpl*)OdDbSystemInternals::getImpl(pObj);
  }  

  OdUInt32 m_iLastId;
  OdUInt32 m_iNumSubent;

  SubentRWDataArray m_subentDataRWArr;
  OdUInt32Array m_arrId;
  OdUInt32Array m_arrId2;
  OdUInt32Array m_arrId3;
  bool m_bValUnk;

  bool m_bTmpPrsMgrType; //true -  OdDbPersSubentManager, false -  OdDbAssocPersSubentManager

public:
  OdDbAssocPersSubentManagerImpl();

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);

  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  //virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual OdResult parseSubentData(SubentDataArray& pData);

  //OdDbPersSubentManager(OdDbPersSubentManager const &)

  //Convert OdDbAssocPersSubentManager data to OdDbPersSubentManager data
  void convertToPersSubentManager(OdDbPersSubentManagerImpl* pPersSubentData);

  //Convert OdDbPersSubentManager data to OdDbAssocPersSubentManager data
  OdResult convertToAssocPersSubentManager(const OdDbPersSubentManagerImpl* pPersSubentData);

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void cleanData();
  OdUInt32 createNewStep();
  OdArray <OdUInt32> infoAcisDataIndexes(OdUInt32 depIndex);
  OdResult addSubentRWData(AcisDataType dt, AcisDataTypeArrFirst dtFirst, OdUInt32 idx, OdArray<OdUInt32> arr);
  OdUInt32 maxSubentIdIndex();

protected:
  void setDefaultValuesToArraysId(SubentRWData& pSubentRWData, AcisDataType dt, AcisDataTypeArrFirst dtFirst);
  friend class OdDbAssocPersSubentManager;
  friend class OdDbPersSubentManager;
  friend class OdDbPersSubentManagerImpl;

  //void reevaluateSurfaceFromEdges(unsigned int,class BODY *,OdArray<class ENTITY *> const &);
  //void reevaluateOffset(unsigned int,OdArray<class BODY *> const &,class PersSubentNaming::AnnotationData const *);
  //void reevaluateSurfaceExtend(unsigned int,class BODY *,OdArray<class EdgeStartMidEnd> const &);
  //void reevaluateSurfaceFilletChamfer(unsigned int,class BODY *,OdArray<class BODY *> const &,OdArray<bool> const &);
  //void reevaluateSurfaceFilletChamfer(unsigned int,class BODY *,OdArray<class BODY *> const &,OdArray<bool> const &);
  //void reevaluateSurfaceTrim(unsigned int,class BODY *,OdArray<class EDGE *> const &,OdArray<OdArray<class FACE *> > > const &);
  //void reevaluateSurfaceTrim(unsigned int,class BODY *,OdArray<class EDGE *> const &,OdArray<OdArray<class FACE *> > > const &);
  //bool isSolidId(unsigned int)const;
  //void reportSolidId(unsigned int);
  //void reevaluateNetworkSurface(unsigned int,class BODY *,class COEDGE *);
  //void reevaluateLoft(unsigned int,class BODY *,bool,bool,bool,class FACE * * const,OdArray<OdArray<class EDGE *>> const &,OdArray<OdArray<bool>&);
  //void reevaluateLoft(unsigned int,class BODY *,bool,bool,bool,class FACE * * const,OdArray<OdArray<class EDGE *>> const &,OdArray<OdArray<bool>&);
  //void reevaluateSweep(unsigned int,class BODY *,bool,bool,class FACE * * const,OdArray<class EDGE *> const &,OdArray<bool> const &,OdArray<unsigned int> const &,OdArray<OdArray<unsigned int> > &);
  //void reevaluateSweep(unsigned int,class BODY *,bool,bool,class FACE * * const,OdArray<class EDGE *> const &,OdArray<bool> const &,OdArray<unsigned int> const &,OdArray<OdArray<unsigned int> > &);
  //void reevaluateRevolve(unsigned int,class BODY *,bool,bool,OdGeVector3d const &,class FACE * * const,OdArray<class EDGE *> const &,OdArray<unsigned int> const &);
  //void reevaluateRevolve(unsigned int,class BODY *,bool,bool,OdGeVector3d const &,class FACE * * const,OdArray<class EDGE *> const &,OdArray<unsigned int> const &);
  //void reevaluateExtrude(unsigned int,class BODY *,bool,class FACE * * const,OdArray<class EDGE *> const &,OdArray<unsigned int> const &);
  //void reevaluateExtrude(unsigned int,class BODY *,bool,class FACE * * const,OdArray<class EDGE *> const &,OdArray<unsigned int> const &);
  //void mirrorStepIds(OdArray<unsigned int> const &,bool);
  //void getProfileEdgesFromProfileBody(class BODY const *,OdArray<class EDGE *> &,OdArray<bool> &);
  //void getProfileEdgesFromProfileBody(class BODY const *,OdArray<class EDGE *> &,OdArray<bool> &);
  //void reevaluateTweak(unsigned int,class BODY *);
  //void reevaluateBlend(unsigned int,class BODY *,class BODY *);
  //void reevaluatePrimitive(unsigned int,class BODY *);
  //enum OdResult auditBody(class BODY const *,OdDbAuditInfo *);
  //enum OdResult auditPersSubent(unsigned int,OdDbAuditInfo *);
  //enum OdResult auditStep(unsigned int,OdDbAuditInfo *);
  //bool isValidPersSubent(unsigned int)const;
  //bool isValidStep(unsigned int)const;
  //bool isGeneratedId(unsigned int)const;
  //void deletePersSubent(unsigned int);
  //void deleteStep(unsigned int);
  //bool isIdPurgeable(unsigned int)const;
  //void makeIdPurgeable(unsigned int,bool);
  //void convertToPrimitive(class BODY *,unsigned int);
  //void insureStepIdsInBodyExist(class BODY const *);
  //void insureStepIdExists(unsigned int);
  //void getEntitiesFromPersSubentId(unsigned int,class BODY const *,OdDbEntity *,OdArray<class ENTITY *> &);
  //unsigned int createNewStep(bool);
  //unsigned int createNewPersSubent(class BODY * &,class ENTITY * &,OdDbEntity *,bool);
  //void setStatus(enum OdDbAssocPersSubentManager::Status);
  //enum OdDbAssocPersSubentManager::Status status()const;
};


#include "TD_PackPop.h"

#endif // DbAssocPersSubentManagerImpl_INCLUDED_
