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

#ifndef _DbBlockLinearParameter_h_Included_
#define _DbBlockLinearParameter_h_Included_

#include "DbBlock2PtParameter.h"
#include "DbBlockParamValueSet.h"

class OdTvDbBlockLinearGrip;
typedef OdSmartPtr<OdTvDbBlockLinearGrip> OdTvDbBlockLinearGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockLinearParameter : public OdTvDbBlock2PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockLinearParameter);
  OdTvDbBlockLinearParameter();
  //OdString distanceDescription() const;
  //OdString distanceName() const;
  //OdTvDbBlockLinearGripPtr getAssociatedLinearGrip( OdTvDbBlockParameter::ParameterComponent, OdDb::OpenMode );
  //double offset() const;
  //void setDistanceDescription( const OdString& );
  //void setDistanceName( const OdString& );
  //void setOffset(double);
  //void setUpdatedDistance(double);
  void setValueSet(const OdTvDbBlockParamValueSet&);
  const OdTvDbBlockParamValueSet& valueSet() const;
  void stretch(const OdGeMatrix3d& m);
};

#endif //_DbBlockLinearParameter_h_Included_