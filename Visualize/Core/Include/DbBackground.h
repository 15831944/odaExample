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

#ifndef _ODDBBACKGROUND_INCLUDED_
#define _ODDBBACKGROUND_INCLUDED_

#include "TD_PackPush.h"

#include "DbObject.h"
#include "DbEntity.h"

#define ODDB_BACKGROUND_DICTIONARY TV_ACAD_BACKGROUND

/** \details
    This class is a base class for all background objects.
    Corresponding C++ library: SCENEOE

    \remarks
    Database-resident background objects are stored in the NamedObjectsDictionary
    under TV_ACAD_BACKGROUND.
    
    \sa
    TD_Db
    <group OdTvDb_Classes> 
*/
class SCENEOE_EXPORT OdTvDbBackground : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBackground);

  OdTvDbBackground();
  virtual ~OdTvDbBackground();

  /** \details
    Returns the OdGiDrawable for this Background object.
  */
  virtual OdGiDrawable* drawable();
};

typedef OdSmartPtr<OdTvDbBackground> OdTvDbBackgroundPtr;

/** \details
    This class is for a solid background.
    Corresponding C++ library: SCENEOE

    \sa
    TD_Db
    <group OdTvDb_Classes> 
*/
class SCENEOE_EXPORT OdTvDbSolidBackground : public OdTvDbBackground
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSolidBackground);

  OdTvDbSolidBackground();
  virtual ~OdTvDbSolidBackground();

  void setColorSolid(const OdCmEntityColor& color);
  OdCmEntityColor colorSolid() const;

  // OdTvDbObject overridden functions

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // OdRxObject overridden functions

  //virtual void copyFrom(const OdRxObject* pSource);

  // OdGiDrawable overridden functions

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual OdGiDrawable::DrawableType drawableType() const;
};

typedef OdSmartPtr<OdTvDbSolidBackground> OdTvDbSolidBackgroundPtr;

/** \details
    This class is for a gradient background.
    Corresponding C++ library: SCENEOE

    \sa
    TD_Db
    <group OdTvDb_Classes> 
*/
class SCENEOE_EXPORT OdTvDbGradientBackground : public OdTvDbBackground
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbGradientBackground);

  OdTvDbGradientBackground();
  virtual ~OdTvDbGradientBackground();

  void setColorTop(const OdCmEntityColor& color);
  OdCmEntityColor colorTop() const;
  void setColorMiddle(const OdCmEntityColor& color);
  OdCmEntityColor colorMiddle() const;
  void setColorBottom(const OdCmEntityColor& color);
  OdCmEntityColor colorBottom() const;
  void setHorizon(double horizon);
  double horizon() const;
  void setHeight(double height);
  double height() const ;
  void setRotation(double rotation);
  double rotation() const;

  // OdTvDbObject overridden functions

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // OdRxObject overridden functions

  //virtual void copyFrom(const OdRxObject* pSource);

  // OdGiDrawable overridden functions

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual OdGiDrawable::DrawableType drawableType() const;
};

typedef OdSmartPtr<OdTvDbGradientBackground> OdTvDbGradientBackgroundPtr;

/** \details
    This class is for an image background.
    Corresponding C++ library: SCENEOE

    \sa
    TD_Db
    <group OdTvDb_Classes> 
*/
class SCENEOE_EXPORT OdTvDbImageBackground : public OdTvDbBackground
{
public:

  ODDB_DECLARE_MEMBERS(OdTvDbImageBackground);

  OdTvDbImageBackground();
  virtual ~OdTvDbImageBackground();

  void setImageFilename(const OdString& filename);
  const OdString& imageFilename() const;
  void setFitToScreen(bool bFitToScreen);
  bool fitToScreen() const;
  void setMaintainAspectRatio(bool bMaintainAspectRatio);
  bool maintainAspectRatio() const;
  void setUseTiling(bool bUseTiling);
  bool useTiling() const;
  void setXOffset(double xOffset);
  double xOffset() const;
  void setYOffset(double yOffset);
  double yOffset() const;
  void setXScale(double xScale);
  double xScale() const;
  void setYScale(double yScale);
  double yScale() const;

  // OdTvDbObject overridden functions

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // OdRxObject overridden functions

  //virtual void copyFrom(const OdRxObject* pSource);

  // OdGiDrawable overridden functions

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual OdGiDrawable::DrawableType drawableType() const;
};

typedef OdSmartPtr<OdTvDbImageBackground> OdTvDbImageBackgroundPtr;

/** \details
    This class implements a ground plane for a background object in a viewport.
    Corresponding C++ library: SCENEOE

    \sa
    TD_Db
    <group OdTvDb_Classes> 
*/
class SCENEOE_EXPORT OdTvDbGroundPlaneBackground : public OdTvDbBackground
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbGroundPlaneBackground);

  OdTvDbGroundPlaneBackground();
  virtual ~OdTvDbGroundPlaneBackground();

  void setColorSkyZenith(const OdCmEntityColor& color);
  OdCmEntityColor colorSkyZenith() const;
  void setColorSkyHorizon(const OdCmEntityColor& color);
  OdCmEntityColor colorSkyHorizon() const;
  void setColorUndergroundHorizon(const OdCmEntityColor& color);
  OdCmEntityColor colorUndergroundHorizon() const;
  void setColorUndergroundAzimuth(const OdCmEntityColor& color);
  OdCmEntityColor colorUndergroundAzimuth() const;
  void setColorGroundPlaneNear(const OdCmEntityColor& color);
  OdCmEntityColor colorGroundPlaneNear() const;
  void setColorGroundPlaneFar(const OdCmEntityColor& color);
  OdCmEntityColor colorGroundPlaneFar() const;

  // OdTvDbObject overridden functions

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // OdRxObject overridden functions

  //virtual void copyFrom(const OdRxObject* pSource);

  // OdGiDrawable overridden functions

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual OdGiDrawable::DrawableType drawableType() const;
};

typedef OdSmartPtr<OdTvDbGroundPlaneBackground> OdTvDbGroundPlaneBackgroundPtr;

/** \details
    This class implements a sky for a background object in a viewport.
    Corresponding C++ library: SCENEOE

    \sa
    TD_Db
    <group OdTvDb_Classes> 
*/
class SCENEOE_EXPORT OdTvDbSkyBackground : public OdTvDbBackground
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSkyBackground);

  OdTvDbSkyBackground();
  virtual ~OdTvDbSkyBackground();

  void setSunId(const OdTvDbObjectId& sunId);
  OdTvDbObjectId sunId() const;

  // OdTvDbObject overridden functions

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // OdRxObject overridden functions

  //virtual void copyFrom(const OdRxObject* pSource);

  // OdGiDrawable overridden functions

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual OdGiDrawable::DrawableType drawableType() const;
};

typedef OdSmartPtr<OdTvDbSkyBackground> OdTvDbSkyBackgroundPtr;

/** \details
    This class implements a image based lighting for a background object in a viewport.
    Corresponding C++ library: SCENEOE

    \sa
    TD_Db
    <group OdTvDb_Classes>
*/
class SCENEOE_EXPORT OdTvDbIBLBackground : public OdTvDbBackground
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbIBLBackground);

  OdTvDbIBLBackground();
  virtual ~OdTvDbIBLBackground();

  virtual void setEnable(bool bEnable);
  virtual bool enable() const;
  virtual void setIBLImageName(const OdString &filename);
  virtual const OdString &IBLImageName() const;
  virtual void setRotation(double rotation);
  virtual double rotation() const;
  virtual void setDisplayImage(bool bDisplay);
  virtual bool displayImage() const;
  virtual void setSecondaryBackground(const OdTvDbObjectId &bgId);
  virtual OdTvDbObjectId secondaryBackground() const;

  virtual void setDataFrom(const OdTvDbIBLBackground *pBkgnd);

  // OdTvDbObject overridden functions

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // OdRxObject overridden functions

  //virtual void copyFrom(const OdRxObject* pSource);

  // OdGiDrawable overridden functions

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual OdGiDrawable::DrawableType drawableType() const;
};

typedef OdSmartPtr<OdTvDbIBLBackground> OdTvDbIBLBackgroundPtr;

SCENEOE_EXPORT OdTvDbObjectId odtvdbGetBackgroundDictionaryId(OdTvDbDatabase* pDb, bool createIfNotFound = false);
SCENEOE_EXPORT OdTvDbDictionaryPtr odtvdbGetBackgroundDictionary(OdTvDbDatabase* pDb, OdDb::OpenMode mode, bool createIfNotFound = false);

#include "TD_PackPop.h"

#endif // _ODDBBACKGROUND_INCLUDED_
