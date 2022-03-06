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

#ifndef _ODDB_3DSOLID_INCLUDED_
#define _ODDB_3DSOLID_INCLUDED_

#include "DbModelerGeometryImpl.h"
#include "Db3dSolid.h"
#include "ModelerHistory.h"

class OdTvDb3dSolidImpl : public OdTvDbModelerGeometryImpl
{
  OdTvDbObjectId m_idHistory;
  mutable OdTvDbObjectPtr m_pHistoryObj; //It keeps ShHistory object. It should be created for nonDBRO object and should be added to database with 3dSolid
  bool m_recordHistoryIsSpecified;
  friend class OdTvDb3dSolid;
  friend class OdTvDbBody;
  friend class OdTvDbShModelerHistoryImpl;
  friend struct OdTvDb3dSolidTfPE;

public:
  OdTvDb3dSolidImpl();
  static OdTvDb3dSolidImpl* getImpl(const OdTvDb3dSolid *pObj)
  { return (OdTvDb3dSolidImpl*)OdTvDbSystemInternals::getImpl(pObj);}
protected:

  virtual void invalidateCache();

public:
  bool solidHistoryIsSpecified();
  void recordSolidHistoryIsSpecified(bool solidHistory);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual OdResult checkInterference(const OdTvDb3dSolid* otherSolid,
    bool createNewSolid, 
    bool& solidsInterfere,
    OdTvDb3dSolidPtr &commonVolumeSolid)
    const;

  virtual OdResult getMassProp(double& volume,
    OdGePoint3d& centroid,
    double momInertia[3],
    double prodInertia[3],
    double prinMoments[3],
    OdGeVector3d prinAxes[3], 
    double radiiGyration[3],
    OdGeExtents3d& extents) const;

  virtual OdResult getSection(const OdGePlane& plane, OdTvDbRegionPtr &sectionRegion) const;

  virtual OdResult getSlice(const OdGePlane& plane, bool bGetNegHalfToo, OdTvDb3dSolidPtr &pNegHalfSolid);
  virtual OdResult getSlice(OdTvDbSurface* pSurface,  bool bGetNegHalfToo, OdTvDb3dSolidPtr &pNegHalfSolid);

  virtual OdResult cleanBody();

  virtual OdResult separateBody(OdTvDb3dSolidPtrArray &newSolids);

  virtual OdResult createPyramid(double height, int sides, double radius, double topRadius = 0.0 );

  virtual bool recordHistory() const;
  virtual bool showHistory() const;
  virtual OdResult setRecordHistory(OdTvDb3dSolidPtr pSol, bool bRecord);
  virtual OdResult setShowHistory(OdTvDb3dSolidPtr pSol, bool bShow);
};

#endif // _ODDB_3DSOLID_INCLUDED_
