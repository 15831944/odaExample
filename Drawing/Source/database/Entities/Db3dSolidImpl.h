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

class OdDb3dSolidImpl : public OdDbModelerGeometryImpl
{
  OdDbObjectId m_idHistory;
  mutable OdDbObjectPtr m_pHistoryObj; //It keeps ShHistory object. It should be created for nonDBRO object and should be added to database with 3dSolid
  bool m_recordHistoryIsSpecified;
  friend class OdDb3dSolid;
  friend class OdDbShModelerHistoryImpl;
  friend struct OdDb3dSolidTfPE;

public:
  OdDb3dSolidImpl();
protected:

  virtual void invalidateCache();

public:
  static OdDb3dSolidImpl* getImpl(const OdDb3dSolid *pObj)
  { return (OdDb3dSolidImpl*)OdDbSystemInternals::getImpl(pObj); }
  bool solidHistoryIsSpecified();
  void recordSolidHistoryIsSpecified(bool solidHistory);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual OdResult checkInterference(const OdDb3dSolid* otherSolid,
    bool createNewSolid, 
    bool& solidsInterfere,
    OdDb3dSolidPtr &commonVolumeSolid)
    const;

  virtual OdResult getMassProp(double& volume,
    OdGePoint3d& centroid,
    double momInertia[3],
    double prodInertia[3],
    double prinMoments[3],
    OdGeVector3d prinAxes[3], 
    double radiiGyration[3],
    OdGeExtents3d& extents) const;

  virtual OdResult getSection(const OdGePlane& plane, OdDbRegionPtr &sectionRegion) const;

  virtual OdResult createSculptedSolid(OdDbEntityPtrArray& limitingBodies, const OdGeIntArray& limitingFlags);

  virtual OdResult getSlice(const OdGePlane& plane, bool bGetNegHalfToo, OdDb3dSolidPtr &pNegHalfSolid);
  virtual OdResult getSlice(OdDbSurface* pSurface,  bool bGetNegHalfToo, OdDb3dSolidPtr &pNegHalfSolid);

  virtual OdResult cleanBody();

  virtual OdResult separateBody(OdDb3dSolidPtrArray &newSolids);

  virtual OdResult createPyramid(double height, int sides, double radius, double topRadius = 0.0 );

  virtual bool recordHistory() const;
  virtual bool showHistory() const;
  virtual OdResult setRecordHistory(OdDb3dSolidPtr pSol, bool bRecord);
  virtual OdResult setShowHistory(OdDb3dSolidPtr pSol, bool bShow);
};

#endif // _ODDB_3DSOLID_INCLUDED_
