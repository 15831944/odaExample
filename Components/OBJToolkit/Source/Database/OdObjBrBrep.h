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

// OdObjBrBrep.h: interface for the OdObjBrBody class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRBODY_H_INCLUDED_)
#define TEIGHA_ODOBJBRBODY_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"
#include "OBJToolkit.h"
#include "../DevInclude/IBr/IBrBrep.h"
#include "OdObjBrFile.h"
#include "OdObjBrComplex.h"
namespace OBJToolkit
{
  class OdObjBrFile;
  class OdObjBrComplex;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrBrep
  // Description: the class encapsulates information about the major topology class for OBJ data
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrBrep : public OdIBrBrep
  {
  protected:
    OdObjBrComplex *m_pComplex; 
    OdObjBrFile *m_pFile;

  public:
    ~OdObjBrBrep();
    OdObjBrBrep();

    virtual bool getTransformation(OdGeMatrix3d& m) const;

    void setComplex(OdObjBrComplex* pComplex);
    OdObjBrComplex* getComplex();

    void setFile(OdObjBrFile *file);
    OdObjBrFile* getFile();
  };

}

#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRBODY_H_INCLUDED_)

