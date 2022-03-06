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

#include "OdaCommon.h"
#include "sdai.h"
#include <vector>

// Use some other external point struct for geometry representation
struct PointF
{
  double X;
  double Y;
};


class RailProfileDef
{
public:
  RailProfileDef(double scaleFactor);

  bool buildProfile(SdaiModel model, SdaiAppInstance profileDefinition);

private:
  void buildPoints(std::vector<PointF>& collection);

private:
  // base parameters:
  double lengthBase1 ;
  double lengthBase2 ;
  double lengthBase3 ;
  double lengthBase4 ;

  double angleBase1 ;
  double angleBase2 ;

  // web parameters:
  double lengthWeb1 ;
  double lengthWeb2 ;

  // head parameters:
  double lengthHead1;
  double lengthHead2;
  double lengthHead3;

  double angleHead1 ;
  double angleHead2 ;

};


