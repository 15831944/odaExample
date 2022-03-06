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
using System.IO;
using Teigha.Core;
using ODA.Sdai.sdai;

namespace ExIfcSchemaDumpSwigMgd
{
  public class OdExIfcShemaDumper
  {
    StreamWriter DumpStream;
    public OdExIfcShemaDumper(StreamWriter dumpStream)
    {
      DumpStream = dumpStream;
    }

    public void dumpTypes(OdRxDictionary types)
    {
      for (UInt32 id = 0; id < types.numEntries(); id++)
      {
        OdDAI_DefinedType pDefinedType = OdDAI_DefinedType.cast(types.getAt(types.keyAt(id)));
        if (pDefinedType.domain().isSimpleType())
        {
          continue;
        }
        DumpStream.Write("TYPE {0} = {1};\n", pDefinedType.name(), getDefinedTypeName(pDefinedType));
        DumpStream.Write("END_TYPE;\n\n");
      }
    }

    public void dumpEntities(OdRxDictionary entities)
    {
      Dictionary<String, List<OdDAI_Entity>> subtypes = new Dictionary<string, List<OdDAI_Entity>>();

      collectSubtypes(entities, subtypes);

      for (UInt32 id = 0; id < entities.numEntries(); id++)
      {
        OdDAI_Entity pEntity = OdDAI_Entity.cast(entities.getAt(entities.keyAt(id)));

        DumpStream.Write("ENTITY {0}", pEntity.name());
        dumpSubtypes(pEntity, subtypes);
        dumpSupertypes(pEntity.supertypes());
        DumpStream.Write(";\n");

        OdDAI_AttributeSet attributes = pEntity.attributes();
        dumpExplicitAttributes(attributes);
        dumpDerivedAttributes(attributes);
        dumpInverseAttributes(attributes);

        DumpStream.Write("END_ENTITY;\n\n");
      }
    }

    void dumpExplicitAttributes(OdDAI_AttributeSet attributes)
    {
      for (OdDAI_ConstIterator it = attributes.createConstIterator(); it.next();)
      {
        OdDAI_Attribute pAttr = OdRxValueHelper.rxvalue_cast<OdDAI_Attribute>(it.getCurrentMember());
        OdDAI_ExplicitAttribute pExplicit = OdDAI_ExplicitAttribute.cast(pAttr);
        if (pExplicit != null)
        {
          DumpStream.Write("    {0} : {1}{2};\n",
            pExplicit.name(),
            (pExplicit.optional() ? "OPTIONAL " : ""),
        getBaseTypeName(pExplicit.domain()));
        }
      }
    }

    void dumpInverseAttributes(OdDAI_AttributeSet attributes)
    {
      bool hasInverse = false;
      for (OdDAI_ConstIterator it = attributes.createConstIterator(); it.next();)
      {
        OdDAI_Attribute pAttr = OdRxValueHelper.rxvalue_cast<OdDAI_Attribute>(it.getCurrentMember());
        OdDAI_InverseAttribute pInverse = OdDAI_InverseAttribute.cast(pAttr);
        if (pInverse != null)
        {
          if (hasInverse == false)
          {
            DumpStream.Write(" INVERSE\n");
            hasInverse = true;
          }
          DumpStream.Write("    {0} : ", pInverse.name());
          if (pInverse.minCardinality() != int.MaxValue)
          {
            DumpStream.Write("{0} [{1}:", pInverse.duplicates() ? "BAG" : "SET", pInverse.minCardinality());
            if (pInverse.maxCardinality() != int.MaxValue)
            {
              DumpStream.Write("{0}] OF ", pInverse.maxCardinality());
            }
            else
            {
              DumpStream.Write("?] OF ");
            }
          }
          DumpStream.Write("{0} FOR {1};\n",
            pInverse.domain().name(),
            pInverse.invertedAttr().name());
        }
      }
    }

    void dumpDerivedAttributes(OdDAI_AttributeSet attributes)
    {
      bool hasDerived = false;
      for (OdDAI_ConstIterator it = attributes.createConstIterator(); it.next();)
      {
        OdDAI_Attribute pAttr = OdRxValueHelper.rxvalue_cast<OdDAI_Attribute>(it.getCurrentMember());
        OdDAI_DerivedAttribute pDerived = OdDAI_DerivedAttribute.cast(pAttr);
        if (pDerived != null)
        {
          if (hasDerived == false)
          {
            DumpStream.Write(" DERIVE\n");
            hasDerived = true;
          }
          DumpStream.Write("    {0} : {1};\n",
            pDerived.name(),
            getBaseTypeName(pDerived.domain()));
        }
      }
    }


    void collectSubtypes(OdRxDictionary entities, Dictionary<String, List<OdDAI_Entity>> subtypes)
    {
      for (UInt32 id = 0; id < entities.numEntries(); id++)
      {
        OdDAI_Entity pEntity = OdDAI_Entity.cast(entities.getAt(entities.keyAt(id)));
        for (OdDAI_ConstIterator it = pEntity.supertypes().createConstIterator(); it.next();)
        {
          OdDAI_Entity pSupertype = OdRxValueHelper.rxvalue_cast<OdDAI_Entity>(it.getCurrentMember());

          List<OdDAI_Entity> subtype = null;
          if (!subtypes.TryGetValue(pSupertype.name(), out subtype))
          {
            subtype = new List<OdDAI_Entity>();
            subtypes.Add(pSupertype.name(), subtype);
          }
          subtype.Add(pEntity);
        }
      }
    }

    void dumpSubtypes(OdDAI_Entity pEntity, Dictionary<String, List<OdDAI_Entity>> subtypes)
    {
      List<OdDAI_Entity> entitySubtypes = null;
      if (subtypes.TryGetValue(pEntity.name(), out entitySubtypes))
      {
        DumpStream.Write("\n SUPERTYPE OF (ONEOF");
        String list = "";
        bool bFirst = true;
        foreach (var item in entitySubtypes)
        {
          addListElement(item.name(), bFirst, ref list);
          if (bFirst)
            bFirst = false;
        }
        DumpStream.Write("{0}))", list);
      }
    }

    void dumpSupertypes(OdDAI_List_OdDAI_Entity__p supertypes)
    {
      for (OdDAI_ConstIterator it = supertypes.createConstIterator(); it.next();)
      {
        OdDAI_Entity pSupertype = OdRxValueHelper.rxvalue_cast<OdDAI_Entity>(it.getCurrentMember());
        DumpStream.Write("\n SUBTYPE OF ({0})", pSupertype.name());
      }
    }

    String getDefinedTypeName(OdDAI_DefinedType pDefinedType)
    {
      if (pDefinedType.domain().isSimpleType())
      {
        return getSimpleTypeName(pDefinedType.domain().simpleType());
      }
      else if (pDefinedType.domain().isAggregationType())
      {
        return getAggregationTypeName(pDefinedType.domain().aggregationType());
      }
      else if (pDefinedType.domain().isDefinedType())
      {
        return pDefinedType.domain().definedType().name();
      }
      else if (pDefinedType.domain().isConstructedType())
      {
        return getConstructedTypeName(pDefinedType.domain().constructedType());
      }
      return "UNDEFINED";
    }

    String getConstructedTypeName(OdDAI_ConstructedType pConstructedType)
    {
      if (pConstructedType.isEnumerationType())
      {
        return getEnumerationTypeName(pConstructedType.enumerationType());
      }
      else if (pConstructedType.isSelectType())
      {
        return getSelectTypeName(pConstructedType.selectType());
      }
      return "UNDEFINED";
    }

    String getSelectTypeName(OdDAI_SelectType pSelectType)
    {
      String res = "SELECT";
      bool bFirst = true;
      foreach (var item in pSelectType.selections())
      {
        addListElement(item.name(), bFirst, ref res);
        if (bFirst)
          bFirst = false;
      }
      res += ")";
      return res;
    }

    String getEnumerationTypeName(OdDAI_EnumerationType pEnumarationType)
    {
      String res = "ENUMERATION OF";
      bool bFirst = true;
      foreach (var item in pEnumarationType.elements().getArray())
      {
        addListElement(item, bFirst, ref res);
        if (bFirst)
          bFirst = false;
      }
      res += ")";
      return res;
    }

    void addListElement(String elem, bool isFirst, ref String res, String ind = "  ")
    {
      res += "\n";
      res += ind;
      if (isFirst == false)
      {
        res += ",";
      }
      else
      {
        res += "(";
      }
      res += elem;
    }

    String getSimpleTypeName(OdDAI_SimpleType pSimpleType)
    {
      if (OdDAI_BinaryType.cast(pSimpleType) != null)
      {
        OdDAI_BinaryType pType = OdDAI_BinaryType.cast(pSimpleType);
        return String.Format("BINARY{0}{1}", (pType.width() != int.MaxValue ? pType.width().ToString() : String.Empty), (pType.fixedWidth() ? " FIXED" : ""));
      }
      if (OdDAI_BooleanType.cast(pSimpleType) != null)
      {
        return "BOOLEAN";
      }
      if (OdDAI_IntegerType.cast(pSimpleType) != null)
      {
        return "INTEGER";
      }
      if (OdDAI_LogicalType.cast(pSimpleType) != null)
      {
        return "LOGICAL";
      }
      if (OdDAI_BinaryType.cast(pSimpleType) != null)
      {
        return "NUMBER";
      }
      if (OdDAI_RealType.cast(pSimpleType) != null)
      {
        OdDAI_RealType pType = OdDAI_RealType.cast(pSimpleType);
        return "REAL" + (pType.precision() != int.MaxValue ? pType.precision().ToString() : String.Empty);
      }
      if (OdDAI_StringType.cast(pSimpleType) != null)
      {
        OdDAI_StringType pType = OdDAI_StringType.cast(pSimpleType);
        return "STRING" + (pType.width() != int.MaxValue ? pType.width().ToString() : String.Empty) + (pType.fixedWidth() ? " FIXED" : "");
      }
      if (pSimpleType == null)
      {
        return "UNDEFINED";
      }
      return "TODO";
    }

    String getAggregationTypeName(OdDAI_AggregationType pAggregationType)
    {
      String res = "";
      OdDAI_Bound lowerBound;
      OdDAI_Bound upperBound;
      if (OdDAI_ArrayType.cast(pAggregationType) != null)
      {
        OdDAI_ArrayType pType = OdDAI_ArrayType.cast(pAggregationType);
        lowerBound = pType.lowerBound();
        upperBound = pType.upperBound();
        res = "ARRAY";
      }
      else if (OdDAI_VariableSizeAggregationType.cast(pAggregationType) != null)
      {
        OdDAI_VariableSizeAggregationType pVariableSizeAggregationType = OdDAI_VariableSizeAggregationType.cast(pAggregationType);
        lowerBound = pVariableSizeAggregationType.lowerBound();
        upperBound = pVariableSizeAggregationType.upperBound();
        if (OdDAI_BagType.cast(pVariableSizeAggregationType) != null)
        {
          res = "BAG";
        }
        else if (OdDAI_ListType.cast(pVariableSizeAggregationType) != null)
        {
          res = "LIST";
        }
        else if (OdDAI_SetType.cast(pVariableSizeAggregationType) != null)
        {
          res = "SET";
        }
      }
      else
      {
        return "UNDEFINED";
      }
      return res + (lowerBound != null ?
        "[" + getBound(lowerBound) + ":" + getBound(upperBound) + "] " :
        String.Empty) +
        "OF " + getBaseTypeName(pAggregationType.elementType());
    }

    String getBound(OdDAI_Bound pBound)
    {
      if (OdDAI_IntegerBound.cast(pBound) != null)
      {
        return OdDAI_IntegerBound.cast(pBound).boundValue().ToString();
      }
      return "?";
    }

    String getBaseTypeName(OdDAI_BaseType baseType)
    {
      if (baseType.isSimpleType())
      {
        return getSimpleTypeName(baseType.simpleType());
      }
      if (baseType.isNamedType())
      {
        return baseType.namedType().name();
      }
      if (baseType.isAggregationType())
      {
        return getAggregationTypeName(baseType.aggregationType());
      }
      return "UNDEFINED";
    }
  }
}