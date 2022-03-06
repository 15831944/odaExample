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

#ifndef _DbBlockElementImpl_h_Included_
#define _DbBlockElementImpl_h_Included_

#include "DbBlockElement.h"
#include "DbEvalGraphImpl.h"

class OdTvDbBlockRepresentationContext;
class OdTvDbBlockElementImpl : public OdTvDbEvalExprImpl
{
  friend class OdTvDbBlockElement;
protected:
  OdString m_sName;
  OdInt32 m_nVersionMajor,m_nVersionMinor,unk5; // OdDb::kDHL_CURRENT,76,0
  bool m_bIsMemberOfCurrentVisibilitySet;
  bool isMemberOfCurrentVisibilitySet()const{ return m_bIsMemberOfCurrentVisibilitySet;}
  void setMemberOfCurrentVisibilitySet(bool v) { m_bIsMemberOfCurrentVisibilitySet = v; }
  virtual bool connectionAllowed(const OdString&,OdTvDbEvalNodeId,const OdString&) const;
  virtual bool connectTo(const OdString&,OdTvDbEvalNodeId,const OdString&);
  virtual bool disconnectFrom(const OdString&,OdTvDbEvalNodeId,const OdString&);
  virtual bool hasConnectionNamed(const OdString&) const;
  virtual bool getConnectedNames(const OdString&,unsigned long,OdStringArray&) const;
  virtual bool getConnectedObjects(const OdString&,OdTvDbEvalNodeIdArray&) const;
  virtual void getConnectionNames(OdStringArray&) const;
  virtual bool getConnectionType  (const OdString& name, OdTvResBuf::ValueType& type) const;
  virtual OdTvResBufPtr getConnectionValue (const OdString& name) const;
  virtual void getStretchPoints( OdGePoint3dArray& a )const;
  virtual void moveStretchPointsAt( const OdIntArray& ia , const OdGeVector3d& v );
  virtual OdTvDbBlockElement::HistoryCompression historyCompression() const;
  virtual bool historyRequired() const;
  virtual bool hasInstanceData()const; // has instance data loaded
  virtual bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*&, bool bRequireEvaluate); // loads instance data from xdata chain
  virtual OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis) const; // saves instance data to xdata chain
  virtual void updateConnections();
  virtual bool evaluate( const OdTvDbEvalContext* ctx );
  OdTvDbBlockRepresentationContext* getRepresentation( const OdTvDbEvalContext* ctx ) const;
  virtual OdResult transformBy( const OdGeMatrix3d& );
public:
  virtual bool isModified() const { return false; }
  OdTvDbBlockElementImpl() : m_bIsMemberOfCurrentVisibilitySet(true)
    , m_nVersionMajor(OdDb::kDHL_CURRENT)
    , m_nVersionMinor(76)
    , unk5(0) {}
  DECLARE_GET_IMPL(OdTvDbBlockElement);
};

struct OdTvDbConnectionPoint
{
  OdTvDbConnectionPoint() : m_nId(0), m_vType(OdTvResBuf::kRtNone){}
  OdTvDbEvalNodeId m_nId;
  OdString m_sConnection;
  OdString m_sThisConnection;
  OdTvResBuf::ValueType m_vType;
};
struct OdTvDbConnectionDescriptor
{
  const wchar_t* m_sName;
  OdTvResBuf::ValueType m_vType;
};
template<int N> class OdTvDbConnectionPointArrayT
{
public:
  OdTvDbConnectionPoint m_pData[N];
  OdTvDbConnectionPointArrayT(OdTvDbConnectionDescriptor* cc)
  {
    for (int i = 0; i < N; ++i)
    {
      m_pData[i].m_sThisConnection = cc[i].m_sName;
      m_pData[i].m_vType = cc[i].m_vType;
    }
  }
  OdTvDbConnectionPoint& operator[](int n){ return m_pData[n]; }
  const OdTvDbConnectionPoint& operator[](int n) const { return m_pData[n]; }
  int size() const { return N; }

  void dwgIn( OdTvDbDwgFiler* pFiler )
  {
    for ( int i = 0; i < N; i++ )
    {
      m_pData[i].m_nId = pFiler->rdInt32();
      m_pData[i].m_sConnection = pFiler->rdString();
    }
  }

  void dwgOut( OdTvDbDwgFiler* pFiler )
  {
    for ( int i = 0; i < N; i++ )
    {
      pFiler->wrInt32( m_pData[i].m_nId );
      pFiler->wrString( m_pData[i].m_sConnection );
    }
  }

  void dxfIn( OdTvDbDxfFiler* pFiler, int idGroupCode, int stringGroupCode)
  {
    while (!pFiler->atEOF())
    {
      int gc = pFiler->nextItem();
      if ( gc >= idGroupCode && (gc-idGroupCode) < N )
        m_pData[ gc - idGroupCode ].m_nId = pFiler->rdInt32();
      else if ( gc >= stringGroupCode && (gc-stringGroupCode) < N )
        m_pData[ gc - stringGroupCode ].m_sConnection = pFiler->rdString();
      else
      {
        pFiler->pushBackItem();
        return;
      }
    }
  }
  void dxfOut( OdTvDbDxfFiler* pFiler, int idGroupCode, int stringGroupCode, bool sequential = false )
  {
    if (sequential)
    {
      for ( int i = 0; i < N; i++ )
        pFiler->wrInt32( idGroupCode + i, m_pData[i].m_nId );
      for ( int j = 0; j < N; j++ )
        pFiler->wrString( stringGroupCode + j, m_pData[j].m_sConnection );
    }
    else
    {
      for ( int i = 0; i < N; i++ )
      {
        pFiler->wrInt32( idGroupCode + i, m_pData[i].m_nId );
        pFiler->wrString( stringGroupCode + i, m_pData[i].m_sConnection );
      }
    }
  }
};

template<int N, class Base> class OdTvDbConnectionPointsImpl : public Base
{
public:
  OdTvDbConnectionPointArrayT<N> m_pConnections;
  OdTvDbConnectionPointsImpl(OdTvDbConnectionDescriptor* cc) : m_pConnections(cc){}
  virtual bool connectionAllowed(const OdString& thisConnectionName, OdTvDbEvalNodeId sourceConnectableId, const OdString& sourceConnectionName) const
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0)
      {
        OdTvResBuf::ValueType vt;
        if (OdTvDbEvalConnectablePtr(Base::getGraph()->getNode(sourceConnectableId))->getConnectionType(sourceConnectionName, vt))
          return vt == m_pConnections[i].m_vType;
      }
    }
    return false;
  }
  virtual bool connectTo(const OdString& thisConnectionName,OdTvDbEvalNodeId sourceConnectableId, const OdString& sourceConnectionName)
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0)
      {
        m_pConnections[i].m_nId = sourceConnectableId;
        m_pConnections[i].m_sConnection = sourceConnectionName;
        return true;
      }
    }
    return false;
  }
  virtual bool disconnectFrom(const OdString& thisConnectionName, OdTvDbEvalNodeId sourceConnectableId, const OdString& sourceConnectionName)
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0)
      {
        if (m_pConnections[i].m_nId == sourceConnectableId && m_pConnections[i].m_sConnection == sourceConnectionName)
        {
          m_pConnections[i].m_nId = 0;
          m_pConnections[i].m_sConnection = OdString::kEmpty;
          return true;
        }
      }
    }
    return false;
  }
  virtual bool hasConnectionNamed(const OdString& thisConnectionName) const
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0)
        return true;
    }
    return false;
  }
  virtual bool getConnectedNames(const OdString& thisConnectionName, unsigned long sourceConnectableId,OdStringArray& names) const
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0 && m_pConnections[i].m_nId == sourceConnectableId)
      {
        names.append(m_pConnections[i].m_sConnection);
      }
    }
    return true;
  }
  virtual bool getConnectedObjects(const OdString& thisConnectionName, OdTvDbEvalNodeIdArray& nodes) const
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0)
      {
        nodes.append(m_pConnections[i].m_nId);
      }
    }
    return true;
  }
  virtual void getConnectionNames(OdStringArray& names) const
  {
    for (int i = 0; i < N; ++i)
    {
        names.append(m_pConnections[i].m_sThisConnection);
    }
  }
  virtual bool getConnectionType(const OdString& thisConnectionName, OdTvResBuf::ValueType& type) const
  {
    for (int i = 0; i < N; ++i)
    {
      if (m_pConnections[i].m_sThisConnection.iCompare(thisConnectionName) == 0)
      {
        type = m_pConnections[i].m_vType;
        return true;
      }
    }
    return false;
  }
};

#endif // _DbBlockElementImpl_h_Included_
