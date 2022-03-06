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
    , m_AttachPt(OdDbMText::kTopLeft)
    , m_DrawDir(OdDbMText::kLtoR)
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

  void setXDirWithCheck(const OdGeVector3d&, OdDbAuditInfo *, OdDbObjectId);
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

  void setNormalWithCheck(const OdGeVector3d& v, OdDbAuditInfo * pA, OdDbObjectId id)
  { m_vNmal = checkNormal(v, pA, id);}
  OdDb::TextHorzMode horizontalMode() const
  {
    switch(m_AttachPt)
    {
    case OdDbMText::kTopCenter:
    case OdDbMText::kBottomCenter:
    case OdDbMText::kMiddleCenter:
      return OdDb::kTextCenter;

    case OdDbMText::kTopRight:
    case OdDbMText::kMiddleRight:
    case OdDbMText::kBottomRight:
      return OdDb::kTextRight;
    }

    return OdDb::kTextLeft;
  }
  void setHorizontalMode(OdDb::TextHorzMode mode);
  OdDb::TextVertMode verticalMode() const
  {
    switch(m_AttachPt)
    {
    case OdDbMText::kMiddleLeft:
    case OdDbMText::kMiddleCenter:
    case OdDbMText::kMiddleRight:
      return OdDb::kTextVertMid;

    case OdDbMText::kBottomLeft:
    case OdDbMText::kBottomCenter:
    case OdDbMText::kBottomRight:
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
  OdArray<OdDbObjectId> m_childsId; // saving child id 
  OdArray<OdString> m_childsContent; // saving child text string 

  OdInt32 m_numColumns;
  OdDbMText::ColumnType m_type;
  bool m_autoHeight;
  bool m_flowReversed;

  OdColumnsData() : m_type(OdDbMText::kNoColumns)
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
  OdCmColor         m_backgroundColor;
  OdCmTransparency  m_backgroundTransparency;
  OdUInt8           m_backgroundFlags;

  OdBackgroundData() : m_backgroundFlags(0)
    , m_backgroundScaleFactor(1.5)
  {
    m_backgroundColor.setColorMethod(OdCmEntityColor::kNone);
  }

};

class OdDbMTextImpl : public TextStyleRef<OdDbEntityImpl>, public OdMTextRendererData
{
  static OdDbMTextImpl* getImpl(const OdDbMText *pObj)
  { return (OdDbMTextImpl*)OdDbSystemInternals::getImpl(pObj);}


public:
  OdBackgroundData  m_backgroundData;
  OdColumnsData     m_columnsData;
  FragmentsArray    m_Fragments;
  OdUInt32          m_cntStyleChanges;
  OdString          m_strTextR18;
  OdDbObjectId      m_idRegAppTableRec;
  OdInt16           m_nVersion;
  bool              m_bDefault;
  bool              m_bAttribute;
  bool              m_bColumnMText;

  OdDbMTextImpl();

  DBENT_EXPORT static void drawMText(OdGiWorldDraw* pWd, OdMTextRendererData& data, OdDbObjectId textStyleId, bool bRaw, FragmentsArray* fragments, bool doDraw = true);
  void makeFragments(OdGiWorldDraw *ctxt, const OdDbObject* pObj);
  
  virtual void copyFromContextData(OdDbObject*, OdDbObjectContextData* pData, OdDbObjectContextData* pDataDef);
  void decomposeForSave(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void audit(OdDbAuditInfo* pAuditInfo);
  void correctTextCoding();
  void correctUnicodeWithCIF();

  void clearCache()
  {
    m_Fragments.clear();
  }
  OdString getR15String(OdDbDatabase* pDb, OdMTextRendererData& data);
  OdString getR18String(OdDbDatabase* pDb, OdMTextRendererData& data);

  OdString getLowVersionString(OdDbDatabase* pDb, OdMTextRendererData& data, bool bR15);
  OdGePoint3d getFirstColumnPos(const OdMTextRendererData& data, const OdColumnsData& columnsData);
  void addjustColumn(OdGePoint3d& statPt, double totalHeight, OdUInt8 attachPt);
  void transformBy(const OdGeMatrix3d& xform, bool mirrText);
  double rotation(const OdGeVector3d& planeVec) const;
  bool getAnnotativeTextParams(const OdDbMText* obj, OdDbMTextObjectContextData* ctx, OdMTextRendererData& rndData, FragmentsArray* pFragmentsArray = nullptr);

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler, OdDbObject* pObject);
  void dxfOutFields(OdDbDxfFiler* pFiler, const OdDbMText* pEnt) const;

  OdResult dxfInEmbObject(OdDbDxfFiler* pFiler);
  void dxfOutEmbObject(OdDbDxfFiler* pFiler) const;

  static void drawVMText(OdGiCommonDraw* pWd, OdMTextRendererData& data, TextProps* textStyle, bool bRaw, FragmentsArray* fragments);
  static void drawHMText(OdGiCommonDraw* pWd, OdMTextRendererData& data, TextProps* textStyle, bool bRaw, FragmentsArray* fragments);

  void drawMText(OdGiWorldDraw* pWd, const OdDbObject* pObj, bool doDraw); 
  void drawMultiColumnsHMText(OdGiCommonDraw* pWd, OdMTextRendererData& data, OdColumnsData& columnsData, TextProps* textStyle, FragmentsArray* fragments); //const OdString& str, bool bHasField); //, OdMTextRendererData& data, TextProps* textStyle, bool bRaw, FragmentsArray* fragments);
//  OdCmColor backgroundColor() const;
  void drawFragments(OdGiGeometry& geom, OdGiCommonDraw* pWd, OdMTextRendererData* data, FragmentsArray* fragments) const;
  void processFields(OdGiCommonDraw* pWd, FragmentsArray* fragments) const;

  void getBoundingPoints(OdGePoint3dArray& array, const OdMTextRendererData& data) const;
  void calcBoundingPoints(double width, double actHeight, const OdMTextRendererData& data, OdGePoint3dArray& array) const;

  void drawBackground(OdGiGeometry& geom, OdGiCommonDraw* pWd, const OdBackgroundData& bgrData, 
    const OdMTextRendererData& data, const OdColumnsData& columnsData);
  
  void backgroundPoints(const OdBackgroundData& bgrData, const OdMTextRendererData& data, const OdColumnsData& columnsData,
    OdGePoint3dArray& points, OdGePoint3dArray& framePts);

  void calcRealExtents(FragmentsArray* fragments, OdMTextRendererData* data);

  OdString decomposeMText(OdDbDatabase* pWd, OdMTextRendererData& data, OdColumnsData& columnsData, OdDb::DwgVersion version);
  OdString textContent(OdDbDatabase* pDb, OdMTextRendererData& data);
  void multiColunmDataCorrect(OdDbDatabase* pDb);
  friend class OdDbMText;
  friend class OdDbAttributeImpl;
  friend class OdDbAttribute;
  friend class OdDbAttributeDefinition;
  friend class OdDbAttributeDefinitionImpl;
  friend class OdDbTableImpl;
  friend class OdDbLeaderImpl;
//  friend class BackgroundColorNameDxfLoadResolver;
};

#endif // _ODDBMTEXTIMPL_INCLUDED_
