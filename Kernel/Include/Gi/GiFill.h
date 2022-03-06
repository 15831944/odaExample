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

#ifndef _OD_GIFILL_H_
#define _OD_GIFILL_H_

#include "RxObject.h"
#include "HatchPattern.h"
#include "UInt8Array.h"
#include "CmColorBase.h"
#include "UInt32Array.h"
#include "Ge/GeExtents3d.h"
#include "IntArray.h"
#include "Ge/GePoint2dArray.h"

#include "TD_PackPush.h"

/** \details
    This class is a base class for boundary filling definitions.

    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiFill : public OdRxObject
{
  protected:
    double m_dDeviation;
  public:
    ODRX_DECLARE_MEMBERS(OdGiFill);
    /** \details
      Default constructor for the OdGiFill class. Sets deviation of fill to 0.
    */
    OdGiFill();

    /** \details
      Retrieves deviation value of the fill.
    */
    double deviation() const;
    
    /** \details
      Sets deviation of the fill.
      
      \param dDeviation [in]  Deviation for the fill.
    */
    void setDeviation(double dDeviation);

    virtual void copyFrom(const OdRxObject* pSource);

    virtual bool operator ==(const OdGiFill& fill) const;
    virtual bool operator !=(const OdGiFill& fill) const;

    virtual void saveBytes(OdUInt8Array &bytes) const;
    virtual void loadBytes(const OdUInt8 *pBytes);

    static OdSmartPtr<OdGiFill> loadFill(const OdUInt8 *pBytes);
  protected:
    void pushDbl(OdUInt8Array &bytes, double dDbl) const;
    void pushInt(OdUInt8Array &bytes, OdUInt32 nInt) const;
    void popDbl(const OdUInt8 *&pBytes, double &dDbl) const;
    void popInt(const OdUInt8 *&pBytes, OdUInt32 &nInt) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGiFill object pointers.
*/
typedef OdSmartPtr<OdGiFill> OdGiFillPtr;

inline
OdGiFill::OdGiFill()
  : m_dDeviation(0.0)
{ }

inline
double OdGiFill::deviation() const
{
  return m_dDeviation;
}

inline
void OdGiFill::setDeviation(double dDeviation)
{
  m_dDeviation = dDeviation;
}

/** \details
    This class is a specialization of OdGiFill for hatch pattern type of filling.

    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiHatchPattern : public OdGiFill
{
  protected:
    OdHatchPattern m_aHatchPattern;
    double m_dPatternScale;
    OdDb::LineWeight m_patternLineWeight;
    OdCmEntityColor m_patternColor;
    OdCmTransparency m_patternTransparency;
    OdSmartPtr< OdGiHatchPattern > m_pNext;

    enum Flags { kDraft = (1 << 0), kExternal = (1 << 1), kAlignedToCenter = (1 << 2), kEmpty = (1 << 3) };
    OdUInt32 m_nFlags;
  public:
    ODRX_DECLARE_MEMBERS(OdGiHatchPattern);
    /** \details
      Default constructor for the OdGiHatchPattern class. Sets the pattern scale to 1.0, pattern flags to 0 and initializes
      the underlaying fill object. 
    */
    OdGiHatchPattern();

    /** \details
      Retrieves lines that compose this pattern.  
      
      \returns
      a reference to the OdHatchPattern that represents an array of pattern lines.
    */
    const OdHatchPattern &patternLines() const;
    
    /** \details
      Retrieves lines that compose this pattern.  
      
      \returns
      a reference to the OdHatchPattern that represents an array of pattern lines.
    */
    OdHatchPattern &patternLines();
    
    /** \details
      Specifies pattern lines for this hatch pattern.
      
      \param aHatchPattern [in]  An array of hatch pattern lines.
    */
    void setPatternLines(const OdHatchPattern &aHatchPattern);

    virtual void copyFrom(const OdRxObject* pSource);

    virtual bool operator ==(const OdGiFill& fill) const;
    virtual bool operator !=(const OdGiFill& fill) const;

    virtual void saveBytes(OdUInt8Array &bytes) const;
    virtual void loadBytes(const OdUInt8 *pBytes);

    bool isDraft() const;
    void setDraft(bool draft);

    /** \details
      Retrieves scale of this pattern.  
      
      \returns
      scale of the hatch pattern as a value of double type.
    */
    double patternScale() const;
    
    /** \details
      Specifies pattern scale for this hatch pattern.
      
      \param scale [in]  Scale of the pattern.
    */
    void setPatternScale( double scale );

    bool isExternal() const;
    void setExternal(bool isExt);

    OdCmEntityColor getPatternColor() const;
    void setPatternColor(const OdCmEntityColor& color);

    OdDb::LineWeight getPatternLineWeight() const;
    void setPatternLineWeight(OdDb::LineWeight lineweight);

    /** \details
    Is used to obtain custom pattern transparency value (Default is 255)
    \returns Pattern transparency value
    */
    OdCmTransparency getPatternTransparency() const;

    /** \details
    Sets custom pattern transparency value.
    \param transparency [in] Pattern transparency value.
    */
    void setPatternTransparency(const OdCmTransparency& transparency);

    /** \details
    Is used to obtain next pattern in the pattern chain
    \returns Pointer to the next OdGiHatchPattern
    */
    OdSmartPtr< OdGiHatchPattern > getNext() const;

    /** \details
    Is used to set next pattern in the pattern chain
    \param pNext [in] Pointer to OdGiHatchPattern
    */
    void setNext(const OdSmartPtr< OdGiHatchPattern >& pNext);

    /** \details
    Is used to obtain 'kAlignedToCenter' flag value (Default is false)
    \returns 'kAlignedToCenter' flag value
    */
    bool isAlignedToCenter() const;

    /** \details
    Is used to set 'kAlignedToCenter' flag that forces
    pattern initial position to the center of the shell
    \param aligned [in] Value to be set
    */
    void setAlignedToCenter(bool aligned);

    /** \details
    Is used to obtain 'kEmpty' flag value (Default is false)
    \returns 'kEmpty' flag value
    */
    bool isEmpty() const;

    /** \details
    Is used to set 'kEmpty' flag that forces
    pattern to be skipped on rendering regardless of it content
    \param empty [in] Value to be set
    */
    void setEmpty(bool empty);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGiHatchPattern object pointers.
*/
typedef OdSmartPtr<OdGiHatchPattern> OdGiHatchPatternPtr;

inline
OdGiHatchPattern::OdGiHatchPattern() :
  OdGiFill(),
  m_nFlags(0),
  m_dPatternScale(1.0),
  m_patternLineWeight(OdDb::LineWeight(-1)),
  m_patternColor(OdCmEntityColor::kNone),
  m_patternTransparency((OdUInt8)255)
{ }

inline
const OdHatchPattern &OdGiHatchPattern::patternLines() const
{
  return m_aHatchPattern;
}

inline
OdHatchPattern &OdGiHatchPattern::patternLines()
{
  return m_aHatchPattern;
}

inline
void OdGiHatchPattern::setPatternLines(const OdHatchPattern &aHatchPattern)
{
  m_aHatchPattern = aHatchPattern;
}

inline
bool OdGiHatchPattern::isDraft() const
{
  return GETBIT(m_nFlags, kDraft);
}

inline
void OdGiHatchPattern::setDraft(bool draft)
{
  SETBIT(m_nFlags, kDraft, draft);
}

inline
double OdGiHatchPattern::patternScale() const
{
  return m_dPatternScale;
}

inline
void OdGiHatchPattern::setPatternScale(double scale)
{
  m_dPatternScale = scale;
}

inline
bool OdGiHatchPattern::isExternal() const
{
  return GETBIT(m_nFlags, kExternal);
}

inline
void OdGiHatchPattern::setExternal(bool isExt)
{
  SETBIT(m_nFlags, kExternal, isExt);
}

inline
OdCmEntityColor OdGiHatchPattern::getPatternColor() const
{
  return m_patternColor;
}

inline
void OdGiHatchPattern::setPatternColor(const OdCmEntityColor& color)
{
  m_patternColor = color;
}

inline
OdDb::LineWeight OdGiHatchPattern::getPatternLineWeight() const
{
  return m_patternLineWeight;
}

inline
void OdGiHatchPattern::setPatternLineWeight(OdDb::LineWeight lineWeight)
{
  m_patternLineWeight = lineWeight;
}

inline
OdCmTransparency OdGiHatchPattern::getPatternTransparency() const
{
  return m_patternTransparency;
}

inline
void OdGiHatchPattern::setPatternTransparency(const OdCmTransparency& transparency)
{
  m_patternTransparency = transparency;
}

inline
OdGiHatchPatternPtr OdGiHatchPattern::getNext() const
{
  return m_pNext;
}

inline
void OdGiHatchPattern::setNext(const OdGiHatchPatternPtr& pNext)
{
  m_pNext = pNext;
}

inline
bool OdGiHatchPattern::isAlignedToCenter() const
{
  return GETBIT(m_nFlags, kAlignedToCenter);
}

inline
void OdGiHatchPattern::setAlignedToCenter(bool value)
{
  SETBIT(m_nFlags, kAlignedToCenter, value);
}

inline
bool OdGiHatchPattern::isEmpty() const
{
  return GETBIT(m_nFlags, kEmpty);
}

inline
void OdGiHatchPattern::setEmpty(bool empty)
{
  SETBIT(m_nFlags, kEmpty, empty);
}


inline
OdGiFillPtr OdGiFill::loadFill(const OdUInt8 *pBytes)
{
  OdGiFillPtr pObj;
  switch (*pBytes)
  {
  case 0: pObj = OdGiFill::createObject(); break;
  case 1:
  case 2:
  case 3:
  case 4: pObj = OdGiHatchPattern::createObject(); break;
  }
  if (!pObj.isNull())
    pObj->loadBytes(pBytes);
  return pObj;
}



/** \details
    This class is a specialization of OdGiHatchPattern for hatch pattern type of filling for internal using.

    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiFillHatch : public OdGiHatchPattern
{
public:

  ODRX_DECLARE_MEMBERS(OdGiFillHatch);

  OdGiFillHatch();
  ~OdGiFillHatch();

  virtual void copyFrom(const OdRxObject* pSource) ODRX_OVERRIDE;

  virtual bool operator ==(const OdGiFill& fill) const ODRX_OVERRIDE;
  virtual bool operator !=(const OdGiFill& fill) const ODRX_OVERRIDE;

  //virtual void saveBytes(OdUInt8Array& bytes) const;
  //virtual void loadBytes(const OdUInt8* pBytes);

  enum EvaluateEnum
  {
    kNotEvaluated = 0,
    kEvaluated = 1,
    kEvaluatedEmpty = 2
  }m_eData;

  //getters

  double deviation() const;
  double viewRotation() const;
  double elevation() const;
  OdUInt32 hatchDensity() const;
  OdUInt32 pointLimit() const;
  OdUInt32 maxDrawPoints() const;
  OdInt16 smoothHatch() const;
  bool isSolidFill() const;
  bool isHatchTooDense() const;
  bool isGradientFill() const;
  bool isDrawCache() const;
  bool isMPolygon() const;
  bool isDBRO() const;
  bool hasCache() const;

  OdResult getResult() const;
  const OdUInt32Array getLoopsFlags() const;
  const OdUInt32Array getLoopsMarker() const;
  OdGeIslandStyle getStyle() const;
  OdGeExtents3d getExtents() const;
  OdGeTol getTolerance() const;
  void getPoints(OdGePoint2dArray& startPoints, OdGePoint2dArray& endPoints) const;
  OdHatchPattern& patternLines();

  //setters
  void set(const double dDeviation,
    const double dViewRotation,
    const double dElevation,
    const OdUInt32 maxHatchDensity,
    const OdUInt32 pointLimit,
    const OdUInt32 maxPointsToDraw,
    const OdInt16 nSmoothHatch,
    const bool bHatchTooDense,
    const bool bSolidFill,
    const bool bGradientFill,
    const bool bMPolygon,
    const bool bDBRO,
    const OdUInt32Array& loopsFlags,
    const OdUInt32Array& loopsMarker,
    const OdGeIslandStyle style,
    const OdHatchPattern& pattern);


  void setHatchTooDense(const bool bHatchTooDense);
  void setResult(const OdResult res);
  void setLoopsFlags(const OdUInt32Array& loopsFlags);
  void setLoopsMarker(const OdUInt32Array& loopsMarker);
  void setExtents(const OdGeExtents3d& ext3d);
  void setDrawCache(const bool bDrawCache);
  void setTolerance(const OdGeTol tol);
  void setPoints(const OdGePoint2dArray& startPoints, const OdGePoint2dArray& endPoints);

protected:
  OdUInt32Array m_loopsFlags;
  OdUInt32Array m_loopsMarker;
  OdGePoint2dArray m_startPoints;
  OdGePoint2dArray m_endPoints;
  OdIntArray m_loopArray;
  OdIntArray m_loopTypes;
  OdHatchPattern m_aHatchPattern;
  OdGeExtents3d m_extents3d;
  OdGeTol m_tol;
  OdGeIslandStyle m_style;
  OdResult m_result;

  double m_dDeviation;
  double m_dViewRotation;
  double m_dElevation;
  OdUInt32 m_maxHatchDensity;
  OdUInt32 m_pointLimit;
  OdUInt32 m_maxPointsToDraw;
  OdInt16 m_nSmoothHatch;
  bool m_bHatchTooDense;
  bool m_bSolidFill;
  bool m_bGradientFill;
  bool m_bDrawCache;
  bool m_bMPolygon;
  bool m_bDBRO;
};

typedef OdSmartPtr<OdGiFillHatch> OdGiFillHatchPtr;


inline OdGiFillHatch::OdGiFillHatch() : OdGiHatchPattern(), m_dDeviation(.0),
m_dViewRotation(.0),
m_dElevation(.0),
m_maxHatchDensity(0),
m_pointLimit(0),
m_nSmoothHatch(0),
m_bHatchTooDense(false),
m_bSolidFill(false),
m_bGradientFill(false),
m_bDrawCache(false),
m_bMPolygon(false),
m_style(OdGeIslandStyle_Normal),
m_maxPointsToDraw(0),
m_result(eInvalidInput),
m_eData(kNotEvaluated)
{
  
}

inline OdGiFillHatch::~OdGiFillHatch()
{
}




#include "TD_PackPop.h"

#endif //_OD_GIFILL_H_
