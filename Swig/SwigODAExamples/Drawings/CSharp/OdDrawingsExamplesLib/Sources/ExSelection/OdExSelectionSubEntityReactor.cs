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
using Teigha.TD;

namespace OdDrawingsExamplesMgdLib.ExSelection
{
  public class OdExSelectionSubEntityReactor : OdGsSelectionReactor
  {
    public OdExPathNode GetRootPathNode { get; private set; }

    public override bool selected(OdGiDrawableDesc pDrawableDesc)
    {
      if (GetRootPathNode != null)
        return true;
      OdDbObjectIdArray ids = new OdDbObjectIdArray();
      OdGiDrawableDesc pDD = pDrawableDesc;
      do
      {
        if (pDD.persistId != null)
          ids.Add(new OdDbObjectId(pDD.persistId));
        pDD = pDD.pParent;
      } while (pDD != null);

      if (ids.Count == 0)
        return false;
      ids.Reverse();
      for (int nPath = 0; nPath < ids.Count; nPath++)
      {
        OdExPathNode pPath = new OdExPathNode();
        pPath.m_pParent = GetRootPathNode;
        pPath.m_id = ids[nPath];
        GetRootPathNode = pPath;
      }
      pDrawableDesc.markToBreak(true);
      return true;
    }

    public override uint selected(OdGiPathNode pathNode, OdGiViewport viewInfo)
    {
      if (GetRootPathNode != null)
        return kBreak;
      OdDbObjectIdArray ids = new OdDbObjectIdArray();
      IntPtr gsMark = pathNode.selectionMarker();
      OdGiPathNode pPN = pathNode;
      // Attributes is a part of BlockRef's
      if (pPN.persistentDrawableId() != null && (new OdDbObjectId(pPN.persistentDrawableId())).safeOpenObject().isKindOf(OdDbAttribute.desc()) &&
        pPN.parent() != null && pPN.parent().persistentDrawableId() != null && (new OdDbObjectId(pPN.parent().persistentDrawableId())).safeOpenObject().isKindOf(OdDbBlockReference.desc()))
        pPN = pPN.parent();
      //
      do
      {
        if (pPN.persistentDrawableId() != null)
          ids.Add(new OdDbObjectId(pPN.persistentDrawableId()));
        pPN = pPN.parent();
      } while (pPN != null);

      if (ids.Count == 0)
        return kContinue;
      ids.Reverse();
      for (int nPath = 0; nPath < ids.Count; nPath++)
      {
        OdExPathNode pPath = new OdExPathNode();
        pPath.m_pParent = GetRootPathNode;
        pPath.m_id = ids[nPath];
        GetRootPathNode = pPath;
      }
      GetRootPathNode.m_selMark = gsMark;
      return kBreak;
    }
  }
}