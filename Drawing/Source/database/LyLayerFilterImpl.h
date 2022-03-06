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

class OdLyBoolExprImpl : public OdLyBoolExpr
{
public:
    OdLyBoolExprImpl(const OdArray<OdLyAndExpr*>& andExprArray) { m_andExprArray = andExprArray; }
    virtual ~OdLyBoolExprImpl()
    {
      try
      {
        for (unsigned int i = 0; i < m_andExprArray.size(); i++)
        {
            delete m_andExprArray[i];
            m_andExprArray[i] = NULL;
        }
      }
      catch (...)
      {
        ODA_FAIL();
      }
    }
    virtual const OdArray<OdLyAndExpr*>& getAndExprs() const { return m_andExprArray; }
    bool filter(OdDbLayerTableRecord* layer, OdDbDatabase* pDatabase);
private:
    OdArray<OdLyAndExpr*> m_andExprArray;
};

class OdLyAndExprImpl : public OdLyAndExpr
{
  OdArray<OdLyRelExpr*> m_relExprArray;
public:
    OdLyAndExprImpl(const OdArray<OdLyRelExpr*>& relExprArray) { m_relExprArray = relExprArray; }
    virtual ~OdLyAndExprImpl()
    {
      try
      {
        for (unsigned int i = 0; i < m_relExprArray.size(); i++)
        {
          delete m_relExprArray[i];
          m_relExprArray[i] = NULL;
        }
      }
      catch (...)
      {
        ODA_FAIL();
      }
    }
    virtual const OdArray<OdLyRelExpr*>& getRelExprs() const { return m_relExprArray; }
    bool filter(OdDbLayerTableRecord* layer, OdDbDatabase* pDatabase);
};

class OdLyRelExprImpl : public OdLyRelExpr
{
  OdString m_constant, m_variable;
public:
    OdLyRelExprImpl(const OdString& constant, const OdString& variable)
    {
        m_constant = constant;
        m_variable = variable;
    }
    virtual const OdString& getConstant() const { return m_constant; }
    virtual const OdString& getVariable() const { return m_variable; }
    bool filter(OdDbLayerTableRecord* layer, OdDbDatabase* pDatabase);
    bool compareWithLineWeight(OdDb::LineWeight lineWeight);
};

class OdLyLayerFilterManagerImpl : public OdLyLayerFilterManager
{
  OdLyLayerFilterPtr m_pRoot, m_pCurrent;
  OdDbDatabase* m_pDatabase;
  static OdResult loadNestedFilters( OdDbObjectPtr obj, 
    OdLyLayerFilterPtr& pRoot, OdLyLayerFilterPtr& pCurrent );
  static void saveNestedFilters( OdDbDatabase* db, OdDbObjectPtr obj, 
    const OdLyLayerFilterPtr& pRoot, const OdLyLayerFilterPtr& pCurrent );
public:
  OdLyLayerFilterManagerImpl() : m_pDatabase(0) {}
  ODRX_DECLARE_MEMBERS( OdLyLayerFilterManagerImpl );
  void setDatabase( OdDbDatabase* db );
  virtual OdResult getFilters( OdLyLayerFilterPtr& pRoot, OdLyLayerFilterPtr& pCurrent );
  virtual void setFilters( const OdLyLayerFilterPtr pRoot, const OdLyLayerFilterPtr pCurrent );
};

class OdLyLayerFilterImpl
{
  OdString m_Name;
  OdLyLayerFilter* m_pParent;
  OdLyLayerFilterArray m_NestedFilters;
  OdString m_sExpression;
  OdLyBoolExpr* m_pBoolExpr;
  OdDbDatabase* m_pDatabase;

  static bool isValidName( const OdString& s );
public:
  OdLyLayerFilterImpl();
  virtual ~OdLyLayerFilterImpl();

  virtual const OdString& name() const;
  virtual bool setName( const OdString& s );
  virtual bool allowRename() const;
  virtual OdLyLayerFilter* parent() const;
  void setParent(OdLyLayerFilter* lf);
  
  //nested filter manipulation
  virtual const OdLyLayerFilterArray& getNestedFilters() const;
  virtual void addNested( OdLyLayerFilter* filter );
  virtual void removeNested( OdLyLayerFilter* filter );
  
  virtual OdResult generateNested();
  virtual bool dynamicallyGenerated() const;
  
  virtual bool allowNested() const;
  virtual bool allowDelete() const;
  virtual bool isProxy() const;
  virtual bool isIdFilter() const;
  
  virtual bool filter( OdDbLayerTableRecord* layer ) const;
  virtual const OdString& filterExpression() const;
  virtual const OdLyBoolExpr* filterExpressionTree() const { return m_pBoolExpr; }
  virtual OdResult setFilterExpression( const OdString& expr );
  
  virtual bool compareTo(const OdLyLayerFilter* pOther) const;
  
  virtual OdResult readFrom(OdDbDxfFiler* filer);
  virtual void writeTo(OdDbDxfFiler* pFiler) const;
};

class OdLyGroupFilterImpl : public OdLyLayerFilterImpl
{
  OdDbObjectIdArray m_Ids;
public:
  virtual void addLayerId( const OdDbObjectId& id );
  virtual void removeLayerId (const OdDbObjectId& id);
  virtual const OdDbObjectIdArray& layerIds() const;
  virtual OdResult readFrom(OdDbDxfFiler* filer);
  virtual void writeTo(OdDbDxfFiler* pFiler) const;
  virtual bool isIdFilter() const;
  virtual bool filter( OdDbLayerTableRecord* layer ) const;
};

class OdLyRootFilter : public OdLyLayerFilter
{
public:
  ODRX_DECLARE_MEMBERS( OdLyRootFilter );
  OdLyRootFilter()
  {
    OdLyLayerFilter::setName( OD_T("All") );
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
  bool filter( OdDbLayerTableRecord* ) const
  {
    return true;
  }
};

class OdLyInUseFilter : public OdLyLayerFilter
{
public:
  ODRX_DECLARE_MEMBERS( OdLyInUseFilter );
  OdLyInUseFilter()
  {
    OdLyLayerFilter::setName( OD_T("All Used Layers") );
    OdLyLayerFilter::setFilterExpression( OD_T("USED == \"TRUE\"") );
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
  bool filter( OdDbLayerTableRecord* lt ) const
  {
    return lt->isInUse();
  }
};

class OdLySystemInternals
{
public:
  static OdLyLayerFilterImpl* getImpl( const OdLyLayerFilter* f )
  {
    return reinterpret_cast<OdLyLayerFilterImpl*>( f->m_pImpl );
  }
  static void setImpl( OdLyLayerFilter* f, OdLyLayerFilterImpl* impl )
  {
    f->m_pImpl = impl;
  }
};

#endif // _LyLayerFilterImpl_h_Included_
