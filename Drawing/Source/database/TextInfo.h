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

#ifndef _ODTEXTINFO_INCLUDED_
#define _ODTEXTINFO_INCLUDED_

#include "DbObjectId.h"

class OdTextInfo
{
protected:
	enum
	{
		TEXT_GEN_BACKWARD = 2,
		TEXT_GEN_UPSIDEDOWN = 4,
		SHAPE         = 1,
		VERTICALTEXT  = 4
	};

	OdUInt16	m_TextGenFlags;

	OdTextInfo() : m_TextGenFlags(0) {}

public:
  OdUInt16 getGenerationFlags() const { return m_TextGenFlags; }
  void setGenerationFlags(OdUInt16 value) { m_TextGenFlags = value; }

	void setUpsideDown(bool value) { SETBIT(m_TextGenFlags, TEXT_GEN_UPSIDEDOWN, value); }
  bool isUpsideDown() const { return GETBIT(m_TextGenFlags, TEXT_GEN_UPSIDEDOWN); }

	void setBackwards(bool value) { SETBIT(m_TextGenFlags, TEXT_GEN_BACKWARD, value); }
  bool isBackwards() const { return GETBIT(m_TextGenFlags, TEXT_GEN_BACKWARD); }
};


#endif // _ODTEXTINFO_INCLUDED_
