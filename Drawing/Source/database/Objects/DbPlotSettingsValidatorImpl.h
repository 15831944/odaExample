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

#ifndef __DB_PLOTSETTINGS_IMPL_H__
#define __DB_PLOTSETTINGS_IMPL_H__

#include "DbPlotSettingsValidator.h"
#include "DbPlotSettingsValidatorPE.h"

class OdDbPlotSettingsValidatorImpl : public OdDbPlotSettingsValidator
{
  OdMutex               m_lock;
  OdArray<OdString>     m_StyleSheet;
  OdArray<OdString>     m_DeviceList;
  OdArray<OdDbPlotSettingsValidatorPE::psvPaperInfo> m_MediaList;
  OdInt32               m_nActiveMediaIndx;
  OdInt32               m_nActiveDeviceIndx;

private:
  OdResult changeActiveMedia( OdString mediaName );
  OdResult changeActiveDevice(const OdDbPlotSettings* pPlotSet, OdString deviceName );
  OdResult updateActiveDeviceMediaIndexes(const OdDbPlotSettings* pPlotSet, bool bMedia );
  OdResult updateMediaListForActiveDevice( const OdDbPlotSettings* pPlotSet );
  int findDeviceByName(const OdString& pName) const;
  int findMediaByCanonicalName(const OdString& pName) const;
  int findMediaByLocaleName(const OdString& pName) const;
  bool isDeviceActive(const OdString& pName) const;
  bool isMediaActive( const OdString& pName ) const;
  virtual OdResult recalculatePlotData(OdDbPlotSettings* pPlotSet);
  bool isHWSwap(OdDbPlotSettings* pPlotSet) const;
  bool isWLessH(OdDbPlotSettings* pPlotSet) const;
  OdDbPlotSettingsValidatorPEPtr getValidator() const;
  virtual OdResult setCanonicalMediaName(OdDbPlotSettings* pPlotSet, const OdString& mediaName, bool setMediaDefault);


public:
  OdDbPlotSettingsValidatorImpl();

  virtual OdResult setPlotCfgName(
    OdDbPlotSettings* pPlotSet,
    const OdString& plotDeviceName,
    const OdString& mediaName = OdString::kEmpty);

  virtual OdResult setCanonicalMediaName(
    OdDbPlotSettings* pPlotSet,
    const OdString& mediaName);

  virtual OdResult setPlotOrigin(
    OdDbPlotSettings *pPlotSet,
    double xCoordinate,
    double yCoordinate);

  virtual OdResult setPlotPaperUnits(
    OdDbPlotSettings* pPlotSet,
    const PlotPaperUnits units);

  virtual OdResult setPlotRotation(
    OdDbPlotSettings* pPlotSet,
    const PlotRotation rotationType);

  virtual OdResult setPlotCentered(
    OdDbPlotSettings* pPlotSet,
    bool isCentered);

  virtual OdResult setPlotType(
    OdDbPlotSettings* pPlotSet,
    const PlotType plotAreaType);

  virtual OdResult setPlotWindowArea(
    OdDbPlotSettings* pPlotSet,
    double xmin,
    double ymin,
    double xmax,
    double ymax);

  virtual OdResult setPlotViewName(
    OdDbPlotSettings* pPlotSet,
    const OdString& viewName);

  virtual OdResult setUseStandardScale(
    OdDbPlotSettings* pPlotSet,
    bool useStandard);

  virtual OdResult setCustomPrintScale(
    OdDbPlotSettings* pPlotSet,
    double numerator,
    double denominator);

  virtual OdResult setCurrentStyleSheet(
    OdDbPlotSettings* pPlotSet,
    const OdString& styleSheetName);

  virtual OdResult setStdScaleType(
    OdDbPlotSettings* pPlotSet,
    const StdScaleType scaleType);

  virtual OdResult setStdScale(
    OdDbPlotSettings* pPlotSet,
    double standardScale);

  virtual void plotDeviceList(
    OdArray<const OdChar*> & deviceList);

  virtual OdResult canonicalMediaNameList(
    OdDbPlotSettings* pPlotSet,
    OdArray<const OdChar*> & mediaList);

  virtual OdString getLocaleMediaName(
    OdDbPlotSettings *pPlotSet,
    const OdString&  canonicalName);

  virtual OdString getLocaleMediaName(
    OdDbPlotSettings *pPlotSet,
    int index);

  virtual OdResult setClosestMediaName(
    OdDbPlotSettings* pPlotSet,
    double paperWidth,
    double paperHeight,
    const PlotPaperUnits units,
    bool matchPrintableArea);

  virtual OdResult plotStyleSheetList(
    OdArray<const OdChar*> & styleList);

  virtual void refreshLists(
    OdDbPlotSettings* pPlotSet);

  virtual OdResult setZoomToPaperOnUpdate(
    OdDbPlotSettings* pPlotSet,
    bool doZoom);

  virtual OdResult setDefaultPlotConfig(
    OdDbPlotSettings* pPlotSet);
};

#endif // __DB_PLOTSETTINGS_IMPL_H__
