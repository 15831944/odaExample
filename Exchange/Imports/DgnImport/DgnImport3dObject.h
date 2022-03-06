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

#ifndef _DGN_IMPORT_3DOBJECT_INCLUDED_ 
#define _DGN_IMPORT_3DOBJECT_INCLUDED_

#include "DgnImportPE.h"
#include "DbRegion.h"

namespace TD_DGN_IMPORT 
{

OdDbRegionPtr createDwgRegion( OdDgElement* pElement, OdDbBlockTableRecord* pOwner );

//------------------------------------------------------------------------------

struct OdDgnSolidImportPE : OdDgnImportPE
{
public:
  virtual bool allowImportElement(OdDgElement*) ODRX_OVERRIDE;
  virtual void subImportElement(OdDgElement*, OdDbBlockTableRecord*) ODRX_OVERRIDE;
};

//------------------------------------------------------------------------------

struct OdDgnSurfaceImportPE : OdDgnImportPE
{
public:
  virtual bool allowImportElement(OdDgElement*) ODRX_OVERRIDE;
  virtual void subImportElement(OdDgElement*, OdDbBlockTableRecord*) ODRX_OVERRIDE;
};

//------------------------------------------------------------------------------

struct OdDgnBSplineSurfaceImportPE : OdDgnImportPE
{
public:
  virtual void subImportElement(OdDgElement*, OdDbBlockTableRecord*) ODRX_OVERRIDE;
private:
  bool convertBSplineSurfaceTo3dSurface(OdDgElement* pElm, OdDbBlockTableRecord* pOwner);
};

//------------------------------------------------------------------------------

struct OdDgnConeImportPE : OdDgnImportPE
{
public:
  virtual void subImportElement(OdDgElement*, OdDbBlockTableRecord*) ODRX_OVERRIDE;
private:
  bool convertConeTo3dSolid(OdDgElement* pElm, OdDbBlockTableRecord* pOwner);
};
//------------------------------------------------------------------------------

}
#endif // _DGN_IMPORT_3DOBJECT_INCLUDED_
