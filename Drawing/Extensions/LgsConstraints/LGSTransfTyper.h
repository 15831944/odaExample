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
#ifndef LGSTransfTyper_INCLUDED_
#define LGSTransfTyper_INCLUDED_

#include "TD_PackPush.h"

#include "LGSConstraintsExport.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeVector3d.h"
#include "Ge/GeMatrix3d.h"

/** <group Extension_Classes>
*/
class LGSCONSTRAINTS_EXPORT LGSTransfTyper
{
public:
  enum TransformationType
  {
    TransTypeMove,
    TransTypeRotate,
    TransTypeNo,
    TransTypeComposite
  };

  LGSTransfTyper();
  LGSTransfTyper(const OdGeVector3d& move);
  LGSTransfTyper(const OdGePoint3d& center, const double& ang);

  bool isFitTransform(const OdGePoint3d& src, const OdGePoint3d& dst);

  bool isSimpleTypeTransformation() const;

  TransformationType getType() const;
  void setType(TransformationType type);
  

  bool getMoveParam(OdGeVector3d& move);
  bool getRotateParam(OdGePoint3d& center, double& ang);
private:
  TransformationType m_type;

  OdGeVector3d m_move;
  OdGePoint3d m_center;
  double m_ang;

  OdGeMatrix3d m_matr;
};

#include "TD_PackPop.h"

#endif
