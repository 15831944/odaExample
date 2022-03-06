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

#ifndef _DbBlockXYParameter_h_Included_
#define _DbBlockXYParameter_h_Included_

#include "DbBlock2PtParameter.h"
#include "DbBlockParamValueSet.h"

class OdTvDbBlockXYGrip;
typedef OdSmartPtr<OdTvDbBlockXYGrip>OdTvDbBlockXYGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockXYParameter : public OdTvDbBlock2PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockXYParameter);
  OdTvDbBlockXYParameter();
  //double definitionHorzDistance()const;
  //double definitionVertDistance()const;
  OdTvDbBlockXYGripPtr getAssociatedXYGrip(OdTvDbBlockParameter::ParameterComponent,OdDb::OpenMode);
  //OdString horzDescription() const;
  //double horzDistance()const;
  //OdString horzName()const;
  //void setDefinitionHorzDistance(double);
  //void setDefinitionVertDistance(double);
  //void setHorzDescription(const OdString&);
  //void setHorzDistance(double);
  //void setHorzName(const OdString&);
  //void setUpdatedHorzDistance(double);
  //void setUpdatedVertDistance(double);
  //void setVertDescription(const OdString&);
  //void setVertDistance(double);
  //void setVertName(const OdString&);
  //void setXOffset(double);
  //void setXValueSet(const OdTvDbBlockParamValueSet &);
  //void setYOffset(double);
  //void setYValueSet(const OdTvDbBlockParamValueSet &);
  //double updatedHorzDistance() const;
  //double updatedVertDistance() const;
  //OdString  vertDescription() const;
  //double vertDistance() const;
  //OdString  vertName() const;
  //double XOffset() const;
  //const OdTvDbBlockParamValueSet& xValueSet() const;
  //double YOffset() const;
  //const OdTvDbBlockParamValueSet& yValueSet() const;
};

#endif // _DbBlockXYParameter_h_Included_
