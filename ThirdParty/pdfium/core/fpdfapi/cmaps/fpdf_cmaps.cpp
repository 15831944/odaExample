// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/fpdfapi/cmaps/cmap_int.h"

#include "core/fpdfapi/cpdf_modulemgr.h"
#include "core/fpdfapi/font/cpdf_fontglobals.h"
#include "core/fpdfapi/page/cpdf_pagemodule.h"

extern "C" {

static int compareWord(const void* p1, const void* p2) {
  return (*(uint16_t*)p1) - (*(uint16_t*)p2);
}

static int compareWordRange(const void* key, const void* element) {
  if (*(uint16_t*)key < *(uint16_t*)element)
    return -1;
  if (*(uint16_t*)key > ((uint16_t*)element)[1])
    return 1;
  return 0;
}

static int compareDWordRange(const void* p1, const void* p2) {
  uint32_t key = *(uint32_t*)p1;
  uint16_t hiword = (uint16_t)(key >> 16);
  const auto* element = reinterpret_cast<const FXCMAP_DWordCIDMap*>(p2);
  if (hiword < element->m_HiWord)
    return -1;
  if (hiword > element->m_HiWord)
    return 1;

  uint16_t loword = (uint16_t)key;
  if (loword < element->m_LoWordLow)
    return -1;
  if (loword > element->m_LoWordHigh)
    return 1;
  return 0;
}

};  // extern "C"

namespace {

const FXCMAP_CMap* FindNextCMap(const FXCMAP_CMap* pMap) {
  return pMap->m_UseOffset ? pMap + pMap->m_UseOffset : nullptr;
}

}  // namespace

const FXCMAP_CMap* FPDFAPI_FindEmbeddedCMap(const ByteString& bsName,
                                            int charset,
                                            int coding) {
  CPDF_FontGlobals* pFontGlobals =
      CPDF_ModuleMgr::Get()->GetPageModule()->GetFontGlobals();

  const FXCMAP_CMap* pCMaps;
  uint32_t count;
  std::tie(count, pCMaps) = pFontGlobals->GetEmbeddedCharset(charset);
  for (uint32_t i = 0; i < count; i++) {
    if (bsName == pCMaps[i].m_Name)
      return &pCMaps[i];
  }
  return nullptr;
}

uint16_t FPDFAPI_CIDFromCharCode(const FXCMAP_CMap* pMap, uint32_t charcode) {
  ASSERT(pMap);
  if (charcode >> 16) {
    while (pMap) {
      if (pMap->m_DWordMapType == FXCMAP_CMap::Range) {
        ASSERT(pMap->m_pDWordMap);
        auto* found = static_cast<FXCMAP_DWordCIDMap*>(
            bsearch(&charcode, pMap->m_pDWordMap, pMap->m_DWordCount,
                    sizeof(FXCMAP_DWordCIDMap), compareDWordRange));
        if (found) {
          return found->m_CID + static_cast<uint16_t>(charcode) -
                 found->m_LoWordLow;
        }
      } else {
        ASSERT(pMap->m_DWordMapType == FXCMAP_CMap::None);
        ASSERT(!pMap->m_pDWordMap);
      }
      pMap = FindNextCMap(pMap);
    }
    return 0;
  }

  uint16_t code = (uint16_t)charcode;
  while (pMap) {
    if (!pMap->m_pWordMap)
      return 0;
    if (pMap->m_WordMapType == FXCMAP_CMap::Single) {
      uint16_t* found = static_cast<uint16_t*>(
          bsearch(&code, pMap->m_pWordMap, pMap->m_WordCount, 4, compareWord));
      if (found)
        return found[1];

    } else if (pMap->m_WordMapType == FXCMAP_CMap::Range) {
      uint16_t* found = static_cast<uint16_t*>(bsearch(
          &code, pMap->m_pWordMap, pMap->m_WordCount, 6, compareWordRange));
      if (found)
        return found[2] + code - found[0];
    }
    pMap = FindNextCMap(pMap);
  }
  return 0;
}

uint32_t FPDFAPI_CharCodeFromCID(const FXCMAP_CMap* pMap, uint16_t cid) {
  // TODO(dsinclair): This should be checking both pMap->m_WordMap and
  // pMap->m_DWordMap. There was a second while() but it was never reached as
  // the first always returns. Investigate and determine how this should
  // really be working. (https://codereview.chromium.org/2235743003 removed the
  // second while loop.)
  ASSERT(pMap);
  while (pMap) {
    if (pMap->m_WordMapType == FXCMAP_CMap::Single) {
      const uint16_t* pCur = pMap->m_pWordMap;
      const uint16_t* pEnd = pMap->m_pWordMap + pMap->m_WordCount * 2;
      while (pCur < pEnd) {
        if (pCur[1] == cid)
          return pCur[0];

        pCur += 2;
      }
    } else if (pMap->m_WordMapType == FXCMAP_CMap::Range) {
      const uint16_t* pCur = pMap->m_pWordMap;
      const uint16_t* pEnd = pMap->m_pWordMap + pMap->m_WordCount * 3;
      while (pCur < pEnd) {
        if (cid >= pCur[2] && cid <= pCur[2] + pCur[1] - pCur[0])
          return pCur[0] + cid - pCur[2];

        pCur += 3;
      }
    }
    pMap = FindNextCMap(pMap);
  }
  return 0;
}
