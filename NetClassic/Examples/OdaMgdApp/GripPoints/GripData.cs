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
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Teigha;
using Teigha.DatabaseServices;
using Teigha.GraphicsSystem;
using Teigha.Runtime;
using Teigha.GraphicsInterface;
using Teigha.Geometry;
using Teigha.Colors;

namespace OdaMgdApp
{

  public class GripDataExtended
  {
    GripMarkCollection m_markCol;
    GripDataSubentCollection m_dataSubentCol;

    public GripDataExtended()
    {
      m_markCol = new GripMarkCollection();
      m_dataSubentCol = new GripDataSubentCollection();
    }

    public GripMarkCollection MarksCollection
    {
      get { return m_markCol; }
      set { m_markCol = value; }
    }

    public GripDataSubentCollection DataSubentCollection
    {
      get { return m_dataSubentCol; }
      set { m_dataSubentCol = value; }
    }
  };

  public class GripDataSubentCollection : CollectionBase
  {
    //strongly typed accessor
    public GripDataSubentity this[int index]
    {
      get
      {
        return (GripDataSubentity)this.List[index];
      }
      set
      {
        this.List[index] = value;
      }
    }

    public void Add(GripDataSubentity grData)
    {
      this.List.Add(grData);
    }
  }

  public class GripDataSubentity
  {
    FullSubentityPath m_entPath;
    GripMarkCollection m_marksCollection;

    public GripDataSubentity()
    {
      m_entPath = new FullSubentityPath();
      m_marksCollection = new GripMarkCollection();
    }

    public FullSubentityPath EntPath
    {
      get { return m_entPath; }
      set { m_entPath = value; }
    }

    public GripMarkCollection MarksCollection
    {
      get { return m_marksCollection; }
      set { m_marksCollection = value; }
    }
  };

}
