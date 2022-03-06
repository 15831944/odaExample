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
#ifndef __DG_CELLHEADER_H__
#define __DG_CELLHEADER_H__

#include "TD_PackPush.h"

#include "DgGraphicsElement.h"
#include "DgElementIterator.h"
#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeExtents3d.h"
#include "DgModel.h"
#include "Gi/GiClipBoundary.h"

class OdBinaryData;

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgCellHeader2d : public OdDgGraphicsElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL( OdDgCellHeader2d );

  virtual void setHbitFlag(bool flag);

  virtual OdString getName() const;
  virtual void setName(const OdString& name);

  virtual OdGePoint2d getOrigin() const;
  virtual void setOrigin( const OdGePoint2d& origin );

  //it is used to rotate its ranges only (the border shown by Microstation)
  virtual OdGeMatrix2d getTransformation() const;
  virtual void setTransformation( const OdGeMatrix2d& rotation );

  virtual bool isPolygonWithHoles() const;

  //support for its complexity
  virtual void add( OdDgElementPtr pElement );
  virtual OdDgElementIteratorPtr createIterator( bool atBeginning = true, bool skipDeleted = true ) const;

  // OdGiDrawable overridden
  bool subWorldDraw(OdGiWorldDraw* pWd) const;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pDrwTraits) const;
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  OdResult subGetGeomExtents(const OdDgElementId& idView, OdGeExtents3d& extents ) const;
  virtual void subSetDatabaseDefaults( OdDgDatabase* pDb, bool doSubents);

  virtual void subHighlight(bool bDoIt = true, const OdDgFullSubentPath* pSubId = 0, bool highlightAll = false) const;

  virtual OdRxObjectPtr clone() const;

  /** \details
  Sets the erased mode of this object.

  \param eraseIt [in]  Boolean to specify if object is to be erased or unerased.

  \remarks
  Erased objects are not deleted from the database or from memory.

  Erased objects are not filed when the database is saved or sent to a DGN file.
*/
  virtual OdResult erase(
    bool eraseIt = true);

  virtual OdResult subExplode( OdRxObjectPtrArray& entitySet ) const;

  virtual bool loadFromLibrary( const OdDgModelPtr& pLibraryCell, OdDg::DuplicateRecordCloning uDuplicateRecordCloning = OdDg::kDrcIgnore);

	virtual bool changeDrawingOrderOfElements(OdDgElementIdArray& arrRelatedElements, OdDgElementIdArray& arrRelatingElements, const OdDg::OdDgChangeDrawingOrderMode& uMode);

  virtual void setGeometryModified(bool bSet);
};

typedef OdSmartPtr<OdDgCellHeader2d> OdDgCellHeader2dPtr;

class OdDgCellHeader3d;
typedef OdSmartPtr<OdDgCellHeader3d> OdDgCellHeader3dPtr;

/** \details
   
    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgCellHeader3d : public OdDgGraphicsElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL( OdDgCellHeader3d );

  virtual void setHbitFlag(bool flag);

  virtual OdString getName() const;
  virtual void setName(const OdString& name);

  virtual OdGePoint3d getOrigin() const;
  virtual void setOrigin( const OdGePoint3d& origin );

  //it is used to rotate its ranges only (the border shown by Microstation)
  virtual OdGeMatrix3d getTransformation() const;
  virtual void setTransformation( const OdGeMatrix3d& rotation );

  virtual bool isPolygonWithHoles() const;

  //support for its complexity
  virtual void add( OdDgElementPtr pElement );
  virtual OdDgElementIteratorPtr createIterator( bool atBeginning = true, bool skipDeleted = true ) const;

  virtual OdRxObjectPtr clone() const;

  virtual OdResult explodeGeometry( OdRxObjectPtrArray& entitySet ) const;

  /** \details
  Sets the erased mode of this object.

  \param eraseIt [in]  Boolean to specify if object is to be erased or unerased.

  \remarks
  Erased objects are not deleted from the database or from memory.

  Erased objects are not filed when the database is saved or sent to a DGN file.
*/
  virtual OdResult erase(
    bool eraseIt = true);

  // OdGiDrawable overridden
  bool subWorldDraw(OdGiWorldDraw* pWd) const;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pDrwTraits) const;
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  OdResult subGetGeomExtents(const OdDgElementId& idView, OdGeExtents3d& extents) const;
  virtual void subSetDatabaseDefaults(OdDgDatabase* pDb, bool doSubents);

  virtual OdResult subExplode(OdRxObjectPtrArray& entitySet) const;

  virtual void subHighlight(bool bDoIt = true, const OdDgFullSubentPath* pSubId = 0, bool highlightAll = false) const;

	virtual bool loadFromLibrary(const OdDgModelPtr& pLibraryCell, OdDg::DuplicateRecordCloning uDuplicateRecordCloning = OdDg::kDrcIgnore);// Drawing order settings

	virtual bool changeDrawingOrderOfElements(OdDgElementIdArray& arrRelatedElements, OdDgElementIdArray& arrRelatingElements, const OdDg::OdDgChangeDrawingOrderMode& uMode);

  virtual void setGeometryModified(bool bSet);
};

class OdDgAnnotationCellHeader2d;
typedef OdSmartPtr<OdDgAnnotationCellHeader2d> OdDgAnnotationCellHeader2dPtr;

/** \details
   
    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgAnnotationCellHeader2d : public OdDgCellHeader2d
{
  ODDG_DECLARE_MEMBERS_INTERNAL( OdDgAnnotationCellHeader2d );
   
  virtual bool getUseAnnotationScaleFlag() const;
  virtual void setUseAnnotationScaleFlag( bool bSet );
   
  virtual double getAnnotationScale() const;
  virtual void   setAnnotationScale( double dAnnotationScale );

  bool subWorldDraw(OdGiWorldDraw* pWd) const;
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  OdResult subGetGeomExtents(const OdDgElementId& idView, OdGeExtents3d& extents) const;
};

class OdDgAnnotationCellHeader3d;
typedef OdSmartPtr<OdDgAnnotationCellHeader3d> OdDgAnnotationCellHeader3dPtr;

/** \details
   
    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgAnnotationCellHeader3d : public OdDgCellHeader3d
{
  ODDG_DECLARE_MEMBERS_INTERNAL( OdDgAnnotationCellHeader3d );

  virtual bool getUseAnnotationScaleFlag() const;
  virtual void setUseAnnotationScaleFlag( bool bSet );

  virtual double getAnnotationScale() const;
  virtual void   setAnnotationScale( double dAnnotationScale );

  bool subWorldDraw(OdGiWorldDraw* pWd) const;
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  OdResult subGetGeomExtents(const OdDgElementId& idView, OdGeExtents3d& extents) const;
};

//=======================================================================================================
//                                         OdDgAssocRegion classes
//=======================================================================================================

/** \details
  This class declares the methods for managing all types of association regions.

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
namespace OdDgAssocRegion
{
  enum OdDgAssocRegionType
  {
    kFromElements = 0,
    kHatchFill    = 1,
    kUnion        = 2,
    kIntersect    = 3,
    kDifference   = 4
  };

  enum OdDgAssocRegionFillModeInteriorShapes
  {
    kIgnore = 0,
    kLocate = 1,
    kIdentifyAlternating = 2
  };
};

class OdDgAssocRegion2d;
typedef OdSmartPtr<OdDgAssocRegion2d> OdDgAssocRegion2dPtr;

/** \details
   
    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgAssocRegion2d : public OdDgCellHeader2d
{
  ODDG_DECLARE_MEMBERS_INTERNAL( OdDgAssocRegion2d );

  virtual void setName(const OdString& name);

  virtual OdDgAssocRegion::OdDgAssocRegionType getRegionType() const;
  virtual void setRegionType( const OdDgAssocRegion::OdDgAssocRegionType& uType );

  virtual OdDgAssocRegion::OdDgAssocRegionFillModeInteriorShapes getFillModeInteriorShapes() const;
  virtual void setFillModeInteriorShapes( const OdDgAssocRegion::OdDgAssocRegionFillModeInteriorShapes& uType );

  virtual bool getLocateInteriorTextsFlag() const;
  virtual void setLocateInteriorTextsFlag( bool bSet );

  virtual double getFillModeMaxGap() const;
  virtual void setFillModeMaxGap( double dGap );

  virtual OdGePoint2dArray getSeedPoints() const;
  virtual void             setSeedPoints( const OdGePoint2dArray& arrSeedPts );

  virtual OdDgElementIdArray getDependedElements() const;
  virtual void               setDependedElements( const OdDgElementIdArray& arrDependedElements );

  virtual double getTextMargins() const;
  virtual void   setTextMargins( double dMargins );

  virtual bool   recalculate();

  bool     subWorldDraw(OdGiWorldDraw* pWd) const;
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  OdResult subGetGeomExtents(const OdDgElementId& idView, OdGeExtents3d& extents) const;
  virtual OdResult subExplode(OdRxObjectPtrArray& entitySet) const;
  virtual OdRxObjectPtr clone() const;
};

class OdDgAssocRegion3d;
typedef OdSmartPtr<OdDgAssocRegion3d> OdDgAssocRegion3dPtr;

/** \details
   
    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgAssocRegion3d : public OdDgCellHeader3d
{
  ODDG_DECLARE_MEMBERS_INTERNAL( OdDgAssocRegion3d );

  virtual void setName(const OdString& name);

  virtual OdDgAssocRegion::OdDgAssocRegionType getRegionType() const;
  virtual void setRegionType( const OdDgAssocRegion::OdDgAssocRegionType& uType );

  virtual OdDgAssocRegion::OdDgAssocRegionFillModeInteriorShapes getFillModeInteriorShapes() const;
  virtual void setFillModeInteriorShapes( const OdDgAssocRegion::OdDgAssocRegionFillModeInteriorShapes& uType );

  virtual bool getLocateInteriorTextsFlag() const;
  virtual void setLocateInteriorTextsFlag( bool bSet );

  virtual double getFillModeMaxGap() const;
  virtual void setFillModeMaxGap( double dGap );

  virtual OdGePoint3dArray getSeedPoints() const;
  virtual void             setSeedPoints( const OdGePoint3dArray& arrSeedPts );

  virtual OdDgElementIdArray getDependedElements() const;
  virtual void               setDependedElements( const OdDgElementIdArray& arrDependedElements );

  virtual double getTextMargins() const;
  virtual void   setTextMargins( double dMargins );

  virtual bool   recalculate();

  bool     subWorldDraw(OdGiWorldDraw* pWd) const;
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  OdResult subGetGeomExtents(const OdDgElementId& idView, OdGeExtents3d& extents) const;
  virtual OdResult subExplode(OdRxObjectPtrArray& entitySet) const;
  virtual OdRxObjectPtr clone() const;
};

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgAssocRegionRecalculatePE : public OdRxObject
{
  ODRX_DECLARE_MEMBERS(OdDgAssocRegionRecalculatePE);
  long        m_references;     //used by each object separately
public:

  OdDgAssocRegionRecalculatePE();
  ~OdDgAssocRegionRecalculatePE();

  //OdRxObject overridden
  virtual void addRef();
  virtual void release();
  virtual long numRefs() const;

  virtual bool recalculateElementBasedRegion( OdDgGraphicsElement* pAssocRgn, const OdDgElementIdArray& arrDependedElements );
  virtual bool recalculateHatchFillRegion( OdDgGraphicsElement* pAssocRgn, const OdDgElementIdArray& arrDependedElements, const OdGePoint3dArray& arrSeedPts );
  virtual bool recalculateUnionRegion( OdDgGraphicsElement* pAssocRgn, const OdDgElementIdArray& arrDependedElements );
  virtual bool recalculateIntersectRegion( OdDgGraphicsElement* pAssocRgn, const OdDgElementIdArray& arrDependedElements );
  virtual bool recalculateDifferenceRegion( OdDgGraphicsElement* pAssocRgn, const OdDgElementId& idBlank, const OdDgElementId& idTool );
};

typedef OdSmartPtr<OdDgAssocRegionRecalculatePE> OdDgAssocRegionRecalculatePEPtr;

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgCellBoundaryClipPE : public OdRxObject
{
  ODRX_DECLARE_MEMBERS(OdDgCellBoundaryClipPE);
  long        m_references;     //used by each object separately
public:

  OdDgCellBoundaryClipPE();
  ~OdDgCellBoundaryClipPE();

  //OdRxObject overridden
  virtual void addRef();
  virtual void release();
  virtual long numRefs() const;

  // Access to cell header boundary clip tools

  virtual bool getBoundaryClip( const OdDgElementPtr& pCell, OdGiClipBoundary& clipBoundary );
};

typedef OdSmartPtr<OdDgCellBoundaryClipPE> OdDgCellBoundaryClipPEPtr;

#include "TD_PackPop.h"

#endif // __DG_CELLHEADER_H__
