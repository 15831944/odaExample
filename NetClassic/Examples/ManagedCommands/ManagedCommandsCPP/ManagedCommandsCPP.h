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

#pragma once

using namespace System;
using namespace System::Collections;
using namespace Teigha::Runtime;
using namespace Teigha::Geometry;
using namespace Teigha::DatabaseServices;
using namespace Teigha::UserIO;

/** \details
  To test a command from native code:
  Launch OdaMfcApp C++ sample
  Create new file (or open existing)
  Using Tools/Load App dialog, load NetloadCommandModule_*.tx
  Invoke command prompt via Shift + C
  Type 'NETLOAD', and browse to ManagedTestCommand_*.tx
  Type AddSomeText at the command prompt
  To debug managed code, debugger type should be set to Mixed or Managed only, in project properties/Debugging tab.

  Test command from managed sample:
  Open OdaMgdApp sample
  Create new file (or open existing)
  Commands will be loaded automatically; if no, 
  in command prompt or Edit->Registered commands choose 'NETLOAD', and browse to ManagedTestCommand_*.tx.
  In command prompt or Edit->Registered commands type 'AddSomeText'.
*/
namespace ManagedCommands
{

	public ref class ManagedCommandsCPP1 // there can be many classes in one dll with methods marked as commands by CommandMethodAttribute.
	{
  public:
    /* Add DBText to current drawing. */
    [CommandMethod("Managed commands C++/CLI", "AddSomeTestText", CommandFlags::Modal)]
    void AddDbText();

    /* Try different ways to get inputs from user by Editor. */
    [CommandMethod("Managed commands C++/CLI", "TestInput", CommandFlags::Modal)]
    void TestInputCommand();
	};

  public ref class ManagedCommandsCPP2
  {
  public:
    /* Export current layout to new dwg file. */
    [CommandMethod("Managed commands C++/CLI", "ExportLayout", CommandFlags::Modal)]
    void run();
  };

}
