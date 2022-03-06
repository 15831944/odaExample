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

#ifndef DbAssocPersSubentId_INCLUDED_
#define DbAssocPersSubentId_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbSubentId.h"
#include "SmartPtr.h"

class OdTvDbEntity;
class OdTvDbDwgFiler;
class OdTvDbDxfFiler;
class OdTvDbAuditInfo;

class OdTvDbAssocPersSubentId;
typedef OdSmartPtr<OdTvDbAssocPersSubentId> OdTvDbAssocPersSubentIdPtr;

class OdTvDbAssocSimplePersSubentId;
typedef OdSmartPtr<OdTvDbAssocSimplePersSubentId> OdTvDbAssocSimplePersSubentIdPtr;

class OdTvDbAssocSingleEdgePersSubentId;
typedef OdSmartPtr<OdTvDbAssocSingleEdgePersSubentId> OdTvDbAssocSingleEdgePersSubentIdPtr;

class OdTvDbAssocIndexPersSubentId;
typedef OdSmartPtr<OdTvDbAssocIndexPersSubentId> OdTvDbAssocIndexPersSubentIdPtr;

class OdTvDbAssocAsmBasedEntityPersSubentId;
typedef OdSmartPtr<OdTvDbAssocAsmBasedEntityPersSubentId> OdTvDbAssocAsmBasedEntityPersSubentIdPtr;

#include "TD_PackPush.h"

/** \details
  This is the abstract base class that represents the persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocPersSubentId : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocPersSubentId);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocPersSubentId() {}

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocPersSubentId() {}

  /** \details
    Gets all subentity identifiers corresponding to this associated persistent subentity identifier.
  */
  virtual OdResult getTransientSubentIds(const OdTvDbEntity*      pEntity, 
                                         OdArray<OdDbSubentId>& subents) const;

  /** \details
    Declares the pure method that returns the subentity type and must be overridden in derived classes.
  */
  virtual OdDb::SubentType subentType(const OdTvDbEntity* pEntity) const = 0;

  /** \details
    Returns the number of transient subentity identifiers corresponding to this associated 
    persistent subentity identifier.
  */
  virtual int transientSubentCount(const OdTvDbEntity* pEntity) const;

  /** \details
    Declares the pure method that checks whether this identifier is kNull and must be overridden in derived classes.
  */
  virtual bool isNull() const = 0;

  /** \details
    Checks whether this identifier is equal to the given identifier.
  */
  virtual bool isEqualTo(const OdTvDbEntity* pEntity, const OdTvDbAssocPersSubentId* pOther) const
  {
    return (this == pOther) || ((pEntity != NULL) && (pOther != NULL) && (isA() == pOther->isA()));
  }

  /** \details
    Notifies this associated persistent subentity identifier that the entity has been mirrored and 
    that the associated persistent subentity identifier possibly should be updated itself to identify 
    the same subentity in the mirrored entity.
  */
  virtual OdResult mirror(const OdTvDbEntity* pMirroredEntity);

  /** \details
    Reads the class identification of the actual associated persistent subentity identifier of derived class, 
    creates an instance for this derived class and calls dwgInFields() on it.
  */
  static OdResult createObjectAndDwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbAssocPersSubentIdPtr& pCreatedPersSubentId);

  /** \details
    Reads the class identification of the actual associated persistent subentity identifier of derived class, 
    creates an instance for this derived class and calls dxfInFields() on it.
  */
  static OdResult createObjectAndDxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbAssocPersSubentIdPtr& pCreatedPersSubentId);

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

  /** \details
    Provides the standard audit protocol.
  */
  virtual void audit(OdTvDbAuditInfo* /*pAuditInfo*/) {}
};

//----------------------------------------------------------------------------

/** \details
  This class represents the single edge persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocSingleEdgePersSubentId : public OdTvDbAssocPersSubentId
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocSingleEdgePersSubentId);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocSingleEdgePersSubentId();

  /** \details
    Returns the number of transient subentity identifiers corresponding to this associated 
    persistent subentity identifier for the given entity.
  */
  virtual int transientSubentCount(const OdTvDbEntity* /*pEntity*/) const { return 1; }

  /** \details
    Returns the subentity type for the given entity.
  */
  virtual OdDb::SubentType subentType(const OdTvDbEntity* /*pEntity*/) const { return OdDb::kEdgeSubentType; }

  /** \details
    Checks whether this identifier is kNull (always False).
  */
  virtual bool isNull() const { return false; }

  /** \details
    Checks whether this identifier is equal to the given identifier.
  */
  virtual bool isEqualTo(const OdTvDbEntity* pEntity, const OdTvDbAssocPersSubentId* pOther) const
  {
    return OdTvDbAssocPersSubentId::isEqualTo(pEntity, pOther);
  }

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

protected:
  /*!DOM*/
  bool m_Unk_Bool_1;
};

//----------------------------------------------------------------------------

/** \details
  This class represents the simple persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocSimplePersSubentId : public OdTvDbAssocPersSubentId
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocSimplePersSubentId);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocSimplePersSubentId();

  /** \details
    Initializes this instance using the specified ID instance.
  */
  void init(const OdDbSubentId& subentId);

  /** \details
    Returns the number of transient subentity identifiers corresponding to this associated 
    persistent subentity identifier for the given entity.
  */
  virtual int transientSubentCount(const OdTvDbEntity* /*pEntity*/) const { return !isNull() ? 1 : 0; }

  /** \details
    Returns the subentity type for the given entity.
  */
  virtual OdDb::SubentType subentType(const OdTvDbEntity* /*pEntity*/) const { return m_SubentId.type(); }

  /** \details
    Returns the subentity ID for the given entity.
  */
  virtual OdDbSubentId subentId(const OdTvDbEntity* /*pEntity*/) const { return m_SubentId; }

  /** \details
    Checks whether this identifier is kNull.
  */
  virtual bool isNull() const
  {
    return m_SubentId.type() == OdDb::kNullSubentType;
  }

  /** \details
    Checks whether this identifier is equal to the given identifier.
  */
  virtual bool isEqualTo(const OdTvDbEntity* pEntity, const OdTvDbAssocPersSubentId* pOther) const
  {
    if (!OdTvDbAssocPersSubentId::isEqualTo(pEntity, pOther))
      return false;

    OdTvDbAssocSimplePersSubentIdPtr pOtherSimple = pOther;
    return m_SubentId == pOtherSimple->m_SubentId;
  }

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

  /** \details
    Provides the standard audit protocol.
  */
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);

protected:
  /*!DOM*/
  bool m_Unk_Bool_1;
private:
  /*!DOM*/
  OdDbSubentId m_SubentId;
};

//----------------------------------------------------------------------------

/** \details
  This class represents the index persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocIndexPersSubentId : public OdTvDbAssocPersSubentId
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocIndexPersSubentId);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocIndexPersSubentId();

  /** \details
    Initializes this instance using the specified ID instance.
  */
  void init(const OdDbSubentId& subentId);

  /** \details
    Returns the number of transient subentity identifiers corresponding to this associated 
    persistent subentity identifier for the given entity.
  */
  virtual int transientSubentCount(const OdTvDbEntity* /*pEntity*/) const { return !isNull() ? 1 : 0; }

  /** \details
    Returns the subentity type for the given entity.
  */
  virtual OdDb::SubentType subentType(const OdTvDbEntity* /*pEntity*/) const { return m_SubentId.type(); }

  /** \details
    Returns the subentity ID for the given entity.
  */
  virtual OdDbSubentId subentId(const OdTvDbEntity* /*pEntity*/) const { return m_SubentId; }

  /** \details
    Checks whether this identifier is kNull.
  */
  virtual bool isNull() const
  {
    return m_SubentId.type() == OdDb::kNullSubentType;
  }

  /** \details
    Checks whether this identifier is equal to the given identifier.
  */
  virtual bool isEqualTo(const OdTvDbEntity* pEntity, const OdTvDbAssocPersSubentId* pOther) const
  {
    if (!OdTvDbAssocPersSubentId::isEqualTo(pEntity, pOther))
      return false;

    OdTvDbAssocIndexPersSubentIdPtr pOtherIndex = pOther;
    return m_SubentId == pOtherIndex->m_SubentId;
  }

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

  /** \details
    Provides the standard audit protocol.
  */
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);

protected:
  /*!DOM*/
  bool m_Unk_Bool_1;
private:
  /*!DOM*/
  OdDbSubentId m_SubentId;
};

/** \details
This class represents the modeler entity persistent subentity identifier.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocAsmBasedEntityPersSubentId : public OdTvDbAssocPersSubentId
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocAsmBasedEntityPersSubentId);

  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbAssocAsmBasedEntityPersSubentId();

  /** \details
  Initializes this instance using the specified ID instance.
  */
  void init(const OdDbSubentId& subentId);

  /** \details
  Returns the number of transient subentity identifiers corresponding to this associated
  persistent subentity identifier for the given entity.
  */
  virtual int transientSubentCount(const OdTvDbEntity* /*pEntity*/) const { return !isNull() ? 1 : 0; }

  /** \details
  Returns the subentity type for the given entity.
  */
  virtual OdDb::SubentType subentType(const OdTvDbEntity* /*pEntity*/) const { return m_SubentId.type(); }

  /** \details
  Returns the subentity ID for the given entity.
  */
  virtual OdDbSubentId subentId(const OdTvDbEntity* /*pEntity*/) const { return m_SubentId; }

  /** \details
  Checks whether this identifier is kNull.
  */
  virtual bool isNull() const
  {
    return m_SubentId.type() == OdDb::kNullSubentType;
  }

  /** \details
  Checks whether this identifier is equal to the given identifier.
  */
  virtual bool isEqualTo(const OdTvDbEntity* pEntity, const OdTvDbAssocPersSubentId* pOther) const
  {
    if (!OdTvDbAssocPersSubentId::isEqualTo(pEntity, pOther))
      return false;

    OdTvDbAssocAsmBasedEntityPersSubentIdPtr pOtherIndex = pOther;
    return m_SubentId == pOtherIndex->m_SubentId;
  }

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

  /** \details
  Provides the standard audit protocol.
  */
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);

protected:
  /*!DOM*/
  bool m_Unk_Bool_1;
private:
  /*!DOM*/
  OdDbSubentId m_SubentId;
};


#include "TD_PackPop.h"

#endif


