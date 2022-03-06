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

#ifndef EX_H_COLORCONVERTERCALLBACK
#define EX_H_COLORCONVERTERCALLBACK

#include "TD_PackPush.h"

#include "RxObject.h"

/** <group ExRender_Classes>
  \details
  This is the interface class for objects of color converter types.

  \sa
  <exref target="https://www.opendesign.com/blog/2017/october/frequently-asked-how-can-i-modify-drawn-colors-my-application-during-display">Frequently Asked: How can I modify drawn colors from my application during display?</exref>
*/
class OdColorConverterCallback : public OdRxObject
{
  public:
    /** \details
      This method is intended for color conversion.

      \param originalColor [in] Original color.

      \returns
      Converted color.
    */
    virtual ODCOLORREF convert(ODCOLORREF originalColor) = 0;

    /** \details
      This method determines whether the convert() method should be called to
      convert the background color.

      \returns
      True if conversion for the background color is required; false otherwise.
    */
    virtual bool convertBackgroundColors() const { return true; }
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdColorConverterCallback object pointers.
*/
typedef OdSmartPtr<OdColorConverterCallback> OdColorConverterCallbackPtr;

/** <group ExRender_Classes>
  \details
  Helper class which is provide converted colors caching ability for OdColorConverterCallback.
*/
class OdColorConverterCallbackCaching
{
  protected:
    // Hardcoded number of cache entries. 4 looks optimal for sequential colors.
    // From other side it willn't seriously reduce performance for random colors.
    enum { kNumCacheEntries = 4 };
    mutable struct ColorEntry
    {
      ODCOLORREF m_originalColor;
      ODCOLORREF m_convertedColor;
      ColorEntry *m_pNext, *m_pPrev;
    } m_colorEntries[kNumCacheEntries];
    OdColorConverterCallback *m_pCallback;
    mutable ColorEntry *m_pCache, *m_pCacheEnd;
    mutable OdUInt32 m_nInvokedEntries;
  protected:
    void moveEntryToStart(ColorEntry *pCe) const
    {
      pCe->m_pPrev->m_pNext = pCe->m_pNext;
      if (pCe->m_pNext)
        pCe->m_pNext->m_pPrev = pCe->m_pPrev;
      else
        m_pCacheEnd = pCe->m_pPrev;
      pCe->m_pPrev = NULL;
      pCe->m_pNext = m_pCache;
      m_pCache->m_pPrev = pCe;
      m_pCache = pCe;
    }
  public:
    /** \details
      Constructs color conversion cache.

      \param pCallback [in]  Optional color conversion callback to be set immediately.
    */
    OdColorConverterCallbackCaching(OdColorConverterCallback *pCallback = NULL)
      : m_pCallback(pCallback), m_pCache(NULL), m_pCacheEnd(NULL), m_nInvokedEntries(0) { }

    /** \details
      Clear previously cached colors.
    */
    void refresh()
    {
      m_pCache = m_pCacheEnd = NULL;
      m_nInvokedEntries = 0;
    }

    /** \details
      Setup color conversion callback.

      \param pCallback [in] Color conversion callback.
    */
    void setColorConverterCallback(OdColorConverterCallback *pCallback)
    { m_pCallback = pCallback; refresh(); }

    /** \details
      Returns active color conversion callback.

      \returns
      Color conversion callback.
    */
    OdColorConverterCallback *colorConverterCallback() const { return m_pCallback; }

    /** \details
      This method is intended for color conversion.

      \param originalColor [in] Original color.

      \returns
      Converted color.
    */
    ODCOLORREF convert(ODCOLORREF originalColor) const
    {
      if (!m_pCallback)
        return originalColor;
      ColorEntry *pCe = m_pCache;
      while (pCe)
      {
        if (pCe->m_originalColor == originalColor)
          break;
        pCe = pCe->m_pNext;
      }
      if (pCe)
      {
        if (pCe->m_pPrev)
          moveEntryToStart(pCe);
      }
      else
      { // Invoke new color entry
        if (m_nInvokedEntries < kNumCacheEntries)
        {
          pCe = m_colorEntries + m_nInvokedEntries++;
          pCe->m_pPrev = NULL;
          pCe->m_pNext = m_pCache;
          if (m_pCache)
            m_pCache->m_pPrev = pCe;
          else
            m_pCacheEnd = pCe;
          m_pCache = pCe;
        }
        else
        {
          pCe = m_pCacheEnd;
          moveEntryToStart(pCe);
        }
        pCe->m_originalColor = originalColor;
        pCe->m_convertedColor = m_pCallback->convert(originalColor);
      }
      return pCe->m_convertedColor;
    }
};

#include "TD_PackPop.h"

#endif // EX_H_COLORCONVERTERCALLBACK
