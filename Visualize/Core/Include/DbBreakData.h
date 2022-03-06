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

#ifndef _DbBreakData_h_Included_
#define _DbBreakData_h_Included_

#include "DbObject.h"
#include "OdArray.h"
#include "SmartPtr.h"
#include "DbDimAssoc.h"

class OdTvDbBreakPointRef;
typedef OdSmartPtr<OdTvDbBreakPointRef> OdTvDbBreakPointRefPtr;
typedef OdArray<OdTvDbBreakPointRefPtr> OdTvDbBreakPointRefPtrArray;

/** \details 
  This class represents break data for dimensions.

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbBreakData : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBreakData);

  OdTvDbObjectId dimObjId() const;
  void setDimObjId(const OdTvDbObjectId& dimId);

  void addBreakPointRef(OdTvDbBreakPointRef* ptRef);
  void getBreakPointRef(int lineIndex, OdTvDbBreakPointRefPtrArray& ptRefs) const;
  void getBreakPointRef(OdTvDbBreakPointRefPtrArray& ptRefs) const;
  void deleteAllBreakPointRefs();
  OdResult removeAssociativity(bool force = true);
  //OdResult postToDb(OdTvDbObjectId& breakObjId);
  //OdResult eraseFromDb(); 

  virtual OdResult dwgInFields (OdTvDbDwgFiler*);
  virtual void dwgOutFields(OdTvDbDwgFiler*) const;
  virtual OdResult dxfInFields (OdTvDbDxfFiler*);
  virtual void dxfOutFields(OdTvDbDxfFiler*) const;
  virtual void modifiedGraphics(const OdTvDbEntity* pEnt);
  virtual void erased(const OdTvDbObject* pObj, bool erasing);
  virtual void modified(const OdTvDbObject* pObj);

  OdResult updateAssociativity(const OdTvDbObjectIdArray& ids, int cmdType);
};

typedef OdSmartPtr<OdTvDbBreakData> OdTvDbBreakDataPtr;

/** \details 
  This class represents break points for dimensions.

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbBreakPointRef : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBreakPointRef);

  enum BreakPointType { 
    kDynamic           = 0,
    kStatic            = 1,
    kStatic2Point      = 2
  };

  OdTvDbBreakPointRef::BreakPointType pointType() const;
  void setPointType(OdTvDbBreakPointRef::BreakPointType newVal);
  OdInt32 lineIndex() const;
  void setLineIndex(OdInt32 index);
  OdGePoint3d breakPoint() const;
  void setBreakPoint(const OdGePoint3d& pt);
  OdGePoint3d breakPoint2() const;
  void setBreakPoint2(const OdGePoint3d& pt);
  void getBreakPointId(OdTvDbXrefFullSubentPath& idPath) const;
  void setBreakPointId(const OdTvDbXrefFullSubentPath& idPath);
  OdTvDbEntityPtr subentPtr() const;
  OdResult intersectWith(const OdTvDbEntity* pEnt, OdGePoint3dArray& points, OdGePoint3dArray& textBoxPts);

  virtual OdResult dwgInFields (OdTvDbDwgFiler*);
  virtual void dwgOutFields(OdTvDbDwgFiler*) const;
  virtual OdResult dxfInFields (OdTvDbDxfFiler*);
  virtual void dxfOutFields(OdTvDbDxfFiler*) const;
};

#endif

