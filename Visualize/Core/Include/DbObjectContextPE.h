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

#ifndef _ODDBOBJECTCONTEXTPE_H_ICLUDED_
#define _ODDBOBJECTCONTEXTPE_H_ICLUDED_

#include "DbObjectContextInterface.h"
#include "DbObjectContextCollection.h"
#include "DbObjectContextData.h"

/** \details
<group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectContextDefaultPE : public OdTvDbObjectContextInterface
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextDefaultPE);
  virtual OdResult addContext(OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual bool hasContext(const OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual OdResult removeContext(OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual bool supportsCollection(const OdTvDbObject*,const OdString&) const;
};

class OdTvDbContextDataSubManager;

/** \details
<group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectContextPE : public OdTvDbObjectContextInterface
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextPE);
  virtual OdResult setDefaultContext(OdTvDbObject*,const OdTvDbObjectContext&);
  virtual OdTvDbObjectContextDataPtr getDefaultContextData(const OdTvDbObject* ,const OdString& /*,bool*/) const;
  virtual OdResult addContext(OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject* pObj,const OdTvDbObjectContext& ctx, const OdTvDbObjectContext& def) const = 0;
  virtual bool hasContext(const OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual OdResult removeContext(OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual bool supportsCollection(const OdTvDbObject*,const OdString&) const;
  virtual OdTvDbObjectContextDataPtr getContextData(const OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual void compose(OdTvDbObject* pObj);
/*  
  virtual OdResult addContext(OdTvDbObject*,const OdTvDbObjectContext&,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextCollection* contextCollection(const OdTvDbObject*,const OdString&) const;
  virtual OdResult addCurrentContext(OdTvDbObject*,const OdString&,OdTvDbObjectContextData*) const;
  //virtual OdResult copyContextData(const OdTvDbObject*,OdTvDbObject*) const;
  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdResult deleteContextData(OdTvDbObject*) const;
  virtual OdResult dwgInContextData(const OdTvDbObject*,OdTvDbDwgFiler*) const;
  virtual OdResult dwgOutContextData(const OdTvDbObject*,OdTvDbDwgFiler*) const;
  OdTvDbContextDataSubManager* getContextDataSubManager(const OdTvDbObject*,const OdTvDbObjectContext&,bool,bool) const;
  OdTvDbContextDataSubManager* getContextDataSubManager(const OdTvDbObject*,const OdString&,bool,bool) const;
  virtual OdResult getContexts(const OdTvDbObject*,const OdString&,OdRxObjectPtrArray&) const;
  virtual OdTvDbObjectContextData*  getCurrentContextData(const OdTvDbObject*,const OdString&,bool) const;
  static OdTvDbObjectContextPE* getObjectContextPE(const OdTvDbObject*);
  virtual bool  hasContext(const OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual int  numContexts(const OdTvDbObject*,const OdString&) const;
  virtual OdResult removeAllContexts(OdTvDbObject*,const OdString&) const;
  virtual OdResult removeContext(OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual OdResult removeContext(OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdResult replaceContext(OdTvDbObject*,OdTvDbObjectContextData*,bool) const;
  virtual OdResult saveContextData(const OdTvDbObject*) const;
  virtual bool  supportsCollection(const OdTvDbObject*,const OdString&) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);
  OdResult updateContextData(const OdTvDbObject*,void *) const;
  static void init();
  static void uninit();*/
};

typedef OdSmartPtr<OdTvDbObjectContextPE> OdTvDbObjectContextPEPtr;

/** \details
<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbObjectContextHatchPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextHatchPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const ODRX_OVERRIDE;
  virtual OdResult addContext(OdTvDbObject* pObject, const OdTvDbObjectContext& ctx) const ODRX_OVERRIDE;
/*
  virtual OdTvDbObjectContextData*  getContextData(const OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual OdTvDbObjectContextData*  getCurrentContextData(const OdTvDbObject*,const OdString&,bool) const;
  virtual bool  hasContext(const OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual OdResult removeAllContexts(OdTvDbObject*,const OdString&) const;
  virtual OdResult removeContext(OdTvDbObject*,const OdTvDbObjectContext&) const;
  virtual bool  supportsCollection(const OdTvDbObject*,const OdString&) const;
  */
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextMTextPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextMTextPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
  //virtual OdResult addContext(OdTvDbObject*,const OdTvDbObjectContext&,OdTvDbObjectContextData*) const;
};

/** \details
<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbObjectContextTextPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextTextPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
};
typedef OdSmartPtr<OdTvDbObjectContextTextPE> OdTvDbObjectContextTextPEPtr;

/** \details
<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbObjectContextAttributePE : public OdTvDbObjectContextTextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextAttributePE);
  virtual OdResult addContext(OdTvDbObject* pObject, const OdTvDbObjectContext& ctx) const ODRX_OVERRIDE;
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextLeaderPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextLeaderPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextMLeaderPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextMLeaderPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const ODRX_OVERRIDE;
  virtual OdResult addContext(OdTvDbObject*,const OdTvDbObjectContext&) const ODRX_OVERRIDE;
};
typedef OdSmartPtr<OdTvDbObjectContextMLeaderPE> OdTvDbObjectContextMLeaderPEPtr;

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextFcfPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextFcfPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
};

/** \details
<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbObjectContextBlkRefPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextBlkRefPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const ODRX_OVERRIDE;
  virtual OdResult setDefaultContext(OdTvDbObject*,const OdTvDbObjectContext&) ODRX_OVERRIDE;
  virtual OdResult addContext(OdTvDbObject*,const OdTvDbObjectContext&) const ODRX_OVERRIDE;
  virtual OdResult removeContext(OdTvDbObject*,const OdTvDbObjectContext&) const ODRX_OVERRIDE;
  virtual void compose(OdTvDbObject*);
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextDimPE : public OdTvDbObjectContextPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextDimPE);
  virtual OdResult addContext(OdTvDbObject* pObject, const OdTvDbObjectContext& ctx) const;
/*  virtual void *  contextDataManager(const OdTvDbObject*,bool) const;
  virtual OdTvDbObjectContextData*  createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult dwgInContextData(const OdTvDbObject*,OdTvDbDwgFiler*) const;
  virtual OdResult saveContextDataManager(OdTvDbObject*,void *) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextAlDimPE : public OdTvDbObjectContextDimPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextAlDimPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
/*  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextAngDimPE : public OdTvDbObjectContextDimPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextAngDimPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
/*  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextDmDimPE : public OdTvDbObjectContextDimPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextDmDimPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
/*  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextOrdDimPE : public OdTvDbObjectContextDimPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextOrdDimPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
/*  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextRaDimPE : public OdTvDbObjectContextDimPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextRaDimPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
/*  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

/** \details
<group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbObjectContextRaDimLrgPE : public OdTvDbObjectContextRaDimPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectContextRaDimLrgPE);
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdTvDbObjectContext&, const OdTvDbObjectContext& def) const;
/*  virtual OdTvDbObjectContextData* copyExtDictContextData(const OdTvDbObject*,OdTvDbObjectContextData*) const;
  virtual OdTvDbObjectContextDataPtr createContextData(const OdTvDbObject*,const OdString&,const OdTvDbObjectContext*,OdTvDbObjectContextData*,const OdTvDbContextDataSubManager*) const;
  virtual OdResult synchronizeContextData(const OdTvDbObject*,const OdTvDbObjectContext&);*/
};

TOOLKIT_EXPORT bool odtvdbGetContextDataAndScale(class OdGiCommonDraw* pWd, const OdTvDbObject* pObject, OdTvDbAnnotScaleObjectContextDataPtr& ctx, double* scaleOut = 0, bool getDefaultScale = false);

#endif
