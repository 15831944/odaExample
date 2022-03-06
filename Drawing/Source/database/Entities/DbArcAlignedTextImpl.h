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

#ifndef _ODDBAATEXTIMPL_INCLUDED_
#define _ODDBAATEXTIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "Gi/GiTextStyle.h"
#include "DbArcAlignedText.h"
#include "TextStyleRef.h"

class CharProps
{
public:
  OdString m_Char;
  double m_Width;
  double m_LastPos;
  double m_MinX;
  double m_Angle;
  double m_Radius;
  OdGePoint3d m_Position;
  OdGeVector3d m_Dir;
  bool m_IsUnderline;
  OdGePoint3d m_UnderPoints[2];

  CharProps() : m_Width(0.0), m_LastPos(0.0), m_MinX(0.0), 
    m_Angle(0.0), m_Radius(0.0), m_IsUnderline(false) {}
};

typedef OdArray<CharProps> PropsArray;

class OdDbArcAlignedTextImpl : public TextStyleRef<OdDbEntityImpl>
                             , public OdGiTextStyle
{
  static OdDbArcAlignedTextImpl* getImpl(const OdDbArcAlignedText *pObj)
  { return (OdDbArcAlignedTextImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  ODRX_HEAP_OPERATORS();  // ODRX_USING_HEAP_OPERATORS() causes mac compiler error

  OdCmEntityColor   m_TextColor;
  OdUInt16          m_ReversedCharOrder;  // 0 - normal, 1-reverse
  OdUInt16          m_Alignment;          // 2 - left; 4 - center; 1 - fit along the arc; 3 - right
  OdUInt16          m_TextPosition;       // 1 - on convex side; 2 - on concave side
  OdUInt16          m_WizardFlag;         // 0 - off, 1 - on
  OdUInt16          m_TextDirection;      // 1 - outward from center; 2- inward to the center
  OdString          m_strText;
  double            m_dOffsetFromArc;
  double            m_dRightOffset;
  double            m_dLeftOffset;

  OdGePoint3d       m_Point;
  OdGeVector3d      m_vNormal;
  double            m_dRadius;
  double            m_dStartAngle;
  double            m_dEndAngle;

  double            m_dCharSpacing;
  PropsArray        m_PropChars;
  OdString          m_TextStyleName;

  OdDbArcAlignedTextImpl();

  OdUInt16 isShxFont() const    { return OdUInt16(OdGiTextStyle::isShxFont() ? 1 : 0); }
  void setShxFont(OdUInt16 val) { OdGiTextStyle::setShxFont(val!=0); }

  double charSpacing() const      { return m_dCharSpacing; }
  void setCharSpacing(double val) { m_dCharSpacing = val; }

  OdDbObjectId arcId() const;
  void setArcId(OdDbObjectId id);
  void setArcIdAndFillData(OdDbObjectId id);

  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void audit(OdDbAuditInfo* pAuditInfo);
  OdAnsiString getAnsiText() const;
  void copyStyleData();

private:
  OdDbSoftPointerId m_ArcId;

  friend class OdDbArcAlignedText;
};

#endif // _ODDBAATEXTIMPL_INCLUDED_
