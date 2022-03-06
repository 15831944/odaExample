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




#ifndef _ODDBDATABASEREACTOR_INCLUDED_
#define _ODDBDATABASEREACTOR_INCLUDED_

#include "TD_PackPush.h"

#include "RxObject.h"
#include "IdArrays.h"

/** \details
    This class is the base class for custom classes that receive notification
    of OdTvDbDatabase events.
    
    \remarks
    Events consist of the addition, modification, or deletion of objects 
    from an OdTvDbDatabase instance.
    
    \remarks
    The default implementations of all methods in this class do nothing.

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDatabaseReactor : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbDatabaseReactor);
  
  OdTvDbDatabaseReactor() {}
  
  /** \details
    Notification function called whenever an OdTvDbObject has been appended to an OdTvDbDatabase.
    
    \param pDb [in]  Pointer to the database being modified.
    \param pObject [in]  Pointer to the object being appended.
    
    \remarks
    This function is called after the operation.
  */
  virtual void objectAppended(
    const OdTvDbDatabase* pDb, 
    const OdTvDbObject* pObject);

  
  /** \details
    Notification function called whenever an OdTvDbObject has been unappended from an OdTvDbDatabase by an Undo operation.
    
    \param pDb [in]  Pointer to the database being modified.
    \param pObject [in]  Pointer to the object being unappended.

    \remarks
    This function is called after the operation.
  */
  virtual void objectUnAppended(
    const OdTvDbDatabase* pDb, 
    const OdTvDbObject* pObject);

  
  /** \details
    Notification function called whenever an OdTvDbObject has been reappended to an OdTvDbDatabase by a Redo operation.
    
    \param pDb [in]  Pointer to the database being modified.
    \param pObject [in]  Pointer to the object being reappended.

    \remarks
    This function is called after the operation.
  */
  virtual void objectReAppended(
    const OdTvDbDatabase* pDb, 
    const OdTvDbObject* pObject);

  
  /** \details
    Notification function called whenever an OdTvDbObject is about to be modified.
    
    \param pDb [in]  Pointer to the database being modified.
    \param pObject [in]  Pointer to the object being modified.
    
    \remarks
    This function is called before the operations.
    
    \sa
    objectModified
  */
  virtual void objectOpenedForModify(
    const OdTvDbDatabase* pDb, 
    const OdTvDbObject* pObject);

  
  /** \details
    Notification function called whenever an OdTvDbObject has been modified.
    
    \param pDb [in]  Pointer to the database being modified.
    \param pObject [in]  Pointer to the object being modified.
    
    \remarks
    This function is called after the operations.

    \sa
    objectOpenedForModify
  */
  virtual void objectModified(
    const OdTvDbDatabase* pDb, 
    const OdTvDbObject* pObject);
    
  
  /** \details
    Notification function called whenever an OdTvDbObject has been erased or unerased.
    
    \param pDb [in]  Pointer to the database being modified.
    \param pObject [in]  Pointer to the object being modified.
    \param erased [in]  True if and only if the object is being erased.
    
    \remarks
    This function is called after the operation.
  */
  virtual void objectErased(
    const OdTvDbDatabase* pDb, 
    const OdTvDbObject* pObject, 
    bool erased = true);

  /** \details
    Notification function called whenever a database -resident system variable is about to change.
    
    \param pDb [in]  Pointer to the database being modified.
    \param name [in]  Name of the system variable being modified.
    
    \remarks
    This function is called before the operation.
    
    \sa
    headerSysVarChanged
  */
  virtual void headerSysVarWillChange(
    const OdTvDbDatabase* pDb, 
    const OdString& name);

/*DOM-IGNORE-BEGIN*/    
/*!DOM*/
#define RO_VAR_DEF(type, name, d1, d2, r1, r2)
/*!DOM*/
#define RO_VAR_DEF_H(type, name, d1, d2, r1, r2)
/*!DOM*/
#define VAR_DEF(type, name, d1, d2, r1, r2)\
  /** Description: Notification function called whenever the ##NAME system variable is about to change. \
    Arguments: pDb (I) Pointer to the database being modified. \
    Remarks: This function is called before the operation. \
    Remarks: ##remarks \
    Notes: ##notes \
    See Also: ##see_also \
  */\
  SVARS_FUNC_MODIFIER void headerSysVar_##name##_WillChange(const OdTvDbDatabase* pDb);

#include "SysVarDefs.h"

#undef VAR_DEF
#undef RO_VAR_DEF
#undef RO_VAR_DEF_H

/*!DOM*/
#define VAR_DEF(type, name, dxf, d1, d2, r1, r2)\
  /** Description: Notification function called whenever the DIM##NAME system variable is about to change. \
    Arguments: pDb (I) Pointer to the database being modified. \
    Remarks: This function is called before the operation. \
    Remarks: ##remarks \
    Notes: ##notes \
    See Also: ##see_also \
  */ \
  virtual void headerSysVar_dim##name##_WillChange(const OdTvDbDatabase* pDb);

#include "DimVarDefs.h"
#undef VAR_DEF
/*DOM-IGNORE-END*/

  /** \details
    Notification function called whenever a database -resident system variable has changed.
    
    \param pDb [in]  Pointer to the database being modified.
    \param name [in]  Name of the system variable being modified.
    
    \remarks
    This function is called after the operation.
    
    \sa
    headerSysVarWillChange
  */
  virtual void headerSysVarChanged(
    const OdTvDbDatabase* pDb, 
    const OdString& name);

/*DOM-IGNORE-BEGIN*/
/*!DOM*/
#define VAR_DEF(type, name, d1, d2, r1, r2)\
  /** Description: Notification function called whenever the ##NAME system variable has been changed. \
    Arguments: pDb (I) Pointer to the database being modified. \
    Remarks: This function is called after the operation. \
    Remarks: ##remarks \
    Notes: ##notes \
    See Also: ##see_also \
  */ \
  SVARS_FUNC_MODIFIER void headerSysVar_##name##_Changed(const OdTvDbDatabase* pDb);

#include "SysVarDefs.h"

#undef VAR_DEF

/*!DOM*/
#define VAR_DEF(type, name, dxf, d1, d2, r1, r2)\
  /** Description: Notification function called whenever the DIM##NAME system variable has been changed. \
    Arguments: pDb (I) Pointer to the database being modified. \
    Remarks: This function is called after the operation. \
    Remarks: ##remarks \
    Notes: ##notes \
    See Also: ##see_also \
  */ \
  virtual void headerSysVar_dim##name##_Changed(const OdTvDbDatabase* pDb);

#include "DimVarDefs.h"
#undef VAR_DEF
/*DOM-IGNORE-END*/

  /** \details
    Notification function called after the specified application is loaded and all its proxy
    objects are resurrected.
    
    \param pDb [in]  Pointer to the database being modified.
    \param appname [in]  Name of the resurrecting application.
    \param objectIds [in]  Object IDs of the resurrected objects.
  */
  virtual void proxyResurrectionCompleted(
    const OdTvDbDatabase* pDb,
    const OdString& appname, 
    OdTvDbObjectIdArray& objectIds);

  /** \details
    Notification function called whenever a database is about to be deleted from memory.
    \param pDb [in]  Pointer to the database being deleted.

    \remarks
    This function is called before the operation.
  */
  virtual void goodbye(
    const OdTvDbDatabase* pDb);
};
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDatabaseReactor object pointers.
*/
typedef OdSmartPtr<OdTvDbDatabaseReactor> OdTvDbDatabaseReactorPtr;

#include "TD_PackPop.h"

#endif // _ODDBDATABASEREACTOR_INCLUDED_
