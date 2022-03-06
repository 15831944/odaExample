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




#ifndef OD_DBOLE_H
#define OD_DBOLE_H

#include "TD_PackPush.h"

#include "DbFrame.h"
#include "DbObject.h"
#include "DwgDeclareMembers.h"

/** \details
    This class is the abstract base class for OdTvDbOle2Frame graphical entities 
    contained in an OdTvDbDatabase instance.
    
    \sa
    TD_Db
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbOleFrame : public OdTvDbFrame
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbOleFrame);

  OdTvDbOleFrame();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbOleFrame object pointers.
*/
typedef OdSmartPtr<OdTvDbOleFrame> OdTvDbOleFramePtr;

#include "TD_PackPop.h"

#endif // OD_DBOLE_H_
