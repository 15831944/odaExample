namespace OdaMgdApp
{
  partial class DrawingForm
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
      this.drawingPanel = new System.Windows.Forms.Panel();
      this.SuspendLayout();
      // 
      // drawingPanel
      // 
      this.drawingPanel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.drawingPanel.Location = new System.Drawing.Point(0, 0);
      this.drawingPanel.Name = "drawingPanel";
      this.drawingPanel.Size = new System.Drawing.Size(800, 450);
      this.drawingPanel.TabIndex = 0;
      this.drawingPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.drawingPanel_Paint);
      this.drawingPanel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.drawingPanel_MouseClick);
      this.drawingPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.drawingPanel_MouseDown);
      this.drawingPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.drawingPanel_MouseMove);
      this.drawingPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.drawingPanel_MouseUp);
      this.drawingPanel.Resize += new System.EventHandler(this.drawingPanel_Resize);
      // 
      // DrawingForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(800, 450);
      this.Controls.Add(this.drawingPanel);
      this.Name = "DrawingForm";
      this.Text = "DrawingForm";
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.DrawingForm_FormClosing);
      this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.DrawingForm_KeyDown);
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Panel drawingPanel;
  }
}