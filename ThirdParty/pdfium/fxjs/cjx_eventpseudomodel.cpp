// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "fxjs/cjx_eventpseudomodel.h"

#include "fxjs/cfxjse_arguments.h"
#include "fxjs/cfxjse_engine.h"
#include "fxjs/cfxjse_value.h"
#include "xfa/fxfa/cxfa_eventparam.h"
#include "xfa/fxfa/cxfa_ffnotify.h"
#include "xfa/fxfa/cxfa_ffwidgethandler.h"
#include "xfa/fxfa/parser/cscript_eventpseudomodel.h"

namespace {

void StringProperty(CFXJSE_Value* pValue, WideString& wsValue, bool bSetting) {
  if (bSetting) {
    wsValue = pValue->ToWideString();
    return;
  }
  pValue->SetString(wsValue.UTF8Encode().AsStringView());
}

void InterProperty(CFXJSE_Value* pValue, int32_t& iValue, bool bSetting) {
  if (bSetting) {
    iValue = pValue->ToInteger();
    return;
  }
  pValue->SetInteger(iValue);
}

void BooleanProperty(CFXJSE_Value* pValue, bool& bValue, bool bSetting) {
  if (bSetting) {
    bValue = pValue->ToBoolean();
    return;
  }
  pValue->SetBoolean(bValue);
}

}  // namespace

CJX_EventPseudoModel::CJX_EventPseudoModel(CScript_EventPseudoModel* model)
    : CJX_Object(model) {}

CJX_EventPseudoModel::~CJX_EventPseudoModel() {}

void CJX_EventPseudoModel::Change(CFXJSE_Value* pValue,
                                  bool bSetting,
                                  XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::Change, bSetting);
}

void CJX_EventPseudoModel::CommitKey(CFXJSE_Value* pValue,
                                     bool bSetting,
                                     XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::CommitKey, bSetting);
}

void CJX_EventPseudoModel::FullText(CFXJSE_Value* pValue,
                                    bool bSetting,
                                    XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::FullText, bSetting);
}

void CJX_EventPseudoModel::KeyDown(CFXJSE_Value* pValue,
                                   bool bSetting,
                                   XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::Keydown, bSetting);
}

void CJX_EventPseudoModel::Modifier(CFXJSE_Value* pValue,
                                    bool bSetting,
                                    XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::Modifier, bSetting);
}

void CJX_EventPseudoModel::NewContentType(CFXJSE_Value* pValue,
                                          bool bSetting,
                                          XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::NewContentType, bSetting);
}

void CJX_EventPseudoModel::NewText(CFXJSE_Value* pValue,
                                   bool bSetting,
                                   XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::NewText, bSetting);
}

void CJX_EventPseudoModel::PrevContentType(CFXJSE_Value* pValue,
                                           bool bSetting,
                                           XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::PreviousContentType, bSetting);
}

void CJX_EventPseudoModel::PrevText(CFXJSE_Value* pValue,
                                    bool bSetting,
                                    XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::PreviousText, bSetting);
}

void CJX_EventPseudoModel::Reenter(CFXJSE_Value* pValue,
                                   bool bSetting,
                                   XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::Reenter, bSetting);
}

void CJX_EventPseudoModel::SelEnd(CFXJSE_Value* pValue,
                                  bool bSetting,
                                  XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::SelectionEnd, bSetting);
}

void CJX_EventPseudoModel::SelStart(CFXJSE_Value* pValue,
                                    bool bSetting,
                                    XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::SelectionStart, bSetting);
}

void CJX_EventPseudoModel::Shift(CFXJSE_Value* pValue,
                                 bool bSetting,
                                 XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::Shift, bSetting);
}

void CJX_EventPseudoModel::SoapFaultCode(CFXJSE_Value* pValue,
                                         bool bSetting,
                                         XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::SoapFaultCode, bSetting);
}

void CJX_EventPseudoModel::SoapFaultString(CFXJSE_Value* pValue,
                                           bool bSetting,
                                           XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::SoapFaultString, bSetting);
}

void CJX_EventPseudoModel::Target(CFXJSE_Value* pValue,
                                  bool bSetting,
                                  XFA_Attribute eAttribute) {
  Property(pValue, XFA_Event::Target, bSetting);
}

void CJX_EventPseudoModel::Emit(CFXJSE_Arguments* pArguments) {
  CFXJSE_Engine* pScriptContext = GetDocument()->GetScriptContext();
  if (!pScriptContext)
    return;

  CXFA_EventParam* pEventParam = pScriptContext->GetEventParam();
  if (!pEventParam)
    return;

  CXFA_FFNotify* pNotify = GetDocument()->GetNotify();
  if (!pNotify)
    return;

  CXFA_FFWidgetHandler* pWidgetHandler = pNotify->GetWidgetHandler();
  if (!pWidgetHandler)
    return;

  pWidgetHandler->ProcessEvent(pEventParam->m_pTarget, pEventParam);
}

void CJX_EventPseudoModel::Reset(CFXJSE_Arguments* pArguments) {
  CFXJSE_Engine* pScriptContext = GetDocument()->GetScriptContext();
  if (!pScriptContext)
    return;

  CXFA_EventParam* pEventParam = pScriptContext->GetEventParam();
  if (!pEventParam)
    return;

  pEventParam->Reset();
}

void CJX_EventPseudoModel::Property(CFXJSE_Value* pValue,
                                    XFA_Event dwFlag,
                                    bool bSetting) {
  CFXJSE_Engine* pScriptContext = GetDocument()->GetScriptContext();
  if (!pScriptContext)
    return;

  CXFA_EventParam* pEventParam = pScriptContext->GetEventParam();
  if (!pEventParam)
    return;

  switch (dwFlag) {
    case XFA_Event::CancelAction:
      BooleanProperty(pValue, pEventParam->m_bCancelAction, bSetting);
      break;
    case XFA_Event::Change:
      StringProperty(pValue, pEventParam->m_wsChange, bSetting);
      break;
    case XFA_Event::CommitKey:
      InterProperty(pValue, pEventParam->m_iCommitKey, bSetting);
      break;
    case XFA_Event::FullText:
      StringProperty(pValue, pEventParam->m_wsFullText, bSetting);
      break;
    case XFA_Event::Keydown:
      BooleanProperty(pValue, pEventParam->m_bKeyDown, bSetting);
      break;
    case XFA_Event::Modifier:
      BooleanProperty(pValue, pEventParam->m_bModifier, bSetting);
      break;
    case XFA_Event::NewContentType:
      StringProperty(pValue, pEventParam->m_wsNewContentType, bSetting);
      break;
    case XFA_Event::NewText:
      StringProperty(pValue, pEventParam->m_wsNewText, bSetting);
      break;
    case XFA_Event::PreviousContentType:
      StringProperty(pValue, pEventParam->m_wsPrevContentType, bSetting);
      break;
    case XFA_Event::PreviousText:
      StringProperty(pValue, pEventParam->m_wsPrevText, bSetting);
      break;
    case XFA_Event::Reenter:
      BooleanProperty(pValue, pEventParam->m_bReenter, bSetting);
      break;
    case XFA_Event::SelectionEnd:
      InterProperty(pValue, pEventParam->m_iSelEnd, bSetting);
      break;
    case XFA_Event::SelectionStart:
      InterProperty(pValue, pEventParam->m_iSelStart, bSetting);
      break;
    case XFA_Event::Shift:
      BooleanProperty(pValue, pEventParam->m_bShift, bSetting);
      break;
    case XFA_Event::SoapFaultCode:
      StringProperty(pValue, pEventParam->m_wsSoapFaultCode, bSetting);
      break;
    case XFA_Event::SoapFaultString:
      StringProperty(pValue, pEventParam->m_wsSoapFaultString, bSetting);
      break;
    case XFA_Event::Target:
      break;
    default:
      break;
  }
}
