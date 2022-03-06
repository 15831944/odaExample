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


#ifndef _ODTV_TRAITSSTORAGE_H_INCLUDED_
#define _ODTV_TRAITSSTORAGE_H_INCLUDED_

#include "TD_PackPush.h"

// TD_GI
#include "GiWorldDraw.h"
#include "GiSubEntityTraitsData.h"
#include "Gi/GiTextStyle.h"
// TD_DB
#include "DbObjectId.h"
#include "DbFiler.h"			// need for OdTvDbDwgFiler

//TD_DBRoot
#include "OdShxFont.h"
#include "OdFontTable.h"

//TV
#include "TvTraitsDefImpl.h"
#include "TvDataLink.h"

/** \details
    Saver of the GI subentity traits
*/
class OdTvTraitsSaver
{
  OdGiSubEntityTraitsData m_traitsData;
  OdUInt32 m_traitsChanges;
  OdGiCommonDraw* m_pCommonDraw;

public:

  OdTvTraitsSaver()
    : m_pCommonDraw(NULL)
    , m_traitsChanges(0)
  {
  }

  // setup
  void setCommonDraw(OdGiCommonDraw* pCommonDraw){ m_pCommonDraw = pCommonDraw;}
  //get
  OdGiCommonDraw* getCommonDraw() {return m_pCommonDraw;}
  // roll back
  void restoreTraits();
  // get all from world draw
  void storeTraits();

  // Setters
  void setColor(const OdTvCmEntityColor& color);
  void setLayer(OdDbStub* layerId);
  void setLineType(OdDbStub* lineTypeId);
  void setFillType(OdGiFillType fillType);
  void setLineWeight(OdDb::LineWeight lineWeight);
  void setLineTypeScale(double lineTypeScale = 1.0);
  void setThickness(double thickness);
  void setMaterial(OdDbStub* materialId);
  void setTransparency(const OdCmTransparency &transparency);
  void setSecondaryTrueColor(const OdTvCmEntityColor& color);
  void setDrawFlags(OdUInt32 flags);
  void setFill(const OdGiFill* pFill);
};

/** \details
    Set of common traits for the geometry data
*/
class OdTvGeometryDataTraits
{
  // changes flags
  enum
  {
    kColor          =        (1 << 0),
    kLinetypeScale  =        (1 << 1),
    kLayer          =        (1 << 2),
    kLinetype       =        (1 << 3),
    kMaterial       =        (1 << 4),
    kLineweight     =        (1 << 5),
    kVisible        =        (1 << 6),
    kSecondaryColor =        (1 << 7),
    kTransparency   =        (1 << 8)
  };

  // traits
  double            m_dLinetypeScale;
  OdTvCmEntityColor   m_color;
  OdTvCmEntityColor   m_secondaryColor; //specific color. Each geometry should decide about it usage individually. Not participate in 'playAndSave' method
  OdTvDbObjectId      m_layerId;
  OdTvDbObjectId      m_linetypeId;
  OdTvDbObjectId      m_materialId;
  OdUInt16          m_traitsChanges;
  OdDb::LineWeight  m_nLineweight;
  bool              m_bVisible;         //visibility. Each geometry should decide about it usage individually. Not participate in 'playAndSave' method
  OdCmTransparency  m_transparency;

public:
  // Constructors/destructors
  //
  OdTvGeometryDataTraits();
  ~OdTvGeometryDataTraits();

  // Accessors / transformers
  //
  double lineTypeScale() const;
  const OdTvCmEntityColor& color() const;
  const OdTvCmEntityColor& secondaryColor() const;
  OdDbStub* layer() const;
  OdDbStub* lineType() const;
  OdDbStub* material() const;
  const OdCmTransparency& transparency() const;
  OdDb::LineWeight lineWeight() const;
  bool visibility() const;

  void setLineTypeScale(double lineTypeScale);
  void setColor(const OdTvCmEntityColor& trueColor);
  void setSecondaryColor(const OdTvCmEntityColor& trueColor);
  void setLayer(OdDbStub* layerId);
  void setLineType(OdDbStub* lineTypeId);
  void setMaterial(OdDbStub* materialId);
  void setLineWeight(OdDb::LineWeight lineWeight);
  void setVisibility(bool bVisible);
  void setTransparency(const OdCmTransparency& transparency);
  void resetColor();
  void resetSecondaryColor();
  void resetLayer();
  void resetLinetype();
  void resetLinetypeScale();
  void resetMaterial();
  void resetLineWeight();
  void resetVisibility();
  void resetTransparency();

  //play data to traits
  void playAndSave(OdTvTraitsSaver& saver);
  bool hasColor();
  bool hasLineweight();
  bool hasSecondaryColor();
  bool hasLayer();
  bool hasLineType();
  bool hasMaterial();
  bool hasTransparency();
  bool hasVisibility();

  //read/write
  void read(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver);
  void write(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

private:
  void setColor(OdUInt32 color);
  void setSecondaryColor(OdUInt32 color);
};

inline double OdTvGeometryDataTraits::lineTypeScale() const
{
  return m_dLinetypeScale;
}
inline const OdTvCmEntityColor& OdTvGeometryDataTraits::color() const
{
  return m_color;
}
inline const OdTvCmEntityColor& OdTvGeometryDataTraits::secondaryColor() const
{
  return m_secondaryColor;
}
inline OdDbStub* OdTvGeometryDataTraits::layer() const
{
  return m_layerId;
}
inline OdDbStub* OdTvGeometryDataTraits::lineType() const
{
  return m_linetypeId;
}
inline OdDbStub* OdTvGeometryDataTraits::material() const
{
  return m_materialId;
}
inline const OdCmTransparency& OdTvGeometryDataTraits::transparency() const
{
  return m_transparency;
}
inline OdDb::LineWeight OdTvGeometryDataTraits::lineWeight() const
{
  return m_nLineweight;
}
inline bool OdTvGeometryDataTraits::visibility() const
{
  return m_bVisible;
}
inline void OdTvGeometryDataTraits::setLineTypeScale(double lineTypeScale)
{
  m_dLinetypeScale = lineTypeScale;
  SETBIT(m_traitsChanges, kLinetypeScale, true);
}
inline void OdTvGeometryDataTraits::setColor(const OdTvCmEntityColor& color)
{
  m_color = color;
  SETBIT(m_traitsChanges, kColor, true);
}
inline void OdTvGeometryDataTraits::setSecondaryColor(const OdTvCmEntityColor& color)
{
  m_secondaryColor = color;
  SETBIT(m_traitsChanges, kSecondaryColor, true);
}
inline void OdTvGeometryDataTraits::setColor(OdUInt32 color)
{
  m_color.setColor(color);
  SETBIT(m_traitsChanges, kColor, true);
}
inline void OdTvGeometryDataTraits::setSecondaryColor(OdUInt32 color)
{
  m_secondaryColor.setColor(color);
  SETBIT(m_traitsChanges, kSecondaryColor, true);
}
inline void OdTvGeometryDataTraits::setLayer(OdDbStub* layerId)
{
  m_layerId = layerId;
  SETBIT(m_traitsChanges, kLayer, true);
}
inline void OdTvGeometryDataTraits::setLineType(OdDbStub* lineTypeId)
{
  m_linetypeId = lineTypeId;
  SETBIT(m_traitsChanges, kLinetype, true);
}
inline void OdTvGeometryDataTraits::setMaterial(OdDbStub* materialId)
{
  m_materialId = materialId;
  SETBIT(m_traitsChanges, kMaterial, true);
}
inline void OdTvGeometryDataTraits::setTransparency(const OdCmTransparency &transparency)
{
  m_transparency = transparency;
  SETBIT(m_traitsChanges, kTransparency, true);
}
inline void OdTvGeometryDataTraits::setLineWeight(OdDb::LineWeight lineWeight)
{
  m_nLineweight = lineWeight;
  SETBIT(m_traitsChanges, kLineweight, true);
}
inline void OdTvGeometryDataTraits::setVisibility(bool bVisible)
{
  m_bVisible = bVisible;
  SETBIT(m_traitsChanges, kVisible, true);
}
inline void OdTvGeometryDataTraits::resetColor()
{
  m_color = OdCmEntityColor::kByLayer;
  SETBIT(m_traitsChanges, kColor, false);
}
inline void OdTvGeometryDataTraits::resetSecondaryColor()
{
  m_secondaryColor = OdCmEntityColor::kByLayer;
  SETBIT(m_traitsChanges, kSecondaryColor, false);
}
inline void OdTvGeometryDataTraits::resetLayer()
{
  OdTvDbObjectId nullId;
  nullId.setNull();

  m_layerId = nullId;
  SETBIT(m_traitsChanges, kLayer, false);
}
inline void OdTvGeometryDataTraits::resetLinetype()
{
  OdTvDbObjectId nullId;
  nullId.setNull();

  m_linetypeId = nullId;
  SETBIT(m_traitsChanges, kLinetype, false);
}
inline void OdTvGeometryDataTraits::resetLinetypeScale()
{
  m_dLinetypeScale = 1.0;
  SETBIT(m_traitsChanges, kLinetypeScale, false);
}
inline void OdTvGeometryDataTraits::resetMaterial()
{
  OdTvDbObjectId nullId;
  nullId.setNull();

  m_materialId = nullId;
  SETBIT(m_traitsChanges, kMaterial, false);
}
inline void OdTvGeometryDataTraits::resetLineWeight()
{
  m_nLineweight = OdDb::kLnWtByLwDefault;
  SETBIT(m_traitsChanges, kLineweight, false);
}
inline void OdTvGeometryDataTraits::resetVisibility()
{
  m_bVisible = true;
  SETBIT(m_traitsChanges, kVisible, false);
}
inline void OdTvGeometryDataTraits::resetTransparency()
{
  m_transparency = OdCmTransparency(1.);
  SETBIT(m_traitsChanges, kTransparency, false);
}

/** \details
    Set of specific traits for geometry type
*/
class OdTvGeomSpecificTraits : public OdTvIObjectImpl
{
  // changes flags
  enum GeomSpecificTraits
  {
    kPolylineColor        =        (1 << 0),
    kEdgesColor           =        (1 << 1),
    kFacesColor           =        (1 << 2),
    kVerticesColor        =        (1 << 3),
    kTextColor            =        (1 << 4),
    kLineWeight           =        (1 << 5),
    kEdgeWeight           =        (1 << 6),
    kLineLinetype         =        (1 << 7),
    kEdgeLinetype         =        (1 << 8),
    kLineLinetypeScale    =        (1 << 9),
    kEdgeLinetypeScale    =        (1 << 10),
    kPolylineLayer        =        (1 << 11),
    kEdgesLayer           =        (1 << 12),
    kFacesLayer           =        (1 << 13),
    kVerticesLayer        =        (1 << 14),
    kTextLayer            =        (1 << 15),
    kPolylineVisible      =        (1 << 16),
    kEdgesVisible         =        (1 << 17),
    kVerticesVisible      =        (1 << 18),
    kFacesVisible         =        (1 << 19),
    kTextVisible          =        (1 << 20),
    kPolylineTransparency =        (1 << 21),
    kFacesTransparency    =        (1 << 22),
    kTextTransarency      =        (1 << 23),
  };

  /*
  All fields below for each entity stores the final (net) values of the attributes, i.e. with taking into account
  the parent-inheritance. If it is need to check for the concreate entity whether
  the attribute was individually set, it is need to check the 'm_bLocalWasInitialized'
  flag is true and m_traitsChanges has requested type. 
  */

  // colors
  OdTvCmEntityColor   m_polylinesColor;
  OdTvCmEntityColor   m_edgesColor;
  OdTvCmEntityColor   m_facesColor;
  OdTvCmEntityColor   m_verticesColor;
  OdTvCmEntityColor   m_textColor;

  // line weights
  OdDb::LineWeight  m_lineWeight;
  OdDb::LineWeight  m_edgeWeight;

  // linetype
  OdTvDbObjectId  m_lineLinetype;
  OdTvDbObjectId  m_edgeLinetype;

  // linetype scale
  double  m_lineLinetypeScale;
  double  m_edgeLinetypeScale;

  // layer
  OdTvDbObjectId m_polylinesLayer;
  OdTvDbObjectId m_edgesLayer;
  OdTvDbObjectId m_verticesLayer;
  OdTvDbObjectId m_facesLayer;
  OdTvDbObjectId m_textLayer;

  // visibility
  bool m_polylinesVisible;
  bool m_edgesVisible;
  bool m_verticesVisible;
  bool m_facesVisible;
  bool m_textVisible;

  // transparency
  OdCmTransparency m_polylineTransparency;
  OdCmTransparency m_facesTransparency;
  OdCmTransparency m_textTransparency;

  unsigned int      m_nRefCounter;          // reference counter

  OdUInt32          m_traitsChangesParent;   // traits which was changed (from parent)
  OdUInt32          m_traitsChanges;         // traits which was changed (individually)

  // Constructor
  OdTvGeomSpecificTraits();

public:
  //destructor
  ~OdTvGeomSpecificTraits();

  // from using inside objects which is nt derived from 'OdTvIObject
  static OdTvSmartPtrInternal<OdTvGeomSpecificTraits> createObject();

  // inheritance stuff
  void copyDataFromParent(OdTvGeomSpecificTraits* pParentData);

  //read/write
  void read(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver);
  void write(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  // copying stuff
  void copyLocalTo(OdTvGeomSpecificTraits* pTargetData) const;

  // Accessors / transformers
  bool                    hasLocalChanges() const;
  bool                    hasChangesParent() const;

  bool                        hasColorData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalColorData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentColorData(OdTvGeometryData::GeometryTypes geomType) const;
  const OdTvCmEntityColor&    getColorData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setColorData(const OdTvCmEntityColor& color, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void                        resetColorData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  bool                        hasLineWeightData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalLineWeightData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentLineWeightData(OdTvGeometryData::GeometryTypes geomType) const;
  OdDb::LineWeight            getLineWeightData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setLineWeightData(OdDb::LineWeight lw, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true); 
  void                        resetLineWeightData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  bool                        hasLinetypeData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalLinetypeData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentLinetypeData(OdTvGeometryData::GeometryTypes geomType) const;
  OdTvDbObjectId                getLinetypeData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setLinetypeData(OdTvDbObjectId lt, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void                        resetLinetypeData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  bool                        hasLinetypeScaleData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalLinetypeScaleData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentLinetypeScaleData(OdTvGeometryData::GeometryTypes geomType) const;
  double                      getLinetypeScaleData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setLinetypeScaleData(double ltScale, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void                        resetLinetypeScaleData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  bool                        hasLayerData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalLayerData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentLayerData(OdTvGeometryData::GeometryTypes geomType) const;
  OdTvDbObjectId                getLayerData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setLayerData(OdTvDbObjectId l, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void                        resetLayerData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  bool                        hasVisibilityData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalVisibilityData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentVisibilityData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        getVisibilityData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setVisibilityData(bool bVisible, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void                        resetVisibilityData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  bool                        hasTransparencyData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasLocalTransparencyData(OdTvGeometryData::GeometryTypes geomType) const;
  bool                        hasParentTransparencyData(OdTvGeometryData::GeometryTypes geomType) const;
  const OdCmTransparency&     getTransparencyData(OdTvGeometryData::GeometryTypes geomType) const;
  void                        setTransparencyData(const OdCmTransparency& transparency, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void                        resetTransparencyData(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

private:

  GeomSpecificTraits  traitsForColor(OdTvGeometryData::GeometryTypes geomType) const; 
  GeomSpecificTraits  traitsForLayer(OdTvGeometryData::GeometryTypes geomType) const;
  GeomSpecificTraits  traitsForVisibility(OdTvGeometryData::GeometryTypes geomType) const;
  GeomSpecificTraits  traitsForTransparency(OdTvGeometryData::GeometryTypes geomType) const;
  void                updateTraitsChanges(GeomSpecificTraits traits, bool bFromParent);
  void                resetTraitsChanges(GeomSpecificTraits traits, bool bFromParent);
};

typedef OdTvSmartPtrInternal<OdTvGeomSpecificTraits> OdTvGeomSpecificTraitsPtr;

#include "TD_PackPop.h"

#endif //_ODTV_TRAITSSTORAGE_H_INCLUDED_

