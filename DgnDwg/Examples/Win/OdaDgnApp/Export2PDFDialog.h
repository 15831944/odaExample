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
#if !defined(AFX_EXPORT2PDFDIALOG_H__4AF80B03_7FB7_42D3_9281_E8A5F4FB9A36__INCLUDED_)
#define AFX_EXPORT2PDFDIALOG_H__4AF80B03_7FB7_42D3_9281_E8A5F4FB9A36__INCLUDED_

//#include "Export2PDFPreview.h"

#include "PdfExportParams.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Export2PDFDialog.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CExport2PDFDialog dialog

class CExport2PDFDialog : public CDialog
{
// Construction
public:
	CExport2PDFDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExport2PDFDialog)
	enum { IDD = IDD_PDFEXPORT };
	CString	m_FileName;
	CString	m_Autor;
	CString	m_Keywords;
	CString	m_Creator;
	CString	m_Title;
	CString	m_sPlotStyleTable;
	BOOL	m_bEmbedded;
  BOOL	m_bEmbeddedOptimized;
	BOOL	m_bSimpleGeomOpt;
	BOOL	m_bSHXAsGeometry;
	BOOL	m_bTTFAsGeometry;
  BOOL	m_bZoomToExtents;
  BOOL	m_bEnableLayers;
  BOOL	m_bExportOffLayers;
  BOOL	m_bEncoded;
  //BOOL	m_bMono;
  BOOL	m_bPlotStyleTable;
  BOOL	m_bASCIIHEXEncoded;
  BOOL  m_bTextSearchable;
  BOOL  m_bCropImages;
  BOOL  m_bDCTCompression;
  BOOL  m_bUsePRC;
  BOOL  m_bMeasuring;
  BOOL  m_bUseGsCache;
	CString	m_Producer;
	CString	m_Subject;
	double	m_dPaperH;
	double	m_dPaperW;
  double  m_dLeftMargin;
  double  m_dRightMargin;
  double  m_dTopMargin;
  double  m_dBottomMargin;
	int		  m_Layouts;
	int		  m_Views;
  BOOL m_bUseHLR;
  BOOL m_bExportHyperlinks;
  BOOL m_bLinearized;
  OdDgDatabasePtr m_pDb;
  OdDgHostAppServices *m_pHost;
  unsigned int m_iHatchDPI;
  unsigned int m_iGeomDPI;
  unsigned int m_iBWImagesDPI;
  unsigned int m_iColorImagesDPI;
  unsigned int m_iDCTQuality;
  unsigned int m_iPdfAMode;
  BOOL m_bMergeLinesCrossing;
  CComboBox         m_colorPolicy;
  OdDgElementId     m_idFence;

  OdArray<OdString> m_LayoutsViews;

  OdString m_UserPassword;
  OdString m_OwnerPassword;
  TD_PDF_2D_EXPORT::PDFExportParams::PDFAccessPermissionsFlags m_AccessPermissionFlags;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExport2PDFDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  afx_msg void OnCheckZoom();
  afx_msg void OnParametersUpdated();
  afx_msg void OnCheckEmbedded();
  afx_msg void OnClickCustomButton();
  afx_msg void OnCheckTextAsGeometry();
  afx_msg void OnCheckLayers();
  afx_msg void OnClickSelectViewButton();
  afx_msg void OnClickSecurityButton();
	//}}AFX_VIRTUAL

// Implementation
protected:
//  CExport2PDFPreview dlg;

  void fillLayoutList(OdArray<OdString> &layouts/*, OdArray<double> &divWH*/);
  OdDbStub* getNextViewForActiveLayout(OdDbStub* objectId);
  OdUInt32 ExportToPdf(OdString pdfFileName);

	// Generated message map functions
	//{{AFX_MSG(CExport2PDFDialog)
	afx_msg void OnBrowse();
	afx_msg void OnExport();
  afx_msg void OnBnClickedPlotStyleTable();
	afx_msg void OnBrowse2();
//  afx_msg void OnPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedPrc();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORT2PDFDIALOG_H__4AF80B03_7FB7_42D3_9281_E8A5F4FB9A36__INCLUDED_)
