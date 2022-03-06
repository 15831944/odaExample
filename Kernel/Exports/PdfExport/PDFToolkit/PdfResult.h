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




#ifndef _PDFRESULT_INCLUDED_
#define _PDFRESULT_INCLUDED_ /*!DOM*// 

namespace TD_PDF
{

enum PDFResult
{
  eOk                       = 0,
  eInternalError            = 1,
  eEmptyInputArray          = 2,
  eNotSortedArray           = 3,
  eDuplicatedElement        = 4,
  eNullDocument             = 5,
  eKeyNotFound              = 6,
  eNullBaseName             = 7,
  eNotImplementedYet        = 8,
  eCannotFillFontDescriptor = 9,

  eLastErrorNum             = 0xFFFF
};

};

#endif //_PDFRESULT_INCLUDED_

