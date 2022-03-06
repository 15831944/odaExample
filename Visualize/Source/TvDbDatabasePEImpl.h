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

#ifndef _ODTV_DBDATABASEPEIMPL_H_INCLUDED_
#define _ODTV_DBDATABASEPEIMPL_H_INCLUDED_

#include "DbBaseDatabasePEImpl.h"
#include "OdDbStub.h"

/** \details
This class implements the protocol extension for the Visualize SDK internal (DB) db layout (which is equal to database)
*/
class OdTvLayoutPEImpl : public OdBaseLayoutPEImpl
{
public:
  virtual OdString name(const OdRxObject*);
  virtual bool isModelLayout(const OdRxObject*);
  virtual bool printLineweights(const OdRxObject*);
  virtual bool showPlotStyles(const OdRxObject*);
  virtual OdString paperName(const OdRxObject*);
  virtual void getPaperSize(const OdRxObject*, double& paperWidth, double& paperHeight) const;
  virtual OdDbBaseLayoutPE::PlotRotation plotRotation(const OdRxObject*);
  virtual double getTopMargin(const OdRxObject*);
  virtual double getRightMargin(const OdRxObject*);
  virtual double getBottomMargin(const OdRxObject*);
  virtual double getLeftMargin(const OdRxObject*);
  virtual bool isOverallVPortErased(const OdRxObject*);
  virtual OdResult getGeomExtents(const OdRxObject*, OdGeExtents3d& ext);

  virtual bool useStandardScale(const OdRxObject*);
  virtual void getStdScale(const OdRxObject*, double& scale);
  virtual void getCustomPrintScale(const OdRxObject*, double& numerator, double& denominator);
  virtual int plotType(const OdRxObject*);
  virtual OdString getPlotViewName(const OdRxObject*);
  virtual void getPlotWindowArea(const OdRxObject*, double& xmin, double& ymin, double& xmax, double& ymax);
  virtual void getPlotOrigin(const OdRxObject*, double& x, double& y);
  virtual void getPlotPaperSize(const OdRxObject*, double& paperWidth, double& paperHeight);
  virtual int plotPaperUnits(const OdRxObject*);

  virtual OdDbStub* getBlockId(const OdRxObject*) const;
  virtual bool scalePSLinetypes(const OdRxObject*) const;
  virtual bool getApproxExtents(const OdRxObject*, OdGePoint3d& extMin, OdGePoint3d& extMax) const;
};


/** \details
This class implements the protocol extension for the Visualize SDK internal (DB) database
*/
class OdTvDbDatabasePEImpl : public OdBaseDatabasePEImpl
{
public:
  virtual OdDbBaseHostAppServices* appServices(OdDbBaseDatabase* pDb) const;
  virtual OdString getFilename(OdDbBaseDatabase* pDb) const;
  virtual OdGiDefaultContextPtr createGiContext(OdDbBaseDatabase* pDb) const;
  virtual void putNamedViewInfo(OdDbBaseDatabase* pDb, OdDbStub* layoutInfo, 
                                 OdStringArray& names, OdGePoint3dArray& points);

  OdBaseTextIteratorPtr createTextIterator(OdDbBaseDatabase* db, const OdChar* textString, int length, bool raw, const OdGiTextStyle* pTextStyle) const;

  virtual OdGsDevicePtr setupActiveLayoutViews(OdGsDevice* pDevice, OdGiDefaultContext* pGiCtx);
  virtual OdGsDevicePtr setupLayoutView(OdGsDevice* pDevice, OdGiDefaultContext* pDgnContext,
                                        OdDbStub* objectId);
  virtual void setupPalette(OdGsDevice* device, OdGiDefaultContext* giContext, 
                            OdDbStub* layoutId = 0, ODCOLORREF palBg = ODRGBA(0,0,0,0));
  virtual OdDbStub* getNextViewForActiveLayout(OdGiDefaultContext* pDgnContext, OdDbStub* objectId);
  virtual void loadPlotstyleTableForActiveLayout(OdGiDefaultContext* pTdContext, OdDbBaseDatabase* db);

  virtual void startTransaction(OdDbBaseDatabase* pDb);
  virtual void abortTransaction(OdDbBaseDatabase* pDb);

  virtual void applyLayoutSettings(OdGsDCRect& clipBox, OdGsDevice* pDevice, OdDbBaseDatabase* db, OdUInt32 extentsFlags = kZeroFlags, OdUInt32 dpi = 72);
  virtual void zoomToExtents(const OdGsDCRect& outputRect, OdGsDevice* pDevice, OdDbBaseDatabase* db, OdGeBoundBlock3d& plotExtents,
                             OdUInt32 extentsFlags = kZeroFlags, OdDbStub* objectId = NULL);
  virtual OdRxIteratorPtr layers(OdDbBaseDatabase* db) const;
  virtual OdRxIteratorPtr visualStyles(OdDbBaseDatabase* db) const;
  virtual void setCurrentLayout(OdDbBaseDatabase* db, const OdString& name);
  virtual OdRxIteratorPtr layouts(OdDbBaseDatabase* db) const;
  virtual OdDbStub* findLayoutIdByViewport(OdDbBaseDatabase* db, OdDbStub* pViewportId);

  // returns the first visible view Id associated with model named name
  virtual OdDbStub* findLayoutNamed(OdDbBaseDatabase* db, const OdString& name);
  virtual OdDbStub* getFirstLayoutId(OdDbBaseDatabase* db);
  virtual OdTimeStamp getCreationTime(OdDbBaseDatabase* db);
  virtual OdTimeStamp getUpdateTime(OdDbBaseDatabase* db);
  virtual OdString getFingerPrintGuid(OdDbBaseDatabase* db);
  virtual OdString getVersionGuid(OdDbBaseDatabase* db);
  //virtual OdDbBaseViewTableIteratorPEPtr getViewTableIterator(OdDbBaseDatabase* db);
  virtual int getUnits(OdDbBaseDatabase* db);
  virtual OdUnitsFormatter* baseFormatter(OdDbBaseDatabase* db);
  //virtual OdDbBaseViewTablePEPtr getViewTable(OdDbBaseDatabase* db);
  virtual OdSmartPtr<class OdDbBaseViewportTablePE> getViewportTable(OdDbBaseDatabase* db);
  //virtual OdString getLayoutName(OdDbStub* elementId);
  //virtual OdDbBaseLayoutIteratorPEPtr newLayoutIteratorPE(OdDbBaseDatabasePE* db);
  virtual int getMeasurement(OdDbBaseDatabase* db);
  virtual bool getLineTypeById( OdDbBaseDatabase* db, OdDbStub* pLTypeId, OdGiLinetype& LType );
  virtual bool getTextStyleById( OdDbBaseDatabase* db, OdDbStub* idStyle, OdGiTextStyle& shapeInfo );
  virtual OdDbStub* getId(const OdRxObject* pObj) const;
  virtual OdDbStub *getObject(OdDbBaseDatabase* db, OdUInt64 handle);
  virtual OdCodePageId getCodePage(OdDbBaseDatabase* db);
  virtual OdDbStub* getModelBlockId(OdDbBaseDatabase* pDb);
  virtual OdDbStub* getPaperBlockId(OdDbBaseDatabase* pDb);
  virtual OdDbStub* currentLayoutId(OdDbBaseDatabase* pDb);
  virtual OdDbStub* xrefBlockId(OdDbBaseDatabase* pDb);
  virtual void setMultiThreadedRender(OdDbBaseDatabase* pDb, bool bOn);
  virtual bool isAProxy(OdRxObject* pDrw);
  virtual OdRxObjectPtr openObject(OdDbStub* pId);
  virtual bool getAnnoScaleSet(OdDbStub* drawableId, OdGiAnnoScaleSet& res);
  virtual OdDbStub* getCurrentLongTransation(const OdDbBaseDatabase* pDb);
  virtual bool findImage(OdDbBaseDatabase* db, OdDbStub* pObjId, OdString& path);
  virtual OdRxObjectPtr addDatabaseUnloadReactor(OdDbBaseDatabase* pDb, OdRxObject* pPrevReactor, DatabaseUnloadReactor* pReactorRedirect);
  virtual void removeDatabaseUnloadReactor(OdDbBaseDatabase* pDb, OdRxObject* pReactor);
  virtual bool getDatabasePartialViewingMode( OdDbBaseDatabase* pDb ) const;

  virtual OdResult faceConversionHelper(OdDbStub*& material, OdDbBaseDatabase* pSourceDb, OdDbBaseDatabase* pDestinationDb,
    const OdGiMaterialTraits* pMaterialTraits, const OdGiMapper* pMaterialMapper = 0, const OdCmEntityColor* pMaterialColor = 0);

  virtual OdRxObjectPtr getLayout(OdDbBaseDatabase* pDb, const OdString& name);
};

#endif //_ODTV_DBDATABASEPEIMPL_H_INCLUDED_
