// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXGE_CFX_FONTCACHE_H_
#define CORE_FXGE_CFX_FONTCACHE_H_

#include <map>
#include <memory>

#include "core/fxcrt/fx_system.h"
#include "core/fxge/cfx_font.h"
#include "core/fxge/fx_font.h"
#include "core/fxge/fx_freetype.h"

class CFX_FaceCache;
#ifdef ODA_CHANGES
class CPDF_Font;
#endif // ODA_CHANGES

class CFX_FontCache {
 public:
  CFX_FontCache();
  ~CFX_FontCache();
  CFX_FaceCache* GetCachedFace(const CFX_Font* pFont);
  void ReleaseCachedFace(const CFX_Font* pFont);
#ifdef _SKIA_SUPPORT_
  CFX_TypeFace* GetDeviceCache(const CFX_Font* pFont);
#endif

#ifdef ODA_CHANGES
  FT_ULong GetCharCodeFromFaceCache(CPDF_Font* pFont, CFX_Font* pCFXFont, FT_UInt glyph_index, wchar_t ref_code);
  bool IsCharCodeInFaceCache(CPDF_Font* pFont, CFX_Font* pCFXFont, wchar_t char_code);
#endif // ODA_CHANGES

 private:
  struct CountedFaceCache {
    CountedFaceCache();
    ~CountedFaceCache();
    std::unique_ptr<CFX_FaceCache> m_Obj;
    uint32_t m_nCount;
  };

  using CFX_FTCacheMap = std::map<FXFT_Face, std::unique_ptr<CountedFaceCache>>;
  CFX_FTCacheMap m_FTFaceMap;
  CFX_FTCacheMap m_ExtFaceMap;
#ifdef ODA_CHANGES
  using OdFaceInfoMap = std::map<FT_UInt, std::vector<FT_ULong> >;
  using OdFaceGlyphInfo = std::pair<bool, OdFaceInfoMap>;
  using OdFaceGlyphCache = std::map<ByteString, OdFaceGlyphInfo>;
  OdFaceGlyphCache m_FaceGlyphCache;

  void LoadGlyphCache(FXFT_Face face, OdFaceGlyphInfo& glyph_cache);
  OdFaceGlyphCache::iterator FindFaceInfo(OdFaceGlyphCache& FaceGlyphCache, CPDF_Font* pFont, CFX_Font* pCFXFont);

#endif // ODA_CHANGES
};

#endif  // CORE_FXGE_CFX_FONTCACHE_H_
