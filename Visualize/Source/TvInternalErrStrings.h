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

////////////////////////////////////////////////////////////
// return codes definition container

//        Code                Message string

OD_TV_INTERR_DEF( tvSuccess,           OD_T("All is OK"))
OD_TV_INTERR_DEF( tvErased,            OD_T("Object was erased"))
OD_TV_INTERR_DEF( tvNullObjectId,      OD_T("Null object Id"))
OD_TV_INTERR_DEF( tvNotOpenForRead,    OD_T("Not opened for read"))
//OD_TV_INTERR_DEF( tvNotOpenForWrite,   OD_T("Not opened for write"))
OD_TV_INTERR_DEF( tvKeyNotFound,       OD_T("Key not found"))
OD_TV_INTERR_DEF( tvNullEntityPointer, OD_T("Null entity pointer"))
OD_TV_INTERR_DEF( tvNotInDatabase,     OD_T("Object not in Database"))
OD_TV_INTERR_DEF( tvNoDatabase,        OD_T("No Database"))
OD_TV_INTERR_DEF( tvWrongDatabase,     OD_T("Wrong Database"))
OD_TV_INTERR_DEF( tvImposibleToDefineParentObj, OD_T("Impossible to define parent object"))
OD_TV_INTERR_DEF( tvAlreadyInDb, OD_T("Entity already in database under another owner"))
OD_TV_INTERR_DEF( tvDeviceHasNoContext,       OD_T("Device has zero context"))
OD_TV_INTERR_DEF( tvContextHasNoDatabase,     OD_T("Device context has zero database"))
OD_TV_INTERR_DEF( tvCannotCreateDbDatabase,     OD_T("Cannot create internal Db database"))
OD_TV_INTERR_DEF( tvCannotWriteDbDatabase,     OD_T("Cannot write internal Db database"))
OD_TV_INTERR_DEF( tvCannotReadDbDatabase,     OD_T("Cannot read internal Db database"))

