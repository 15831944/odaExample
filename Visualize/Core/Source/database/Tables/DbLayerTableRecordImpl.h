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

#ifndef _ODDBLAYERTABLERECORDIMPL_INCLUDED_
#define _ODDBLAYERTABLERECORDIMPL_INCLUDED_

#include "DbSymbolTableRecordImpl.h"
#include "PlotStyleRef.h"
#include "DbSystemInternals.h"
#include "DbLayerTableRecord.h"
#include "CmColor.h"

class OdTvDbIdSimpleMap;

class OdTvDbLayerTableRecordImplTransparencyContainer : public OdRxObject
{
  private:
    OdTvCmTransparency m_transparency;
  public:
    inline void setTransparency(const OdTvCmTransparency &transparency)
    {
      m_transparency = transparency;
    }
    inline const OdTvCmTransparency &transparency() const
    {
      return m_transparency;
    }
};
typedef OdSmartPtr<OdTvDbLayerTableRecordImplTransparencyContainer> OdTvDbLayerTableRecordImplTransparencyContainerPtr;

class OdTvDbLayerTableRecordImpl : public PlotStyleRef<OdTvDbSymbolTableRecordImpl>
{
  static OdTvDbLayerTableRecordImpl* getImpl(const OdTvDbLayerTableRecord *pObj)
  { return (OdTvDbLayerTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

	enum
	{
		FROZEN      = 1,
		FROZENVPDEF = 2,
		LOCKED      = 4
	};

private:
  //OdUInt16 m_LinetypeIndx;

protected:
  OdTvCmColor         m_color;   // Layer color does not have a corresponding color dictionary entry.
  OdTvDbLayerTableRecordImplTransparencyContainerPtr m_pTransparency;
  OdTvDbObjectId      m_UnknownHardPointerId; // AC27 support

  OdInt8           m_Lineweight;
  // Optimization of subWorldDraw
  enum
  {
    kOverridesChecked = 1,
    kHasOverrides     = 2
  };
  mutable OdUInt8   m_ovrFlags;
  void clearOverridesFlags();
  bool hasAnyOverrides(const OdTvDbLayerTableRecord *pLTR) const;
  //
private:
  bool              m_bPlottable;
  bool              m_bIsOff;
  bool              m_bInUse;

  TOOLKIT_EXPORT OdInt16 getLayerColorIndex(bool forDxf = true) const;

public:
  ///////////////////////////////////////
  //OdTvDbObjectId linetypeId() const;
  //OdString linetypeName() const;
  //void setLinetype(OdTvDbObjectId id);
  //void setLinetype(const OdChar * name);

public:
  OdTvDbLayerTableRecordImpl();

  virtual OdTvDbObjectId linetypeId() const
  {
    if (m_LinetypeId.isNull())
    {
      OdTvDbDatabase * pDb = database();
      if (pDb)
      {
        m_LinetypeId = pDb->getLinetypeContinuousId();
      }
    }
    return m_LinetypeId;
  }

  virtual OdTvDbObjectId materialId() const
  {
    if (m_MaterialId.isNull())
    {
      OdTvDbDatabase * pDb = database();
      if (pDb)
      {
        m_MaterialId = pDb->globalMaterialId();
      }
    }
    return m_MaterialId;
  }

  bool isPlottable() const
  {
    if(m_Name.iCompare(OdTvDbSymUtil::layerDefpointsName())==0)// 'DefPoints' layer can't be plotted.
      return false;
    return m_bPlottable;
  }
	void setPlottable(bool value)  { m_bPlottable = value; }

  bool isFrozenVPDefault() const { return GETBIT(m_Flags, FROZENVPDEF); }
  void setIsFrozenVPDefault(bool value) { SETBIT(m_Flags, FROZENVPDEF, value); }

  bool isLocked() const          { return GETBIT(m_Flags, LOCKED); }
  void setIsLocked(bool value)   { SETBIT(m_Flags, LOCKED, value); }

  bool isFrozen() const          { return GETBIT(m_Flags, FROZEN); }
  void setIsFrozen(bool value)   { SETBIT(m_Flags, FROZEN, value); }

  void setIsOff(bool value)      { m_bIsOff = value; }
  bool isOff() const             { return m_bIsOff; }

  bool isInUse() const           { return m_bInUse;}
  void setInUse(bool value)      { m_bInUse = value; }
  
  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void audit (OdTvDbAuditInfo* pAuditInfo);
  TOOLKIT_EXPORT static void fixColorIndex(short & index, OdTvDbFiler * pFiler, OdTvDbLayerTableRecord * pLayer);
  virtual void setName(const OdString& name);
  int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;

  virtual void mergeXrefTable(
    OdTvDbIdPair& idPair,
    OdTvDbSymbolTable* pTable,
    OdTvDbIdMapping& idMap,
    OdTvDbSymbolTableRecord* pRec);

  friend class OdTvDbLayerTableRecord;
  friend class OdTvDbLayerTable;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
};

#endif //_ODDBLAYERTABLERECORDIMPL_INCLUDED_
