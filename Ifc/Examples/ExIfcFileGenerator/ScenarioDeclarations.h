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

//
// scenarios names container
//

class OdIfcHostAppServices;
#define FILE_GENERATOR_SCENARIO_DEF(handler, name, number) void handler(OdIfcHostAppServices* app, int curRun);

#define FILE_GENERATOR_METHOD_DATA_DECALRE() \
/*                          scenario handler                  scenario name                     runs*/  \
FILE_GENERATOR_SCENARIO_DEF(IfcCSGPrimitives,                 IfcCSGPrimitives,                 1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcFixedReferenceSweptAreaSolid,  IfcFixedReferenceSweptAreaSolid,  1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcFixedReferenceSweptAreaSolid2, IfcFixedReferenceSweptAreaSolid2, 1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcFixedReferenceSweptAreaSolid3, IfcFixedReferenceSweptAreaSolid3, 1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcSweptDiskSolid,                IfcSweptDiskSolid,                1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcAlignmentWithoutCant,          IfcAlignmentWithoutCant,          1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcAlignmentWithCant,             IfcAlignmentWithCant,             1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcSweptDiskSolidIndexedPolycurve,IfcSweptDiskSolidIndexedPolycurve,1)      \
FILE_GENERATOR_SCENARIO_DEF(IfcOpenCrossProfileDef,           IfcOpenCrossProfileDef,           1)      \

