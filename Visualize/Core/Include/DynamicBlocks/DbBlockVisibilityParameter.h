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

#ifndef _DbBlockVisibilityParameter_h_Included_
#define _DbBlockVisibilityParameter_h_Included_

#include "DbBlock1PtParameter.h"

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockVisibilityParameter : public OdTvDbBlock1PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockVisibilityParameter);
  OdTvDbBlockVisibilityParameter();
  bool isInitialized() const;
  void setInitiaized(bool);
  int currentVisibilityState()const;
  void setCurrentVisibilityState(int);
  void clearListOfVisibilityStates();
  OdString visibilityName() const;
  void setVisibilityName(const OdString&);
  OdString visibilityDescription() const;
  void setVisibilityDescription(const OdString&);
  void blockEntityList( OdTvDbObjectIdArray& ) const;
  void setBlockEntityList( OdTvDbObjectIdArray& );
  int numberOfVisibilityStates() const;
  void visibilityState(int index, OdString& name, OdTvDbObjectIdArray& objects, OdTvDbObjectIdArray& elements);
  void setVisibilityState(int index,const OdString& name, const OdTvDbObjectIdArray& objects, const OdTvDbObjectIdArray& elements);
  virtual void getPropertyDescription(OdTvDbBlkParamPropertyDescriptorArray& ) const ODRX_OVERRIDE;
  void listVisibleEntities( OdTvDbObjectIdArray& ) const;
  virtual void setMemberOfCurrentVisibilitySet(bool) ODRX_OVERRIDE {}
};
typedef OdSmartPtr<OdTvDbBlockVisibilityParameter> OdTvDbBlockVisibilityParameterPtr;

#endif // _DbBlockVisibilityParameter_h_Included_
