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
#if !defined(AFX_CDAPROPLISTVIEW_H_INCLUDED_)
#define AFX_CDAPROPLISTVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;
#include "afxcmn.h"
#include "OdArray.h"
#include "RxProperty.h"
#include "RxAttribute.h"
#include "RxValue.h"
#include "resource.h"
#include "Ge/GePoint3d.h"
// ColorListCtrl.h : header file
//

#define UINT unsigned int
#define ULONG unsigned long

OdRxPropertyBase* getActualProperty(OdRxObject* pObject, OdRxPropertyBase* pProperty, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex);

/////////////////////////////////////////////////////////////////////////////
// CCDAPropertiesListCtrl view

class CCDAPropertiesListCtrl : public CListCtrl
{
public:
  CCDAPropertiesListCtrl();
  virtual ~CCDAPropertiesListCtrl();
	DECLARE_DYNCREATE(CCDAPropertiesListCtrl)

// Operations
public:

  void  initData(OdRxObject* pDb, OdRxObject* pObject, const RECT& wndRect, OdInt32 iSubPropertyIndex = -1, 
    const OdString& strPropName = OdString::kEmpty, OdInt32 iArrayIndex = -1, OdInt32 iTopOffset = 0, bool bIgnoreUnionType = false);
  void  onMoveOwner();
  void  setRxObject(OdRxObject* pObject, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex);
  void  updatePropertyCtrlPositions();
  void  updateControlData();
  void  addPropertyCtrl(OdRxPropertyBase* pProperty, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1, const OdString& strPropertyName = OdString::kEmpty, OdInt32 iFixedSubPropertyIndex = -1);
  void  addCategoryCtrl(const OdString& strCategory);
  CWnd* createDefaultCDAControl(OdRxObject* pObject, OdRxPropertyBase* pProperty, const CRect& rItem, CWnd* pParentWnd, OdInt32 iRescID, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

	// Generated message map functions
protected:
  afx_msg void OnDestroy();
  afx_msg void OnVScroll(UINT SBCode, UINT Pos, CScrollBar *SB);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	/*//{{AFX_MSG(CCDAPropertiesListCtrl)
	//}}AFX_MSG*/
	DECLARE_MESSAGE_MAP()

protected:
	//afx_msg void CustDraw( NMHDR * pNotifyStruct, LRESULT * result );

private:
  bool              m_bDataInitialized;
  OdInt32           m_iDefaultRowHeight;
  CWnd*             m_pNameStatic;
  CWnd*             m_pValueStatic;
  OdArray<CWnd*>    m_arrWndPtr;
  OdRxObject*       m_pDb;
  OdRxObject*       m_pObject;
  OdString          m_strPropertyName;
  OdInt32           m_iSubPropertyIndex;
  OdInt32           m_iArrayIndex;
  OdInt32           m_iTopOffset;
  bool              m_bIgnoreUnionType;
};

/////////////////////////////////////////////////////////////////////////////
// CCDABoolCheckBox ( bool )

class CCDABoolCheckBox : public CButton
{
  public:
    CCDABoolCheckBox();
    virtual ~CCDABoolCheckBox();
    DECLARE_DYNCREATE(CCDABoolCheckBox)

  public:
    static CWnd* createCDABoolCheckBox(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, const CRect& btnRect,
      CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

    bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, const CRect& btnRect,
      CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

    OdUInt32 getRscIndex() const;

    bool getPropertyValue(bool& bValue) const;
    void setPropertyValue(bool bValue);

  protected:
    DECLARE_MESSAGE_MAP()
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

  private:
    OdRxObject*           m_pDb;
    OdRxObject*           m_pObject;
    OdRxPropertyBasePtr   m_pProperty;
    OdInt32               m_iArrayIndex;
    OdInt32               m_iSubPropertyIndex;
    OdUInt32              m_uRscIndex;
    bool                  m_bValue;
    bool                  m_bReadOnly;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAEditCtrl (OdUInt8, OdUInt16, OdUInt32, OdUInt64, OdInt8, OdInt16, OdInt32, OdInt64, double, float, OdString, OdAnsiString )

class CCDAEditCtrl : public CEdit
{
public:

  enum CCDAEditCtrlValueTypes
  {
    kInt8   = 0,
    kInt16  = 1,
    kInt32  = 2,
    kInt64  = 3,
    kUInt8  = 4,
    kUInt16 = 5,
    kUInt32 = 6,
    kUInt64 = 7,
    kDouble = 8,
    kFloat =  9,
    kString = 10,
    kAnsiString = 11 
  };

public:
  CCDAEditCtrl();
  virtual ~CCDAEditCtrl();
  DECLARE_DYNCREATE(CCDAEditCtrl)

public:
  static CWnd* createCDAEditCtrl(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDAEditCtrlValueTypes uValueType,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDAEditCtrlValueTypes uValueType,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  OdUInt32 getRscIndex() const;

  bool getPropertyValue(OdString& strValue) const;
  bool setPropertyValue(const OdString& strValue);

protected:
  DECLARE_MESSAGE_MAP()
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
  OdRxObject*            m_pDb;
  OdRxObject*            m_pObject;
  OdRxPropertyBasePtr    m_pProperty;
  OdInt32                m_iArrayIndex;
  OdInt32                m_iSubPropertyIndex;
  OdUInt32               m_uRscIndex;
  OdString               m_strValue;
  bool                   m_bReadOnly;
  CCDAEditCtrlValueTypes m_uValueType;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAComboBox (enums, from id)

class CCDAComboBox : public CComboBox
{
public:

  enum CCDAComboBoxValueTypes
  {
    kEnum = 0,
    kCollection = 1,
  };

public:
  CCDAComboBox();
  virtual ~CCDAComboBox();
  DECLARE_DYNCREATE(CCDAComboBox)

public:
  static CWnd* createCDAComboBox(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDAComboBoxValueTypes uValueType,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDAComboBoxValueTypes uValueType,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  OdUInt32 getRscIndex() const;

  bool getPropertyValueAndInitCBData();
  bool setPropertyValue(OdInt32 iCBIndex);

protected:
  DECLARE_MESSAGE_MAP()
  virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);

private:
  OdRxObject*            m_pDb;
  OdRxObject*            m_pObject;
  OdRxPropertyBasePtr    m_pProperty;
  OdInt32                m_iArrayIndex;
  OdInt32                m_iSubPropertyIndex;
  OdUInt32               m_uRscIndex;
  bool                   m_bReadOnly;
  CCDAComboBoxValueTypes m_uValueType;
  OdInt32                m_iCurIndex;
  OdArray<OdString>      m_arrPathToCollection;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAStdTypeButton (arrays of standard types, OdGePoint2d, OdGePoint3d...)

class CCDAStdTypeButton : public CButton
{
public:

  enum CCDAStdButtonValueTypes
  {
    kBoolArray       = 0,
    kInt8Array       = 1,
    kInt16Array      = 2,
    kInt32Array      = 3,
    kInt64Array      = 4,
    kUInt8Array      = 5,
    kUInt16Array     = 6,
    kUInt32Array     = 7,
    kUInt64Array     = 8,
    kDoubleArray     = 9,
    kFloatArray      = 10,
    kStringArray     = 11,
    kAnsiStringArray = 12,
    kDouble2dArray   = 13,
    kInt322dArray    = 14,
    kPoint3dArray    = 15,
    kTimeStampArray  = 16,
    kPoint2d         = 17,
    kPoint3d         = 18,
    kVector2d        = 19,
    kVector3d        = 20,
    kScale3d         = 21,
    kOdDbHandle      = 22,
    kOdRect          = 23,
    kExtents2d       = 24,
    kExtents3d       = 25,
    kMatrix2d        = 26,
    kMatrix3d        = 27,
    kQuaternion      = 28,
    kDoubleColor     = 29,
    kMaterialColor   = 30,
    kCmTransparency  = 31,
    kRxObject        = 32,
    kReference       = 33,
    kUnionType       = 34
  };

public:
  CCDAStdTypeButton();
  virtual ~CCDAStdTypeButton();
  DECLARE_DYNCREATE(CCDAStdTypeButton)

public:
  static CWnd* createCDAStdButton(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDAStdButtonValueTypes uValueType,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDAStdButtonValueTypes uValueType,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  OdUInt32 getRscIndex() const;

  bool onButtonClick();

  OdString getPropertyValueStr(const OdRxValue& propValue);

protected:
  DECLARE_MESSAGE_MAP()
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
  OdRxObject*             m_pDb;
  OdRxObject*             m_pObject;
  OdRxPropertyBasePtr     m_pProperty;
  OdInt32                 m_iArrayIndex;
  OdInt32                 m_iSubPropertyIndex;
  OdUInt32                m_uRscIndex;
  bool                    m_bReadOnly;
  CCDAStdButtonValueTypes m_uValueType;
  OdRxValue               m_curValue;
  OdString                m_strName;
};

///////////////////////////////////////////////////////////////////////////////////
// CCDACollectionButton (indexed properties and collections)

class CCDACollectionButton : public CButton
{
public:

  enum CCDACollectionButtonTypes
  {
    kArray           = 0,
    kCollection      = 1
  };

public:
  CCDACollectionButton();
  virtual ~CCDACollectionButton();
  DECLARE_DYNCREATE(CCDACollectionButton)

public:
  static CWnd* createCDACollectionButton(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDACollectionButtonTypes uCtrlType,
    OdRxValue& typeValue, const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1, bool bEnable = true);

  static CWnd* createCDACollectionButton(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDACollectionButtonTypes uCtrlType,
    const OdString& strTypeValue, const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1, bool bEnable = true);

  bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty, CCDACollectionButtonTypes uCtrlType, OdRxValue& typeValue, 
    const OdString& strTypeValue, const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1, bool bEnable = true);

  OdUInt32 getRscIndex() const;

  bool onButtonClick();

protected:
  DECLARE_MESSAGE_MAP()
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
  OdRxObject*               m_pDb;
  OdRxObject*               m_pObject;
  OdRxPropertyBasePtr       m_pProperty;
  OdInt32                   m_iArrayIndex;
  OdInt32                   m_iSubPropertyIndex;
  OdUInt32                  m_uRscIndex;
  bool                      m_bReadOnly;
  CCDACollectionButtonTypes m_uCtrlType;
  OdRxValue                 m_typeValue;
  OdString                  m_strTypeName;
  OdString                  m_strName;
};


///////////////////////////////////////////////////////////////////////
// CCDAOdColorButton (OdCmEntityColor)

class CCDAOdColorCombo : public CComboBox
{

public:
  CCDAOdColorCombo();
  virtual ~CCDAOdColorCombo();
  DECLARE_DYNCREATE(CCDAOdColorCombo)

public:
  static CWnd* createCDAColorCombo(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  OdUInt32 getRscIndex() const;

  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  OdArray<ODCOLORREF> getOdPalette(OdRxAttribute* pAttr, OdRxObject* pDb);

protected:
  DECLARE_MESSAGE_MAP()
  virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);

private:
  OdRxObject*             m_pDb;
  OdRxObject*             m_pObject;
  OdRxPropertyBasePtr     m_pProperty;
  OdInt32                 m_iArrayIndex;
  OdInt32                 m_iSubPropertyIndex;
  OdInt32                 m_iItemIndex;
  OdUInt32                m_uRscIndex;
  bool                    m_bReadOnly;
  OdCmEntityColor         m_curColor;
  OdArray<ODCOLORREF>     m_palette;
  ODCOLORREF              m_rgbColor;
  OdString                m_strName;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAStdTypeButton (arrays of standard types OdTimeStamp)

class CCDADateTimeCtrl : public CDateTimeCtrl
{

public:
  CCDADateTimeCtrl();
  virtual ~CCDADateTimeCtrl();
  DECLARE_DYNCREATE(CCDADateTimeCtrl)

public:
  static CWnd* createCDADateTimeCtrl(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  bool initData(OdRxObject* pDb, OdRxObject* pObject, OdRxPropertyBase* pProperty,
    const CRect& btnRect, CWnd* pParentWnd, OdUInt32 uRscIndex, OdInt32 iSubPropertyIndex = -1, OdInt32 iArrayIndex = -1);

  OdUInt32 getRscIndex() const;

protected:
  DECLARE_MESSAGE_MAP()
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
  OdRxObject*             m_pDb;
  OdRxObject*             m_pObject;
  OdRxPropertyBasePtr     m_pProperty;
  OdInt32                 m_iArrayIndex;
  OdInt32                 m_iSubPropertyIndex;
  OdUInt32                m_uRscIndex;
  bool                    m_bReadOnly;
  OdRxValue               m_curValue;
  OdString                m_strName;
  CTime                   m_oldTime;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAStdBtnSetValueDlg dialog

class CCDAStdBtnSetValueDlg : public CDialog
{
  DECLARE_DYNAMIC(CCDAStdBtnSetValueDlg)

public:

  enum CCDAStdBtnSetValueDlgType
  {
    kPoint2d = 0,
    kPoint3d = 1,
    kVector2d = 2,
    kVector3d = 3,
    kScale3d = 4,
    kExtents2d = 5,
    kExtents3d = 6,
    kMatrix2d = 7,
    kMatrix3d = 8,
    kQuaternion = 9,
    kRect = 10,
    kDoubleColor = 11,
    kHandle = 12
  };

public:
  CCDAStdBtnSetValueDlg(CWnd* pParent, CCDAStdBtnSetValueDlgType uType, bool bEnable, const OdRxValue& propValue, const OdString& strPropName);   // standard constructor
  virtual ~CCDAStdBtnSetValueDlg();

  // Dialog Data
  enum { IDD = IDD_CDASTDBTN_DLG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

  afx_msg void OnOk();

public:
  double m_dX1;
  double m_dX2;
  double m_dX3;
  double m_dY1;
  double m_dY2;
  double m_dY3;
  double m_dZ1;
  double m_dZ2;
  double m_dZ3;
  double m_dW;

  double m_dOldX1;
  double m_dOldX2;
  double m_dOldX3;
  double m_dOldY1;
  double m_dOldY2;
  double m_dOldY3;
  double m_dOldZ1;
  double m_dOldZ2;
  double m_dOldZ3;
  double m_dOldW;

  CCDAStdBtnSetValueDlgType m_uType;
  bool   m_bEnable;
  OdRxValue m_value;
  OdString m_strPropName;
  bool   m_bDataModified;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAStdArraySetValueDlg dialog

class CCDAStdArraySetValueDlg : public CDialog
{
  DECLARE_DYNAMIC(CCDAStdArraySetValueDlg)

public:

  enum CCDAStdArraySetValueDlgType
  {
    kBool       = 0,
    kInt8       = 1,
    kUInt8      = 2,
    kInt16      = 3,
    kUInt16     = 4,
    kInt32      = 5,
    kUInt32     = 6,
    kInt64      = 7,
    kUInt64     = 8,
    kDouble     = 9,
    kFloat      = 10,
    kString     = 11,
    kAnsiString = 12,
    kPoint3d    = 13,
    kDateTime   = 14
  };

public:
  CCDAStdArraySetValueDlg(CWnd* pParent, CCDAStdArraySetValueDlgType uType, bool bEnable, const OdString& strPropName);   // standard constructor
  virtual ~CCDAStdArraySetValueDlg();

  // Dialog Data
  enum { IDD = IDD_CDASTDARRAY_DLG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  void updateValuesList();
  void setSelectedValue(int iSelIndex);

  DECLARE_MESSAGE_MAP()

  afx_msg void OnLvnItemchangedValueList(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnOk();
  afx_msg void OnAddValue();
  afx_msg void OnModifyValue();
  afx_msg void OnDeleteValue();

public:
  OdArray<bool>     m_boolArr;
  OdArray<OdInt8>   m_int8Arr;
  OdArray<OdUInt8>  m_uInt8Arr;
  OdArray<OdInt16>  m_int16Arr;
  OdArray<OdUInt16> m_uInt16Arr;
  OdArray<OdInt32>  m_int32Arr;
  OdArray<OdUInt32> m_uInt32Arr;
  OdArray<OdInt64>  m_int64Arr;
  OdArray<OdUInt64> m_uInt64Arr;
  OdArray<double>   m_doubleArr;
  OdArray<float>    m_floatArr;
  OdArray<OdString> m_stringArr;
  OdArray<OdAnsiString> m_ansiStringArr;
  OdArray<OdGePoint3d> m_point3dArr;
  OdArray<OdTimeStamp> m_dateTimeArr;

  OdArray<OdString> m_arrValues;

  double  m_dXValue;
  double  m_dYValue;
  double  m_dZValue;
  CString m_strValue;
  CTime   m_timeValue;
  int     m_iBoolRadio;
  int     m_iSelectedItem;
  bool    m_bSkipSelChange;
  int     m_iCurCount;
  CDateTimeCtrl m_dateTimeCtrl;

  CCDAStdArraySetValueDlgType m_uType;
  bool   m_bEnable;
  OdRxValue m_value;
  OdString m_strPropName;
  bool   m_bDataModified;
};

/////////////////////////////////////////////////////////////////////////////
// CCDAStdArraySetValueDlg dialog

class CCDASetTransperencyDlg : public CDialog
{
  DECLARE_DYNAMIC(CCDASetTransperencyDlg)

public:
  CCDASetTransperencyDlg(CWnd* pParent, OdCmTransparency& curTrans, bool bEnable, const OdString& strPropName);   // standard constructor
  virtual ~CCDASetTransperencyDlg();

  // Dialog Data
  enum { IDD = IDD_CDASETTRANS_DLG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:
  bool   m_bEnable;
  OdString m_strPropName;
  int     m_iValue;
  bool    m_bDataModified;
};

/////////////////////////////////////////////////////////////////////////////

// CCDAIndexedArrayDlg dialog

class CCDAIndexedArrayDlg : public CDialog
{
  DECLARE_DYNAMIC(CCDAIndexedArrayDlg)

public:
  CCDAIndexedArrayDlg(CWnd* pParent, OdRxObject* pDb, OdRxObject* pObject, OdRxValue& defaultValue, bool bEnable, OdInt32 iSubPropertyIndex = -1,
    const OdString& strPropName = OdString::kEmpty);   // standard constructor
  virtual ~CCDAIndexedArrayDlg();

  // Dialog Data
  enum { IDD = IDD_CDA_ARRAYPROP };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

  afx_msg void OnLvnItemchangedValueList(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnOk();
  afx_msg void OnAddBtn();
  afx_msg void OnDeleteBtn();

private:
  CCDAPropertiesListCtrl m_listCtrl;
  OdInt32                m_iSubPropertyIndex;
  OdString               m_strPropName;
  OdRxValue              m_defaultValue;
  bool                   m_bEnable;
  OdRxObject*            m_pDb;
  OdRxObject*            m_pObject;
};

/////////////////////////////////////////////////////////////////////////////

// CCDAUnionTypeDlg dialog

class CCDAUnionTypeDlg : public CDialog
{
  DECLARE_DYNAMIC(CCDAUnionTypeDlg)

public:
  CCDAUnionTypeDlg(CWnd* pParent, OdRxObject* pObject, OdRxObject* pDb, OdRxPropertyBase* pProperty, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex);   // standard constructor
  virtual ~CCDAUnionTypeDlg();

  // Dialog Data
  enum { IDD = IDD_CDA_UNIONTYPE };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

  afx_msg void OnOk();
  afx_msg void OnPropTypeComboSelchange();

private:
  CCDAPropertiesListCtrl m_listCtrl;
  OdRxPropertyBasePtr    m_pProperty;
  OdRxObject*            m_pDb;
  OdRxObjectPtr          m_pObject;
  OdRxObjectPtr          m_pCurListObject;
  OdInt32                m_iSubPropertyIndex;
  OdInt32                m_iArrayIndex;
  bool                   m_bRxObject;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDAPROPLISTVIEW_H_INCLUDED_)
