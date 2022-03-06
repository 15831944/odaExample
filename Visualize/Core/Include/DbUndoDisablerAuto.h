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




#ifndef _ODDBUNDODISABLERAUTO_
#define _ODDBUNDODISABLERAUTO_

#include "TD_PackPush.h"

/** \details
    This class, for the duration of its existence,
    disables Undo Recording for its associated object.
    
    <group OdTvDb_Classes>
*/
class OdTvDbUndoDisablerAuto
{
  OdTvDbObject* m_pObj;
public:
  /** \details
    Constructor -- Disables Undo recording.
  */
  /** \param pObj [in]  Pointer to the object whose Undo Recording is to be disabled.
  */
  OdTvDbUndoDisablerAuto(OdTvDbObject* pObj)
    : m_pObj(pObj)
  {
    if (pObj != NULL)
    {
      pObj->disableUndoRecording(true);
    }
  }
  /** \details
    Destructor -- Enables Undo recording.
  */
  ~OdTvDbUndoDisablerAuto()
  {
    if (m_pObj != NULL)
    {
      m_pObj->disableUndoRecording(false);
    }
  }
};

#include "TD_PackPop.h"

#endif //#ifndef _ODDBUNDODISABLERAUTO_
