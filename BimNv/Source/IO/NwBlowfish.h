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

#ifndef __NWBLOWFISH_H__
#define __NWBLOWFISH_H__

#include "NwExport.h"

#define NUM_SUBKEYS  18
#define NUM_S_BOXES  4
#define NUM_ENTRIES  256

#define MAX_STRING   256
#define MAX_PASSWD   56  // 448bits

#ifdef ODA_BIGENDIAN
struct NWBF_WordByte
{
unsigned int zero : 8;
unsigned int one : 8;
unsigned int two : 8;
unsigned int three : 8;
};
#else
struct NWBF_WordByte
{
  unsigned int three : 8;
  unsigned int two : 8;
  unsigned int one : 8;
  unsigned int zero : 8;
};
#endif

union NWBF_Word
{
  OdUInt32 word;
  NWBF_WordByte byte;
};

struct NWBF_DWord
{
  NWBF_Word word0;
  NWBF_Word word1;
};


class NwBlowfish
{
private:
  OdUInt32 PA[NUM_SUBKEYS];
  OdUInt32 SB[NUM_S_BOXES][NUM_ENTRIES];

  inline void BF_En(NWBF_Word *, NWBF_Word *);
  inline void BF_De(NWBF_Word *, NWBF_Word *);

public:
  NwBlowfish();
  ~NwBlowfish();

  void Reset();
  bool GenSubkeys(OdUInt8 *Passwd, OdUInt32 len);
  bool GenSubkeys2(OdUInt8 *Passwd, OdUInt32 len);
  bool Encrypt(void *, OdUInt32);
  bool Decrypt(void *, OdUInt32);
};


#endif // __NWBLOWFISH_H__
