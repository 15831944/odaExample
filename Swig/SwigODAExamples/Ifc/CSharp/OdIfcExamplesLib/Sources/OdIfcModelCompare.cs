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
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Teigha.Core;
using ODA.Ifc.IfcCore;
using ODA.Sdai.sdai;

namespace OdIfcExamplesLibMgd
{
  public class OdIfcModelCompare
  {
    public static bool CompareModels(OdDAI_Model modelLeft, OdDAI_Model modelRight)
    {
      if (modelLeft == null || modelRight == null)
      {
        Console.WriteLine("\nInvalid model parameters.");
        return false;
      }

      OdDAI_InstanceIterator leftIterator = modelLeft.newIterator();
      OdDAI_InstanceIterator rightIterator = modelRight.newIterator();

      while (!leftIterator.done())
      {
        OdIfc_OdIfcEntity leftEntity = OdIfc_OdIfcEntity.cast(leftIterator.id().openObject());
        if (rightIterator.done())
        {
          Console.WriteLine("\nCan not seek to the next entity in right: {0}.", leftIterator.id().getHandle().ToUInt64());
          return false;
        }

        OdDAIObjectId id = leftIterator.id();
        OdDbHandle currentHandle = id.getHandle();

        OdIfc_OdIfcEntity rightEntity = OdIfc_OdIfcEntity.cast(rightIterator.id().openObject());
        if (rightEntity == null || leftEntity == null)
        {
          Console.WriteLine("\nIterator error.");
          return false;
        }

        if (rightEntity.comparedTo(leftEntity) != Ordering.kEqual)
        {
          Console.WriteLine("[ does not equal ] ");
          Console.WriteLine("  right - {0}({1}) ", rightEntity.typeName(), new OdDAIObjectId(rightEntity.id()).getHandle());
          Console.WriteLine("  left  - {0}({1}) \r\n", leftEntity.typeName(), new OdDAIObjectId(rightEntity.id()).getHandle());
          break;
        }

        rightIterator.step();
        leftIterator.step();
      }

      if (!rightIterator.done())
      {
        Console.WriteLine("\nRight file differs of left.");
        return false;
      }

      return true;
    }


    public static bool CompareHeaders(OdDAI_OdHeaderSection headerSectionLeft, OdDAI_OdHeaderSection headerSectionRight)
    {
      return
        HeaderEntitiesCompare<OdDAI_FileDescription>(headerSectionLeft, headerSectionRight, OdDAI_OdHeaderEntityType.kFileDescription) &&
        HeaderEntitiesCompare<OdDAI_FileName>(headerSectionLeft, headerSectionRight, OdDAI_OdHeaderEntityType.kFileName) &&
        HeaderEntitiesCompare<OdDAI_FileSchema>(headerSectionLeft, headerSectionRight, OdDAI_OdHeaderEntityType.kFileSchema);
    }

    private static bool HeaderEntitiesCompare<HeaderEntity>(OdDAI_OdHeaderSection headerSectionLeft, OdDAI_OdHeaderSection headerSectionRight, OdDAI_OdHeaderEntityType HeaderSectionType)
      where HeaderEntity : OdDAI_ApplicationInstance
    {
      if (headerSectionLeft == null || headerSectionRight == null)
      {
        Console.WriteLine("\nHeader section is null.");
        return false;
      }

      OdDAI_ApplicationInstance entityLeft = headerSectionLeft.getEntityByType(HeaderSectionType);
      OdDAI_ApplicationInstance entityRight = headerSectionRight.getEntityByType(HeaderSectionType);

      if (entityLeft == null || entityRight == null)
      {
        Console.WriteLine("\nHeader entity is null.");
        return false;
      }

      HeaderEntity left = Cast<HeaderEntity>(entityLeft);
      HeaderEntity right = Cast<HeaderEntity>(entityRight);

      return IsEqual<HeaderEntity>(left, right);
    }

    private static Dictionary<Type, MethodInfo> type2IsEqualMethodCache = new Dictionary<Type, MethodInfo>();

    private static bool IsEqual<HeaderEntity>(HeaderEntity left, HeaderEntity right)
    {
      MethodInfo isEqual = null;
      if (!type2IsEqualMethodCache.TryGetValue(typeof(HeaderEntity), out isEqual))
      {
        MethodInfo[] IsEqualMethods = GetMethods<sdai_Globals>("IsEqual");
        isEqual = IsEqualMethods.FirstOrDefault(xMethod =>
        xMethod.ReturnParameter.ParameterType == typeof(bool) &&
        xMethod.GetParameters().Count() == 2 &&
        xMethod.GetParameters()[0].ParameterType == xMethod.GetParameters()[0].ParameterType &&
        xMethod.GetParameters()[0].ParameterType == typeof(HeaderEntity));

        type2IsEqualMethodCache.Add(typeof(HeaderEntity), isEqual);
      }
      return (bool)isEqual.Invoke(null, new object[] { left, right });
    }

    private static MethodInfo[] GetMethods<TFromTypeFind>(String methodName)
    {
      return typeof(TFromTypeFind).GetMethods().Where(xMethod => xMethod.Name == methodName).ToArray();
    }

    private static HeaderEntity Cast<HeaderEntity>(OdRxObject entityLeft)
      where HeaderEntity : OdDAI_ApplicationInstance
    {
      Type type = typeof(HeaderEntity);
      var method = type.GetMethod("cast");
      return method.Invoke(null, new object[] { entityLeft }) as HeaderEntity;
    }
  }
}