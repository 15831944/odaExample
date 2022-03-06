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

namespace OdExIfcViewerSwigMgd
{
  partial class Form1
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.btnOpenIfcFile = new System.Windows.Forms.Button();
      this.btnPan = new System.Windows.Forms.CheckBox();
      this.btnRotation = new System.Windows.Forms.CheckBox();
      this.panelRendering = new System.Windows.Forms.Panel();
      this.SuspendLayout();
      // 
      // btnOpenIfcFile
      // 
      this.btnOpenIfcFile.Location = new System.Drawing.Point(12, 9);
      this.btnOpenIfcFile.Name = "btnOpenIfcFile";
      this.btnOpenIfcFile.Size = new System.Drawing.Size(75, 23);
      this.btnOpenIfcFile.TabIndex = 3;
      this.btnOpenIfcFile.Text = "Open Ifc File";
      this.btnOpenIfcFile.UseVisualStyleBackColor = true;
      this.btnOpenIfcFile.Click += new System.EventHandler(this.BtnOpenDwgFile_Click);
      // 
      // btnPan
      // 
      this.btnPan.Appearance = System.Windows.Forms.Appearance.Button;
      this.btnPan.AutoSize = true;
      this.btnPan.Location = new System.Drawing.Point(93, 9);
      this.btnPan.Name = "btnPan";
      this.btnPan.Size = new System.Drawing.Size(36, 23);
      this.btnPan.TabIndex = 1;
      this.btnPan.Text = "Pan";
      this.btnPan.UseVisualStyleBackColor = true;
      this.btnPan.CheckedChanged += new System.EventHandler(this.btnPan_CheckedChanged);
      // 
      // btnRotation
      // 
      this.btnRotation.Appearance = System.Windows.Forms.Appearance.Button;
      this.btnRotation.AutoSize = true;
      this.btnRotation.Location = new System.Drawing.Point(135, 9);
      this.btnRotation.Name = "btnRotation";
      this.btnRotation.Size = new System.Drawing.Size(57, 23);
      this.btnRotation.TabIndex = 2;
      this.btnRotation.Text = "Rotation";
      this.btnRotation.UseVisualStyleBackColor = true;
      this.btnRotation.CheckedChanged += new System.EventHandler(this.btnRotation_CheckedChanged);
      // 
      // panelRendering
      // 
      this.panelRendering.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.panelRendering.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.panelRendering.Location = new System.Drawing.Point(12, 38);
      this.panelRendering.Name = "panelRendering";
      this.panelRendering.Size = new System.Drawing.Size(776, 400);
      this.panelRendering.TabIndex = 1;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(800, 450);
      this.Controls.Add(this.btnRotation);
      this.Controls.Add(this.btnPan);
      this.Controls.Add(this.btnOpenIfcFile);
      this.Controls.Add(this.panelRendering);
      this.Name = "Form1";
      this.Text = "OdExIfcViewerSwigMgd";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion
    private System.Windows.Forms.CheckBox btnPan;
    private System.Windows.Forms.CheckBox btnRotation;
    private System.Windows.Forms.Panel panelRendering;
    private System.Windows.Forms.Button btnOpenIfcFile;
  }
}

