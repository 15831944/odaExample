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


#ifndef _OD_DBSUN_H_INCLUDED_
#define _OD_DBSUN_H_INCLUDED_

#include "TD_PackPush.h"

#include "Gi/GiLightTraits.h"
#include "DbLight.h"
#include "RxDictionary.h"

class SCENEOE_EXPORT OdTvDbSun;
typedef OdSmartPtr<OdTvDbSun> OdTvDbSunPtr;


/** \details
    Corresponding C++ library: SCENEOE

    <group OdTvDb_Classes>
*/
class SCENEOE_EXPORT OdTvDbSun : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSun);

  OdTvDbSun();

  virtual DrawableType drawableType() const;
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  
  OdGiDrawable* drawable();

  virtual bool isOn() const;


  virtual void setOn(bool value);


  virtual double intensity() const;


  virtual void setIntensity(double intensity);

 
  virtual const OdTvCmColor& sunColor() const;


  virtual void setSunColor(const OdTvCmColor& color);


  virtual const OdGiShadowParameters& shadowParameters() const;


  virtual void setShadowParameters(const OdGiShadowParameters& params);


  virtual void setDateTime(const OdTvDbDate& datetime);


  virtual const OdTvDbDate& dateTime() const;


  virtual void setDayLightSavingsOn(bool value);


  virtual bool isDayLightSavingsOn() const;


  virtual OdResult setAzimuth(double azimuth);


  virtual double azimuth() const;


  virtual OdResult setAltitude(double altitude);


  virtual double altitude() const;


  virtual const OdGeVector3d& sunDirection() const;


  virtual void setSunDirection(const OdGeVector3d& sundir);


  virtual void setSkyParameters(const OdGiSkyParameters& params);


  virtual void skyParameters(OdGiSkyParameters& params) const;

  static OdTvDbSunPtr castByClassName(OdRxObject* obj);
  static OdTvDbSunPtr safeCastByClassName(OdRxObject* obj);
  static OdTvDbSunPtr safeCreateByClassName();
};


inline OdTvDbSunPtr OdTvDbSun::castByClassName(OdRxObject* obj) {
  return ::odrxCastByClassName<OdTvDbSun>(obj, "AcTvDbSun");
}

inline OdTvDbSunPtr OdTvDbSun::safeCastByClassName(OdRxObject* obj) {
  return ::odrxSafeCastByClassName<OdTvDbSun>(obj, "AcTvDbSun");
}

inline OdTvDbSunPtr OdTvDbSun::safeCreateByClassName() {
  return ::odrxSafeCreateObject<OdTvDbSun>("AcTvDbSun", "TV_SCENEOE");
};


#include "TD_PackPop.h"

#endif

