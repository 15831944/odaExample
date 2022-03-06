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

using System;
using Teigha.Core;

namespace ExIfcCDAWalkerSwigMgd
{
  public class OdExCDATreePrinter : OdExAbstractNotifier
  {
    int m_level;

    public OdExCDATreePrinter()
    { m_level = 0; }

    public override void onLevelBegin(OdRxObject inst)
    {
      ++m_level;

      Console.WriteLine("{0}Hierarchy level: {1}\n", tabulation(m_level), m_level);

      String className = inst.isA().name();
      Console.WriteLine("{0}Class: {1}\n", tabulation(m_level), className);

      String entityName = String.Empty;

      OdRxProperty propName = OdRxProperty.cast(OdRxMemberQueryEngine.theEngine().find(inst, "Name"));
      if (propName != null)
      {
        OdRxValue valName = OdRxValue.create();

        if (OdResult.eOk == propName.getValue(inst, valName))
          entityName = OdRxValueHelper.rxvalue_cast<String>(valName);
      }

      Console.WriteLine("{0}Name: `{1}`\n", tabulation(m_level), entityName);
    }

    public override void onLevelEnd(OdRxObject inst)
    {
      --m_level;
    }

    public override void onHierarchyAttributeFound(OdRxObject inst, OdRxMember member)
    {
      String propName = member.name();
      Console.WriteLine("{0}Hierarchy property name: {1}\n", tabulation(m_level), propName);
    }

    public override void onHasRepresentation(OdRxObject inst, OdRxObject reprInst)
    {
      String reprClassName = reprInst.isA().name();
      Console.WriteLine("{0}Can be vectorized here (Representation: {1})\n", tabulation(m_level), reprClassName);
      // vectorize(inst); // not reprInst
    }

    protected String tabulation(int tab)
    {
      if (tab < 0)
        tab = 0;
      return new string(' ', tab);
    }

  };

}