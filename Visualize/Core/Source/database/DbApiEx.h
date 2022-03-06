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


#ifndef OD_DBDICTIONARYVAR_H
template <class T> class OdSmartPtr;
class OdTvDbDictionaryVar;
typedef OdSmartPtr<OdTvDbDictionaryVar> OdTvDbDictionaryVarPtr;
#endif

class OdTvDbSpatialFilter;
class OdTvDbLeader;



#ifndef DBAPIEX_DEFINED
#define DBAPIEX_DEFINED


/** Get OdTvDbDictionaryVar object given variable name.
    Note: Recommended method for getting/setting variable values stored in OdTvDbDictionaryVar
    objects is using OdTvDbDatabase::getXXX() / OdTvDbDatabase::setXXX() (like getXCLIPFRAME()).
    getXXX() methods take care about default value if corresponding OdTvDbDictionaryVar
    object is absent.
    @param pDb (I) Pointer to OdTvDbDatabase.
    @param name (I) Variable name
    @param mode (I) Open mode (kForRead or OdDb::kForWrite)
    @return Smart pointer to OdTvDbDictionaryVar object. If mode is OdDb::kForRead may return null pointer.
    If mode is OdDb::kForWrite always returns valid pointer (possibly to newly created and propery added
    to database object)
*/
TOOLKIT_EXPORT OdTvDbDictionaryVarPtr odDbGetDictionaryVar(const OdTvDbDatabase * pDb, 
                                                         const OdString& name,
                                                         OdDb::OpenMode mode);

/* Get & set Spatial Filter object transformations */
TOOLKIT_EXPORT void odDbGetSpatialFilterMatrices (const OdTvDbSpatialFilter& filter, OdGeMatrix3d& inverseBlockMatrix, OdGeMatrix3d& clipBoundMatrix);
TOOLKIT_EXPORT void odDbSetSpatialFilterMatrices (OdTvDbSpatialFilter& filter, OdGeMatrix3d& inverseBlockMatrix, OdGeMatrix3d& clipBoundMatrix);


/* Set Leader's annotation type (DXF group code 73) */
DBENT_EXPORT void odDbSetLeaderAnnoType(OdTvDbLeader&, int);
/* Set leader hasHookline flag (DXF group code 75) */
DBENT_EXPORT void odDbSetLeaderHookLine(OdTvDbLeader&, bool hasHookline);

#endif

