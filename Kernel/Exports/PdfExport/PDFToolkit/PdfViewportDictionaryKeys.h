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


// Entries in the catalog, PDFDictionary)

#ifndef _PDF_DICT_KEYS_A_
#define _PDF_DICT_KEYS_A_(KEYNAME, KEYTYPE)
#endif

_PDF_DICT_KEYS_A_(Type             , PDFName)       //(Optional) The type of PDF object that this dictionary describes; must be Viewport for a viewport dictionary.
_PDF_DICT_KEYS_A_(BBox             , PDFRectangle)  //(Required) A rectangle in default user space coordinates specifying the location of the viewport on the page.
_PDF_DICT_KEYS_A_(Name             , PDFBaseString) //(Optional) A descriptive text string or title of the viewport, intended for use in a user interface.
_PDF_DICT_KEYS_A_(Measure          , PDFDictionary) //(Optional) A measure dictionary that specifies the scale and units that should apply to measurements taken on the contents within the viewport.

#undef _PDF_DICT_KEYS_A_
