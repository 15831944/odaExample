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

#ifndef _ODDB_MOTIONPATH_IMPL_INCLUDED_
#define _ODDB_MOTIONPATH_IMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbMotionPath.h"
#include "DbObjectImpl.h"

class OdDbMotionPathImpl : public OdDbObjectImpl
{
  protected:
    static OdDbMotionPathImpl* getImpl(const OdDbMotionPath *pObj)
    {
      return (OdDbMotionPathImpl*)OdDbSystemInternals::getImpl(pObj);
    }

  public:
    OdDbMotionPathImpl();
    virtual ~OdDbMotionPathImpl();

  protected:
    static OdUInt32 kCurrentVersion;

    OdDbHardPointerId m_cameraId;
    OdDbHardPointerId m_targetId;
    OdDbHardPointerId m_viewRecId;
    OdUInt32          m_nFrames;
    OdUInt32          m_nFPS;
    bool              m_bDecel;

    void setCameraPath(const OdDbObjectId &pathId);
    OdDbObjectId cameraPath() const;

    void setTargetPath(const OdDbObjectId &pathId);
    OdDbObjectId targetPath() const;

    void setViewTableRecordId(const OdDbObjectId &viewId);
    OdDbObjectId viewTableRecordId() const;

    void setFrames(OdUInt32 nFrames);
    OdUInt32 frames() const;

    void setFrameRate(OdUInt32 nRate);
    OdUInt32 frameRate() const;

    void setCornerDecel(bool bCornerDecel);
    bool cornerDecel() const;

    OdResult dwgInFields(OdDbObject *pObj, OdDbDwgFiler *pFiler);
    void dwgOutFields(const OdDbObject *pObj, OdDbDwgFiler *pFiler) const;
    OdResult dxfInFields(OdDbObject *pObj, OdDbDxfFiler *pFiler);
    void dxfOutFields(const OdDbObject *pObj, OdDbDxfFiler *pFiler) const;

    friend class OdDbMotionPath;
};

#endif // _ODDB_MOTIONPATH_IMPL_INCLUDED_
