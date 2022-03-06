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


///////////////////////////////////////////////////////////////////////////////
//
// ThreejsJSONExport.h - Open Design Threejs JSON Export definitions
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _THREEJSJSON_EXPORT_INCLUDED_
#define _THREEJSJSON_EXPORT_INCLUDED_

#include "DbBaseDatabase.h"

class OdStreamBuf;

/** \details
  <group OdExport_Classes> 
*/
namespace TD_THREEJSJSON_EXPORT
{

  /** \details
     Exports an element to ThreejsJSON file
     
     Input : background - color of scene background
             bFacesEnabled - if true, export to JSON with faces, else - with lines and points
     Output: pOutStream - output stream (file stream, memory stream)
    
     Return : eOk is ok
              or OdResult error code
  */
  OdResult exportThreejsJSON(OdDbBaseDatabase *pDb, OdStreamBuf *pOutStream, const ODCOLORREF &background, bool bFacesEnabled = false);

};

#endif // _THREEJSJSON_EXPORT_INCLUDED_

