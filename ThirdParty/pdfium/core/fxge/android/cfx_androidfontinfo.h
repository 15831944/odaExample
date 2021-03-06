// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXGE_ANDROID_CFX_ANDROIDFONTINFO_H_
#define CORE_FXGE_ANDROID_CFX_ANDROIDFONTINFO_H_

#include "core/fxcrt/fx_system.h"
#include "core/fxcrt/unowned_ptr.h"
#include "core/fxge/cfx_fontmapper.h"
#include "core/fxge/fx_font.h"
#include "core/fxge/ifx_systemfontinfo.h"

class CFPF_SkiaFontMgr;

class CFX_AndroidFontInfo : public IFX_SystemFontInfo {
 public:
  CFX_AndroidFontInfo();
  ~CFX_AndroidFontInfo() override;

  bool Init(CFPF_SkiaFontMgr* pFontMgr);

  // IFX_SystemFontInfo:
  bool EnumFontList(CFX_FontMapper* pMapper) override;
  void* MapFont(int weight,
                bool bItalic,
                int charset,
                int pitch_family,
                const char* face) override;
  void* GetFont(const char* face) override;
  uint32_t GetFontData(void* hFont,
                       uint32_t table,
                       uint8_t* buffer,
                       uint32_t size) override;
  bool GetFaceName(void* hFont, ByteString* name) override;
  bool GetFontCharset(void* hFont, int* charset) override;
  void DeleteFont(void* hFont) override;

#ifdef ODA_CHANGES
  virtual void AddPathEnumFonts(const char* path) override {}
#endif // ODA_CHANGES

 protected:
  UnownedPtr<CFPF_SkiaFontMgr> m_pFontMgr;
};

#endif  // CORE_FXGE_ANDROID_CFX_ANDROIDFONTINFO_H_
