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


#ifndef _ODTV_ENTITYGEOMETRYDATA_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRYDATA_H_INCLUDED_

#include "TD_PackPush.h"
#include "GiWorldDraw.h"
#include "GiViewportDraw.h"
#include "ChunkAllocator.h"
#include "TvGeometryData.h"
#include "TvInterfaceWrappers.h"
#include "TvDataLink.h"
#include "TvEntity.h"
#include "TvTraitsStorage.h"
#include "TvUserDataImpl.h"
#include "OdStack.h"
#define STL_USING_SET
#include "OdaSTL.h"

//DB Experiment
#include "DbObjectId.h"
#include "GiGeometrySimplifier.h"

class OdTvGeometryDataImpl;

class OdTvEntityImpl;
typedef OdSmartPtr<OdTvEntityImpl> OdTvEntityImplPtr;

class OdTvStringAccess : public OdString
{
public:
  static OdUInt64 getObjectSize(const OdString* pString)
  {
    if (pString == NULL)
      return 0;

    //base size
    OdUInt64 res = sizeof(OdStringData);

    //case for the ansi string
    OdAnsiString* pAString = (static_cast<const OdTvStringAccess*>(pString))->getAnsiString();
    if (pAString)
      res += (sizeof(OdStringDataA) + (pAString->getAllocLength() + 1) * sizeof(char));

    //case for unicode string
    if (pString->getAllocLength() > 0)
      res += ((pString->getAllocLength() + 1) * sizeof(OdChar));

    return res;
  }
};

class OdTvTriangulatorImpl : public OdGiGeometrySimplifier
{
public:
  OdTvTriangulatorImpl(OdInt32Array* pFaceArr, const OdTvPointArray* pVerticesArr, OdUInt32 startFaceIndex = 0)
    : m_pFacesArr(pFaceArr)
    , m_iCurFaceIndex(startFaceIndex)
  {
    setVertexData(pVerticesArr->size(), pVerticesArr->getPtr());
  }

  OdTvTriangulatorImpl(OdInt32Array* pFaceArr, const OdTvPoint* pVerticesArr, OdUInt32 nVertices, OdUInt32 startFaceIndex = 0)
    : m_pFacesArr(pFaceArr)
    , m_iCurFaceIndex(startFaceIndex)
  {
    setVertexData(nVertices, pVerticesArr);
  }

  virtual ~OdTvTriangulatorImpl() { }

  virtual void triangleOut(const OdInt32* vertices, const OdGeVector3d* pNormal)
  {
    if (m_pFacesArr)
    {
      m_pFacesArr->push_back(m_iCurFaceIndex);
      m_pFacesArr->push_back(vertices[0]);
      m_pFacesArr->push_back(vertices[1]);
      m_pFacesArr->push_back(vertices[2]);
    }
  }

  virtual void generateShellFaces(OdInt32 faceListSize, const OdInt32* pFaceList, const OdGiEdgeData* pEdgeData = 0, const OdGiFaceData* pFaceData = 0)
  {
    const OdInt32* pFaceListEnd = pFaceList + faceListSize;
    OdInt32 nFaceSize, nFaceIndex = m_iCurFaceIndex;

    for (; pFaceList < pFaceListEnd; ++nFaceIndex)
    {
      const OdInt32* pSaveFaceList = pFaceList;

      nFaceSize = *pFaceList;
      if (nFaceSize >= 0)
        pFaceList += (nFaceSize + 1);
      if (pFaceList < pFaceListEnd && *pFaceList < 0) // hole
      {
        do
        {
          nFaceSize = abs(*pFaceList);
          pFaceList += (nFaceSize + 1);
        } while (pFaceList < pFaceListEnd && *pFaceList < 0);
      }

      // update face index
      m_iCurFaceIndex = nFaceIndex;

      shellFaceOut(OdInt32(pFaceList - pSaveFaceList), pSaveFaceList, 0);
    }
  }

protected:
  OdInt32Array* m_pFacesArr;
  OdUInt32      m_iCurFaceIndex;
};

/** \details
This class implements the attributes storage (traits and transform) for the all geometry objects
*/
class OdTvGeometryDataAttributes
{
public:
  OdTvGeometryDataAttributes() : m_pLocalTraits(NULL), m_pTransform(NULL){}
  ~OdTvGeometryDataAttributes();

  OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType, OdTvGeometryData::GeometryTypes firstColorGeomType, OdTvGeometryData::GeometryTypes secondColorGeomType);
  OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType) const;
  OdTvResult setLineWeight(const OdTvLineWeightDef& lw);
  OdTvLineWeightDef getLineWeight() const;
  OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvDbDatabase* pDb = NULL);
  OdTvLinetypeDef getLinetype(OdTvDbDatabase* pDb) const;
  OdTvResult setLinetypeScale(double linetypeScale);
  double getLinetypeScale() const;
  OdTvResult setLayer(const OdTvLayerDef& l, OdTvDbDatabase* pDb = NULL);
  OdTvLayerDef getLayer(OdTvDbDatabase* pDb) const;
  OdTvResult setVisibility(const OdTvVisibilityDef& visible);
  OdTvVisibilityDef getVisibility() const;
  OdTvResult setTransparency(const OdTvTransparencyDef& transparency);
  OdTvTransparencyDef getTransparency() const;
  OdTvResult setMaterial(const OdTvMaterialDef& material, OdTvDbDatabase* pDb = NULL);
  OdTvMaterialDef getMaterial(OdTvDbDatabase* pDb) const;

  OdTvResult rotate(double x, double y, double z);
  OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin);
  OdTvResult translate(double x, double y, double z);
  OdTvResult translate(const OdTvVector& aVector);
  OdTvResult scale(double x, double y, double z);
  OdTvResult setModelingMatrix(const OdTvMatrix& matrix);
  OdTvMatrix getModelingMatrix() const;
  OdTvResult appendModelingMatrix(const OdTvMatrix& matrix);

protected:
  void setColorInternal(OdTvCmEntityColor& color, OdUInt16 geomType, OdTvGeometryData::GeometryTypes& firstColorGeomType, OdTvGeometryData::GeometryTypes& secondColorGeomType);
  void resetColor(OdUInt16 geomType, OdTvGeometryData::GeometryTypes& firstColorGeomType, OdTvGeometryData::GeometryTypes& secondColorGeomType);
  void resetLineWeight();
  void resetLinetype();
  void resetLinetypeScale();
  void resetLayer();
  void resetVisibility();
  void resetTransparency();
  void resetMaterial();

public:

  OdTvGeometryDataTraits*               m_pLocalTraits;         // pointer to the local traits data (NULL by default)
  OdTvMatrix*                           m_pTransform;           // transform matrix (NULL by default)
};

/** \details
This class is used to ensure OdGiGeometry::pushModelTransform()/OdGiGeometry::popModelTransform() 
consistency (exception safety) with additional optimization check of matrix identity.

\sa
TD_Gi

<group OdGi_Classes> 
*/
class OdGiModelTransformSaverTv
{
  OdGiGeometry& m_geom;
  bool          m_bExist;
public:
  OdGiModelTransformSaverTv(OdGiGeometry& geom, OdTvGeometryDataAttributes* pAttrib) : m_geom(geom)
  {
    OdGeMatrix3d* pMatr = NULL;
    if (pAttrib)
      pMatr = pAttrib->m_pTransform;

    m_bExist = pMatr != NULL;
    if (m_bExist)
      m_geom.pushModelTransform(*pMatr);
  }
  OdGiModelTransformSaverTv(OdGiGeometry& geom, OdGeMatrix3d* pMatr, OdGeMatrix3d* pPrevMatr = NULL) : m_geom(geom)
  {
    bool bFirstExist = pMatr != NULL;
    bool bSecondExist = pPrevMatr != NULL;

    m_bExist = (bFirstExist || bSecondExist);

    if (m_bExist)
    {
      if (bFirstExist && bSecondExist)
      {
        OdTvMatrix resMatr = *pMatr;
        resMatr.preMultBy(*pPrevMatr);
        m_geom.pushModelTransform(resMatr);
      }
      else if (bFirstExist)
        m_geom.pushModelTransform(*pMatr);
      else
        m_geom.pushModelTransform(*pPrevMatr);
    }
  }
  ~OdGiModelTransformSaverTv()
  {
    if (m_bExist)
      m_geom.popModelTransform();
  }
};

#define OD_TV_HEAP_OPERATORS_DEFINE(baseClass, num) \
  void* baseClass::operator new(size_t size) \
  { \
    if( odTvGetFactoryImpl()->getUseAllocatorForGeometryData() ) \
      return s_aAlloc.getAt(num)->alloc((int)size); \
    else \
      return ::odrxAlloc( size ); \
  } \
  void baseClass::operator delete(void* p) \
  { \
    if( odTvGetFactoryImpl()->getUseAllocatorForGeometryData() ) \
      s_aAlloc.getAt(num)->release(p); \
    else \
      ::odrxFree( p ); \
  }

/** \details
    This class implements the base for the all geometry type entity data objects
*/
class OdTvGeometryDataImpl : public OdTvIObject
{
protected:
  ODCA_HEAP_ALLOCATOR();
  friend class OdTvModule;

  /** \details
    Destructor.
  */
  virtual ~OdTvGeometryDataImpl();

public:

  /** \details
    reimplementation of the 'new' 'delete'.
  */
  ODCA_HEAP_OPERATORS();

  /** \details
    Constructor.
  */
  OdTvGeometryDataImpl();

  /** \details
    Enum for the geometries type
  */
  enum TvGeometryType
  {
    /*First block: as in TD_GI*/
    Circle = 0,
    CircleArc = 1,
    CircleWedge = 2,
    Ellipse = 3,
    EllipticArc = 4,
    Polyline = 5,
    Polygon = 6,
    Mesh = 7,
    Shell = 8,
    Sphere = 9,
    Cylinder = 10,
    Grid = 11,
    Text = 12,
    InfiniteLine = 13,
    Nurbs = 14,
    RasterImage = 15,
    PointCloud = 16,
    Insert = 17,
    SubEntity = 18,
    ColoredShape = 19,
    Box = 20,
    Brep = 21,
    RcsPointCloud = 24,
    ProgressiveMesh = 25,

    //FOR THE FUTURE
    /*CuttingSection = 21,
    NurbsSurf = 22,
    Marker = 23,*/

    DummyLast
  };

  /** \details
  Enum for the general geometry data flags
  */
  enum geomDataFlags
  {
    kRtInvisiblePerSession = 1,
    kInvisiblePersistent = 2,
    kSelectable = 4,
    kDrawEveryWhere = 8,              // All display modes.
    kDrawInWireframe = 16,            // Wireframe display mode.
    kDrawInRender = 32                // Rendering dispay mode.
  };

  //********************************************************************************************//
  //                                  Public interface                                          //
  //********************************************************************************************//

  /** \details
  Set the color of the geometry data
  */
  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll);

  /** \details
  Get the color of the geometry data as rgb, inherited or index
  */
  virtual OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll) const;

  /** \details
  Set the line weight of the geometry data
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw);

  /** \details
  Get the line weight of the geometry data
  */
  virtual OdTvLineWeightDef getLineWeight() const;

  /** \details
  Set the linetype of the geometry data
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvDbDatabase* pDb = NULL);

  /** \details
  Get the linetype of the geometry data
  */
  virtual OdTvLinetypeDef getLinetype(OdTvDbDatabase* pDb) const;

  /** \details
  Set the linetype scale of the geometry data
  */
  virtual OdTvResult setLinetypeScale(double linetypeScale);

  /** \details
  Get the linetype scale of the geometry data
  */
  virtual double getLinetypeScale() const;

  /** \details
  Set the layer of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& l, OdTvDbDatabase* pDb = NULL);

  /** \details
  Get the layer of the geometry
  */
  virtual OdTvLayerDef getLayer(OdTvDbDatabase* pDb) const;

  /** \details
  Set the visibility property of the geometry
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible);

  /** \details
  Get the visibility property of the geometry
  */
  virtual OdTvVisibilityDef getVisibility() const;

  /** \details
  Set the transparency property of the geometry
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency);

  /** \details
  Get the transparency property of the geometry
  */
  virtual OdTvTransparencyDef getTransparency() const;

  /** \details
  Sets the material for the geometry.
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material, OdTvDbDatabase* pDb = NULL);

  /** \details
  Retrieves the current material applied to the geometry.
  */
  virtual OdTvMaterialDef getMaterial(OdTvDbDatabase* pDb) const;

  /** \details
  Sets the selectability
  */
  virtual void setSelectability(const OdTvSelectabilityDef& selectability);

  /** \details
  Check if geometry data can be selected
  */
  virtual bool isSelectable() const;

  //**************************************************************************************
  // Misc methods
  //**************************************************************************************

  /** \details
  Set target display mode of the entity
  */
  virtual OdTvResult setTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetMode);

  /** \details
  Get target display mode of the entity
  */
  virtual OdTvGeometryData::TargetDisplayMode getTargetDisplayMode() const;

  /** \details
  Set the real time visibility property of the geometry data

  \param bVisible [in]  if false, make entity invisible
  */
  OdTvResult setTempVisibility(bool bVisible);

  /** \details
  Get the real time visibility property of the geometry data. True means visible
  */
  bool getTempVisibility();

  /** \details
  Get marker of this geometry data
  */
  OdGsMarker getMarker() const { return m_marker; };

  /** \details
  Get all markers of this geometry data (including subgeometry and all markers for the subentities)
  */
  virtual void getMarkers(std::set< OdGsMarker >& markers, std::set< OdGsMarker >* pCompareMarkers = NULL) const
  { 
    if (!pCompareMarkers)
      markers.insert(m_marker);
    else
    {
      if (pCompareMarkers->find(m_marker) == pCompareMarkers->end())
        markers.insert(m_marker);
    }
  };

  //**************************************************************************************
  // Group of the methods for the using transform matrix with this entity
  //**************************************************************************************

  /** \details
  Join rotation matrix to this matrix that rotates geometry around the X, Y and Z axes.
  */
  virtual OdTvResult rotate(double x, double y, double z);

  /** \details
  Join rotation matrix to this matrix with rotation around an arbitrary vector by number of degrees
  */
  virtual OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin);

  /** \details
  Join translation matrix to this matrix that moves geometry along X, Y, Z axis
  */
  virtual OdTvResult translate(double x, double y, double z);

  /** \details
  Join translation matrix to this matrix that moves geometry in vector distance
  */
  virtual OdTvResult translate(const OdTvVector& aVector);

  /** \details
  Join scale matrix to this matrix that scales multiplier along X, Y, Z axis
  */
  virtual OdTvResult scale(double x, double y, double z);

  /** \details
  Set the transform matrix which can rotate, transform and scale the entity
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix);

  /** \details
  Get the transform matrix which can rotate, transform and scale the entity
  */
  virtual OdTvMatrix getModelingMatrix() const;

  /** \details
  Multiply existing transform matrix by new matrix
  */
  virtual OdTvResult appendModelingMatrix(const OdTvMatrix& matrix);

  /** \details
  Returns all appropriate object snap points of this geometry object.
  */
  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  /** \details
   Retrieves the flag of supporting snap mode of the geometry data.
   */
  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

  /** \details
  Return close point to pickPoint.
  */
  virtual OdTvPoint getClosestPoint(const OdTvPoint& pickPoint, const OdTvPointArray& points, const OdTvVector& snapDir) const;

  /** \details
  Get transform matrix from this geometry, and parent sub entities (if exists)
  */
  void getTransformWithSubEntities(OdTvMatrix& transform) const;

  //********************************************************************************************//
  //                                  Internal methods                                          //
  //********************************************************************************************//

  /** \details
  Return the link to this data. Method for 'OdTvLinkIdAccess'
  */
  OdTvDataLink* getLink()
  {
    return m_pLink;
  }

  /** \details
    Set/get previous and next items in the list
  */
  void setPrev(OdTvGeometryDataImpl* pData);
  void setNext(OdTvGeometryDataImpl* pData);

  OdTvGeometryDataImpl* getPrev() const;
  OdTvGeometryDataImpl* getNext() const;

  /** \details
  Set/get parent entity
  */
  virtual void            setParentEntityId(OdTvDbObjectId dbId);
  virtual OdTvDbObjectId  getParentEntityId() const;

  /** \details
    Remove the itself linkage

    \remarks
    This is an equivalent to removeFromDatabase for database objects.
    The object itself could be not deleted but it is already not relevant
  */
  void removeLinkage();

  /** \details
   empty method

   \remarks
   Just for the interface compatibility with the database objects
 */
  void setOpenMode(OdTv::OpenMode mode);

  /** \details
    special methods for read/write thickness and normal
  */
  double        rdThickness(OdTvDbDwgFiler* pFiler);
  OdTvVector& rdNormal(OdTvDbDwgFiler* pFiler, OdTvVector& p);

  void wrThickness(OdTvDbDwgFiler* pFiler, double val) const;
  void wrNormal(OdTvDbDwgFiler* pFiler, const OdTvVector& p) const;

  /** \details
  Checks that there is parent entity specific traits or local traits
  */
  bool hasSpecificOrLocalTraits(const OdTvEntityImpl* pParentEntity, OdTvGeometryData::GeometryTypes clGeomType) const;

  /** \details
  Checks that there is parent entity specific traits or local traits
  */
  void setSpecificAndLocalTraits(OdTvTraitsSaver& saver, const OdTvEntityImpl* pParentEntity, OdTvGeometryData::GeometryTypes clGeomType) const;

  /** \details
  Set the filling traits for the objects (flags and secondary color if need)
  */
  void setFillingTraits(OdTvTraitsSaver& saver, const OdTvEntityImpl* pParentEntity, OdUInt8 fillingflags = OdTv::kAsSolid) const;

  /** \details
  Return true and only true if the data should update traits
  */
  bool isNeedUpdateTraits(const OdTvEntityImpl* pParentEntity, OdTvGeometryData::GeometryTypes clGeomType ) const
  {
    return hasThickness() || hasFilling() || hasSpecificOrLocalTraits(pParentEntity, clGeomType);
  }

  /** \details
  Set selection marker according to the selection state
  */
  void setSelectionMarker(OdGiCommonDraw* pCommonDraw, OdGsMarker& marker) const;

  /** \details
  Set selection marker according to the selection state
  */
  void setSelectionMarker(OdGsMarker& marker) const;

  /** \details
  Reset selection marker
  */
  void resetSelectionMarker() const;

  //********************************************************************************************//
  //                                  Virtual interface                                         //
  //********************************************************************************************//

  /** \details
    Returns the geometry type of the entity data
  */
  virtual TvGeometryType entityGeometryDataType() const = 0;

  /** \details
   Draw method.

   \remarks
   This method should be called inside 'subWorldDraw' method of the TvEntity for each GeometryData object
 */
  virtual bool draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const = 0;

  /** \details
  Draw method.

  \remarks
  This method should be called inside 'subViewportDraw' method of the TvEntity for each GeometryData object
  */
  virtual void drawView(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity) const { return;  }

  /** \details
  Fake draw method (only for set the appropriate markers)

   \remarks
   This method should be called inside 'subWorldDraw' method of the TvEntity for each GeometryData object which target display mode is not satisfy to the view render mode
  */
  virtual void drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;

  /** \details
   Before draw method (when it is need to recalculate something before draw)

   \remarks
   This method should be called inside 'subWorldDraw' method of the TvEntity for each GeometryData object
 */
  virtual void beforeDraw(const OdTvEntityImpl* pParentEntity) { return; }

  /** \details
    Returns the type of the primary color

    \remarks
    Each geometry has primary color
  */
  virtual OdTvGeometryData::GeometryTypes getFirstColorGeomType() const = 0;

  /** \details
    Returns the type of the secondary color

    \remarks
    Not each geometry has secondary color
  */
  virtual OdTvGeometryData::GeometryTypes getSecondColorGeomType() const { return OdTvGeometryData::kNone; }

  /** \details
  Returns true if and only if geometry data has thickness
  */
  virtual bool hasThickness() const { return false; }

  /** \details
  Returns true if and only if geometry data is filled
  */
  virtual bool hasFilling() const { return false; }

  /** \details
  Sets shared data to geometry data before read
  */
  virtual void setReadSharedData(void *pSharedData) { return; }

  /** \details
  get geometry data about the some shared data
  */
  virtual void* getReadSharedData() const {return NULL;}

  /** \details
    Read method.

    \remarks
    This method should be called inside 'dwgInFields' method of the TvEntity for each GeometryData object
  */
  virtual void read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());

  /** \details
    Write method.

    \remarks
    This method should be called inside 'dwgOutFields' method of the TvEntity for each GeometryData object
  */
  virtual void write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  /** \details
  Copy data to the specified geometry
  */
  virtual bool copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /** \details
  Some actions after transformation was modified (it may be own transformation of parent sub entity transformation)
  */
  virtual void actionAfterTransformModifying() {};

  /** \details
  Copy traits from entity
  */
  virtual void copyTraitsFromEntity(OdTvEntityImpl* pEntity, bool bAllowSubstituteTransform);

  //**************************************************************************************
  // OdTvIObject methods implementation
  //**************************************************************************************

  /** \details
  Declares the method incrementing the reference counter in objects derived from this class.
  */
  virtual void addRef()
  {
    ++m_nRefCounter;
  }

  /** \details
  Declares the method decrementing the reference counter in objects derived from this class.
  */
  virtual void release()
  {
    if (m_nRefCounter == 1)
    {
      delete this;
    }
    else
      --m_nRefCounter;
  }
  /** \details
  Returns the value of the reference counter, that is, the number of references to an instance of this class.
  */
  virtual long numRefs() const
  {
    return m_nRefCounter;
  }

  //**************************************************************************************
  // OdTvXDataStorage methods implementation
  //**************************************************************************************

  /** \details
  Append the user data to the entity
  */
  OdTvResult appendUserData(OdTvUserData* pUserData, const OdTvRegAppId& id);

  /** \details
  Get user data
  */
  OdTvUserData* getUserData(const OdTvRegAppId& id) const;

  /** \details
  Get the count of the user data
  */
  OdUInt32 getUserDataCount();

  /** \details
  All registered apps for which the user data is set
  */
  OdTvResult getUserDataApps(OdTvRegAppIdArray& ids);

  /** \details
  Removes user data
  */
  OdTvResult removeUserData(const OdTvRegAppId& id);

  /** \details
  Removes all user data
  */
  OdTvResult clearUserData();

  /** \details
  Read method.
  */
  void readXData(OdTvDbDwgFiler* pFiler, OdTvDbDatabase* pDb, OdTvVSFVersion ver);

  /** \details
  Write method.
  */
  void writeXData(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getXDataObjectSize() const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getSizeOfDynamicData(bool bIncludeDataFromOwnHeap = false) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const = 0;

  /** \details
  Return the value of memory, which all geometry chunks takes up.
  */
  static OdUInt64 getChunksSize(OdTvResult* rc = NULL);

  static bool isRayIntersectBox(const OdTvPoint& rayStartPos, const OdTvVector& rayDir, const OdTvPoint& boxMin, const OdTvPoint& boxMax);

  static bool isRayIntersectTriangle(const OdTvPoint& pickPoint, const OdTvVector& eyeDir, const OdTvPoint& v0, const OdTvPoint& v1, const OdTvPoint& v2, double& u, double& v);

protected:

  bool isGeomTypeInvisible(OdTvGeometryData::GeometryTypes geomType, const OdTvEntityImpl* pParentEntity) const;
  OdTvPoint getClosestPointFromLine(const OdTvPoint& start, const OdTvPoint& end, const OdTvPoint& pickPoint, const OdTvVector& snapDir) const;
  OdTvPoint getCenterFromPoints(const OdTvPointArray& points) const;
  OdTvVector getSnapDirFromMatrix(const OdTvMatrix& xWorldToEye, const OdTvPoint& pickPoint, double focalLength) const;
  void drawForMarkersTwoGeomTypeCase(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  void drawForMarkers3DCase(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;

  /** \details
  Get closest point to the eyeDir ray through the pick point and the face
  */
  bool getClosestPointFromTriangFace(OdUInt32 index, OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint
    , const OdTvVector& eyeDir, const OdInt32* pFaceArr, const OdTvPoint* pVerticesArr
    , OdTvPoint& closestPoint, const OdTvMatrix* pTransform = NULL) const;

  bool getClosestVertex(const OdTvPoint2d& pickPnt2d, const OdTvPointArray& faceVertices, const OdTvVector& eyeDir, const OdTvMatrix& totalTransform
    , const OdTvMatrix* pTransform, double& distance, OdTvPoint& closestVertex, const OdTvVector* pFaceNormal = NULL, bool bIgnoreNormal = false) const;

protected:

  template <typename T1, typename T2>
  struct secondValueComparator 
  { bool operator ()(const std::pair<T1, T2>& a, const std::pair<T1, T2>& b) const { return a.second > b.second; } };

  //attributes data
  OdTvGeometryDataAttributes*           m_pAttributes;          // pointer to the locase attributes (NULL by default)
  OdTvDbObjectId                        m_parentEntityId;       // pointer to the parent entity (this data need for the select with 'dynamicSubEntityHlt' option
  OdGsMarker                            m_marker;               // marker of this geometry
  OdTvGeometryDataImpl*                 m_pPrev;                // pointer to the previous data in the Doubly linked list of the data stored in the entity
  OdTvGeometryDataImpl*                 m_pNext;                // pointer to the next data in the Doubly linked list of the data stored in the entity
  OdTvXDataStorage*                     m_pUserData;            // pointer to the user data
  OdTvDataLink*                         m_pLink;                // pointer to the linker object which contains the pointer to this object
  unsigned int                          m_nRefCounter;          // reference counter
  mutable OdUInt32                      m_flags;                // different flags (first 16 is for geometry data, second 16 for the inheritants)
};

typedef OdTvSmartPtrInternal<OdTvGeometryDataImpl> OdTvGeometryDataImplPtr;



/** \details
    This is an wrapper of the interface class for OdTvGeometryData object.

    \remarks
    The purpose of this class is to connect the internal entity object with an interface object
*/

class OdTvGeometryDataWrapper : public OdTvGeometryData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvGeometryData)

  friend class OdTvGeometryDataIteratorImpl;
  friend class OdTvEntityImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Returns the smart ptr to the 'OdTvLineData' object
  */
  virtual OdTv::OdTvGeometryDataType getType(OdTvResult* rc = NULL) const;

  /** \details
  Returns the parent entity of the geometry data
  */
  virtual OdTvEntityId getParentEntity(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the parent subentity of the geometry data.
  */
  virtual OdTvGeometryDataId getParentSubEntity(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the top level parent entity of the geometry data.
  */
  virtual OdTvEntityId getParentTopLevelEntity(OdTvResult* rc = NULL) const;

  /** \details
  Set the color of the geometry data
  */
  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)kAll);

  /** \details
  Get the color of the geometry data as rgb, inherited or index
  */
  virtual OdTvColorDef getColor(GeometryTypes geomType = kAll, OdTvResult*rc = NULL);

  /** \details
  Set the line weight of the geometry data
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw);

  /** \details
  Get the line weight of the geometry data
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvResult*rc = NULL);

  /** \details
  Set the linetype of the geometry datay
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt);

  /** \details
  Get the linetype of the geometry data
  */
  virtual OdTvLinetypeDef getLinetype(OdTvResult*rc = NULL);

  /** \details
  Set the linetype scale of the geometry data
  */
  virtual OdTvResult setLinetypeScale(double linetypeScale);

  /** \details
  Get the linetype scale of the geometry data
  */
  virtual double getLinetypeScale(OdTvResult*rc = NULL);

  /** \details
  Set the layer of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& lt);

  /** \details
  Get the layer of the geometry
  */
  virtual OdTvLayerDef getLayer(OdTvResult*rc = NULL);

  /** \details
  Set the visibility property of the geometry
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible);

  /** \details
  Get the visibility property of the geometry
  */
  virtual OdTvVisibilityDef getVisibility(OdTvResult* rc = NULL) const;

  /** \details
  Set the transparency property of the geometry
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency);

  /** \details
  Get the transparency property of the geometry
  */
  virtual OdTvTransparencyDef getTransparency(OdTvResult* rc = NULL);

  /** \details
  Sets the material for the geometry.
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material);

  /** \details
  Retrieves the current material applied to the geometry.
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const;

  /** \details
  Get database of this object
  */
  virtual OdTvDatabaseId getDatabase(OdTvResult* rc = NULL);

  //**************************************************************************************
  // Misc methods
  //**************************************************************************************

  /** \details
  Set target display mode of the entity
  */
  virtual OdTvResult setTargetDisplayMode(TargetDisplayMode targetMode);

  /** \details
  Get target display mode of the entity
  */
  virtual TargetDisplayMode getTargetDisplayMode(OdTvResult*rc = NULL) const;

  /** \details
  Copy geometry to specified entity
  */
  virtual OdTvGeometryDataId copyTo(OdTvEntityId& targetEntityId, OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for the using transform matrix with this entity
  //**************************************************************************************

  /** \details
  Join rotation matrix to this matrix that rotates geometry around the X, Y and Z axes.
  */
  virtual OdTvResult rotate(double x, double y, double z);

  /** \details
  Join rotation matrix to this matrix with rotation around an arbitrary vector by number of degrees
  */
  virtual OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin);

  /** \details
  Join translation matrix to this matrix that moves geometry along X, Y, Z axis
  */
  virtual OdTvResult translate(double x, double y, double z);

  /** \details
  Join translation matrix to this matrix that moves geometry in vector distance
  */
  virtual OdTvResult translate(const OdTvVector& aVector);

  /** \details
  Join scale matrix to this matrix that scales multiplier along X, Y, Z axis
  */
  virtual OdTvResult scale(double x, double y, double z);

  /** \details
  Set the transform matrix which can rotate, transform and scale the entity
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix);

  /** \details
  Get the transform matrix which can rotate, transform and scale the entity
  */
  virtual OdTvMatrix getModelingMatrix(OdTvResult* rc = NULL) const;

  /** \details
  Multiply existing transform matrix by new matrix
  */
  virtual OdTvResult appendModelingMatrix(const OdTvMatrix& matrix);

  /** \details
  Returns all appropriate object snap points of this geometry object.
  */
  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  /** \details
   Retrieves the flag of supporting snap mode of the geometry data.
   */
  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // set of the methods, which have returned the typified data
  //**************************************************************************************

  /** \details
  Returns the smart ptr to the 'OdTvPolylineData' object if the data has appropriate type
  */
  virtual OdTvPolylineDataPtr getAsPolyline(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvCircleData' object if the data has appropriate type
  */
  virtual OdTvCircleDataPtr getAsCircle(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvCircleArcData' object if the data has appropriate type
  */
  virtual OdTvCircleArcDataPtr getAsCircleArc(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvCircleWedgeData' object if the data has appropriate type
  */
  virtual OdTvCircleWedgeDataPtr getAsCircleWedge(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvEllipseData' object if the data has appropriate type
  */
  virtual OdTvEllipseDataPtr getAsEllipse(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvEllipticArcData' object if the data has appropriate type
  */
  virtual OdTvEllipticArcDataPtr getAsEllipticArc(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvPolygonData' object if the data has appropriate type
  */
  virtual OdTvPolygonDataPtr getAsPolygon(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvShellData' object if the data has appropriate type
  */
  virtual OdTvShellDataPtr getAsShell(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvBrepData' object if the data has appropriate type
  */
  virtual OdTvBrepDataPtr getAsBrep(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvMeshData' object if the data has appropriate type
  */
  virtual OdTvMeshDataPtr getAsMesh(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvSphereData' object if the data has appropriate type
  */
  virtual OdTvSphereDataPtr getAsSphere(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvCylinderData' object if the data has appropriate type
  */
  virtual OdTvCylinderDataPtr getAsCylinder(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvBoxData' object if the data has appropriate type
  */
  virtual OdTvBoxDataPtr getAsBox(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvTextData' object if the data has appropriate type
  */
  virtual OdTvTextDataPtr getAsText(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvNurbsData' object if the data has appropriate type
  */
  virtual OdTvNurbsDataPtr getAsNurbs(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvInfiniteLineData' object if the data has appropriate type
  */
  virtual OdTvInfiniteLineDataPtr getAsInfiniteLine(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvRasterImageData' object if the data has appropriate type
  */
  virtual OdTvRasterImageDataPtr getAsRasterImage(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvpointCloudData' object if the data has appropriate type
  */
  virtual OdTvPointCloudDataPtr getAsPointCloud(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvGrid' object if the data has appropriate type
  */
  virtual OdTvGridDataPtr getAsGrid(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvColoredShape' object if the data has appropriate type
  */
  virtual OdTvColoredShapeDataPtr getAsColoredShape(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvEntity' object if the data has appropriate type
  */
  virtual OdTvEntityPtr getAsSubEntity(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvInsertData' object if the data has appropriate type
  */
  virtual OdTvInsertDataPtr getAsInsert(OdTvResult* rc = NULL) const;

  /** \details
  Returns the smart ptr to the 'OdTvRcsPointCloudData' object if the data has appropriate type
  */
  virtual OdTvRcsPointCloudDataPtr getAsRcsPointCloud(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
};

/** \details
This is an implementation of the iterator class for the geometry data
*/
class ODTV_EXPORT OdTvGeometryDataIteratorImpl : public OdTvGeometryDataIterator
{
public:
  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the geometry data currently referenced by this Iterator object.
  */
  virtual OdTvGeometryDataId getGeometryData(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified geometry data.
  \param objectId [in]  Geometry Data ID.
  */
  virtual OdTvResult seek(const OdTvGeometryDataId& geometryDataId);

  /** \details
  Methods for creating the object
  */
  static OdTvGeometryDataIteratorPtr createObject(OdTvGeometryDataId geomDataId);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvGeometryDataIteratorImpl();
  OdTvGeometryDataIteratorImpl(const OdTvGeometryDataId& geomDataId);

  virtual ~OdTvGeometryDataIteratorImpl();

  OdTvGeometryDataId   m_geomDataId;

  // reference counter
  unsigned int          m_nRefCounter;

};

/** \details
    Declares the define for getting the interface for the typified geometry
*/
#define ODTV_DEFINE_GET_TYPIFIED_GEOMETRY_INTERFACE(pRet, GeometryName)                                    \
  OdTvGeometryDataImpl* pData = OdTvSmartPtrAccess<OdTvGeometryDataImpl>::get(&m_pObjectImpl);             \
  if ( pData->entityGeometryDataType() != OdTvGeometryDataImpl::GeometryName )                             \
  {                                                                                                         \
    if ( rc )                                                                                               \
      *rc = tvGeometryDataHasAnotherType;                                                                  \
    return pRet;                                                                                            \
  }                                                                                                         \
  OdTv##GeometryName##DataImpl* pTypifiedImpl = static_cast<OdTv##GeometryName##DataImpl*>(pData);        \
  if ( pTypifiedImpl == NULL )                                                                              \
  {                                                                                                         \
    if ( rc )                                                                                               \
      *rc = tvGeometryDataHasAnotherType;                                                                  \
    return pRet;                                                                                            \
  }                                                                                                         \
  OdTvFactoryImplPtr factoryImplPtr = odTvGetFactoryImpl();                                               \
  if ( !factoryImplPtr.isNull() )                                                                           \
  {                                                                                                         \
    OdTvInterfaceWrappersPool* pWrappersPool = factoryImplPtr->getWrappersPool();                          \
    if ( rc )                                                                                               \
      *rc = tvOk;                                                                                          \
    return pWrappersPool->get##GeometryName##DataInterface(pTypifiedImpl, m_pParentEntity->objectId());           \
  }                                                                                                         \
  else if ( rc )                                                                                            \
  {                                                                                                         \
    *rc = tvFactoryDoesntExist;                                                                            \
    return pRet;                                                                                            \
  }


/** \details
    Declares the define for getting the interface for the typified geometry
*/
#define ODTV_DEFINE_GET_TYPIFIED_GEOMETRY_INTERFACE_FROMID(GeometryName)                                                           \
  OdTv##GeometryName##DataPtr pRet;                                                                                                \
  OdDbStub* pStub = NULL;                                                                                                          \
  if ( m_pMiscIdData )                                                                                                             \
    pStub = static_cast<OdDbStub*>(m_pMiscIdData);                                                                                 \
  if (m_pLink)                                                                                                                     \
  {                                                                                                                                \
    OdTvDataLink* pLinkThis = static_cast<OdTvDataLink*>(m_pLink);                                                                 \
    if (pLinkThis)                                                                                                                 \
    {                                                                                                                              \
      if ( pLinkThis->isDataValid() )                                                                                              \
      {                                                                                                                            \
        OdTvGeometryDataImpl* pData = static_cast<OdTvGeometryDataImpl*>(pLinkThis->getData());                                    \
        if ( pData )                                                                                                               \
        {                                                                                                                          \
          if ( pData->entityGeometryDataType() == OdTvGeometryDataImpl::GeometryName )                                             \
          {                                                                                                                        \
            OdTv##GeometryName##DataImpl* pTypifiedImpl = static_cast<OdTv##GeometryName##DataImpl*>(pData);                       \
            if ( pTypifiedImpl )                                                                                                   \
            {                                                                                                                      \
              OdTvFactoryImplPtr factoryImplPtr = odTvGetFactoryImpl();                                                            \
              if ( !factoryImplPtr.isNull() )                                                                                      \
              {                                                                                                                    \
                OdTvInterfaceWrappersPool* pWrappersPool = factoryImplPtr->getWrappersPool();                                      \
                if ( rc )                                                                                                          \
                  *rc = tvOk;                                                                                                      \
                return pWrappersPool->get##GeometryName##DataInterface(pTypifiedImpl, pStub != NULL ? OdTvDbObjectId(pStub) : OdTvDbObjectId());    \
              }                                                                                                                    \
              else if ( rc )                                                                                                       \
                *rc = tvFactoryDoesntExist;                                                                                        \
            }                                                                                                                      \
            else if ( rc )                                                                                                         \
              *rc = tvGeometryDataHasAnotherType;                                                                                  \
          }                                                                                                                        \
          else if ( rc )                                                                                                           \
            *rc = tvGeometryDataHasAnotherType;                                                                                    \
        }                                                                                                                          \
        else if ( rc )                                                                                                             \
          *rc = tvIdWrongDataType;                                                                                                 \
      }                                                                                                                            \
      else if ( rc )                                                                                                               \
        *rc = tvGeometryDataDoesntExistOrBeenDeleted;                                                                              \
    }                                                                                                                              \
    else if ( rc )                                                                                                                 \
      *rc = tvIdHasNoData;                                                                                                         \
  }                                                                                                                                \
  else if ( rc )                                                                                                                   \
    *rc = tvIdHasNoData;                                                                                                           \
  return pRet;

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYGEOMETRYDATA_H_INCLUDED_

