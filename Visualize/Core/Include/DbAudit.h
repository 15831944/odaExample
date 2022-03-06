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




#ifndef _ODDB_AUDIT_INCLUDED_
#define _ODDB_AUDIT_INCLUDED_

#include "TD_PackPush.h"

#include "DbExport.h"

#include "OdString.h"
#include "CmColor.h"
#include "OdAuditInfo.h"

class OdTvDbObject;
class OdTvDbObjectId;
class OdTvDbDatabase;
class OdDbHandle;
class OdTvDbHostAppServices;

TOOLKIT_EXPORT OdString odTvDbGetObjectName(const OdTvDbObject* pObj);
TOOLKIT_EXPORT OdString odTvDbGetObjectIdName(const OdTvDbObjectId& id);
TOOLKIT_EXPORT OdString odTvDbGetHandleName(const OdDbHandle& handle);
TOOLKIT_EXPORT OdString odTvDbGenerateName(const OdTvDbObjectId& id, OdTvDbHostAppServices* pHostApp = 0);
TOOLKIT_EXPORT OdString odTvDbGenerateName(OdUInt32 i, OdTvDbHostAppServices* pHostApp = 0);
TOOLKIT_EXPORT bool     odTvDbAuditColorIndex(OdInt16& colorIndex, OdTvDbAuditInfo* pAuditInfo, OdTvDbHostAppServices* pHostApp = 0);
TOOLKIT_EXPORT bool     odTvDbAuditColorIndex(OdInt16& colorIndex, OdTvDbAuditInfo* pAuditInfo, OdTvDbHostAppServices* pHostApp, OdTvDbObject* pObj, unsigned int sid, unsigned int n);
TOOLKIT_EXPORT bool     odTvDbAuditColor(OdTvCmColor& color, OdTvDbAuditInfo* pAuditInfo, OdTvDbHostAppServices* pHostApp = 0);
TOOLKIT_EXPORT bool     odTvDbAuditColor(OdTvCmColor& color, OdTvDbAuditInfo* pAuditInfo, OdTvDbHostAppServices* pHostApp, OdTvDbObject* pObj, unsigned int sid, unsigned int n);

/** \details
  This class tracks audit information during a database audit.

  \sa
  TD_Db

  <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbAuditInfo : public OdAuditInfo
{
public:
  /** \details
    Notification function called to print error information.
    \remarks
    Prints log information about an error detected or fixed during an audit.

    \param name [in] Type of erroneous data found.
    \param value [in] Value of the bad data.
    \param validation [in] Reason the data were bad.
    \param defaultValue [in] Default value to which the were set.

    \remarks
    As implemented, this functions does nothing.
  */
  virtual void printError(
    const OdString& name,
    const OdString& value,
    const OdString& validation = OdString::kEmpty,
    const OdString& defaultValue = OdString::kEmpty );

  /** \details
    Notification function called to print error information.

    \param pObject [in]  Pointer to the object which generated the error.
    \param value [in] Value of the bad data.
    \param validation [in] Reason the data were bad.
    \param defaultValue [in] Default value to which the were set.
    
    \remarks
    odTvDbGetObjectName(pObject) is used to generate the name.
  */
  virtual void printError(
    const OdRxObject* pObject,
    const OdString& value,
    const OdString& validation = OdString::kEmpty,
    const OdString& defaultValue = OdString::kEmpty);
};

#include "TD_PackPop.h"

#endif // _ODDB_AUDIT_INCLUDED_

