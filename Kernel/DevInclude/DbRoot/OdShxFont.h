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


#ifndef _OD_SHXFONT_INCLUDED_
#define _OD_SHXFONT_INCLUDED_

#define  STL_USING_STACK
#define  STL_USING_MAP
#include "OdaSTL.h"

#include "OdFont.h"
#include "DbRootExport.h"
#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeCircArc3d.h"
#include "OdBinaryData.h"
#include "OdStreamBuf.h"
#include "Ge/GeBoundBlock2d.h"
#include "Gi/OdPolyPolygon3d.h"
#include "OdMutex.h"
#include "OdArray.h"
#include "TPtr.h"

class OdShxVectorizer;

enum odShxTypeText
{
  enShxHorChar = 0,
  enShxHorCharWithPenUp = 1,
  enShxVertChar = 2,
  enShxVertCharWithPenUp = 3
};

struct FontCircle
{
  OdGePoint2d center;
  double      radius;
};

struct FontArc
{
  OdGePoint2d p1;
  OdGePoint2d p2;
  OdGePoint2d p3;
};

class _TypeShapeInfo
{
public:
  bool              bboxValid;
  OdGePoint2d       advance;
  OdGePoint2d       m_MinPoint;
  OdGePoint2d       m_MaxPoint;
  OdPolyPolygon3d   m_Ppg; // used for enShxHorChar and enShxVertChar
  OdArray<FontArc>  m_CircArc;
  OdArray<FontCircle> m_Circles;
  _TypeShapeInfo() : bboxValid(false), m_nRefCounter(1){}
  _TypeShapeInfo(const _TypeShapeInfo& o) : m_nRefCounter(1),
    bboxValid(o.bboxValid), advance(o.advance),
    m_MinPoint(o.m_MinPoint), m_MaxPoint(o.m_MaxPoint)
  {
    //make own copy of data
    makeGeomCopy(o);
  }

  void reset()
  {
    m_Ppg.points().clear();
    m_Ppg.counts().clear();
    m_CircArc.clear();
    m_Circles.clear();
    bboxValid = false;
  }
  void copyFrom(const _TypeShapeInfo& o)
  {
    reset();
    bboxValid = o.bboxValid;
    advance = o.advance;
    m_MinPoint = o.m_MinPoint;
    m_MaxPoint = o.m_MaxPoint;
    //make own copy of data
    makeGeomCopy(o);
  }
  void addRef() { ++m_nRefCounter; }
  void release();
  long numRefs() const { return m_nRefCounter; }

private:
  void makeGeomCopy(const _TypeShapeInfo& o)
  {
    if(o.m_Ppg.points().size())
      m_Ppg.points().append(o.m_Ppg.points());
    if(o.m_Ppg.counts().size())
      m_Ppg.counts().append(o.m_Ppg.counts());
    if(o.m_CircArc.size())
      m_CircArc.append(o.m_CircArc);
    if(o.m_Circles.size())
      m_Circles.append(o.m_Circles);
  }

private:
  mutable OdRefCounter m_nRefCounter;
};
typedef TPtr<_TypeShapeInfo> _TypeShapeInfoPtr;

class _OdShapeInfo
{
public:
  OdInt32           position;
  _TypeShapeInfoPtr m_ShapeInfo[4];
  _OdShapeInfo() : position(0) {}
};
typedef std::map<OdUInt16, _OdShapeInfo> OdShapeMap;

class OdShxFont;
class OdGiConveyorGeometry;
class OdShxVectorizer;
typedef OdSmartPtr<OdShxFont> OdShxFontPtr;
typedef std::stack<OdGePoint2d> OdShapePositionStack; // CORE13429

//Service class for support and optimization of repetitive
//OdShxFont::drawCharacter() calls when generating a text
class DBROOT_EXPORT OdShxTextData
{
public:
  OdShxTextData(bool bEnable);
  ~OdShxTextData();

  //returns last scale calculated in drawCharacter() call
  bool hasScale() const;
  //returns true if initialized
  operator bool() const { return m_pImpl != NULL; }

private:
  class Impl;
  Impl* m_pImpl;
  Impl* impl() { return m_pImpl; }

  friend class OdShxFont;
};

class DBROOT_EXPORT OdShxFont : public OdFont
                              , protected OdMutex
{
public:
  typedef struct
  {
    OdInt32   m_FileLoc;
    OdUInt16 m_ShapeNo;
  } CharLoc;

private:
  OdInt16 m_MinShp;
  OdInt16 m_MaxShp;

  void readSignature();
  bool createSmallIndex(OdShxVectorizer& vec);
  _TypeShapeInfoPtr getShapeInfo(OdChar character, const OdTextProperties& textFlags, bool bForExtents = false);

protected:
  OdShxFontPtr   m_SHXfont; // for big font subshape
  OdBinaryData   m_RawData;
  OdShapeMap     m_Index;
  double         m_Above;
  double         m_Below;
  OdUInt8        m_Modes;
  OdUInt8        m_BfHeight;
  OdUInt8        m_BfWidth;
  mutable OdMutex m_localMutex;
  OdString       m_fileName;

  static OdInt32 readFontFlags(OdStreamBuf* io);
  void setMinShp(OdInt16 value) { m_MinShp = value; }
  OdInt16 getMinShp() const { return m_MinShp; }

  void setMaxShp(OdInt16 value) { m_MaxShp = value; }
  OdInt16 getMaxShp() const { return m_MaxShp; }

public:
  ODRX_DECLARE_MEMBERS(OdShxFont);

  OdShxFont();
  virtual ~OdShxFont();

  OdUInt8 getBfWidth() const { return m_BfWidth; }
  OdUInt8 getBfHeight() const { return m_BfHeight; }

  //OdaFont interface

  virtual double getAbove() const;
  virtual double getBelow() const;
  virtual OdResult initialize(OdStreamBuf* io);
  virtual OdResult drawCharacter(OdChar character,
                                 OdGePoint2d& advance,
                                 OdGiCommonDraw* pWd,
                                 OdTextProperties& textFlags);
  virtual OdResult drawCharacter(OdChar character, OdGePoint2d& advance,
                                 OdGiConveyorGeometry* pGeom,
                                 OdTextProperties& textFlags);
  virtual OdString shapeNameByIndex(OdUInt16 index);
  virtual OdUInt16 shapeIndexByName(const OdString& name);

  //Returns all characters available in this font.
  virtual OdUInt32 getAvailableChars(OdCharArray& retArray);

  virtual bool hasCharacter(OdChar character);

  static OdShxFontPtr createFont(OdStreamBuf* io);

  OdResult loadFromInitFile(OdStreamBuf* io,
    OdInt32 numEntries,
    OdInt32 dataSize,
    OdInt32 above,
    OdInt32 below,
    OdInt32 modes,
    OdInt32 subType);

  void setMainShxFont(OdShxFont* font)
  {
    m_SHXfont = font;
  }

  const OdShxFont* getMainShxFont() const
  {
    return m_SHXfont;
  }

  virtual void getScore( OdChar character, 
                         OdGePoint2d& advance, 
                         OdGePoint3d* pointsOver,
                         OdGePoint3d* pointsUnder,
                         const OdTextProperties& textFlags);
  
  virtual bool supportsVerticalMode();

  void setFileName(const OdString& fileName);
  OdString getFileName() const;
  virtual void getDescriptor(OdTtfDescriptor& descr) const;
  friend class OdShxVectorizer;

  OdResult drawCharacterImp(OdChar character, OdGePoint2d& advance, OdGiCommonDraw* pWd,
    OdTextProperties& textFlags, OdShxTextData* pOdShxTextData);
  OdResult drawCharacterImp(OdChar character, OdGePoint2d& advance, OdGiConveyorGeometry* pGeom,
    OdTextProperties& textFlags, OdShxTextData* pOdShxTextData);
private:
  _TypeShapeInfoPtr getShapeInfoImp(OdChar character, const OdTextProperties& textFlags, 
    bool bForExtents, OdShxTextData* pOdShxTextData);
  OdShapeMap::iterator getEnd() { return m_Index.end(); }
  OdShapeMap::iterator find(OdUInt16 ch);
};


#endif // _OD_SHXFONT_INCLUDED_
