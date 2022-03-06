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

#ifndef _ODDBMTEXTIMPL_INCLUDED_
#define _ODDBMTEXTIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbMText.h"
#include "TextStyleRef.h"
#include "OdMTextIterator.h"
#include "DbObjectContextDataManager.h"
#include "Ge/GeDoubleArray.h"

class OdMTextRendererData
{
public:
  OdMTextRendererData()
    : m_XDir(OdGeVector3d::kXAxis)
    , m_vNmal(OdGeVector3d::kZAxis)
    , m_dRefRectWidth(0.0)
    , m_dRefRectHeight(0.0)
    , m_dHeight(0.0)
    , m_dLinespacingFactor(1.0)
    , m_LinespacingStyle(OdDb::kAtLeast)
    , m_AttachPt(OdTvDbMText::kTopLeft)
    , m_DrawDir(OdTvDbMText::kLtoR)
    , m_dBoxHeight(0.0)
    , m_dBoxWidth(0.0)
    , m_hasField(false)
    , m_cols(1)
    , m_bIsVertical(false)
    , m_bTextInTable(false)
    , m_ascent(0.0)
    , m_descent(0.0)
    , m_pViewPort(0)
    , m_dCheckSum(0.0)
    , m_bTileMod(true)
    , m_bPaperOriented(false)
    , m_bMultiColumn(false)
  {}

  double            m_dRefRectWidth;
  double            m_dRefRectHeight;
  double            m_dHeight;
  double            m_dLinespacingFactor;
  double            m_dBoxHeight;
  double            m_dBoxWidth;
  double            m_ascent;
  double            m_descent;
  double            m_dCheckSum;
  OdGePoint3d       m_Location;
  OdGePoint3d       m_Min;
  OdGePoint3d       m_Max;

  OdGeVector3d      m_XDir;
  OdGeVector3d      m_vNmal;

  OdString          m_strText;
  OdAnsiString      m_ansiStrText;
  OdGiViewport*     m_pViewPort;
  bool              m_bTileMod;
  bool              m_bPaperOriented;

  OdInt32           m_cols;
  OdInt16           m_LinespacingStyle;
  OdUInt8           m_AttachPt;
  OdUInt8           m_DrawDir;
  bool              m_hasField;
  bool              m_bIsVertical;
  bool              m_bTextInTable;
  bool              m_bMultiColumn;

  void setXDirWithCheck(const OdGeVector3d&, OdTvDbAuditInfo *, OdTvDbObjectId);
  const OdGeVector3d& normal() const {return m_vNmal;}
  void setNormal(const OdGeVector3d& normalv)
  {
    double dLen = normalv.length();
    if (dLen <= OdGeContext::gTol.equalVector())
    {
      throw OdError(eInvalidInput);
    }
    m_vNmal = normalv / dLen;
  }

  void setNormalWithCheck(const OdGeVector3d& v, OdTvDbAuditInfo * pA, OdTvDbObjectId id)
  { m_vNmal = checkNormal(v, pA, id);}
  OdDb::TextHorzMode horizontalMode() const
  {
    switch(m_AttachPt)
    {
    case OdTvDbMText::kTopCenter:
    case OdTvDbMText::kBottomCenter:
    case OdTvDbMText::kMiddleCenter:
      return OdDb::kTextCenter;

    case OdTvDbMText::kTopRight:
    case OdTvDbMText::kMiddleRight:
    case OdTvDbMText::kBottomRight:
      return OdDb::kTextRight;
    }

    return OdDb::kTextLeft;
  }
  void setHorizontalMode(OdDb::TextHorzMode mode);
  OdDb::TextVertMode verticalMode() const
  {
    switch(m_AttachPt)
    {
    case OdTvDbMText::kMiddleLeft:
    case OdTvDbMText::kMiddleCenter:
    case OdTvDbMText::kMiddleRight:
      return OdDb::kTextVertMid;

    case OdTvDbMText::kBottomLeft:
    case OdTvDbMText::kBottomCenter:
    case OdTvDbMText::kBottomRight:
      return OdDb::kTextBottom;
    }
    return OdDb::kTextTop;
  }
  void setVerticalMode(OdDb::TextVertMode mode);
};

class OdColumnsData
{
public:
  double m_gutter;
  double m_colWidth;
  double m_lastColumnRenderedHeight;

  OdGeDoubleArray m_colHeights;
  OdGeDoubleArray m_colActWidths;
  OdGeDoubleArray m_colActHeights;
  OdArray<OdTvDbObjectId> m_childsId; // saving child id 
  OdArray<OdString> m_childsContent; // saving child text string 

  OdInt32 m_numColumns;
  OdTvDbMText::ColumnType m_type;
  bool m_autoHeight;
  bool m_flowReversed;

  OdColumnsData() : m_type(OdTvDbMText::kNoColumns)
    , m_autoHeight(false)
    , m_numColumns(0)
    , m_flowReversed(false)
    , m_gutter(0.0)
    , m_colWidth(0.0)
    , m_lastColumnRenderedHeight(0.0)
  {}
};

class OdBackgroundData
{
public:
  double            m_backgroundScaleFactor;
  OdTvCmColor         m_backgroundColor;
  OdTvCmTransparency  m_backgroundTransparency;
  OdUInt8           m_backgroundFlags;

  OdBackgroundData() : m_backgroundFlags(0)
    , m_backgroundScaleFactor(1.5)
  {
    m_backgroundColor.setColorMethod(OdCmEntityColor::kNone);
  }

};

class OdTvDbMTextImpl : public TextStyleRef<OdTvDbEntityImpl>, public OdMTextRendererData
{
  static OdTvDbMTextImpl* getImpl(const OdTvDbMText *pObj)
  { return (OdTvDbMTextImpl*)OdTvDbSystemInternals::getImpl(pObj);}


public:
  OdBackgroundData  m_backgroundData;
  OdColumnsData     m_columnsData;
  FragmentsArray    m_Fragments;
  OdUInt32          m_cntStyleChanges;
  OdString          m_strTextR18;
  OdTvDbObjectId      m_idRegAppTableRec;
  OdInt16           m_nVersion;
  bool              m_bDefault;
  bool              m_bAttribute;
  bool              m_bColumnMText;

  OdTvDbMTextImpl();

  DBENT_EXPORT static void drawMText(OdGiWorldDraw* pWd, OdMTextRendererData& data, OdTvDbObjectId textStyleId, bool bRaw, FragmentsArray* fragments, bool doDraw = true);
  void makeFragments(OdGiWorldDraw *ctxt, const OdTvDbObject* pObj);
  
  virtual void copyFromContextData(OdTvDbObject*, OdTvDbObjectContextData* pData, OdTvDbObjectContextData* pDataDef);
  void decomposeForSave(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void audit(OdTvDbAuditInfo* pAuditInfo);
  void correctTextCoding();
  void correctUnicodeWithCIF();

  void clearCache()
  {
    m_Fragments.clear();
  }
  OdString getR15String(OdTvDbDatabase* pDb, OdMTextRendererData& data);
  OdString getR18String(OdTvDbDatabase* pDb, OdMTextRendererData& data);

  OdString getLowVersionString(OdTvDbDatabase* pDb, OdMTextRendererData& data, bool bR15);
  OdGePoint3d getFirstColumnPos(const OdMTextRendererData& data, const OdColumnsData& columnsData);
  void addjustColumn(OdGePoint3d& statPt, double totalHeight, OdUInt8 attachPt);
  void transformBy(const OdGeMatrix3d& xform, bool mirrText);
  double rotation(const OdGeVector3d& planeVec) const;
  bool getAnnotativeTextParams(const OdTvDbMText* obj, OdTvDbMTextObjectContextData* ctx, OdMTextRendererData& rndData);

private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObject* pObject);
  void dxfOutFields(OdTvDbDxfFiler* pFiler, const OdTvDbMText* pEnt) const;

  OdResult dxfInEmbObject(OdTvDbDxfFiler* pFiler);
  void dxfOutEmbObject(OdTvDbDxfFiler* pFiler) const;

  static void drawVMText(OdGiCommonDraw* pWd, OdMTextRendererData& data, TextProps* textStyle, bool bRaw, FragmentsArray* fragments);
  static void drawHMText(OdGiCommonDraw* pWd, OdMTextRendererData& data, TextProps* textStyle, bool bRaw, FragmentsArray* fragments);

  void drawMText(OdGiWorldDraw* pWd, const OdTvDbObject* pObj, bool doDraw); 
  void drawMultiColumnsHMText(OdGiCommonDraw* pWd, OdMTextRendererData& data, OdColumnsData& columnsData, TextProps* textStyle, FragmentsArray* fragments); //const OdString& str, bool bHasField); //, OdMTextRendererData& data, TextProps* textStyle, bool bRaw, FragmentsArray* fragments);
//  OdTvCmColor backgroundColor() const;
  void drawFragments(OdGiGeometry& geom, OdGiCommonDraw* pWd, OdMTextRendererData* data, FragmentsArray* fragments) const;
  void processFields(OdGiCommonDraw* pWd, FragmentsArray* fragments) const;

  void getBoundingPoints(OdGePoint3dArray& array, const OdMTextRendererData& data) const;
  void calcBoundingPoints(double width, double actHeight, const OdMTextRendererData& data, OdGePoint3dArray& array) const;

  void drawBackground(OdGiGeometry& geom, OdGiCommonDraw* pWd, const OdBackgroundData& bgrData, 
    const OdMTextRendererData& data, const OdColumnsData& columnsData);
  
  void backgroundPoints(const OdBackgroundData& bgrData, const OdMTextRendererData& data, const OdColumnsData& columnsData,
    OdGePoint3dArray& points, OdGePoint3dArray& framePts);

  void calcRealExtents(FragmentsArray* fragments, OdMTextRendererData* data);

  OdString decomposeMText(OdTvDbDatabase* pWd, OdMTextRendererData& data, OdColumnsData& columnsData, OdDb::DwgVersion version);
  OdString textContent(OdTvDbDatabase* pDb, OdMTextRendererData& data);
  void multiColunmDataCorrect(OdTvDbDatabase* pDb);
  friend class OdTvDbMText;
  friend class OdTvDbAttributeImpl;
  friend class OdTvDbAttribute;
  friend class OdTvDbAttributeDefinition;
  friend class OdTvDbAttributeDefinitionImpl;
  friend class OdTvDbTableImpl;
  friend class OdTvDbLeaderImpl;
//  friend class BackgroundColorNameDxfLoadResolver;
};

#endif // _ODDBMTEXTIMPL_INCLUDED_
