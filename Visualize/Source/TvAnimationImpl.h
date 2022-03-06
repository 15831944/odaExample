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

#ifndef _ODTV_ANIMATIONIMPL_H_INCLUDED_
#define _ODTV_ANIMATIONIMPL_H_INCLUDED_

#include "TvAnimation.h"
#define STL_USING_SET
#define STL_USING_MAP
#include "OdaSTL.h"
#include <set>
#include <map>

class OdTvAnimationActionImpl : public OdTvDbObject, public OdTvXDataStorage
{
public:
  struct Frame
  {
    Frame();
    ~Frame();
    std::map< OdInt16, double > m_values;
    bool m_isKey;
    OdTvAnimationAction::Interpolator m_interpolator;

    bool translation( OdTvVector& ) const;
    bool rotation( OdTvVector& ) const;
    bool scale( OdTvVector& ) const;
  };

  typedef std::map< OdUInt32, Frame > OdTvFrames;
  typedef std::map< OdInt16, double > OdTvKeyValues;
protected:
  OdUInt32 m_nNumFrames;
  OdUInt32 m_nFps;
  mutable OdUInt32 m_nActiveFrame;
  mutable std::map< OdUInt32, Frame > m_frames;
  mutable bool m_bHasCache;

  bool m_bNeedSave;

  OdTvAnimationActionImpl();

  Frame* getFrame( OdUInt32 nFrame );
  const Frame* getFrame( OdUInt32 nFrame ) const;
  void calculateFrame( OdUInt32 nFrame ) const;
  bool interpolateValue( const Frame& f1, const Frame& f2, OdUInt32 n1, OdUInt32 n2, OdUInt32 nFrame, OdTvAnimationAction::Interpolator ipl, OdTvAnimationAction::Keydata kd, double& value ) const;
  bool splineInterpolation( OdUInt32 n1, double val1, OdUInt32 n2, double val2, OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double& value ) const;

  bool prevKeypoint( OdUInt32 nFrame, OdUInt32& res, OdTvAnimationAction::Keydata* data = NULL, double* pVal = NULL ) const;
  bool nextKeypoint( OdUInt32 nFrame, OdUInt32& res, OdTvAnimationAction::Keydata* data = NULL, double* pVal = NULL ) const;
public:
  ODRX_DECLARE_MEMBERS( OdTvAnimationActionImpl );
  virtual ~OdTvAnimationActionImpl();

  virtual OdUInt32 numFrames( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setNumFrames( OdUInt32 nFrames, bool bRescaleRange = false );

  virtual OdUInt32 FPS( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setFPS( OdUInt32 );

  virtual OdUInt32 activeFrame( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setActiveFrame( OdUInt32 nFrame ) const;

  OdTvMatrix activeFrameMatrix( const OdTvAnimationContainer::OdTvActorBasis& basis = OdTvAnimationContainer::OdTvActorBasis(), bool bSkipScale = false ) const;

  OdTvVector activeFrameScale() const;

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields( OdTvDbDwgFiler* pFiler );

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields( OdTvDbDwgFiler* pFiler ) const;


  virtual OdTvResult setName( const OdString& sName );
  virtual OdString getName() const;

  virtual OdTvResult setKeypoint( OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double keyval, OdTvAnimationAction::Interpolator ipl = OdTvAnimationAction::kCubic );
  virtual bool hasKeypoint( OdUInt32 nFrame, OdTvResult* rc = NULL ) const;
  virtual bool keypointHasData( OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double* pValue = NULL, OdTvResult* rc = NULL ) const;
  virtual OdTvResult removeKeypoint( OdUInt32 nFrame );
  virtual OdTvResult removeKeypoints();

  OdTvAnimationAction::OdTvAnimationKeypointIteratorPtr getKeypointsIterator( OdTvResult* rc = NULL ) const;

  OdUInt32 numKeypoints() const;
  void removeNonKeyFrames( OdUInt32* nMaxFrame = NULL ) const;
  void scaleKeypoints( double scale );

  virtual bool frameData( OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double* pValue, OdTvResult* rc = NULL ) const;

  virtual bool getNeedSaveInFile( OdTvResult* rc = NULL ) const;
  void setNeedSaveInFile( bool bNeedSave );
};

typedef OdSmartPtr<OdTvAnimationActionImpl> OdTvAnimationActionImplPtr;

class OdTvAnimationActionWrapper : public OdTvAnimationAction
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL( OdTvAnimationAction, OdTvAnimationActionImpl )

    friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  virtual OdUInt32 numFrames( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setNumFrames( OdUInt32 nFrames, bool bRescaleRange = false );

  virtual OdUInt32 FPS( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setFPS( OdUInt32 );

  virtual OdUInt32 activeFrame( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setActiveFrame( OdUInt32 nFrame ) const;

  virtual OdTvResult setName( const OdString& sName );
  virtual OdString getName( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setKeypoint( OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double keyval, OdTvAnimationAction::Interpolator ipl = OdTvAnimationAction::kCubic );
  virtual bool hasKeypoint( OdUInt32 nFrame, OdTvResult* rc = NULL ) const;
  virtual bool keypointHasData( OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double* pValue = NULL, OdTvResult* rc = NULL ) const;
  virtual OdTvResult removeKeypoint( OdUInt32 nFrame );
  virtual OdTvResult removeKeypoints();

  virtual OdTvAnimationAction::OdTvAnimationKeypointIteratorPtr getKeypointsIterator( OdTvResult* rc = NULL ) const;

  virtual bool frameData( OdUInt32 nFrame, OdTvAnimationAction::Keydata kd, double* pValue, OdTvResult* rc = NULL ) const;

  virtual bool getNeedSaveInFile( OdTvResult* rc = NULL ) const;

  ODTV_DEFINE_XDATA_DECL( virtual );
  ODTV_DEFINE_HANDLED_OBJECT_DECL( virtual );
};

class OdTvAnimationKeypointIteratorImpl : public OdTvAnimationAction::OdTvAnimationKeypointIterator
{
  OdTvAnimationKeypointIteratorImpl();
  OdTvAnimationKeypointIteratorImpl( OdTvAnimationActionImpl::OdTvFrames* pFrames );
  // reference counter
  unsigned int                m_nRefCounter;

  OdTvAnimationActionImpl::OdTvFrames* m_pFrames;
  OdTvAnimationActionImpl::OdTvFrames::const_iterator m_iterator;
public:
  virtual ~OdTvAnimationKeypointIteratorImpl();
  virtual OdUInt32 frame( OdTvResult* rc = NULL ) const;
  virtual bool hasData( OdTvAnimationAction::Keydata kd, double* pValue = NULL, OdTvResult* rc = NULL ) const;
  static OdTvAnimationAction::OdTvAnimationKeypointIteratorPtr createObject( OdTvAnimationActionImpl::OdTvFrames* pFrames );

  virtual bool done( OdTvResult* rc = NULL ) const;
  virtual OdTvResult step();

  ODTV_WRAPPERS_REFERENCE_MEMBERS()
};

/** \details
This is an implementation of the iterator class for the animation actions
*/
class OdTvAnimationActionsIteratorImpl : public OdTvAnimationActionsIterator
{
  friend class OdTvDatabaseImpl;
public:

  virtual ~OdTvAnimationActionsIteratorImpl();

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done( OdTvResult* rc = NULL ) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();
  virtual OdTvAnimationActionId getAnimationAction( OdTvResult* rc = NULL ) const;

  virtual OdTvResult seek( const OdTvAnimationActionId& actionId );
  static OdTvAnimationActionsIteratorPtr createObject( OdTvDbDictionaryIterator* pDbIterator );

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvAnimationActionsIteratorImpl();
  OdTvAnimationActionsIteratorImpl( OdTvDbDictionaryIterator* pDbIterator );

  // Db iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};

class OdTvAnimationItem
{
protected:
  OdTvAnimationActionId m_action;
  OdTvSubItemPath m_path;
  OdInt32 m_nRepeats;
  OdUInt32 m_nTimeStart;
  //cached data
  OdTvMatrix m_originalMatrix;
  double m_originalFW;
  double m_originalFH;
  OdTvAnimationContainer::OdTvActorBasis m_basis;
  OdTvEntityId::EntityTypes m_type;
  bool m_bCustomBasis;

  OdUInt32 timeToFrame( OdUInt32 msec ) const;
  void writeTvPath( OdTvDbDwgFiler* pFiler, const OdTvSubItemPath& path ) const;
  void readTvPath( OdTvDbDwgFiler* pFiler, OdTvSubItemPath& path );

  bool init( OdTvAnimationContainer::OdTvActorBasis* pBasis = NULL );
  bool initAsEntity( OdTvAnimationContainer::OdTvActorBasis* pBasis = NULL );
  bool initAsCamera( OdTvAnimationContainer::OdTvActorBasis* pBasis = NULL );
  bool initAsInsert( OdTvAnimationContainer::OdTvActorBasis* pBasis = NULL );

  bool isCustomBasis() const { return m_bCustomBasis; }
public:

  OdTvAnimationItem( const OdTvAnimationActionId& action, const OdTvSubItemPath&, OdInt32, OdUInt32, OdTvAnimationContainer::OdTvActorBasis* );
  OdTvAnimationItem();
  ~OdTvAnimationItem();

  OdTvAnimationActionId action() const { return m_action; }
  const OdTvSubItemPath& actor() const { return m_path; }
  OdInt32 repeats() const { return m_nRepeats; }
  OdUInt32 timeStart() const { return m_nTimeStart; }
  bool totalTime( OdUInt32& msec ) const;
  const OdTvAnimationContainer::OdTvActorBasis& basis() const { return m_basis; }

  void applyAction( OdUInt32 msec );
  void resetAction();

  void write( OdTvDbDwgFiler* pFiler ) const;
  void read( OdTvDbDwgFiler* pFiler );

  void validate();
};

class OdTvAnimationIteratorImpl : public OdTvAnimationIterator
{
  const OdVector< OdTvAnimationItem* >* m_pItems;
  OdUInt32 m_nCurrent;
  // reference counter
  unsigned int          m_nRefCounter;
  static OdTvSubItemPath m_emptyPath;
  static OdTvAnimationContainer::OdTvActorBasis m_emptyBasis;
public:
  OdTvAnimationIteratorImpl( const OdVector< OdTvAnimationItem* >* );
  ~OdTvAnimationIteratorImpl();

  virtual bool done( OdTvResult* rc = NULL ) const;
  virtual OdTvResult step();

  virtual OdUInt32 timeStart( OdTvResult* rc = NULL ) const;
  virtual OdTvAnimationActionId action( OdTvResult* rc = NULL ) const;
  virtual const OdTvSubItemPath& actor( OdTvResult* rc = NULL ) const;
  virtual OdInt32 repeats( OdTvResult* rc = NULL ) const;
  virtual const OdTvAnimationContainer::OdTvActorBasis& basis( OdTvResult* rc = NULL ) const;

  static OdTvAnimationIteratorPtr createObject( const OdVector< OdTvAnimationItem* >* pItems );

  inline const OdTvAnimationItem* current() const { return m_pItems->operator[]( m_nCurrent ); }
  inline OdUInt32 currentIndex() const { return m_nCurrent; }

  ODTV_WRAPPERS_REFERENCE_MEMBERS()
};

class OdTvAnimationContainerImpl : public OdTvDbObject, public OdTvXDataStorage
{
protected:
  OdVector< OdTvAnimationItem* > m_items;
  OdUInt32 m_nCurrentTime;
  bool m_bNeedSave;

  OdUInt32 recDelete( const OdTvSubItemPath& path );

  OdTvAnimationContainerImpl();
public:
  ODRX_DECLARE_MEMBERS( OdTvAnimationContainerImpl );
  
  virtual ~OdTvAnimationContainerImpl();
  virtual OdTvResult addAnimation( const OdTvSubItemPath& actor, const OdTvAnimationActionId& actionId, OdInt32 nRepeats = 0, OdUInt32 timeStart = 0, OdTvAnimationContainer::OdTvActorBasis* pCustomBasis = NULL );
  virtual OdTvResult removeAnimation( const OdTvAnimationIteratorPtr& pIterator );
  virtual OdTvResult removeAnimations( const OdTvSubItemPath& path );
  virtual OdTvResult removeAnimations();
  virtual OdTvResult validateAnimations();

  virtual OdTvAnimationIteratorPtr getAnimationIterator( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setCurrentTime( OdUInt32 msec );
  virtual OdUInt32 currentTime( OdTvResult* rc = NULL ) const;
  virtual bool totalTime( OdUInt32& msec, OdTvResult* rc = NULL ) const;

  virtual OdTvResult reset();

    /** \details
  Reads the .dwg file data of this object.
  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields( OdTvDbDwgFiler* pFiler );

  /** \details
  Writes the .dwg file data of this object.
  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields( OdTvDbDwgFiler* pFiler ) const;

  virtual OdTvResult setName( const OdString& sName );
  virtual OdString getName() const;
  virtual bool getNeedSaveInFile( OdTvResult* rc = NULL ) const;
  void setNeedSaveInFile( bool bNeedSave );
};

typedef OdSmartPtr<OdTvAnimationContainerImpl> OdTvAnimationContainerImplPtr;

class OdTvAnimationContainerWrapper : public OdTvAnimationContainer
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL( OdTvAnimationContainer, OdTvAnimationContainerImpl )

    friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  virtual OdTvResult addAnimation( const OdTvSubItemPath& actor, const OdTvAnimationActionId& actionId, OdInt32 nRepeats = 0, OdUInt32 timeStart = 0, OdTvAnimationContainer::OdTvActorBasis* pCustomBasis = NULL );
  virtual OdTvResult removeAnimation( const OdTvAnimationIteratorPtr& pIterator );
  virtual OdTvResult removeAnimations( const OdTvSubItemPath& path );
  virtual OdTvResult removeAnimations();
  virtual OdTvResult validateAnimations();

  virtual OdTvAnimationIteratorPtr getAnimationIterator( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setCurrentTime( OdUInt32 msec );
  virtual OdUInt32 currentTime( OdTvResult* rc = NULL ) const;

  virtual OdTvResult reset();

  virtual OdTvResult setName( const OdString& sName );
  virtual OdString getName( OdTvResult* rc = NULL ) const;

  virtual bool totalTime( OdUInt32& msec, OdTvResult* rc = NULL ) const;

  virtual bool getNeedSaveInFile( OdTvResult* rc = NULL ) const;

  ODTV_DEFINE_XDATA_DECL( virtual );
  ODTV_DEFINE_HANDLED_OBJECT_DECL( virtual );
};

/** \details
This is an implementation of the iterator class for the animation containers
*/
class OdTvAnimationContainersIteratorImpl : public OdTvAnimationContainersIterator
{
  friend class OdTvDatabaseImpl;
public:

  virtual ~OdTvAnimationContainersIteratorImpl();

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done( OdTvResult* rc = NULL ) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();
  virtual OdTvAnimationContainerId getAnimationContainer( OdTvResult* rc = NULL ) const;

  virtual OdTvResult seek( const OdTvAnimationContainerId& managerId );
  static OdTvAnimationContainersIteratorPtr createObject( OdTvDbDictionaryIterator* pDbIterator );

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvAnimationContainersIteratorImpl();
  OdTvAnimationContainersIteratorImpl( OdTvDbDictionaryIterator* pDbIterator );

  // Db iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};


#endif // _ODTV_ANIMATIONIMPL_H_INCLUDED_

