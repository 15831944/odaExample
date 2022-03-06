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

#ifndef _DBANNOTATIONSCALECOLLECTION_H_INLCUDED_
#define _DBANNOTATIONSCALECOLLECTION_H_INLCUDED_
#include "DbObjectContextCollection.h"
#include "TD_PackPush.h"

class OdTvDbAnnotationScaleCollection;
class OdTvDbAnnotationScaleViewCollection;
class OdTvDbAnnotationScaleCollectionIteratorImpl;
class OdTvDbAnnotationScaleCollectionImpl;
class OdTvDbAnnotationScaleViewCollectionImpl;
class OdTvDbAnnotationScaleViewCollectionIteratorImpl;
typedef OdSmartPtr<OdTvDbAnnotationScaleCollection>OdTvDbAnnotationScaleCollectionPtr;
typedef OdSmartPtr<OdTvDbAnnotationScaleViewCollection>OdTvDbAnnotationScaleViewCollectionPtr;

class TOOLKIT_EXPORT OdTvDbAnnotationScaleCollection : public OdTvDbObjectContextCollection
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAnnotationScaleCollection);
  static OdTvDbAnnotationScaleCollectionPtr createObject(OdTvDbDatabase*);
  virtual OdString name() const;
  virtual OdTvDbObjectContextPtr currentContext(const OdTvDbObject *) const;
  virtual OdResult setCurrentContext(const OdTvDbObjectContext*);
  virtual OdResult addContext(const OdTvDbObjectContext *);
  virtual OdResult removeContext(const OdString &);
  virtual OdResult lockContext(const OdTvDbObjectContext*);
  virtual OdResult unlockContext();
  virtual bool locked() const;
  virtual OdTvDbObjectContextPtr getContext(const OdString &) const;
  virtual bool hasContext(const OdString &) const;
  virtual OdTvDbObjectContextCollectionIteratorPtr newIterator() const;
protected:
  OdTvDbAnnotationScaleCollectionImpl* m_pImpl;
  OdTvDbAnnotationScaleCollection(OdTvDbAnnotationScaleCollectionImpl*);
  friend class OdTvDbAnnotationScaleCollectionImpl;
};

class TOOLKIT_EXPORT OdTvDbAnnotationScaleCollectionIterator : public OdTvDbObjectContextCollectionIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAnnotationScaleCollectionIterator);
  virtual OdResult start();
  virtual bool next();
  virtual bool done() const;
  virtual OdTvDbObjectContextPtr getContext() const;
protected:
  OdTvDbAnnotationScaleCollectionIteratorImpl* m_pImpl;
  OdTvDbAnnotationScaleCollectionIterator(OdTvDbAnnotationScaleCollectionIteratorImpl*);
  friend class OdTvDbAnnotationScaleCollection;
};

class TOOLKIT_EXPORT OdTvDbAnnotationScaleViewCollection : public OdTvDbObjectContextCollection
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAnnotationScaleViewCollection);
  static OdTvDbAnnotationScaleViewCollectionPtr createObject(OdTvDbDatabase*);
  virtual OdResult addContext(const OdTvDbObjectContext*);
  virtual OdTvDbObjectContextPtr currentContext(const OdTvDbObject *) const;
  virtual OdTvDbObjectContextPtr getContext(const OdString &) const;
  virtual bool hasContext(const OdString &) const;
  virtual OdResult lockContext(const OdTvDbObjectContext *);
  virtual bool locked() const;
  virtual OdString name() const;
  virtual OdResult removeContext(const OdString &);
  virtual OdResult setCurrentContext(const OdTvDbObjectContext*);
  virtual OdResult unlockContext();
  virtual OdTvDbObjectContextCollectionIteratorPtr newIterator() const;
protected:
  OdTvDbAnnotationScaleViewCollectionImpl* m_pImpl;
  OdTvDbAnnotationScaleViewCollection(OdTvDbAnnotationScaleViewCollectionImpl*);
};

class TOOLKIT_EXPORT OdTvDbAnnotationScaleViewCollectionIterator : public OdTvDbObjectContextCollectionIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAnnotationScaleViewCollectionIterator);
  virtual OdResult start();
  virtual bool done() const;
  virtual bool next();
  virtual OdTvDbObjectContextPtr getContext() const;
protected:
  OdTvDbAnnotationScaleViewCollectionIteratorImpl* m_pImpl;
  OdTvDbAnnotationScaleViewCollectionIterator(OdTvDbAnnotationScaleViewCollectionIteratorImpl*);
  friend class OdTvDbAnnotationScaleViewCollection;
};

// add runtime scale representation for the given scale id (used after scale cloning)
TOOLKIT_EXPORT void odtvdbAddRuntimeScale(OdTvDbAnnotationScaleCollection* coll, OdTvDbObjectId scaleId);
TOOLKIT_EXPORT void odtvdbAddRuntimeScale(OdTvDbAnnotationScaleViewCollection* coll, OdTvDbObjectId scaleId);

#include "TD_PackPop.h"

#endif // _DBANNOTATIONSCALECOLLECTION_H_INLCUDED_
