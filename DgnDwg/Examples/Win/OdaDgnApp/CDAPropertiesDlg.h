/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
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
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "RxObject.h"
#include "CDAPropertiesListCtrl.h"

// CCDAPropertiesDlg dialog

class CCDAPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CCDAPropertiesDlg)

public:
  CCDAPropertiesDlg(CWnd* pParent, OdRxObject* pDb, OdRxObject* pObject, OdInt32 iSubPropertyIndex = -1, const OdString& strPropName = OdString::kEmpty);   // standard constructor
	virtual ~CCDAPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_CDA_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnOk();

private:
  CCDAPropertiesListCtrl m_listCtrl;
  OdInt32           m_iSubPropertyIndex;
  OdString          m_strPropName;
  OdRxObject*       m_pDb;
  OdRxObject*       m_pObject;
};
