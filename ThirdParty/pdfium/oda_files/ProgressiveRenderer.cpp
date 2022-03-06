/////////////////////////////////////////////////////////////////////////////// 
// Created by Open Design Alliance 
///////////////////////////////////////////////////////////////////////////////

#include "ProgressiveRenderer.h"

#include "core/fpdfapi/page/cpdf_image.h"
#include "core/fpdfapi/page/cpdf_imageobject.h"
#include "core/fpdfapi/page/cpdf_pageobject.h"
#include "core/fpdfapi/page/cpdf_pageobjectholder.h"
#include "core/fpdfapi/render/cpdf_pagerendercache.h"
#include "core/fpdfapi/render/cpdf_renderoptions.h"
#include "core/fpdfapi/render/cpdf_renderstatus.h"
#include "core/fxcrt/ifx_pauseindicator.h"
#include "core/fxge/cfx_renderdevice.h"
#include "third_party/base/ptr_util.h"

#include "RenderStatus.h"

OdProgressiveRenderer::OdProgressiveRenderer(CPDF_RenderContext* pContext, CFX_RenderDevice* pDevice,
    const CPDF_RenderOptions* pOptions, std::wstring& current_layer_name, bool& is_object_visible, long options)
  :CPDF_ProgressiveRenderer(pContext, pDevice, pOptions)
  ,m_CurrentLayerName(current_layer_name)
  ,m_IsObjectVisible(is_object_visible)
  , m_PdfImportOptions(options)
{

}

OdProgressiveRenderer::~OdProgressiveRenderer() 
{

}

void OdProgressiveRenderer::Continue(IFX_PauseIndicator* pPause)
{
  while (m_Status == ToBeContinued) 
  {
    if (!m_pCurrentLayer) {
      if (m_LayerIndex >= m_pContext->CountLayers()) 
      {
        m_Status = Done;
        return;
      }
      m_pCurrentLayer = m_pContext->GetLayer(m_LayerIndex);
      m_LastObjectRendered =
          m_pCurrentLayer->m_pObjectHolder->GetPageObjectList()->end();
      m_pRenderStatus = pdfium::MakeUnique<OdRenderStatus>(m_CurrentLayerName, m_IsObjectVisible, m_PdfImportOptions);
      m_pRenderStatus->Initialize(
          m_pContext.Get(), m_pDevice.Get(), nullptr, nullptr, nullptr, nullptr,
          m_pOptions, m_pCurrentLayer->m_pObjectHolder->m_iTransparency, false,
          nullptr);
      m_pDevice->SaveState();
      m_ClipRect = m_pCurrentLayer->m_Matrix.GetInverse().TransformRect(CFX_FloatRect(m_pDevice->GetClipBox()));
    }
    CPDF_PageObjectList::iterator iter;
    CPDF_PageObjectList::iterator iterEnd =
        m_pCurrentLayer->m_pObjectHolder->GetPageObjectList()->end();
    if (m_LastObjectRendered != iterEnd) 
    {
      iter = m_LastObjectRendered;
      ++iter;
    } 
    else 
    {
      iter = m_pCurrentLayer->m_pObjectHolder->GetPageObjectList()->begin();
    }
    int nObjsToGo = kStepLimit;
    bool is_mask = false;
    while (iter != iterEnd)
    {
      CPDF_PageObject* pCurObj = iter->get();
      if (pCurObj && pCurObj->m_Left <= m_ClipRect.right &&
          pCurObj->m_Right >= m_ClipRect.left &&
          pCurObj->m_Bottom <= m_ClipRect.top &&
          pCurObj->m_Top >= m_ClipRect.bottom) 
      {
        if (m_pOptions->HasFlag(RENDER_BREAKFORMASKS) && pCurObj->IsImage() &&
            pCurObj->AsImage()->GetImage()->IsMask()) {
          if (m_pDevice->GetDeviceCaps(FXDC_DEVICE_CLASS) == FXDC_PRINTER)
          {
            m_LastObjectRendered = iter;
            m_pRenderStatus->ProcessClipPath(pCurObj->m_ClipPath,
                                             &m_pCurrentLayer->m_Matrix);
            return;
          }
          is_mask = true;
        }
        if (m_pRenderStatus->ContinueSingleObject(
                pCurObj, &m_pCurrentLayer->m_Matrix, pPause)) 
        {
          return;
        }
        if (pCurObj->IsImage() && m_pRenderStatus->GetRenderOptions()->HasFlag(
                                      RENDER_LIMITEDIMAGECACHE)) 
        {
          m_pContext->GetPageCache()->CacheOptimization(
              m_pRenderStatus->GetRenderOptions()->GetCacheSizeLimit());
        }
        if (pCurObj->IsForm() || pCurObj->IsShading())
          nObjsToGo = 0;
        else
          --nObjsToGo;
      }
      m_LastObjectRendered = iter;
      if (nObjsToGo == 0) 
      {
        if (pPause && pPause->NeedToPauseNow())
          return;
        nObjsToGo = kStepLimit;
      }
      ++iter;
      if (is_mask && iter != iterEnd)
        return;
    }
    if (m_pCurrentLayer->m_pObjectHolder->IsParsed()) 
    {
      m_pRenderStatus.reset();
      m_pDevice->RestoreState(false);
      m_pCurrentLayer = nullptr;
      m_LayerIndex++;
      if (is_mask || (pPause && pPause->NeedToPauseNow())) 
      {
        return;
      }
    }
    else if (is_mask)
    {
      return;
    } 
    else
    {
      m_pCurrentLayer->m_pObjectHolder->ContinueParse(pPause);
      if (!m_pCurrentLayer->m_pObjectHolder->IsParsed())
        return;
    }
  }
}
