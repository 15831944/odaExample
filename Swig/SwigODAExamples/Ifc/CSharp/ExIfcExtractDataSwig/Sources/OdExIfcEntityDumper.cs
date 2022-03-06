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
using ODA.Ifc.IfcCore;
using ODA.Sdai.sdai;

namespace ExIfcExtractDataSwigMgd
{

  public class OdExIfcEntityDumper
  {
    public uint inverse_aggregates = 0;
    public uint empty_inverse_aggregates = 0;

    public void dumpEntity(OdIfc_OdIfcEntity inst, OdDAI_Entity entityDef)
    {
      OdDAI_List_OdDAI_Entity__p superEntities = entityDef.supertypes();
      for (OdDAI_ConstIterator it_super = superEntities.createConstIterator(); it_super.next();)
      {
        OdDAI_Entity pEntity = OdRxValueHelper.rxvalue_cast<OdDAI_Entity>(it_super.getCurrentMember());
        dumpEntity(inst, pEntity);
      }

      String entName = entityDef.name();
      String strAbstract = entityDef.instantiable().toStr() == "T" ? "INSTANTIABLE" : "ABSTRACT";
      Console.Write("\t{0} {1}\n", strAbstract, entName);
      for (OdDAI_ConstIterator it = entityDef.attributes().createConstIterator(); it.next();)
      {
        OdDAI_Attribute pAttr = OdRxValueHelper.rxvalue_cast<OdDAI_Attribute>(it.getCurrentMember());

        String strAttrType = "UNKNOWN";
        OdDAI_ExplicitAttribute pExplicit = OdDAI_ExplicitAttribute.cast(pAttr);
        if (pExplicit != null)
        {
          strAttrType = ("EXPLICIT");
        }

        OdDAI_InverseAttribute pInverse = OdDAI_InverseAttribute.cast(pAttr);
        if (pInverse != null)
        {
          strAttrType = ("INVERSE");
        }

        OdDAI_DerivedAttribute pDerived = OdDAI_DerivedAttribute.cast(pAttr);
        if (pDerived != null)
        {
          strAttrType = ("DERIVED");
        }

        String attrName = pAttr.name();
        String attrNameW = attrName;
        Console.Write("\t\t{0} .{1}", strAttrType, attrNameW);

        OdRxValue val;
        val = inst.getAttr(attrName);

        bool unset = false;
        OdRxValueType vt = val.type();

        if (vt.IsEqual(OdRxValueTypeDesc_sdai.value_Desc_OdDAIObjectId()))
        {
          OdDAIObjectId idVal = OdRxValueHelper.rxvalue_cast<OdDAIObjectId>(val);
          if (idVal != null)
          {
            unset = sdai_Globals.OdDAI_Utils_isUnset(idVal);
            if (!unset)
            {
              UInt64 int64 = idVal.getHandle().ToUInt64();
              Console.Write(" = {0:X}", int64);
            }
          }
        }
        else
        if (vt.IsEqual(OdRxValueTypeDesc_IfcCore.value_Desc_OdIfcGUID()))
        {
          OdIfcGUID guidVal = OdRxValueHelper.rxvalue_cast<OdIfcGUID>(val);
          if (guidVal != null)
          {
            unset = sdai_Globals.OdDAI_Utils_isUnset(guidVal.ToString());
            if (!unset)
            {
              Console.Write(" = '{0}'", guidVal.ToString());
            }
          }
        }
        else
        if (vt.IsEqual(OdRxValueTypeDesc_KERNEL.value_Desc_int()))
        {
          int intVal = OdRxValueHelper.rxvalue_cast<int>(val);
          if (true)
          {
            unset = sdai_Globals.OdDAI_Utils_isUnset(intVal);
            if (!unset)
              Console.Write(" = {0}", intVal);
          }
        }
        else
        if (vt.IsEqual(OdRxValueTypeDesc_KERNEL.value_Desc_double()))
        {
          double dblVal = OdRxValueHelper.rxvalue_cast<double>(val);
          if (true)
          {
            unset = sdai_Globals.OdDAI_Utils_isUnset(dblVal);
            if (!unset)
              Console.Write(" = {0}", dblVal);
          }
        }
        else
        if (vt.IsEqual(OdRxValueTypeDesc_KERNEL.value_Desc_OdAnsiString()))
        {
          String strVal = OdRxValueHelper.rxvalue_cast<String>(val);
          if (strVal != null)
          {
            unset = sdai_Globals.OdDAI_Utils_isUnset(strVal);
            if (!unset)
            {
              String strW = strVal;
              Console.Write(" = '{0}'", strW);
            }
          }
        }
        else
        if (vt.isEnum())
        {
          String strVal = OdRxValueHelper.rxvalue_cast<String>(val);

          if (strVal != null)
          {
            unset = sdai_Globals.OdDAI_Utils_isUnset(strVal);
            if (!unset)
            {
              String enumVal = strVal;
              Console.Write(" = {0}.", enumVal);
            }
          }
        }
        else if (vt.isSelect())
        {
          OdDAI_Select select = OdRxValueHelper.rxvalue_cast<OdDAI_Select>(val);
          if (select != null)
          {
            OdTCKind selectKind = select.kind();

            unset = (selectKind == OdTCKind.tkNull);
            if (!unset)
            {
              String typePath = val.typePath();
              Console.Write(" = {0}(", typePath);

              switch (selectKind)
              {
                case OdTCKind.tkObjectId: // An object identifier's value.
                  {
                    OdDAIObjectId idVal = select.getHandle();
                    if (idVal != null)
                    {
                      UInt64 int64 = idVal.getHandle().ToUInt64();
                      Console.Write("{0:X}", int64);
                    }
                    break;
                  }
                case OdTCKind.tkLong: // An unsigned 32-bit integer value.
                  {
                    int intVal;
                    if (select.getInt32(out intVal))
                      Console.Write("{0}", (uint)intVal);
                    break;
                  }
                case OdTCKind.tkBoolean: // A boolean value.
                  {
                    OdDAI_Boolean booleanVal = new OdDAI_Boolean();
                    if (select.getBoolean(booleanVal))
                      Console.Write("{0}", booleanVal.toStr());
                    break;
                  }
                case OdTCKind.tkDouble: // A double value.
                  {
                    double dVal;
                    if (select.getDouble(out dVal))
                      Console.Write("{0}", dVal);
                    break;
                  }
                case OdTCKind.tkBinary: // A binary value.
                case OdTCKind.tkLogical: // A logical value.
                  break;
                case OdTCKind.tkString:
                  {
                    String wcsVal = "";
                    if (select.getString(ref wcsVal))
                      Console.Write("'{0}'", wcsVal);
                    break;
                  }
                case OdTCKind.tkSequence:
                  {
                    Console.Write("TODO: kSequence not implemented yet");
                    break;
                  }
                default:
                  { Console.Write("Not implemented yet."); }
                  break;

              }
              Console.Write(")");
            }
          }
        }
        else
    //if (vt == OdRxValueType.Desc<OdDAIObjectIds>.value()
    //  || vt == OdRxValueType.Desc<OdDAI_Aggr<OdDAIObjectId>* >.value())
    if (vt.isAggregate())
        {
          OdDAI_Aggr aggr = OdRxValueHelper.rxvalue_cast<OdDAI_Aggr>(val);
          if (aggr != null)
          {
            unset = aggr.isNil();
            if (!unset)
            {
              Console.Write(" = ");

              OdDAI_AggrType aggrType = aggr.aggrType();
              switch (aggrType)
              {
                case OdDAI_AggrType.aggrTypeArray:
                  Console.Write("ARRAY");
                  break;
                case OdDAI_AggrType.aggrTypeBag:
                  Console.Write("BAG");
                  break;
                case OdDAI_AggrType.aggrTypeList:
                  Console.Write("LIST");
                  break;
                case OdDAI_AggrType.aggrTypeSet:
                  Console.Write("SET");
                  break;
              }

              Console.Write("[");
              OdDAI_Iterator iterator = aggr.createIterator();
              for (iterator.beginning(); iterator.next();)
              {
                OdRxValue value = iterator.getCurrentMember();
                String strVal = value.toString();
                Console.Write(" {0} ", strVal);
              }
              Console.Write("]");
            }
          }
        }
        else
        {
          //
          // Deprecated: OdArray instead of Aggregate
          //
          OdDAIObjectIds idsVal = OdRxValueHelper.rxvalue_cast<OdDAIObjectIds>(val);
          if (idsVal != null)
          {
            ++inverse_aggregates;
            unset = (idsVal.Count == 0);
            if (!unset)
            {
              UInt64 int64 = idsVal[0].getHandle().ToUInt64();
              Console.Write(" = ({0:X}", int64);
              for (int i = 1; i < idsVal.Count; ++i)
              {
                int64 = idsVal[i].getHandle().ToUInt64();
                Console.Write(", {0:X}", int64);
              }
              Console.Write(")");
            }
            else
              ++empty_inverse_aggregates;
          }
        }

        if (unset)
          Console.Write(" = UNSET");

        Console.Write("\n");
      }
    }

  }
}