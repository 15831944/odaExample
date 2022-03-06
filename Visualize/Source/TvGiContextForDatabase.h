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

#ifndef _ODTV_GICONTEXT_H_INCLUDED_
#define _ODTV_GICONTEXT_H_INCLUDED_

#include "GiDefaultContext.h"
#include "StaticRxObject.h"
#include "TvDatabaseImpl.h"
#include "Ps/PlotStyles.h"

//#include "DbExport.h"
//#include "OdPlatform.h"
//#include "Gi/GiSubEntityTraitsData.h"
//#include "Gi/GiLinetyper.h"
//

//DB Experiment
#include "DbDatabaseReactor.h"

#include "TD_PackPush.h"

struct OdGsClientViewInfo;
class OdGsView;
class OdGiContextualColorsImpl;

/** \details
This template class is a specialization of the OdArray class for ODCOLORREF objects.
*/
typedef OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > ODTVPALETTE;

/** \details
    This class defines the operations and properties that are used in the
    vectorization process of an OdTvDatabaseImpl.

*/
class OdTvGiContextForDatabase : public OdGiDefaultContext
{
public:
  ODRX_HEAP_OPERATORS();
private:
  enum
  {
    kPlotGeneration                  = 1,
    kUseGsModel                      = 2,
    kOdGiZeroTextNormals             = 4,
    kTTFPolyDraw                     = 8,
    kForceDisplaySilhouettes         = 16,
    kLastFlag                        = kForceDisplaySilhouettes
  };

  OdUInt32              m_fflags;

  class TvDatabaseHolder : public OdStaticRxObject<OdTvDbDatabaseReactor>
  {
  public:
    TvDatabaseHolder();
    ~TvDatabaseHolder();

    OdDbDatabaseTv* m_pDb;

    void setDatabase(OdDbDatabaseTv* pDb);

    void goodbye(const OdTvDbDatabase* pDb);
  }
  m_TvHolder;

protected:
  ODCOLORREF           m_paletteBackground;
  ODTVPALETTE          m_logPalette;

  OdUInt32             m_uPointLineWeight;
  OdUInt32             m_uLineCapStyle;
  OdUInt32             m_uLineJoinStyle;

  bool                 m_bNeedRegenBrep;
  OdTvRegenAbort*      m_pRegenAbort;
  OdUInt32             m_iAntiAliasingMode;
  bool                 m_bDisplaySilhouettes;

  OdUInt32             m_uTxtQuality;

  bool                 m_bColorHighlight;
  OdCmEntityColor      m_highlightColor;
  OdUInt8              m_highlightTransparency;

  OdArray<OdGiSelectionStyle*> m_usedHighlightStyles;

public:

  ODRX_DECLARE_MEMBERS(OdTvGiContextForDatabase);

  OdTvGiContextForDatabase();
  virtual ~OdTvGiContextForDatabase();

  // OdGiContext overridden functions

  virtual OdDbBaseDatabase* database() const;
  virtual OdGiDrawablePtr openDrawable(OdDbStub* drawableId);
  virtual OdUInt32 numberOfIsolines() const;
  virtual double commonLinetypeScale() const;
  virtual OdDb::LineWeight defaultLineWeight() const;
  virtual bool quickTextMode() const;
  virtual void setTextQuality(OdUInt32 value);
  virtual OdUInt32 textQuality() const;
  virtual ImageQuality imageQuality() const;
  virtual OdUInt32 fadingIntensityPercentage(FadingType fadingType) const;
  virtual bool ttfPolyDraw() const;
  virtual OdUInt32 displaySilhouettes() const;

  /** \details
  Set the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be setted.
  \param uValue [in]  Lineweight style value.
  */
  virtual OdTvResult setLineWeightConfiguration(LineWeightStyle styleEntry, OdUInt32 uValue);

  /** \details
  Returns the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be returned.

  \remarks
  For kPointLineWeight style, 0 will be returned if point lineweight is disabled or 1 will be returned if enabled.
  For kLineCapStyle style, entry will be returned as a member of the OdPs::LineEndStyle enumeration.
  For kLineJoinStyle style, entry will be returned as a member of the OdPs::LineJoinStyle enumeration.
  */
  virtual OdUInt32 lineWeightConfiguration(LineWeightStyle styleEntry) const;

  /** \details
    Sets the database to be vectorized.

    \param pDb [in]  Pointer to the database.
    \param bTrackDbDestroy [in]  if to the database is not NULL then
    this parameter specifies if implementation should track database lifetime
    (by adding reactor to the database and processing OdTvDbDatabaseReactor::goodbye() event)
    and to clear pointer to the database if it will be destroyed. If you sure that lifetime of this object
    is shorter then lifetime of the database you may set this parameter to false
    to turn off unnecessary database lifetime tracking.
  */
  void setDatabase( OdDbDatabaseTv* pDb );

  /** \details
    Returns the database that is currently being vectorized.
  */
  OdDbDatabaseTv* getDatabase() const;

  /** \details
    Returns the OdGsClientViewInfo for the specified viewport.
    \param vpId [in]  Object ID of the viewport.
    \param viewInfo [out]  Receives the client view info.
  */
  virtual void fillGsClientViewInfo(const OdTvDbObjectId& vpId, OdGsClientViewInfo& viewInfo);

  /** \details
  Returns the OdDbStub for the specified handle id.
  \param objectId [in]  Object ID of the object.
  Returns the pointer to OdDbStub.
  */
  virtual OdDbStub* getStubByID( OdUInt64 objectId ) const;

  virtual OdDbStub* getStubByMatName(const OdString& strMatName) const;

  virtual void getDefaultTextStyle(OdGiTextStyle& textStyle);

  unsigned int circleZoomPercent(OdDbStub* viewportId) const;

  virtual OdIntPtr drawableFilterFunctionId(OdDbStub* viewportId) const;
  virtual OdUInt32 drawableFilterFunction(OdIntPtr functionId, const OdGiDrawable *pDrawable, OdUInt32 nFlags);

  /** \details
    Returns true if and only the GsModel flag of this Context Object is set..
  */
  bool useGsModel() const;

  /** \details
    Controls the GsModel flag of this Context Object.
    \param enable [in]  Controls the Gs Model.
  */
  void enableGsModel(bool enable);

  /** \details
    Returns true if and only the PlotGeneration flag of this Context Object is set.
  */
  bool isPlotGeneration() const;

  /** \details
    Controls the PlotGeneration flag of this Context Object.
    \param plotGeneration [in]  Controls plot generation.
  */
  void setPlotGeneration(bool plotGeneration);

  /** \details
    Returns true if and only the kOdGiZeroTextNormals flag of this Context Object is set.
  */
  virtual bool isZeroTextNormals() const;

  /** \details
    Controls the ZeroTextNormals flag of this Context Object.
    \param bZeroTextNormals [in]  Controls text normals generation.
  */
  void setZeroTextNormals(bool bZeroTextNormals);

  /** \details
    Enables TrueType text contours info output.
    \param bPolyDraw [in]  Controls kTTFPolyDraw flag of this Context Object.
  */
  void setTtfPolyDrawMode(bool bPolyDraw);

  /** \details
    Returns current state of display silhouettes forcing mode.
  */
  bool isForceDisplaySilhouettesEnabled() const;

  /** \details
    Sets current state of display silhouettes forcing mode.
    \param bOn [in]  Enable or disable display silhouettes forcing.
  */
  void setForceDisplaySilhouettes(bool bOn);

  /** \details
    Returns true if and only if filling of TrueType fonts is enabled.
  */
  bool fillTtf() const;

  /** \details
    Returns true if and only if shell/mesh geometry primitives should be filled during this vectorization.
  */
  bool fillMode() const;

  /** \details
    Returns the palette background color for this Context object.
  */
  ODCOLORREF paletteBackground() const { return m_paletteBackground; }
  /** \details
    Sets the palette background color for this Context object.
    \param paletteBackground [in]  Palette background.
  */
  void setPaletteBackground(ODCOLORREF paletteBackground) { m_paletteBackground = paletteBackground; }

  /** \details
  Sets the logical pallete to be used by this Device object.

  \param logicalPalette [in]  Logical palette.
  \param numColors [in]  Number of colors in palette.

  \remarks
  The logical pallete is used in the case of indexed colors
  */
  virtual void setLogicalPalette(const ODCOLORREF* logicalPalette, int numColors);

  /** \details
  Returns the logical pallete used by this Device object.

  \param numColors [out]  Number of colors in palette.
  */
  virtual const ODCOLORREF* getLogicalPalette(int &numColors) const;

  /** \details
    Loads the specified plot style table for this Context object.
    \param pStreamBuf [in]  Pointer to the StreamBuf object from which the data are to be read.
  */
  void loadPlotStyleTable(OdStreamBuf* pStreamBuf);
  
  /** \details
    Returns the plot style type for this Context object.
  */
  virtual PStyleType plotStyleType() const;

  /** \details
    Returns the plot style data for the specified pen number or object Id.
    \param penNumber [in]  Pen number.
    \param psNameId [in]  Object id of the plot style name.
    \param plotStyleData [out]  Receives the plot style data.
  */
  virtual void plotStyle(int penNumber, OdPsPlotStyleData& plotStyleData) const;

  virtual void plotStyle(OdDbStub* psNameId, OdPsPlotStyleData& plotStyleData) const;

  /** \details
    Returns an interface for access section geometry functionality.
  */
  virtual OdGiSectionGeometryManagerPtr getSectionGeometryManager();

  /** \details
  Controls rendering anti-aliasing.
  */
  void setAntiAliasingMode(OdUInt32 mode);

  /** \details
    Controls rendering anti-aliasing.
  */
  virtual OdUInt32 antiAliasingMode() const;

  /** \details
    Controls Xref properties overriding.
  */
  virtual bool xrefPropertiesOverride() const;

  /** \details
  Returns SolidHatchAsPolygonMode set for this Context Object.
  */
  SolidHatchAsPolygonMode hatchAsPolygon() const;

  /** \details
  Controls SolidHatchAsPolygonMode of this Context Object.
  \param bOn [in]  Controls hatch as polygon generation.
  */
  void setHatchAsPolygon(SolidHatchAsPolygonMode mode);

  void setNeedRegenBreps(bool bNeedRegenBrep) { m_bNeedRegenBrep = bNeedRegenBrep; }

  bool isNeedRegenBrep() const { return m_bNeedRegenBrep; }

  /** \details
  Returns true if and only if this vectorization process should be aborted.
  */
  virtual bool regenAbort() const;

  /** \details
  Assigns the OdTvRegenAbort to the context
  */
  void setRegenAbort(OdTvRegenAbort* pRegenAbort);

  /** \details
  Returns the assigned OdTvRegenAbort instance
  */
  OdTvRegenAbort* getRegenAbort() const;

  /** \details
  Controls displaying of the silhouettes (special edges marked as 'silhouettes'
  */
  void setDisplaySilhouettes(bool bDisplay);

  /** \details
  Apply tv highlight style to gi highlight style
  */
  void applyHighlightStyle(const OdTvHighlightStyleId& highlightStyleId);

  void setUsedHighlihgtStyles( OdArray<OdTvHighlightStyleId>* usedStyles );

  /** \details
  Retrieves the selection styles for entities highlighting.

  \param nStyle [in]  Selection style index.
  \param selStyle [out]  Receives the selection style data.

  \returns
  Number of selection styles provided by this context object.

  \remarks
  This method should return at least single selection style for 0 index.
  */
  OdUInt32 selectionStyle(OdUInt32 nStyle, OdGiSelectionStyle &selStyle) const;

  /** \details
  Set parameters for color highlighting.

  \param opt [in]   Option
  \param nVal [in]  New value
  */
  void setColorHighlightOption(OdTvGsDevice::Options opt, OdUInt32 nVal);

  /** \details
  Get parameters for color highlighting.

  \param opt  [in]   Option
  \param nVal [out]  Value
  */
  void getColorHighlightOption(OdTvGsDevice::Options opt, OdUInt32& nVal);

  /** \details
  Retrieves set of flags, which describe images behavior during selection.

  \returns
  Set of ImageSelectionFlags enumeration bit flags.
*/
  virtual OdUInt32 imageSelectionBehavior() const;

  /** \details
  Need to make this class non-abstract due to OdRxObject inheritance
  */
  virtual void addRef() {}
  virtual void release() {}
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvGiContextForDatabase object pointers.
*/
typedef OdSmartPtr<OdTvGiContextForDatabase> OdGiContextForTvDatabasePtr;

/** \details
This class defines the operations and properties that are used in the
vectorization process in the case of protocol extension

*/
class OdTvGiContextForDatabaseRx : public OdTvGiContextForDatabase
{
  OdRefCounter m_nRefCounter;

public:
  ODRX_HEAP_OPERATORS();
  ODRX_DECLARE_MEMBERS(OdTvGiContextForDatabaseRx);


  OdTvGiContextForDatabaseRx();
  virtual ~OdTvGiContextForDatabaseRx() {}

  /** \details
  Increments the reference counter.
  */
  void addRef()
  {
    ++m_nRefCounter;
  }

  /** \details
  Decrements the reference counter, checks the reference counter, and destroys the instance
  when the reference counter reaches zero.
  */
  void release()
  {
    ODA_ASSERT((m_nRefCounter > 0));
    if (!(--m_nRefCounter))
    {
      delete this;
    }
  }
};

/** \details
This template class is a specialization of the OdSmartPtr class for OdTvGiContextForDatabaseRx object pointers.
*/
typedef OdSmartPtr<OdTvGiContextForDatabaseRx> OdGiContextForTvDatabaseRxPtr;


#include "TD_PackPop.h"

#endif //_ODTV_GICONTEXT_H_INCLUDED_
