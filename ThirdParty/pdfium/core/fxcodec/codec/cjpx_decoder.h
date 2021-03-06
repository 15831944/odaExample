// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXCODEC_CODEC_CJPX_DECODER_H_
#define CORE_FXCODEC_CODEC_CJPX_DECODER_H_

#include <memory>
#include <vector>

#include "core/fxcodec/codec/codec_int.h"
#include "core/fxcrt/unowned_ptr.h"
#ifdef NO_PDFIUM_LIB_OPEN_OPENJPEG
#include "openjpeg.h"
#else
#include "third_party/libopenjpeg20/openjpeg.h"
#endif

class CPDF_ColorSpace;

class CJPX_Decoder {
 public:
  explicit CJPX_Decoder(CPDF_ColorSpace* cs);
  ~CJPX_Decoder();

  bool Init(const unsigned char* src_data, uint32_t src_size);
  void GetInfo(uint32_t* width, uint32_t* height, uint32_t* components);
  bool Decode(uint8_t* dest_buf,
              int pitch,
              const std::vector<uint8_t>& offsets);

 private:
  const uint8_t* m_SrcData;
  uint32_t m_SrcSize;
  // TODO(rharrison): Convert these to unowned ptrs, if possible.
  opj_image_t* m_Image;
  opj_codec_t* m_Codec;
  std::unique_ptr<DecodeData> m_DecodeData;
  opj_stream_t* m_Stream;
  opj_dparameters_t m_Parameters;
  UnownedPtr<const CPDF_ColorSpace> const m_ColorSpace;
};

#endif  // CORE_FXCODEC_CODEC_CJPX_DECODER_H_
