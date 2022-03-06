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


#ifndef __NW_GICONTEXTFORNwDatabase_H__
#define __NW_GICONTEXTFORNwDatabase_H__

#include "Gi/GiSelectionStyle.h"
#include "GiDefaultContext.h"
#include "StaticRxObject.h"
#include "NwDatabase.h"
#include "NwExport.h"
#include "NwObjectReactor.h"

#include "TD_PackPush.h"

struct OdGsClientViewInfo;
class OdGiSelectionStyle;

/** \details
  This class defines the operations and properties that are used for rendering an OdNwDatabase.
*/
class NWDBEXPORT OdGiContextForNwDatabase : public OdGiDefaultContext
{
  enum
  {
    kPlotGeneration                  = 1,
    kUseGsModel                      = 2,
    kOdGiZeroTextNormals             = 4,
    kDisableLayoutHelperLinkReactors = 8,
    kTTFPolyDraw                     = 16,
    kTrackDbDestroy                  = 32,
    kManageContextualColors          = 64,
    kKeepPSLayoutHelperView          = 128,
    kErasePSLayoutHelperView         = 256,
    kLastFlag                        = kErasePSLayoutHelperView
  };

  OdUInt32              m_fflags;

  /** \details
    
    
  */
  class NWDBEXPORT DatabaseHolder : public OdStaticRxObject<OdNwDatabaseReactor>
  {
  public:
    /** \details
      Default constructor.
    */
    DatabaseHolder();

    /** \details
      Destructor. Frees allocated resources.
    */
    ~DatabaseHolder();

    /** \details
      Sets the given database object for the DatabaseHolder object.

      \param pDb Pointer to the database object to set.
    */
    void setDatabase(OdNwDatabase * pDb);

    /** \details
      Notification function called whenever a database is about to be deleted from memory.
      \param pDb [in] Pointer to the database being deleted.

      \remarks
      This function is called before the operation.
    */
    void goodbye(const OdNwDatabase* pDb);

    OdNwDatabase* m_pDb;
  } m_DbHolder;

  ODRX_DECLARE_MEMBERS(OdGiContextForNwDatabase);

protected:
  ODCOLORREF m_paletteBackground;
  OdGiSelectionStyle m_selectionStyle;

public:
  /** \details
    Default constructor.
  */
  OdGiContextForNwDatabase();
  
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdGiContextForNwDatabase();
  
  /** \details
    Returns a pointer to the database.
  */
  virtual OdDbBaseDatabase* database() const;
  
  /** \details
    Checks whether this vectorization is intended for hard copy output.

    \returns true if this vectorization is intended for hard copy output, false otherwise.
  */
  virtual bool isPlotGeneration() const;
  
  /** \details
    Sets the flag indicating whether this vectorization is intended for hard copy output. 
    
    \param plotGeneration [in] Hard copy output flag to set.
  */
  virtual void setPlotGeneration(bool plotGeneration);
  
  /** \details
    Sets the background palette.
    
    \param ODCOLORREF [in] Background palette to set.
  */
  virtual void setPaletteBackground(ODCOLORREF paletteBackground);
  
  /** \details
    Opens for reading the specified drawable object that belongs to the database associated with this context object.
    
    \param drawableId [in] Object ID of the drawable to open.
    \returns A smart pointer to the open drawable object.
  */
  virtual OdGiDrawablePtr openDrawable(OdDbStub* drawableId);
  
  /** \details
    Returns the palette background color for this vectorization.
    
    \returns Palette background as ODCOLORREF.
  */
  virtual ODCOLORREF paletteBackground() const;

  /** \details
    Sets a pointer to the database. 
    
    \param pNwDatabase [in] Pointer to the OdNwDatabase object to set.
  */
  void setDatabase( OdNwDatabase* pNwDatabase );

  /** Description:
    Returns the database that is currently being vectorized.
  */
  OdNwDatabase* getDatabase() const;

  /** \details
    Retrieves an OdGsClientViewInfo object for the specified viewport.
    
    \param vpId [in] Object ID of the viewport to get the OdGsClientViewInfo object for.
    \param viewInfo [out] Receives the client view information.
  */
  virtual void fillGsClientViewInfo(const OdNwObjectId& vpId, OdGsClientViewInfo& viewInfo);

  /** \details
    Returns the internal drawable filtration function ID. 
    \param viewportId [in] Pointer to the object ID of the viewport object to be queried. 
    \returns An internal drawable filtration function ID as OdIntPtr.  
  */
  virtual OdIntPtr drawableFilterFunctionId(OdDbStub* viewportId) const;

  /** \details
    Retrieves the set of flags for the drawable filtration function (called for each drawable vectorization).
    
    \param functionId [in] Internal drawable filtration function ID. 
    \param pDrawable [in] Currently vectorizing drawable pointer.
    \param nFlags [in] Set of input flags.
    \returns Currently returns 0.
  */
  virtual OdUInt32 drawableFilterFunction(OdIntPtr functionId, const OdGiDrawable *pDrawable, OdUInt32 nFlags);

  /** \details
    Returns true if the GsModel flag of this context object is set.
  */
  bool useGsModel() const;

  /** \details
    Controls the GsModel flag of this context object.
    
    \param enable [in] Enables or disables the GsModel flag.
  */
  void enableGsModel(bool enable);

  /** \details
    Retrieves the lineweight display style configuration.
    
    \param styleEntry [in] Lineweight style entry for which the current setting is to be returned.
    \returns
    * For kPointLineWeight style, 0 is returned if the point lineweight is disabled, or 1 is returned if enabled.
    * For kLineCapStyle style, the entry is returned as a member of the OdPs::LineEndStyle enumeration.
    * For kLineJoinStyle style, the entry is returned as a member of the OdPs::LineJoinStyle enumeration.
  */
  OdUInt32 lineWeightConfiguration(LineWeightStyle styleEntry) const;

  /** \details
    Checks whether smooth contour information output is used for TrueType fonts.
    
    \returns true if smooth contour information output is used for TrueType fonts (OdCharacterProperties::kBezierCurves flag), or false otherwise.
  */
  virtual bool ttfPolyDraw() const;

  /** \details
    Enables or disables the TTF PolyDraw mode which adjusts the quality of the TrueType font visualization using smoother contour information output.
    
    \param bPolyDraw [in] Flag indicating whether the TTF PolyDraw mode is enabled or disabled.
  */
  void setTtfPolyDrawMode(bool bPolyDraw);

  /** \details
    Returns the selection style for entities highlighting.

    \param nStyle [in]  Selection style index.
    \param selStyle [out]  Receives the selection style data.

    \returns
    Number of selection styles provided by this context object.
  */
  OdUInt32 selectionStyle(OdUInt32 nStyle, OdGiSelectionStyle &selStyle) const override;

  /** \details
    Sets the selection style for entities highlighting.

    \param nStyle [in]  Selection style index.
    \param selStyle [out]  Sets the selection style data.

    \returns
    Number of selection styles provided by this context object.
  */
  OdUInt32 setSelectionStyle(OdUInt32 nStyle, const OdGiSelectionStyle &selStyle);
};

typedef OdSmartPtr<OdGiContextForNwDatabase> OdGiContextForNwDatabasePtr;

#include "TD_PackPop.h"

#endif // __NW_GICONTEXTFORNwDatabase_H__

