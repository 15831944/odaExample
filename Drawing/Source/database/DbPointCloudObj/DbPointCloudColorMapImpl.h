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
#ifndef _ODDBPOINTCLOUDCOLORMAPIMPL_INCLUDED_
#define _ODDBPOINTCLOUDCOLORMAPIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbPointCloudObj/DbPointCloudColorMap.h"
#include "Objects/DbObjectImpl.h"
#include "OdaSTL.h"


class OdDbPointCloudColorRampImpl
{
  friend class OdDbPointCloudColorRamp;
  friend class OdDbPointCloudColorMap;
  friend class findRampByGUID;
  
private:

  class RampItem
  {
  public:
    int color;
    bool visibility;
  };

  OdArray<RampItem> m_Items;
  OdString name;
};

class OdDbPointCloudClassificationColorRampImpl
{
  friend class OdDbPointCloudClassificationColorRamp;
  friend class OdDbPointCloudColorMap;

private:

  class RampItem
  {
  public:
    int color;
    bool visibility;
  };

  OdArray<RampItem> m_Items;
  OdString name;
};


class OdDbPointCloudColorMapImpl : public OdDbObjectImpl
{
  friend class OdDbPointCloudColorMap;

public: 
  OdDbPointCloudColorMapImpl();

  static OdDbPointCloudColorMapImpl* getImpl( const OdDbPointCloudColorMap *pObj )
  {
    return (OdDbPointCloudColorMapImpl*)OdDbSystemInternals::getImpl( pObj );
  }
private:

  OdInt16 m_unk70_1;
  OdString m_defaultIntensityColorScheme;
  OdString m_defaultElevationColorScheme;
  OdString m_defaultClassificationColorScheme;

  std::map<OdString, OdDbPointCloudColorRamp> m_colorRamps;
 
  std::map<OdString, OdDbPointCloudClassificationColorRamp> m_classColorRamp;

  OdArray<OdPoinCloudColorSchemeCollectionReactor *> m_reactors;

};

#endif //_ODDBPOINTCLOUDCOLORMAPIMPL_INCLUDED_
