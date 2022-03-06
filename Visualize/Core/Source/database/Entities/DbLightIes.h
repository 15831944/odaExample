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

#ifndef __OD_DB_LIGHTIES__
#define __OD_DB_LIGHTIES__

#include "TD_PackPush.h"

#include "Gi/GiLightTraits.h"

class OdGiGeometry;
class OdTvDbHostAppServices;
class OdTvDbDatabase;

class OdTvDbLightIes
{
  public:
    ODRX_HEAP_OPERATORS();

	  OdTvDbLightIes();
	  ~OdTvDbLightIes();

    void buildInternalRepresentation(double *vertAngles, OdInt32 numVertAngles, double *horzAngles, OdInt32 numHorzAngles, double **candelaDistribution);
    void render(OdGiGeometry *pWD, double scale, OdInt32 interpolation = 0) const;

    double *vertAngles() const;
    OdInt32 numVertAngles() const;
    double *horzAngles() const;
    OdInt32 numHorzAngles() const;
    double **candelaDistribution() const;
    double maxCandela() const;
    OdGiWebLightTraits::WebFileType fileType() const;
    OdGiWebLightTraits::WebSymmetry fileSymmetry() const;
    bool isHorzAng90To270() const;

    double getValue(double theta, double phi) const;
    double getValue_ipl(double theta, double phi) const;
    bool load(const OdChar *pFileName, OdTvDbHostAppServices *pSvcs, OdTvDbDatabase *pDb);

  private:
    double *_vertAngles;
    OdInt32 _numVertAngles;
    double *_horzAngles;
    OdInt32 _numHorzAngles;
    double **_candelaDistribution;
    double _maxCandela;
    OdGiWebLightTraits::WebFileType _fileType;
    OdGiWebLightTraits::WebSymmetry _symmetryType;
    bool _horzAng90To270;

    void drawCandelaDistribution(OdGiGeometry *pWD, double scale) const;
    void drawCandelaDistribution_ipl(OdGiGeometry *pWD, double scale, int level) const;

    void freeArrays(double *&vertAngles, OdInt32 &numVertAngles, double *&horzAngles, OdInt32 &numHorzAngles, double **&candelaDistribution);
};

#include "TD_PackPop.h"

#endif // __OD_DB_LIGHTIES__
