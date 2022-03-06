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

#ifndef _ODDBMLINESTYLE_INCLUDED_
#define _ODDBMLINESTYLE_INCLUDED_

#include "DbSystemInternals.h"
#include "DbMlineStyle.h"

#include "OdArray.h"
#include "CmColor.h"
#include "DbObjectImpl.h"


class OdTvDbMlineStyleImpl : public OdTvDbObjectImpl
{
public:
  static OdTvDbMlineStyleImpl* getImpl(const OdTvDbMlineStyle *pObj)
  { return (OdTvDbMlineStyleImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdString      m_strMLineStyleName;
  OdString      m_strStyleDescription;
  OdTvCmColor     m_fillColor;
  double        m_dStartAngle;
  double        m_dEndAngle;

  // 1 = Fill on
  // 2 = Display miters
  // 16 = Start square end (line) cap
  // 32 = Start inner arcs cap
  // 64 = Start round (outer arcs) cap
  // 256 = End square (line) cap
  // 512 = End inner arcs
  // 1024 = End round (outer arcs) cap
  OdUInt16  m_Flags;

	class Segment
	{
	public:
		OdTvCmColor     m_color;
    OdTvDbObjectId  m_LinetypeId;
		double        m_dOffset;

  public:
		OdTvCmColor     getColor() const {return m_color;}
		void setColor(const OdTvCmColor    & color) {m_color = color;}

  	OdTvDbObjectId& linetypeId() { return m_LinetypeId; }
	  const OdTvDbObjectId& getLinetypeId() const { return m_LinetypeId; }

		double getOffset() const {return m_dOffset;}
		void setOffset(double offset) {m_dOffset = offset;}

    void set(const OdTvCmColor& color, const OdTvDbObjectId& id, double offset);

    Segment() : m_dOffset(0.0) {}

    bool operator ==(const Segment &seg2) const
    {
      return m_color == seg2.m_color && m_LinetypeId == seg2.m_LinetypeId;
    }
    bool operator !=(const Segment &seg2) const
    {
      return m_color != seg2.m_color || m_LinetypeId != seg2.m_LinetypeId;
    }
	};

	typedef OdArray<Segment> SegmentArray;

  SegmentArray m_Segments;

public:
  OdTvDbMlineStyleImpl();

  int addElement(double offset, const OdTvCmColor& color, const OdTvDbObjectId& linetypeId, bool bSort = false);
  void setElement(int id, double offset, const OdTvCmColor& color, const OdTvDbObjectId& linetypeId, bool bSort = false);

  void audit(OdTvDbAuditInfo* pAuditInfo);

  OdResult dxfInFields  (OdTvDbDxfFiler* pFiler, OdTvDbMlineStyle* pObj); // OSHA 23/08/2005
  void  dxfOutFields(OdTvDbDxfFiler* pFiler);     // OSHA 07/09/2005
  void  fixName(OdTvDbMlineStyle* pObj, OdTvDbAuditInfo* pAuditInfo);
private:

  bool isValidName(const OdString&);

  friend class OdTvDbMlineStyle;
  friend class OdTvDbMline;
  friend class OdTvDbMlineImpl;

};

#endif // _ODDBMLINESTYLE_INCLUDED_
