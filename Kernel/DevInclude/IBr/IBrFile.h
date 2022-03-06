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

#ifndef _INC_DDBRIMPFILE_3F84312B035B_INCLUDED
#define _INC_DDBRIMPFILE_3F84312B035B_INCLUDED


#include "IBrEntity.h"

class OdIBrBrep;
class OdIBrEdge;
class OdIBrVertex;
class OdIBrFace;
class OdIBrComplex;
class OdIBrShell;

class OdIBrFile : public OdIBrEntity
{

public:
  virtual void next(const OdIBrBrep *pFirstChild,  OdIBrBrep * & pCurChild) = 0;
  virtual void next(const OdIBrVertex *pFirstChild,  OdIBrVertex * & pCurChild) = 0;
  virtual void next(const OdIBrShell *pFirstChild,  OdIBrShell * & pCurChild) = 0;
  virtual void next(const OdIBrFace *pFirstChild,  OdIBrFace * & pCurChild) = 0;
  virtual void next(const OdIBrEdge *pFirstChild,  OdIBrEdge * & pCurChild) = 0;
  virtual void next(const OdIBrComplex *pFirstChild,  OdIBrComplex * & pCurChild) = 0;
  virtual OdIBrEntity* setSubentPath(OdInt32 /*type*/, OdGsMarker /*index*/) const { return 0; }
};

#endif /* _INC_DDBRIMPFILE_3F84312B035B_INCLUDED */

