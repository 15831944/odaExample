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


#ifndef _ODBOOLEANCOMMAND_INCLUDED_
#define _ODBOOLEANCOMMAND_INCLUDED_

#include "Ed/EdCommandStack.h"
#include "ModelerDefs.h"

class UnionCommand : public OdEdCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("Union");
  }

  void execute(OdEdCommandContext* pCmdCtx);
};

//TODO: support OdDbCurve, OdDbPoint intersections with OdDbEntity (acad doesn't support it)
//if intersection is empty, we erase input entities (unlike acad)
class IntersectCommand : public OdEdCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("Intersect");
  }

  void execute(OdEdCommandContext* pCmdCtx);
};

//TODO: support OdDbCurve, OdDbPoint subtraction with OdDbEntity (acad doesn't support it)
//if subtraction is empty, we erase input entities (unlike acad)
class SubtractCommand : public OdEdCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("Subtract");
  }

  void execute(OdEdCommandContext* pCmdCtx);
};

class BooleanExCommand : public OdEdCommand
{
protected:
  void execute(OdEdCommandContext* pCmdCtx, OdDb::BoolOperType operationType);
};

class UnionExCommand : public BooleanExCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("UnionEx");
  }

  void execute(OdEdCommandContext* pCmdCtx)
  {
    BooleanExCommand::execute(pCmdCtx, OdDb::kBoolUnite);
  }
};

class IntersectExCommand : public BooleanExCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("IntersectEx");
  }

  void execute(OdEdCommandContext* pCmdCtx)
  {
    BooleanExCommand::execute(pCmdCtx, OdDb::kBoolIntersect);
  }
};

class SubtractExCommand : public BooleanExCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("SubtractEx");
  }

  void execute(OdEdCommandContext* pCmdCtx)
  {
    BooleanExCommand::execute(pCmdCtx, OdDb::kBoolSubtract);
  }
};

class IntersectSurfCommand : public OdEdCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("IntersectSurf");
  }

  void execute(OdEdCommandContext* pCmdCtx);
};

class SculptCommand : public OdEdCommand
{
public:
  const OdString groupName() const
  {
    return OD_T("MODELER GEOMETRY");
  }
  const OdString globalName() const
  {
    return OD_T("Sculpt");
  }

  void execute(OdEdCommandContext* pCmdCtx);
};

#endif //_ODBOOLEANCOMMAND_INCLUDED_
