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
using ODA.Ifc.IfcCore;

namespace OdIfcExamplesLibMgd
{
  public class OdIfcApplicationServicesSample
  {
    public class ExSystemServices : RxSystemServicesImpl
    {
      public ExSystemServices(string userInfo, string userSignature)
      {
        Globals.odActivate(userInfo, userSignature);
      }
    }

    public class ExOdIfcHostAppServices : OdIfcHostAppServices
    {
      public override OdGsDevice gsBitmapDevice(OdRxObject pViewObj, OdRxObject pDb, uint flags)
      {
        OdRxModule module = Globals.odrxDynamicLinker().loadModule("WinBitmap.txv");
        OdGsModule gsModule = new OdGsModule(OdRxModule.getCPtr(module).Handle, false);
        return gsModule.createBitmapDevice();
      }
    }

    public ExSystemServices m_SystemServices { get; private set; }
    public OdIfcHostAppServices m_HostAppServices { get; private set; }

    public OdIfcApplicationServicesSample(string userInfo, string userSignature)
    {
      m_SystemServices = new ExSystemServices(userInfo, userSignature);
      m_HostAppServices = new OdIfcHostAppServices();
    }
  }
}