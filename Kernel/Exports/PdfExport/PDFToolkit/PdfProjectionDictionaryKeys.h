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

_PDF_DICT_KEYS_A_(Subtype         , PDFName          )//(Required)
_PDF_DICT_KEYS_A_(CS              , PDFName          )//(Optional)
_PDF_DICT_KEYS_A_(F               , PDFNumber        )//(Optional; meaningful only if the value of CS is XNF)
_PDF_DICT_KEYS_A_(N               , PDFNumber        )//(Meaningful only if the value of CS is XNF; required if the value of Subtype is P)
_PDF_DICT_KEYS_A_(FOV             , PDFNumber        )//(Required if Subtype is P, ignored otherwise)
_PDF_DICT_KEYS_A_(PS              , PDFObject        )//number or name (Optional; meaningful only if Subtype is P)
_PDF_DICT_KEYS_A_(OS              , PDFNumber        )//(Optional; meaningful only if Subtype is O)
_PDF_DICT_KEYS_A_(OB              , PDFName          )// ???


#undef _PDF_DICT_KEYS_A_
