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

using ODA.Ifc.IfcCore;
using OdIfcExamplesLibMgd;
using OdIfcExamplesLibUIMgd;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Teigha.Core;

namespace OdExIfcViewerSwigMgd
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();

      this.Load += Form1_Load;
      this.FormClosing += Form1_FormClosing;
    }

    private void Form1_FormClosing(object sender, FormClosingEventArgs e)
    {
      renderingPanel.UnInit();
      UnInitODA();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      InitODA();
      CreateGUI();
    }

    private MemoryTransaction m_rootMemoryTransaction;
    private OdIfcApplicationServicesSample m_services;
    private void InitODA()
    {
      //Create Root Memory Transaction , more detail see: https://docs.opendesign.com/tnet/tnet_Memory.html
      m_rootMemoryTransaction = MemoryManager.GetMemoryManager().StartTransaction();

      //Create Host Application Services
      m_services = new OdIfcApplicationServicesSample(ActivationData.userInfo, ActivationData.userSignature);

      /**********************************************************************/
      /* Initialize ODA SDK                                                 */
      /**********************************************************************/
      Globals.odrxInitialize(m_services.m_SystemServices);
      Globals.odDbRootInitialize();
      Globals.odgsInitialize();

      /**********************************************************************/
      /* Initialize IfcCore                                                 */
      /**********************************************************************/

      IfcCore_Globals.odIfcInitialize(false /* No CDA */, true /* No geometry calculation needed */);
    }

    private void UnInitODA()
    {
      MemoryManager.GetMemoryManager().StopTransaction(m_rootMemoryTransaction);

      /**********************************************************************/
      /* Uninitialize IfcCore                                               */
      /**********************************************************************/
      IfcCore_Globals.odIfcUninitialize();

      Globals.odgsUninitialize();
      Globals.odDbRootUninitialize();
      /**********************************************************************/
      /* Uninitialize ODA SDK                                               */
      /**********************************************************************/
      Globals.odrxUninitialize();
    }

    private OdExViewIfcControl renderingPanel;

    private void CreateGUI()
    {
      renderingPanel = new OdExViewIfcControl();
      renderingPanel.Dock = DockStyle.Fill;
      panelRendering.Controls.Add(renderingPanel);

      renderingPanel.EnableZoom(true);
    }

    private void btnPan_CheckedChanged(object sender, EventArgs e)
    {
      if(btnPan.Checked)
      {
        btnRotation.Checked = false;
        renderingPanel.EnablePan(true);
        renderingPanel.EnableRotation(false);
      }
      else
      {
        renderingPanel.EnablePan(false);
      }
    }

    private void btnRotation_CheckedChanged(object sender, EventArgs e)
    {
      if (btnRotation.Checked)
      {
        btnPan.Checked = false;
        renderingPanel.EnableRotation(true);
        renderingPanel.EnablePan(false);
      }
      else
      {
        renderingPanel.EnableRotation(false);
      }
    }


    private void BtnOpenDwgFile_Click(object sender, EventArgs e)
    {
      OpenAndRenderIfc();
    }

    private void OpenAndRenderIfc()
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "Ifc files (*.ifc)|*.ifc|All files (*.*)|*.*";

      if (openFileDialog.ShowDialog() == DialogResult.OK)
      {
        renderingPanel.UnInit();

        StartTransactionForDatabase();

        String ifcFilePath = openFileDialog.FileName;

        OdIfcFile database = m_services.m_HostAppServices.createDatabase(IfcSchema.kScmUndefined);
        if( database.readFile(ifcFilePath) != OdResult.eOk)
        {
          MessageBox.Show("Cannot open ifc file");
          return;
        }

        OdResult res = database.composeEntities();
        if (res != OdResult.eOk)
        {
          if (res == OdResult.eFileInternalErr)
          {
            throw new OdError(OdResult.eFileInternalErr);
          }
          if (res == OdResult.eNullPtr)
          {
            throw new OdError(OdResult.eNullPtr);
          }
        }

        renderingPanel.Init(database);
      }
    }

    private MemoryTransaction mTrDatabase;

    private void StartTransactionForDatabase()
    {
      if (mTrDatabase != null)
        StopTransactionForDatabase();

      mTrDatabase = MemoryManager.GetMemoryManager().StartTransaction();
    }

    private void StopTransactionForDatabase()
    {
      if (mTrDatabase != null)
      {
        MemoryManager.GetMemoryManager().StopTransaction(mTrDatabase);
        mTrDatabase = null;
      }
    }
  }
}
