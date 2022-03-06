/////////////////////////////////////////////////////////////////////////////// 
// Created by Open Design Alliance 
///////////////////////////////////////////////////////////////////////////////

#include "RenderStatus.h"
#include "ImageRenderer.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "core/fpdfapi/font/cpdf_font.h"
#include "core/fpdfapi/font/cpdf_type3char.h"
#include "core/fpdfapi/font/cpdf_type3font.h"
#include "core/fpdfapi/page/cpdf_docpagedata.h"
#include "core/fpdfapi/page/cpdf_form.h"
#include "core/fpdfapi/page/cpdf_formobject.h"
#include "core/fpdfapi/page/cpdf_function.h"
#include "core/fpdfapi/page/cpdf_graphicstates.h"
#include "core/fpdfapi/page/cpdf_image.h"
#include "core/fpdfapi/page/cpdf_imageobject.h"
#include "core/fpdfapi/page/cpdf_meshstream.h"
#include "core/fpdfapi/page/cpdf_page.h"
#include "core/fpdfapi/page/cpdf_pageobject.h"
#include "core/fpdfapi/page/cpdf_pathobject.h"
#include "core/fpdfapi/page/cpdf_shadingobject.h"
#include "core/fpdfapi/page/cpdf_shadingpattern.h"
#include "core/fpdfapi/page/cpdf_textobject.h"
#include "core/fpdfapi/page/cpdf_tilingpattern.h"
#include "core/fpdfapi/parser/cpdf_array.h"
#include "core/fpdfapi/parser/cpdf_dictionary.h"
#include "core/fpdfapi/parser/cpdf_document.h"
#include "core/fpdfapi/render/cpdf_charposlist.h"
#include "core/fpdfapi/render/cpdf_devicebuffer.h"
#include "core/fpdfapi/render/cpdf_dibsource.h"
#include "core/fpdfapi/render/cpdf_docrenderdata.h"
#include "core/fpdfapi/render/cpdf_pagerendercache.h"
#include "core/fpdfapi/render/cpdf_rendercontext.h"
#include "core/fpdfapi/render/cpdf_renderoptions.h"
#include "core/fpdfapi/render/cpdf_scaledrenderbuffer.h"
#include "core/fpdfapi/render/cpdf_textrenderer.h"
#include "core/fpdfapi/render/cpdf_transferfunc.h"
#include "core/fpdfapi/render/cpdf_type3cache.h"
#include "core/fpdfdoc/cpdf_occontext.h"
#include "core/fxcrt/autorestorer.h"
#include "core/fxcrt/cfx_fixedbufgrow.h"
#include "core/fxcrt/fx_safe_types.h"
#include "core/fxcrt/maybe_owned.h"
#include "core/fxge/cfx_defaultrenderdevice.h"
#include "core/fxge/cfx_graphstatedata.h"
#include "core/fxge/cfx_pathdata.h"
#include "core/fxge/cfx_renderdevice.h"
#include "core/fxge/ifx_renderdevicedriver.h"
#include "third_party/base/logging.h"
#include "third_party/base/numerics/safe_math.h"
#include "third_party/base/ptr_util.h"
#include "core/fpdfapi/font/cpdf_cidfont.h"
#include "core/fxge/cfx_gemodule.h"
#include "core/fxge/cfx_fontcache.h"

#include "OdDeviceDriver.h"
#include "RenderDevice.h"
#include "oda_functions.h"

#ifdef _SKIA_SUPPORT_
#include "core/fxge/skia/fx_skia_device.h"
#endif


#define SHADING_STEPS 256

namespace ODA 
{

void ReleaseCachedType3(CPDF_Type3Font* pFont) 
{
  CPDF_Document* pDoc = pFont->GetDocument();
  if (!pDoc)
    return;

  pDoc->GetRenderData()->MaybePurgeCachedType3(pFont);
  pDoc->GetPageData()->ReleaseFont(pFont->GetFontDict());
}

class CPDF_RefType3Cache 
{
 public:
  explicit CPDF_RefType3Cache(CPDF_Type3Font* pType3Font)
      : m_dwCount(0), m_pType3Font(pType3Font) {}

  ~CPDF_RefType3Cache()
  {
    while (m_dwCount--)
      ReleaseCachedType3(m_pType3Font.Get());
  }

  uint32_t m_dwCount;
  UnownedPtr<CPDF_Type3Font> const m_pType3Font;
};

RetainPtr<CFX_DIBitmap> DrawPatternBitmap(CPDF_Document* pDoc,
                                          CPDF_PageRenderCache* pCache,
                                          CPDF_TilingPattern* pPattern,
                                          const CFX_Matrix* pObject2Device,
                                          int width,
                                          int height,
                                          int flags) 
{
  auto pBitmap = pdfium::MakeRetain<CFX_DIBitmap>();
  if (!pBitmap->Create(width, height,
                       pPattern->colored() ? FXDIB_Argb : FXDIB_8bppMask)) 
  {
    return nullptr;
  }
  CFX_DefaultRenderDevice bitmap_device;
  bitmap_device.Attach(pBitmap, false, nullptr, false);
  pBitmap->Clear(0);
  CFX_FloatRect cell_bbox =
      pPattern->pattern_to_form()->TransformRect(pPattern->bbox());
  cell_bbox = pObject2Device->TransformRect(cell_bbox);
  CFX_FloatRect bitmap_rect(0.0f, 0.0f, (float)width, (float)height);
  CFX_Matrix mtAdjust;
  mtAdjust.MatchRect(bitmap_rect, cell_bbox);

  CFX_Matrix mtPattern2Bitmap = *pObject2Device;
  mtPattern2Bitmap.Concat(mtAdjust);
  CPDF_RenderOptions options;
  if (!pPattern->colored())
    options.SetColorMode(CPDF_RenderOptions::kAlpha);

  flags |= RENDER_FORCE_HALFTONE;
  options.SetFlags(flags);

  CPDF_RenderContext context(pDoc, pCache);
  context.AppendLayer(pPattern->form(), &mtPattern2Bitmap);
  context.Render(&bitmap_device, &options, nullptr);
#if defined _SKIA_SUPPORT_PATHS_
  bitmap_device.Flush(true);
  pBitmap->UnPreMultiply();
#endif
  return pBitmap;
}

bool IsAvailableMatrix(const CFX_Matrix& matrix) 
{
  if (matrix.a == 0 || matrix.d == 0)
    return matrix.b != 0 && matrix.c != 0;

  if (matrix.b == 0 || matrix.c == 0)
    return matrix.a != 0 && matrix.d != 0;

  return true;
}

uint32_t CountOutputs(const std::vector<std::unique_ptr<CPDF_Function>>& funcs) 
{
  uint32_t total = 0;
  for (const auto& func : funcs) 
  {
    if (func)
      total += func->CountOutputs();
  }
  return total;
}

void DrawAxialShading(const RetainPtr<CFX_DIBitmap>& pBitmap, CFX_Matrix* pObject2Bitmap, CPDF_Dictionary* pDict, 
  const std::vector<std::unique_ptr<CPDF_Function>>& funcs, CPDF_ColorSpace* pCS, int alpha) {
  ASSERT(pBitmap->GetFormat() == FXDIB_Argb);
  CPDF_Array* pCoords = pDict->GetArrayFor("Coords");
  if (!pCoords)
    return;

  float start_x = pCoords->GetNumberAt(0);
  float start_y = pCoords->GetNumberAt(1);
  float end_x = pCoords->GetNumberAt(2);
  float end_y = pCoords->GetNumberAt(3);
  float t_min = 0;
  float t_max = 1.0f;
  CPDF_Array* pArray = pDict->GetArrayFor("Domain");
  if (pArray) {
    t_min = pArray->GetNumberAt(0);
    t_max = pArray->GetNumberAt(1);
  }
  bool bStartExtend = false;
  bool bEndExtend = false;
  pArray = pDict->GetArrayFor("Extend");
  if (pArray) 
  {
    bStartExtend = !!pArray->GetIntegerAt(0);
    bEndExtend = !!pArray->GetIntegerAt(1);
  }
  int width = pBitmap->GetWidth();
  int height = pBitmap->GetHeight();
  float x_span = end_x - start_x;
  float y_span = end_y - start_y;
  float axis_len_square = (x_span * x_span) + (y_span * y_span);
  uint32_t total_results = std::max(CountOutputs(funcs), pCS->CountComponents());
  CFX_FixedBufGrow<float, 16> result_array(total_results);
  float* pResults = result_array;
  memset(pResults, 0, total_results * sizeof(float));
  uint32_t rgb_array[SHADING_STEPS];
  for (int i = 0; i < SHADING_STEPS; i++) 
  {
    float input = (t_max - t_min) * i / SHADING_STEPS + t_min;
    int offset = 0;
    for (const auto& func : funcs) 
    {
      if (func) {
        int nresults = 0;
        if (func->Call(&input, 1, pResults + offset, &nresults))
          offset += nresults;
      }
    }
    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;
    pCS->GetRGB(pResults, &R, &G, &B);
    rgb_array[i] = FXARGB_TODIB(FXARGB_MAKE(alpha, FXSYS_round(R * 255), FXSYS_round(G * 255), FXSYS_round(B * 255)));
  }
  int pitch = pBitmap->GetPitch();
  CFX_Matrix matrix = pObject2Bitmap->GetInverse();
  for (int row = 0; row < height; row++) 
  {
    uint32_t* dib_buf = (uint32_t*)(pBitmap->GetBuffer() + row * pitch);
    for (int column = 0; column < width; column++) 
    {
      CFX_PointF pos = matrix.Transform(
        CFX_PointF(static_cast<float>(column), static_cast<float>(row)));
      float scale = (((pos.x - start_x) * x_span) + ((pos.y - start_y) * y_span)) / axis_len_square;
      int index = (int32_t)(scale * (SHADING_STEPS - 1));
      if (index < 0)
      {
        if (!bStartExtend)
          continue;

        index = 0;
      }
      else if (index >= SHADING_STEPS)
      {
        if (!bEndExtend)
          continue;

        index = SHADING_STEPS - 1;
      }
      dib_buf[column] = rgb_array[index];
    }
  }
}

void DrawRadialShading(const RetainPtr<CFX_DIBitmap>& pBitmap, CFX_Matrix* pObject2Bitmap, CPDF_Dictionary* pDict,
  const std::vector<std::unique_ptr<CPDF_Function>>& funcs, CPDF_ColorSpace* pCS, int alpha)
{
  ASSERT(pBitmap->GetFormat() == FXDIB_Argb);
  CPDF_Array* pCoords = pDict->GetArrayFor("Coords");
  if (!pCoords)
    return;

  float start_x = pCoords->GetNumberAt(0);
  float start_y = pCoords->GetNumberAt(1);
  float start_r = pCoords->GetNumberAt(2);
  float end_x = pCoords->GetNumberAt(3);
  float end_y = pCoords->GetNumberAt(4);
  float end_r = pCoords->GetNumberAt(5);
  float t_min = 0;
  float t_max = 1.0f;
  CPDF_Array* pArray = pDict->GetArrayFor("Domain");
  if (pArray) {
    t_min = pArray->GetNumberAt(0);
    t_max = pArray->GetNumberAt(1);
  }
  bool bStartExtend = false;
  bool bEndExtend = false;
  pArray = pDict->GetArrayFor("Extend");
  if (pArray) 
  {
    bStartExtend = !!pArray->GetIntegerAt(0);
    bEndExtend = !!pArray->GetIntegerAt(1);
  }
  uint32_t total_results =
    std::max(CountOutputs(funcs), pCS->CountComponents());
  CFX_FixedBufGrow<float, 16> result_array(total_results);
  float* pResults = result_array;
  memset(pResults, 0, total_results * sizeof(float));
  uint32_t rgb_array[SHADING_STEPS];
  for (int i = 0; i < SHADING_STEPS; i++)
  {
    float input = (t_max - t_min) * i / SHADING_STEPS + t_min;
    int offset = 0;
    for (const auto& func : funcs)
    {
      if (func) 
      {
        int nresults;
        if (func->Call(&input, 1, pResults + offset, &nresults))
          offset += nresults;
      }
    }
    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;
    pCS->GetRGB(pResults, &R, &G, &B);
    rgb_array[i] = FXARGB_TODIB(FXARGB_MAKE(alpha, FXSYS_round(R * 255), FXSYS_round(G * 255), FXSYS_round(B * 255)));
  }
  float a = ((start_x - end_x) * (start_x - end_x)) +
    ((start_y - end_y) * (start_y - end_y)) -
    ((start_r - end_r) * (start_r - end_r));
  int width = pBitmap->GetWidth();
  int height = pBitmap->GetHeight();
  int pitch = pBitmap->GetPitch();
  bool bDecreasing = false;
  if (start_r > end_r) 
  {
    int length = (int)sqrt((((start_x - end_x) * (start_x - end_x)) +
      ((start_y - end_y) * (start_y - end_y))));
    if (length < start_r - end_r) {
      bDecreasing = true;
    }
  }
  CFX_Matrix matrix = pObject2Bitmap->GetInverse();
  for (int row = 0; row < height; row++) 
  {
    uint32_t* dib_buf = (uint32_t*)(pBitmap->GetBuffer() + row * pitch);
    for (int column = 0; column < width; column++) 
    {
      CFX_PointF pos = matrix.Transform(
        CFX_PointF(static_cast<float>(column), static_cast<float>(row)));
      float b = -2 * (((pos.x - start_x) * (end_x - start_x)) +
        ((pos.y - start_y) * (end_y - start_y)) +
        (start_r * (end_r - start_r)));
      float c = ((pos.x - start_x) * (pos.x - start_x)) +
        ((pos.y - start_y) * (pos.y - start_y)) - (start_r * start_r);
      float s;
      if (a == 0)
      {
        s = -c / b;
      }
      else 
      {
        float b2_4ac = (b * b) - 4 * (a * c);
        if (b2_4ac < 0)
        {
          continue;
        }
        float root = sqrt(b2_4ac);
        float s1, s2;
        if (a > 0)
        {
          s1 = (-b - root) / (2 * a);
          s2 = (-b + root) / (2 * a);
        }
        else 
        {
          s2 = (-b - root) / (2 * a);
          s1 = (-b + root) / (2 * a);
        }
        if (bDecreasing)
        {
          if (s1 >= 0 || bStartExtend) 
          {
            s = s1;
          }
          else 
          {
            s = s2;
          }
        }
        else 
        {
          if (s2 <= 1.0f || bEndExtend)
          {
            s = s2;
          }
          else 
          {
            s = s1;
          }
        }
        if ((start_r + s * (end_r - start_r)) < 0)
        {
          continue;
        }
      }
      int index = (int32_t)(s * (SHADING_STEPS - 1));
      if (index < 0) 
      {
        if (!bStartExtend) 
        {
          continue;
        }
        index = 0;
      }
      if (index >= SHADING_STEPS)
      {
        if (!bEndExtend)
        {
          continue;
        }
        index = SHADING_STEPS - 1;
      }
      dib_buf[column] = rgb_array[index];
    }
  }
}

void DrawFuncShading(const RetainPtr<CFX_DIBitmap>& pBitmap, CFX_Matrix* pObject2Bitmap, CPDF_Dictionary* pDict,
  const std::vector<std::unique_ptr<CPDF_Function>>& funcs, CPDF_ColorSpace* pCS, int alpha) 
{
  ASSERT(pBitmap->GetFormat() == FXDIB_Argb);
  CPDF_Array* pDomain = pDict->GetArrayFor("Domain");
  float xmin = 0, ymin = 0, xmax = 1.0f, ymax = 1.0f;
  if (pDomain) 
  {
    xmin = pDomain->GetNumberAt(0);
    xmax = pDomain->GetNumberAt(1);
    ymin = pDomain->GetNumberAt(2);
    ymax = pDomain->GetNumberAt(3);
  }
  CFX_Matrix mtDomain2Target = pDict->GetMatrixFor("Matrix");
  CFX_Matrix matrix = pObject2Bitmap->GetInverse();
  matrix.Concat(mtDomain2Target.GetInverse());
  int width = pBitmap->GetWidth();
  int height = pBitmap->GetHeight();
  int pitch = pBitmap->GetPitch();
  uint32_t total_results = std::max(CountOutputs(funcs), pCS->CountComponents());
  CFX_FixedBufGrow<float, 16> result_array(total_results);
  float* pResults = result_array;
  memset(pResults, 0, total_results * sizeof(float));
  for (int row = 0; row < height; row++) 
  {
    uint32_t* dib_buf = (uint32_t*)(pBitmap->GetBuffer() + row * pitch);
    for (int column = 0; column < width; column++) 
    {
      CFX_PointF pos = matrix.Transform(
        CFX_PointF(static_cast<float>(column), static_cast<float>(row)));
      if (pos.x < xmin || pos.x > xmax || pos.y < ymin || pos.y > ymax)
        continue;

      float input[] = { pos.x, pos.y };
      int offset = 0;
      for (const auto& func : funcs) 
      {
        if (func) 
        {
          int nresults;
          if (func->Call(input, 2, pResults + offset, &nresults))
            offset += nresults;
        }
      }

      float R = 0.0f;
      float G = 0.0f;
      float B = 0.0f;
      pCS->GetRGB(pResults, &R, &G, &B);
      dib_buf[column] = FXARGB_TODIB(FXARGB_MAKE(
        alpha, (int32_t)(R * 255), (int32_t)(G * 255), (int32_t)(B * 255)));
    }
  }
}

bool GetScanlineIntersect(int y, const CFX_PointF& first, const CFX_PointF& second, float* x)
{
  if (first.y == second.y)
    return false;

  if (first.y < second.y) 
  {
    if (y < first.y || y > second.y)
      return false;
  }
  else 
    if (y < second.y || y > first.y) 
    {
      return false;
    }
  *x = first.x + ((second.x - first.x) * (y - first.y) / (second.y - first.y));
  return true;
}

void DrawGouraud(const RetainPtr<CFX_DIBitmap>& pBitmap, int alpha, CPDF_MeshVertex triangle[3]) 
{
  float min_y = triangle[0].position.y;
  float max_y = triangle[0].position.y;
  for (int i = 1; i < 3; i++) 
  {
    min_y = std::min(min_y, triangle[i].position.y);
    max_y = std::max(max_y, triangle[i].position.y);
  }
  if (min_y == max_y)
    return;

  int min_yi = std::max(static_cast<int>(floor(min_y)), 0);
  int max_yi = static_cast<int>(ceil(max_y));

  if (max_yi >= pBitmap->GetHeight())
    max_yi = pBitmap->GetHeight() - 1;

  for (int y = min_yi; y <= max_yi; y++) 
  {
    int nIntersects = 0;
    float inter_x[3];
    float r[3];
    float g[3];
    float b[3];
    for (int i = 0; i < 3; i++)
    {
      CPDF_MeshVertex& vertex1 = triangle[i];
      CPDF_MeshVertex& vertex2 = triangle[(i + 1) % 3];
      CFX_PointF& position1 = vertex1.position;
      CFX_PointF& position2 = vertex2.position;
      bool bIntersect = GetScanlineIntersect(y, position1, position2, &inter_x[nIntersects]);
      if (!bIntersect)
        continue;

      float y_dist = (y - position1.y) / (position2.y - position1.y);
      r[nIntersects] = vertex1.r + ((vertex2.r - vertex1.r) * y_dist);
      g[nIntersects] = vertex1.g + ((vertex2.g - vertex1.g) * y_dist);
      b[nIntersects] = vertex1.b + ((vertex2.b - vertex1.b) * y_dist);
      nIntersects++;
    }
    if (nIntersects != 2)
      continue;

    int min_x, max_x, start_index, end_index;
    if (inter_x[0] < inter_x[1]) 
    {
      min_x = (int)floor(inter_x[0]);
      max_x = (int)ceil(inter_x[1]);
      start_index = 0;
      end_index = 1;
    }
    else 
    {
      min_x = (int)floor(inter_x[1]);
      max_x = (int)ceil(inter_x[0]);
      start_index = 1;
      end_index = 0;
    }

    int start_x = std::max(min_x, 0);
    int end_x = max_x;
    if (end_x > pBitmap->GetWidth())
      end_x = pBitmap->GetWidth();

    uint8_t* dib_buf =
      pBitmap->GetBuffer() + y * pBitmap->GetPitch() + start_x * 4;
    float r_unit = (r[end_index] - r[start_index]) / (max_x - min_x);
    float g_unit = (g[end_index] - g[start_index]) / (max_x - min_x);
    float b_unit = (b[end_index] - b[start_index]) / (max_x - min_x);
    float R = r[start_index] + (start_x - min_x) * r_unit;
    float G = g[start_index] + (start_x - min_x) * g_unit;
    float B = b[start_index] + (start_x - min_x) * b_unit;
    for (int x = start_x; x < end_x; x++)
    {
      R += r_unit;
      G += g_unit;
      B += b_unit;
      FXARGB_SETDIB(dib_buf,
        FXARGB_MAKE(alpha, (int32_t)(R * 255), (int32_t)(G * 255),
        (int32_t)(B * 255)));
      dib_buf += 4;
    }
  }
}

void DrawFreeGouraudShading(const RetainPtr<CFX_DIBitmap>& pBitmap, CFX_Matrix* pObject2Bitmap, CPDF_Stream* pShadingStream,
  const std::vector<std::unique_ptr<CPDF_Function>>& funcs, CPDF_ColorSpace* pCS, int alpha) 
{
  ASSERT(pBitmap->GetFormat() == FXDIB_Argb);

  CPDF_MeshStream stream(kFreeFormGouraudTriangleMeshShading, funcs,
    pShadingStream, pCS);
  if (!stream.Load())
    return;

  CPDF_MeshVertex triangle[3];
  memset(triangle, 0, sizeof(triangle));

  while (!stream.BitStream()->IsEOF())
  {
    CPDF_MeshVertex vertex;
    uint32_t flag;
    if (!stream.ReadVertex(*pObject2Bitmap, &vertex, &flag))
      return;

    if (flag == 0) 
    {
      triangle[0] = vertex;
      for (int j = 1; j < 3; j++)
      {
        uint32_t tflag;
        if (!stream.ReadVertex(*pObject2Bitmap, &triangle[j], &tflag))
          return;
      }
    }
    else 
    {
      if (flag == 1)
        triangle[0] = triangle[1];

      triangle[1] = triangle[2];
      triangle[2] = vertex;
    }
    DrawGouraud(pBitmap, alpha, triangle);
  }
}

void DrawLatticeGouraudShading(const RetainPtr<CFX_DIBitmap>& pBitmap, CFX_Matrix* pObject2Bitmap, CPDF_Stream* pShadingStream,
  const std::vector<std::unique_ptr<CPDF_Function>>& funcs, CPDF_ColorSpace* pCS, int alpha) 
{
  ASSERT(pBitmap->GetFormat() == FXDIB_Argb);

  int row_verts = pShadingStream->GetDict()->GetIntegerFor("VerticesPerRow");
  if (row_verts < 2)
    return;

  CPDF_MeshStream stream(kLatticeFormGouraudTriangleMeshShading, funcs,
    pShadingStream, pCS);
  if (!stream.Load())
    return;

  std::vector<CPDF_MeshVertex> vertices[2];
  vertices[0] = stream.ReadVertexRow(*pObject2Bitmap, row_verts);
  if (vertices[0].empty())
    return;

  int last_index = 0;
  while (1) 
  {
    vertices[1 - last_index] = stream.ReadVertexRow(*pObject2Bitmap, row_verts);
    if (vertices[1 - last_index].empty())
      return;

    CPDF_MeshVertex triangle[3];
    for (int i = 1; i < row_verts; ++i) 
    {
      triangle[0] = vertices[last_index][i];
      triangle[1] = vertices[1 - last_index][i - 1];
      triangle[2] = vertices[last_index][i - 1];
      DrawGouraud(pBitmap, alpha, triangle);
      triangle[2] = vertices[1 - last_index][i];
      DrawGouraud(pBitmap, alpha, triangle);
    }
    last_index = 1 - last_index;
  }
}

struct Coon_BezierCoeff
{
  float a, b, c, d;
  void FromPoints(float p0, float p1, float p2, float p3) 
  {
    a = -p0 + 3 * p1 - 3 * p2 + p3;
    b = 3 * p0 - 6 * p1 + 3 * p2;
    c = -3 * p0 + 3 * p1;
    d = p0;
  }
  Coon_BezierCoeff first_half() 
  {
    Coon_BezierCoeff result;
    result.a = a / 8;
    result.b = b / 4;
    result.c = c / 2;
    result.d = d;
    return result;
  }
  Coon_BezierCoeff second_half()
  {
    Coon_BezierCoeff result;
    result.a = a / 8;
    result.b = 3 * a / 8 + b / 4;
    result.c = 3 * a / 8 + b / 2 + c / 2;
    result.d = a / 8 + b / 4 + c / 2 + d;
    return result;
  }
  void GetPoints(float p[4]) 
  {
    p[0] = d;
    p[1] = c / 3 + p[0];
    p[2] = b / 3 - p[0] + 2 * p[1];
    p[3] = a + p[0] - 3 * p[1] + 3 * p[2];
  }
  void GetPointsReverse(float p[4])
  {
    p[3] = d;
    p[2] = c / 3 + p[3];
    p[1] = b / 3 - p[3] + 2 * p[2];
    p[0] = a + p[3] - 3 * p[2] + 3 * p[1];
  }
  void BezierInterpol(Coon_BezierCoeff& C1, Coon_BezierCoeff& C2, Coon_BezierCoeff& D1, Coon_BezierCoeff& D2)
  {
    a = (D1.a + D2.a) / 2;
    b = (D1.b + D2.b) / 2;
    c = (D1.c + D2.c) / 2 - (C1.a / 8 + C1.b / 4 + C1.c / 2) +
      (C2.a / 8 + C2.b / 4) + (-C1.d + D2.d) / 2 - (C2.a + C2.b) / 2;
    d = C1.a / 8 + C1.b / 4 + C1.c / 2 + C1.d;
  }
  float Distance() 
  {
    float dis = a + b + c;
    return dis < 0 ? -dis : dis;
  }
};

struct Coon_Bezier 
{
  Coon_BezierCoeff x, y;
  void FromPoints(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
  {
    x.FromPoints(x0, x1, x2, x3);
    y.FromPoints(y0, y1, y2, y3);
  }

  Coon_Bezier first_half() 
  {
    Coon_Bezier result;
    result.x = x.first_half();
    result.y = y.first_half();
    return result;
  }

  Coon_Bezier second_half() 
  {
    Coon_Bezier result;
    result.x = x.second_half();
    result.y = y.second_half();
    return result;
  }

  void BezierInterpol(Coon_Bezier& C1, Coon_Bezier& C2, Coon_Bezier& D1, Coon_Bezier& D2) 
  {
    x.BezierInterpol(C1.x, C2.x, D1.x, D2.x);
    y.BezierInterpol(C1.y, C2.y, D1.y, D2.y);
  }

  void GetPoints(std::vector<FX_PATHPOINT>& pPoints, size_t start_idx) 
  {
    float p[4];
    int i;
    x.GetPoints(p);
    for (i = 0; i < 4; i++)
      pPoints[start_idx + i].m_Point.x = p[i];

    y.GetPoints(p);
    for (i = 0; i < 4; i++)
      pPoints[start_idx + i].m_Point.y = p[i];
  }

  void GetPointsReverse(std::vector<FX_PATHPOINT>& pPoints, size_t start_idx) 
  {
    float p[4];
    int i;
    x.GetPointsReverse(p);
    for (i = 0; i < 4; i++)
      pPoints[i + start_idx].m_Point.x = p[i];

    y.GetPointsReverse(p);
    for (i = 0; i < 4; i++)
      pPoints[i + start_idx].m_Point.y = p[i];
  }

  float Distance() 
  { 
    return x.Distance() + y.Distance();
  }
};

int Interpolate(int p1, int p2, int delta1, int delta2, bool* overflow)
{
  pdfium::base::CheckedNumeric<int> p = p2;
  p -= p1;
  p *= delta1;
  p /= delta2;
  p += p1;
  if (!p.IsValid())
    *overflow = true;
  return p.ValueOrDefault(0);
}

int BiInterpolImpl(int c0, int c1, int c2, int c3, int x, int y, int x_scale, int y_scale, bool* overflow) 
{
  int x1 = Interpolate(c0, c3, x, x_scale, overflow);
  int x2 = Interpolate(c1, c2, x, x_scale, overflow);
  return Interpolate(x1, x2, y, y_scale, overflow);
}

struct Coon_Color 
{
  Coon_Color() 
  { 
    memset(comp, 0, sizeof(int) * 3); 
  }
  int comp[3];

  // Returns true if successful, false if overflow detected.
  bool BiInterpol(Coon_Color colors[4], int x, int y, int x_scale, int y_scale) 
  {
    bool overflow = false;
    for (int i = 0; i < 3; i++) 
    {
      comp[i] = BiInterpolImpl(colors[0].comp[i], colors[1].comp[i],
        colors[2].comp[i], colors[3].comp[i], x, y,
        x_scale, y_scale, &overflow);
    }
    return !overflow;
  }

  int Distance(Coon_Color& o) 
  {
    return std::max({ abs(comp[0] - o.comp[0]), abs(comp[1] - o.comp[1]), abs(comp[2] - o.comp[2]) });
  }
};

#define COONCOLOR_THRESHOLD 4
struct CPDF_PatchDrawer 
{
  Coon_Color patch_colors[4];
  int max_delta;
  CFX_PathData path;
  CFX_RenderDevice* pDevice;
  int fill_mode;
  int alpha;
  void Draw(int x_scale, int y_scale, int left, int bottom, Coon_Bezier C1, Coon_Bezier C2, Coon_Bezier D1, Coon_Bezier D2)
  {
    bool bSmall = C1.Distance() < 2 && C2.Distance() < 2 && D1.Distance() < 2 &&
      D2.Distance() < 2;
    Coon_Color div_colors[4];
    int d_bottom = 0;
    int d_left = 0;
    int d_top = 0;
    int d_right = 0;
    if (!div_colors[0].BiInterpol(patch_colors, left, bottom, x_scale, y_scale))
    {
      return;
    }
    if (!bSmall) 
    {
      if (!div_colors[1].BiInterpol(patch_colors, left, bottom + 1, x_scale, y_scale))
      {
        return;
      }
      if (!div_colors[2].BiInterpol(patch_colors, left + 1, bottom + 1, x_scale, y_scale)) 
      {
        return;
      }
      if (!div_colors[3].BiInterpol(patch_colors, left + 1, bottom, x_scale, y_scale)) 
      {
        return;
      }
      d_bottom = div_colors[3].Distance(div_colors[0]);
      d_left = div_colors[1].Distance(div_colors[0]);
      d_top = div_colors[1].Distance(div_colors[2]);
      d_right = div_colors[2].Distance(div_colors[3]);
    }

    if (bSmall ||
      (d_bottom < COONCOLOR_THRESHOLD && d_left < COONCOLOR_THRESHOLD &&
        d_top < COONCOLOR_THRESHOLD && d_right < COONCOLOR_THRESHOLD)) 
    {
      std::vector<FX_PATHPOINT>& pPoints = path.GetPoints();
      C1.GetPoints(pPoints, 0);
      D2.GetPoints(pPoints, 3);
      C2.GetPointsReverse(pPoints, 6);
      D1.GetPointsReverse(pPoints, 9);
      int fillFlags = FXFILL_WINDING | FXFILL_FULLCOVER;
      if (fill_mode & RENDER_NOPATHSMOOTH) 
      {
        fillFlags |= FXFILL_NOPATHSMOOTH;
      }
      pDevice->DrawPath( &path, nullptr, nullptr,
        FXARGB_MAKE(alpha, div_colors[0].comp[0], div_colors[0].comp[1],
          div_colors[0].comp[2]),
        0, fillFlags);
    }
    else 
    {
      if (d_bottom < COONCOLOR_THRESHOLD && d_top < COONCOLOR_THRESHOLD) 
      {
        Coon_Bezier m1;
        m1.BezierInterpol(D1, D2, C1, C2);
        y_scale *= 2;
        bottom *= 2;
        Draw(x_scale, y_scale, left, bottom, C1, m1, D1.first_half(),
          D2.first_half());
        Draw(x_scale, y_scale, left, bottom + 1, m1, C2, D1.second_half(),
          D2.second_half());
      }
      else 
        if (d_left < COONCOLOR_THRESHOLD &&  d_right < COONCOLOR_THRESHOLD)
        {
          Coon_Bezier m2;
          m2.BezierInterpol(C1, C2, D1, D2);
          x_scale *= 2;
          left *= 2;
          Draw(x_scale, y_scale, left, bottom, C1.first_half(), C2.first_half(),
            D1, m2);
          Draw(x_scale, y_scale, left + 1, bottom, C1.second_half(),
            C2.second_half(), m2, D2);
        }
        else 
        {
          Coon_Bezier m1, m2;
          m1.BezierInterpol(D1, D2, C1, C2);
          m2.BezierInterpol(C1, C2, D1, D2);
          Coon_Bezier m1f = m1.first_half();
          Coon_Bezier m1s = m1.second_half();
          Coon_Bezier m2f = m2.first_half();
          Coon_Bezier m2s = m2.second_half();
          x_scale *= 2;
          y_scale *= 2;
          left *= 2;
          bottom *= 2;
          Draw(x_scale, y_scale, left, bottom, C1.first_half(), m1f,
            D1.first_half(), m2f);
          Draw(x_scale, y_scale, left, bottom + 1, m1f, C2.first_half(),
            D1.second_half(), m2s);
          Draw(x_scale, y_scale, left + 1, bottom, C1.second_half(), m1s, m2f,
            D2.first_half());
          Draw(x_scale, y_scale, left + 1, bottom + 1, m1s, C2.second_half(), m2s,
            D2.second_half());
        }
    }
  }
};

void DrawCoonPatchMeshes(ShadingType type, const RetainPtr<CFX_DIBitmap>& pBitmap, CFX_Matrix* pObject2Bitmap, CPDF_Stream* pShadingStream,
  const std::vector<std::unique_ptr<CPDF_Function>>& funcs, CPDF_ColorSpace* pCS, int fill_mode, int alpha) 
{
  ASSERT(pBitmap->GetFormat() == FXDIB_Argb);
  ASSERT(type == kCoonsPatchMeshShading ||
    type == kTensorProductPatchMeshShading);

  CFX_DefaultRenderDevice device;
  device.Attach(pBitmap, false, nullptr, false);
  CPDF_MeshStream stream(type, funcs, pShadingStream, pCS);
  if (!stream.Load())
    return;

  CPDF_PatchDrawer patch;
  patch.alpha = alpha;
  patch.pDevice = &device;
  patch.fill_mode = fill_mode;

  for (int i = 0; i < 13; i++) 
  {
    patch.path.AppendPoint(
      CFX_PointF(), i == 0 ? FXPT_TYPE::MoveTo : FXPT_TYPE::BezierTo, false);
  }

  CFX_PointF coords[16];
  int point_count = type == kTensorProductPatchMeshShading ? 16 : 12;
  while (!stream.BitStream()->IsEOF())
  {
    if (!stream.CanReadFlag())
      break;
    uint32_t flag = stream.ReadFlag();
    int iStartPoint = 0, iStartColor = 0, i = 0;
    if (flag) 
    {
      iStartPoint = 4;
      iStartColor = 2;
      CFX_PointF tempCoords[4];
      for (i = 0; i < 4; i++) 
      {
        tempCoords[i] = coords[(flag * 3 + i) % 12];
      }
      memcpy(coords, tempCoords, sizeof(tempCoords));
      Coon_Color tempColors[2];
      tempColors[0] = patch.patch_colors[flag];
      tempColors[1] = patch.patch_colors[(flag + 1) % 4];
      memcpy(patch.patch_colors, tempColors, sizeof(Coon_Color) * 2);
    }
    for (i = iStartPoint; i < point_count; i++)
    {
      if (!stream.CanReadCoords())
        break;
      coords[i] = pObject2Bitmap->Transform(stream.ReadCoords());
    }

    for (i = iStartColor; i < 4; i++) 
    {
      if (!stream.CanReadColor())
        break;

      float r;
      float g;
      float b;
      std::tie(r, g, b) = stream.ReadColor();

      patch.patch_colors[i].comp[0] = (int32_t)(r * 255);
      patch.patch_colors[i].comp[1] = (int32_t)(g * 255);
      patch.patch_colors[i].comp[2] = (int32_t)(b * 255);
    }
    CFX_FloatRect bbox = CFX_FloatRect::GetBBox(coords, point_count);
    if (bbox.right <= 0 || bbox.left >= (float)pBitmap->GetWidth() ||
      bbox.top <= 0 || bbox.bottom >= (float)pBitmap->GetHeight()) 
    {
      continue;
    }
    Coon_Bezier C1, C2, D1, D2;
    C1.FromPoints(coords[0].x, coords[0].y, coords[11].x, coords[11].y,
      coords[10].x, coords[10].y, coords[9].x, coords[9].y);
    C2.FromPoints(coords[3].x, coords[3].y, coords[4].x, coords[4].y,
      coords[5].x, coords[5].y, coords[6].x, coords[6].y);
    D1.FromPoints(coords[0].x, coords[0].y, coords[1].x, coords[1].y,
      coords[2].x, coords[2].y, coords[3].x, coords[3].y);
    D2.FromPoints(coords[9].x, coords[9].y, coords[8].x, coords[8].y,
      coords[7].x, coords[7].y, coords[6].x, coords[6].y);
    patch.Draw(1, 1, 0, 0, C1, C2, D1, D2);
  }
}

class OdStateRestorer
{
public:
  explicit OdStateRestorer(bool& val, const bool new_val)
    :m_Val(val)
  {
    old_val = m_Val;
    m_Val = new_val;
  }
  ~OdStateRestorer()
  {
    m_Val = old_val;
  }

  bool& m_Val;
  bool old_val;
};

}  // namespace

OdRenderStatus::OdRenderStatus(std::wstring& current_layer_name, bool& is_object_visible, long options)
  :CPDF_RenderStatus()
  ,m_CurrentLayerName(current_layer_name)
  ,m_IsObjectVisible(is_object_visible)
  , m_PdfImportOptions(options)
{

}

OdRenderStatus::~OdRenderStatus()
{

}

void OdRenderStatus::RenderSingleObject(CPDF_PageObject* pObj, const CFX_Matrix* pObj2Device) 
{
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
  AutoRestorer<int> restorer(&s_CurrentRecursionDepth);
  if (++s_CurrentRecursionDepth > kRenderMaxRecursionDepth) 
  {
    return;
  }
  m_pCurObj = pObj;
  
  std::vector<WideString> layers_cache;
  bool visible = true;
  if (m_Options.GetOCContext() && pObj->m_ContentMark.HasRef()) 
  {
    visible = m_Options.GetOCContext()->CheckObjectVisible(pObj);
    for (size_t i = 0; i < pObj->m_ContentMark.CountItems(); ++i) 
    {
      const CPDF_ContentMarkItem& item = pObj->m_ContentMark.GetItem(i);
      if (item.GetName() == "OC" && item.GetParamType() == CPDF_ContentMarkItem::PropertiesDict)
      {
        CPDF_Dictionary* pDict = item.GetParam();
        if (pDict)
        {
          layers_cache.emplace_back(pDict->GetUnicodeTextFor("Name"));
        }
      }
    }
  }
  if (0 != layers_cache.size())
    m_CurrentLayerName = layers_cache.back().c_str();
  else
    m_CurrentLayerName.clear();

  m_IsObjectVisible = visible;

  ProcessClipPath(pObj->m_ClipPath, pObj2Device);
  if (ProcessTransparency(pObj, pObj2Device)) 
  {
    return;
  }
  ProcessObjectNoClip(pObj, pObj2Device);
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
}

bool OdRenderStatus::ContinueSingleObject(CPDF_PageObject* pObj, const CFX_Matrix* pObj2Device, IFX_PauseIndicator* pPause)
{
  if (m_pImageRenderer) 
  {
    if (m_pImageRenderer->Continue(pPause))
      return true;

    if (!m_pImageRenderer->GetResult())
      DrawObjWithBackground(pObj, pObj2Device);
    m_pImageRenderer.reset();
    return false;
  }

  m_pCurObj = pObj;

  std::vector<WideString> layers_cache;
  bool visible = true;
  if (m_Options.GetOCContext() && pObj->m_ContentMark.HasRef())
  {
    visible = m_Options.GetOCContext()->CheckObjectVisible(pObj);
    for (size_t i = 0; i < pObj->m_ContentMark.CountItems(); ++i)
    {
      const CPDF_ContentMarkItem& item = pObj->m_ContentMark.GetItem(i);
      if (item.GetName() == "OC" && item.GetParamType() == CPDF_ContentMarkItem::PropertiesDict)
      {
        CPDF_Dictionary* pDict = item.GetParam();
        if (pDict)
        {
          layers_cache.emplace_back(pDict->GetUnicodeTextFor("Name"));
        }
      }
    }
  }

  if (0 != layers_cache.size())
    m_CurrentLayerName = layers_cache.back().c_str();
  else
    m_CurrentLayerName.clear();

  m_IsObjectVisible = visible;

  auto od_device = dynamic_cast<OdDeviceDriver*>(m_pDevice->GetDeviceDriver());
  bool tmp_state(true);
  ODA::OdStateRestorer state_restorer(nullptr != od_device && pObj->IsImage() && od_device->isClippingEnabled() && !od_device->isImageClippingEnabled() ? od_device->isClippingEnabled() : tmp_state, false);

  ProcessClipPath(pObj->m_ClipPath, pObj2Device);
  if (ProcessTransparency(pObj, pObj2Device))
    return false;

  if (!pObj->IsImage())
  {
    ProcessObjectNoClip(pObj, pObj2Device);
    return false;
  }

  m_pImageRenderer = pdfium::MakeUnique<OdImageRenderer>(m_CurrentLayerName, m_IsObjectVisible);
  if (!m_pImageRenderer->Start(this, pObj->AsImage(), pObj2Device, false,
                               FXDIB_BLEND_NORMAL)) 
  {
    if (!m_pImageRenderer->GetResult())
      DrawObjWithBackground(pObj, pObj2Device);
    m_pImageRenderer.reset();
    return false;
  }
  return ContinueSingleObject(pObj, pObj2Device, pPause);
}

void OdRenderStatus::ProcessObjectNoClip(CPDF_PageObject* pObj, const CFX_Matrix* pObj2Device) 
{
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
  bool bRet = false;
  switch (pObj->GetType()) 
  {
    case CPDF_PageObject::TEXT:
      bRet = ProcessText(pObj->AsText(), pObj2Device, nullptr);
      break;
    case CPDF_PageObject::PATH:
      bRet = ProcessPath(pObj->AsPath(), pObj2Device);
      break;
    case CPDF_PageObject::IMAGE:
      bRet = ProcessImage(pObj->AsImage(), pObj2Device);
      break;
    case CPDF_PageObject::SHADING:
      ProcessShading(pObj->AsShading(), pObj2Device);
      return;
    case CPDF_PageObject::FORM:
      bRet = ProcessForm(pObj->AsForm(), pObj2Device);
      break;
  }
  if (!bRet)
    DrawObjWithBackground(pObj, pObj2Device);
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
}

bool OdRenderStatus::DrawObjWithBlend(CPDF_PageObject* pObj,
  const CFX_Matrix* pObj2Device) {
  bool bRet = false;
  switch (pObj->GetType()) 
  {
  case CPDF_PageObject::PATH:
    bRet = ProcessPath(pObj->AsPath(), pObj2Device);
    break;
  case CPDF_PageObject::IMAGE:
    bRet = ProcessImage(pObj->AsImage(), pObj2Device);
    break;
  case CPDF_PageObject::FORM:
    bRet = ProcessForm(pObj->AsForm(), pObj2Device);
    break;
  case CPDF_PageObject::TEXT:
    bRet = ProcessText(pObj->AsText(), pObj2Device, nullptr);
    break;
  default:
    break;
  }
  return bRet;
}

void OdRenderStatus::DrawObjWithBackground(CPDF_PageObject* pObj, const CFX_Matrix* pObj2Device) 
{
  FX_RECT rect;
  if (GetObjectClippedRect(pObj, pObj2Device, false, rect))
  {
    return;
  }
  int res = 300;
  if (pObj->IsImage() &&
      m_pDevice->GetDeviceCaps(FXDC_DEVICE_CLASS) == FXDC_PRINTER) 
  {
    res = 0;
  }
  CPDF_ScaledRenderBuffer buffer;
  if (!buffer.Initialize(m_pContext.Get(), m_pDevice, rect, pObj, &m_Options, res))
  {
    return;
  }
  CFX_Matrix matrix = *pObj2Device;
  matrix.Concat(*buffer.GetMatrix());
  GetScaledMatrix(matrix);
  CPDF_Dictionary* pFormResource = nullptr;
  const CPDF_FormObject* pFormObj = pObj->AsForm();
  if (pFormObj) 
  {
    const auto& pFormDict = pFormObj->form()->m_pFormDict;
    if (pFormDict)
      pFormResource = pFormDict->GetDictFor("Resources");
  }
  OdRenderStatus status(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
  status.Initialize(m_pContext.Get(), buffer.GetDevice(), buffer.GetMatrix(),
                    nullptr, nullptr, nullptr, &m_Options, m_iTransparency,
                    m_bDropObjects, pFormResource);
  status.RenderSingleObject(pObj, &matrix);
  buffer.OutputToDevice();
}

bool OdRenderStatus::ProcessForm(const CPDF_FormObject* pFormObj, const CFX_Matrix* pObj2Device) 
{
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif

  //Start ODA

  //CPDF_Dictionary* pOC = pFormObj->form()->m_pFormDict->GetDictFor("OC");
  //if (pOC && m_Options.GetOCContext() &&
  //    !m_Options.GetOCContext()->CheckOCGVisible(pOC)) {
  //  return true;
  //}

  CPDF_Dictionary* pOC = pFormObj->form()->m_pFormDict->GetDictFor("OC");
  if (pOC && m_Options.GetOCContext())
  {
    m_IsObjectVisible = m_Options.GetOCContext()->CheckOCGVisible(pOC);
    m_CurrentLayerName = pOC->GetUnicodeTextFor("Name").c_str();
    ByteString csType = pOC->GetStringFor("Type", "OCG");
  }

  CFX_Matrix matrix = pFormObj->form_matrix();
  matrix.Concat(*pObj2Device);
  const auto& pFormDict = pFormObj->form()->m_pFormDict;
  CPDF_Dictionary* pResources =
      pFormDict ? pFormDict->GetDictFor("Resources") : nullptr;
  OdRenderStatus status(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
  status.Initialize(m_pContext.Get(), m_pDevice, nullptr, m_pStopObj, this,
                    pFormObj, &m_Options, m_iTransparency, m_bDropObjects,
                    pResources, false);
  status.m_curBlend = m_curBlend;
  {
    CFX_RenderDevice::StateRestorer restorer(m_pDevice);
    status.RenderObjectList(pFormObj->form(), &matrix);
    m_bStopped = status.m_bStopped;
  }
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
  return true;
}

bool OdRenderStatus::ProcessTransparency(CPDF_PageObject* pPageObj, const CFX_Matrix* pObj2Device)
{
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
  int blend_type = pPageObj->m_GeneralState.GetBlendType();
  if (blend_type == FXDIB_BLEND_UNSUPPORTED)
    return true;

  CPDF_Dictionary* pSMaskDict =
      ToDictionary(pPageObj->m_GeneralState.GetSoftMask());
  if (pSMaskDict) 
  {
    if (pPageObj->IsImage() &&
        pPageObj->AsImage()->GetImage()->GetDict()->KeyExist("SMask")) 
    {
      pSMaskDict = nullptr;
    }
  }
  CPDF_Dictionary* pFormResource = nullptr;
  float group_alpha = 1.0f;
  int iTransparency = m_iTransparency;
  bool bGroupTransparent = false;
  const CPDF_FormObject* pFormObj = pPageObj->AsForm();
  if (pFormObj)
  {
    group_alpha = pFormObj->m_GeneralState.GetFillAlpha();
    iTransparency = pFormObj->form()->m_iTransparency;
    bGroupTransparent = !!(iTransparency & PDFTRANS_ISOLATED);
    const auto& pFormDict = pFormObj->form()->m_pFormDict;
    if (pFormDict)
      pFormResource = pFormDict->GetDictFor("Resources");
  }
  bool bTextClip =
      (pPageObj->m_ClipPath.HasRef() &&
       pPageObj->m_ClipPath.GetTextCount() > 0 &&
       m_pDevice->GetDeviceClass() == FXDC_DISPLAY &&
       !(m_pDevice->GetDeviceCaps(FXDC_RENDER_CAPS) & FXRC_SOFT_CLIP));
  if ((m_Options.HasFlag(RENDER_OVERPRINT)) && pPageObj->IsImage() &&
      pPageObj->m_GeneralState.GetFillOP() &&
      pPageObj->m_GeneralState.GetStrokeOP()) 
  {
    CPDF_Document* pDocument = nullptr;
    CPDF_Page* pPage = nullptr;
    if (m_pContext->GetPageCache()) {
      pPage = m_pContext->GetPageCache()->GetPage();
      pDocument = pPage->m_pDocument.Get();
    } 
    else 
    {
      pDocument = pPageObj->AsImage()->GetImage()->GetDocument();
    }
    CPDF_Dictionary* pPageResources =
        pPage ? pPage->m_pPageResources.Get() : nullptr;
    CPDF_Object* pCSObj = pPageObj->AsImage()
                              ->GetImage()
                              ->GetStream()
                              ->GetDict()
                              ->GetDirectObjectFor("ColorSpace");
    CPDF_ColorSpace* pColorSpace =
        pDocument->LoadColorSpace(pCSObj, pPageResources);
    if (pColorSpace) 
    {
      int format = pColorSpace->GetFamily();
      if (format == PDFCS_DEVICECMYK || format == PDFCS_SEPARATION ||
          format == PDFCS_DEVICEN) 
      {
        blend_type = FXDIB_BLEND_DARKEN;
      }
      pDocument->GetPageData()->ReleaseColorSpace(pCSObj);
    }
  }
  if (!pSMaskDict && group_alpha == 1.0f && blend_type == FXDIB_BLEND_NORMAL &&
      !bTextClip && !bGroupTransparent)
  {
    return false;
  }
  bool isolated = !!(iTransparency & PDFTRANS_ISOLATED);
  if (m_bPrint) 
  {
    bool bRet = false;
    int rendCaps = m_pDevice->GetRenderCaps();
    if (rendCaps & FXRC_BLEND_MODE) 
    {
      int oldBlend = m_curBlend;
      m_curBlend = blend_type;
      bRet = DrawObjWithBlend(pPageObj, pObj2Device);
      m_curBlend = oldBlend;
    }
    if (!bRet)
    {
      DrawObjWithBackground(pPageObj, pObj2Device);
    }
    return true;
  }
  FX_RECT rect = pPageObj->GetBBox(pObj2Device);
  rect.Intersect(m_pDevice->GetClipBox());
  if (rect.IsEmpty())
    return true;

  CFX_Matrix deviceCTM = m_pDevice->GetCTM();
  float scaleX = fabs(deviceCTM.a);
  float scaleY = fabs(deviceCTM.d);
  int width = FXSYS_round((float)rect.Width() * scaleX);
  int height = FXSYS_round((float)rect.Height() * scaleY);
  CFX_DefaultRenderDevice bitmap_device;
  RetainPtr<CFX_DIBitmap> oriDevice;
  if (!isolated && (m_pDevice->GetRenderCaps() & FXRC_GET_BITS)) 
  {
    oriDevice = pdfium::MakeRetain<CFX_DIBitmap>();
    if (!m_pDevice->CreateCompatibleBitmap(oriDevice, width, height))
      return true;
    m_pDevice->GetDIBits(oriDevice, rect.left, rect.top);
  }
  if (!bitmap_device.Create(width, height, FXDIB_Argb, oriDevice))
    return true;

  RetainPtr<CFX_DIBitmap> bitmap = bitmap_device.GetBitmap();
  bitmap->Clear(0);

  CFX_Matrix new_matrix = *pObj2Device;
  new_matrix.Translate(-rect.left, -rect.top);
  new_matrix.Scale(scaleX, scaleY);

  RetainPtr<CFX_DIBitmap> pTextMask;
  if (bTextClip) 
  {
    pTextMask = pdfium::MakeRetain<CFX_DIBitmap>();
    if (!pTextMask->Create(width, height, FXDIB_8bppMask))
      return true;

    pTextMask->Clear(0);
    CFX_DefaultRenderDevice text_device;
    text_device.Attach(pTextMask, false, nullptr, false);
    for (size_t i = 0; i < pPageObj->m_ClipPath.GetTextCount(); ++i)
    {
      CPDF_TextObject* textobj = pPageObj->m_ClipPath.GetText(i);
      if (!textobj)
        break;

      CFX_Matrix text_matrix = textobj->GetTextMatrix();
      CPDF_TextRenderer::DrawTextPath(
          &text_device, textobj->GetCharCodes(), textobj->GetCharPositions(),
          textobj->m_TextState.GetFont(), textobj->m_TextState.GetFontSize(),
          &text_matrix, &new_matrix, textobj->m_GraphState.GetObject(),
          (FX_ARGB)-1, 0, nullptr, 0);
    }
  }
  OdRenderStatus bitmap_render(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
  bitmap_render.Initialize(m_pContext.Get(), &bitmap_device, nullptr,
                           m_pStopObj, nullptr, nullptr, &m_Options, 0,
                           m_bDropObjects, pFormResource, true);
  bitmap_render.ProcessObjectNoClip(pPageObj, &new_matrix);
#if defined _SKIA_SUPPORT_PATHS_
  bitmap_device.Flush(true);
  bitmap->UnPreMultiply();
#endif
  m_bStopped = bitmap_render.m_bStopped;
  if (pSMaskDict) 
  {
    CFX_Matrix smask_matrix = *pPageObj->m_GeneralState.GetSMaskMatrix();
    smask_matrix.Concat(*pObj2Device);
    RetainPtr<CFX_DIBSource> pSMaskSource =
        LoadSMask(pSMaskDict, &rect, &smask_matrix);
    if (pSMaskSource)
      bitmap->MultiplyAlpha(pSMaskSource);
  }
  if (pTextMask) {
    bitmap->MultiplyAlpha(pTextMask);
    pTextMask.Reset();
  }
  int32_t blitAlpha = 255;
  if (iTransparency & PDFTRANS_GROUP && group_alpha != 1.0f) 
  {
    blitAlpha = (int32_t)(group_alpha * 255);
#ifndef _SKIA_SUPPORT_
    bitmap->MultiplyAlpha(blitAlpha);
    blitAlpha = 255;
#endif
  }
  iTransparency = m_iTransparency;
  if (pPageObj->IsForm()) 
  {
    iTransparency |= PDFTRANS_GROUP;
  }
  CompositeDIBitmap(bitmap, rect.left, rect.top, 0, blitAlpha, blend_type,
                    iTransparency);
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
  return true;
}
namespace {

  CFX_Font* GetFont(CPDF_Font* pFont, int32_t position) {
    return position == -1 ? pFont->GetFont() : pFont->GetFontFallback(position);
  }

bool createOutString(CPDF_Font* pFont, CFX_Font* pCFXFont, const int char_count, const uint32_t* char_code, const FXTEXT_CHARPOS* char_pos, const bool fix_unicode_table, WideString& out_str)
{
  out_str.clear();
  bool is_vaid_str = false;
  for (int i = 0; i < char_count; ++i, ++char_code, ++char_pos)
  {
    WideString unicode = pFont->UnicodeFromCharCode(*char_code);
    if (fix_unicode_table && !pFont->IsType1Font() && !pFont->IsStandardFont() && (pFont->IsCIDFont() || pFont->IsType3Font() || pFont->IsEmbedded()) && 2 > unicode.GetLength())
    {

      WideString unicode_t = pFont->CPDF_Font::UnicodeFromCharCode(*char_code);
      bool has_ToNicode_dict = true;
      if (unicode_t.IsEmpty())
        has_ToNicode_dict = false;

      CFX_GEModule* pModule = CFX_GEModule::Get();
      if (pModule)
      {
        auto pFontCache = pModule->GetFontCache();

        FT_ULong font_char_code = pFontCache->GetCharCodeFromFaceCache(pFont, pCFXFont, char_pos->m_GlyphIndex, unicode.IsEmpty() ? 0 : unicode[0]);
        if (0 != font_char_code)
        {
          if (nullptr != pCFXFont->GetFace())
          {
            if (nullptr != pCFXFont->GetFace()->charmap)
            {
              const bool cond1 = (pCFXFont->GetFace()->charmap->encoding == FT_ENCODING_UNICODE);
              const bool cond2 = (pCFXFont->GetFace()->charmap->encoding != FT_ENCODING_UNICODE && !has_ToNicode_dict);
              const bool cond3 = !(pCFXFont->GetFace()->charmap->encoding_id == 0 && pCFXFont->GetFace()->charmap->platform_id == 3);

              if( (cond1 || cond2) && cond3)
                unicode = (wchar_t)font_char_code;
            }
          }
        }

      }

    }

    if (!unicode.IsEmpty())
      is_vaid_str = true;
    out_str += !unicode.IsEmpty() ? unicode : WideString((wchar_t)*char_code);
  }
  return is_vaid_str;
}

}  // namespace

bool DrawNormalText(RenderDevice* pDevice,
  const std::vector<uint32_t>& charCodes,
  const std::vector<float>& charPos,
  CPDF_Font* pFont,
  float font_size,
  const CFX_Matrix* pText2Device,
  FX_ARGB fill_argb,
  const CPDF_RenderOptions* pOptions,
  const bool isType3Font,
  OdPdfiumFontInfo& type3_info,
  const long pdfimport_options,
  const bool is_hex_string_source)
{
  CPDF_CharPosList CharPosList;
  CharPosList.Load(charCodes, charPos, pFont, font_size);
  if (CharPosList.m_nChars == 0)
    return true;
  int FXGE_flags = 0;
  if (pOptions) {
    if (pOptions->HasFlag(RENDER_CLEARTYPE)) {
      FXGE_flags |= FXTEXT_CLEARTYPE;
      if (pOptions->HasFlag(RENDER_BGR_STRIPE))
        FXGE_flags |= FXTEXT_BGR_STRIPE;
    }
    if (pOptions->HasFlag(RENDER_NOTEXTSMOOTH))
      FXGE_flags |= FXTEXT_NOSMOOTH;
    if (pOptions->HasFlag(RENDER_PRINTGRAPHICTEXT))
      FXGE_flags |= FXTEXT_PRINTGRAPHICTEXT;
    if (pOptions->HasFlag(RENDER_NO_NATIVETEXT))
      FXGE_flags |= FXTEXT_NO_NATIVETEXT;
    if (pOptions->HasFlag(RENDER_PRINTIMAGETEXT))
      FXGE_flags |= FXTEXT_PRINTIMAGETEXT;
  }
  else {
    FXGE_flags = FXTEXT_CLEARTYPE;
  }
  if (pFont->IsCIDFont())
    FXGE_flags |= FXFONT_CIDFONT;
  
  const bool invalid_as_geometry = getOption(pdfimport_options, kImportInvalidFontAsGeometry) && is_hex_string_source;
  type3_info.invalid_text_as_geom = getOption(pdfimport_options, kImportInvalidFontAsGeometry);
  const bool fix_unicode_table = getOption(pdfimport_options, kFixUnicodeTable);
  WideString unicode_str;
  bool bDraw = true;
  int32_t fontPosition = CharPosList.m_pCharPos[0].m_FallbackFontPosition;
  uint32_t startIndex = 0;
  for (uint32_t i = 0; i < CharPosList.m_nChars; i++) {
    int32_t curFontPosition = CharPosList.m_pCharPos[i].m_FallbackFontPosition;
    if (fontPosition == curFontPosition)
      continue;

    CFX_Font* font = GetFont(pFont, fontPosition);
    bool is_vaid_str = createOutString(pFont, font, i - startIndex, &charCodes[startIndex], CharPosList.m_pCharPos + startIndex, fix_unicode_table, unicode_str);
    if (invalid_as_geometry && !is_vaid_str)
    {
      FXGE_flags |= FXTEXT_NO_NATIVETEXT;
      FXGE_flags |= FXTEXT_PRINTGRAPHICTEXT;
    }
    if (!pDevice->DrawNormalTextEx(
      i - startIndex, CharPosList.m_pCharPos + startIndex, font,
      font_size, pText2Device, fill_argb, FXGE_flags, isType3Font, unicode_str, type3_info, pFont)) {
      bDraw = false;
    }
    fontPosition = curFontPosition;
    startIndex = i;
  }
  CFX_Font* font = GetFont(pFont, fontPosition);
  bool is_vaid_str = createOutString(pFont, font, CharPosList.m_nChars - startIndex, &charCodes[startIndex], CharPosList.m_pCharPos + startIndex, fix_unicode_table, unicode_str);
  if (invalid_as_geometry && !is_vaid_str)
  {
    FXGE_flags |= FXTEXT_NO_NATIVETEXT;
    FXGE_flags |= FXTEXT_PRINTGRAPHICTEXT;
  }
  if (!pDevice->DrawNormalTextEx(CharPosList.m_nChars - startIndex,
    CharPosList.m_pCharPos + startIndex, font,
    font_size, pText2Device, fill_argb,
    FXGE_flags, isType3Font, unicode_str, type3_info, pFont)) {
    bDraw = false;
  }
  return bDraw;
}

float OdGetCharWidth(uint32_t charCode, CPDF_Font* pFont) 
{
  if (charCode == CPDF_Font::kInvalidCharCode)
    return 0;

  if (float w = pFont->GetCharWidthF(charCode))
    return w;

  ByteString str;
  pFont->AppendChar(&str, charCode);
  if (float w = pFont->GetStringWidth(str.c_str(), 1))
    return w;

  return pFont->GetCharBBox(charCode).Width();
}

bool OdRenderStatus::ProcessText(CPDF_TextObject* textobj, const CFX_Matrix* pObj2Device, CFX_PathData* pClippingPath)
{
  if (textobj->GetCharCodes().empty())
    return true;

  const TextRenderingMode text_render_mode = textobj->m_TextState.GetTextMode();
  if (text_render_mode == TextRenderingMode::MODE_INVISIBLE)
    return true;

  CPDF_Font* pFont = textobj->m_TextState.GetFont();
  
  if (!getOption(m_PdfImportOptions, kImportType3FontAsTT) && pFont->IsType3Font())
    return ProcessType3Text(textobj, pObj2Device);

  bool bFill = false;
  bool bStroke = false;
  bool bClip = false;
  if (pClippingPath) {
    bClip = true;
  }
  else {
    if (getOption(m_PdfImportOptions, kImportType3FontAsTT))
    {
      bFill = true;
    }
    else
    {
      switch (text_render_mode) {
      case TextRenderingMode::MODE_FILL:
      case TextRenderingMode::MODE_FILL_CLIP:
        bFill = true;
        break;
      case TextRenderingMode::MODE_STROKE:
      case TextRenderingMode::MODE_STROKE_CLIP:
        if (pFont->GetFace())
          bStroke = true;
        else
          bFill = true;
        break;
      case TextRenderingMode::MODE_FILL_STROKE:
      case TextRenderingMode::MODE_FILL_STROKE_CLIP:
        bFill = true;
        if (pFont->GetFace())
          bStroke = true;
        break;
      case TextRenderingMode::MODE_INVISIBLE:
        // Already handled above, but the compiler is not smart enough to
        // realize it. Fall through.
        NOTREACHED();
      case TextRenderingMode::MODE_CLIP:
        bFill = true;
        break;
      }
    }
  }
  FX_ARGB stroke_argb = 0;
  FX_ARGB fill_argb = 0;
  bool bPattern = false;
  if (bStroke)
  {
    if (textobj->m_ColorState.GetStrokeColor()->IsPattern())
    {
      bPattern = true;
    }
    else 
    {
      stroke_argb = GetStrokeArgb(textobj);
    }
  }
  if (bFill)
  {
    if (textobj->m_ColorState.GetFillColor()->IsPattern()) 
    {
      bPattern = true;
    }
    else
    {
      fill_argb = GetFillArgb(textobj);
    }
  }
  CFX_Matrix text_matrix = textobj->GetTextMatrix();
  if (!ODA::IsAvailableMatrix(text_matrix))
    return true;

  float font_size = textobj->m_TextState.GetFontSize();
  if (bPattern) {
    DrawTextPathWithPattern(textobj, pObj2Device, pFont, font_size,
      &text_matrix, bFill, bStroke);
    return true;
  }
  if (bClip || bStroke) 
  {
    const CFX_Matrix* pDeviceMatrix = pObj2Device;
    CFX_Matrix device_matrix;
    if (bStroke) {
      const float* pCTM = textobj->m_TextState.GetCTM();
      if (pCTM[0] != 1.0f || pCTM[3] != 1.0f) {
        CFX_Matrix ctm(pCTM[0], pCTM[1], pCTM[2], pCTM[3], 0, 0);
        text_matrix.ConcatInverse(ctm);
        device_matrix = ctm;
        device_matrix.Concat(*pObj2Device);
        pDeviceMatrix = &device_matrix;
      }
    }
    int flag = 0;
    if (bStroke && bFill) 
    {
      flag |= FX_FILL_STROKE;
      flag |= FX_STROKE_TEXT_MODE;
    }
    if (textobj->m_GeneralState.GetStrokeAdjust())
      flag |= FX_STROKE_ADJUST;
    if (m_Options.HasFlag(RENDER_NOTEXTSMOOTH))
      flag |= FXFILL_NOPATHSMOOTH;
    return CPDF_TextRenderer::DrawTextPath(
      m_pDevice, textobj->GetCharCodes(), textobj->GetCharPositions(), pFont,
      font_size, &text_matrix, pDeviceMatrix,
      textobj->m_GraphState.GetObject(), fill_argb, stroke_argb,
      pClippingPath, flag);
  }
  text_matrix.Concat(*pObj2Device);

  std::vector<std::vector<uint32_t>> codes_storage;
  std::vector<std::vector<float>> position_storage;
  std::vector<CFX_Matrix> matrix_storage;
 
  
  uint32_t space_char_code = pFont->CharCodeFromUnicode(32);

  float fontsize = textobj->m_TextState.GetFontSize();
  float space_width(0.0);
  if(CPDF_Font::kInvalidCharCode != space_char_code)
    space_width = static_cast<float>(OdGetCharWidth(space_char_code, pFont))* fontsize / 1000.;
  if (std::fabs(space_width) < 1e-7)
  {
    for (auto& elem : textobj->GetCharCodes())
    {
      if (elem != CPDF_Font::kInvalidCharCode)
      {
        const float val = static_cast<float>(OdGetCharWidth(elem, pFont)* fontsize / 1000.);
        if (std::fabs(space_width) < 1e-7)
        {
          space_width = val;
        }
        else
        {
          space_width = std::min(space_width, val);
        }

      }
    }
  }
  float word_space = textobj->m_TextState.GetWordSpace();
  float char_space = textobj->m_TextState.GetCharSpace();

  char_space = text_matrix.GetInverse().TransformDistance(char_space);

  CPDF_CIDFont* pCIDFont = pFont->AsCIDFont();
  bool isVertWriting = false;
  if (pCIDFont)
    isVertWriting = pCIDFont->IsVertWriting();

  codes_storage.resize(1);
  position_storage.resize(1);
  matrix_storage.push_back(text_matrix);

  auto start_idx(0);
  auto cur_idx(0);

  std::function<void()> fix_last_text_obj =
    [&textobj, &codes_storage, &position_storage, &matrix_storage, &start_idx, &text_matrix]()
  {
    if (start_idx > 0)
    {
      auto j = start_idx - 1;
      while (j > 0 && textobj->GetCharCodes()[j + 1] == CPDF_Font::kInvalidCharCode)
      {
        --j;
      }
      float start_pos = textobj->GetCharPositions()[j];
      std::for_each(position_storage.back().begin(), position_storage.back().end(), [&start_pos](float& elem)
        {
          elem -= start_pos;
        }
      );
      CFX_PointF point = matrix_storage.back().Transform(CFX_PointF(start_pos, 0.0));
      matrix_storage.back().e = point.x;
      matrix_storage.back().f = point.y;
    }
  };

  std::function<void()> add_new_text_obj =
    [&textobj, &codes_storage, &position_storage, &matrix_storage, &start_idx, &text_matrix, &fix_last_text_obj]()
  {
    
    fix_last_text_obj();

    matrix_storage.push_back(text_matrix);
    codes_storage.emplace_back(std::vector<uint32_t>());
    position_storage.emplace_back(std::vector<float>());
  };

  for (auto i = 0; i < textobj->GetCharCodes().size(); ++i)
  {
    uint32_t charcode = textobj->GetCharCodes()[i];

    auto last_pos = 0 == cur_idx ? 0.0 : textobj->GetCharPositions()[cur_idx - 1];
    auto cur_pos = 0 == i ? 0.0 : textobj->GetCharPositions()[i - 1];
    auto last_symbol_width(0.0);
    if (isVertWriting)
    {
      uint16_t CID = pCIDFont->CIDFromCharCode(charcode);
      last_symbol_width = pCIDFont->GetVertWidth(CID) * fontsize / 1000.;
    }
    else
      last_symbol_width = static_cast<float>(OdGetCharWidth(textobj->GetCharCodes()[cur_idx], pFont)) * fontsize / 1000.;
    auto last_symbol_end = last_pos + last_symbol_width + char_space;

    if (CPDF_Font::kInvalidCharCode == charcode || charcode == space_char_code)
    {
      if (codes_storage.back().size() == 0)
        continue;

      const auto next_idx = i + 1;
      auto next_pos = i < textobj->GetCharPositions().size() ? textobj->GetCharPositions()[i] : last_pos;

      if (next_idx < textobj->GetCharCodes().size() && 
        (CPDF_Font::kInvalidCharCode != textobj->GetCharCodes()[next_idx] && textobj->GetCharCodes()[next_idx] != space_char_code))
      {
        if ((std::fabs(last_pos) > std::fabs(next_pos)) || (std::fabs(last_symbol_end) + 1.5 * std::fabs(space_width) < std::fabs(next_pos)))
        {
          add_new_text_obj();

          continue;
        }
        if (space_char_code == CPDF_Font::kInvalidCharCode)
        {
          if (std::fabs(next_pos) - std::fabs(last_symbol_end) < std::fabs(0.5 * space_width))
            continue;
        }
        else
        {
          if ((charcode != space_char_code ) && (std::fabs(next_pos) - std::fabs(last_symbol_end) < std::fabs(0.5 * space_width)))
            continue;
        }
        if (codes_storage.back().size() > 0)
          position_storage.back().push_back(last_symbol_end + char_space);
        codes_storage.back().push_back(space_char_code == CPDF_Font::kInvalidCharCode ? 32 : space_char_code);
      }
      continue;
    }

    if ((0 != codes_storage.back().size()) &&
      ((std::fabs(last_pos) > std::fabs(cur_pos)) || (std::fabs(last_symbol_end) + 1.5 * std::fabs(space_width) < std::fabs(cur_pos))))
    {
      add_new_text_obj();
    }

    if (0 == codes_storage.back().size())
      start_idx = i;
    if (codes_storage.back().size() > 0)
      position_storage.back().push_back(textobj->GetCharPositions()[i - 1]);
    codes_storage.back().push_back(charcode);
    cur_idx = i;
  }

  if (codes_storage.back().size() != 0)
  {
    fix_last_text_obj();
  }

  RenderDevice* render_device = dynamic_cast<RenderDevice*>(m_pDevice);
  if (nullptr == render_device)
    return false;

  bool ret = true;
  for (auto i = 0; i < codes_storage.size(); ++i)
  {
    OdPdfiumFontInfo type3_info;

    if (pFont->IsType3Font())
    {
      CFX_Matrix matrix_offset;
      matrix_offset.a = matrix_storage[i].GetXUnit();
      matrix_offset.d = matrix_storage[i].GetYUnit();
      matrix_offset.e = matrix_storage[i].e;
      matrix_offset.f = matrix_storage[i].f;

      CPDF_Type3Font* pType3Font = pFont->AsType3Font();

      CFX_Matrix char_matrix = pType3Font->GetFontMatrix();
      char_matrix.Scale(font_size, font_size);

      float max_x(-std::numeric_limits<float>::max()), max_y(-std::numeric_limits<float>::max()),
        min_x(std::numeric_limits<float>::max()), min_y(std::numeric_limits<float>::max());

      bool hasType3Size(false);

      for (size_t iChar = 0; iChar < codes_storage[i].size(); ++iChar)
      {
        uint32_t charcode = codes_storage[i][iChar];
        if (charcode == CPDF_Font::kInvalidCharCode)
          continue;

        CPDF_Type3Char* pType3Char = pType3Font->LoadChar(charcode);
        if (!pType3Char)
          continue;

        CFX_Matrix matrix = char_matrix;
        matrix.e += iChar > 0 ? position_storage[i][iChar - 1] : 0;
        matrix.Concat(matrix_offset);

        CPDF_Form* form = pType3Char->form();
        if (nullptr == form)
          continue;
        for (const auto& pCurObj : *form->GetPageObjectList())
        {
          CPDF_PathObject* path_obj = pCurObj->AsPath();
          if (nullptr == path_obj)
            continue;
          CPDF_Path path = path_obj->m_Path;

          CFX_PathData path_data(*path.GetObject());
          path_data.Transform(&matrix);
          CFX_FloatRect bbox = path_data.GetBoundingBox();

          max_x = std::max(max_x, bbox.right);
          max_y = std::max(max_y, bbox.top);
          min_x = std::min(min_x, bbox.left);
          min_y = std::min(min_y, bbox.bottom);
          hasType3Size = true;

        }
      }

      uint32_t A_char = pType3Font->CharCodeFromUnicode(65);
      bool hasAHeight(false);
      float A_max_y(-std::numeric_limits<float>::max()), A_min_y(std::numeric_limits<float>::max());
      if (CPDF_Font::kInvalidCharCode != A_char)
      {
        CPDF_Type3Char* pType3Char = pType3Font->LoadChar(std::numeric_limits<float>::max());
        if (pType3Char)
        {
          CFX_Matrix matrix = char_matrix;

          CPDF_Form* form = pType3Char->form();
          if (nullptr != form)
          {
            for (const auto& pCurObj : *form->GetPageObjectList())
            {
              CPDF_PathObject* path_obj = pCurObj->AsPath();
              if (nullptr != path_obj)
              {
                CPDF_Path path = path_obj->m_Path;

                CFX_PathData path_data(*path.GetObject());
                path_data.Transform(&matrix);
                path_data.Transform(&matrix_offset);
                CFX_FloatRect bbox = path_data.GetBoundingBox();

                A_max_y = std::max(A_max_y, bbox.top);
                A_min_y = std::min(A_min_y, bbox.bottom);
                hasAHeight = true;
              }
            }
          }
        }
      }
      if (hasType3Size)
      {
        type3_info.type3info.m_TextHeight = std::fabs(max_y - min_y);
        type3_info.type3info.m_TextWidth = std::fabs(max_x - min_x);
      }
      const float A_height = std::fabs(A_max_y - A_min_y);
      if (hasAHeight && A_height > std::numeric_limits<float>::epsilon() )
      {
        type3_info.type3info.m_TextHeight = A_height;
      }

      matrix_storage[i].Scale(1.0 /matrix_storage[i].GetXUnit(), 1.0 /matrix_storage[i].GetYUnit());

      matrix_storage[i].e = 0;
      matrix_storage[i].f = 0;
      CFX_PointF tmp_point(type3_info.type3info.m_TextWidth, type3_info.type3info.m_TextHeight);
      tmp_point = matrix_storage[i].Transform(tmp_point);

      if (hasType3Size)
      {
        matrix_storage[i].e = min_x;
        matrix_storage[i].f = min_y;
      }

      type3_info.type3info.m_TextHeight *= matrix_storage[i].GetYUnit();

    }

    type3_info.space_width = space_width;
    ret = ret && DrawNormalText(
      render_device, codes_storage[i], position_storage[i], pFont,
      font_size, &matrix_storage[i], fill_argb, &m_Options, pFont->IsType3Font(), type3_info, m_PdfImportOptions, textobj->IsHexStringSource());
  }

  return ret;


}

bool OdRenderStatus::ProcessType3Text(CPDF_TextObject* textobj, const CFX_Matrix* pObj2Device)
{
  CPDF_Type3Font* pType3Font = textobj->m_TextState.GetFont()->AsType3Font();
  if (pdfium::ContainsValue(m_Type3FontCache, pType3Font))
    return true;

  CFX_Matrix dCTM = m_pDevice->GetCTM();
  float sa = fabs(dCTM.a);
  float sd = fabs(dCTM.d);
  CFX_Matrix text_matrix = textobj->GetTextMatrix();
  CFX_Matrix char_matrix = pType3Font->GetFontMatrix();
  float font_size = textobj->m_TextState.GetFontSize();
  char_matrix.Scale(font_size, font_size);
  FX_ARGB fill_argb = GetFillArgb(textobj, true);
  int fill_alpha = FXARGB_A(fill_argb);
  int device_class = m_pDevice->GetDeviceClass();
  std::vector<FXTEXT_GLYPHPOS> glyphs;
  if (device_class == FXDC_DISPLAY)
    glyphs.resize(textobj->GetCharCodes().size());
  else if (fill_alpha < 255)
    return false;

  ODA::CPDF_RefType3Cache refTypeCache(pType3Font);
  for (size_t iChar = 0; iChar < textobj->GetCharCodes().size(); ++iChar) 
  {
    uint32_t charcode = textobj->GetCharCodes()[iChar];
    if (charcode == static_cast<uint32_t>(-1))
      continue;

    CPDF_Type3Char* pType3Char = pType3Font->LoadChar(charcode);
    if (!pType3Char)
      continue;

    CFX_Matrix matrix = char_matrix;
    matrix.e += iChar > 0 ? textobj->GetCharPositions()[iChar - 1] : 0;
    matrix.Concat(text_matrix);
    matrix.Concat(*pObj2Device);
    if (!pType3Char->LoadBitmap(m_pContext.Get()))
    {
      if (!glyphs.empty()) 
      {
        for (size_t i = 0; i < iChar; ++i)
        {
          const FXTEXT_GLYPHPOS& glyph = glyphs[i];
          if (!glyph.m_pGlyph)
            continue;

          m_pDevice->SetBitMask(glyph.m_pGlyph->m_pBitmap,
                                glyph.m_Origin.x + glyph.m_pGlyph->m_Left,
                                glyph.m_Origin.y - glyph.m_pGlyph->m_Top,
                                fill_argb);
        }
        glyphs.clear();
      }

      std::unique_ptr<CPDF_GraphicStates> pStates =
          CloneObjStates(textobj, false);
      CPDF_RenderOptions options = m_Options;
      uint32_t option_flags = options.GetFlags();
      option_flags |= RENDER_FORCE_HALFTONE | RENDER_RECT_AA;
      option_flags &= ~RENDER_FORCE_DOWNSAMPLE;
      options.SetFlags(option_flags);

      CPDF_Dictionary* pFormResource = nullptr;
      if (pType3Char->form() && pType3Char->form()->m_pFormDict) 
      {
        pFormResource =
            pType3Char->form()->m_pFormDict->GetDictFor("Resources");
      }
      if (fill_alpha == 255)
      {
        OdRenderStatus status (m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
        status.Initialize(m_pContext.Get(), m_pDevice, nullptr, nullptr, this,
                          pStates.get(), &options,
                          pType3Char->form()->m_iTransparency, m_bDropObjects,
                          pFormResource, false, pType3Char, fill_argb);
        status.m_Type3FontCache = m_Type3FontCache;
        status.m_Type3FontCache.push_back(pType3Font);

        CFX_RenderDevice::StateRestorer restorer(m_pDevice);
        status.RenderObjectList(pType3Char->form(), &matrix);
      } 
      else
      {
        FX_RECT rect =
            matrix.TransformRect(pType3Char->form()->CalcBoundingBox())
                .GetOuterRect();
        CFX_DefaultRenderDevice bitmap_device;
        if (!bitmap_device.Create((int)(rect.Width() * sa),
                                  (int)(rect.Height() * sd), FXDIB_Argb,
                                  nullptr)) {
          return true;
        }
        bitmap_device.GetBitmap()->Clear(0);
        OdRenderStatus status(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
        status.Initialize(m_pContext.Get(), &bitmap_device, nullptr, nullptr,
                          this, pStates.get(), &options,
                          pType3Char->form()->m_iTransparency, m_bDropObjects,
                          pFormResource, false, pType3Char, fill_argb);
        status.m_Type3FontCache = m_Type3FontCache;
        status.m_Type3FontCache.push_back(pType3Font);
        matrix.Translate(-rect.left, -rect.top);
        matrix.Scale(sa, sd);
        status.RenderObjectList(pType3Char->form(), &matrix);
        m_pDevice->SetDIBits(bitmap_device.GetBitmap(), rect.left, rect.top);
      }
    } 
    else 
      if (pType3Char->GetBitmap()) 
      {
      if (device_class == FXDC_DISPLAY) 
      {
        RetainPtr<CPDF_Type3Cache> pCache = GetCachedType3(pType3Font);
        refTypeCache.m_dwCount++;
        CFX_GlyphBitmap* pBitmap = pCache->LoadGlyph(charcode, &matrix, sa, sd);
        if (!pBitmap)
          continue;

        CFX_Point origin(FXSYS_round(matrix.e), FXSYS_round(matrix.f));
        if (glyphs.empty()) 
        {
          m_pDevice->SetBitMask(pBitmap->m_pBitmap, origin.x + pBitmap->m_Left,
                                origin.y - pBitmap->m_Top, fill_argb);
        } 
        else 
        {
          glyphs[iChar].m_pGlyph = pBitmap;
          glyphs[iChar].m_Origin = origin;
        }
      } 
      else 
      {
        CFX_Matrix image_matrix = pType3Char->matrix();
        image_matrix.Concat(matrix);
        OdImageRenderer renderer(m_CurrentLayerName, m_IsObjectVisible);
        if (renderer.Start(this, pType3Char->GetBitmap(), fill_argb, 255,
                           &image_matrix, 0, false, FXDIB_BLEND_NORMAL)) 
        {
          renderer.Continue(nullptr);
        }
        if (!renderer.GetResult())
          return false;
      }
    }
  }

  if (glyphs.empty())
    return true;

  FX_RECT rect = FXGE_GetGlyphsBBox(glyphs, 0, sa, sd);
  auto pBitmap = pdfium::MakeRetain<CFX_DIBitmap>();
  if (!pBitmap->Create(static_cast<int>(rect.Width() * sa),
                       static_cast<int>(rect.Height() * sd), FXDIB_8bppMask)) 
  {
    return true;
  }
  pBitmap->Clear(0);
  for (const FXTEXT_GLYPHPOS& glyph : glyphs) 
  {
    if (!glyph.m_pGlyph)
      continue;

    pdfium::base::CheckedNumeric<int> left = glyph.m_Origin.x;
    left += glyph.m_pGlyph->m_Left;
    left -= rect.left;
    left *= sa;
    if (!left.IsValid())
      continue;

    pdfium::base::CheckedNumeric<int> top = glyph.m_Origin.y;
    top -= glyph.m_pGlyph->m_Top;
    top -= rect.top;
    top *= sd;
    if (!top.IsValid())
      continue;

    pBitmap->CompositeMask(left.ValueOrDie(), top.ValueOrDie(),
                           glyph.m_pGlyph->m_pBitmap->GetWidth(),
                           glyph.m_pGlyph->m_pBitmap->GetHeight(),
                           glyph.m_pGlyph->m_pBitmap, fill_argb, 0, 0,
                           FXDIB_BLEND_NORMAL, nullptr, false, 0);
  }
  m_pDevice->SetBitMask(pBitmap, rect.left, rect.top, fill_argb);
  return true;
}

void OdRenderStatus::DrawTilingPattern(CPDF_TilingPattern* pPattern, CPDF_PageObject* pPageObj, const CFX_Matrix* pObj2Device, bool bStroke) 
{
  if (!pPattern->Load())
    return;

  auto od_device = dynamic_cast<OdDeviceDriver*>(m_pDevice->GetDeviceDriver());
  bool tmp_state(true);
  ODA::OdStateRestorer state_restorer(nullptr != od_device ? od_device->isClippingEnabled() : tmp_state, true);

  CFX_RenderDevice::StateRestorer restorer(m_pDevice);
  if (pPageObj->IsPath()) 
  {
    if (!SelectClipPath(pPageObj->AsPath(), pObj2Device, bStroke))
      return;
  } 
  else 
    if (pPageObj->IsImage()) 
    {
      m_pDevice->SetClip_Rect(pPageObj->GetBBox(pObj2Device));
    } 
    else 
    {
      return;
    }

  FX_RECT clip_box = m_pDevice->GetClipBox();
  if (clip_box.IsEmpty())
    return;

  CFX_Matrix dCTM = m_pDevice->GetCTM();
  float sa = fabs(dCTM.a);
  float sd = fabs(dCTM.d);
  clip_box.right = clip_box.left + (int32_t)ceil(clip_box.Width() * sa);
  clip_box.bottom = clip_box.top + (int32_t)ceil(clip_box.Height() * sd);

  CFX_Matrix mtPattern2Device = *pPattern->pattern_to_form();
  mtPattern2Device.Concat(*pObj2Device);
  GetScaledMatrix(mtPattern2Device);

  bool bAligned =
      pPattern->bbox().left == 0 && pPattern->bbox().bottom == 0 &&
      pPattern->bbox().right == pPattern->x_step() &&
      pPattern->bbox().top == pPattern->y_step() &&
      (mtPattern2Device.IsScaled() || mtPattern2Device.Is90Rotated());

  CFX_FloatRect cell_bbox = mtPattern2Device.TransformRect(pPattern->bbox());

  float ceil_height = std::ceil(cell_bbox.Height());
  float ceil_width = std::ceil(cell_bbox.Width());

  // Validate the float will fit into the int when the conversion is done.
  if (!pdfium::base::IsValueInRangeForNumericType<int>(ceil_height) ||
      !pdfium::base::IsValueInRangeForNumericType<int>(ceil_width)) 
  {
    return;
  }

  int width = static_cast<int>(ceil_width);
  int height = static_cast<int>(ceil_height);
  if (width <= 0)
    width = 1;
  if (height <= 0)
    height = 1;

  CFX_FloatRect clip_box_p =
      mtPattern2Device.GetInverse().TransformRect(CFX_FloatRect(clip_box));
  int min_col = (int)ceil((clip_box_p.left - pPattern->bbox().right) /
                          pPattern->x_step());
  int max_col = (int)floor((clip_box_p.right - pPattern->bbox().left) /
                           pPattern->x_step());
  int min_row = (int)ceil((clip_box_p.bottom - pPattern->bbox().top) /
                          pPattern->y_step());
  int max_row = (int)floor((clip_box_p.top - pPattern->bbox().bottom) /
                           pPattern->y_step());

  // Make sure we can fit the needed width * height into an int.
  if (height > std::numeric_limits<int>::max() / width)
    return;

  if (width > clip_box.Width() || height > clip_box.Height() ||
      width * height > clip_box.Width() * clip_box.Height()) {
    std::unique_ptr<CPDF_GraphicStates> pStates;
    if (!pPattern->colored())
      pStates = CloneObjStates(pPageObj, bStroke);

    auto& pFormDict = pPattern->form()->m_pFormDict;
    CPDF_Dictionary* pFormResource =
        pFormDict ? pFormDict->GetDictFor("Resources") : nullptr;
    for (int col = min_col; col <= max_col; col++) 
    {
      for (int row = min_row; row <= max_row; row++) 
      {
        CFX_PointF original = mtPattern2Device.Transform(
            CFX_PointF(col * pPattern->x_step(), row * pPattern->y_step()));
        CFX_Matrix matrix = *pObj2Device;
        matrix.Translate(original.x - mtPattern2Device.e,
                         original.y - mtPattern2Device.f);
        CFX_RenderDevice::StateRestorer restorer2(m_pDevice);
        OdRenderStatus status(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
        status.Initialize(m_pContext.Get(), m_pDevice, nullptr, nullptr, this,
                          pStates.get(), &m_Options,
                          pPattern->form()->m_iTransparency, m_bDropObjects,
                          pFormResource);
        status.RenderObjectList(pPattern->form(), &matrix);
      }
    }
    return;
  }
  if (bAligned) 
  {
    int orig_x = FXSYS_round(mtPattern2Device.e);
    int orig_y = FXSYS_round(mtPattern2Device.f);
    min_col = (clip_box.left - orig_x) / width;
    if (clip_box.left < orig_x)
      min_col--;

    max_col = (clip_box.right - orig_x) / width;
    if (clip_box.right <= orig_x)
      max_col--;

    min_row = (clip_box.top - orig_y) / height;
    if (clip_box.top < orig_y)
      min_row--;

    max_row = (clip_box.bottom - orig_y) / height;
    if (clip_box.bottom <= orig_y)
      max_row--;
  }
  float left_offset = cell_bbox.left - mtPattern2Device.e;
  float top_offset = cell_bbox.bottom - mtPattern2Device.f;
  RetainPtr<CFX_DIBitmap> pPatternBitmap;
  if (width * height < 16) 
  {
    RetainPtr<CFX_DIBitmap> pEnlargedBitmap =
        ODA::DrawPatternBitmap(m_pContext->GetDocument(), m_pContext->GetPageCache(),
                          pPattern, pObj2Device, 8, 8, m_Options.GetFlags());
    pPatternBitmap = pEnlargedBitmap->StretchTo(width, height, 0, nullptr);
  } else {
    pPatternBitmap = ODA::DrawPatternBitmap(
        m_pContext->GetDocument(), m_pContext->GetPageCache(), pPattern,
        pObj2Device, width, height, m_Options.GetFlags());
  }
  if (!pPatternBitmap)
    return;

  if (m_Options.ColorModeIs(CPDF_RenderOptions::kGray))
    pPatternBitmap->ConvertColorScale(0, 0xffffff);

  FX_ARGB fill_argb = GetFillArgb(pPageObj);
  int clip_width = clip_box.right - clip_box.left;
  int clip_height = clip_box.bottom - clip_box.top;
  auto pScreen = pdfium::MakeRetain<CFX_DIBitmap>();
  if (!pScreen->Create(clip_width, clip_height, FXDIB_Argb))
    return;

  pScreen->Clear(0);
  uint32_t* src_buf = (uint32_t*)pPatternBitmap->GetBuffer();
  for (int col = min_col; col <= max_col; col++) 
  {
    for (int row = min_row; row <= max_row; row++) 
    {
      int start_x, start_y;
      if (bAligned) {
        start_x = FXSYS_round(mtPattern2Device.e) + col * width - clip_box.left;
        start_y = FXSYS_round(mtPattern2Device.f) + row * height - clip_box.top;
      } 
      else
      {
        CFX_PointF original = mtPattern2Device.Transform(
            CFX_PointF(col * pPattern->x_step(), row * pPattern->y_step()));

        pdfium::base::CheckedNumeric<int> safeStartX =
            FXSYS_round(original.x + left_offset);
        pdfium::base::CheckedNumeric<int> safeStartY =
            FXSYS_round(original.y + top_offset);

        safeStartX -= clip_box.left;
        safeStartY -= clip_box.top;
        if (!safeStartX.IsValid() || !safeStartY.IsValid())
          return;

        start_x = safeStartX.ValueOrDie();
        start_y = safeStartY.ValueOrDie();
      }
      if (width == 1 && height == 1) 
      {
        if (start_x < 0 || start_x >= clip_box.Width() || start_y < 0 ||
            start_y >= clip_box.Height())
        {
          continue;
        }
        uint32_t* dest_buf =
            (uint32_t*)(pScreen->GetBuffer() + pScreen->GetPitch() * start_y +
                        start_x * 4);
        if (pPattern->colored())
          *dest_buf = *src_buf;
        else
          *dest_buf = (*(uint8_t*)src_buf << 24) | (fill_argb & 0xffffff);
      } 
      else 
      {
        if (pPattern->colored())
        {
          pScreen->CompositeBitmap(start_x, start_y, width, height,
                                   pPatternBitmap, 0, 0);
        }
        else 
        {
          pScreen->CompositeMask(start_x, start_y, width, height,
                                 pPatternBitmap, fill_argb, 0, 0);
        }
      }
    }
  }
  CompositeDIBitmap(pScreen, clip_box.left, clip_box.top, 0, 255,
                    FXDIB_BLEND_NORMAL, false);
}

bool OdRenderStatus::ProcessImage(CPDF_ImageObject* pImageObj, const CFX_Matrix* pObj2Device) 
{
  OdImageRenderer render(m_CurrentLayerName, m_IsObjectVisible);
  if (render.Start(this, pImageObj, pObj2Device, m_bStdCS, m_curBlend))
    render.Continue(nullptr);
  return render.GetResult();
}

RetainPtr<CFX_DIBitmap> OdRenderStatus::LoadSMask(CPDF_Dictionary* pSMaskDict, FX_RECT* pClipRect, const CFX_Matrix* pMatrix) 
{
  if (!pSMaskDict)
    return nullptr;

  CPDF_Stream* pGroup = pSMaskDict->GetStreamFor("G");
  if (!pGroup)
    return nullptr;

  std::unique_ptr<CPDF_Function> pFunc;
  CPDF_Object* pFuncObj = pSMaskDict->GetDirectObjectFor("TR");
  if (pFuncObj && (pFuncObj->IsDictionary() || pFuncObj->IsStream()))
    pFunc = CPDF_Function::Load(pFuncObj);

  CFX_Matrix matrix = *pMatrix;
  matrix.Translate(-pClipRect->left, -pClipRect->top);

  CPDF_Form form(m_pContext->GetDocument(), m_pContext->GetPageResources(),
                 pGroup);
  form.ParseContent();

  CFX_DefaultRenderDevice bitmap_device;
  bool bLuminosity = pSMaskDict->GetStringFor("S") != "Alpha";
  int width = pClipRect->right - pClipRect->left;
  int height = pClipRect->bottom - pClipRect->top;
  FXDIB_Format format;
#if _FX_PLATFORM_ == _FX_PLATFORM_APPLE_ || defined _SKIA_SUPPORT_ || \
    defined _SKIA_SUPPORT_PATHS_
  format = bLuminosity ? FXDIB_Rgb32 : FXDIB_8bppMask;
#else
  format = bLuminosity ? FXDIB_Rgb : FXDIB_8bppMask;
#endif
  if (!bitmap_device.Create(width, height, format, nullptr))
    return nullptr;

  CFX_DIBitmap& bitmap = *bitmap_device.GetBitmap();
  int color_space_family = 0;
  if (bLuminosity)
  {
    CPDF_Array* pBC = pSMaskDict->GetArrayFor("BC");
    FX_ARGB back_color = 0xff000000;
    if (pBC)
    {
      CPDF_Object* pCSObj = nullptr;
      CPDF_Dictionary* pDict = pGroup->GetDict();
      if (pDict && pDict->GetDictFor("Group"))
      {
        pCSObj = pDict->GetDictFor("Group")->GetDirectObjectFor("CS");
      }
      const CPDF_ColorSpace* pCS =
          m_pContext->GetDocument()->LoadColorSpace(pCSObj);
      if (pCS) 
      {
        // Store Color Space Family to use in CPDF_RenderStatus::Initialize.
        color_space_family = pCS->GetFamily();

        float R, G, B;
        uint32_t comps = 8;
        if (pCS->CountComponents() > comps) 
        {
          comps = pCS->CountComponents();
        }
        CFX_FixedBufGrow<float, 8> float_array(comps);
        float* pFloats = float_array;
        FX_SAFE_UINT32 num_floats = comps;
        num_floats *= sizeof(float);
        if (!num_floats.IsValid())
        {
          return nullptr;
        }
        memset(pFloats, 0, num_floats.ValueOrDie());
        size_t count = pBC->GetCount() > 8 ? 8 : pBC->GetCount();
        for (size_t i = 0; i < count; i++) 
        {
          pFloats[i] = pBC->GetNumberAt(i);
        }
        pCS->GetRGB(pFloats, &R, &G, &B);
        back_color = 0xff000000 | ((int32_t)(R * 255) << 16) |
                     ((int32_t)(G * 255) << 8) | (int32_t)(B * 255);
        m_pContext->GetDocument()->GetPageData()->ReleaseColorSpace(pCSObj);
      }
    }
    bitmap.Clear(back_color);
  } 
  else 
  {
    bitmap.Clear(0);
  }
  CPDF_Dictionary* pFormResource = nullptr;
  if (form.m_pFormDict) 
  {
    pFormResource = form.m_pFormDict->GetDictFor("Resources");
  }
  CPDF_RenderOptions options;
  options.SetColorMode(bLuminosity ? CPDF_RenderOptions::kNormal
                                   : CPDF_RenderOptions::kAlpha);
  OdRenderStatus status(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
  status.Initialize(m_pContext.Get(), &bitmap_device, nullptr, nullptr, nullptr,
                    nullptr, &options, 0, m_bDropObjects, pFormResource, true,
                    nullptr, 0, color_space_family, bLuminosity);
  status.RenderObjectList(&form, &matrix);

  auto pMask = pdfium::MakeRetain<CFX_DIBitmap>();
  if (!pMask->Create(width, height, FXDIB_8bppMask))
    return nullptr;

  uint8_t* dest_buf = pMask->GetBuffer();
  int dest_pitch = pMask->GetPitch();
  uint8_t* src_buf = bitmap.GetBuffer();
  int src_pitch = bitmap.GetPitch();
  std::vector<uint8_t> transfers(256);
  if (pFunc) 
  {
    CFX_FixedBufGrow<float, 16> results(pFunc->CountOutputs());
    for (int i = 0; i < 256; i++)
    {
      float input = (float)i / 255.0f;
      int nresult;
      pFunc->Call(&input, 1, results, &nresult);
      transfers[i] = FXSYS_round(results[0] * 255);
    }
  }
  else 
  {
    for (int i = 0; i < 256; i++) 
    {
      transfers[i] = i;
    }
  }
  if (bLuminosity) 
  {
    int Bpp = bitmap.GetBPP() / 8;
    for (int row = 0; row < height; row++) 
    {
      uint8_t* dest_pos = dest_buf + row * dest_pitch;
      uint8_t* src_pos = src_buf + row * src_pitch;
      for (int col = 0; col < width; col++) 
      {
        *dest_pos++ = transfers[FXRGB2GRAY(src_pos[2], src_pos[1], *src_pos)];
        src_pos += Bpp;
      }
    }
  } 
  else 
    if (pFunc) 
    {
    int size = dest_pitch * height;
    for (int i = 0; i < size; i++) 
    {
      dest_buf[i] = transfers[src_buf[i]];
    }
  } 
  else 
  {
    memcpy(dest_buf, src_buf, dest_pitch * height);
  }
  return pMask;
}

bool SetDIBitsWithBlend(const RetainPtr<CFX_DIBSource>& pBitmap, int left, int top, int blend_mode, OdDeviceDriver* driver, FX_RECT& clip_rect)
{
  ASSERT(!pBitmap->IsAlphaMask());
  CFX_Matrix ctm = driver->GetCTM();
  float fScaleX = fabs(ctm.a);
  float fScaleY = fabs(ctm.d);
  FX_RECT dest_rect(left, top,
    FXSYS_round(left + pBitmap->GetWidth() / fScaleX),
    FXSYS_round(top + pBitmap->GetHeight() / fScaleY));
  dest_rect.Intersect(clip_rect);
  if (dest_rect.IsEmpty())
    return true;

  FX_RECT src_rect(dest_rect.left - left, dest_rect.top - top,
    dest_rect.left - left + dest_rect.Width(),
    dest_rect.top - top + dest_rect.Height());
  src_rect.left = FXSYS_round(src_rect.left * fScaleX);
  src_rect.top = FXSYS_round(src_rect.top * fScaleY);
  src_rect.right = FXSYS_round(src_rect.right * fScaleX);
  src_rect.bottom = FXSYS_round(src_rect.bottom * fScaleY);

  return driver->DrawShadingAsBitmap(pBitmap, 0, &src_rect, dest_rect.left, dest_rect.top, blend_mode);
}

void OdRenderStatus::RenderObjectList(
  const CPDF_PageObjectHolder* pObjectHolder,
  const CFX_Matrix* pObj2Device) {
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
  CFX_FloatRect clip_rect = pObj2Device->GetInverse().TransformRect(
    CFX_FloatRect(m_pDevice->GetClipBox()));
  for (const auto& pCurObj : *pObjectHolder->GetPageObjectList()) {
    if (pCurObj.get() == m_pStopObj) {
      m_bStopped = true;
      return;
    }
    if (!pCurObj)
      continue;

    if (pCurObj->m_Left > clip_rect.right ||
      pCurObj->m_Right < clip_rect.left ||
      pCurObj->m_Bottom > clip_rect.top ||
      pCurObj->m_Top < clip_rect.bottom) {
      continue;
    }

    if (0 != pObjectHolder->m_iTransparency && CPDF_PageObject::SHADING == pCurObj->GetType())
    {
      pCurObj->m_GeneralState.SetFillAlpha((float)0.6);
    }

    RenderSingleObject(pCurObj.get(), pObj2Device);
    if (m_bStopped)
      return;
  }
#if defined _SKIA_SUPPORT_
  DebugVerifyDeviceIsPreMultiplied();
#endif
}

void OdRenderStatus::DrawShading(CPDF_ShadingPattern* pPattern, CFX_Matrix* pMatrix, FX_RECT& clip_rect, int alpha, bool bAlphaMode)
{
  const auto& funcs = pPattern->GetFuncs();
  CPDF_Dictionary* pDict = pPattern->GetShadingObject()->GetDict();
  CPDF_ColorSpace* pColorSpace = pPattern->GetCS();
  if (!pColorSpace)
    return;

  FX_ARGB background = 0;
  if (!pPattern->IsShadingObject() && pDict->KeyExist("Background"))
  {
    CPDF_Array* pBackColor = pDict->GetArrayFor("Background");
    if (pBackColor &&
      pBackColor->GetCount() >= pColorSpace->CountComponents()) 
    {
      CFX_FixedBufGrow<float, 16> comps(pColorSpace->CountComponents());
      for (uint32_t i = 0; i < pColorSpace->CountComponents(); i++)
        comps[i] = pBackColor->GetNumberAt(i);
      float R = 0.0f;
      float G = 0.0f;
      float B = 0.0f;
      pColorSpace->GetRGB(comps, &R, &G, &B);
      background = ArgbEncode(255, (int32_t)(R * 255), (int32_t)(G * 255),
        (int32_t)(B * 255));
    }
  }
  if (pDict->KeyExist("BBox"))
  {
    clip_rect.Intersect(
      pMatrix->TransformRect(pDict->GetRectFor("BBox")).GetOuterRect());
  }

  CPDF_DeviceBuffer buffer;
  buffer.Initialize(m_pContext.Get(), m_pDevice, &clip_rect, m_pCurObj, 150);
  CFX_Matrix FinalMatrix = *pMatrix;
  FinalMatrix.Concat(*buffer.GetMatrix());
  RetainPtr<CFX_DIBitmap> pBitmap = buffer.GetBitmap();
  if (!pBitmap->GetBuffer())
    return;

  pBitmap->Clear(background);
  switch (pPattern->GetShadingType())
  {
    case kInvalidShading:
    case kMaxShading:
      return;
    case kFunctionBasedShading:
      ODA::DrawFuncShading(pBitmap, &FinalMatrix, pDict, funcs, pColorSpace, alpha);
      break;
    case kAxialShading:
      ODA::DrawAxialShading(pBitmap, &FinalMatrix, pDict, funcs, pColorSpace, alpha);
      break;
    case kRadialShading:
      ODA::DrawRadialShading(pBitmap, &FinalMatrix, pDict, funcs, pColorSpace,
        alpha);
      break;
    case kFreeFormGouraudTriangleMeshShading: 
    {
      // The shading object can be a stream or a dictionary. We do not handle
      // the case of dictionary at the moment.
      if (CPDF_Stream* pStream = ToStream(pPattern->GetShadingObject())) 
      {
        ODA::DrawFreeGouraudShading(pBitmap, &FinalMatrix, pStream, funcs,
          pColorSpace, alpha);
      }
    } 
    break;
    case kLatticeFormGouraudTriangleMeshShading: 
    {
      // The shading object can be a stream or a dictionary. We do not handle
      // the case of dictionary at the moment.
      if (CPDF_Stream* pStream = ToStream(pPattern->GetShadingObject())) 
      {
        ODA::DrawLatticeGouraudShading(pBitmap, &FinalMatrix, pStream, funcs,
          pColorSpace, alpha);
      }
    } 
    break;
    case kCoonsPatchMeshShading:
    case kTensorProductPatchMeshShading: 
    {
      // The shading object can be a stream or a dictionary. We do not handle
      // the case of dictionary at the moment.
      if (CPDF_Stream* pStream = ToStream(pPattern->GetShadingObject())) 
      {
        ODA::DrawCoonPatchMeshes(pPattern->GetShadingType(), pBitmap, &FinalMatrix,
          pStream, funcs, pColorSpace, m_Options.GetFlags(), alpha);
      }
    } 
    break;
  }

  OdDeviceDriver* driver = dynamic_cast<OdDeviceDriver*>(m_pDevice->GetDeviceDriver());
  if(nullptr != driver)
    SetDIBitsWithBlend(pBitmap, clip_rect.left, clip_rect.top, FXDIB_BLEND_NORMAL, driver, clip_rect);

}
