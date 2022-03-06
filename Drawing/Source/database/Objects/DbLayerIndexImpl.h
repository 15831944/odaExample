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

#ifndef _ODDBLAYERINDEXIMPL_INCLUDED_
#define _ODDBLAYERINDEXIMPL_INCLUDED_

#include "DbIndexImpl.h"
#include "OdArray.h"
#include "DbLayerIndex.h"
#include "DbSystemInternals.h"

class OdLayerIndexMap;

class OdDbLayerIndexImpl : public OdDbIndexImpl
{
  static OdDbLayerIndexImpl* getImpl(const OdDbLayerIndex *pObj)
  { return (OdDbLayerIndexImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
	class Item
	{
	public:
		OdString& name() { return m_strName; }
		const OdString& getName() const { return m_strName; }
		void setName(const OdString& value) { m_strName = value; }

    OdInt32 getNumEntries() const { return m_nNumEntries; }
    void setNumEntries(OdInt32 value) { m_nNumEntries = value; }

		Item() : m_nNumEntries(0) {}
    Item(const OdString& layerName, OdDbHardOwnershipId bufferId, OdInt32 n)
      : m_strName(layerName), m_Id(bufferId), m_nNumEntries(n) {}

		OdDbObjectId& id() { return m_Id; }
		const OdDbObjectId& getId() const { return m_Id; }

	private:
		OdString	          m_strName;
    OdInt32             m_nNumEntries;
		OdDbHardOwnershipId m_Id;
	};

  inline OdDbObjectId getEntitiesOnLayer(const OdString& sLayerName) const
  {
    for(unsigned int i = 0; i<m_Entries.size(); ++i)
    {
      if(m_Entries[i].getName().iCompare(sLayerName)==0)
        return m_Entries[i].getId();
    }
    return OdDbObjectId::kNull;
  }


	typedef OdArray<Item>  ItemArray;

	ItemArray m_Entries;

  void buildLayerMap(OdLayerIndexMap& ids, OdDbLayerTable* pLayerTable, bool bClearIdsOnLayer);
  void saveData(OdLayerIndexMap& ids, OdDbLayerTable* pLayerTable);

  friend class OdDbLayerIndex;
  friend class OdDbLayerIndexIterator;
};

#endif // _ODDBLAYERINDEXIMPL_INCLUDED_
