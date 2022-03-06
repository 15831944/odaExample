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

#include "OdaCommon.h"
#include "DynamicLinker.h"
#include "PdfPublish/PdfPublish.h"


using namespace OdPdfPublish;

OdResult OdPdfPublishControlsEx(OdDbBaseHostAppServices* pHostApp, const OdString& sOutPdf)
{
  if (sOutPdf.isEmpty())
  {
    return eInvalidInput;
  }

  OdFilePtr pPublisher = OdFile::createObject();

  OdDocumentPtr pDoc = OdDocument::createObject();
  pDoc->setInformation(L"Pdf Publish Controls Sample Document", L"Author", L"Controls Sample", L"Oda Pdf Publish");
  pDoc->setHostServices(pHostApp);

  OdPagePtr pPage = OdPage::createObject();
  pPage->setFormat(Page::kA3);
  pPage->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage);

  OdUInt32 top_line_top = 830;
  OdUInt32 top_line_text_top = 650;

  OdRect button_rect(20, 200, top_line_top - 80, top_line_top);
  OdButtonPtr pButton = OdButton::createObject();
  OdString button_name(L"TestButton");
  pButton->setName(button_name);
  pButton->setLabel(L"Test");
  pPage->addButton(pButton, button_rect);

  OdRect tx_button_rect(20, 200, top_line_text_top - 30, top_line_text_top);
  OdTextFieldPtr tx2button = OdTextField::createObject();
  OdString tx2button_name(L"ButtonText");
  tx2button->setName(tx2button_name);
  pPage->addTextField(tx2button, tx_button_rect);

  const OdChar* buttonActionBase = 
    L"var text_field = getField('%s');\n"
    L"if(text_field != null)          \n"
    L"  text_field.value = '%s';      \n";
  pPage->addJavaScriptActionByField(button_name, OdString().format(buttonActionBase, tx2button_name.c_str(), L"button is pressed"), Action::kButtonPressed);
  pPage->addJavaScriptActionByField(button_name, OdString().format(buttonActionBase, tx2button_name.c_str(), L"button is released"), Action::kButtonReleased);
  pPage->addJavaScriptActionByField(button_name, OdString().format(buttonActionBase, tx2button_name.c_str(), L"cursor enters"), Action::kCursorEnter);
  pPage->addJavaScriptActionByField(button_name, OdString().format(buttonActionBase, tx2button_name.c_str(), L"cursor exits"), Action::kCursorExit);

  OdRect listbox_rect(220, 420, top_line_top - 160, top_line_top);
  OdListBoxPtr pListBox = OdListBox::createObject();
  OdString listbox_name(L"TestListBox");
  pListBox->setName(listbox_name);
  OdStringArray displayed_values;
  OdStringArray export_values;
  for(int i = 0; i < 15; ++i)
  {
    displayed_values.append(OdString().format(L"lb_disp%i", i));
    export_values.append(OdString().format(L"lb_exp%i", i));
  }
  pListBox->setContents(displayed_values, export_values);
  pPage->addListBox(pListBox, listbox_rect);

  OdRect tx_listbox_rect(220, 420, top_line_text_top - 30, top_line_text_top);
  OdTextFieldPtr tx2listbox = OdTextField::createObject();
  OdString tx2listbox_name(L"ListBoxText");
  tx2listbox->setName(tx2listbox_name);
  pPage->addTextField(tx2listbox, tx_listbox_rect);

  const OdChar* listboxActionBase = 
    L"var text_field = getField('%s');                  \n"
    L"var field = getField('%s');                       \n"
    L"if(text_field != null && field != null)           \n"
    L"{                                                 \n"
    L"  text_field.value = field.value;                 \n"
    L"}                                                 \n";
  pPage->addJavaScriptActionByField(listbox_name, OdString().format(listboxActionBase, tx2listbox_name.c_str(), listbox_name.c_str()), Action::kLoseFocus);

  OdRect dropdown_rect(440, 640, top_line_top - 30, top_line_top);
  OdDropDownListPtr pDropDown = OdDropDownList::createObject();
  OdString dropdown_name(L"TestDropDown");
  pDropDown->setName(dropdown_name);
  OdStringArray dddisplayed_values;
  OdStringArray ddexport_values;
  for(int i = 0; i < 15; ++i)
  {
    dddisplayed_values.append(OdString().format(L"dd_disp%i", i));
    ddexport_values.append(OdString().format(L"dd_exp%i", i));
  }
  pDropDown->setContents(dddisplayed_values, ddexport_values);
  pPage->addDropDownList(pDropDown, dropdown_rect);

  OdRect tx_dropdown_rect(440, 640, top_line_text_top - 30, top_line_text_top);
  OdTextFieldPtr tx2dropdown = OdTextField::createObject();
  OdString tx2dropdown_name(L"DropDownText");
  tx2dropdown->setName(tx2dropdown_name);
  pPage->addTextField(tx2dropdown, tx_dropdown_rect);

  pPage->addJavaScriptActionByField(dropdown_name, OdString().format(listboxActionBase, tx2dropdown_name.c_str(), dropdown_name.c_str()), Action::kLoseFocus);

  OdRect checkbox_rect(755, 805, top_line_top - 30, top_line_top);
  OdCheckBoxPtr pCheckBox = OdCheckBox::createObject();
  pCheckBox->setBorder(true);
  pCheckBox->setBorderStyle(Border::kDashed);
  pCheckBox->setFontSize(20);
  OdString checkbox_name(L"TestCheckBox");
  pCheckBox->setName(checkbox_name);
  pCheckBox->setExportValue(L"CheckBox Exported Value");
  pPage->addCheckBox(pCheckBox, checkbox_rect);

  OdRect tx_checkbox_rect(680, 880, top_line_text_top - 30, top_line_text_top);
  OdTextFieldPtr tx2checkbox = OdTextField::createObject();
  OdString tx2checkbox_name(L"CheckBoxText");
  tx2checkbox->setName(tx2checkbox_name);
  pPage->addTextField(tx2checkbox, tx_checkbox_rect);

  const OdChar* checkboxActionBase = 
    L"var text_field = getField('%s');                     \n"
    L"var cb_field = getField('%s');                       \n"
    L"if(text_field != null && cb_field != null)           \n"
    L"{                                                    \n"
    L"  if(cb_field.value == 'Yes')                        \n"
    L"    text_field.value = cb_field.exportValues[0];     \n"
    L"  else                                               \n"
    L"    text_field.value = cb_field.value;               \n"
    L"}                                                    \n";
  pPage->addJavaScriptActionByField(checkbox_name, OdString().format(checkboxActionBase, tx2checkbox_name.c_str(), checkbox_name.c_str()), Action::kButtonReleased);


  OdRect radio_btn_rect(975, 1025, top_line_top - 30, top_line_top);
  OdString radio_btn_name(L"TestRadioButton");
  for(int i = 0; i < 3; ++i)
  {
    OdRadioButtonPtr pRadioButton = OdRadioButton::createObject();
    pRadioButton->setGrouping(true);
    pRadioButton->setName(radio_btn_name);
    if(1 == i)
      pRadioButton->setDefaultState(true);
    pRadioButton->setExportValue(OdString().format(L"RadioButton Exported Value %i", i));
    pPage->addRadioButton(pRadioButton, radio_btn_rect);
    radio_btn_rect.m_max.y = radio_btn_rect.m_min.y - 10;
    radio_btn_rect.m_min.y = radio_btn_rect.m_max.y - 30;
  }

  OdRect tx_radio_btn_rect(900, 1100, top_line_text_top - 30, top_line_text_top);
  OdTextFieldPtr tx2radio_btn = OdTextField::createObject();
  OdString tx2radio_btn_name(L"RadioButtonText");
  tx2radio_btn->setName(tx2radio_btn_name);
  pPage->addTextField(tx2radio_btn, tx_radio_btn_rect);

  const OdChar* radio_btnActionBase = 
    L"var text_field = getField('%s');                     \n"
    L"var rb_field = getField('%s');                       \n"
    L"if(text_field != null && rb_field != null)           \n"
    L"{                                                    \n"
    L"  count = rb_field.page.length;                      \n"
    L"  for(var i = 0; i<count ; i++)                      \n"
    L"    if(rb_field.isBoxChecked(i))                     \n"
    L"      text_field.value = rb_field.exportValues[i];   \n"
    L"}                                                    \n";
  pPage->addJavaScriptActionByField(radio_btn_name, OdString().format(radio_btnActionBase, tx2radio_btn_name.c_str(), radio_btn_name.c_str()), Action::kButtonReleased);

  OdRect text_rect(20, 1100, top_line_text_top - 80, top_line_text_top - 50);
  OdTextFieldPtr pTextField = OdTextField::createObject();
  OdString text_name(L"TextText");
  pTextField->setName(text_name);
  pPage->addTextField(pTextField, text_rect);
  const OdChar* textActionBase = 
    L"var text_field = getField('%s');                     \n"
    L"if(text_field != null)                               \n"
    L"{                                                    \n"
    L"  text_field.value = Date().toString() + ': ' +      \n"
    L"  text_field.value;                                  \n"
    L"}                                                    \n";
  pPage->addJavaScriptActionByField(text_name, OdString().format(textActionBase, text_name.c_str()), Action::kLoseFocus);

  OdRect rect_table1(20, 550, 100, 550);
  OdRect rect_table2(600, 1100, 100, 550);

  OdDoubleArray columns_sizes;
  columns_sizes.resize(10, 0.1);

  OdSlideTablePtr table1 = OdSlideTable::createObject();
  table1->setDimensions(columns_sizes, 30);

  OdSlideTablePtr table2 = OdSlideTable::createObject();
  table2->setDimensions(columns_sizes, 30);

  OdTextFieldPtrArray fields;

  OdUInt32 col_count = 10;
  OdUInt32 row_count = 20;
  for(OdUInt32 i=0; i<row_count ; ++i)
  {
    for(OdUInt32 j = 0; j < col_count; ++j)
    {
      OdTextFieldPtr textField = OdTextField::createObject();
      OdString fieldName;
      if(0 == i)
        fieldName.format(L"head%i_%i", i, j);
      else
        fieldName.format(L"field%i_%i", i, j);
      textField->setName(fieldName);
      textField->setDefaultValue(fieldName);
      textField->setBorder(true);
      fields.append(textField);

    }
  }
  table1->setHeader(true);
  table1->setText(row_count, col_count, fields);

  table2->setHeader(true);
  table2->setText(row_count, col_count, fields);
  table2->setButtons(L"Prev", L"Next");


  pPage->addSlideTable(table1, rect_table1);
  pPage->addSlideTable(table2, rect_table2);

  OdRect sign_rect(20, 1100, 40, 80);
  OdSignatureFieldPtr pSignatureField = OdSignatureField::createObject();
  OdString sign_name(L"SignatureFieldTest");
  pSignatureField->setName(sign_name);
  pPage->addSignatureField(pSignatureField, sign_rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}
