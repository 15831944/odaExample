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

// OdNameIterator.h: interface for the OdNameIterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_OD_NAMEITERATOR_H_)
#define _OD_NAMEITERATOR_H_

#include "OdString.h"
#include "OdCodePage.h"

class TOOLKIT_EXPORT OdNameIterator
{
  const OdChar*         m_Text;
	const OdChar*         m_pCurr;
  int                   m_nLen;
	OdCodePageId          m_Codepage;
  OdChar                m_CurrentChar;
  bool                  m_CurrentValid;

  void     start();

private:
  // To protect from usage
  OdNameIterator() {}

public:

	OdNameIterator(const OdString& str, OdCodePageId codepage);
  ~OdNameIterator();

  void init(const OdString& str, OdCodePageId codepage);
  OdChar   operator *();
  OdChar   nextChar();

  OdInt16   length();
  OdInt16   find(OdChar ch);
  OdString  left(int nCount);
  OdString  right(int nCount);
  OdString  makeUpper();
  OdString  replaceLastChars(const OdString& str);
  OdString  replace (OdChar chOld, OdChar chNew);
  OdString  add (const OdString& strToAdd);

  OdInt16 findOneOf(const OdString& sName);

  OdChar  nextCPChar(bool& isCPChar);
  OdString convertToR14Name();
  OdCodePageId codepage();
};

#endif // !defined(_OD_NAMEITERATOR_H_)
