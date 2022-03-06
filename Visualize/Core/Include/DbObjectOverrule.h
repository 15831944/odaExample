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

#ifndef _DBOBJECTOVERRULE_H_INCLUDED_
#define _DBOBJECTOVERRULE_H_INCLUDED_

#include "RxOverrule.h"
#include "TD_PackPush.h"
#include "DbObject.h"

/** \details
  This class overrules a subset of operations which an object of a database specifies. 
  It is used as a base class for classes derived from OdTvDbObject to change their behavior. 
  Each default implementation calls the corresponding method of the target class.
    
  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbObjectOverrule();

  /** \details
    Overrules the OdTvDbObject::subOpen() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an object.
    \param mode [in]  A mode to be opened in.
  */
  virtual OdResult open(OdTvDbObject* pSubject, OdDb::OpenMode mode);

  /** \details
    Overrules the OdTvDbObject::subClose() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an object.
  */
  virtual OdResult close(OdTvDbObject* pSubject);

  /** \details
    Overrules the OdTvDbObject::subErase() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an object.
    \param erasing [in]  An erase status mode that was passed in the erase() method.
  */
  virtual OdResult erase(OdTvDbObject* pSubject, bool erasing);

  /** \details
    Overrules the OdTvDbObject::subDeepClone() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an object.
    \param idMap [in]  A current object ID map.
  */
  virtual OdTvDbObjectPtr deepClone(const OdTvDbObject* pSubject, OdTvDbIdMapping& idMap, OdTvDbObject* pOwner, bool bPrimary = true);

  /** \details
    Overrules the OdTvDbObject::subWblockClone() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an object.
    \param idMap [in]  A current object ID map.
  */
  virtual OdTvDbObjectPtr wblockClone(const OdTvDbObject* pSubject, OdTvDbIdMapping& idMap, OdTvDbObject* pOwner, bool bPrimary = true);
};

/** \details
  This class overrules a subset of property linked operations which an object or entity specifies. 
  It is used as a base class for classes derived from OdTvDbObject or OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.
    
  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbPropertiesOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbPropertiesOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbPropertiesOverrule();

  /** \details
    Overrules the OdTvDbObject::subGetClassID() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an object or entity.
    \param pClsid [out]  A pointer to the corresponding COM wrapper class ID.
  */
  virtual OdResult getClassID(const OdTvDbObject* pSubject, void* pClsid);

  /** \details
    Overrules the OdTvDbEntity::subList() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
  */
  virtual void list(const OdTvDbEntity* pSubject);
};

#include "TD_PackPop.h"

#endif //_DBOBJECTOVERRULE_H_INCLUDED_
