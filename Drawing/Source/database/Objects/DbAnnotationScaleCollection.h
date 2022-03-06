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

class OdDbAnnotationScaleCollection;
class OdDbAnnotationScaleViewCollection;
class OdDbAnnotationScaleCollectionIteratorImpl;
class OdDbAnnotationScaleCollectionImpl;
class OdDbAnnotationScaleViewCollectionImpl;
class OdDbAnnotationScaleViewCollectionIteratorImpl;
typedef OdSmartPtr<OdDbAnnotationScaleCollection>OdDbAnnotationScaleCollectionPtr;
typedef OdSmartPtr<OdDbAnnotationScaleViewCollection>OdDbAnnotationScaleViewCollectionPtr;

class TOOLKIT_EXPORT OdDbAnnotationScaleCollection : public OdDbObjectContextCollection
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAnnotationScaleCollection);
  static OdDbAnnotationScaleCollectionPtr createObject(OdDbDatabase*);
  virtual OdString name() const;
  virtual OdDbObjectContextPtr currentContext(const OdDbObject *) const;
  virtual OdResult setCurrentContext(const OdDbObjectContext*);
  virtual OdResult addContext(const OdDbObjectContext *);
  virtual OdResult removeContext(const OdString &);
  virtual OdResult lockContext(const OdDbObjectContext*);
  virtual OdResult unlockContext();
  virtual bool locked() const;
  virtual OdDbObjectContextPtr getContext(const OdString &) const;
  virtual bool hasContext(const OdString &) const;
  virtual OdDbObjectContextCollectionIteratorPtr newIterator() const;
protected:
  OdDbAnnotationScaleCollectionImpl* m_pImpl;
  OdDbAnnotationScaleCollection(OdDbAnnotationScaleCollectionImpl*);
  friend class OdDbAnnotationScaleCollectionImpl;
};

class TOOLKIT_EXPORT OdDbAnnotationScaleCollectionIterator : public OdDbObjectContextCollectionIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAnnotationScaleCollectionIterator);
  virtual OdResult start();
  virtual bool next();
  virtual bool done() const;
  virtual OdDbObjectContextPtr getContext() const;
protected:
  OdDbAnnotationScaleCollectionIteratorImpl* m_pImpl;
  OdDbAnnotationScaleCollectionIterator(OdDbAnnotationScaleCollectionIteratorImpl*);
  friend class OdDbAnnotationScaleCollection;
};

class TOOLKIT_EXPORT OdDbAnnotationScaleViewCollection : public OdDbObjectContextCollection
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAnnotationScaleViewCollection);
  static OdDbAnnotationScaleViewCollectionPtr createObject(OdDbDatabase*);
  virtual OdResult addContext(const OdDbObjectContext*);
  virtual OdDbObjectContextPtr currentContext(const OdDbObject *) const;
  virtual OdDbObjectContextPtr getContext(const OdString &) const;
  virtual bool hasContext(const OdString &) const;
  virtual OdResult lockContext(const OdDbObjectContext *);
  virtual bool locked() const;
  virtual OdString name() const;
  virtual OdResult removeContext(const OdString &);
  virtual OdResult setCurrentContext(const OdDbObjectContext*);
  virtual OdResult unlockContext();
  virtual OdDbObjectContextCollectionIteratorPtr newIterator() const;
protected:
  OdDbAnnotationScaleViewCollectionImpl* m_pImpl;
  OdDbAnnotationScaleViewCollection(OdDbAnnotationScaleViewCollectionImpl*);
};

class TOOLKIT_EXPORT OdDbAnnotationScaleViewCollectionIterator : public OdDbObjectContextCollectionIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAnnotationScaleViewCollectionIterator);
  virtual OdResult start();
  virtual bool done() const;
  virtual bool next();
  virtual OdDbObjectContextPtr getContext() const;
protected:
  OdDbAnnotationScaleViewCollectionIteratorImpl* m_pImpl;
  OdDbAnnotationScaleViewCollectionIterator(OdDbAnnotationScaleViewCollectionIteratorImpl*);
  friend class OdDbAnnotationScaleViewCollection;
};

// add runtime scale representation for the given scale id (used after scale cloning)
TOOLKIT_EXPORT void oddbAddRuntimeScale(OdDbAnnotationScaleCollection* coll, OdDbObjectId scaleId);
TOOLKIT_EXPORT void oddbAddRuntimeScale(OdDbAnnotationScaleViewCollection* coll, OdDbObjectId scaleId);

#include "TD_PackPop.h"

#endif // _DBANNOTATIONSCALECOLLECTION_H_INLCUDED_
