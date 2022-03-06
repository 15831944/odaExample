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




#ifndef OD_DBVBAPROJECT_H
#define OD_DBVBAPROJECT_H

#include "TD_PackPush.h"

#include "DbObject.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents VBA Project objects in an OdTvDbDatabase instance.

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbVbaProject : public OdTvDbObject
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbVbaProject);

  OdTvDbVbaProject();

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** \details
    Returns the project data for this VBA Project object.

    \param vbaProject [out]  Receives the project data.
  */
  virtual void getVbaProject(OdBinaryData& vbaProject) const;

  /** \details
    Sets the project data for this VBA Project object.

    \param vbaProject [out]  Project data.
  */
  void setVbaProject(const OdBinaryData& vbaProject);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbVbaProject object pointers.
*/
typedef OdSmartPtr<OdTvDbVbaProject> OdTvDbVbaProjectPtr;

#include "TD_PackPop.h"

#endif //OD_DBVBAPROJECT_H

