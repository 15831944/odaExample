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

_PDF_DICT_KEYS_INT32_(BitsPerCoordinate                 ) // (Required) The number of bits used to represent each vertex coordinate.
_PDF_DICT_KEYS_INT32_(BitsPerComponent                  ) // (Required) The number of bits used to represent each color component.
_PDF_DICT_KEYS_INT32_(BitsPerFlag                       ) // (Required) The number of bits used to represent the edge flag for each vertex
//_PDF_DICT_KEYS_A_    (Function         , PDFFunction    ) // (Optional)
_PDF_DICT_KEYS_A_    (Decode           , PDFArray       ) // (Required) An array of numbers specifying how to map vertex coordinates
                                                          // and color components into the appropriate ranges of values.

#undef _PDF_DICT_KEYS_A_
