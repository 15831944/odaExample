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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Collections.Specialized;

using Teigha;
using Teigha.DatabaseServices;
using Teigha.UserIO;
using Teigha.GraphicsSystem;
using Teigha.Runtime;
using Teigha.GraphicsInterface;
using Teigha.Geometry;

namespace OdaMgdApp
{
  public partial class MainForm : Form
  {
    // --------------------------------------- form fields ----------------------------------------

    Services appServices; // necessary for ODA product activation
    LayoutPaper layoutPaper; // paper layout for the drawing
    TextBox historyTextBox; // text box for displaying commands messages history
    LayoutHelperDevice helperDeviceAreaView; // layout device for areaView
    Device graphicsDeviceAreaView; // graphics device for areaView
    GsModule gsModuleAreaView; // graphics module for areaView
    Graphics graphicsAreaView; // graphics for the panel for areaView
    bool isAreaViewActiveOnPanel; // if currently areaView is being displayed on the panel

    // ------------------------------------ properties --------------------------------------------

    public UserSettings UserSettings { get; private set; }
    public DrawingForm ActiveDrawingForm { get { return ((DrawingForm)this.ActiveMdiChild); } }
    public ToolStripMenuItem CommandsMenu { get { return this.registeredCommandsToolStripMenuItem; } }
    public ToolStripMenuItem AreaViewOnPanelMenu { get { return this.inTheDrawingToolStripMenuItem; } }

    // -------------------------------------- winapi ----------------------------------------------

    // for disabling aero
    [DllImport("dwmapi.dll", EntryPoint = "DwmEnableComposition")]
    protected extern static uint Win32DwmEnableComposition(uint uCompositionAction);
    void DisableAero()
    {
      Win32DwmEnableComposition((uint)0);
    }

    // for making placeholder in text input (console) for commands (cue banner for textbox)
    private const int EM_SETCUEBANNER = 0x1501;
    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    private static extern Int32 SendMessage(IntPtr hWnd, int msg, int wParam, [MarshalAs(UnmanagedType.LPWStr)]string lParam);

    // for making text in text input (console) for commands to not go under the showHideHistoryButton
    private const int EM_SETMARGINS = 0xd3;
    [System.Runtime.InteropServices.DllImport("user32.dll")]
    private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wp, IntPtr lp);

    // ------------------------- initialization and deinitialization ------------------------------

    public MainForm(String filePathToPreopen)
    {
      ActivateAndInitializeODA();
      InitializeEditor();
      LoadModules();
      LoadCommands();
      InitializeComponent();
      InitializeCustomComponents();
      PreopenDwgOnFormOpeningIfNeeded(filePathToPreopen);
    }

    void ActivateAndInitializeODA()
    {
      Services.odActivate(ActivationData.userInfo, ActivationData.userSignature);
      appServices = new Services();
    }

    void InitializeEditor()
    {
      Editor.Current = new UserIO.Editor_OdaMgdApp(this);
    }

    void LoadModules()
    {
      SystemObjects.DynamicLinker.LoadApp("GripPoints", false, false);
      SystemObjects.DynamicLinker.LoadApp("PlotSettingsValidator", false, false);
      SystemObjects.DynamicLinker.LoadApp("ExDynamicBlocks", false, false);
      SystemObjects.DynamicLinker.LoadApp("ExEvalWatchers", false, false);
      //SystemObjects.DynamicLinker.LoadApp("PdfModuleVINet", false, false);
      //SystemObjects.DynamicLinker.LoadApp("PdfModuleVI", false, false);
    }

    // Loads our commands, so there is no need to load them from the menu manually.
    void LoadCommands()
    {
      string errorMsg = "";

      Module NetloadCommandModule = SystemObjects.DynamicLinker.LoadModule("NetloadCommandModule.tx", false, true);
      if (NetloadCommandModule == null)
      {
        errorMsg += "NetloadCommandModule could not be loaded; NETLOAD command is not available.\n";
      }

      string currentPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetEntryAssembly().Location);

      try
      {
        Editor.Current.Command("NETLOAD", currentPath + "\\ManagedCommandsCS.dll");
      }
      catch (System.Exception)
      {
        errorMsg += "ManagedCommandsCS could not be loaded; commands from this module are not available.\n";
      }

      // next command has version and studio version in its name; form name with version and search it in current directory
      var txFiles = System.IO.Directory.EnumerateFiles(currentPath, "*.tx");
      string managedTestCommandSubName = "ManagedCommandsCPP_" + HostApplicationServices.Current.VersionString;
      string managedCommandsCppName = "";
      foreach (string currentFile in txFiles)
      {
        string fileName = System.IO.Path.GetFileName(currentFile);
        if (fileName.Contains(managedTestCommandSubName))
        {
          managedCommandsCppName = currentFile;
          break;
        }
      }

      try
      {
        Editor.Current.Command("NETLOAD", managedCommandsCppName);
      }
      catch (System.Exception)
      {
        errorMsg += "ManagedCommandsCPP could not be loaded; commands from this module are not available.\n";
      }

      if (errorMsg != "")
      {
        MessageBox.Show("Could not load commands:\n" + errorMsg, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }

      // these are commands from native c++ samples;
      // they are auto-registered on module load, but not firing "commandAdded" to our command stack
      Module nativeCommandsModule = SystemObjects.DynamicLinker.LoadModule("ExCommands", false, true);

    } // loadCommands

    void InitializeCustomComponents()
    {
      HostApplicationServices.Current = new HostAppServ(AppProgressBar);
      
      Environment.SetEnvironmentVariable("DDPLOTSTYLEPATHS", ((HostAppServ)HostApplicationServices.Current).FindConfigPath(String.Format("PrinterStyleSheetDir")));
      
      UserSettings = new UserSettings();
      
      UpdateRecentFilesMenu();
      UpdateMenuWithCommands();
      UpdateRecentCommandsMenu();

      layoutPaper = new LayoutPaper();
      RXClass nLt = RXObject.GetClass(typeof(Layout));
      nLt.AddX(LayoutPaperPE.GetClass(), layoutPaper);

      //DisableAero();

      ObjectOverrule.Overruling = false; // on app start overruling option is not chosen

      textBoxConsole.Text = "";
      SetInputBackgroundText("Type a command...");


      // initialize showHideHistoryButton

      Button showHideHistoryButton = new System.Windows.Forms.Button();

      showHideHistoryButton.Anchor = ((System.Windows.Forms.AnchorStyles)((
        (System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) | System.Windows.Forms.AnchorStyles.Right
        )));
      showHideHistoryButton.Size = new System.Drawing.Size(20, 20);
      showHideHistoryButton.Location = new Point(textBoxConsole.ClientSize.Width - showHideHistoryButton.Width +2, -2);
      showHideHistoryButton.Name = "showHideHistoryButton";
      showHideHistoryButton.TabIndex = 12;
      showHideHistoryButton.Text = "˄";
      showHideHistoryButton.UseVisualStyleBackColor = true;
      showHideHistoryButton.Visible = true;
      showHideHistoryButton.Click += new System.EventHandler(this.showHideHistoryButton_Click);

      textBoxConsole.Controls.Add(showHideHistoryButton);
      showHideHistoryButton.BringToFront();

      // Send EM_SETMARGINS to prevent text from disappearing underneath the button
      SendMessage(textBoxConsole.Handle, EM_SETMARGINS, (IntPtr)2, (IntPtr)(showHideHistoryButton.Width << 16));


      // initialize historyTextBox

      this.historyTextBox = new System.Windows.Forms.TextBox();

      historyTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((
        System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right
        )));
      int historyTextBoxHeight = 154;
      int historyTextBoxWidth = 573;
      historyTextBox.Size = new System.Drawing.Size(historyTextBoxWidth, historyTextBoxHeight);
      historyTextBox.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
      historyTextBox.Location = new Point(0, this.ClientSize.Height - historyTextBoxHeight);
      historyTextBox.Multiline = true;
      historyTextBox.Name = "historyTextBox";
      historyTextBox.ReadOnly = true;
      historyTextBox.TabIndex = 11;
      historyTextBox.Visible = false;
      historyTextBox.ScrollBars = ScrollBars.Vertical;

      this.Controls.Add(historyTextBox);


      // initialize SnapManager and its modes (all on by default)

      SnapManager_OdaMgdApp.selectedSnapModes = new SelectedSnapModes(true);
      SnapManager_OdaMgdApp.hitRadius = 10.0;

      enableAllToolStripMenuItem_Click(enableAllToolStripMenuItem, null);
    }

    public void ReinitInputTextAndResetFocus()
    {
      SetInputBackgroundText("Type a command...");
    }

    public void SetInputBackgroundText(String text)
    {
      if (textBoxConsole != null)
      {
        SendMessage(textBoxConsole.Handle, EM_SETCUEBANNER, 1, text); // prelast param 0 if text should not be displayed on focus, 1 if should
      }
      if (ActiveMdiChild != null)
      {
        ActiveMdiChild.Focus();
      }
    }

    private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
    {
      if (isAreaViewActiveOnPanel)
        deactivateAreaViewOnPanel();
      appServices.Dispose();
    }

    // ------------------------------- menu buttons processing ------------------------------------

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenDwgInNewDrawingForm(false, null, null);
    }

    private void partialOpenToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenDwgInNewDrawingForm(true, null, null);
    }

    private void openRecentToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenDwgInNewDrawingForm(false, null, ((ToolStripMenuItem)sender).Text);
    }

    private void newToolStripMenuItem_Click(object sender, EventArgs e)
    {
      CreateDwgInNewDrawingForm();
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      SaveDwgInActiveDrawingForm();
    }

    private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.Database != null)
        {
          if (DialogResult.OK == saveAsFileDialog.ShowDialog(this))
          {
            ActiveDrawingForm.ApplyViewChanges();
            ActiveDrawingForm.Database.SaveAs(saveAsFileDialog.FileName, DwgVersion.Current, true);
          }
        }
      }
    }

    private void closeToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Close();
      }
    }

    private void closeAllToolStripMenuItem_Click(object sender, EventArgs e)
    {
      foreach (DrawingForm form in this.MdiChildren)
      {
        form.Close();
      }
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    private void setActiveLayoutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.helperDevice != null)
        {
          SelectLayouts selLayoutForm = new SelectLayouts(ActiveDrawingForm.Database);
          selLayoutForm.Show();
        }
      }
    }

    private void fileDependencyToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.helperDevice != null)
        {
          File_Dependency fileDependencyForm = new File_Dependency(ActiveDrawingForm.Database);
          fileDependencyForm.Show();
        }
      }
    }

    private void layersToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.helperDevice != null)
        {
          Layers layersForm = new Layers(ActiveDrawingForm.Database, ActiveDrawingForm.helperDevice);
          layersForm.Show();
        }
      }
    }

    private void blockToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Block();
      }
    }

    private void lineToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Line();
      }
    }

    private void recoverToolStripMenuItem_Click(object sender, EventArgs e)
    {
      using (AuditInfo aiAppAudit = new CustomAuditInfo("AuditReport.txt"))
      {
        aiAppAudit.FixErrors = true;
        OpenDwgInNewDrawingForm(false, aiAppAudit, null);
      }
    }

    private void zoomToExtentsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.ZoomExtents();
      }
    }

    private void zoomWindowToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Zoom();
      }
    }

    private void refreshToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Regenerate();
      }
    }

    private void exportToPDFToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        PDFExport PDFExportForm = new PDFExport(ActiveDrawingForm.Database);
        PDFExportForm.Show();
      }
    }

    private void exportToDWFToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
        if (ActiveDrawingForm.Database != null && ActiveDrawingForm.helperDevice != null)
          ImExport.DWF_export(ActiveDrawingForm.Database, ActiveDrawingForm.helperDevice);
    }

    private void exportToSVGToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
        if (ActiveDrawingForm.Database != null)
          ImExport.SVG_export(ActiveDrawingForm.Database);
    }

    private void saveBitmapToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.Database != null)
        {
          BMPExport bmpExport = new BMPExport(ActiveDrawingForm.Database);
          bmpExport.Show();
        }
      }
    }

    private void publishToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
        if (ActiveDrawingForm.Database != null && ActiveDrawingForm.helperDevice != null)
          ImExport.Publish(ActiveDrawingForm.Database, ActiveDrawingForm.helperDevice);
    }

    private void dPublishToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
        if (ActiveDrawingForm.Database != null && ActiveDrawingForm.helperDevice != null)
          ImExport.Publish3d(ActiveDrawingForm.Database, ActiveDrawingForm.helperDevice);
    }

    private void dwfImportToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
        if (ActiveDrawingForm.Database != null)
          ImExport.Dwf_import(ActiveDrawingForm.Database);
    }

    private void pageSetupToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.PageSetup();
      }
    }

    private void printPreviewToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.Database != null && ActiveDrawingForm.helperDevice != null)
        {
          Print.Printing pr = new Print.Printing();
          pr.Print(ActiveDrawingForm.Database, ActiveDrawingForm.helperDevice.ActiveView, true);
        }
      }
    }

    private void printToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.Database != null && ActiveDrawingForm.helperDevice != null)
        {
          Print.Printing pr = new Print.Printing();
          pr.Print(ActiveDrawingForm.Database, ActiveDrawingForm.helperDevice.ActiveView, false);
        }
      }
    }

    private void saveImageToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
        ActiveDrawingForm.ExportImage();
    }

    private void lineOverruleToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ToolStripMenuItem mi = (ToolStripMenuItem)sender;
        mi.Checked = !mi.Checked;
        if (!mi.Checked)
        {
          ActiveDrawingForm.GripManager.StopLineOverruling();
        }
        else
        {
          ActiveDrawingForm.GripManager.StartLineOverruling();
        }
      }
    }

    private void imageOverruleToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ToolStripMenuItem mi = (ToolStripMenuItem)sender;
        mi.Checked = !mi.Checked;
        if (!mi.Checked)
        {
          ActiveDrawingForm.GripManager.StopImageOverruling();
        }
        else
        {
          ActiveDrawingForm.GripManager.StartImageOverruling();
        }
      }
    }

    private void universalOverruleToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ToolStripMenuItem mi = (ToolStripMenuItem)sender;
        mi.Checked = !mi.Checked;
        if (!mi.Checked)
        {
          ActiveDrawingForm.GripManager.StopUniversalOverruling();
        }
        else
        {
          ActiveDrawingForm.GripManager.StartUniversalOverruling(ActiveDrawingForm.Database);
        }
      }
    }

    private void exportSelectedToNewFileToolStripMenuItem_Click(object sender, EventArgs e)
    {
      ActiveDrawingForm.SelectAndExportToAnotherDwg();
    }

    private void exportSelectedToBMPToolStripMenuItem_Click(object sender, EventArgs e)
    {
      ActiveDrawingForm.SelectAndExportToBmp();
    }

    private void onThePanelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (isAreaViewActiveOnPanel)
        deactivateAreaViewOnPanel();
      else
        activateAreaViewOnPanel();
    }

    private void inTheDrawingToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm == null)
      {
        WriteTextAndHistoryText("No active drawing to apply area view.");
        return;
      }
        
      if (ActiveDrawingForm.PanelState.AreaViewInDrawingState)
        ActiveDrawingForm.deactivateAreaViewInDrawing();
      else
        ActiveDrawingForm.activateAreaViewInDrawing();
    }

    private void endpointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeEnd, sender);
    }

    private void midpointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeMid, sender);
    }

    private void centerToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeCenter, sender);
    }

    private void nodeToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeNode, sender);
    }

    private void quadrantToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeQuad, sender);
    }

    private void intersectionToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeIntersection, sender);
    }

    private void insertionPointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeIns, sender);
    }

    private void perpendicularToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModePerpendicular, sender);
    }

    private void tangentToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeTangent, sender);
    }

    private void nearestToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeNear, sender);
    }

    private void apparentIntersectionToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeApparentIntersection, sender);
    }

    private void parallelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeParallel, sender);
    }

    private void startPointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      switchSnapModeSetting(ObjectSnapModes.ModeStartpoint, sender);
    }

    private void enableAllToolStripMenuItem_Click(object sender, EventArgs e)
    {
      System.Collections.IEnumerator enumerator = snapModesToolStripMenuItem.DropDownItems.GetEnumerator();
      enumerator.MoveNext(); // enable all
      enumerator.MoveNext(); // disable all
      enumerator.MoveNext(); // separator
      for (int i = 1; enumerator.MoveNext(); i++)
      {
        ((ToolStripMenuItem)enumerator.Current).Checked = true;
        SnapManager_OdaMgdApp.selectedSnapModes.setModeByIndex(i, true);
      }
    }

    private void disableAllToolStripMenuItem_Click(object sender, EventArgs e)
    {
      System.Collections.IEnumerator enumerator = snapModesToolStripMenuItem.DropDownItems.GetEnumerator();
      enumerator.MoveNext(); // enable all
      enumerator.MoveNext(); // disable all
      enumerator.MoveNext(); // separator
      for (int i = 1; enumerator.MoveNext(); i++)
      {
        ((ToolStripMenuItem)enumerator.Current).Checked = false;
        SnapManager_OdaMgdApp.selectedSnapModes.setModeByIndex(i, false);
      }
    }

    // ----------------------------- panel buttons processing ---------------------------------

    private void toolStripButtonOpen_Click(object sender, EventArgs e)
    {
      OpenDwgInNewDrawingForm(false, null, null);
    }

    private void toolStripButtonSave_Click(object sender, EventArgs e)
    {
      SaveDwgInActiveDrawingForm();
    }

    private void toolStripButtonZoomToExtents_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.ZoomExtents();
      }
    }

    private void toolStripButtonDolly_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        toolStripButtonDolly.Checked = !toolStripButtonDolly.Checked;
        ActiveDrawingForm.PanelState.DollyState = toolStripButtonDolly.Checked;
        ActiveDrawingForm.Dolly();
      }
    }

    private void toolStripButtonOrbit_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        toolStripButtonOrbit.Checked = !toolStripButtonOrbit.Checked;
        ActiveDrawingForm.PanelState.OrbitState = toolStripButtonOrbit.Checked;
        ActiveDrawingForm.Orbit();
      }
    }

    private void toolStripButtonWire2d_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Wire2dViewMode(true);
      }
    }

    private void toolStripButtonWire3d_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Wire3dViewMode(true);
      }
    }

    private void toolStripButtonHidden_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.HiddenViewMode(true);
      }
    }

    private void toolStripButtonFlatShaded_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.FlatShadedViewMode(true);
      }
    }

    private void toolStripButtontoolStripButtonGouraudShaded_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.GouraudShadedViewMode(true);
      }
    }

    private void toolStripButtonFlatShadedEd_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.FlatShadedEdViewMode(true);
      }
    }

    private void toolStripButtonGouraudShadedEd_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.GouraudShadedEdViewMode(true);
      }
    }

    private void toolStripButtonLine_Click(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        ActiveDrawingForm.Line();
      }
    }

    // ------------------------------- other buttons processing -------------------------------------

    private void showHideHistoryButton_Click(object sender, EventArgs e)
    {
      if (historyTextBox.Visible == false)
      {
        historyTextBox.Visible = true;
        historyTextBox.SelectionStart = historyTextBox.Text.Length;
        historyTextBox.ScrollToCaret();
        ((Button)sender).Text = "˅";
      }
      else
      {
        historyTextBox.Visible = false;
        ((Button)sender).Text = "˄";
      }
    }

    // ------------------------------- form events processing -------------------------------------

    private void textBoxConsole_KeyUp(object sender, KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Enter)
      {
        // finish input and selections if there were any
        if (ActiveDrawingForm != null)
        {
          if (ActiveDrawingForm.currentUserInputState == UserInputState.InProgress)
          {
            ActiveDrawingForm.currentUserInputState = UserInputState.Done;
            return;
          }
          if (ActiveDrawingForm.selectingBySelector)
          {
            ((UserIO.Editor_OdaMgdApp)Editor.Current).SelectionDone(true);
            return;
          }
        }
        // do command by name and params entered
        string command = textBoxConsole.Text.Trim().ToLower();
        DoCommandWithNameAndArguments(command.Split(' '));
      }
    }

    public void DoCommandFromMenu(object sender, EventArgs e)
    {
      string command = ((System.Windows.Forms.ToolStripItem)sender).Text;
      DoCommandWithNameAndArguments(command);
    }

    private void MainForm_MdiChildActivate(object sender, EventArgs e)
    {
      if (ActiveDrawingForm != null)
      {
        SetControlButtonsState(ActiveDrawingForm.PanelState);

        // comment this if don't want area view to reinitialize when switching active drawing
        if (isAreaViewActiveOnPanel)
        {
          deactivateAreaViewOnPanel();
          activateAreaViewOnPanel();
        }
      }
    }

    private void areaViewPanel_Paint(object sender, PaintEventArgs e)
    {
      if (helperDeviceAreaView != null)
        helperDeviceAreaView.Update();
    }

    public void DrawingForm_Move(object sender, System.EventArgs e)
    {
      UpdateAreaView();
    }

    // ---------------------------------- helping functions ---------------------------------------

    void PreopenDwgOnFormOpeningIfNeeded(String path)
    {
      if (path != null)
        OpenDwgInNewDrawingForm(false, null, path);
    }

    void OpenDwgInNewDrawingForm(bool partial, AuditInfo auditInfo, String pathGiven)
    {
      String path;
      if (pathGiven == null)
      {
        if (DialogResult.OK != openFileDialog.ShowDialog(this))
        {
          WriteTextAndHistoryText("No file chosen for opening.");
          return;
        }

        path = openFileDialog.FileName;
      }
      else
      {
        path = pathGiven;
      }

      if (!System.IO.File.Exists(path))
      {
        MessageBox.Show("Could not find file:\n" + path, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        return;
      }

      DrawingForm newForm = new DrawingForm(path, partial, auditInfo);
      newForm.MdiParent = this;
      newForm.WindowState = FormWindowState.Maximized;
      newForm.SetActiveViewModeButtons();
      newForm.Show();

      UserSettings.LastOpenedFile = path;
      UpdateRecentFilesMenu();
      UserSettings.Save();
    }

    void CreateDwgInNewDrawingForm()
    {
      DrawingForm newForm = new DrawingForm(null, false, null);
      newForm.MdiParent = this;
      newForm.WindowState = FormWindowState.Maximized;
      newForm.SetActiveViewModeButtons();
      newForm.Show();
    }

    void SaveDwgInActiveDrawingForm()
    {
      if (ActiveDrawingForm != null)
      {
        if (ActiveDrawingForm.Database != null)
        {
          ActiveDrawingForm.ApplyViewChanges();
          try
          {
            ActiveDrawingForm.Database.Save();
          }
          catch(Teigha.Runtime.Exception e)
          {
            if (e.ErrorStatus == ErrorStatus.NoFileName)
              saveAsToolStripMenuItem_Click(null, null);
            else
              throw;
          }
        }
      }
    }

    public void WriteText(String text)
    {
      textBoxConsole.Text = text;
    }

    public void WriteTextAndHistoryText(String text)
    {
      textBoxConsole.Text = text;
      historyTextBox.AppendText(text + Environment.NewLine);
    }

    public String ReadText()
    {
      return textBoxConsole.Text;
    }

    public string GetOpenPathFromDialog(string prompt, out DialogResult result)
    {
      netloadCommandDialog.FileName = prompt;
      result = netloadCommandDialog.ShowDialog();
      string path = "";
      if (result == System.Windows.Forms.DialogResult.OK)
        path = netloadCommandDialog.FileName;
      return path;
    }

    public string GetSavePathFromDialog(string proposedFileName)
    {
      string path = "";
      saveAsFileDialog.InitialDirectory = System.IO.Path.GetDirectoryName(proposedFileName);
      saveAsFileDialog.FileName = System.IO.Path.GetFileName(proposedFileName);
      if (saveAsFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
      {
        path = saveAsFileDialog.FileName;
      }
      return path;
    }

    void UpdateRecentFilesMenu()
    {
      System.Windows.Forms.MenuStrip menu = this.MainMenu;
      if (menu == null) // means attempt to update menu before window appeared
        return;

      recentFilesToolStripMenuItem.DropDownItems.Clear();
      StringCollection lastOpenedFiles = UserSettings.LastOpenedFiles;

      foreach (String str in lastOpenedFiles)
      {
        System.Windows.Forms.ToolStripItem newRecentFileItem = recentFilesToolStripMenuItem.DropDownItems.Add(str);
        newRecentFileItem.Click += openRecentToolStripMenuItem_Click;
      }
    }

    public void UpdateRecentCommandsMenu()
    {
      System.Windows.Forms.MenuStrip menu = this.MainMenu;
      if (menu == null) // means attempt to update menu before window appeared
        return;

      recentCommandsToolStripMenuItem.DropDownItems.Clear();
      StringCollection lastExecutedCommands = UserSettings.LastExecutedCommands;

      foreach (String str in lastExecutedCommands)
      {
        System.Windows.Forms.ToolStripItem newRecentCommandItem = recentCommandsToolStripMenuItem.DropDownItems.Add(str);
        newRecentCommandItem.Click += DoCommandFromMenu;
      }
    }

    public void UpdateMenuWithCommands()
    {
      UserIO.Editor_OdaMgdApp ed = (UserIO.Editor_OdaMgdApp)Editor.Current;
      ToolStripMenuItem menu = CommandsMenu;

      if (menu == null) // means we are loading commands before window appeared
        return;

      menu.DropDownItems.Clear();

      System.Collections.Generic.List<CommandTextDescription> commands = ed.ListCommands();
      foreach (CommandTextDescription command in commands)
      {
        System.Windows.Forms.ToolStripItem groupMenu = getSubitemWithName(command.groupName, menu);

        if (groupMenu == null)
          groupMenu = menu.DropDownItems.Add(command.groupName);

        System.Windows.Forms.ToolStripItem newCommandItem =
          ((System.Windows.Forms.ToolStripMenuItem)groupMenu).DropDownItems.Add(command.command);

        newCommandItem.Click += DoCommandFromMenu;
      }
    }

    System.Windows.Forms.ToolStripMenuItem getSubitemWithName(string name, System.Windows.Forms.ToolStripMenuItem item)
    {
      foreach (System.Windows.Forms.ToolStripMenuItem subItem in item.DropDownItems)
      {
        if (subItem.Text == name)
        {
          return subItem;
        }
      }
      return null;
    }

    public void DoCommandWithNameAndArguments(params object[] parameter)
    {
      if (ActiveDrawingForm == null || ActiveDrawingForm.Database == null)
      {
        WriteTextAndHistoryText("No active drawing to apply command.");
        return;
      }

      try
      {
        historyTextBox.AppendText(parameter[0] + Environment.NewLine);
        Editor.Current.Command(parameter);
        historyTextBox.AppendText(Environment.NewLine);
        ReinitInputTextAndResetFocus();
      }
      catch (System.Exception err)
      {
        MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    public void SetRedrawTimeDisplay(String timeString)
    {
      redrawMsLabel.Text = timeString;
    }

    public void SetControlButtonsState(ControlButtonState state)
    {
      if (toolStripButtonDolly.Checked != state.DollyState) toolStripButtonDolly.Checked = state.DollyState;
      if (toolStripButtonOrbit.Checked != state.OrbitState) toolStripButtonOrbit.Checked = state.OrbitState;
      if (toolStripButtonWire2d.Checked != state.Wire2dState) toolStripButtonWire2d.Checked = state.Wire2dState;
      if (toolStripButtonWire3d.Checked != state.Wire3dState) toolStripButtonWire3d.Checked = state.Wire3dState;
      if (toolStripButtonHidden.Checked != state.HiddenState) toolStripButtonHidden.Checked = state.HiddenState;
      if (toolStripButtonFlatShaded.Checked != state.FlatShadedState) toolStripButtonFlatShaded.Checked = state.FlatShadedState;
      if (toolStripButtonGouraudShaded.Checked != state.GouraudShadedState) toolStripButtonGouraudShaded.Checked = state.GouraudShadedState;
      if (toolStripButtonFlatShadedEd.Checked != state.FlatShadedEdState) toolStripButtonFlatShadedEd.Checked = state.FlatShadedEdState;
      if (toolStripButtonGouraudShadedEd.Checked != state.GouraudShadedEdState) toolStripButtonGouraudShadedEd.Checked = state.GouraudShadedEdState;
      if (toolStripButtonLine.Checked != state.DrawLineButtonState) toolStripButtonLine.Checked = state.DrawLineButtonState;
      if (inTheDrawingToolStripMenuItem.Checked != state.AreaViewInDrawingState) inTheDrawingToolStripMenuItem.Checked = state.AreaViewInDrawingState;
    }

    void activateAreaViewOnPanel()
    {
      if (ActiveDrawingForm == null || ActiveDrawingForm.Database == null)
      {
        WriteTextAndHistoryText("No active drawing to apply area view.");
        return;
      }

      // in active drawing form exists database, which should be displayed at another control
      areaViewPanel.Visible = true;
      // do like in initializeGraphics of the drawing form

      helperDeviceAreaView = null;
      graphicsDeviceAreaView = null;
      gsModuleAreaView = (GsModule)SystemObjects.DynamicLinker.LoadModule("WinOpenGL.txv", false, true);

      graphicsAreaView = Graphics.FromHwnd(areaViewPanel.Handle);

      graphicsDeviceAreaView = gsModuleAreaView.CreateDevice();

      // setup device properties
      using (Dictionary props = graphicsDeviceAreaView.Properties)
      {
        if (props.Contains("WindowHWND")) // Check if property is supported
          props.AtPut("WindowHWND", new RxVariant(areaViewPanel.Handle)); // hWnd necessary for DirectX device
        if (props.Contains("WindowHDC")) // Check if property is supported
          props.AtPut("WindowHDC", new RxVariant(graphicsAreaView.GetHdc())); // hWindowDC necessary for Bitmap device
        if (props.Contains("DoubleBufferEnabled")) // Check if property is supported
          props.AtPut("DoubleBufferEnabled", new RxVariant(true));
        if (props.Contains("EnableSoftwareHLR")) // Check if property is supported
          props.AtPut("EnableSoftwareHLR", new RxVariant(true));
        if (props.Contains("DiscardBackFaces")) // Check if property is supported
          props.AtPut("DiscardBackFaces", new RxVariant(true));

        // setup paperspace viewports or tiles
        ContextForDbDatabase ctx = new ContextForDbDatabase(ActiveDrawingForm.Database);
        ctx.UseGsModel = true;

        helperDeviceAreaView = LayoutHelperDevice.SetupActiveLayoutViews(graphicsDeviceAreaView, ctx);
        Aux.preparePlotstyles(ActiveDrawingForm.Database, ctx);
      }
      // set palette
      helperDeviceAreaView.SetLogicalPalette(Device.DarkPalette);
      // set output extents (like resize())
      helperDeviceAreaView.OnSize(areaViewPanel.Size);
      helperDeviceAreaView.Update();

      isAreaViewActiveOnPanel = true;
      onThePanelToolStripMenuItem.Checked = true;

      foreach(Form form in this.MdiChildren)
      {
        form.Move += DrawingForm_Move;
      }
    }

    void deactivateAreaViewOnPanel()
    {
      areaViewPanel.Visible = false;
      onThePanelToolStripMenuItem.Checked = false;

      if (graphicsAreaView != null)
      {
        graphicsAreaView.Dispose();
        graphicsAreaView = null;
      }
      if (helperDeviceAreaView != null)
      {
        helperDeviceAreaView.Dispose();
        helperDeviceAreaView = null;
      }
      if (graphicsDeviceAreaView != null)
      {
        graphicsDeviceAreaView.Dispose();
        graphicsDeviceAreaView = null;
      }
      if (gsModuleAreaView != null)
      {
        gsModuleAreaView.Dispose();
        gsModuleAreaView = null;
      }

      isAreaViewActiveOnPanel = false;
      foreach (Form form in this.MdiChildren)
      {
        form.Move -= DrawingForm_Move;
      }
    }

    // this should be called when mdi child windows are being moved;
    // it prevents them from drawing their traces on area panel by background
    public void UpdateAreaView()
    {
      graphicsDeviceAreaView.Update();
    }

    public void ActiveDrawingFormClosing()
    {
      deactivateAreaViewOnPanel();
    }

    void switchSnapModeSetting(ObjectSnapModes mode, Object sender)
    {
      ToolStripMenuItem item = sender as ToolStripMenuItem;
      item.Checked = !item.Checked;
      SnapManager_OdaMgdApp.selectedSnapModes.setModeByIndex((int)mode, item.Checked);
    }
  }

  // ------------------------------------------ enumerations --------------------------------------

  public enum MouseMode
  {
    Quiescent,
    Selection,
    DragDrop,
    ZoomWindow,
    Zoom,
    Orbit,
    Dolly
  }

}
