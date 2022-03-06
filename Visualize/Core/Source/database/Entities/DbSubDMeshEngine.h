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

#ifndef _ODDBSUBDMESHENGINE_INCLUDED_
#define _ODDBSUBDMESHENGINE_INCLUDED_

#include "Int32Array.h"
#include "GsMarkerArray.h"
#include "Ge/GeDoubleArray.h"
#include "Gi/GiMaterial.h"
#include "CmEntityColorArray.h"

namespace SUBDENGINE
{
  static const OdUInt32 gsMarkersNULL = 0;

  struct FaceData
  {
    OdUInt32         nNewDataStart;

    OdGsMarker       MarkersDefault;
    OdCmEntityColor  tcolorsDefault;
    OdDbStub*        MaterialIdsDefault;
//    OdGiMapper       MappersDefault;
    OdTvCmTransparency TransparencyDefault;

    OdGsMarkerArray           Markers;
    OdCmEntityColorArray      tcolors;
    OdArray<OdDbStub*>        MaterialIds;
//    OdArray<OdGiMapper>       Mappers;
    OdArray<OdTvCmTransparency> Transparency;

    FaceData() : nNewDataStart(0), MarkersDefault(0), MaterialIdsDefault(0) {}

    void applyDataFromTo(OdUInt32 nFaceIndex, OdUInt32 nNewFaceIndex)
    {
      if (!Markers.isEmpty())
      {
        if (Markers.size() <= nNewFaceIndex)
          Markers.resize(nNewFaceIndex+1, MarkersDefault);

        Markers[nNewFaceIndex] = Markers[nFaceIndex];
      }
      if (!tcolors.isEmpty())
      {
        if (tcolors.size() <= nNewFaceIndex)
          tcolors.resize(nNewFaceIndex+1, tcolorsDefault);

        tcolors[nNewFaceIndex] = tcolors[nFaceIndex];
      }
      if (!MaterialIds.isEmpty())
      {
        if (MaterialIds.size() <= nNewFaceIndex)
          MaterialIds.resize(nNewFaceIndex+1, MaterialIdsDefault);

        MaterialIds[nNewFaceIndex] = MaterialIds[nFaceIndex];
      }
//       if (!Mappers.isEmpty())
//       {
//         if (Mappers.size() <= nNewFaceIndex)
//           Mappers.resize(nNewFaceIndex+1);
// 
//         Mappers[nNewFaceIndex] = Mappers[nFaceIndex];
//       }
      if (!Transparency.isEmpty())
      {
        if (Transparency.size() <= nNewFaceIndex)
          Transparency.resize(nNewFaceIndex+1, TransparencyDefault);

        Transparency[nNewFaceIndex] = Transparency[nFaceIndex];
      }
    }

    void startNewData()
    {
      if (!tcolors.isEmpty())
        nNewDataStart = tcolors.size();
      else if (!Markers.isEmpty())
        nNewDataStart = Markers.size();
      else if (!MaterialIds.isEmpty())
        nNewDataStart = MaterialIds.size();
      //else if (!Mappers.isEmpty())
      //  nNewDataStart = Mappers.size();
      else if (!Transparency.isEmpty())
        nNewDataStart = Transparency.size();
    }

    void removeOldData()
    {
      if (!tcolors.isEmpty())
        tcolors.removeSubArray(0, nNewDataStart-1);
      if (!Markers.isEmpty())
        Markers.removeSubArray(0, nNewDataStart-1);
      if (!MaterialIds.isEmpty())
        MaterialIds.removeSubArray(0, nNewDataStart-1);
      //if (!Mappers.isEmpty())
      //  Mappers.removeSubArray(0, nNewDataStart-1);
      if (!Transparency.isEmpty())
        Transparency.removeSubArray(0, nNewDataStart-1);

      nNewDataStart = 0;
    }

    void fillGi(OdGiFaceData &fd)
    {
      fd.setTrueColors(tcolors.asArrayPtr());
      fd.setSelectionMarkers(Markers.asArrayPtr());
      fd.setMaterials(MaterialIds.asArrayPtr());
      //fd.setMappers(Mappers.asArrayPtr());
      fd.setTransparency(Transparency.asArrayPtr());
    }
  };

  struct CreaseInfo
  {
    static const double UNINITCREASE;
    static const double NOCREASE_VALUE;

    OdUInt32Array &EdgeMarkers;
    OdGeDoubleArray &EdgeCrease;
    OdInt32Array &Edges;
    mutable std::map<OdUInt64, OdUInt32> m_cache;
    CreaseInfo(OdGeDoubleArray &ec, OdInt32Array &e, OdUInt32Array &em)
      : EdgeCrease(ec)
      , Edges(e)
      , EdgeMarkers(em)
    { }

    CreaseInfo(const OdGeDoubleArray &ec, const OdInt32Array &e, const  OdUInt32Array &em)
      : EdgeCrease((OdGeDoubleArray &)ec)
      , Edges((OdInt32Array &)e)
      , EdgeMarkers((OdUInt32Array &)em)
    { }

    bool auditMe () const;
    OdInt32Array::const_iterator findEdge(OdInt32 V0, OdInt32 V1, OdInt32Array::const_iterator pFrom = 0) const;
    OdInt32Array::const_iterator findEdge0(OdInt32 V0, OdInt32 V1, OdInt32Array::const_iterator pFrom = 0) const;
    OdGeDoubleArray::const_iterator findCrease(OdInt32 EdgeVx1, OdInt32 EdgeVx2, OdInt32 *pEdgePos) const;

    void addCreaseWithCheck(OdInt32 edge1, OdInt32 edge2, double dCrease, OdInt32 gsMarker, bool bEdgeHasPair);
  };

  bool zeroCrease(const OdGePoint3dArray &vxs, const OdInt32Array &faces, const CreaseInfo &creaseInfo, OdGePoint3dArray &vxs1, OdInt32Array &faces1, FaceData &faceData, int nLevel, CreaseInfo &newCreaseInfo);
};

#endif // _ODDBSUBDMESHENGINE_INCLUDED_
