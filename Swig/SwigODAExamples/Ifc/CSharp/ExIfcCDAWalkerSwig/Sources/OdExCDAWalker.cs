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

using Teigha.Core;

namespace ExIfcCDAWalkerSwigMgd
{
  class OdExCDAWalker
  {
    OdExAbstractNotifier m_pNotifier;

    public OdExCDAWalker(OdExAbstractNotifier notifier)
    { m_pNotifier = notifier; }

    public void run(OdRxObject inst)
    {
      walkCDA(inst);
    }

    protected void walkCDA(OdRxObject inst)
    {
      if (m_pNotifier != null)
        m_pNotifier.onLevelBegin(inst);

      //
      // Try to find attribute called Representation, if it isn't null, the instance can be vectorized.
      //
      OdRxMember memRepr = OdRxMemberQueryEngine.theEngine().find(inst, "Representation");
      if (memRepr != null)
      {
        if (memRepr.isKindOf(OdRxProperty.desc()))
        {
          OdRxProperty propRepr = OdRxProperty.cast(memRepr);

          OdRxValue idRepresentation = OdRxValue.create();
          if (OdResult.eOk == propRepr.getValue(inst, idRepresentation))
          {
            IOdRxReferenceType reference = idRepresentation.type().reference();
            if (reference != null)
            {
              OdRxObject reprInst = reference.dereference(idRepresentation, IOdRxReferenceType.OpenMode.kForRead);
              if (reprInst != null)
              {
                if (m_pNotifier != null)
                  m_pNotifier.onHasRepresentation(inst, reprInst);
              }
            }
          }
        }
      }

      //
      // Walk along all Rx Properties of instance and try to find Hierarchy Attribute
      //
      OdRxMemberIterator it = OdRxMemberQueryEngine.theEngine().newMemberIterator(inst);
      for (; !it.done(); it.next())
      {
        OdRxMember member = it.current();

        OdRxAttributeCollection attrs = member.attributes();

        int numAttrs = attrs.count();
        for (int i = 0; i < numAttrs; ++i)
        {
          OdRxAttribute attr = attrs.getAt(i);

          OdRxClass pRx = attr.isA();
          if (pRx.isDerivedFrom(OdRxHierarchyLevelAttribute.desc()))
          {
            if (m_pNotifier != null)
              m_pNotifier.onHierarchyAttributeFound(inst, member);

            if (member.isKindOf(OdRxProperty.desc()))
            {
              OdRxProperty prop = OdRxProperty.cast(member);

              OdRxValue idHierarchy = OdRxValue.create();
              if (OdResult.eOk == prop.getValue(inst, idHierarchy))
              {
                IOdRxReferenceType reference = idHierarchy.type().reference();
                if (reference != null)
                {
                  OdGiDrawable pInst = OdGiDrawable.cast(reference.dereference(idHierarchy, IOdRxReferenceType.OpenMode.kForRead));
                  walkCDA(pInst);
                }
              }
            }
            else if (member.isKindOf(OdRxCollectionProperty.desc()))
            {
              OdRxCollectionProperty collection = OdRxCollectionProperty.cast(member);
              OdRxValueIterator itValues = collection.newValueIterator(inst);

              if (itValues != null)
                for (; !itValues.done(); itValues.next())
                {
                  OdRxValue treeNodeId = itValues.current();
                  IOdRxReferenceType reference = treeNodeId.type().reference();
                  if (reference != null)
                  {
                    OdGiDrawable pInst = OdGiDrawable.cast(reference.dereference(treeNodeId, IOdRxReferenceType.OpenMode.kForRead));
                    walkCDA(pInst);
                  }
                }
            }
          }
        }
      }

      if (m_pNotifier != null)
        m_pNotifier.onLevelEnd(inst);
    }

  };
}