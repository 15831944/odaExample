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

#ifndef _DbBlock1PtParameter_h_Included_
#define _DbBlock1PtParameter_h_Included_

#include "DbBlockParameter.h"

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlock1PtParameter : public OdTvDbBlockParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlock1PtParameter);
  OdTvDbBlockGripPtr getAssociatedGrip( OdDb::OpenMode );
  virtual void graphEvalEnd(bool);
  OdGePoint3d definitionPoint() const;
  void setDefinitionPoint( const OdGePoint3d& );
  OdGePoint3d point();
  void setPoint( const OdGePoint3d& );
  OdGePoint3d updatedPoint();
  void setUpdatedPoint( const OdGePoint3d& );
};

typedef OdSmartPtr<OdTvDbBlock1PtParameter> OdTvDbBlock1PtParameterPtr;

#endif // _DbBlock1PtParameter_h_Included_
