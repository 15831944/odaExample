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

#ifndef _ODDBVIEWREPIMPL_INCLUDED_
#define _ODDBVIEWREPIMPL_INCLUDED_

#include "DbViewRep.h"
#include "DbObjectImpl.h"
#include "DbCompoundObjectId.h"
#include "DbCompoundObjectIdImpl.h"
#include "RxSketchObject.h"
#include "RxSketchManager.h"

class OdViewRepDataImpl
{
public:
  OdViewRepDataImpl();
  virtual ~OdViewRepDataImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  OdInt32 m_tag; // 0 1 ... 11 ... -2049
  OdUInt32 m_nUnknown2; // 1
  
  mutable OdUInt32 m_dbEntCount; // 1 ... 2 // cnt of ids
  OdArray<OdDbObjectId> m_dbEntIds; // graphicEntities
  OdBoolArray m_dbEntBools; // 1

  OdUInt32 m_nUnknown4; // 0 ---> 2
  
  mutable bool m_hasCurve3d; 
  mutable enum OdGe::EntityId m_entId; // OdUInt32 // 23=x17 for DbLine // 17=x11 for DbEllipse // 11 for DbArc
  OdSharedPtr<OdGeCurve3d> m_pCurve3d;

  mutable bool m_hasAdvCurve3d; // 0
  OdInt32 m_nAdvUnknown1, //-464897
          m_nAdvUnknown2; //1
  OdUInt32 m_nAdvUnknown3, //3154
          m_nAdvUnknown4; //-1
  OdSharedPtr<OdGeCurve3d> m_pAdvCurve3d;
};

class OdViewRepDataBlockImpl
{
public:
  OdViewRepDataBlockImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  OdUInt32 m_unknown;
  OdArray<OdViewRepDataImpl> m_data;
};

class OdViewRepRecordImpl
{
public:
  OdViewRepRecordImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  OdUInt64 m_unknown;
  OdUInt16 m_unknown2;
  OdUInt64Array m_unknown3;

  OdSmartPtr<OdDbCompoundObjectIdImpl> m_pBlockRefPathObjectId;
};

class OdViewRepObjectBlockRecordImpl
{
public:
  OdViewRepObjectBlockRecordImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  OdInt64 m_unknown;
  OdInt32 m_unknown2;

  OdInt16 m_unknown3;
  OdInt16 m_unknown4;

  OdUInt8Array m_arrUnknown;
  OdGeMatrix3d m_matrix;

  OdInt64Array m_arrUnknown2;

  OdArray<OdViewRepDataBlockImpl> m_blocks;
};


class OdDbViewRepImpl : public OdDbObjectImpl
{
private:
  friend class OdDbViewRep; friend class OdDbViewBorder;

  static OdDbViewRepImpl* getImpl(const OdDbViewRep* pObj)
  { 
    return (OdDbViewRepImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbViewRepImpl();

  // OdDbObjectImpl methods
  ////virtual void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  //virtual void decomposeForSave(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  //OdGeMatrix3d m_sketchModelSpaceToModelSpaceXform;
  //OdGeMatrix3d m_sketchModelSpaceToPaperSpaceXform;
  //OdGeMatrix3d m_viewModelSpaceToModelSpaceXform;
  //OdGeMatrix3d m_viewModelSpaceToPaperSpaceXform;

  OdArray<OdViewRepRecordImpl> m_records;
  OdArray<OdViewRepObjectBlockRecordImpl> m_globalBlocks;

  OdUInt32 m_Unknown1;
  OdUInt32 m_flags;
  OdUInt32 m_Unknown6;
  OdUInt64 m_invertorDrawingViewId;

  OdString m_sUnknown1;
  OdString m_sUnknown2;

  OdUInt32 m_shadeResolution;

  OdDbViewRep::ViewStyleType m_styleType;
  OdDbViewRep::ViewType m_viewType;

  bool m_Unknown9;

  OdDbObjectId m_viewBlockReferenceId;
  OdDbObjectId m_viewRepImageId;
  OdDbObjectId m_viewBorderId;

  OdDbObjectId m_viewRepSourceId;
  OdDbObjectId m_viewRepOrientation;
  OdDbObjectId m_viewRepOrientationDef;

  OdDbObjectId m_viewportId;

  OdGePoint2d m_viewBasePoint;
  double m_rotationAngle;

  OdDbObjectId m_viewRepModelSpaceViewSelSetId;
  bool m_Unknown19;
  //OdInt16 m_Unknown20;
  OdDbObjectId m_viewBlockReferenceId_1;
  
  OdRxSketchManagerPtr m_sketchManager;
  OdArray <OdRxSketchObjectPtr> m_pSketchObjects;

  OdInt32 m_Unknown22;
  OdDbObjectId m_viewRepDetailDefinitionId;

  bool m_Unknown23;
  OdDbObjectId m_blockReferenceId;

  std::map<OdUInt64, OdDbObjectId> m_mapAssocProjectedEntityPersSubentIds; //OdInt32 m_Unknown24; OdUInt64 m_Unknown25; OdDbObjectId m_assocProjectedEntityPersSubentId;
  
  OdSmartPtr<OdDbCompoundObjectIdImpl> m_pBlockRefPathObjectId; // no way to call serialize via OdRxObject

  OdDbObjectId m_UnknownId_3;
};

#endif // _ODDBVIEWREPIMPL_INCLUDED_
