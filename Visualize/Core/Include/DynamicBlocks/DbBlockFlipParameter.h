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

#ifndef _DbBlockFlipParameter_h_Included_
#define _DbBlockFlipParameter_h_Included_

#include "DbBlock2PtParameter.h"

class OdTvDbBlockFlipGrip;
typedef OdSmartPtr<OdTvDbBlockFlipGrip> OdTvDbBlockFlipGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockFlipParameter : public OdTvDbBlock2PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockFlipParameter);
  OdTvDbBlockFlipParameter();
  enum FlipState{ NotFlipped = 0, Flipped };

  FlipState flipState() const;
  void setFlipState(FlipState);
  FlipState updatedFlipState() const;
  void setUpdatedFlipState(FlipState);
  virtual void graphEvalEnd(bool);
  OdString flipLabel() const;
  void setFlipLabel(const OdString &);
  OdString flipLabelDescription()const;
  void setFlipLabelDescription(const OdString &);
  OdString baseStateLabel() const;
  void setBaseStateLabel(const OdString &);
  OdString flippedStateLabel()const;
  void setFlippedStateLabel(const OdString &);
  OdGePoint3d definitionLabelPoint() const;
  void setDefinitionLabelPoint(const OdGePoint3d &);
  OdTvDbBlockFlipGripPtr  getAssociatedFlipGrip( OdDb::OpenMode );
};

typedef OdSmartPtr<OdTvDbBlockFlipParameter>OdTvDbBlockFlipParameterPtr;

#endif // _DbBlockFlipParameter_h_Included_
