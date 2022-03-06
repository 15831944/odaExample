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

#ifndef _WRSILHOUETTESCACHE_H_
#define _WRSILHOUETTESCACHE_H_

#include "OdArray.h"
#include "wrWiresCache.h"
#include "DbDatabase.h"

class OdCmEntityColor;
class OdDbStub;

/** Description:

{group:BrepRenderer_Classes}
*/
class wrSilhouette : public wrTransformStore
{
public:
  OdUInt64        vpId;
  const OdDbStub *vpObjectId;

  OdGePoint3d     vpTarget;
  OdGePoint3d     vpDirFromTarget;
  OdGeVector3d    vpUpDir;
  bool            vpPerspective;
  wrWireArray     wires;
  bool            bSupportTrueColor;
  bool            bCanBeSavedToDwg;

  wrSilhouette();

  bool isSameState(const OdGeVector3d &DirFromCenter
    , const OdGeVector3d &UpDir
    , bool Perspective) const;
};

class wrSilhouetteCache : public OdArray<wrSilhouette>
{
  bool m_bEasySave;
  bool m_bJustLoaded;

  void clearViewportIDs();
  void clearUnusedCacheItems();
public:
  wrSilhouetteCache();
  virtual ~wrSilhouetteCache();
  wrSilhouette *find(const OdDbStub *vpObjectId);
  wrSilhouette *find(OdUInt64 vpId);
  void setupViewPortsObjectId(OdDbDatabasePtr pCurDatabase);
  void prepareCacheForSave(OdDbDatabasePtr pCurDatabase);
  void setChanged();
  void invalidateCache();
  void transformBy(const OdGeMatrix3d &xMat);
  void setColor(OdCmEntityColor clrIndx);
  OdUInt32 numOfValidForDwgSilhouettes() const;
};

#endif // _WRSILHOUETTESCACHE_H_
