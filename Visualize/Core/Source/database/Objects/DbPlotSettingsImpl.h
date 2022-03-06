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

#ifndef _ODDBPLOTSETTINGSIMPL_INCLUDED_
#define _ODDBPLOTSETTINGSIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbPlotSettings.h"
#include "FileDependency.h"
#include "DbObjectImpl.h"

class OdTvDbPlotSettingsImpl : public OdTvDbObjectImpl
{
  static OdTvDbPlotSettingsImpl* getImpl(const OdTvDbPlotSettings *pObj)
  { return (OdTvDbPlotSettingsImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint2d m_PaperImageOrigin;
  double      m_dScaleFactor;
  OdInt16     m_ScaleType;
  OdString    m_strCurrentStyleSheet;
  OdInt16     m_PlotType;
  OdInt16     m_PlotRotation;
  OdInt16     m_PlotPaperUnits;
  double      m_dDrawingUnits;
  double      m_dRealWorldUnits;
  OdGePoint2d m_WindowMax; // indicates the upper right window corner
  OdGePoint2d m_WindowMin; // indicates the lower left window corner
  OdGePoint2d m_Origin;
  double      m_dPaperHeight;
  double      m_dPaperWidth;
  double      m_dTopMargin;
  double      m_dRightMargin;
  double      m_dBottomMargin;
  double      m_dLeftMargin;
  OdTvDbHardPointerId m_plotViewId; // Id of viewTableRecord should be stored.
  OdTvDbSoftPointerId m_VisualStyleId;
  OdString    m_strPaperSize;
  OdString    m_strPrinterOrConfigFileName;
  OdString    m_storedInitialMedia;

  class Pc3FileDependency : public OdDb::TvFileDependency
  {
  public:
    Pc3FileDependency() : OdDb::TvFileDependency( OD_T("Acad:PlotConfig") ){}
    void setFileName( const OdString& name, OdTvDbDatabase* db, bool updateDependencies = true )
    {
      if ( name.getLength() < 4 || name.right( 4 ).makeLower() != OD_T(".pc3") ) return;
#if defined(sgi) || defined(__BCPLUSPLUS__)
      OdDb::
#endif
      TvFileDependency::setFileName( name, db, updateDependencies );
    }
  };
  Pc3FileDependency m_pPrinterOrConfigFilePath;

  OdDb::TvFileDependency m_pCurrentStyleSheetPath;
  OdString    m_strPageSetupName;

  /* 1 = PlotViewportBorders
  2 = ShowPlotStyles
  4 = PlotCentered
  8 = PlotHidden
  16 = UseStandardScale
  32 = PlotPlotStyles
  64 = ScaleLineweights
  128 = PrintLineweights
  512 = DrawViewportsFirst
  1024 = ModelType
  2048 = UpdatePaper
  4096 = ZoomToPaperOnUpdate
  8192 = Initializing
  16384 = PrevPlotInit */
  OdUInt16    m_PlotLayoutFlags;

  // new in acad2004 fields
  OdInt16   m_shadePlot;         // dxf 76 - shade plot mode
  OdInt16   m_shadePlotResLevel; // dxf 77 - shade plot resolution level
  OdInt16   m_shadePlotCustomDPI;

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

  OdString plotViewName() const; // instead field - need for save pre-r18 files
  void setPlotViewName(OdTvDbDatabase& Db, const OdString& name); // instead field - need for load pre-r18 files
  virtual bool isModelLayout() const;

public:
  OdTvDbPlotSettingsImpl();
private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  friend class OdTvDbPlotSettings;
  friend class OdTvDbPlotSettingsValidatorImpl;
};

#endif // _ODDBPLOTSETTINGSIMPL_INCLUDED_
