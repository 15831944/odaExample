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

#ifndef PLOTSTYLEREF_DEFINED
#define PLOTSTYLEREF_DEFINED

#include "DbDictionaryWithDefault.h"
#include "DbPlaceHolder.h"
#include "DbMaterial.h"

OdString oddbPlotStyleName(const OdDbDatabase* pDb, const OdDbObjectId& plotStyleNameId, OdInt16 colorIndex);
OdResult oddbPlotStyleNameId(const OdDbDatabase* pDb, const OdString& newName, OdDbObjectId& plotStyleNameId);

template<class T> class PlotStyleRef : public T
{
protected:
  mutable OdDbObjectId m_PlotStyleNameId;
  mutable OdDbObjectId m_LinetypeId;
  mutable OdDbObjectId m_MaterialId;

public:
  PlotStyleRef()  {}

///////////////////////////////////////////////////
  OdDbObjectId plotStyleId() const
  {
    if (m_PlotStyleNameId.isNull())
    {
      OdDbDatabase* pDb = T::database();
      if (pDb)
      {
        OdDbDictionaryWithDefaultPtr pDic = pDb->getPlotStyleNameDictionaryId(false).openObject();
        if (!pDic.isNull())
        {
          OdDbObjectId id = pDic->defaultId();
          if (pDb == id.database())
            m_PlotStyleNameId = id;
          return id;
        }
      }
    }
    return m_PlotStyleNameId;
  }

  ////////////////////////////////////////////////////////////////////////
  OdString plotStyleName(OdInt16 colorIndex) const
  {
    return ::oddbPlotStyleName(T::database(), m_PlotStyleNameId, colorIndex);
  }

  ////////////////////////////////////////////////////////////////
  OdResult setPlotStyleName(const OdString& newName)
  {
    return ::oddbPlotStyleNameId(T::database(), newName, m_PlotStyleNameId);
  }

  ////////////////////////////////////////////////////////////////
  void setPlotStyleId(OdDbObjectId newId)
  {
    m_PlotStyleNameId = newId;
  }

///////////////////////////////////////////////////////////////////
  virtual OdDbObjectId linetypeId() const
  {
    if (m_LinetypeId.isNull())
    {
      OdDbDatabase * pDb = T::database();
      if (pDb)
      {
        OdDbObjectId id = pDb->getLinetypeByLayerId();
        if (id.database() == pDb)
          m_LinetypeId = id;
        return id;
      }
    }
    return m_LinetypeId;
  }

  OdString linetypeName() const
  {
    return OdDbSymUtil::getSymbolName(linetypeId());
  }

  bool hasLinetypeByLayer() const
  { return m_LinetypeId.isNull() || (m_LinetypeId == m_LinetypeId.database()->getLinetypeByLayerId());}

  bool hasLinetypeByBlock() const
  { return !m_LinetypeId.isNull() && (m_LinetypeId == m_LinetypeId.database()->getLinetypeByBlockId());}

  bool hasLinetypeContinuous() const
  { return !m_LinetypeId.isNull() && (m_LinetypeId == m_LinetypeId.database()->getLinetypeContinuousId());}

  virtual void setLinetype(OdDbObjectId id, bool /*doSubents*/ = true)
  {
    m_LinetypeId = id;
    if (!T::database())
    {
      T::setDatabase(id.database());
    }
  }

  void setLinetypeId(OdDbObjectId id) // this one does not check that id is in the same DB
  {
    m_LinetypeId = id;
  }

///////////////////////////////////////////////////////////////////
  virtual OdDbObjectId materialId() const
  {
    return m_MaterialId;
  }

  OdString materialName() const
  {
    OdString strMat;
    OdDbMaterialPtr pMaterial = materialId().openObject();
    if (!pMaterial.isNull())
    {
      strMat = pMaterial->name();
    }
    return strMat;
  }

  void setMaterialId(OdDbObjectId id) // this one does not check that id is in the same DB
  {
    m_MaterialId = id;
  }
};

#endif  // PLOTSTYLEREF_DEFINED
