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

#ifndef _LyLayerFilterImpl_h_Included_
#define _LyLayerFilterImpl_h_Included_

#include "LyLayerFilter.h"
#include "DbDatabase.h"
#include "DbLayerTableRecord.h"

class OdTvLyBoolExprImpl : public OdTvLyBoolExpr
{
public:
    OdTvLyBoolExprImpl(const OdArray<OdTvLyAndExpr*>& andExprArray) { m_andExprArray = andExprArray; }
    virtual ~OdTvLyBoolExprImpl()
    {
        for (unsigned int i = 0; i < m_andExprArray.size(); i++)
        {
            delete m_andExprArray[i];
            m_andExprArray[i] = NULL;
        }
    }
    virtual const OdArray<OdTvLyAndExpr*>& getAndExprs() const { return m_andExprArray; }
    bool filter(OdTvDbLayerTableRecord* layer, OdTvDbDatabase* pDatabase);
private:
    OdArray<OdTvLyAndExpr*> m_andExprArray;
};

class OdTvLyAndExprImpl : public OdTvLyAndExpr
{
  OdArray<OdTvLyRelExpr*> m_relExprArray;
public:
    OdTvLyAndExprImpl(const OdArray<OdTvLyRelExpr*>& relExprArray) { m_relExprArray = relExprArray; }
    virtual ~OdTvLyAndExprImpl()
    {
        for (unsigned int i = 0; i < m_relExprArray.size(); i++)
        {
            delete m_relExprArray[i];
            m_relExprArray[i] = NULL;
        }
    }
    virtual const OdArray<OdTvLyRelExpr*>& getRelExprs() const { return m_relExprArray; }
    bool filter(OdTvDbLayerTableRecord* layer, OdTvDbDatabase* pDatabase);
};

class OdTvLyRelExprImpl : public OdTvLyRelExpr
{
  OdString m_constant, m_variable;
public:
    OdTvLyRelExprImpl(const OdString& constant, const OdString& variable)
    {
        m_constant = constant;
        m_variable = variable;
    }
    virtual const OdString& getConstant() const { return m_constant; }
    virtual const OdString& getVariable() const { return m_variable; }
    bool filter(OdTvDbLayerTableRecord* layer, OdTvDbDatabase* pDatabase);
    bool compareWithLineWeight(OdDb::LineWeight lineWeight);
};

class OdTvLyLayerFilterManagerImpl : public OdTvLyLayerFilterManager
{
  OdTvLyLayerFilterPtr m_pRoot, m_pCurrent;
  OdTvDbDatabase* m_pDatabase;
  static OdResult loadNestedFilters( OdTvDbObjectPtr obj, 
    OdTvLyLayerFilterPtr& pRoot, OdTvLyLayerFilterPtr& pCurrent );
  static void saveNestedFilters( OdTvDbDatabase* db, OdTvDbObjectPtr obj, 
    const OdTvLyLayerFilterPtr& pRoot, const OdTvLyLayerFilterPtr& pCurrent );
public:
  ODRX_DECLARE_MEMBERS( OdTvLyLayerFilterManagerImpl );
  void setDatabase( OdTvDbDatabase* db );
  virtual OdResult getFilters( OdTvLyLayerFilterPtr& pRoot, OdTvLyLayerFilterPtr& pCurrent );
  virtual void setFilters( const OdTvLyLayerFilterPtr pRoot, const OdTvLyLayerFilterPtr pCurrent );
};

class OdTvLyLayerFilterImpl
{
  OdString m_Name;
  OdTvLyLayerFilter* m_pParent;
  OdTvLyLayerFilterArray m_NestedFilters;
  OdString m_sExpression;
  OdTvLyBoolExpr* m_pBoolExpr;
  OdTvDbDatabase* m_pDatabase;

  static bool isValidName( const OdString& s );
public:
  OdTvLyLayerFilterImpl();
  virtual ~OdTvLyLayerFilterImpl();

  virtual const OdString& name() const;
  virtual bool setName( const OdString& s );
  virtual bool allowRename() const;
  virtual OdTvLyLayerFilter* parent() const;
  void setParent(OdTvLyLayerFilter* lf);
  
  //nested filter manipulation
  virtual const OdTvLyLayerFilterArray& getNestedFilters() const;
  virtual void addNested( OdTvLyLayerFilter* filter );
  virtual void removeNested( OdTvLyLayerFilter* filter );
  
  virtual OdResult generateNested();
  virtual bool dynamicallyGenerated() const;
  
  virtual bool allowNested() const;
  virtual bool allowDelete() const;
  virtual bool isProxy() const;
  virtual bool isIdFilter() const;
  
  virtual bool filter( OdTvDbLayerTableRecord* layer ) const;
  virtual const OdString& filterExpression() const;
  virtual const OdTvLyBoolExpr* filterExpressionTree() const { return m_pBoolExpr; }
  virtual OdResult setFilterExpression( const OdString& expr );
  
  virtual bool compareTo(const OdTvLyLayerFilter* pOther) const;
  
  virtual OdResult readFrom(OdTvDbDxfFiler* filer);
  virtual void writeTo(OdTvDbDxfFiler* pFiler) const;
};

class OdTvLyGroupFilterImpl : public OdTvLyLayerFilterImpl
{
  OdTvDbObjectIdArray m_Ids;
public:
  virtual void addLayerId( const OdTvDbObjectId& id );
  virtual void removeLayerId (const OdTvDbObjectId& id);
  virtual const OdTvDbObjectIdArray& layerIds() const;
  virtual OdResult readFrom(OdTvDbDxfFiler* filer);
  virtual void writeTo(OdTvDbDxfFiler* pFiler) const;
  virtual bool isIdFilter() const;
  virtual bool filter( OdTvDbLayerTableRecord* layer ) const;
};

class OdTvLyRootFilter : public OdTvLyLayerFilter
{
public:
  ODRX_DECLARE_MEMBERS( OdTvLyRootFilter );
  OdTvLyRootFilter()
  {
    OdTvLyLayerFilter::setName( OD_T("All") );
  }
  virtual bool allowRename() const
  {
    return false;
  }
  virtual bool allowDelete() const
  {
    return false;
  }
  virtual bool dynamicallyGenerated() const
  {
    return true;
  }
  bool filter( OdTvDbLayerTableRecord* ) const
  {
    return true;
  }
};

class OdTvLyInUseFilter : public OdTvLyLayerFilter
{
public:
  ODRX_DECLARE_MEMBERS( OdTvLyInUseFilter );
  OdTvLyInUseFilter()
  {
    OdTvLyLayerFilter::setName( OD_T("All Used Layers") );
    OdTvLyLayerFilter::setFilterExpression( OD_T("USED == \"TRUE\"") );
  }
  virtual bool allowRename() const
  {
    return false;
  }
  virtual bool allowDelete() const
  {
    return false;
  }
  virtual bool dynamicallyGenerated() const
  {
    return true;
  }
  bool filter( OdTvDbLayerTableRecord* lt ) const
  {
    return lt->isInUse();
  }
};

class OdTvLySystemInternals
{
public:
  static OdTvLyLayerFilterImpl* getImpl( const OdTvLyLayerFilter* f )
  {
    return reinterpret_cast<OdTvLyLayerFilterImpl*>( f->m_pImpl );
  }
  static void setImpl( OdTvLyLayerFilter* f, OdTvLyLayerFilterImpl* impl )
  {
    f->m_pImpl = impl;
  }
};

#endif // _LyLayerFilterImpl_h_Included_
