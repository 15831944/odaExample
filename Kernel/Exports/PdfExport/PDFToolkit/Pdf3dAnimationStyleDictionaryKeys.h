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

_PDF_DICT_KEYS_A_(Type,    PDFName)       //(Optional). The type of PDF object that this dictionary describes; if present, shall be 3DAnimationStyle.
_PDF_DICT_KEYS_A_(Subtype, PDFName)       //(Optional) The animation style described by this dictionary; Default value: None
_PDF_DICT_KEYS_A_(PC,      PDFInteger)    //(Optional) An integer specifying the play count for this animation style.Default value: 0
_PDF_DICT_KEYS_A_(TM,      PDFNumber)     //(Optional) A positive number specifying the time multiplier to be used when running the animation.Default value: 1

#undef _PDF_DICT_KEYS_A_
