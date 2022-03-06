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

#ifndef __TNW_PATHLINKMAP_H__
#define __TNW_PATHLINKMAP_H__

#include "NwExport.h"
#define STL_USING_MAP
#define STL_USING_VECTOR
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "OdResult.h"

class OdNwModelItem;
class OdNwObjectId;
class OdNwDatabase;

class NWDBEXPORT OdNwPathLinkMap
{
public:
  OdNwPathLinkMap();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  ~OdNwPathLinkMap() = default;

public:
  void clear();
  OdResult generateReadPathMap(OdNwModelItem* pRoot);
  OdResult generateWritePathMap();

public:
  OdNwModelItem* getRoot() const;
  inline std::vector<OdNwModelItem*>& getReadLinkObj() { return m_vReadLinkObj; }
  OdNwModelItem* getReadLink(OdUInt32 idx) const;
  OdUInt32 getWriteLinkId(OdNwModelItem* pPathLink) const;

public:
  void setRoot(OdNwModelItem* pRoot);
  void setDefault(OdNwDatabase* pDb);

private:
  std::map<OdNwObjectId, OdUInt32>  m_mWriteMap;
  std::vector<OdNwModelItem*>       m_vReadLinkObj;
  OdNwModelItem*                    m_pRoot;
  bool                              m_bFlag;
};

typedef std::shared_ptr<OdNwPathLinkMap> OdNwPathLinkMapPtr;
typedef std::weak_ptr<OdNwPathLinkMap> OdNwPathLinkMapWeakPtr;

#endif //__TNW_PATHLINKMAP_H__
