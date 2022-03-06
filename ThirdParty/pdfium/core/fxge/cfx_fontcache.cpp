// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/fxge/cfx_fontcache.h"

#include <memory>
#include <utility>

#include "core/fxge/cfx_facecache.h"
#include "core/fxge/fx_font.h"
#include "core/fxge/fx_freetype.h"
#include "third_party/base/ptr_util.h"
#ifdef ODA_CHANGES
#include "../fpdfapi/parser/cpdf_dictionary.h"
#include "../fpdfapi/parser/cpdf_array.h"
#include "../fpdfapi/font/cpdf_font.h"
#endif // ODA_CHANGES

CFX_FontCache::CountedFaceCache::CountedFaceCache() {}

CFX_FontCache::CountedFaceCache::~CountedFaceCache() {}

CFX_FontCache::CFX_FontCache() {}

CFX_FontCache::~CFX_FontCache() {
  ASSERT(m_ExtFaceMap.empty());
  ASSERT(m_FTFaceMap.empty());
}

CFX_FaceCache* CFX_FontCache::GetCachedFace(const CFX_Font* pFont) {
  FXFT_Face face = pFont->GetFace();
  const bool bExternal = !face;
  CFX_FTCacheMap& map = bExternal ? m_ExtFaceMap : m_FTFaceMap;
  auto it = map.find(face);
  if (it != map.end()) {
    CountedFaceCache* counted_face_cache = it->second.get();
    counted_face_cache->m_nCount++;
    return counted_face_cache->m_Obj.get();
  }

  auto counted_face_cache = pdfium::MakeUnique<CountedFaceCache>();
  counted_face_cache->m_nCount = 2;
  auto new_cache =
      pdfium::MakeUnique<CFX_FaceCache>(bExternal ? nullptr : face);
  CFX_FaceCache* face_cache = new_cache.get();
  counted_face_cache->m_Obj = std::move(new_cache);
  map[face] = std::move(counted_face_cache);
  return face_cache;
}

#ifdef _SKIA_SUPPORT_
CFX_TypeFace* CFX_FontCache::GetDeviceCache(const CFX_Font* pFont) {
  return GetCachedFace(pFont)->GetDeviceCache(pFont);
}
#endif

#ifdef ODA_CHANGES
void CFX_FontCache::LoadGlyphCache(FXFT_Face face, OdFaceGlyphInfo& glyph_cache)
{
  glyph_cache.first = true;
  FT_UInt   gindex(0), prev_charcode(0);
  FT_ULong  charcode = FT_Get_First_Char(face, &gindex);
  while (gindex != 0)
  {
    glyph_cache.second[gindex].push_back(charcode);
    if (glyph_cache.first && prev_charcode != charcode - 1)
      glyph_cache.first = false;
    prev_charcode = charcode;

    charcode = FT_Get_Next_Char(face, charcode, &gindex);
  }
  if (glyph_cache.first)
    int qq = 0;
}

CFX_FontCache::OdFaceGlyphCache::iterator CFX_FontCache::FindFaceInfo(OdFaceGlyphCache& FaceGlyphCache,
  CPDF_Font* pFont, CFX_Font* pCFXFont)
{
  ByteString face_name = pCFXFont->GetFamilyName();
  if (face_name.IsEmpty())
    face_name = pFont->GetBaseFont();
  else
    face_name = pCFXFont->GetFaceName();
  if (pCFXFont->IsEmbedded())
    face_name += " Embedded";

  auto face_it = FaceGlyphCache.find(face_name);
  if (FaceGlyphCache.end() == face_it)
  {
    OdFaceGlyphInfo glyph_cache;
    LoadGlyphCache(pCFXFont->GetFace(), glyph_cache);

    face_it = FaceGlyphCache.emplace(face_name, glyph_cache).first;
  }
  return face_it;
}

FT_ULong CFX_FontCache::GetCharCodeFromFaceCache(CPDF_Font* pFont, CFX_Font* pCFXFont, FT_UInt glyph_index, wchar_t ref_code)
{
  FXFT_Face face = pCFXFont->GetFace();
  if (nullptr == face)
    return 0;

  auto face_it = FindFaceInfo(m_FaceGlyphCache, pFont, pCFXFont);

  if (face_it->second.first)
    return 0;

  auto glyph_it = face_it->second.second.find(glyph_index);
  if (face_it->second.second.end() == glyph_it)
    return 0;

  FT_ULong ret = glyph_it->second[0];

  if (0 == ref_code)
    return ret;
  
  auto char_code_it = std::find(glyph_it->second.begin(), glyph_it->second.end(), ref_code);

  if (glyph_it->second.end() != char_code_it)
    ret = *char_code_it;
  else
    ret = glyph_it->second[0];
  
  return ret;
}

bool CFX_FontCache::IsCharCodeInFaceCache(CPDF_Font* pFont, CFX_Font* pCFXFont, wchar_t char_code)
{
  FXFT_Face face = pCFXFont->GetFace();
  if (nullptr == face)
    return false;

  auto face_it = FindFaceInfo(m_FaceGlyphCache, pFont, pCFXFont);

  for (auto& elem : face_it->second.second)
  {
    if (elem.second.end() != std::find(elem.second.begin(), elem.second.end(), char_code))
      return true;
  }
  return false;
}

#endif // ODA_CHANGES

void CFX_FontCache::ReleaseCachedFace(const CFX_Font* pFont) {
  FXFT_Face face = pFont->GetFace();
  const bool bExternal = !face;
  CFX_FTCacheMap& map = bExternal ? m_ExtFaceMap : m_FTFaceMap;

  auto it = map.find(face);
  if (it == map.end())
    return;

  CountedFaceCache* counted_face_cache = it->second.get();
  if (counted_face_cache->m_nCount > 2) {
    counted_face_cache->m_nCount--;
  } else {
    map.erase(it);
  }
}
