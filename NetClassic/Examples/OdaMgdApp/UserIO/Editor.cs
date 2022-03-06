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
using System.Windows.Forms;
using Teigha.DatabaseServices;
using Teigha.Geometry;
using Teigha.UserIO;

namespace OdaMgdApp.UserIO
{

  public class Editor_OdaMgdApp : Editor
  {
    MainForm form;
    PointPicker picker;
    Selector selector;

    public Editor_OdaMgdApp(MainForm form) : base()
    {
      CommandAdded += onCommandAdded;
      UnknownCommand += onUnknownCommand;
      CommandEnded += onCommandEnded;
      this.form = form;
    }

    // ---------------------------------------------- Events ----------------------------------------------

    // is called when there is new command added to global command list; when it happens, menu with commands should be updated
    public void onCommandAdded(Object sender, CommandEventArgs arg)
    {
      form.UpdateMenuWithCommands();
    }

    public void onUnknownCommand(Object sender, UnknownCommandEventArgs arg)
    {
      form.WriteTextAndHistoryText("Unknown command: " + arg.GlobalCommandName);
    }

    public void onCommandEnded(Object sender, CommandEventArgs arg)
    {
      if (form != null)
      {
        if (form.ActiveMdiChild != null)
        {
          if (form.ActiveDrawingForm.helperDevice != null)
          {
            form.ActiveDrawingForm.helperDevice.Invalidate();
            form.ActiveDrawingForm.helperDevice.Update();
          }

          form.WriteText("");
          form.ReinitInputTextAndResetFocus();
        }

        if (form.UserSettings != null)
        {
          form.UserSettings.LastExecutedCommand = arg.GlobalCommandName;
          form.UpdateRecentCommandsMenu();
          form.UserSettings.Save();
        }
        
      }
    }

    public void SelectionDone(bool done)
    {
      if (form.ActiveDrawingForm.selected.Count > 0 && done)
      {
        selector.isSelected = true;
      }
      else
      {
        selector.cancel = true;
      }
    }

    // ---------------------------------------------- Other ----------------------------------------------

    public override void WriteMessage(string message)
    {
      form.WriteTextAndHistoryText(message);
    }

    // ---------------------------------------------- Getters ----------------------------------------------

    public override PromptResult GetString(String message)
    {
      form.WriteText("");
      form.SetInputBackgroundText(message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptResult res = new PromptResult();

      if (uis == UserInputState.Done)
      {
        res.StringResult = form.ReadText();
        res.Status = PromptStatus.OK;
      }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    public override PromptResult GetString(PromptStringOptions options)
    {
      form.WriteText("");
      form.SetInputBackgroundText(options.Message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptResult res = new PromptResult();

      if (uis == UserInputState.Done)
      {
        res.StringResult = form.ReadText();
        if (options.UseDefaultValue && res.StringResult == "")
        {
          res.StringResult = options.DefaultValue;
        }
        res.Status = PromptStatus.OK;
      }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    public override PromptFileNameResult GetFileNameForOpen(string prompt)
    {
      string parameterFromCommand = Editor.Current.CommandDefaultParameters.GetNextParameterAndRemove() as string;
      PromptFileNameResult res;
      if (parameterFromCommand != null)
      {
        res = new PromptFileNameResult(parameterFromCommand);
        res.Status = PromptStatus.OK;
      }
      else
      {
        DialogResult dialogRes;
        String path = form.GetOpenPathFromDialog(prompt, out dialogRes);
        res = new PromptFileNameResult(path);
        if (dialogRes == System.Windows.Forms.DialogResult.OK)
          res.Status = PromptStatus.OK;
        else if (dialogRes == System.Windows.Forms.DialogResult.Cancel)
          res.Status = PromptStatus.Cancel;
        else
          res.Status = PromptStatus.Error;
      }
      return res;
    }

    public override PromptFileNameResult GetFileNameForSave(PromptSaveFileOptions options)
    {
      string parameterFromCommand = Editor.Current.CommandDefaultParameters.GetNextParameterAndRemove() as string;
      if (parameterFromCommand != null)
      {
        return new PromptFileNameResult(parameterFromCommand);
      }
      else
      {
        PromptFileNameResult res = new PromptFileNameResult(form.GetSavePathFromDialog(options.InitialFileName));
        if (res.StringResult == "")
          res.Status = PromptStatus.Cancel;
        else
          res.Status = PromptStatus.OK;
        return res;
      }
    }

    public override PromptPointResult GetPoint(PromptPointOptions options)
    {
      if (picker == null)
      {
        picker = new PointPicker();
      }

      // change events on click on window to picking point mode
      picker.InitPointPicker(form.ActiveDrawingForm);

      while (!picker.cancel && !picker.picked)
      {
        Application.DoEvents();
      }

      // change events on click on window back to originals
      picker.DeinitPointPicker();

      return picker.promptPointResult;
    }

    public override PromptSelectionResult GetSelection()
    {
      if (selector == null)
      {
        selector = new Selector();
      }

      selector.InitSelector(form.ActiveDrawingForm);

      while (!selector.cancel && !selector.isSelected)
      {
        Application.DoEvents();
      }

      PromptSelectionResult res = new PromptSelectionResult();
      if (selector.isSelected == true)
      {
        res.Status = PromptStatus.OK;
      }
      else if (selector.cancel == true)
      {
        res.Status = PromptStatus.Cancel;
      }
      else
      {
        res.Status = PromptStatus.Error;
      }

      ObjectIdCollection selected = form.ActiveDrawingForm.selected;
      res.Value = new SelectionSet_OdaMgdApp(selected);

      selector.DeinitSelector();

      return res;
    }

    public override PromptDoubleResult GetDouble(string message)
    {
      form.WriteText("");
      form.SetInputBackgroundText(message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptDoubleResult res = new PromptDoubleResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
        try
        {
          IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
          res.Value = double.Parse(text, provider);
        }
        catch (FormatException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (OverflowException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (ArgumentNullException)
        {
          res.Status = PromptStatus.Error;
        }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    public override PromptDoubleResult GetDouble(PromptDoubleOptions options)
    {
      form.WriteText("");
      form.SetInputBackgroundText(options.Message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptDoubleResult res = new PromptDoubleResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
      {
        if (text.Trim() == "") // nothing entered, use default value
        {
          res.Value = options.DefaultValue;
          res.Status = PromptStatus.OK;
        }
        else
        {
          try
          {
            IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
            res.Value = double.Parse(text, provider);
            res.Status = PromptStatus.OK;
          }
          catch (FormatException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (OverflowException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (ArgumentNullException)
          {
            res.Status = PromptStatus.Error;
          }
        }
      }
      else // this should never happen
      {
        res.Status = PromptStatus.None;
      }

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;
      return res;
    }

    public override PromptIntegerResult GetInteger(string message)
    {
      form.WriteText("");
      form.SetInputBackgroundText(message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      int resInt = 0;
      String text = form.ReadText();
      PromptIntegerResult res = new PromptIntegerResult();

      if (uis == UserInputState.Done)
        try
        {
          IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
          resInt = int.Parse(text, provider);
        }
        catch (FormatException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (OverflowException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (ArgumentNullException)
        {
          res.Status = PromptStatus.Error;
        }

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

     
      res.Value = resInt;
      return res;
    }

    public override PromptIntegerResult GetInteger(PromptIntegerOptions options)
    {
      form.WriteText("");
      form.SetInputBackgroundText(options.Message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptIntegerResult res = new PromptIntegerResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
      {
        if (text.Trim() == "") // nothing entered, use default value
        {
          res.Value = options.DefaultValue;
          res.Status = PromptStatus.OK;
        }
        else
        {
          try
          {
            IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
            res.Value = int.Parse(text, provider);
            res.Status = PromptStatus.OK;
          }
          catch (FormatException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (OverflowException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (ArgumentNullException)
          {
            res.Status = PromptStatus.Error;
          }
        }
      }
      else // this should never happen
      {
        res.Status = PromptStatus.None;
      }

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;
      return res;
    }

    // here could be another way of asking for distance, for example asking for 2 points and calculating distance between them automatically,
    // but here we just enter distance as double value to console in both methods

    public override PromptDoubleResult GetDistance(string message)
    {
      form.WriteText("");
      form.SetInputBackgroundText(message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptDoubleResult res = new PromptDoubleResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
        try
        {
          IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
          res.Value = double.Parse(text, provider);
        }
        catch (FormatException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (OverflowException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (ArgumentNullException)
        {
          res.Status = PromptStatus.Error;
        }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    public override PromptDoubleResult GetDistance(PromptDistanceOptions options)
    {
      form.WriteText("");
      form.SetInputBackgroundText(options.Message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptDoubleResult res = new PromptDoubleResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
      {
        if (text.Trim() == "") // nothing entered, use default value
        {
          res.Value = options.DefaultValue;
          res.Status = PromptStatus.OK;
        }
        else
        {
          try
          {
            IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
            res.Value = double.Parse(text, provider);
            res.Status = PromptStatus.OK;
          }
          catch (FormatException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (OverflowException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (ArgumentNullException)
          {
            res.Status = PromptStatus.Error;
          }
        }
      }
      else // this should never happen
      {
        res.Status = PromptStatus.None;
      }

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;
      return res;
    }

    public override PromptResult GetKeywords(string message, params string[] globalKeywords) // could use parameters here
    {
      form.WriteText("");
      form.SetInputBackgroundText(message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptResult res = new PromptResult();

      if (uis == UserInputState.Done)
      {
        res.StringResult = form.ReadText();
        res.Status = PromptStatus.OK;
      }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    public override PromptResult GetKeywords(PromptKeywordOptions options)
    {
      form.WriteText("");
      form.SetInputBackgroundText(options.Message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptResult res = new PromptResult();

      if (uis == UserInputState.Done)
      {
        res.StringResult = form.ReadText();
        res.Status = PromptStatus.OK;
      }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    // here could be another way of asking for angle, for example with real time displaying of dimensions,
    // but here we just enter angle as double value to console in both methods

    public override PromptDoubleResult GetAngle(string message)
    {
      form.WriteText("");
      form.SetInputBackgroundText(message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptDoubleResult res = new PromptDoubleResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
        try
        {
          IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
          res.Value = double.Parse(text, provider);
        }
        catch (FormatException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (OverflowException)
        {
          res.Status = PromptStatus.Error;
        }
        catch (ArgumentNullException)
        {
          res.Status = PromptStatus.Error;
        }
      else
        res.Status = PromptStatus.None;

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;

      return res;
    }

    public override PromptDoubleResult GetAngle(PromptAngleOptions options)
    {
      form.WriteText("");
      form.SetInputBackgroundText(options.Message);

      form.ActiveDrawingForm.currentUserInputState = UserInputState.InProgress;

      UserInputState uis = form.ActiveDrawingForm.LoopTillUserInput();

      PromptDoubleResult res = new PromptDoubleResult();
      String text = form.ReadText();

      if (uis == UserInputState.Done)
      {
        if (text.Trim() == "") // nothing entered, use default value
        {
          res.Value = options.DefaultValue;
          res.Status = PromptStatus.OK;
        }
        else
        {
          try
          {
            IFormatProvider provider = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
            res.Value = double.Parse(text, provider);
            res.Status = PromptStatus.OK;
          }
          catch (FormatException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (OverflowException)
          {
            res.Status = PromptStatus.Error;
          }
          catch (ArgumentNullException)
          {
            res.Status = PromptStatus.Error;
          }
        }
      }
      else // this should never happen
      {
        res.Status = PromptStatus.None;
      }

      form.ActiveDrawingForm.currentUserInputState = UserInputState.NotActive;
      return res;
    }
  } // Editor

}
