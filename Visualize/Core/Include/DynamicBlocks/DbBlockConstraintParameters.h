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

#ifndef _DbBlockConstraintParameter_h_Included_
#define _DbBlockConstraintParameter_h_Included_

#include "DbBlock2PtParameter.h"
#include "DbBlockParamValueSet.h"

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockConstraintParameter : public OdTvDbBlock2PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockConstraintParameter);
  OdTvDbObjectId dependency();
  void setDependency(OdTvDbObjectId id);
};

typedef OdSmartPtr<OdTvDbBlockConstraintParameter> OdTvDbBlockConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockLinearConstraintParameter : public OdTvDbBlockConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockLinearConstraintParameter);
  OdTvDbBlockLinearConstraintParameter();
  OdString description() const;
  void setDescription(const OdString&);
  double value() const;
  void setValue(double v);
  const OdTvDbBlockParamValueSet& valueSet() const;
  void setValueSet(const OdTvDbBlockParamValueSet&);
};

typedef OdSmartPtr<OdTvDbBlockLinearConstraintParameter> OdTvDbBlockLinearConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockHorizontalConstraintParameter : public OdTvDbBlockLinearConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockHorizontalConstraintParameter);
  OdTvDbBlockHorizontalConstraintParameter();
};

typedef OdSmartPtr<OdTvDbBlockHorizontalConstraintParameter> OdTvDbBlockHorizontalConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockVerticalConstraintParameter : public OdTvDbBlockLinearConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockVerticalConstraintParameter);
  OdTvDbBlockVerticalConstraintParameter();
};

typedef OdSmartPtr<OdTvDbBlockVerticalConstraintParameter> OdTvDbBlockVerticalConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockAlignedConstraintParameter : public OdTvDbBlockLinearConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockAlignedConstraintParameter);
  OdTvDbBlockAlignedConstraintParameter();
};

typedef OdSmartPtr<OdTvDbBlockAlignedConstraintParameter> OdTvDbBlockAlignedConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockAngularConstraintParameter : public OdTvDbBlockConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockAngularConstraintParameter);
  OdTvDbBlockAngularConstraintParameter();
};

typedef OdSmartPtr<OdTvDbBlockAngularConstraintParameter> OdTvDbBlockAngularConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockDiametricConstraintParameter : public OdTvDbBlockConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockDiametricConstraintParameter);
  OdTvDbBlockDiametricConstraintParameter();
};

typedef OdSmartPtr<OdTvDbBlockDiametricConstraintParameter> OdTvDbBlockDiametricConstraintParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockRadialConstraintParameter : public OdTvDbBlockConstraintParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockRadialConstraintParameter);
  OdTvDbBlockRadialConstraintParameter();
};

typedef OdSmartPtr<OdTvDbBlockRadialConstraintParameter> OdTvDbBlockRadialConstraintParameterPtr;

#endif //_DbBlockConstraintParameter_h_Included_
