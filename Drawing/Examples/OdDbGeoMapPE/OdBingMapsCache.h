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

#ifndef _OD_BINGMAPSCACHE_
#define _OD_BINGMAPSCACHE_

#include "OdaCommon.h"
#include "DbSystemServices.h"
#include "DbHostAppServices.h"

#include "Ge/GeExtents2d.h"
#include "DbGeoData.h"
#include "DbGeoMap.h"

#include <curl/multi.h>
#include <tinyxml.h>
#include <math.h>
#define STL_USING_ALL
#include "OdaSTL.h"

//////////////////////////
// OdDbGeoMapTile
//////////////////////////
class OdDbGeoMapTile
{
  char m_cMapTypeId;
  int m_nLOD;
  OdInt32 m_nTileX;
  OdInt32 m_nTileY;
public:
  OdDbGeoMapTile();
  OdDbGeoMapTile(char cMapTypeId, int nLOD, OdInt32 nTileX, OdInt32 nTileY);
  void set(char cMapTypeId, int nLOD, OdInt32 nTileX, OdInt32 nTileY);
  void getUrl(OdAnsiString & sUrl) const;
  void getParentTile(OdDbGeoMapTile & tile) const;
  int getLOD() const;
  OdInt32 getX() const;
  OdInt32 getY() const;
  bool makeParentTile();
  bool operator< (const OdDbGeoMapTile & tile) const;
  bool operator== (const OdDbGeoMapTile& tile) const;
};
//////////////////////////
// OdDbGeoMapTile end
//////////////////////////


//////////////////////////
// OdBingMapsCache
//////////////////////////
#define GEO_CURL_MAX_CONNECTION_NUM 16
#define MAX_TILES_COUNT 5000

class OdBingMapsCache
{
  typedef std::deque <OdDbGeoMapTile> Deque;
  Deque m_deque;
  typedef std::map<OdDbGeoMapTile, OdGiRasterImagePtr> Map;
  Map m_map;
  OdBinaryData m_metadataAerial;
  OdBinaryData m_metadataRoad;
  OdBinaryData m_metadatakHybrid;
  OdGiRasterImagePtr m_pRasterLogoGlobal;
  OdMutex m_mutex;
public:
  OdBingMapsCache();
  OdResult getTiles(const std::set<OdDbGeoMapTile>& arrTiles, OdArray<OdGiRasterImagePtr>& arrRes);
  OdResult getBrandLogo(OdGiRasterImagePtr& pRasterLogo, bool bReset = false);
  OdResult getProviderMetadata(OdGeoMapType eMapType, OdBinaryData& metadata, bool bReset = false);
  OdResult getProvidersString(OdGeoMapType eMapType, const OdDbGeoData* pGeoData, int nLOD, const OdGePoint2dArray& arrImageArea, OdStringArray& arrCopyrightStrings);
};

extern OdBingMapsCache* g_OdBingMapsCache;
//////////////////////////
// OdBingMapsCache end
//////////////////////////

#endif // _OD_BINGMAPSCACHE_
