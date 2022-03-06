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

#include "PrcCommon.h"
#include "PrcDumpModule.h"
#include "StaticRxObject.h"
#include "PrcFile.h"
#include "PrcFileStructure.h"
#include "PrcPartDefinition.h"
#include "PrcMarkups.h"

//
//#define DUMP_COMPRESSION
//
#ifdef DUMP_COMPRESSION
#include "PrcHighlyCompressed3dTess.h"
#include "PrcCompressedSingleWireBody.h"
#include "PrcCompressedLine.h"
#include "PrcCompressedCircle.h"
#include "PrcCompressedHermiteCurve.h"
#include "PrcCompressedEllipse.h"
#include "PrcCompressedCompositeCurve.h"
#endif

ODRX_NO_CONS_DEFINE_MEMBERS(OdPrcEntity_Dumper, OdRxObject);

//DD:EXPORT_ON
ODRX_DEFINE_DYNAMIC_MODULE(OdPrcDumpModule);
//DD:EXPORT_OFF

OdPrcDumpModule::OdPrcDumpModule()
  : m_pDumpers(0)
{
}

OdPrcDumpModule::~OdPrcDumpModule()
{
  if(m_pDumpers)
    uninitApp();
}

void OdPrcEntity_Dumper::dump(const OdRxObject *pObj, const OdPrcListener* pListener) const
{
}

void dumpUnit(const OdPrcUnit &pUnit, const OdPrcListener *pListener)
{
  pListener->dumpBoolean(L"Unit from CAD file", pUnit.unitFromCADFile());
  pListener->dumpDouble(L"Unit", pUnit.unit());
}

void dumpUserData(const OdPrcUserData &pUserData, const OdPrcListener *pListener)
{
  pListener->dumpBits(L"UserData", pUserData.bitData());
}

void dump(const OdChar *pName, const OdPrcObjectIdArray &pArray, const OdPrcListener *pListener)
{
  OdString tmp;
  pListener->dumpUInt32(tmp.format(L"%ls.size()", pName), pArray.size());
  for (OdUInt32 f=0; f<pArray.size(); ++f)
  {
    pListener->dumpObjectId(tmp.format(L"%ls[%d]", pName, f), pArray[f]);
  }
}

void dumpGePoint3d(const OdChar *pName, const OdGePoint3d &pPoint, const OdPrcListener *pListener)
{
  pListener->dumpDouble(OdString(pName) + ".x", pPoint.x);
  pListener->dumpDouble(OdString(pName) + ".y", pPoint.y);
  pListener->dumpDouble(OdString(pName) + ".z", pPoint.z);
}

void dumpGeVector3d(const OdChar *pName, const OdGeVector3d &pVector, const OdPrcListener *pListener)
{
  pListener->dumpDouble(OdString(pName) + ".x", pVector.x);
  pListener->dumpDouble(OdString(pName) + ".y", pVector.y);
  pListener->dumpDouble(OdString(pName) + ".z", pVector.z);
}

void dumpGePoint2d(const OdChar *pName, const OdGePoint2d &pPoint, const OdPrcListener *pListener)
{
  pListener->dumpDouble(OdString(pName) + ".x", pPoint.x);
  pListener->dumpDouble(OdString(pName) + ".y", pPoint.y);
}

void dumpGeVector2d(const OdChar *pName, const OdGeVector2d &pVector, const OdPrcListener *pListener)
{
  pListener->dumpDouble(OdString(pName) + ".x", pVector.x);
  pListener->dumpDouble(OdString(pName) + ".y", pVector.y);
}

void dumpBoundingBox(const OdChar *pName, const OdPrcBoundingBox &pBoundingBox, const OdPrcListener *pListener)
{
  const OdGePoint3d &maxPoint = pBoundingBox.box().maxPoint();
  dumpGePoint3d(OdString(pName) + ".max", maxPoint, pListener);
  const OdGePoint3d &minPoint = pBoundingBox.box().minPoint();
  dumpGePoint3d(OdString(pName) + ".min", minPoint, pListener);
}

void dump(const OdChar *pName, const OdPrcMarkups &pMarkups, const OdPrcListener *pListener)
{
  const OdPrcObjectIdArray &annotationEntities = pMarkups.annotationEntities();
  ::dump(L"annotations", annotationEntities, pListener);
  const OdPrcObjectIdArray &markups = pMarkups.markups();
  ::dump(L"markups", markups, pListener);
  const OdPrcObjectIdArray &leaders = pMarkups.leaders();
  ::dump(L"leaders", leaders, pListener);
  const OdPrcObjectIdArray &linkedItems = pMarkups.linkedItem();
  ::dump(L"linkedItems", linkedItems, pListener);
}

void dumpUncompressedFiles(const OdPrcUncompressedFiles &pUncFile, const OdPrcListener *pListener)
{
  pListener->dumpUInt32(L"Number of uncompressed files", pUncFile.fileContents().size());
  for (OdUInt32 i = 0; i < pUncFile.fileContents().size(); i++)
  {
    pListener->dumpUInt32(L"  Size of uncompressed file", pUncFile.fileContents()[i].size());
    pListener->dumpUncompressedBlock(L"  File Content", pUncFile.fileContents()[i]);
  }
}

void dumpLineAttr(const OdPrcObjectId &pLA, const OdPrcListener *pListener)
{
  pListener->dumpObjectId(L"LineStyleID", pLA);
}

void dumpGraphics(const OdPrcGraphics &pGraph, const OdPrcListener *pListener)
{
  pListener->dumpUInt32(L"layer index", pGraph.layerIndex());
  pListener->dumpUInt16(L"behaviour Bit Field", pGraph.behaviourBitField());
  OdUInt16 nBehaviorBitFiled = pGraph.behaviourBitField();
  if (nBehaviorBitFiled & PRC_GRAPHICS_Show)
  {
    pListener->dumpString(L"", L"Show");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritShow)
  {
    pListener->dumpString(L"", L"SonHeritShow");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_FatherHeritShow)
  {
    pListener->dumpString(L"", L"FatherHeritShow");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritColor)
  {
    pListener->dumpString(L"", L"SonHeritColor");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_FatherHeritColor)
  {
    pListener->dumpString(L"", L"FatherHeritColor");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritLayer)
  {
    pListener->dumpString(L"", L"SonHeritLayer");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_FatherHeritLayer)
  {
    pListener->dumpString(L"", L"FatherHeritLayer");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritTransparency)
  {
    pListener->dumpString(L"", L"SonHeritTransparency");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_FatherHeritTransparency)
  {
    pListener->dumpString(L"", L"FatherHeritTransparency");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritLinePattern)
  {
    pListener->dumpString(L"", L"SonHeritLinePattern");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_FatherHeritLinePattern)
  {
    pListener->dumpString(L"", L"FatherHeritLinePattern");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritLineWidth)
  {
    pListener->dumpString(L"", L"SonHeritLineWidth");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_SonHeritLineWidth)
  {
    pListener->dumpString(L"", L"FatherHeritLineWidth");
  }
  if (nBehaviorBitFiled & PRC_GRAPHICS_Removed)
  {
    pListener->dumpString(L"", L"Removed");
  }
  dumpLineAttr(pGraph.styleId(), pListener);
}

void dumpAttributeEntry(const OdPrcAttributeEntry &pAE, const OdPrcListener *pListener)
{
  pListener->dumpBoolean(L"titleIsInteger", pAE.titleIsInteger());
  pListener->dumpString(L"Title", pAE.getTitle());
  pListener->dumpUInt8(L"Index", pAE.getIndex());
}

void dumpTimeStamp(const OdTimeStamp &ts, const OdPrcListener *pListener)
{
  short year, month, day;
  ts.getDate(month, day, year);
  short hour, minute, second, milisecond;
  ts.getTime(hour, minute, second, milisecond);
  const OdUInt32 nowYear = (year - 1970);
  const OdUInt32 nowMonth = (month-1);
  const OdUInt32 nowDay = (day-1);
  OdString dateTime;
  dateTime.format(L"Date: %02u.%02u.%02u; Time: %02u:%02u:%02u:%04u", nowDay, nowMonth, nowYear,hour, minute, second, milisecond);
  pListener->dumpString(L"Date&Time",dateTime);
}
  
void dumpContentSingleAttribute(const OdPrcContentSingleAttribute &pCSA, const OdPrcListener *pListener)
{
  dumpAttributeEntry(pCSA.attributeEntry(), pListener);
  pListener->dumpUInt8(L"Type", pCSA.getType());
  OdUInt32 type = pCSA.getType();
  switch(type)
  {
  case KEPRCModellerAttributeTypeInt:
    pListener->dumpInt32(L"DataInt32", pCSA.getDataInt32());
    break;
  case KEPRCModellerAttributeTypeReal:
    pListener->dumpDouble(L"DataDouble", pCSA.getDataDouble());
    break;
  case KEPRCModellerAttributeTypeTime:
    dumpTimeStamp(pCSA.getDataTime(), pListener);
    break;
  case KEPRCModellerAttributeTypeString:
    pListener->dumpString(L"DataString",pCSA.getDataStr());
  default:
    pListener->dumpString(L"Attribute data is empty","");
  }
}

void dumpAttribute(const OdPrcAttribute &pA, const OdPrcListener *pListener)
{
  for (OdUInt32 i = 0; i < pA.contentSingleAttribute().size(); i++)
  {
    dumpContentSingleAttribute(pA.contentSingleAttribute()[i], pListener);
  }
  dumpAttributeEntry(pA.attributeEntry(), pListener);
  pListener->dumpUInt32(L"prcType", pA.prcType());
}

void dumpAttributeData(const OdPrcAttributeData &pAD, const OdPrcListener *pListener)
{
  for (OdUInt32 i = 0; i < pAD.attributes().size(); i++)
  {
    dumpAttribute(pAD.attributes()[i], pListener);
  }
}

void dumpRIContent(const OdPrcRepresentationItemContent &pContent, const OdPrcListener *pListener)
{
  const OdPrcBaseTessDataPtr &tess = pContent.tessellation();
  const OdPrcObjectId &coordinateSystem = pContent.localCoordinateSystemID();

  if (tess.isNull())
  {
    pListener->dumpString(L"tessellation", L"null");
  }
}

#define DUMPRI(RI, pListener) dumpUserData(RI->userData(), pListener);\
  pListener->dumpObjectId(L"referenceToBodyId", RI->getReferenceToBodyId());\
  pListener->dumpObjectId(L"localCoordinateSystemID", RI->localCoordinateSystemID());\
  dumpRIContent(*RI, pListener);

#define DUMPBASE(base, pListener) pListener->dumpUInt32(L"Type", base->prcType());\
  pListener->dumpString(L"Name", base->name().name());

#define DUMPREFERENCEDBASE(refBase, pListener)\
  OdPrcFileStructurePtr pFS = refBase->objectId().database(); \
  pListener->dumpString(L"FS_ID", pFS->objectId().getHandle().ascii()); \
  pListener->dumpObjectId(L"ID" , refBase->objectId());\
  DUMPBASE(refBase, pListener)\
  pListener->dumpUInt32(L"cadPersistentIdentifier", refBase->cadPersistentIdentifier());\
  pListener->dumpUInt32(L"cadIdentifier", refBase->cadIdentifier());

#define DUMPGRAPHICS(object, pListener) DUMPREFERENCEDBASE(object, pListener)\
  dumpGraphics(object->graphics(), pListener);\
  dumpAttributeData(object->attributeData(), pListener);

class OdPrcPartDefinition_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPartDefinitionPtr pPrc = pObj;
    DUMPGRAPHICS(pPrc, pListener)

    dumpBoundingBox(L"boundingBox", pPrc->boundingBox(), pListener);
    ::dump(L"representationItem", pPrc->representationItem(), pListener);
    ::dump(L"Markups", pPrc->markups(), pListener);
    ::dump(L"annotationView", pPrc->annotationView(), pListener);
    dumpUserData(pPrc->userData(), pListener);
  }
};

class OdPrcBrepModel_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcBrepModelPtr pBM = pObj;
    DUMPGRAPHICS(pBM, pListener)
    DUMPRI(pBM, pListener)

    pListener->dumpBoolean(L"Is Closed", pBM->isClosed());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcBrepModelPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcWireCurve_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcWireCurvePtr pWC = pObj;
    DUMPGRAPHICS(pWC, pListener)
    DUMPRI(pWC, pListener)
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcWireCurvePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcDirection_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcDirectionPtr pD = pObj;
    DUMPGRAPHICS(pD, pListener)
    DUMPRI(pD, pListener)

    const OdGePoint3d &origin = pD->origin();
    dumpGePoint3d(L"Origin", origin, pListener);
    const OdGeVector3d &direction = pD->direction();
    dumpGeVector3d(L"Direction", direction, pListener);
    pListener->dumpBoolean(L"Has Origin", pD->hasOrigin());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcDirectionPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcConstructionPlane_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcConstructionPlanePtr pCP = pObj;
    DUMPGRAPHICS(pCP, pListener)
    DUMPRI(pCP, pListener)
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcConstructionPlanePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

void dump(const OdChar *pName, const OdGePoint3dArray &pArray, const OdPrcListener *pListener)
{
  OdString tmp;
  for(OdUInt32 f=0; f<pArray.size(); ++f)
  {
    tmp.format(L"%ls %d", pName, f);
    dumpGePoint3d(tmp.c_str(),pArray[f], pListener);
  }
}

void dump(const OdChar *pName, const OdGePoint2dArray &pArray, const OdPrcListener *pListener)
{
  OdString tmp;
  for(OdUInt32 f=0; f<pArray.size(); ++f)
  {
    tmp.format(L"%ls %d", pName, f);
    dumpGePoint2d(tmp.c_str(),pArray[f], pListener);
  }
}

class OdPrcPointSet_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPointSetPtr pPS = pObj;
    DUMPGRAPHICS(pPS, pListener)
    DUMPRI(pPS, pListener)

    const OdGePoint3dArray &point = pPS->point();
    ::dump(L"Point", point, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcPointSetPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcPolyBrepModel_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPolyBrepModelPtr pPBM = pObj;
    DUMPGRAPHICS(pPBM, pListener)
    DUMPRI(pPBM, pListener)

    pListener->dumpBoolean(L"Is Closed", pPBM->isClosed());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcPolyBrepModelPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcPolyWire_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPolyWirePtr pPW = pObj;
    DUMPGRAPHICS(pPW, pListener)
    DUMPRI(pPW, pListener)
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcPolyWirePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcSet_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSetPtr pS = pObj;
    DUMPGRAPHICS(pS, pListener)
    DUMPRI(pS, pListener)

    const OdPrcObjectIdArray &representationItem = pS->representationItem();
    ::dump(L"representationItem", representationItem, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcSetPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

void dump(const OdChar *pName, const OdGeMatrix3d &pMatrix3d, const OdPrcListener *pListener)
{
  OdString tmp;
  tmp.format(L"%ls\nOrigin",pName);
  OdGePoint3d origin;
  OdGeVector3d x, y, z;
  pMatrix3d.getCoordSystem(origin, x, y, z);
  dumpGePoint3d(tmp.c_str(), origin, pListener);
  dumpGeVector3d(L"X axis", x, pListener);
  dumpGeVector3d(L"Y axis", y, pListener);
  dumpGeVector3d(L"Z axis", z, pListener);

  if (
    !OdEqual(pMatrix3d[3][0], 0.) ||
    !OdEqual(pMatrix3d[3][1], 0.) ||
    !OdEqual(pMatrix3d[3][2], 0.) ||
    !OdEqual(pMatrix3d[3][3], 1.)
    )
  {
    pListener->dumpDouble(L"homo.x", pMatrix3d[3][0]);
    pListener->dumpDouble(L"homo.y", pMatrix3d[3][1]);
    pListener->dumpDouble(L"homo.z", pMatrix3d[3][2]);
    pListener->dumpDouble(L"homo.scale", pMatrix3d[3][3]);
  }
}

void dump(const OdChar *pName, const OdPrcTransformation3d *pTransformation3d, const OdPrcListener *pListener)
{
  if (pTransformation3d)
  {
    ::dump(L"Transformation matrix", pTransformation3d->getGeMatrix3d(), pListener);
  }
  else
  {
    pListener->dumpString(L"No transformation", "");
  }
}

void dump(const OdChar *pName, const OdGeMatrix2d &pMatrix2d, const OdPrcListener *pListener)
{
  OdString tmp;
  tmp.format(L"%ls\nOrigin",pName);
  OdGePoint2d origin;
  OdGeVector2d xAxis, yAxis;
  pMatrix2d.getCoordSystem(origin, xAxis, yAxis);
  dumpGePoint2d(tmp.c_str(), origin, pListener);
  dumpGeVector2d(L"X axis", xAxis, pListener);
  dumpGeVector2d(L"Y axis", yAxis, pListener);
}

void dump(const OdChar *pName, const OdPrcTransformation2d * pTransformation2d, const OdPrcListener *pListener)
{
  if (pTransformation2d)
  {
    ::dump(L"Transformation matrix", pTransformation2d->getGeMatrix2d(), pListener);
  }
  else
  {
    pListener->dumpString(L"No transformation", "");
  }
}

class OdPrcCoordinateSystem_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCoordinateSystemPtr pCS = pObj;
    DUMPGRAPHICS(pCS, pListener)
    DUMPRI(pCS, pListener)

    const OdPrcTransformation3d& axisSet = pCS->axisSet();
    ::dump(L"axis set", &axisSet, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcCoordinateSystemPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcAnnotationItem_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcAnnotationItemPtr pAI = pObj;
    DUMPGRAPHICS(pAI, pListener)

    pListener->dumpObjectId(L"markup", pAI->markup());
    dumpUserData(pAI->userData(), pListener);
  }
};

class OdPrcAnnotationSet_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcAnnotationSetPtr pAS = pObj;
    DUMPGRAPHICS(pAS, pListener)

    const OdPrcObjectIdArray &entities = pAS->entities();
    ::dump(L"entities", entities, pListener);
    dumpUserData(pAS->userData(), pListener);
  }
};

class OdPrcAnnotationReference_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcAnnotationReferencePtr pAR = pObj;
    DUMPGRAPHICS(pAR, pListener)

    const OdPrcObjectIdArray &entities = pAR->entities();
    ::dump(L"entities", entities, pListener);
    dumpUserData(pAR->userData(), pListener);
  }
};

class OdPrcMarkup_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMarkupPtr pM = pObj;
    DUMPGRAPHICS(pM, pListener)

    //tessellation --> RxObject
    dumpUserData(pM->userData(), pListener);
    pListener->dumpUInt32(L"type", pM->type());
    pListener->dumpUInt32(L"subtype", pM->subType());
    const OdPrcObjectIdArray &leader = pM->leader();
    ::dump(L"leaders", leader, pListener);
    const OdPrcObjectIdArray &linkedItem = pM->linkedItem();
    ::dump(L"linked Item", linkedItem, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcMarkupPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

class OdPrcMarkupLeader_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMarkupLeaderPtr pML = pObj;
    DUMPGRAPHICS(pML, pListener)

    //tessellation --> RxObject
    dumpUserData(pML->userData(), pListener);
    pListener->dumpObjectId(L"linkedItem ID", pML->linkedItem());
    pListener->dumpObjectId(L"nextLeader ID", pML->nextLeader());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcMarkupLeaderPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellation());
    return subs;
  }
};

void dumpReferenceData(const OdPrcReferenceData &pRD, const OdPrcListener *pListener)
{
  if (pRD.referenceOnPRCBase().isValid())
  {
    pListener->dumpObjectId(L"reference On PRC Base", pRD.referenceOnPRCBase());
  }
  else if (pRD.referenceOnTopology().isValid())
  {
    pListener->dumpObjectId(L"reference On Topology", pRD.referenceOnTopology());
    OdString tmp;
    for (OdUInt32 i = 0; i < pRD.indexes().size(); ++i)
    {
      pListener->dumpUInt32(tmp.format(L"indexes[%d]", i), pRD.indexes()[i]);
    }
  }
  else
  {
    pListener->dumpString(L"reference does not exist", "");
  }
}

class OdPrcMarkupLinkedItem_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMarkupLinkedItemPtr pLI = pObj;
    DUMPGRAPHICS(pLI, pListener)

    dumpUserData(pLI->userData(), pListener);
    pListener->dumpBoolean(L"leader Delete Control", pLI->leaderDeleteControl());
    pListener->dumpBoolean(L"leader Show Control", pLI->leaderShowControl());
    pListener->dumpBoolean(L"markup Delete Control", pLI->markupDeleteControl());
    pListener->dumpBoolean(L"markup Show Control", pLI->markupShowControl());
    dumpReferenceData(pLI->referencedProductOccurrence(), pListener);
    dumpReferenceData(pLI->referenceData(), pListener);
    pListener->dumpObjectId(L"local Coordinate System", pLI->localCoordinateSystem());
  }
};

class OdPrcView_Dumper : public OdPrcEntity_Dumper
{
public:
  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcViewPtr pV = pObj;
    DUMPGRAPHICS(pV, pListener)

    const OdPrcObjectIdArray &displayFilters = pV->displayFilters();
    ::dump(L"displayFilters", displayFilters, pListener);
    //plane() --> Rxobject
    pListener->dumpObjectId(L"sceneDisplayParameters", pV->sceneDisplayParameters());
    const OdPrcObjectIdArray &linkedItems = pV->linkedItems();
    ::dump(L"linkedItems", linkedItems, pListener);
    const OdPrcObjectIdArray &annotations = pV->annotations();
    ::dump(L"annotations", annotations, pListener);
    dumpUserData(pV->userData(), pListener);
    pListener->dumpBoolean(L"AnnotationView", pV->isAnnotationView());
    pListener->dumpBoolean(L"DefaultView", pV->isDefaultView());
    pListener->dumpBoolean(L"DummyPlane", pV->isDummyPlane());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcViewPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->plane());
    return subs;
  }
};

OdString entTypeToString(const OdUInt32 &entType)
{
  switch (entType)
  {
  case PRC_TYPE_ROOT:
    return OdString(L"PRC_TYPE_ROOT");
  case PRC_TYPE_ROOT_PRCBase:
    return OdString(L"PRC_TYPE_ROOT_PRCBase");
  case PRC_TYPE_ROOT_PRCBaseWithGraphics:
    return OdString(L"PRC_TYPE_ROOT_PRCBaseWithGraphics");
  case PRC_TYPE_CRV:
    return OdString(L"PRC_TYPE_CRV");
  case PRC_TYPE_SURF:
    return OdString(L"PRC_TYPE_SURF");
  case PRC_TYPE_TOPO:
    return OdString(L"PRC_TYPE_TOPO");
  case PRC_TYPE_TESS:
    return OdString(L"PRC_TYPE_TESS");
  case PRC_TYPE_MISC:
    return OdString(L"PRC_TYPE_MISC");
  case PRC_TYPE_RI:
    return OdString(L"PRC_TYPE_RI");
  case PRC_TYPE_ASM:
    return OdString(L"PRC_TYPE_ASM");
  case PRC_TYPE_MKP:
    return OdString(L"PRC_TYPE_MKP");
  case PRC_TYPE_GRAPH:
    return OdString(L"PRC_TYPE_GRAPH");
  case PRC_TYPE_MATH:
    return OdString(L"PRC_TYPE_MATH");
  case PRC_TYPE_CRV_Base:
    return OdString(L"PRC_TYPE_CRV_Base");
  case PRC_TYPE_CRV_Blend02Boundary:
    return OdString(L"PRC_TYPE_CRV_Blend02Boundary");
  case PRC_TYPE_CRV_NURBS:
    return OdString(L"PRC_TYPE_CRV_NURBS");
  case PRC_TYPE_CRV_Circle:
    return OdString(L"PRC_TYPE_CRV_Circle");
  case PRC_TYPE_CRV_Composite:
    return OdString(L"PRC_TYPE_CRV_Composite");
  case PRC_TYPE_CRV_OnSurf:
    return OdString(L"PRC_TYPE_CRV_OnSurf");
  case PRC_TYPE_CRV_Ellipse:
    return OdString(L"PRC_TYPE_CRV_Ellipse");
  case PRC_TYPE_CRV_Equation:
    return OdString(L"PRC_TYPE_CRV_Equation");
  case PRC_TYPE_CRV_Helix:
    return OdString(L"PRC_TYPE_CRV_Helix");
  case PRC_TYPE_CRV_Hyperbola:
    return OdString(L"PRC_TYPE_CRV_Hyperbola");
  case PRC_TYPE_CRV_Intersection:
    return OdString(L"PRC_TYPE_CRV_Intersection");
  case PRC_TYPE_CRV_Line:
    return OdString(L"PRC_TYPE_CRV_Line");
  case PRC_TYPE_CRV_Offset:
    return OdString(L"PRC_TYPE_CRV_Offset");
  case PRC_TYPE_CRV_Parabola:
    return OdString(L"PRC_TYPE_CRV_Parabola");
  case PRC_TYPE_CRV_PolyLine:
    return OdString(L"PRC_TYPE_CRV_PolyLine");
  case PRC_TYPE_CRV_Transform:
    return OdString(L"PRC_TYPE_CRV_Transform");
  case PRC_TYPE_SURF_Base:
    return OdString(L"PRC_TYPE_SURF_Base");
  case PRC_TYPE_SURF_Blend01:
    return OdString(L"PRC_TYPE_SURF_Blend01");
  case PRC_TYPE_SURF_Blend02:
    return OdString(L"PRC_TYPE_SURF_Blend02");
  case PRC_TYPE_SURF_Blend03:
    return OdString(L"PRC_TYPE_SURF_Blend03");
  case PRC_TYPE_SURF_NURBS:
    return OdString(L"PRC_TYPE_SURF_NURBS");
  case PRC_TYPE_SURF_Cone:
    return OdString(L"PRC_TYPE_SURF_Cone");
  case PRC_TYPE_SURF_Cylinder:
    return OdString(L"PRC_TYPE_SURF_Cylinder");
  case PRC_TYPE_SURF_Cylindrical:
    return OdString(L"PRC_TYPE_SURF_Cylindrical");
  case PRC_TYPE_SURF_Offset:
    return OdString(L"PRC_TYPE_SURF_Offset");
  case PRC_TYPE_SURF_Pipe:
    return OdString(L"PRC_TYPE_SURF_Pipe");
  case PRC_TYPE_SURF_Plane:
    return OdString(L"PRC_TYPE_SURF_Plane");
  case PRC_TYPE_SURF_Ruled:
    return OdString(L"PRC_TYPE_SURF_Ruled");
  case PRC_TYPE_SURF_Sphere:
    return OdString(L"PRC_TYPE_SURF_Sphere");
  case PRC_TYPE_SURF_Revolution:
    return OdString(L"PRC_TYPE_SURF_Revolution");
  case PRC_TYPE_SURF_Extrusion:
    return OdString(L"PRC_TYPE_SURF_Extrusion");
  case PRC_TYPE_SURF_FromCurves:
    return OdString(L"PRC_TYPE_SURF_FromCurves");
  case PRC_TYPE_SURF_Torus:
    return OdString(L"PRC_TYPE_SURF_Torus");
  case PRC_TYPE_SURF_Transform:
    return OdString(L"PRC_TYPE_SURF_Transform");
  case PRC_TYPE_SURF_Blend04:
    return OdString(L"PRC_TYPE_SURF_Blend04");
  case PRC_TYPE_TOPO_Context:
    return OdString(L"PRC_TYPE_TOPO_Context");
  case PRC_TYPE_TOPO_Item:
    return OdString(L"PRC_TYPE_TOPO_Item");
  case PRC_TYPE_TOPO_MultipleVertex:
    return OdString(L"PRC_TYPE_TOPO_MultipleVertex");
  case PRC_TYPE_TOPO_UniqueVertex:
    return OdString(L"PRC_TYPE_TOPO_UniqueVertex");
  case PRC_TYPE_TOPO_WireEdge:
    return OdString(L"PRC_TYPE_TOPO_WireEdge");
  case PRC_TYPE_TOPO_Edge:
    return OdString(L"PRC_TYPE_TOPO_Edge");
  case PRC_TYPE_TOPO_CoEdge:
    return OdString(L"PRC_TYPE_TOPO_CoEdge");
  case PRC_TYPE_TOPO_Loop:
    return OdString(L"PRC_TYPE_TOPO_Loop");
  case PRC_TYPE_TOPO_Face:
    return OdString(L"PRC_TYPE_TOPO_Face");
  case PRC_TYPE_TOPO_Shell:
    return OdString(L"PRC_TYPE_TOPO_Shell");
  case PRC_TYPE_TOPO_Connex:
    return OdString(L"PRC_TYPE_TOPO_Connex");
  case PRC_TYPE_TOPO_Body:
    return OdString(L"PRC_TYPE_TOPO_Body");
  case PRC_TYPE_TOPO_SingleWireBody:
    return OdString(L"PRC_TYPE_TOPO_SingleWireBody");
  case PRC_TYPE_TOPO_BrepData:
    return OdString(L"PRC_TYPE_TOPO_BrepData");
  case PRC_TYPE_TOPO_SingleWireBodyCompress:
    return OdString(L"PRC_TYPE_TOPO_SingleWireBodyCompress");
  case PRC_TYPE_TOPO_BrepDataCompress:
    return OdString(L"PRC_TYPE_TOPO_BrepDataCompress");
  case PRC_TYPE_TOPO_WireBody:
    return OdString(L"PRC_TYPE_TOPO_WireBody");
  case PRC_TYPE_TESS_Base:
    return OdString(L"PRC_TYPE_TESS_Base");
  case PRC_TYPE_TESS_3D:
    return OdString(L"PRC_TYPE_TESS_3D");
  case PRC_TYPE_TESS_3D_Compressed:
    return OdString(L"PRC_TYPE_TESS_3D_Compressed");
  case PRC_TYPE_TESS_Face:
    return OdString(L"PRC_TYPE_TESS_Face");
  case PRC_TYPE_TESS_3D_Wire:
    return OdString(L"PRC_TYPE_TESS_3D_Wire");
  case PRC_TYPE_TESS_Markup:
    return OdString(L"PRC_TYPE_TESS_Markup");
  case PRC_TYPE_MISC_Attribute:
    return OdString(L"PRC_TYPE_MISC_Attribute");
  case PRC_TYPE_MISC_CartesianTransformation:
    return OdString(L"PRC_TYPE_MISC_CartesianTransformation");
  case PRC_TYPE_MISC_EntityReference:
    return OdString(L"PRC_TYPE_MISC_EntityReference");
  case PRC_TYPE_MISC_MarkupLinkedItem:
    return OdString(L"PRC_TYPE_MISC_MarkupLinkedItem");
  case PRC_TYPE_MISC_ReferenceOnPRCBase:
    return OdString(L"PRC_TYPE_MISC_ReferenceOnPRCBase");
  case PRC_TYPE_MISC_ReferenceOnTopology:
    return OdString(L"PRC_TYPE_MISC_ReferenceOnTopology");
  case PRC_TYPE_MISC_GeneralTransformation:
    return OdString(L"PRC_TYPE_MISC_GeneralTransformation");
  case PRC_TYPE_RI_RepresentationItem:
    return OdString(L"PRC_TYPE_RI_RepresentationItem");
  case PRC_TYPE_RI_BrepModel:
    return OdString(L"PRC_TYPE_RI_BrepModel");
  case PRC_TYPE_RI_Curve:
    return OdString(L"PRC_TYPE_RI_Curve");
  case PRC_TYPE_RI_Direction:
    return OdString(L"PRC_TYPE_RI_Direction");
  case PRC_TYPE_RI_Plane:
    return OdString(L"PRC_TYPE_RI_Plane");
  case PRC_TYPE_RI_PointSet:
    return OdString(L"PRC_TYPE_RI_PointSet");
  case PRC_TYPE_RI_PolyBrepModel:
    return OdString(L"PRC_TYPE_RI_PolyBrepModel");
  case PRC_TYPE_RI_PolyWire:
    return OdString(L"PRC_TYPE_RI_PolyWire");
  case PRC_TYPE_RI_Set:
    return OdString(L"PRC_TYPE_RI_Set");
  case PRC_TYPE_RI_CoordinateSystem:
    return OdString(L"PRC_TYPE_RI_CoordinateSystem");
  case PRC_TYPE_ASM_ModelFile:
    return OdString(L"PRC_TYPE_ASM_ModelFile");
  case PRC_TYPE_ASM_FileStructure:
    return OdString(L"PRC_TYPE_ASM_FileStructure");
  case PRC_TYPE_ASM_FileStructureGlobals:
    return OdString(L"PRC_TYPE_ASM_FileStructureGlobals");
  case PRC_TYPE_ASM_FileStructureTree:
    return OdString(L"PRC_TYPE_ASM_FileStructureTree");
  case PRC_TYPE_ASM_FileStructureTessellation:
    return OdString(L"PRC_TYPE_ASM_FileStructureTessellation");
  case PRC_TYPE_ASM_FileStructureGeometry:
    return OdString(L"PRC_TYPE_ASM_FileStructureGeometry");
  case PRC_TYPE_ASM_FileStructureExtraGeometry:
    return OdString(L"PRC_TYPE_ASM_FileStructureExtraGeometry");
  case PRC_TYPE_ASM_ProductOccurrence:
    return OdString(L"PRC_TYPE_ASM_ProductOccurrence");
  case PRC_TYPE_ASM_PartDefinition:
    return OdString(L"PRC_TYPE_ASM_PartDefinition");
  case PRC_TYPE_ASM_Filter:
    return OdString(L"PRC_TYPE_ASM_Filter");
  case PRC_TYPE_MKP_View:
    return OdString(L"PRC_TYPE_MKP_View");
  case PRC_TYPE_MKP_Markup:
    return OdString(L"PRC_TYPE_MKP_Markup");
  case PRC_TYPE_MKP_Leader:
    return OdString(L"PRC_TYPE_MKP_Leader");
  case PRC_TYPE_MKP_AnnotationItem:
    return OdString(L"PRC_TYPE_MKP_AnnotationItem");
  case PRC_TYPE_MKP_AnnotationSet:
    return OdString(L"PRC_TYPE_MKP_AnnotationSet");
  case PRC_TYPE_MKP_AnnotationReference:
    return OdString(L"PRC_TYPE_MKP_AnnotationReference");
  case PRC_TYPE_GRAPH_Style:
    return OdString(L"PRC_TYPE_GRAPH_Style");
  case PRC_TYPE_GRAPH_Material:
    return OdString(L"PRC_TYPE_GRAPH_Material");
  case PRC_TYPE_GRAPH_Picture:
    return OdString(L"PRC_TYPE_GRAPH_Picture");
  case PRC_TYPE_GRAPH_TextureApplication:
    return OdString(L"PRC_TYPE_GRAPH_TextureApplication");
  case PRC_TYPE_GRAPH_TextureDefinition:
    return OdString(L"PRC_TYPE_GRAPH_TextureDefinition");
  case PRC_TYPE_GRAPH_TextureTransformation:
    return OdString(L"PRC_TYPE_GRAPH_TextureTransformation");
  case PRC_TYPE_GRAPH_LinePattern:
    return OdString(L"PRC_TYPE_GRAPH_LinePattern");
  case PRC_TYPE_GRAPH_FillPattern:
    return OdString(L"PRC_TYPE_GRAPH_FillPattern");
  case PRC_TYPE_GRAPH_DottingPattern:
    return OdString(L"PRC_TYPE_GRAPH_DottingPattern");
  case PRC_TYPE_GRAPH_HatchingPattern:
    return OdString(L"PRC_TYPE_GRAPH_HatchingPattern");
  case PRC_TYPE_GRAPH_SolidPattern:
    return OdString(L"PRC_TYPE_GRAPH_SolidPattern");
  case PRC_TYPE_GRAPH_VPicturePattern:
    return OdString(L"PRC_TYPE_GRAPH_VPicturePattern");
  case PRC_TYPE_GRAPH_AmbientLight:
    return OdString(L"PRC_TYPE_GRAPH_AmbientLight");
  case PRC_TYPE_GRAPH_PointLight:
    return OdString(L"PRC_TYPE_GRAPH_PointLight");
  case PRC_TYPE_GRAPH_DirectionalLight:
    return OdString(L"PRC_TYPE_GRAPH_DirectionalLight");
  case PRC_TYPE_GRAPH_SpotLight:
    return OdString(L"PRC_TYPE_GRAPH_SpotLight");
  case PRC_TYPE_GRAPH_SceneDisplayParameters:
    return OdString(L"PRC_TYPE_GRAPH_SceneDisplayParameters");
  case PRC_TYPE_GRAPH_Camera:
    return OdString(L"PRC_TYPE_GRAPH_Camera");
  case PRC_TYPE_MATH_FCT_1D:
    return OdString(L"PRC_TYPE_MATH_FCT_1D");
  case PRC_TYPE_MATH_FCT_1D_Polynom:
    return OdString(L"PRC_TYPE_MATH_FCT_1D_Polynom");
  case PRC_TYPE_MATH_FCT_1D_Trigonometric:
    return OdString(L"PRC_TYPE_MATH_FCT_1D_Trigonometric");
  case PRC_TYPE_MATH_FCT_1D_Fraction:
    return OdString(L"PRC_TYPE_MATH_FCT_1D_Fraction");
  case PRC_TYPE_MATH_FCT_1D_ArctanCos:
    return OdString(L"PRC_TYPE_MATH_FCT_1D_ArctanCos");
  case PRC_TYPE_MATH_FCT_1D_Combination:
    return OdString(L"PRC_TYPE_MATH_FCT_1D_Combination");
  case PRC_TYPE_MATH_FCT_3D:
    return OdString(L"PRC_TYPE_MATH_FCT_3D");
  case PRC_TYPE_MATH_FCT_3D_Linear:
    return OdString(L"PRC_TYPE_MATH_FCT_3D_Linear");
  case PRC_TYPE_MATH_FCT_3D_NonLinear:
    return OdString(L"PRC_TYPE_MATH_FCT_3D_NonLinear");
  default:
    OdString tmp;
    tmp.format(L"Unknown type (%d)", entType);
    return tmp;
  }
}

void dumpToken(OdUInt32Array::const_iterator &pCurToken, const OdPrcListener *pListener)
{
  OdString tmp;
  switch (*pCurToken)
  {
  case EPRCSchema_Data_Boolean:
    pListener->dumpString(L"Token", OdString(L"Data_Boolean"));
    break;
  case EPRCSchema_Data_Double:
    pListener->dumpString(L"Token", OdString(L"Data_Double"));
    break;
  case EPRCSchema_Data_Character:
    pListener->dumpString(L"Token", OdString(L"Data_Character"));
    break;
  case EPRCSchema_Data_Unsigned_Integer:
    pListener->dumpString(L"Token", OdString(L"Data_Unsigned_Integer"));
    break;
  case EPRCSchema_Data_Integer:
    pListener->dumpString(L"Token", OdString(L"Data_Integer"));
    break;
  case EPRCSchema_Data_String:
    pListener->dumpString(L"Token", OdString(L"Data_String"));
    break;
  case EPRCSchema_Parent_Type:
    pListener->dumpString(L"Token", OdString(L"Parent_Type"));
    pListener->dumpUInt32(L"Type number", *++pCurToken);
    break;
  case EPRCSchema_Vector_2D:
    pListener->dumpString(L"Token", OdString(L"Vector_2D"));
    break;
  case EPRCSchema_Vector_3D:
    pListener->dumpString(L"Token", OdString(L"Vector_3D"));
    break;
  case EPRCSchema_Extent_1D:
    pListener->dumpString(L"Token", OdString(L"Extent_1D"));
    break;
  case EPRCSchema_Extent_2D:
    pListener->dumpString(L"Token", OdString(L"Extent_2D"));
    break;
  case EPRCSchema_Extent_3D:
    pListener->dumpString(L"Token", OdString(L"Extent_3D"));
    break;
  case EPRCSchema_Ptr_Type:
    pListener->dumpString(L"Token", OdString(L"Ptr_Type"));
    pListener->dumpString(L"Ptr type", entTypeToString(*++pCurToken));
    break;
  case EPRCSchema_Ptr_Surface:
    pListener->dumpString(L"Token", OdString(L"Ptr_Surface"));
    break;
  case EPRCSchema_Ptr_Curve:
    pListener->dumpString(L"Token", OdString(L"Ptr_Curve"));
    break;
  case EPRCSchema_For:
    pListener->dumpString(L"Token", OdString(L"For"));
    break;
  case EPRCSchema_SimpleFor:
    pListener->dumpString(L"Token", OdString(L"SimpleFor"));
    break;
  case EPRCSchema_If:
    pListener->dumpString(L"Token", OdString(L"If"));
    break;
  case EPRCSchema_Else:
    pListener->dumpString(L"Token", OdString(L"Else"));
    break;
  case EPRCSchema_Block_Start:
    pListener->dumpString(L"Token", OdString(L"Block_Start"));
    if (*(pCurToken + 1) == 39)
    {
      pListener->dumpString(L"Token", L"Unknown token (39)");
      pCurToken += 2;
      if (*pCurToken == 1)
      {
        pListener->dumpString(L"Token", L"Unknown token (1)");
      }
      else
      {
        ODA_VERIFY(!"FIRST_TIME_HERE");
        tmp.format(L"Unknown token after \"39\" (%d)", *pCurToken);
        pListener->dumpString(L"Token", tmp);
      }
    }
    break;
  case EPRCSchema_Block_Version:
    pListener->dumpString(L"Token", OdString(L"Block_Version"));
    pListener->dumpUInt32(L"Version", *++pCurToken);
    break;
  case EPRCSchema_Block_End:
    pListener->dumpString(L"Token", OdString(L"Block_End"));
    break;
  case EPRCSchema_Value_Declare:
    pListener->dumpString(L"Token", OdString(L"Value_Declare"));
    tmp.format(L"value_%d", *++pCurToken);
    pListener->dumpString(L"Value declare", tmp);
    break;
  case EPRCSchema_Value_Set:
    pListener->dumpString(L"Token", OdString(L"Value_Set"));
    tmp.format(L"value_%d", *++pCurToken);
    pListener->dumpString(L"Value set", tmp);
    break;
  case EPRCSchema_Value_DeclareAndSet:
    pListener->dumpString(L"Token", OdString(L"Value_DeclareAndSet"));
    tmp.format(L"value_%d", *++pCurToken);
    pListener->dumpString(L"Declare and set", tmp);
    break;
  case EPRCSchema_Value:
    pListener->dumpString(L"Token", OdString(L"Value"));
    tmp.format(L"value_%d", *++pCurToken);
    pListener->dumpString(L"Value", tmp);
    break;
  case EPRCSchema_Value_Constant:
    pListener->dumpString(L"Token", OdString(L"Value_Constant"));
    pListener->dumpUInt32(L"Constant", *++pCurToken);
    break;
  case EPRCSchema_Value_For:
    pListener->dumpString(L"Token", OdString(L"Value_For"));
    break;
  case EPRCSchema_Value_CurveIs3D:
    pListener->dumpString(L"Token", OdString(L"Value_CurveIs3D"));
    break;
  case EPRCSchema_Operator_MULT:
    pListener->dumpString(L"Token", OdString(L"Operator_MULT"));
    break;
  case EPRCSchema_Operator_DIV:
    pListener->dumpString(L"Token", OdString(L"Operator_DIV"));
    break;
  case EPRCSchema_Operator_ADD:
    pListener->dumpString(L"Token", OdString(L"Operator_ADD"));
    break;
  case EPRCSchema_Operator_SUB:
    pListener->dumpString(L"Token", OdString(L"Operator_SUB"));
    break;
  case EPRCSchema_Operator_LT:
    pListener->dumpString(L"Token", OdString(L"Operator_LT"));
    break;
  case EPRCSchema_Operator_LE:
    pListener->dumpString(L"Token", OdString(L"Operator_LE"));
    break;
  case EPRCSchema_Operator_GT:
    pListener->dumpString(L"Token", OdString(L"Operator_GT"));
    break;
  case EPRCSchema_Operator_GE:
    pListener->dumpString(L"Token", OdString(L"Operator_GE"));
    break;
  case EPRCSchema_Operator_EQ:
    pListener->dumpString(L"Token", OdString(L"Operator_EQ"));
    break;
  case EPRCSchema_Operator_NEQ:
    pListener->dumpString(L"Token", OdString(L"Operator_NEQ"));
    break;
  default:
    tmp.format(L"Unknown token (%d)", *pCurToken);
    pListener->dumpString(L"Token", tmp);
  }
  pCurToken++;
}

class OdPrcSchema_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSchemaPtr pSchema = pObj;

    pListener->dumpUInt32(L"Number of schemas", pSchema->schemas().size());
    OdString tmp;
    for (OdUInt32 i = 0; i < pSchema->schemas().size(); i++)
    {
      pListener->dumpString(tmp.format(L"Schema type[%d]", i), entTypeToString(pSchema->schemas()[i].schema_type));
      pListener->dumpUInt32(L"Number of tokens", pSchema->schemas()[i].tokens.size());
      OdUInt32Array::const_iterator pCurToken = pSchema->schemas()[i].tokens.begin();
      while (pCurToken != pSchema->schemas()[i].tokens.end())
      {
        dumpToken(pCurToken, pListener);
      }
    }
  }
};

class OdPrcFile_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
     const OdPrcFilePtr pFile = pObj;

     pListener->dumpUInt32(L"Number of file structures", pFile->fileStructures().size());
     //PRCHeader
     dumpUncompressedFiles(pFile->uncompressedFiles(), pListener);
     pListener->dumpUniqueId(L"Application Id", pFile->applicationId());
     pListener->dumpUniqueId(L"File Structure Id", pFile->fileStructureId());
     pListener->dumpUInt32(L"Minimal version for read", pFile->minimalVersionForRead());
     pListener->dumpUInt32(L"Authoring version", pFile->authoringVersion());
     //Schema
     pListener->dumpUInt32(L"Number of file schemas", pFile->schema().schemas().size());
     //ModelFileData --> RxObject
     //for (i=0;i<number_of_file_structures;i++)
       //FileStructure [i] --> RxObject
     pListener->dumpUInt32(L"Number of isolines", pFile->getNumberOfIsolines());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFilePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->fileStructures().size(); ++f)
    {
      subs.push_back(pBD->fileStructures()[f]);
    }
    return subs;
  }
};

class OdPrcModelFileData_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcModelFileDataPtr pMFD = pObj;
    DUMPBASE(pMFD, pListener)

    //PrcUnit
    dumpUnit(pMFD->unit(), pListener);
    pListener->dumpUInt32(L"Number of start product occurrences", pMFD->getStartRootOccurrences().size());
    const OdPrcObjectIdArray &startRootOccurrences = pMFD->getStartRootOccurrences();
    ::dump(L"startRootOccurrences", startRootOccurrences, pListener);
    //UserData
    dumpUserData(pMFD->userData(), pListener);
  }
};

class OdPrcFileStructure_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFileStructurePtr pFS = pObj;

    // Header section
    dumpUncompressedFiles(pFS->uncompressedFiles(),pListener);
    pListener->dumpUniqueId(L"Application Id", pFS->applicationId());
    pListener->dumpUniqueId(L"FileStructure Id", pFS->fileStructureId());
    pListener->dumpUInt32(L"Minimal version for read", pFS->minimalVersionForRead());
    pListener->dumpUInt32(L"Authoring version", pFS->authoringVersion());
    // Globals section
    //Schema
    pListener->dumpUInt32(L"Number of file schemas", pFS->schema().schemas().size());
    //FileStructureGlobals --> RxObject
    // Tree section
    //FileStructureTree --> RxObject
    // Tessellation section
    //FileStructureTessellation --> RxObject
    // Geometry section
    //FileStructureGeometry --> RxObject
    // Extra geometry section
    //FileStructureExtraGeometry --> RxObject
  }
  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFileStructurePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(&pBD->schema());
    subs.push_back(&pBD->fileStructureGlobals());
    subs.push_back(&pBD->fileStructureTree());
    subs.push_back(&pBD->fileStructureTessellation());
    subs.push_back(&pBD->fileStructureGeometry());

    return subs;
  }
};

void dumpColor(const OdPrcListener *pListener, OdUInt32 index, const OdPrcRgbColor &color, const OdString & name = OdString())
{
  OdString key;
  if (name.isEmpty())
  {
    key.format(L"RGB[%d]", index);
  }
  else
  {
    key.format(L"%s,RGB[%d]", name.c_str(), index);
  }
  OdString value;
  value.format(L"%g %g %g", color.r(), color.g(), color.b());
  pListener->dumpString(key.c_str(), value.c_str());
}

void dumpColor(const OdPrcListener *pListener, OdPrcColorIndex index, const OdPrcRgbColorArray & colorArray, const OdString & name = OdString())
{
  if (index.isInit())
  {
    dumpColor(pListener, index, colorArray[index], name);
  }
  else
  {
    pListener->dumpString(name.c_str(), L"not used");
  }
}

void dumpFontKeysSameFont(const OdPrcFontKeysSameFont &pFKSF, const OdPrcListener *pListener)
{
  OdString sBuf;
  pListener->dumpString(L"Font Name", pFKSF.fontName());
  pListener->dumpUInt32(L"Char set", pFKSF.charSet());
  for (OdUInt32 i = 0; i < pFKSF.fontKeys().size(); i++)
  {
    pListener->dumpString(sBuf.format(L"FontKey[%d]", i), "");
    pListener->dumpUInt32(L"Attributes", pFKSF.fontKeys()[i].attributes);
    pListener->dumpUInt32(L"Font Size", pFKSF.fontKeys()[i].font_size);
  }
}

void dumpMarkupSerializationHelper(const OdPrcMarkupSerializationHelper &pMSH, const OdPrcListener *pListener)
{
  OdString sBuf;
  for (OdUInt32 i = 0; i < pMSH.fontKeysSameFont().size(); i++)
  {
    pListener->dumpString(sBuf.format(L"OdPrcFontKeysSameFont[%d]", i), "");
    dumpFontKeysSameFont(pMSH.fontKeysSameFont()[i], pListener);
  }
  pListener->dumpString(L"Default Font Family Name", pMSH.defaultFontFamilyName());
}

class OdPrcFileStructureGlobals_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFileStructureGlobalsPtr pFSG = pObj;
    DUMPBASE(pFSG, pListener)

    //UserData
    dumpUserData(pFSG->userData(), pListener);
    //PicturesArray --> RxObject
    //RGBColor
    for (OdUInt32 i = 0; i < pFSG->colors().size(); i++)
    {
      dumpColor(pListener, i, pFSG->colors()[i]);
    }
    //MarkupSerializationHelper
    dumpMarkupSerializationHelper(pFSG->markupSerializationHelper(), pListener);
    pListener->dumpDouble(L"tessellation Angle Degree", pFSG->tessellationAngleDegree());
    pListener->dumpDouble(L"tessellation Chord Height Ratio", pFSG->tessellationChordHeightRatio());
    const OdPrcObjectIdArray &category1LineStyles = pFSG->category1LineStyles();
    ::dump(L"category1LineStyles", category1LineStyles, pListener);
    const OdPrcObjectIdArray &linePatterns = pFSG->linePatterns();
    ::dump(L"linePatterns", linePatterns, pListener);
    const OdPrcObjectIdArray &materials = pFSG->materials();
    ::dump(L"materials", materials, pListener);
    const OdPrcObjectIdArray &textureDefinitions = pFSG->textureDefinitions();
    ::dump(L"textureDefinitions", textureDefinitions, pListener);
    const OdPrcObjectIdArray &fillPatterns = pFSG->fillPatterns();
    ::dump(L"fillPatterns", fillPatterns, pListener);
    const OdPrcObjectIdArray &coordinateSystem = pFSG->coordinateSystem();
    ::dump(L"coordinateSystem", coordinateSystem, pListener);
    const OdPrcObjectIdArray &referencedFileStructuresID = pFSG->referencedFileStructuresID();
    ::dump(L"referencedFileStructuresID", referencedFileStructuresID, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFileStructureGlobalsPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->pictures().size(); ++f)
    {
      subs.push_back(pBD->pictures()[f]);
    }
    return subs;
  }
};

class OdPrcCategory1LineStyle_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCategory1LineStylePtr pC1LS = pObj;
    DUMPREFERENCEDBASE(pC1LS, pListener);
    if (!pC1LS->getMaterialID().isNull())
    {
      pListener->dumpObjectId(L"MaterialID", pC1LS->getMaterialID());
    }
    else if (pC1LS->getColor().isInit())
    {
      pListener->dumpUInt32(L"ColorIdx", pC1LS->getColor() * 3 + 1);
      OdPrcRgbColor color(pC1LS->getTrueColor());
      pListener->dumpString(L"color", OdString().format(L"%g %g %g", color.r(), color.g(), color.b()).c_str());
    }

    pListener->dumpUInt32(L"PictureIdx", pC1LS->getPictureIdx());
    pListener->dumpDouble(L"lineWidth", pC1LS->lineWidth());
    pListener->dumpObjectId(L"LinePatternID", pC1LS->getLinePatternID());

    OdInt8 value;
    if (pC1LS->getTransparency(value))
    {
      pListener->dumpInt8(L"Transparency", value);
    }
    else
    {
      pListener->dumpString(L"Transparency", L"-");
    }
    if (pC1LS->getAdditionalData1(value))
    {
      pListener->dumpInt8(L"AdditionalData1", value);
    }
    else
    {
      pListener->dumpString(L"AdditionalData1", L"-");
    }
    if (pC1LS->getAdditionalData2(value))
    {
      pListener->dumpInt8(L"AdditionalData2", value);
    }
    else
    {
      pListener->dumpString(L"AdditionalData2", L"-");
    }
    if (pC1LS->getAdditionalData3(value))
    {
      pListener->dumpInt8(L"AdditionalData3", value);
    }
    else
    {
      pListener->dumpString(L"AdditionalData3", L"-");
    }
  }
};

class OdPrcLinePattern_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcLinePatternPtr pLP = pObj;
    DUMPREFERENCEDBASE(pLP, pListener)

    for (OdUInt32 i = 0; i < pLP->length().size(); i++)
    {
      pListener->dumpDouble(L"length", pLP->length()[i]);
    }
    pListener->dumpDouble(L"phase", pLP->phase());
    pListener->dumpBoolean(L"RealLength", pLP->isRealLength());
  }
};

class OdPrcMaterialGeneric_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMaterialGenericPtr pMG = pObj;
    DUMPREFERENCEDBASE(pMG, pListener)

    OdPrcObjectId ppid = pMG->id();
    OdDbBaseDatabase *pDb = ppid.database();
    ODA_ASSERT(pDb);
    OdPrcFileStructure *databaseFS = (OdPrcFileStructure *)pDb;
    const OdPrcRgbColorArray & color = databaseFS->fileStructureGlobals().colors();
    dumpColor(pListener, pMG->ambient(), color, L"ambient");
    dumpColor(pListener, pMG->diffuse(), color, L"diffuse");
    dumpColor(pListener, pMG->emissive(), color, L"emissive");
    dumpColor(pListener, pMG->specular(), color, L"specular");
    pListener->dumpDouble(L"shininess", pMG->shininess());
    pListener->dumpDouble(L"ambientAlpha", pMG->ambientAlpha());
    pListener->dumpDouble(L"diffuseAlpha", pMG->diffuseAlpha());
    pListener->dumpDouble(L"emissiveAlpha", pMG->emissiveAlpha());
    pListener->dumpDouble(L"specularAlpha", pMG->specularAlpha());
  }
};

class OdPrcTextureApplication_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTextureApplicationPtr pTA = pObj;
    DUMPREFERENCEDBASE(pTA, pListener)

    pListener->dumpObjectId(L"TextureDefinitionID", pTA->getTextureDefinitionID());
    pListener->dumpObjectId(L"MaterialGenericID", pTA->getMaterialGenericID());
    pListener->dumpObjectId(L"NextTextureID", pTA->getNextTextureID());
    pListener->dumpUInt32(L"uvCoordinatesIndex", pTA->uvCoordinatesIndex());
  }
};

void dumpPrcTextureMappingType(const OdPrcTextureMappingType &pTMT, const OdPrcListener *pListener)
{
  ::dump(L"transformation", pTMT.cartesianTransformation3d(), pListener);
  pListener->dumpUInt8(L"EPRCTextureMappingType", pTMT.eMappingType()); //enum EPRCTextureMappingType?
  pListener->dumpUInt32(L"MappingOperator", pTMT.eMappingOperator());
}

void dumpPrcTextureTransformation(const OdPrcTextureTransformation &pTT, const OdPrcListener *pListener)
{
  const OdPrcTransformation2d trans = pTT.matrixTransformation();
  ::dump(L"transformation", &trans, pListener);
  pListener->dumpBoolean(L"textureFlipS", pTT.textureFlipS());
  pListener->dumpBoolean(L"textureFlipT", pTT.textureFlipT());
  pListener->dumpUInt32(L"prcType", pTT.prcType());
}

class OdPrcTextureDefinition_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTextureDefinitionPtr pTD = pObj;
    DUMPREFERENCEDBASE(pTD, pListener)

    OdString tmp;
    for (OdUInt32 i = 0; i < pTD->textureMappingAttributesIntensities().size(); i++)
    {
      pListener->dumpDouble(tmp.format(L"textureMappingAttributesIntensities[%d]", i), pTD->textureMappingAttributesIntensities()[i]);
    }
    for (OdUInt32 i = 0; i < pTD->textureMappingAttributesComponents().size(); ++i)
    {
      pListener->dumpUInt8(tmp.format(L"textureMappingAttributesComponents[%d]", i), pTD->textureMappingAttributesComponents()[i]);
    }
    
    dumpPrcTextureMappingType(pTD->textureMappingType(), pListener);
    pListener->dumpInt8(L"textureDimension", pTD->textureDimension());
    pListener->dumpInt8(L"textureApplyingMode", pTD->textureApplyingMode());
    pListener->dumpUInt32(L"textureMappingAttributes", pTD->textureMappingAttributes());
    pListener->dumpUInt32(L"textureFunction", pTD->textureFunction());
    pListener->dumpUInt32(L"blendSrcRgb", pTD->blendSrcRgb());
    pListener->dumpUInt32(L"blendDstRgb", pTD->blendDstRgb());
    pListener->dumpUInt32(L"blendSrcAlpha", pTD->blendSrcAlpha());
    pListener->dumpUInt32(L"blendDstAlpha", pTD->blendDstAlpha());
    pListener->dumpUInt32(L"alphaTest", pTD->alphaTest());
    pListener->dumpUInt32(L"textureWrappingModeS", pTD->textureWrappingModeS());
    pListener->dumpUInt32(L"textureWrappingModeT", pTD->textureWrappingModeT());
    pListener->dumpUInt32(L"textureWrappingModeR", pTD->textureWrappingModeR());
    pListener->dumpUInt32(L"red", pTD->red());
    pListener->dumpUInt32(L"green", pTD->green());
    pListener->dumpUInt32(L"blue", pTD->blue());
    pListener->dumpUInt32(L"alpha", pTD->alpha());
    pListener->dumpUInt32(L"alphaTestReference", pTD->alphaTestReference());
    pListener->dumpBoolean(L"TextureTransformation", pTD->hasTextureTransformation());
    if (pTD->hasTextureTransformation())
    {
      dumpPrcTextureTransformation(pTD->textureTransformation(), pListener);
    }
  }
  virtual OdRxObjectPtrArray subElements(const OdRxObject *pObj) const
  {
    const OdPrcTextureDefinitionPtr pTD = pObj;
    OdRxObjectPtrArray subs;
    subs.push_back(pTD->picture());
    return subs;
  }
};

class OdPrcDottingPattern_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcDottingPatternPtr pDP = pObj;
    DUMPREFERENCEDBASE(pDP, pListener)

    pListener->dumpUInt32(L"colorIndex", pDP->color().isInit() ? pDP->color()*3+1 : 0);
    pListener->dumpUInt32(L"pitch", pDP->pitch());
    pListener->dumpBoolean(L"zigzag", pDP->zigzag());
  }
};

void dumpHatchingPatternLine(const OdPrcHatchingPatternLine &pHPL, const OdPrcListener *pListener)
{
  ::dumpGeVector2d(L"offset", pHPL.offset(),pListener);
  ::dumpGePoint2d(L"start", pHPL.start(),pListener);
  dumpLineAttr(pHPL.style(), pListener);
  pListener->dumpDouble(L"angle", pHPL.angle());
}

class OdPrcHatchingPattern_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcHatchingPatternPtr pHP = pObj;
    DUMPREFERENCEDBASE(pHP, pListener)

    for (OdUInt32 i = 0; i < pHP->hatchingPatternLine().size(); i++)
    {
      dumpHatchingPatternLine(pHP->hatchingPatternLine()[i], pListener);
    }
  }
};

class OdPrcSolidPattern_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSolidPatternPtr pSP = pObj;
    DUMPREFERENCEDBASE(pSP, pListener)

    if (pSP->isMaterial())
    {
      pListener->dumpUInt32(L"colorIndex", (OdUInt32)(OdUInt64)pSP->material().getHandle() + 1);
      pListener->dumpBoolean(L"isMaterial", true);
    }
    else
    {
      pListener->dumpUInt32(L"colorIndex", pSP->color()*3 + 1);
      pListener->dumpBoolean(L"isMaterial", false);
    }
  }
};

class OdPrcPicturePattern_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPicturePatternPtr pPP = pObj;
    DUMPREFERENCEDBASE(pPP, pListener)

    dumpGeVector2d(L"sizeOfVpattern", pPP->sizeOfVpattern(), pListener);
    //OdPrcMarkupTessPtr &tessellationData() 
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcPicturePatternPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->tessellationData());
    return subs;
  }
};

class OdPrcPicture_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPicturePtr pP= pObj;
    DUMPBASE(pP, pListener)

    pListener->dumpInt32(L"Format", pP->format());
    pListener->dumpUInt32(L"Pixel Height", pP->pixelHeight());
    pListener->dumpUInt32(L"Pixel Width", pP->pixelWidth());
    pListener->dumpUInt32(L"Uncompressed File Index", pP->uncompressedFileIndex());
  }
};

class OdPrcFileStructureTree_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFileStructureTreePtr pFST = pObj;
    DUMPBASE(pFST, pListener)

    //Part Definition
    for (OdUInt32 i = 0; i < pFST->partDefinition().size(); i++)
    {
      pListener->dumpObjectId(L"Object ID", pFST->partDefinition()[i]);
    }
    //Product Occurrence --> RxObject
    //Internal Data --> RxObject
    //User Data
    dumpUserData(pFST->userData(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFileStructureTreePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->productOccurrence().size(); ++f)
    {
      subs.push_back(pBD->productOccurrence()[f]);
    }
    return subs;
  }
};

void dumpReferencesOfProductOccurrence(const OdPrcReferencesOfProductOccurrence &pROPO, const OdPrcListener *pListener)
{
  pListener->dumpObjectId(L"ExternalDataID", pROPO.getExternalDataID());
  pListener->dumpObjectId(L"PrototypeID", pROPO.getPrototypeID());
  pListener->dumpObjectId(L"PartDefinitionID", pROPO.getCorrespondingPartDefinition());
  ::dump(L"SonProductOccurrence", pROPO.getSonProductOccurrences(), pListener);
}

void dumpProductInformation(const OdPrcProductInformation &pPI, const OdPrcListener *pListener)
{
  dumpUnit(pPI.unitInformation(), pListener);
  pListener->dumpInt8(L"Product Information Flags", pPI.productInformationFlags());
  pListener->dumpUInt32(L"Product Load Status", pPI.productLoadStatus());
}

void dumpMarkups(const OdPrcMarkups &pM, const OdPrcListener *pListener)
{
  ::dump(L"annotationEntity", pM.annotationEntities(), pListener);
  ::dump(L"markup", pM.markups(), pListener);
  ::dump(L"leader", pM.leaders(), pListener);
  ::dump(L"linkedItem", pM.linkedItem(), pListener);
}

class OdPrcProductOccurrence_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcProductOccurrencePtr pPO = pObj;
    DUMPGRAPHICS(pPO, pListener)
    const OdPrcTransformation3d *location = pPO->location();
    ::dump(L"location", pPO->location(), pListener);
    //referencesOfProductOccurrence
    dumpReferencesOfProductOccurrence(pPO->referencesOfProductOccurrence(), pListener);
    //productInformation
    dumpProductInformation(pPO->productInformation(), pListener);

    ::dump(L"entityReference", pPO->entityReference(), pListener);
    dumpMarkups(pPO->markups(), pListener);
    ::dump(L"annotationView", pPO->annotationViews(), pListener);
    ::dump(L"displayFilter", pPO->displayFilter(), pListener);
    ::dump(L"entityFilter", pPO->entityFilter(), pListener);
    ::dump(L"sceneDisplayParameters", pPO->sceneDisplayParameters(), pListener);

    //userData
    dumpUserData(pPO->userData(), pListener);
    pListener->dumpUInt32(L"Product Behavior", pPO->productBehaviour());
  }
};

class OdPrcReference_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcReferencePtr pR = pObj;
    DUMPGRAPHICS(pR, pListener)

    dumpUserData(pR->userData(), pListener);
    dumpReferenceData(pR->referenceData(), pListener);
    pListener->dumpObjectId(L"localCoordinateSystem", pR->localCoordinateSystem());
  }
};

void dumpContentEntityFilterItems(const OdPrcContentEntityFilterItems &pCEFI, const OdPrcListener *pListener)
{
  const OdPrcObjectIdArray &entities = pCEFI.entities();
  ::dump(L"entities", entities, pListener);
  pListener->dumpBoolean(L"Inclusive entities", pCEFI.isInclusive());
}

void dumpContentLayerFilterItems(const OdPrcContentLayerFilterItems &pCLFI, const OdPrcListener *pListener)
{
  for (OdUInt32 i = 0; i < pCLFI.layerIndex().size(); i++)
  {
    pListener->dumpUInt32(L"layer Index", pCLFI.layerIndex()[i]);
  }
  pListener->dumpBoolean(L"Inclusive layers", pCLFI.isInclusive());
}

class OdPrcFilter_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFilterPtr pF = pObj;
    DUMPREFERENCEDBASE(pF, pListener)

    dumpUserData(pF->userData(), pListener);
    dumpContentEntityFilterItems(pF->contentEntityFilterItems(), pListener);
    dumpContentLayerFilterItems(pF->contentLayerFilterItems(), pListener);
    pListener->dumpBoolean(L"Active", pF->isActive());
  }
};

class OdPrcSceneDisplayParameters_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSceneDisplayParametersPtr pSDP = pObj;
    DUMPREFERENCEDBASE(pSDP, pListener)

    for (OdUInt32 i = 0; i < pSDP->types().size(); i++)
    {
      pListener->dumpUInt32(L"types", pSDP->types()[i]);
    }
    dumpGePoint3d(L"rotationCenter", pSDP->rotationCenter(), pListener);
    const OdPrcObjectIdArray &ambientLight = pSDP->ambientLight();
    ::dump(L"ambientLight", ambientLight, pListener);
    pListener->dumpObjectId(L"camera", pSDP->camera());
    for (OdUInt32 i = 0; i < pSDP->defaultStylesPerType().size(); i++)
    {
      dumpLineAttr(pSDP->defaultStylesPerType()[i], pListener);
    }
    dumpLineAttr(pSDP->defaultStyle(), pListener);
    dumpLineAttr(pSDP->backgroundStyle(), pListener);
    pListener->dumpBoolean(L"Active", pSDP->isActive());
    pListener->dumpBoolean(L"Absolute", pSDP->isAbsolute());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcSceneDisplayParametersPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->clippingPlanes().size(); ++f)
    {
      subs.push_back(pBD->clippingPlanes()[f]);
    }
    return subs;
  }
};

class OdPrcFileStructureInternalData_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFileStructureInternalDataPtr pFSID = pObj;
    DUMPBASE(pFSID, pListener)

    pListener->dumpObjectId(L"Object ID", pFSID->getRootProductOccurrenceID());
  }
};

class OdPrcFileStructureTessellation_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFileStructureTessellationPtr pFST = pObj;
    DUMPBASE(pFST, pListener)
    //tessellations --> RxObject
    //userData
    dumpUserData(pFST->userData(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFileStructureTessellationPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->tessellations().size(); ++f)
    {
      subs.push_back(pBD->tessellations()[f]);
    }
    return subs;
  }
};

void dumpArrayRgba(const OdPrcArrayRgba &pARgba, const OdPrcListener *pListener)
{
  pListener->dumpBoolean(L"Is RGBA", pARgba.isRgba());

  ODA_ASSERT(pARgba.colors().size() % (pARgba.isRgba() ? 4 : 3) == 0);
  OdString tmpKey;
  OdAnsiString tmpValue;
  if (pARgba.isRgba())
  {
    for (OdUInt32 i = 0; i < pARgba.colors().size(); i+=4)
    {
      pListener->dumpAnsiString(tmpKey.format(L"Colors[%d-%d]", i, i + 3), tmpValue.format("(%u; %u; %u; %u)", pARgba.colors()[i], pARgba.colors()[i+1], pARgba.colors()[i+2], pARgba.colors()[i+3]));
    }
  }
  else
  {
    for (OdUInt32 i = 0; i < pARgba.colors().size(); i+=3)
    {
      pListener->dumpAnsiString(tmpKey.format(L"Colors[%d-%d]", i, i + 2), tmpValue.format("(%u; %u; %u)", pARgba.colors()[i], pARgba.colors()[i+1], pARgba.colors()[i+2]));
    }
  }
}

void dumpTessFace(const OdPrcTessFace &pTF, const OdPrcListener *pListener)
{
  OdString tmp;
  for (OdUInt32 i = 0; i < pTF.sizesWire().size(); i++)
  {
    pListener->dumpUInt32(tmp.format(L"Sizes Wire[%d]", i), pTF.sizesWire()[i]);
  }
  for (OdUInt32 i = 0; i < pTF.sizesTriangulated().size(); i++)
  {
    pListener->dumpUInt32(tmp.format(L"Sizes Triangulated[%d]", i), pTF.sizesTriangulated()[i]);
  }
  for (OdUInt32 i = 0; i < pTF.lineAttributes().size(); i++)
  {
    pListener->dumpObjectId(tmp.format(L"LineStyleID[%d]", i), pTF.lineAttributes()[i]);
  }
  dumpArrayRgba(pTF.arrayRGBA(), pListener);
  pListener->dumpUInt32(L"Start Wire", pTF.startWire());
  pListener->dumpUInt32(L"Used Entities Flag", pTF.usedEntitiesFlag());
  pListener->dumpUInt32(L"Start Triangulated", pTF.startTriangulated());
  pListener->dumpUInt32(L"Number Of Texture Coordinate Indexes", pTF.numberOfTextureCoordinateIndexes());
  pListener->dumpUInt32(L"Behavior", pTF.behaviour());
  pListener->dumpBoolean(L"Has Vertex Colors", pTF.hasVertexColors());
  pListener->dumpBoolean(L"Is Optimized", pTF.bOptimised());
}

class OdPrc3dTess_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrc3dTessPtr p3dT = pObj;
    pListener->dumpInt8(L"Normals Recalculation Flags", p3dT->normalsRecalculationFlags());
    pListener->dumpDouble(L"Crease Angle", p3dT->creaseAngle());
    pListener->dumpBoolean(L"Has Faces", p3dT->hasFaces());
    pListener->dumpBoolean(L"Has Loops", p3dT->hasLoops());
    pListener->dumpBoolean(L"Must Recalculate Normals", p3dT->mustRecalculateNormals());
    pListener->dumpBoolean(L"Is Calculated", p3dT->isCalculated());

    OdString tmp;
    OdAnsiString tmpValue;
    for (OdUInt32 i = 0; i < p3dT->wireIndex().size(); ++i)
    {
      pListener->dumpUInt32(tmp.format(L"Wire Index[%d]", i), p3dT->wireIndex()[i]);
    }
    for (OdUInt32 i = 0; i < p3dT->triangulatedIndex().size(); ++i)
    {
      pListener->dumpUInt32(tmp.format(L"Triangulated Index[%d]", i), p3dT->triangulatedIndex()[i]);
    }

    ODA_ASSERT(p3dT->normalCoordinate().size() % 3 == 0);
    for (OdUInt32 i = 0; i < p3dT->normalCoordinate().size(); i+=3)
    {
      pListener->dumpAnsiString(tmp.format(L"Normal Coordinate[%d-%d]", i, i + 2), tmpValue.format("(%0.16f; %0.16f; %.16f)", p3dT->normalCoordinate()[i], p3dT->normalCoordinate()[i+1], p3dT->normalCoordinate()[i+2]));
    }

    ODA_ASSERT(p3dT->textureCoordinate().size() % 2 == 0);
    for (OdUInt32 i = 0; i < p3dT->textureCoordinate().size(); i+=2)
    {
      pListener->dumpAnsiString(tmp.format(L"Texture Coordinate[%d-%d]", i, i + 1), tmpValue.format("(%0.16f; %0.16f)", p3dT->textureCoordinate()[i], p3dT->textureCoordinate()[i+1]));
    }
    
    ODA_ASSERT(p3dT->coordinates().size() % 3 == 0);
    for (OdUInt32 i = 0; i < p3dT->coordinates().size(); i+=3)
    {
      pListener->dumpAnsiString(tmp.format(L"Coordinates[%d-%d]", i, i + 2), tmpValue.format("(%0.16f; %0.16f; %.16f)", p3dT->coordinates()[i], p3dT->coordinates()[i+1], p3dT->coordinates()[i+2]));
    }
    
    for (OdUInt32 i = 0; i < p3dT->faceTessellation().size(); ++i)
    {
      pListener->dumpString(tmp.format(L"OdPrcTessFace[%d]", i), "");
      dumpTessFace(p3dT->faceTessellation()[i], pListener);
    }
  }
};

class OdPrc3dWireTess_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrc3dWireTessPtr p3dWT = pObj;
    OdString tmp;
    for (OdUInt32 i = 0; i < p3dWT->wireIndexes().size(); i++)
    {
      pListener->dumpUInt32(tmp.format(L"Wire Indexes[%d]", i), p3dWT->wireIndexes()[i]);
    }
    dumpArrayRgba(p3dWT->arrayRGBA(), pListener);
    for (OdUInt32 i = 0; i < p3dWT->coordinates().size(); i++)
    {
      pListener->dumpDouble(tmp.format(L"Coordinates[%d]", i), p3dWT->coordinates()[i]);
    }
    pListener->dumpBoolean(L"Is Segment Color", p3dWT->isSegmentColor());
    pListener->dumpBoolean(L"Is Calculated", p3dWT->isCalculated());
  }
};

class OdPrcMarkupTess_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMarkupTessPtr pMT = pObj;
    OdString tmp;
    for (OdUInt32 i = 0; i < pMT->text().size(); i++)
    {
      pListener->dumpString(tmp.format(L"Text[%d]", i), pMT->text()[i]);
    }
    for (OdUInt32 i = 0; i < pMT->codes().size(); i++)
    {
      pListener->dumpUInt32(tmp.format(L"Codes[%d]", i), pMT->codes()[i]);
    }
    for (OdUInt32 i = 0; i < pMT->coordinates().size(); i++)
    {
      pListener->dumpDouble(tmp.format(L"Coordinates[%d]", i), pMT->coordinates()[i]);
    }
    pListener->dumpString(L"Label",pMT->label());
    pListener->dumpInt8(L"Behavior", pMT->behaviour());
  }
};

#ifdef DUMP_COMPRESSION

void dumpBinaryTextureData(const OdPrcBinaryTextureData pBTD, const OdPrcListener *pListener)
{
  OdString tmp;
  for (OdUInt32 i = 0; i < pBTD.textureBinaryData().size(); ++i)
  {
    pListener->dumpUInt32(tmp.format(L"Texture Binary Data[%d]", i), pBTD.textureBinaryData()[i]);
  }
  pListener->dumpUInt32(L"Last Integer Used Bit Number", pBTD.lastIntegerUsedBitNumber());
}
 
void dumpCompressedTextureParameter(const OdPrcCompressedTextureParameter pCTP, const OdPrcListener *pListener)
{
  OdString tmp;
  for (OdUInt32 i = 0; i < pCTP.referenceArray().size(); ++i)
  {
    pListener->dumpUInt32(tmp.format(L"Reference[%d]", i), pCTP.referenceArray()[i]);
  }
  for (OdUInt32 i = 0; i < pCTP.uvParameterArray().size(); ++i)
  {
    pListener->dumpUInt32(tmp.format(L"UV Parameter[%d]", i), pCTP.uvParameterArray()[i]);
  }
  dumpBinaryTextureData(pCTP.BinaryTextureData(), pListener);
}

class OdPrcHighlyCompressed3dTess_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcHighlyCompressed3dTessPtr pHC3dT = pObj;

    OdString tmp;
    for (OdUInt32 i = 0; i < pHC3dT->pointsArray().size(); ++i)
    {
      pListener->dumpInt32(tmp.format(L"Points[%d]", i), pHC3dT->pointsArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->edgeStatusArray().size(); ++i)
    {
      pListener->dumpInt8(tmp.format(L"Edge Status[%d]", i), pHC3dT->edgeStatusArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->pointReferenceArray().size(); ++i)
    {
      pListener->dumpInt32(tmp.format(L"Point Reference[%d]", i), pHC3dT->pointReferenceArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->pointIsReferencedArray().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Point Is Reference[%d]", i), pHC3dT->pointIsReferencedArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->normalAngleArray().size(); ++i)
    {
      pListener->dumpUInt16(tmp.format(L"Normal Angle[%d]", i), pHC3dT->normalAngleArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->triangleFaceArray().size(); ++i)
    {
      pListener->dumpInt32(tmp.format(L"Triangle Face[%d]", i), pHC3dT->triangleFaceArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->pointColorArray().size(); ++i)
    {
      pListener->dumpInt8(tmp.format(L"Point Color[%d]", i), pHC3dT->pointColorArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->normalIsReversed().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Normal Is Reversed[%d]", i), pHC3dT->normalIsReversed()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->normalBinaryData().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Normal Binary Data[%d]", i), pHC3dT->normalBinaryData()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->isFacePlanar().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Is Face Planar[%d]", i), pHC3dT->isFacePlanar()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->isPointColorOnFace().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Is Point Color On Face[%d]", i), pHC3dT->isPointColorOnFace()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->lineAttributeArray().size(); ++i)
    {
      pListener->dumpObjectId(tmp.format(L"Line Attribute[%d]", i), pHC3dT->lineAttributeArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->isMultipleLineAttributeOnFace().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Is Multiple Line Attribute On Face[%d]", i), pHC3dT->isMultipleLineAttributeOnFace()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->behavioursArray().size(); ++i)
    {
      pListener->dumpInt8(tmp.format(L"Behaviours[%d]", i), pHC3dT->behavioursArray()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->faceHasTexture().size(); ++i)
    {
      pListener->dumpBoolean(tmp.format(L"Face Has Texture[%d]", i), pHC3dT->faceHasTexture()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->characterArrayCompressed().size(); ++i)
    {
      pListener->dumpUInt32(tmp.format(L"Character Compressed[%d]", i), pHC3dT->characterArrayCompressed()[i]);
    }
    for (OdUInt32 i = 0; i < pHC3dT->characterArray().size(); ++i)
    {
      pListener->dumpInt8(tmp.format(L"Character[%d]", i), pHC3dT->characterArray()[i]);
    }
    dumpCompressedTextureParameter(pHC3dT->CompressedTextureParameter(), pListener);
    pListener->dumpInt8(L"Normal Angle Number Of Bits",pHC3dT->normalAngleNumberOfBits());
    pListener->dumpDouble(L"Crease Angle",pHC3dT->creaseAngle());
    pListener->dumpDouble(L"Tolerance",pHC3dT->tolerance());
    pListener->dumpBoolean(L"Is Calculated",pHC3dT->isCalculated());
    pListener->dumpBoolean(L"Has Faces",pHC3dT->hasFaces());
    pListener->dumpBoolean(L"Must Recalculate Normals",pHC3dT->mustRecalculateNormals());
    pListener->dumpBoolean(L"Is Point Color",pHC3dT->isPointColor());
    pListener->dumpBoolean(L"Is Multiple Line Attribute",pHC3dT->isMultipleLineAttribute());
    pListener->dumpBoolean(L"No Texture",pHC3dT->noTexture());
    pListener->dumpBoolean(L"All Faces Have Texture",pHC3dT->allFacesHaveTexture());
    pListener->dumpBoolean(L"Has Behaviours",pHC3dT->hasBehaviours());

    pListener->dumpFloat(L"Origin.x", pHC3dT->origin().x);
    pListener->dumpFloat(L"Origin.y", pHC3dT->origin().y);
    pListener->dumpFloat(L"Origin.z", pHC3dT->origin().z);
  }
};
#endif

class OdPrcFileStructureGeometry_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFileStructureGeometryPtr pFSGeom = pObj;
    DUMPBASE(pFSGeom, pListener)

    //dumpFileStructureExactGeometry
    const OdPrcFileStructureExactGeometry &pFSEG = pFSGeom->fileStructureExactGeometry();
    OdString tmp;
    for (OdUInt32 i = 0; i < pFSEG.topologicalContext().size(); i++)
    {
      ::dump(tmp.format(L"Context[%d].body", i), pFSEG.topologicalContext()[i]->bodies(), pListener);
    }

    //User Data
    dumpUserData(pFSGeom->userData(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    OdRxObjectPtrArray subs;

    const OdPrcFileStructureGeometryPtr pFSGeom = pObj;

    const OdPrcFileStructureExactGeometry &pFSEG = pFSGeom->fileStructureExactGeometry();
    for (OdUInt32 i = 0; i < pFSEG.topologicalContext().size(); i++)
    {
      subs.push_back(pFSEG.topologicalContext()[i]);
    }

    return subs;
  }
};

class OdPrcTopoContext_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTopoContextPtr pTC = pObj;
    DUMPBASE(pTC, pListener)

    pListener->dumpInt8(L"Behavior", pTC->behaviour());
    pListener->dumpDouble(L"Granularity",pTC->granularity());
    pListener->dumpDouble(L"Tolerance",pTC->tolerance());
    pListener->dumpBoolean(L"Have Smallest Face Thickness",pTC->haveSmallestFaceThickness());
    pListener->dumpDouble(L"Smallest Thickness",pTC->smallestThickness());
    pListener->dumpBoolean(L"Have Scale",pTC->haveScale());
    pListener->dumpDouble(L"Scale",pTC->scale());
  }
};

//Go to All headers in PRCModule

//------------------PrcLight--------------------//
class OdPrcAmbientLight_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcAmbientLightPtr pAL = pObj;
    DUMPREFERENCEDBASE(pAL, pListener)

    pListener->dumpUInt32(L"specular", pAL->specular());
    pListener->dumpUInt32(L"emissive", pAL->emissive());
    pListener->dumpUInt32(L"diffuse", pAL->diffuse());
    pListener->dumpUInt32(L"ambient", pAL->ambient());
  }
};

class OdPrcDirectionalLight_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcDirectionalLightPtr pDL = pObj;
    DUMPREFERENCEDBASE(pDL, pListener)

    dumpGeVector3d(L"direction", pDL->direction(), pListener);
    pListener->dumpDouble(L"lightIntensity", pDL->lightIntensity());
    pListener->dumpUInt32(L"specular", pDL->specular());
    pListener->dumpUInt32(L"emissive", pDL->emissive());
    pListener->dumpUInt32(L"diffuse", pDL->diffuse());
    pListener->dumpUInt32(L"ambient", pDL->ambient());
  }
};

class OdPrcPointLight_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPointLightPtr pPL = pObj;
    DUMPREFERENCEDBASE(pPL, pListener)

    dumpGePoint3d(L"location", pPL->location(), pListener);
    pListener->dumpDouble(L"quadraticAttenuation", pPL->quadraticAttenuation());
    pListener->dumpDouble(L"linearAttenuation", pPL->linearAttenuation());
    pListener->dumpDouble(L"constantAttenuation", pPL->constantAttenuation());
    pListener->dumpUInt32(L"specular", pPL->specular());
    pListener->dumpUInt32(L"emissive", pPL->emissive());
    pListener->dumpUInt32(L"diffuse", pPL->diffuse());
    pListener->dumpUInt32(L"ambient", pPL->ambient());
  }
};

class OdPrcSpotLight_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSpotLightPtr pSL = pObj;
    DUMPREFERENCEDBASE(pSL, pListener)

    dumpGeVector3d(L"direction", pSL->direction(), pListener);
    pListener->dumpDouble(L"fallOffExponent", pSL->fallOffExponent());
    pListener->dumpDouble(L"fallOffAngle", pSL->fallOffAngle());
    dumpGePoint3d(L"location", pSL->location(), pListener);
    pListener->dumpDouble(L"quadraticAttenuation", pSL->quadraticAttenuation());
    pListener->dumpDouble(L"linearAttenuation", pSL->linearAttenuation());
    pListener->dumpDouble(L"constantAttenuation", pSL->constantAttenuation());
    pListener->dumpUInt32(L"specular", pSL->specular());
    pListener->dumpUInt32(L"emissive", pSL->emissive());
    pListener->dumpUInt32(L"diffuse", pSL->diffuse());
    pListener->dumpUInt32(L"ambient", pSL->ambient());
  }
};

//------------------PrcCurve--------------------//
void dumpInterval(const OdPrcInterval *pI, const OdPrcListener *pListener)
{
  if (pI)
  {
    pListener->dumpDouble(L"min", pI->minValue());
    pListener->dumpDouble(L"max", pI->maxValue());
  }
  else
  {
    pListener->dumpString(L"Interval", L"empty");
  }
}

void dumpParameterization(const OdPrcParameterization &pP, const OdPrcListener *pListener)
{
  dumpInterval(&pP.interval(), pListener);
  pListener->dumpDouble(L"coeff A", pP.coeffA());
  pListener->dumpDouble(L"coeff B", pP.coeffB());
}

void dumpBaseGeometry(const OdPrcBaseGeometry &pBG, const OdPrcListener *pListener)
{
  pListener->dumpBoolean(L"BaseInformation", pBG.hasBaseInformation());
  if (pBG.hasBaseInformation())
  {
    dumpAttributeData(pBG.attributeData(), pListener);
    pListener->dumpString(L"Name", pBG.name().name());
    pListener->dumpUInt32(L"identifier", pBG.identifier());
  }
}

void dumpContentCurve(const OdPrcContentCurve &pCC, const OdPrcListener *pListener)
{
  dumpBaseGeometry(pCC.baseGeometry(), pListener);
  pListener->dumpUInt32(L"extendInfo", pCC.extendInfo());
}

void dumpCurve(OdPrcCurvePtr pCurve, const OdPrcListener *pListener)
{
  pListener->dumpBoolean(L"is 3d", pCurve->is3d());
  dumpContentCurve(pCurve->contentCurve(), pListener);
  dumpParameterization(pCurve->parameterization(), pListener);
  if (pCurve->is3d())
  {
    OdPrcCurve3dPtr pCurve3d = pCurve;
    ::dump(L"Transformation", pCurve3d->transformation(), pListener);
  }
  else
  {
    OdPrcCurve2dPtr pCurve2d = pCurve;
    ::dump(L"Transformation", pCurve2d->transformation(), pListener);
  }
}

class OdPrcBlend02Boundary3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcBlend02Boundary3dPtr pB02B3d = pObj;
    dumpCurve(pB02B3d, pListener);
    dumpGePoint3d(L"startLimitPoint", pB02B3d->startLimitPoint(), pListener);
    dumpGePoint3d(L"endLimitPoint", pB02B3d->endLimitPoint(), pListener);
    const OdGePoint3dArray &points = pB02B3d->crossingPointPositions();
    ::dump(L"crossingPointPositions", points, pListener);
    pListener->dumpDouble(L"baseScale", pB02B3d->baseScale());
    pListener->dumpDouble(L"baseParameter", pB02B3d->baseParameter());
    pListener->dumpDouble(L"angularError", pB02B3d->angularError());
    pListener->dumpDouble(L"chordalError", pB02B3d->chordalError());
    pListener->dumpBoolean(L"intersectionCurveSens", pB02B3d->intersectionCurveSens());
    pListener->dumpBoolean(L"intersectionOrder", pB02B3d->intersectionOrder());
    pListener->dumpBoolean(L"boundingSurfaceSens", pB02B3d->boundingSurfaceSens());
    //const OdPrcBlend02SurfacePtr &blend() const --> from RxObject
    //const OdPrcSurfacePtr &boundingSurface() const --> from RxObject
    pListener->dumpUInt8(L"bound", pB02B3d->bound());
    pListener->dumpUInt32(L"startLimitType", pB02B3d->startLimitType());
    pListener->dumpUInt32(L"endLimitType", pB02B3d->endLimitType());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcBlend02Boundary3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->blend());
    subs.push_back(pBD->boundingSurface());
    return subs;
  }
};

class OdPrcNurbsCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcNurbsCurve3dPtr pNC3d = pObj;
    dumpCurve(pNC3d, pListener);
  }
};

class OdPrcNurbsCurve2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcNurbsCurve2dPtr pNC2d = pObj;
    dumpCurve(pNC2d, pListener);
  }
};

class OdPrcCircle3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCircle3dPtr pC3d = pObj;
    dumpCurve(pC3d, pListener);
    pListener->dumpDouble(L"radius", pC3d->radius());
  }
};

class OdPrcCircle2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCircle2dPtr pC2d = pObj;
    dumpCurve(pC2d, pListener);
    pListener->dumpDouble(L"radius", pC2d->radius());
  }
};

class OdPrcCompositeCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompositeCurve3dPtr pCC3d = pObj;
    dumpCurve(pCC3d, pListener);
    pListener->dumpBoolean(L"isClosed", pCC3d->isClosed());
    for (OdUInt32 i = 0; i < pCC3d->baseSense().size(); i++)
    {
      pListener->dumpBoolean(L"BaseSence", pCC3d->baseSense()[i]);
    }
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcCompositeCurve3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->baseCurve().size(); ++f)
    {
      subs.push_back(pBD->baseCurve()[f]);
    }
    return subs;
  }
};

class OdPrcCompositeCurve2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompositeCurve2dPtr pCC2d = pObj;
    dumpCurve(pCC2d, pListener);
    pListener->dumpBoolean(L"isClosed", pCC2d->isClosed());
    //const OdPrcCurvePtrArray &baseCurve() const --> from RxObject
    for (OdUInt32 i = 0; i < pCC2d->baseSense().size(); i++)
    {
      pListener->dumpBoolean(L"BaseSence", pCC2d->baseSense()[i]);
    }
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcCompositeCurve2dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->baseCurve().size(); ++f)
    {
      subs.push_back(pBD->baseCurve()[f]);
    }
    return subs;
  }
};

class OdPrc2dCurveOnSurfaceCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrc2dCurveOnSurfaceCurve3dPtr pCOSC = pObj;
    dumpCurve(pCOSC, pListener);
    pListener->dumpDouble(L"tolerance", pCOSC->tolerance());
    //const OdPrcCurvePtr &curveUV() const --> from RxObject
    //const OdPrcSurfacePtr &baseSurface() const --> from RxObject  
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrc2dCurveOnSurfaceCurve3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->curveUV());
    subs.push_back(pBD->baseSurface());
    return subs;
  }
};

class OdPrcEllipse3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcEllipse3dPtr pE3d = pObj;
    dumpCurve(pE3d, pListener);
    pListener->dumpDouble(L"radiusAtXAxis", pE3d->radiusAtXAxis());
    pListener->dumpDouble(L"radiusAtYAxis", pE3d->radiusAtYAxis());
  }
};

class OdPrcEllipse2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcEllipse2dPtr pE2d = pObj;
    dumpCurve(pE2d, pListener);
    pListener->dumpDouble(L"radiusAtXAxis", pE2d->radiusAtXAxis());
    pListener->dumpDouble(L"radiusAtYAxis", pE2d->radiusAtYAxis());
  }
};

class OdPrcEquationCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcEquationCurve3dPtr pEC3d = pObj;
    dumpCurve(pEC3d, pListener);
    //const OdPrcMath1dPtr &functionX() const --> from RxObject
    //const OdPrcMath1dPtr &functionY() const --> from RxObject
    //const OdPrcMath1dPtr &functionZ() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcEquationCurve3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->functionX());
    subs.push_back(pBD->functionY());
    subs.push_back(pBD->functionZ());
    return subs;
  }
};

class OdPrcEquationCurve2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcEquationCurve2dPtr pEC2d = pObj;
    dumpCurve(pEC2d, pListener);
    //const OdPrcMath1dPtr &functionX() const --> from RxObject
    //const OdPrcMath1dPtr &functionY() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcEquationCurve2dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->functionX());
    subs.push_back(pBD->functionY());
    return subs;
  }
};

class OdPrcHelixType1Curve_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcHelixType1CurvePtr pHT1C = pObj;
    dumpCurve(pHT1C, pListener);
    dumpGePoint3d(L"start", pHT1C->start(), pListener);
    pListener->dumpBoolean(L"trigonometricOrientation", pHT1C->trigonometricOrientation());
    dumpGeVector3d(L"unitZ", pHT1C->unitZ(), pListener);
    dumpGeVector3d(L"unitU", pHT1C->unitU(), pListener);
    //const OdPrcMath1dPtr &radiusLaw() const --> from RxObject
    //const OdPrcMath1dPtr &zLaw() const --> from RxObject
    //const OdPrcMath1dPtr &thetaLaw() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcHelixType1CurvePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->radiusLaw());
    subs.push_back(pBD->zLaw());
    subs.push_back(pBD->thetaLaw());
    return subs;
  }
};

class OdPrcHelixType0Curve_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcHelixType0CurvePtr pHT0C = pObj;
    dumpCurve(pHT0C, pListener);
    dumpGePoint3d(L"origin", pHT0C->origin(), pListener);
    dumpGePoint3d(L"start", pHT0C->start(), pListener);
    dumpGeVector3d(L"direction", pHT0C->direction(), pListener);
    pListener->dumpDouble(L"radiusEvolution", pHT0C->radiusEvolution());
    pListener->dumpDouble(L"pitch", pHT0C->pitch());
    pListener->dumpBoolean(L"trigonometricOrientation", pHT0C->trigonometricOrientation());
  }
};

class OdPrcHyperbola3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcHyperbola3dPtr pH3d = pObj;
    dumpCurve(pH3d, pListener);
    pListener->dumpDouble(L"semiImageAxis", pH3d->semiImageAxis());
    pListener->dumpDouble(L"semiAxis", pH3d->semiAxis());
    pListener->dumpUInt8(L"parameterizationType", pH3d->parameterizationType());
  }
};

class OdPrcHyperbola2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcHyperbola2dPtr pH2d = pObj;
    dumpCurve(pH2d, pListener);
    pListener->dumpDouble(L"semiImageAxis", pH2d->semiImageAxis());
    pListener->dumpDouble(L"semiAxis", pH2d->semiAxis());
    pListener->dumpUInt8(L"parameterizationType", pH2d->parameterizationType());
  }
};

void dumpCrossingPointsCrvIntersection(const OdPrcCrossingPointsCrvIntersection &pCPCI, const OdPrcListener *pListener)
{
  dumpGeVector3d(L"crossingPointTangent", pCPCI.crossingPointTangent(), pListener);
  dumpGePoint2d(L"crossingPointUv1", pCPCI.crossingPointUv1(), pListener);
  dumpGePoint2d(L"crossingPointUv2", pCPCI.crossingPointUv2(), pListener);
  dumpGePoint3d(L"crossingPointPosition", pCPCI.crossingPointPosition(), pListener);
  pListener->dumpDouble(L"crossingPointScale", pCPCI.crossingPointScale());
  pListener->dumpDouble(L"crossingPointParameter", pCPCI.crossingPointParameter());
  pListener->dumpUInt8(L"crossingPointFlags", pCPCI.crossingPointFlags());
}

class OdPrcIntersectionCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcIntersectionCurve3dPtr pIC3d = pObj;
    dumpCurve(pIC3d, pListener);
    dumpGePoint3d(L"startLimitPoint", pIC3d->startLimitPoint(), pListener);
    dumpGePoint3d(L"endLimitPoint", pIC3d->endLimitPoint(), pListener);
    for(OdUInt32 i = 0; i < pIC3d->crossingPointsCrvIntersection().size(); i++)
    {
      dumpCrossingPointsCrvIntersection(pIC3d->crossingPointsCrvIntersection()[i], pListener);
    }
    pListener->dumpDouble(L"angularError", pIC3d->angularError());
    pListener->dumpDouble(L"chordalError", pIC3d->chordalError());
    pListener->dumpBoolean(L"parameterizationDefinitionRespected", pIC3d->parameterizationDefinitionRespected());
    pListener->dumpBoolean(L"intersectionSense", pIC3d->intersectionSense());
    pListener->dumpBoolean(L"surface1Sense", pIC3d->surface1Sense());
    pListener->dumpBoolean(L"surface2Sense", pIC3d->surface2Sense());
    //const OdPrcSurfacePtr &surface1() const --> from RxObject
    //const OdPrcSurfacePtr &surface2() const --> from RxObject
    pListener->dumpUInt32(L"startLimitType", pIC3d->startLimitType());
    pListener->dumpUInt32(L"endLimitType", pIC3d->endLimitType());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcIntersectionCurve3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->surface1());
    subs.push_back(pBD->surface2());
    return subs;
  }
};

class OdPrcLine3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcLine3dPtr pL3d = pObj;
    dumpCurve(pL3d, pListener);
  }
};

class OdPrcLine2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcLine2dPtr pL2d = pObj;
    dumpCurve(pL2d, pListener);
  }
};

class OdPrcOffsetCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcOffsetCurve3dPtr pOC3d = pObj;
    dumpCurve(pOC3d, pListener);
    pListener->dumpDouble(L"offsetDistance", pOC3d->offsetDistance());
    //const OdPrcCurvePtr &baseCurve() const --> from RxObject
    dumpGeVector3d(L"offsetPlaneNormal", pOC3d->offsetPlaneNormal(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcOffsetCurve3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->baseCurve());
    return subs;
  }
};

class OdPrcParabola3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcParabola3dPtr pP3d = pObj;
    dumpCurve(pP3d, pListener);
    pListener->dumpDouble(L"focalLength", pP3d->focalLength());
    pListener->dumpUInt8(L"parameterizationType", pP3d->parameterizationType());
  }
};

class OdPrcParabola2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcParabola2dPtr pP2d = pObj;
    dumpCurve(pP2d, pListener);
    pListener->dumpDouble(L"focalLength", pP2d->focalLength());
    pListener->dumpUInt8(L"parameterizationType", pP2d->parameterizationType());
  }
};

class OdPrcPolyLine3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPolyLine3dPtr pPL3d = pObj;
    dumpCurve(pPL3d, pListener);
    const OdGePoint3dArray &points = pPL3d->points();
    ::dump(L"points", points, pListener);
  }
};

class OdPrcPolyLine2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPolyLine2dPtr pPL2d = pObj;
    dumpCurve(pPL2d, pListener);
    const OdGePoint2dArray &points = pPL2d->points();
    ::dump(L"points", points, pListener);
  }
};

class OdPrcTransformedCurve3d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTransformedCurve3dPtr pTC3d = pObj;
    dumpCurve(pTC3d, pListener);
    //const OdPrcMath3dPtr &mathTransformation() const --> from RxObject
    //const OdPrcCurvePtr &baseCurve() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcTransformedCurve3dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->mathTransformation());
    subs.push_back(pBD->baseCurve());
    return subs;
  }
};

class OdPrcTransformedCurve2d_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTransformedCurve2dPtr pTC2d = pObj;
    dumpCurve(pTC2d, pListener);
    //const OdPrcMath3dPtr &mathTransformation() const --> from RxObject
    //const OdPrcCurvePtr &baseCurve() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcTransformedCurve2dPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->mathTransformation());
    subs.push_back(pBD->baseCurve());
    return subs;
  }
};

//------------------PrcSurface--------------------//
void dumpContentSurface(const OdPrcContentSurface &pCC, const OdPrcListener *pListener)
{
  dumpBaseGeometry(pCC.baseGeometry(), pListener);
  pListener->dumpUInt32(L"extendInfo", pCC.extendInfo());
}

void dumpUVParametrization(const OdPrcUVParameterization &pUVP, const OdPrcListener *pListener)
{
  dumpGePoint2d(L"minUV", pUVP.uvDomain().minUV(), pListener);
  dumpGePoint2d(L"maxUV", pUVP.uvDomain().maxUV(), pListener);
  pListener->dumpBoolean(L"swapUV", pUVP.swapUV());
  pListener->dumpDouble(L"uCoeffA", pUVP.uCoeffA());
  pListener->dumpDouble(L"vCoeffA", pUVP.vCoeffA());
  pListener->dumpDouble(L"uCoeffB", pUVP.uCoeffB());
  pListener->dumpDouble(L"vCoeffB", pUVP.vCoeffB());
}

void dumpSurface(OdPrcSurfacePtr pSurface, const OdPrcListener *pListener)
{
  dumpContentSurface(pSurface->contentSurface(), pListener);
  ::dump(L"Transformation", pSurface->transformation(), pListener);
  dumpUVParametrization(pSurface->uVParameterization(), pListener);
}

class OdPrcBlend01Surface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcBlend01SurfacePtr pB01S = pObj;
    dumpSurface(pB01S, pListener);
    //const OdPrcCurvePtr &centerCurve() const --> from RxObject
    //const OdPrcCurvePtr &originCurve() const --> from RxObject
    //const OdPrcCurvePtr &tangentCurve() const  --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcBlend01SurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->centerCurve());
    subs.push_back(pBD->originCurve());
    subs.push_back(pBD->tangentCurve());
    return subs;
  }
};

class OdPrcBlend02Surface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcBlend02SurfacePtr pB02S = pObj;
    dumpSurface(pB02S, pListener);
    //const OdPrcSurfacePtr &cliffSupportingSurface1() const --> from RxObject
    //const OdPrcSurfacePtr &cliffSupportingSurface0() const --> from RxObject
    //const OdPrcCurvePtr &boundCurve1() const --> from RxObject
    //const OdPrcCurvePtr &boundCurve0() const --> from RxObject
    //const OdPrcSurfacePtr &boundSurface1() const --> from RxObject
    //const OdPrcSurfacePtr &boundSurface0() const --> from RxObject
    pListener->dumpDouble(L"radius1", pB02S->radius1());
    pListener->dumpDouble(L"radius0", pB02S->radius0());
    pListener->dumpBoolean(L"boundSurfaceSens1", pB02S->boundSurfaceSens1());
    pListener->dumpBoolean(L"boundSurfaceSens0", pB02S->boundSurfaceSens0());
    pListener->dumpBoolean(L"centerCurveSens", pB02S->centerCurveSens());
    //const OdPrcCurvePtr &centerCurve() const --> from RxObject
    pListener->dumpUInt8(L"parameterizationType", pB02S->parameterizationType());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcBlend02SurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->cliffSupportingSurface0());
    subs.push_back(pBD->cliffSupportingSurface1());
    subs.push_back(pBD->boundCurve0());
    subs.push_back(pBD->boundCurve1());
    subs.push_back(pBD->boundSurface0());
    subs.push_back(pBD->boundSurface1());
    subs.push_back(pBD->centerCurve());
    return subs;
  }
};

class OdPrcBlend03Surface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcBlend03SurfacePtr pB03S = pObj;
    dumpSurface(pB03S, pListener);
    ::dump(L"secondDerivatives", (const OdGePoint3dArray &)pB03S->secondDerivatives(), pListener);
    ::dump(L"tangent", (const OdGePoint3dArray &)pB03S->tangent(), pListener);
    ::dump(L"position", pB03S->position(), pListener);
    for (OdUInt32 i = 0; i < pB03S->multiplicities().size(); i++)
    {
      pListener->dumpInt32(L"multiplicities", pB03S->multiplicities()[i]);
    }
    for (OdUInt32 i = 0; i < pB03S->rail2SecondDerivatives().size(); i++)
    {
      pListener->dumpDouble(L"rail2SecondDerivatives", pB03S->rail2SecondDerivatives()[i]);
    }
    for (OdUInt32 i = 0; i < pB03S->rail2DerivativesV().size(); i++)
    {
      pListener->dumpDouble(L"rail2DerivativesV", pB03S->rail2DerivativesV()[i]);
    }
    for (OdUInt32 i = 0; i < pB03S->rail2AnglesV().size(); i++)
    {
      pListener->dumpDouble(L"rail2AnglesV", pB03S->rail2AnglesV()[i]);
    }
    for (OdUInt32 i = 0; i < pB03S->parameters().size(); i++)
    {
      pListener->dumpDouble(L"parameters", pB03S->parameters()[i]);
    }
    pListener->dumpDouble(L"trimVMax", pB03S->trimVMax());
    pListener->dumpDouble(L"trimVMin", pB03S->trimVMin());
    pListener->dumpDouble(L"rail2ParameterV", pB03S->rail2ParameterV());
  }
};

void dumpGeNurbSurface(const OdGeNurbSurface &pGNS, const OdPrcListener *pListener)
{
  pListener->dumpBoolean(L"isRationalInU", pGNS.isRationalInU());
  pListener->dumpBoolean(L"isRationalInV", pGNS.isRationalInV());
  pListener->dumpInt8(L"singularityInU", pGNS.singularityInU());
  pListener->dumpInt8(L"singularityInV", pGNS.singularityInV());
  pListener->dumpInt8(L"degreeInU", pGNS.degreeInU());
  pListener->dumpInt8(L"numControlPointsInU", pGNS.numControlPointsInU());
  pListener->dumpInt8(L"degreeInV", pGNS.degreeInV());
  pListener->dumpInt8(L"numControlPointsInV", pGNS.numControlPointsInV());
  pListener->dumpInt8(L"numKnotsInU", pGNS.numKnotsInU());
  pListener->dumpInt8(L"numKnotsInV", pGNS.numKnotsInV());
  pListener->dumpBoolean(L"isNormalReversed", pGNS.isNormalReversed());

}

class OdPrcNurbsSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcNurbsSurfacePtr pNS = pObj;
    dumpSurface(pNS, pListener);
    dumpGeNurbSurface(pNS->nurbSurface(), pListener);
    pListener->dumpUInt32(L"knotType", pNS->knotType());
    pListener->dumpUInt32(L"surfaceForm", pNS->surfaceForm());
  }
};

class OdPrcCone_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcConePtr pC = pObj;
    dumpSurface(pC, pListener);
    pListener->dumpDouble(L"semiAngle", pC->semiAngle());
    pListener->dumpDouble(L"bottomRadius", pC->bottomRadius());
  }
};

class OdPrcCylinder_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCylinderPtr pC = pObj;
    dumpSurface(pC, pListener);
    pListener->dumpDouble(L"radius", pC->radius());
  }
};

class OdPrcCylindricalSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCylindricalSurfacePtr pCS = pObj;
    dumpSurface(pCS, pListener);
    pListener->dumpDouble(L"tolerance", pCS->tolerance());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcCylindricalSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->baseSurface());
    return subs;
  }
};

class OdPrcOffsetSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcOffsetSurfacePtr pOS = pObj;
    dumpSurface(pOS, pListener);
    pListener->dumpDouble(L"offsetDistance", pOS->offsetDistance());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcOffsetSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->baseSurface());
    return subs;
  }
};

class OdPrcPlane_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcPlanePtr pP = pObj;
    dumpSurface(pP, pListener);
  }
};

class OdPrcRuledSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcRuledSurfacePtr pRS = pObj;
    dumpSurface(pRS, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcRuledSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->firstCurve());
    subs.push_back(pBD->secondCurve());
    return subs;
  }
};

class OdPrcSphere_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSpherePtr pS = pObj;
    dumpSurface(pS, pListener);
    pListener->dumpDouble(L"radius", pS->radius());
  }
};

class OdPrcRevolutionSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcRevolutionSurfacePtr pRS = pObj;
    dumpSurface(pRS, pListener);
    dumpGePoint3d(L"origin", pRS->origin(), pListener);
    dumpGeVector3d(L"xAxis", pRS->x(), pListener);
    dumpGeVector3d(L"yAxis", pRS->y(), pListener);
    pListener->dumpDouble(L"tolerance", pRS->tolerance());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcRevolutionSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->baseCurve());
    return subs;
  }
};

class OdPrcExtrusionSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcExtrusionSurfacePtr pES = pObj;
    dumpSurface(pES, pListener);
    const OdGeVector3d &sweepVector = pES->sweepVector();
    ::dump(L"sweepVector", sweepVector, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcExtrusionSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->baseCurve());
    return subs;
  }
};

class OdPrcFromCurvesSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFromCurvesSurfacePtr pFCS = pObj;
    dumpSurface(pFCS, pListener);
    dumpGePoint3d(L"origin", pFCS->origin(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFromCurvesSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->firstCurve());
    subs.push_back(pBD->secondCurve());
    return subs;
  }
};

class OdPrcTorus_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTorusPtr pT = pObj;
    dumpSurface(pT, pListener);
    pListener->dumpDouble(L"minorRadius", pT->minorRadius());
    pListener->dumpDouble(L"majorRadius", pT->majorRadius());
  }
};

class OdPrcTransformedSurface_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcTransformedSurfacePtr pTS = pObj;
    dumpSurface(pTS, pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcTransformedSurfacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->mathTransformation());
    subs.push_back(pBD->baseSurface());
    return subs;
  }
};

#define DUMPBODY(object, pListener) pListener->dumpObjectId(L"ID", object->objectId());

void dumpBaseTopology(const OdPrcBaseTopology &pBT, const OdPrcListener *pListener)
{
  pListener->dumpString(L"Name", pBT.name().name());
  dumpAttributeData(pBT.attributeData(), pListener);
  pListener->dumpUInt32(L"identifier", pBT.identifier());
  pListener->dumpBoolean(L"baseInformation", pBT.baseInformation());
}

void dumpContentBody(const OdPrcContentBody &pCB, const OdPrcListener *pListener)
{
  dumpBaseTopology(pCB.baseTopology(), pListener);
  pListener->dumpInt8(L"boundingBoxBehaviour", pCB.boundingBoxBehaviour());
}

class OdPrcSingleWireBody_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcSingleWireBodyPtr pSWB = pObj;
    DUMPBODY(pSWB, pListener)

    //const OdPrcTopoItemPtr &wireEdge() const --> from RxObject
    dumpContentBody(pSWB->contentBody(), pListener);
    pListener->dumpUInt32(L"SerialType", pSWB->getSerialType());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcSingleWireBodyPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->wireEdge());
    return subs;
  }
};


#ifdef DUMP_COMPRESSION
class OdPrcCompressedCurve_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedCurvePtr pCC = pObj;
    // empty
  }
};

class OdPrcCompressedLine_Dumper : public OdPrcCompressedCurve_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedLinePtr pCL = pObj;

    dumpGePoint3d(L"startPoint", pCL->getStartPoint(), pListener);
    dumpGePoint3d(L"endPoint", pCL->getEndPoint(), pListener);
  }
};


class OdPrcCompressedCircle_Dumper : public OdPrcCompressedCurve_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedCirclePtr pCC = pObj;

    dumpGePoint3d(L"startPoint", pCC->getStartPoint(), pListener);
    dumpGePoint3d(L"endPoint", pCC->getEndPoint(), pListener);
    dumpGePoint3d(L"middlePointOnCurve", pCC->middlePointOnCurve(), pListener);
    dumpGeVector3d(L"normal", pCC->normal(), pListener);
    dumpGePoint3d(L"center", pCC->center(), pListener);
    pListener->dumpBoolean(L"isStartEqualToEndPoint", pCC->isStartEqualToEndPoint());
    pListener->dumpBoolean(L"particularCircle", pCC->particularCircle());
    pListener->dumpBoolean(L"circleAngle", pCC->circleAngle());
  }
};


class OdPrcCompressedHermiteCurve_Dumper : public OdPrcCompressedCurve_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedHermiteCurvePtr pCHC = pObj;

    OdString tmp;
    for (OdUInt32 i = 0; i < pCHC->tangens().size(); i++)
    {
      dumpGeVector3d(tmp.format(L"tangens[%d]", i), pCHC->tangens()[i], pListener);
    }
    for (OdUInt32 i = 0; i < pCHC->points().size(); i++)
    {
      dumpGePoint3d(tmp.format(L"tangens[%d]", i), pCHC->points()[i], pListener);
    }

    OdGePoint3d p;
    pListener->dumpBoolean(L"hasStartPoint", pCHC->hasStartPoint(p));
    if (pCHC->hasStartPoint(p))
    {
      dumpGePoint3d(L"startPoint", p, pListener);
    }
    pListener->dumpBoolean(L"hasEndPoint", pCHC->hasEndPoint(p));
    if (pCHC->hasEndPoint(p))
    {
      dumpGePoint3d(L"endPoint", p, pListener);
    }
  }
};


class OdPrcCompressedEllipse_Dumper : public OdPrcCompressedCurve_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedEllipsePtr pCE = pObj;
    // empty
  }
};


class OdPrcCompressedCompositeCurve_Dumper : public OdPrcCompressedCurve_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedCompositeCurvePtr pCCC = pObj;

    dumpGePoint3d(L"startPoint", pCCC->getStartPoint(), pListener);
    dumpGePoint3d(L"endPoint", pCCC->getEndPoint(), pListener);
    pListener->dumpUInt32(L"dimension", pCCC->dimension());
    pListener->dumpBoolean(L"isCurveClosed", pCCC->isCurveClosed());

    OdGePoint3d p;
    pListener->dumpBoolean(L"hasStartPoint", pCCC->hasStartPoint(p));
    if (pCCC->hasStartPoint(p))
    {
      dumpGePoint3d(L"startPoint", p, pListener);
    }
    pListener->dumpBoolean(L"hasEndPoint", pCCC->hasEndPoint(p));
    if (pCCC->hasEndPoint(p))
    {
      dumpGePoint3d(L"endPoint", p, pListener);
    }
    pListener->dumpUInt32(L"curvesCount", pCCC->curves().size()); 
  }

  virtual OdRxObjectPtrArray subElements(const OdRxObject *pObj) const
  {
    const OdPrcCompressedCompositeCurvePtr pCCC = pObj;
    OdRxObjectPtrArray subs;
    for(OdUInt32 i = 0; i < pCCC->curves().size(); ++i)
    {
      subs.push_back(pCCC->curves()[i]);
    }
    return subs;
  }
};


class OdPrcCompressedSingleWireBody_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCompressedSingleWireBodyPtr pCSWB = pObj;

    DUMPBODY(pCSWB, pListener);
    dumpContentBody(pCSWB->contentBody(), pListener);
    pListener->dumpUInt32(L"serialType", pCSWB->getSerialType());
    pListener->dumpDouble(L"curveTolerance", pCSWB->curveTolerance());
    pListener->dumpDouble(L"serialTolerance", pCSWB->getTolerance());
  }

  virtual OdRxObjectPtrArray subElements(const OdRxObject *pObj) const
  {
    const OdPrcCompressedSingleWireBodyPtr pCSWB = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pCSWB->curve());
    return subs;
  }
};
#endif

class OdPrcBrepData_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcBrepDataPtr pBD = pObj;
    DUMPBODY(pBD, pListener)

    dumpBoundingBox(L"boundingBox", pBD->boundingBox(), pListener);
    dumpContentBody(pBD->contentBody(), pListener);
    pListener->dumpUInt32(L"Number of connexes", pBD->connex().size());
    pListener->dumpUInt32(L"SerialType", pBD->getSerialType());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcBrepDataPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->connex().size(); ++f)
    {
      subs.push_back(pBD->connex()[f]);
    }
    return subs;
  }
};

class OdPrcCamera_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCameraPtr pC = pObj;
    DUMPREFERENCEDBASE(pC, pListener)

    dumpGePoint3d(L"location", pC->location(), pListener);
    dumpGePoint3d(L"lookAt", pC->lookAt(), pListener);
    dumpGeVector3d(L"up", pC->up(), pListener);
    pListener->dumpDouble(L"yFov", pC->yFov());
    pListener->dumpDouble(L"aspectRatio", pC->aspectRatio());
    pListener->dumpDouble(L"zNear", pC->zNear());
    pListener->dumpDouble(L"zFar", pC->zFar());
    pListener->dumpDouble(L"zoomFactor", pC->zoomFactor());
    pListener->dumpDouble(L"xFov", pC->xFov());
    pListener->dumpBoolean(L"orthographic", pC->orthographic());
  }
};

//------------------PrcTopoItem--------------------//
class OdPrcUniqueVertex_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcUniqueVertexPtr pUV = pObj;

    dumpGePoint3d(L"point", pUV->point(), pListener);
    dumpBaseTopology(pUV->baseTopology(), pListener);
    pListener->dumpDouble(L"tolerance", pUV->tolerance());
    pListener->dumpBoolean(L"haveTolerance", pUV->haveTolerance());
  }
};

class OdPrcMultipleVertex_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMultipleVertexPtr pMV = pObj;

    const OdGePoint3dArray &points = pMV->points();
    ::dump(L"points", points, pListener);
    dumpBaseTopology(pMV->baseTopology(), pListener);
  }
};

void dumpContentWireEdge(const OdPrcContentWireEdge &pCWE, const OdPrcListener *pListener)
{
  dumpBaseTopology(pCWE.baseTopology(), pListener);
  dumpInterval(pCWE.trimInterval(), pListener);
  //const OdPrcCurvePtr &curve3d() const --> from RxObject
}

class OdPrcEdge_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcEdgePtr pE = pObj;

    //const OdPrcTopoItemPtr &vertexEnd() const --> from RxObject
    //const OdPrcTopoItemPtr &vertexStart() const --> from RxObject
    dumpContentWireEdge(pE->contentWireEdge(), pListener);
    pListener->dumpDouble(L"tolerance", pE->tolerance());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    OdRxObjectPtrArray subs;

    const OdPrcEdgePtr pBD = pObj;
    subs.push_back(pBD->vertexStart());
    subs.push_back(pBD->vertexEnd());
    subs.push_back(pBD->contentWireEdge().curve());
    return subs;
  }
};

class OdPrcCoEdge_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcCoEdgePtr pCE = pObj;

    //const OdPrcCurvePtr &curveUV() const --> from RxObject
    //const OdPrcEdgePtr &edge() const --> from RxObject
    dumpBaseTopology(pCE->baseTopology(), pListener);
    pListener->dumpInt8(L"orientationUvWithLoop", pCE->orientationUvWithLoop());
    pListener->dumpInt8(L"orientationWithLoop", pCE->orientationWithLoop());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    OdRxObjectPtrArray subs;

    const OdPrcCoEdgePtr pBD = pObj;
    subs.push_back(pBD->edge());
    subs.push_back(pBD->curveUV());

    return subs;
  }
};

class OdPrcLoop_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcLoopPtr pL = pObj;

    //const OdPrcCoEdgePtrArray &coedges() const --> from RxObject
    dumpBaseTopology(pL->baseTopology(), pListener);
    pListener->dumpInt8(L"orientationWithSurface", pL->orientationWithSurface());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcLoopPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->coedges().size(); ++f)
    {
      subs.push_back(pBD->coedges()[f]);
    }
    return subs;
  }
};

class OdPrcConnex_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcConnexPtr pC = pObj;

    //const OdPrcShellPtrArray &shells() const --> from RxObject
    dumpBaseTopology(pC->baseTopology(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcConnexPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->shells().size(); ++f)
    {
      subs.push_back(pBD->shells()[f]);
    }
    return subs;
  }
};

class OdPrcWireEdge_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcWireEdgePtr pWE = pObj;

    dumpContentWireEdge(pWE->contentWireEdge(), pListener);
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcWireEdgePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->contentWireEdge().curve());
    return subs;
  }
};

class OdPrcShell_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcShellPtr pS = pObj;

    //const OdPrcFacePtrArray &faces() const --> from RxObject
    dumpBaseTopology(pS->baseTopology(), pListener);
    pListener->dumpBoolean(L"shellIsClosed", pS->shellIsClosed());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcShellPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->faces().size(); ++f)
    {
      subs.push_back(pBD->faces()[f]);
    }
    return subs;
  }
};

void dumpDomain(const OdPrcDomain &pD, const OdPrcListener *pListener)
{
  dumpGePoint2d(L"minUV", pD.minUV(), pListener);
  dumpGePoint2d(L"maxUV", pD.maxUV(), pListener);
}

class OdPrcFace_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFacePtr pF = pObj;

    pListener->dumpUInt8(L"orientationSurfaceWithShell", pF->orientationSurfaceWithShell());
    //const OdPrcLoopPtrArray &loops() const --> from RxObject
    const OdPrcDomain *domain = pF->surfaceTrimDomain();
    if(domain)
    {
      dumpDomain(*pF->surfaceTrimDomain(), pListener);
    }
    else
    {
      pListener->dumpString(L"No Domain","");
    } 
    //const OdPrcSurfacePtr &baseSurface() const --> from RxObject
    dumpBaseTopology(pF->baseTopology(), pListener);
    pListener->dumpBoolean(L"haveGraphics", pF->hasGraphics());

    if(pF->hasGraphics())
    {
      dumpGraphics(*pF->graphics(), pListener);
    }
    pListener->dumpInt32(L"OuterLoopIndex", pF->getOuterLoopIndex());
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcFacePtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->loops().size(); ++f)
    {
      subs.push_back(pBD->loops()[f]);
    }
    subs.push_back(pBD->baseSurface());
    return subs;
  }
};

class OdPrcMath1dPolynom_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath1dPolynomPtr pM1dP = pObj;

    for (OdUInt32 i = 0; i < pM1dP->coefficient().size(); i++)
    {
      pListener->dumpDouble(L"coefficient", pM1dP->coefficient()[i]);
    }
  }
};

class OdPrcMath1dTrigonometric_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath1dTrigonometricPtr pM1dT = pObj;

    pListener->dumpDouble(L"dcOffset", pM1dT->dcOffset());
    pListener->dumpDouble(L"frequency", pM1dT->frequency());
    pListener->dumpDouble(L"phase", pM1dT->phase());
    pListener->dumpDouble(L"amplitude", pM1dT->amplitude());
  }
};

class OdPrcMath1dFraction_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath1dFractionPtr pM1dF = pObj;

    //const OdPrcMath1dPtr &numerator() const --> from RxObject
    //const OdPrcMath1dPtr &denominator() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcMath1dFractionPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->numerator());
    subs.push_back(pBD->denominator());
    return subs;
  }
};

class OdPrcMath1dArcTanCos_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath1dArcTanCosPtr pM1dATC = pObj;

    pListener->dumpDouble(L"phase", pM1dATC->phase());
    pListener->dumpDouble(L"frequency", pM1dATC->frequency());
    pListener->dumpDouble(L"a", pM1dATC->a());
    pListener->dumpDouble(L"amplitude", pM1dATC->amplitude());
  }
};

class OdPrcMath1dCombination_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath1dCombinationPtr pM1dC = pObj;

    for (OdUInt32 i = 0; i < pM1dC->combinationFunctions().size(); ++i)
    {
      pListener->dumpDouble(L"coefficient", pM1dC->combinationFunctions()[i].getCoefficient());
    }
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcMath1dCombinationPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    for(OdUInt32 f=0; f<pBD->combinationFunctions().size(); ++f)
    {
      subs.push_back(pBD->combinationFunctions()[f].function());
    }
    return subs;
  }
};

class OdPrcMath3dLinear_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath3dLinearPtr pM3dL = pObj;

    const OdGeMatrix3d &matr = pM3dL->mat();
    ::dump(L"Matrix", matr, pListener);

    //for (OdUInt32 i = 0; i < pM3dL->vect().size(); i++)
    //{
    //  pListener->dumpDouble(L"vect", pM3dL->vect()[i]);
    //}
  }
};

class OdPrcMath3dNonLinear_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcMath3dNonLinearPtr pM3dNL = pObj;

    pListener->dumpDouble(L"d2", pM3dNL->d2());
    //const OdPrcMath3dLinearPtr &leftTransformation() const --> from RxObject
    //const OdPrcMath3dLinearPtr &rightTransformation() const --> from RxObject
  }

  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    const OdPrcMath3dNonLinearPtr pBD = pObj;

    OdRxObjectPtrArray subs;
    subs.push_back(pBD->leftTransformation());
    subs.push_back(pBD->rightTransformation());
    return subs;
  }
};

class OdPrcAuditInfo_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcAuditInfoPtr pAI = pObj;

    //We need this dump?
  }
};

class OdPrcFilerController_Dumper : public OdPrcEntity_Dumper
{
public:

  virtual void dump(const OdRxObject *pObj, const OdPrcListener *pListener) const
  {
    const OdPrcFilerControllerPtr pFC = pObj;

    //We need this dump?
  }
};

#define DUMPERS(a) OdStaticRxObject<OdPrc##a##_Dumper> m_Prc##a;
#define ADDXS(a) OdPrc##a ::desc()->addX(OdPrcEntity_Dumper::desc(),   &m_Prc##a);
#define DELXS(a) OdPrc##a ::desc()->delX(OdPrcEntity_Dumper::desc());

class Dumpers
{
  DUMPERS(File)
  DUMPERS(Schema)
  DUMPERS(ModelFileData)
  DUMPERS(FileStructure)
  DUMPERS(FileStructureGlobals)
  DUMPERS(Picture)
  DUMPERS(FileStructureTree)
  DUMPERS(PartDefinition)
  DUMPERS(BrepModel)
  DUMPERS(WireCurve)
  DUMPERS(Direction)
  DUMPERS(ConstructionPlane)
  DUMPERS(PointSet)
  DUMPERS(PolyBrepModel)
  DUMPERS(PolyWire)
  DUMPERS(Set)
  DUMPERS(CoordinateSystem)
  DUMPERS(AnnotationItem)
  DUMPERS(AnnotationSet)
  DUMPERS(AnnotationReference)
  DUMPERS(Markup)
  DUMPERS(MarkupLeader)
  DUMPERS(MarkupLinkedItem)
  DUMPERS(View)
  DUMPERS(ProductOccurrence)
  DUMPERS(FileStructureInternalData)
  DUMPERS(FileStructureTessellation)
  DUMPERS(3dTess)
  DUMPERS(3dWireTess)
  DUMPERS(MarkupTess)

#ifdef DUMP_COMPRESSION
  DUMPERS(HighlyCompressed3dTess)
  DUMPERS(CompressedCurve)
  DUMPERS(CompressedLine)
  DUMPERS(CompressedCircle)
  DUMPERS(CompressedHermiteCurve)
  DUMPERS(CompressedEllipse)
  DUMPERS(CompressedCompositeCurve)
  DUMPERS(CompressedSingleWireBody)
#endif

  DUMPERS(FileStructureGeometry)
  DUMPERS(TopoContext)
  DUMPERS(Category1LineStyle)
  DUMPERS(LinePattern)
  DUMPERS(MaterialGeneric)
  DUMPERS(TextureApplication)
  DUMPERS(TextureDefinition)
  DUMPERS(DottingPattern)
  DUMPERS(HatchingPattern)
  DUMPERS(SolidPattern)
  DUMPERS(PicturePattern)
  DUMPERS(Reference)
  DUMPERS(Filter)
  DUMPERS(SceneDisplayParameters)
  DUMPERS(Blend02Boundary3d)
  DUMPERS(NurbsCurve3d)
  DUMPERS(NurbsCurve2d)
  DUMPERS(Circle3d)
  DUMPERS(Circle2d)
  DUMPERS(CompositeCurve3d)
  DUMPERS(CompositeCurve2d)
  DUMPERS(2dCurveOnSurfaceCurve3d)
  DUMPERS(Ellipse3d)
  DUMPERS(Ellipse2d)
  DUMPERS(EquationCurve3d)
  DUMPERS(EquationCurve2d)
  DUMPERS(HelixType0Curve)
  DUMPERS(HelixType1Curve)
  DUMPERS(Hyperbola3d)
  DUMPERS(Hyperbola2d)
  DUMPERS(IntersectionCurve3d)
  DUMPERS(Line3d)
  DUMPERS(Line2d)
  DUMPERS(OffsetCurve3d)
  DUMPERS(Parabola3d)
  DUMPERS(Parabola2d)
  DUMPERS(PolyLine3d)
  DUMPERS(PolyLine2d)
  DUMPERS(TransformedCurve3d)
  DUMPERS(TransformedCurve2d)
  DUMPERS(AmbientLight)
  DUMPERS(DirectionalLight)
  DUMPERS(PointLight)
  DUMPERS(SpotLight)
  DUMPERS(Blend01Surface)
  DUMPERS(Blend02Surface)
  DUMPERS(Blend03Surface)
  DUMPERS(NurbsSurface)
  DUMPERS(Cone)
  DUMPERS(Cylinder)
  DUMPERS(CylindricalSurface)
  DUMPERS(OffsetSurface)
  DUMPERS(Plane)
  DUMPERS(RuledSurface)
  DUMPERS(Sphere)
  DUMPERS(RevolutionSurface)
  DUMPERS(ExtrusionSurface)
  DUMPERS(FromCurvesSurface)
  DUMPERS(Torus)
  DUMPERS(TransformedSurface)
  DUMPERS(SingleWireBody)
  DUMPERS(BrepData)
  DUMPERS(Camera)
  DUMPERS(WireEdge)
  DUMPERS(Connex)
  DUMPERS(Shell)
  DUMPERS(Face)
  DUMPERS(Loop)
  DUMPERS(CoEdge)
  DUMPERS(Edge)
  DUMPERS(UniqueVertex)
  DUMPERS(MultipleVertex)
  DUMPERS(Math1dArcTanCos)
  DUMPERS(Math1dCombination)
  DUMPERS(Math1dFraction)
  DUMPERS(Math1dPolynom)
  DUMPERS(Math1dTrigonometric)
  DUMPERS(Math3dLinear)
  DUMPERS(Math3dNonLinear)

public:
  /**********************************************************************/
  /* Add Protocol Extensions                                            */
  /**********************************************************************/
  void addXs()
  {
    ADDXS(File)
    ADDXS(Schema)
    ADDXS(ModelFileData)
    ADDXS(FileStructure)
    ADDXS(FileStructureGlobals)
    ADDXS(Picture)
    ADDXS(FileStructureTree)
    ADDXS(PartDefinition)
    ADDXS(BrepModel)
    ADDXS(WireCurve)
    ADDXS(Direction)
    ADDXS(ConstructionPlane)
    ADDXS(PointSet)
    ADDXS(PolyBrepModel)
    ADDXS(PolyWire)
    ADDXS(Set)
    ADDXS(CoordinateSystem)
    ADDXS(AnnotationItem)
    ADDXS(AnnotationSet)
    ADDXS(AnnotationReference)
    ADDXS(Markup)
    ADDXS(MarkupLeader)
    ADDXS(MarkupLinkedItem)
    ADDXS(View)
    ADDXS(ProductOccurrence)
    ADDXS(FileStructureInternalData)
    ADDXS(FileStructureTessellation)
    ADDXS(3dTess)
    ADDXS(3dWireTess)
    ADDXS(MarkupTess)
#ifdef DUMP_COMPRESSION
    ADDXS(HighlyCompressed3dTess)
    ADDXS(CompressedCurve)
    ADDXS(CompressedLine)
    ADDXS(CompressedCircle)
    ADDXS(CompressedHermiteCurve)
    ADDXS(CompressedEllipse)
    ADDXS(CompressedCompositeCurve)
    ADDXS(CompressedSingleWireBody)
#endif
    ADDXS(FileStructureGeometry)
    ADDXS(TopoContext)
    ADDXS(Category1LineStyle)
    ADDXS(LinePattern)
    ADDXS(MaterialGeneric)
    ADDXS(TextureApplication)
    ADDXS(TextureDefinition)
    ADDXS(DottingPattern)
    ADDXS(HatchingPattern)
    ADDXS(SolidPattern)
    ADDXS(PicturePattern)
    ADDXS(Reference)
    ADDXS(Filter)
    ADDXS(SceneDisplayParameters)
    ADDXS(Blend02Boundary3d)
    ADDXS(NurbsCurve3d)
    ADDXS(NurbsCurve2d)
    ADDXS(Circle3d)
    ADDXS(Circle2d)
    ADDXS(CompositeCurve3d)
    ADDXS(CompositeCurve2d)
    ADDXS(2dCurveOnSurfaceCurve3d)
    ADDXS(Ellipse3d)
    ADDXS(Ellipse2d)
    ADDXS(EquationCurve3d)
    ADDXS(EquationCurve2d)
    ADDXS(HelixType0Curve)
    ADDXS(HelixType1Curve)
    ADDXS(Hyperbola3d)
    ADDXS(Hyperbola2d)
    ADDXS(IntersectionCurve3d)
    ADDXS(Line3d)
    ADDXS(Line2d)
    ADDXS(OffsetCurve3d)
    ADDXS(Parabola3d)
    ADDXS(Parabola2d)
    ADDXS(PolyLine3d)
    ADDXS(PolyLine2d)
    ADDXS(TransformedCurve3d)
    ADDXS(TransformedCurve2d)
    ADDXS(AmbientLight)
    ADDXS(DirectionalLight)
    ADDXS(PointLight)
    ADDXS(SpotLight)
    ADDXS(Blend01Surface)
    ADDXS(Blend02Surface)
    ADDXS(Blend03Surface)
    ADDXS(NurbsSurface)
    ADDXS(Cone)
    ADDXS(Cylinder)
    ADDXS(CylindricalSurface)
    ADDXS(OffsetSurface)
    ADDXS(Plane)
    ADDXS(RuledSurface)
    ADDXS(Sphere)
    ADDXS(RevolutionSurface)
    ADDXS(ExtrusionSurface)
    ADDXS(FromCurvesSurface)
    ADDXS(Torus)
    ADDXS(TransformedSurface)
    ADDXS(SingleWireBody)
    ADDXS(BrepData)
    ADDXS(Camera)
    ADDXS(WireEdge)
    ADDXS(Connex)
    ADDXS(Shell)
    ADDXS(Face)
    ADDXS(Loop)
    ADDXS(CoEdge)
    ADDXS(Edge)
    ADDXS(UniqueVertex)
    ADDXS(MultipleVertex)
    ADDXS(Math1dArcTanCos)
    ADDXS(Math1dCombination)
    ADDXS(Math1dFraction)
    ADDXS(Math1dPolynom)
    ADDXS(Math1dTrigonometric)
    ADDXS(Math3dLinear)
    ADDXS(Math3dNonLinear)
  } // end addXs

  /**********************************************************************/
  /* Delete Protocol Extensions                                         */
  /**********************************************************************/
  void delXs()
  {
    DELXS(File)
    DELXS(Schema)
    DELXS(ModelFileData)
    DELXS(FileStructure)
    DELXS(FileStructureGlobals)
    DELXS(Picture)
    DELXS(FileStructureTree)
    DELXS(PartDefinition)
    DELXS(BrepModel)
    DELXS(WireCurve)
    DELXS(Direction)
    DELXS(ConstructionPlane)
    DELXS(PointSet)
    DELXS(PolyBrepModel)
    DELXS(PolyWire)
    DELXS(Set)
    DELXS(CoordinateSystem)
    DELXS(AnnotationItem)
    DELXS(AnnotationSet)
    DELXS(AnnotationReference)
    DELXS(Markup)
    DELXS(MarkupLeader)
    DELXS(MarkupLinkedItem)
    DELXS(View)
    DELXS(ProductOccurrence)
    DELXS(FileStructureInternalData)
    DELXS(FileStructureTessellation)
    DELXS(3dTess)
    DELXS(3dWireTess)
    DELXS(MarkupTess)
#ifdef DUMP_COMPRESSION
    DELXS(HighlyCompressed3dTess)
    DELXS(CompressedCurve)
    DELXS(CompressedLine)
    DELXS(CompressedCircle)
    DELXS(CompressedHermiteCurve)
    DELXS(CompressedEllipse)
    DELXS(CompressedCompositeCurve)
    DELXS(CompressedSingleWireBody)
#endif
    DELXS(FileStructureGeometry)
    DELXS(TopoContext)
    DELXS(Category1LineStyle)
    DELXS(LinePattern)
    DELXS(MaterialGeneric)
    DELXS(TextureApplication)
    DELXS(TextureDefinition)
    DELXS(DottingPattern)
    DELXS(HatchingPattern)
    DELXS(SolidPattern)
    DELXS(PicturePattern)
    DELXS(Reference)
    DELXS(Filter)
    DELXS(SceneDisplayParameters)
    DELXS(Blend02Boundary3d)
    DELXS(NurbsCurve3d)
    DELXS(NurbsCurve2d)
    DELXS(Circle3d)
    DELXS(Circle2d)
    DELXS(CompositeCurve3d)
    DELXS(CompositeCurve2d)
    DELXS(2dCurveOnSurfaceCurve3d)
    DELXS(Ellipse3d)
    DELXS(Ellipse2d)
    DELXS(EquationCurve3d)
    DELXS(EquationCurve2d)
    DELXS(HelixType0Curve)
    DELXS(HelixType1Curve)
    DELXS(Hyperbola3d)
    DELXS(Hyperbola2d)
    DELXS(IntersectionCurve3d)
    DELXS(Line3d)
    DELXS(Line2d)
    DELXS(OffsetCurve3d)
    DELXS(Parabola3d)
    DELXS(Parabola2d)
    DELXS(PolyLine3d)
    DELXS(PolyLine2d)
    DELXS(TransformedCurve3d)
    DELXS(TransformedCurve2d)
    DELXS(AmbientLight)
    DELXS(DirectionalLight)
    DELXS(PointLight)
    DELXS(SpotLight)
    DELXS(Blend01Surface)
    DELXS(Blend02Surface)
    DELXS(Blend03Surface)
    DELXS(NurbsSurface)
    DELXS(Cone)
    DELXS(Cylinder)
    DELXS(CylindricalSurface)
    DELXS(OffsetSurface)
    DELXS(Plane)
    DELXS(RuledSurface)
    DELXS(Sphere)
    DELXS(RevolutionSurface)
    DELXS(ExtrusionSurface)
    DELXS(FromCurvesSurface)
    DELXS(Torus)
    DELXS(TransformedSurface)
    DELXS(SingleWireBody)
    DELXS(BrepData)
    DELXS(Camera)
    DELXS(WireEdge)
    DELXS(Connex)
    DELXS(Shell)
    DELXS(Face)
    DELXS(Loop)
    DELXS(CoEdge)
    DELXS(Edge)
    DELXS(UniqueVertex)
    DELXS(MultipleVertex)
    DELXS(Math1dArcTanCos)
    DELXS(Math1dCombination)
    DELXS(Math1dFraction)
    DELXS(Math1dPolynom)
    DELXS(Math1dTrigonometric)
    DELXS(Math3dLinear)
    DELXS(Math3dNonLinear)
  }
};

void OdPrcDumpModule::initApp()
{
  // Register OdDbEntity_Dumper with ODA Platform
  OdPrcEntity_Dumper::rxInit();
  m_pDumpers = new Dumpers;
  m_pDumpers->addXs();
}

void OdPrcDumpModule::uninitApp()
{
  m_pDumpers->delXs();
  OdPrcEntity_Dumper::rxUninit();
  delete m_pDumpers;
  m_pDumpers = 0;
}
