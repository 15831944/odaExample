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
using System.Configuration;
using System.Drawing;
using System.Collections.Specialized;

namespace OdaMgdApp
{

  public class UserSettings : ApplicationSettingsBase
  {

    static int MAX_LAST_OPENED_FILES_COUNT = 10;
    static int MAX_LAST_EXECUTED_COMMANDS_COUNT = 10;

    // --------------------------------------- Last opened files ---------------------------------------

    [UserScopedSetting()]
    [DefaultSettingValue("")]
    public StringCollection LastOpenedFiles
    {
      get
      {
        return (StringCollection)this["LastOpenedFiles"];
      }
      set
      {
        this["LastOpenedFiles"] = (StringCollection)value;
      }
    }

    void RemoveFiles(ref StringCollection files)
    {
      if (files.Count > MAX_LAST_OPENED_FILES_COUNT)
      {
        files.RemoveAt(MAX_LAST_OPENED_FILES_COUNT);
        this.RemoveFiles(ref files);
      }
    }

    public String LastOpenedFile
    {
      set
      {
        String str = (String)value;
        StringCollection files = this.LastOpenedFiles;
        int iPos = files.IndexOf(str);
        if(iPos != -1)
        {
          files.RemoveAt(iPos);
        }
        files.Insert(0, str);
        this.RemoveFiles(ref files);
        this.LastOpenedFiles = files;
      }
    }

    // --------------------------------------- Last executed commands ---------------------------------------

    [UserScopedSetting()]
    [DefaultSettingValue("")]
    public StringCollection LastExecutedCommands
    {
      get
      {
        return (StringCollection)this["LastExecutedCommands"];
      }
      set
      {
        this["LastExecutedCommands"] = (StringCollection)value;
      }
    }

    void RemoveCommands(ref StringCollection commands)
    {
      if (commands.Count > MAX_LAST_EXECUTED_COMMANDS_COUNT)
      {
        commands.RemoveAt(MAX_LAST_EXECUTED_COMMANDS_COUNT);
        this.RemoveCommands(ref commands);
      }
    }

    public String LastExecutedCommand
    {
      set
      {
        String str = (String)value;
        StringCollection commands = this.LastExecutedCommands;
        int iPos = commands.IndexOf(str);
        if (iPos != -1)
        {
          commands.RemoveAt(iPos);
        }
        commands.Insert(0, str);
        this.RemoveCommands(ref commands);
        this.LastExecutedCommands = commands;
      }
    }
  }

}
