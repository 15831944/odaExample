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

#ifndef DbAssocEdgePersSubentId_INCLUDED_
#define DbAssocEdgePersSubentId_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"

#include "OdArray.h"
#include "SmartPtr.h"
#include "DbSubentId.h"
#include "DbAssocPersSubentId.h"

class OdTvDbAssocEdgePersSubentId;
typedef OdSmartPtr<OdTvDbAssocEdgePersSubentId> OdTvDbAssocEdgePersSubentIdPtr;

#include "TD_PackPush.h"


/** \details
  This class represents the edge persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocEdgePersSubentId : public OdTvDbAssocPersSubentId
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocEdgePersSubentId);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocEdgePersSubentId();

  /** \details
    Initializies first and second vertex numbers.
  */
  void init(int vertexIdentifier1, int vertexIdentifier2);

  /** \details
    Returns the number of transient subentity identifier corresponding to this associated 
    persistent subentity identifier.
  */
  virtual int transientSubentCount(const OdTvDbEntity* pEntity) const { return !isNull() ? 1 : 0; }

  /** \details
    Returns the subentity type.
  */
  virtual OdDb::SubentType subentType(const OdTvDbEntity* pEntity) const;

  /** \details
    Checks whether the identifier is kNull.
  */
  virtual bool isNull() const { return m_index1 == 0; }

  /** \details
    Checks whether this identifier is equal to the given identifier.
  */
  virtual bool isEqualTo(const OdTvDbEntity* pEntity, const OdTvDbAssocPersSubentId* pOther) const
  {
    if (!OdTvDbAssocPersSubentId::isEqualTo(pEntity, pOther))
      return false;

    OdTvDbAssocEdgePersSubentIdPtr pOtherEdge = pOther;
    return !pOtherEdge.isNull() && ((m_index1 == pOtherEdge->m_index1) && (m_index2== pOtherEdge->m_index2));
  }

  OdResult getTransientSubentIds(const OdTvDbEntity*  pEntity, OdArray<OdDbSubentId>& subents) const;

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  //virtual OdResult audit(OdTvDbAuditInfo* pAuditInfo);

  /** \details
    Returns the first gs-marker.
  */
  OdGsMarker index1() const { return m_index1; }

  /** \details
    Returns the second gs-marker.
  */
  OdGsMarker index2() const { return m_index2; }

  bool isSegmentArcCenter() {return !m_isMidPoint;}
  bool isSegmentMidPoint()  {return m_isMidPoint;}

private:
  /*!DOM*/
  OdGsMarker  m_index1;
  /*!DOM*/
  OdGsMarker  m_index2;
  /*!DOM*/
  bool m_isMidPoint;
};

#include "TD_PackPop.h"

#endif
