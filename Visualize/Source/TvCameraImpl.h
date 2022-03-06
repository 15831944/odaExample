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

#ifndef _ODTV_CAMERAIMPL_H_INCLUDED_
#define _ODTV_CAMERAIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvCamera.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

#include "TvEntity.h"

#include "OdDbStub.h"
#include "DbEntity.h"

#define STL_USING_SET
#include "OdaSTL.h"

#include "TvGsViewImpl.h"
#include "TvGeometryDataImpl.h"

class OdTvCameraGeometryImpl : public OdTvGeometryDataImpl
{
protected:
  bool m_bIsPosition;
public:
  OdTvCameraGeometryImpl( bool bIsPosition );

  virtual ~OdTvCameraGeometryImpl() {}

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return DummyLast; }
  virtual bool                             draw( OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker ) const { return false; }
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kNone; }
  virtual bool                             hasThickness() const { return false; }
  virtual void                             read( OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion() );
  virtual void                             write( OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion() ) const;
  virtual bool                             copyTo( OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity ) const;

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const { return 0; }
};

/** \details
This class is the internal implementation of the camera
*/
class OdTvCameraImpl : public OdTvDbEntity, public OdTvXDataStorage
{
protected:
  OdTvCameraImpl();
public:
  ODRX_DECLARE_MEMBERS( OdTvCameraImpl );

  virtual ~OdTvCameraImpl();

  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  OdTvResult copyTo(OdTvEntityId& targetCameraId, bool bFromInterface = true) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize( OdTvResult* rc = NULL ) const;

  void setName( const OdString& name ){ m_name = name; }
  OdString getName() const { return m_name; }

  virtual OdTvResult setupCamera( const OdTvPoint& position, const OdTvVector& direction, const OdTvVector& upVector );

  OdTvPoint position() const;
  OdTvResult setPosition( const OdTvPoint& p );
  OdTvVector direction() const;
  OdTvVector upVector() const;
  OdTvPoint target() const;
  OdTvResult setTarget( const OdTvPoint& t );
  OdTvResult setUpVector( const OdTvVector& upVector );

  void setViewParameters( double fWidth, double fHeight, bool bPrespective );
  double fieldWidth() const { return m_fWidth; }
  double fieldHeight() const { return m_fHeight; }
  bool isPerspective() const { return m_bIsPerspective; }

  virtual OdTvResult setGlyphSize( OdUInt32 );
  virtual OdTvResult setDisplayGlyph( bool );
  virtual OdTvResult setDisplayTarget( bool );

  void setNearClip( bool bClip, double dNear = 1.0 );
  void setFarClip( bool bClip, double dFar = 0.0 );

  bool isNearClippingEnabled() const { return GETBIT( m_flags, kClipNear ); }
  double nearClippingDistance() const { return m_dNear; }
  bool isFarClippingEnabled() const { return GETBIT( m_flags, kClipFar ); }
  double farClippingDistance() const { return m_dFar; }

  virtual bool displayGlyph() const { return GETBIT( m_flags, kDisplayGlyph ); }
  virtual bool displayTarget() const { return GETBIT( m_flags, kDisplayTarget ); }
  virtual OdUInt32 glyphSize() const { return m_glyphSize; }

  virtual OdTvResult assignView( const OdTvGsViewId& view );
  virtual bool hasAssignedViews() const;
  virtual bool isViewAssigned( const OdTvGsViewId& view ) const;
  virtual OdTvResult unassignView( const OdTvGsViewId& view );

  void transferParamsToView( OdTvGsViewImplPtr pView );
  void syncAssignedViews();

  OdTvGeometryDataId positionId() const { return m_positionId; }
  OdTvGeometryDataId targetId() const { return m_targetId; }
  OdTvGeometryDataId upId() const { return m_upId; }
  OdTvGeometryDataId fieldsId() const { return m_fieldsId; }

  bool isAutoAdjust() const { return m_bAutoAdjust; }
  void setAutoAdjust( bool bAdjust ) { m_bAutoAdjust = bAdjust; }

  bool isAdjustLensLength() const { return !GETBIT( m_flags, kDisableLensSync ); }
  void setAdjustLensLength( bool bAdjust ) { SETBIT( m_flags, kDisableLensSync, !bAdjust ); }

  OdTvResult setupCameraFromView( const OdTvGsViewId& viewId );

  double lensLength() const;
  void setLensLength( double l );

  double focalLength( OdTvResult* rc = NULL ) const;

  double perspectiveVerticalViewAngle( OdTvResult* rc = NULL ) const;
  double perspectiveHorizontalViewAngle( OdTvResult* rc = NULL ) const;

protected:
  OdString m_name;
  OdTvPoint m_position;
  OdTvVector m_direction;
  OdTvVector m_upVector;
  double m_fWidth;
  double m_fHeight;
  bool m_bIsPerspective;
  double m_dNear;
  double m_dFar;
  OdUInt32 m_glyphSize;
  OdUInt8 m_flags;
  enum CameraFlag
  {
    kDisplayGlyph = 1,
    kDisplayTarget = 1 << 1,
    kClipNear = 1 << 2,
    kClipFar = 1 << 3,
    kDisableLensSync = 1 << 4
  };

  std::set< OdTvGsViewId > m_assignedViews;

  OdTvGeometryDataId m_positionId;
  OdTvCameraGeometryImpl* pPositionId;
  OdTvGeometryDataId m_targetId;
  OdTvCameraGeometryImpl* pTargetId;
  OdTvGeometryDataId m_upId;
  OdTvCameraGeometryImpl* pUpId;
  OdTvGeometryDataId m_fieldsId;
  OdTvCameraGeometryImpl* pFieldsId;

  bool m_bAutoAdjust;

  double m_lensLength;
};

typedef OdSmartPtr<OdTvCameraImpl> OdTvCameraImplPtr;

/** \details
This is an wrapper of the interface class for OdTvCamera object.

\remarks
The purpose of this class is to connect the internal light object with an interface object
*/
class OdTvCameraWrapper : public OdTvCamera
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL( OdTvCamera, OdTvCameraImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
    Sets the name for the light.

    \param sName [in]  Layer name as a String value up to 255 characters long.

    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvResult setName( OdString sName );

  /** \details
    Returns the name of the light.
  */
  virtual OdString getName( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setupCamera( const OdTvPoint& position, const OdTvVector& direction, const OdTvVector& upVector );
  virtual OdTvResult setupCamera( const OdTvPoint& position, const OdTvPoint& target, const OdTvVector& upVector );

  virtual OdTvPoint position( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setPosition( const OdTvPoint& p );
  virtual OdTvVector direction( OdTvResult* rc = NULL ) const;
  virtual OdTvVector upVector( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setUpVector( const OdTvVector& upVector );
  virtual OdTvPoint target( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setTarget( const OdTvPoint& t );

  virtual OdTvResult setViewParameters( double fWidth, double fHeight, bool bPrespective );
  virtual double fieldWidth( OdTvResult* rc = NULL ) const;
  virtual double fieldHeight( OdTvResult* rc = NULL ) const;
  virtual bool isPerspective( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setNearClip( bool bClip, double dNear = 1.0 );
  virtual OdTvResult setFarClip( bool bClip, double dFar = 0.0 );

  virtual bool isNearClippingEnabled( OdTvResult* rc = NULL ) const;
  virtual double nearClippingDistance( OdTvResult* rc = NULL ) const;
  virtual bool isFarClippingEnabled( OdTvResult* rc = NULL ) const;
  virtual double farClippingDistance( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setGlyphSize( OdUInt32 );
  virtual OdTvResult setDisplayGlyph( bool );
  virtual OdTvResult setDisplayTarget( bool );

  virtual bool displayGlyph( OdTvResult* rc = NULL ) const;
  virtual bool displayTarget( OdTvResult* rc = NULL ) const;
  virtual OdUInt32 glyphSize( OdTvResult* rc = NULL ) const;

  virtual OdTvResult assignView( const OdTvGsViewId& view );
  virtual bool hasAssignedViews( OdTvResult* rc = NULL ) const;
  virtual bool isViewAssigned( const OdTvGsViewId& view, OdTvResult* rc = NULL ) const;
  virtual OdTvResult unassignView( const OdTvGsViewId& view );

  virtual OdTvGeometryDataId positionId( OdTvResult* rc = NULL ) const;
  virtual OdTvGeometryDataId targetId( OdTvResult* rc = NULL ) const;
  virtual OdTvGeometryDataId upId( OdTvResult* rc = NULL ) const;
  virtual OdTvGeometryDataId fieldsId( OdTvResult* rc = NULL ) const;

  virtual bool isAutoAdjust( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setAutoAdjust( bool bAdjust );

  virtual bool isAdjustLensLength( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setAdjustLensLength( bool bAdjust );

  virtual OdTvResult setupCameraFromView( const OdTvGsViewId& viewId );

  virtual double lensLength( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setLensLength( double l );

  virtual double focalLength( OdTvResult* rc = NULL ) const;

  virtual double perspectiveVerticalViewAngle( OdTvResult* rc = NULL ) const;
  virtual double perspectiveHorizontalViewAngle( OdTvResult* rc = NULL ) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};


#endif //_ODTV_CAMERAIMPL_H_INCLUDED_
