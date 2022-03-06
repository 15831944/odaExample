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




// Copyright (C) 2001 Open DWG Alliance

OdInt64& OdInt64::operator+=(const OdInt64& h2)
{
	OdUInt32 lwsum = (low & 0x0000FFFF) + (h2.low & 0x0000FFFF);
	OdUInt32 hwsum = (low >> 16) + (h2.low >> 16) + (lwsum >> 16);
	low = (hwsum << 16) | (lwsum & 0x0000FFFF);
	hi += (hwsum > 0xFFFF ? h2.hi + 1 : h2.hi);
	return *this;
}

OdInt64& OdInt64::operator >>=(int n)
{
	if(n>0)
	{
		switch(hi) // fast shift
		{
		case 0:
      n>31 ? low = 0 : low >>= n; // Intel32 shr can use only 5b(max=31)
			break;
		case -1:
			low = ~low;
      n>31 ? low = 0 : low >>= n; 
			low = ~low;
			break;
		default:
		{
			if(n>0 && n<64)
			{
				int nDWordsToMove = n/32;
				int nBitsToMove = n%32;
				if(nDWordsToMove==0)
				{
					OdUInt32 border = OdUInt32(hi) << (32-nBitsToMove);
					hi >>= nBitsToMove;
					(low >>= nBitsToMove) |= border;
				}
				else
				{
					low = hi >> nBitsToMove;
					hi = *this < 0 ? -1 : 0;
				}
			}
			else if(n>64)
			{
				*this = *this < 0 ? -1 : 0;
			}
		}
		break;
		}
	}
	return *this;
}

OdUInt64& OdUInt64::operator >>= (int n)
{
  if (n<=0)
    return *this;
    
  if (n<32)
	{
		(low >>= n) |= OdUInt32(hi) << (32-n);
		hi = OdUInt32(hi) >> n;
	}
  else if (n<64)
  {
		low = OdUInt32(hi) >> (n-32);
		hi = 0;
	}
  else 
  {
    low = hi = 0;
  }
  return *this;
}

