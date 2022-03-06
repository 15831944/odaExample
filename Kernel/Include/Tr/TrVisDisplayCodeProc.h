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
// GLES2 device special display codes processing helpers

#ifndef ODTRVISDISPLAYCODEPROC
#define ODTRVISDISPLAYCODEPROC

#include "TD_PackPush.h"

#include "TrVisRendition.h"

/** \details
    <group ExRender_Classes>
*/
class OdTrVisDisplayCodeKeeper
{
  public:
    template <typename TArray>
    static void pushZero(TArray &arry)
    {
      arry.push_back(OdTrVisRendition::kDisplayCodeZero);
    }
    // Highlighting
    template <typename TArray>
    static void pushHighlight(TArray &arry)
    {
      arry.push_back(OdTrVisRendition::kDisplayCodeHighlight);
    }
    template <typename TArray>
    static void pushUnhighlight(TArray &arry)
    {
      arry.push_back(OdTrVisRendition::kDisplayCodeUnhighlight);
    }
    template <typename TArray>
    static void pushHighlight(TArray &arry, bool bHighlight)
    {
      arry.push_back((bHighlight) ? OdTrVisRendition::kDisplayCodeHighlight : OdTrVisRendition::kDisplayCodeUnhighlight);
    }
    // Transform
    template <typename TArray>
    static void pushPushMatrix(TArray &arry, const OdGeMatrix3d &mtx)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodePushMatrix);
      const ValType *pMtxRepresentation = reinterpret_cast<const ValType*>(mtx.entry);
      arry.insert(arry.end(), pMtxRepresentation, pMtxRepresentation + (sizeof(OdGeMatrix3d) / sizeof(ValType)));
    }
    template <typename TArray>
    static void pushPopMatrix(TArray &arry)
    {
      arry.push_back(OdTrVisRendition::kDisplayCodePopMatrix);
    }
    // Fading
    template <typename TArray>
    static void pushFade(TArray &arry, long nFadeSlot)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeFade);
      arry.push_back((ValType)(OdIntPtr)nFadeSlot);
    }
    template <typename TArray>
    static void pushUnfade(TArray &arry, long nFadeSlot)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeUnfade);
      arry.push_back((ValType)(OdIntPtr)nFadeSlot);
    }
    template <typename TArray>
    static void pushFade(TArray &arry, long nFadeSlot, bool bFade)
    {
      if (bFade) pushFade<TArray>(arry, nFadeSlot);
      else pushUnfade<TArray>(arry, nFadeSlot);
    }
    // Markers
    template <typename TArray>
    static void pushMarkers(TArray &arry, OdTrVisStateBranchPtr pBranch, OdTrVisStateBranchType sbType)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeHlMarkers + sbType);
      arry.push_back((ValType)(OdIntPtr)pBranch);
    }
    template <typename TArray>
    static void pushHlMarkers(TArray &arry, OdTrVisStateBranchPtr pHlBranch)
    {
      pushMarkers<TArray>(arry, pHlBranch, kTrVisHighlightingBranch);
    }
    /** \details
      Keeps visibilities markers
    */
    template <typename TArray>
    static void pushVsMarkers( TArray &arry, OdTrVisStateBranchPtr pVsBranch )
    {
      pushMarkers<TArray>(arry, pVsBranch, kTrVisVisibilityBranch);
    }
    // Drawing order
    template <typename TArray>
    static void pushDrawOrder(TArray &arry, double drawOrder)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeDrawOrder);
      arry.push_back(*reinterpret_cast<ValType*>(&drawOrder));
    }
    template <typename TArray>
    static void pushMultiOrder(TArray &arry)
    {
      pushDrawOrder<TArray>(arry, OdTrVisRendition::kDisplayMultiDrawOrderMarker);
    }
    // Drawing order interval
    template <typename TArray>
    static void pushDepthIval(TArray &arry, const OdTrVisIvald &ival)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeDepthIval);
      arry.push_back(*reinterpret_cast<const ValType*>(&ival.m_minBound));
      arry.push_back(*reinterpret_cast<const ValType*>(&ival.m_maxBound));
    }
    // Exploded unions
    template <typename TArray>
    static void pushExploded(TArray &arry)
    {
      arry.push_back(OdTrVisRendition::kDisplayCodeExploded);
    }
    template <typename TArray>
    static void pushNonExploded(TArray &arry)
    {
      arry.push_back(OdTrVisRendition::kDisplayCodeNonExploded);
    }
    template <typename TArray>
    static void pushExploded(TArray &arry, bool bExploded)
    {
      arry.push_back((bExploded) ? OdTrVisRendition::kDisplayCodeExploded : OdTrVisRendition::kDisplayCodeNonExploded);
    }
    // Selection style
    template <typename TArray>
    static void pushSelStyle(TArray& arry, OdUInt32 nSelStyle)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeSelStyle);
      arry.push_back((ValType)(OdIntPtr)nSelStyle);
    }
    /** \details
      Sets id of current rendering object
      \param arry [in] Display list
      \param pID [in] Id to add in display list
    */
    template <typename TArray>
    static void pushSelectionID(TArray &arry, const void *pID)
    { typedef OD_TYPENAME TArray::value_type ValType;
      arry.push_back(OdTrVisRendition::kDisplayCodeSelectionID);
      arry.push_back((ValType)(OdIntPtr)pID);
    }
};

/** \details
    <group ExRender_Classes>
*/
class OdTrVisFastComparator
{
  public:
    template <typename TObj>
    static bool isEqual(const TObj &obj1, const TObj &obj2)
    {
      return !::memcmp(&obj1, &obj2, sizeof(TObj));
    }
    static bool isIdentity(const OdGeMatrix3d &mtx)
    {
      return isEqual(mtx, OdGeMatrix3d::kIdentity);
    }
};

/** \details
    <group ExRender_Classes>
*/
class OdTrVisDisplayListIterator
{
  OdTrVisDisplayId *m_pList;
  OdUInt32 m_nListData, m_nCaret;
  public:
    OdTrVisDisplayListIterator(const OdTrVisDisplayId *pList, OdUInt32 nData)
      : m_pList(const_cast<OdTrVisDisplayId*>(pList)), m_nListData(nData), m_nCaret(0)
    {
    }
    bool isEOF() const { return m_nCaret >= m_nListData; }
    bool isCode() const { return m_pList[m_nCaret] < OdTrVisRendition::kDisplayCodeRange; }
    OdTrVisRendition::DisplayIdCodes code() const { return (OdTrVisRendition::DisplayIdCodes)m_pList[m_nCaret]; }
    static OdUInt32 skipCodeSize(OdTrVisRendition::DisplayIdCodes dispCode)
    { OdUInt32 nSteps = 1;
      switch (dispCode) { case OdTrVisRendition::kDisplayCodePushMatrix: nSteps += sizeof(OdGeMatrix3d) / sizeof(double); break;
                          case OdTrVisRendition::kDisplayCodeDepthIval:  nSteps += 2; break;
                          case OdTrVisRendition::kDisplayCodeFade:      case OdTrVisRendition::kDisplayCodeUnfade:
                          case OdTrVisRendition::kDisplayCodeHlMarkers: case OdTrVisRendition::kDisplayCodeVsMarkers:
                          case OdTrVisRendition::kDisplayCodeSelStyle:  case OdTrVisRendition::kDisplayCodeSelectionID:
                          case OdTrVisRendition::kDisplayCodeDrawOrder : nSteps += 1; break; default: break; }
      return nSteps; }
    void skipCode() { m_nCaret += skipCodeSize(code()); }
    OdTrVisDisplayId &cur() { return m_pList[m_nCaret]; }
    const OdTrVisDisplayId &cur() const { return m_pList[m_nCaret]; }
    OdTrVisDisplayId &next(OdUInt32 n = 1) { return m_pList[m_nCaret + n]; }
    const OdTrVisDisplayId &next(OdUInt32 n = 1) const { return m_pList[m_nCaret + n]; }
    bool step() { if (isCode()) skipCode(); else m_nCaret++; return isEOF(); }
    // Access extensions
    const double *codeAsDoublePtr(OdUInt32 n = 1) const { return reinterpret_cast<const double*>(m_pList + (m_nCaret + n)); }
    const OdGeMatrix3d *codeAsMatrixPtr(OdUInt32 n = 1) const { return reinterpret_cast<const OdGeMatrix3d*>(m_pList + (m_nCaret + n)); }
    const OdTrVisId *codeAsIdPtr(OdUInt32 n = 1) const { return reinterpret_cast<const OdTrVisId*>(m_pList + (m_nCaret + n)); }
    const void *codeAsPtr(OdUInt32 n = 1) const { return OdTrVisIdToPtr(const void, m_pList[m_nCaret + n]); }
    // Debug extensions
    static void dumpDisplayList(const OdTrVisDisplayId *pList, OdUInt32 nData, void (*pDumpFunc)(const OdString &));
    //void traceDumpFunc(const OdString &str) { ODA_TRACE(str.c_str()); } // Example dump function
};

inline void OdTrVisDisplayListIterator::dumpDisplayList(const OdTrVisDisplayId *pList, OdUInt32 nData, void (*pDumpFunc)(const OdString &))
{ OdTrVisDisplayListIterator it(pList, nData);
  while (!it.isEOF())
  {
    if (it.isCode())
    {
      switch (it.code())
      {
        case OdTrVisRendition::kDisplayCodeHighlight:
          pDumpFunc(L"Code Highlight: 1\n");
        break;
        case OdTrVisRendition::kDisplayCodeUnhighlight:
          pDumpFunc(L"Code UnHighlight: 0\n");
        break;
        case OdTrVisRendition::kDisplayCodePushMatrix:
          pDumpFunc(OdString().format(L"Code PushMatrix: { %f, %f, %f, %f }, { %f, %f, %f, %f }, { %f, %f, %f, %f }, { %f, %f, %f, %f }\n",
                                      it.codeAsMatrixPtr()->entry[0][0], it.codeAsMatrixPtr()->entry[0][1], it.codeAsMatrixPtr()->entry[0][2], it.codeAsMatrixPtr()->entry[0][3],
                                      it.codeAsMatrixPtr()->entry[1][0], it.codeAsMatrixPtr()->entry[1][1], it.codeAsMatrixPtr()->entry[1][2], it.codeAsMatrixPtr()->entry[1][3],
                                      it.codeAsMatrixPtr()->entry[2][0], it.codeAsMatrixPtr()->entry[2][1], it.codeAsMatrixPtr()->entry[2][2], it.codeAsMatrixPtr()->entry[2][3],
                                      it.codeAsMatrixPtr()->entry[3][0], it.codeAsMatrixPtr()->entry[3][1], it.codeAsMatrixPtr()->entry[3][2], it.codeAsMatrixPtr()->entry[3][3]));
        break;
        case OdTrVisRendition::kDisplayCodePopMatrix:
          pDumpFunc(L"Code PopMatrix\n");
        break;
        case OdTrVisRendition::kDisplayCodeFade:
          pDumpFunc(OdString().format(L"Code Fade: %u\n", (unsigned)it.next()));
        break;
        case OdTrVisRendition::kDisplayCodeUnfade:
          pDumpFunc(OdString().format(L"Code UnFade: %u\n", (unsigned)it.next()));
        break;
        case OdTrVisRendition::kDisplayCodeHlMarkers:
          pDumpFunc(OdString().format(L"Code HlMarker: %" PRIu64W L"\n", *it.codeAsIdPtr()));
        break;
        case OdTrVisRendition::kDisplayCodeVsMarkers:
          pDumpFunc(OdString().format(L"Code VsMarker: %" PRIu64W L"\n", *it.codeAsIdPtr()));
        break;
        case OdTrVisRendition::kDisplayCodeDrawOrder:
          pDumpFunc(OdString().format(L"Code DrawOrder: %f\n", *it.codeAsDoublePtr()));
        break;
        case OdTrVisRendition::kDisplayCodeDepthIval:
          pDumpFunc(OdString().format(L"Code Depth: { %f, %f }\n", it.codeAsDoublePtr()[0], it.codeAsDoublePtr()[1]));
        break;
        case OdTrVisRendition::kDisplayCodeExploded:
          pDumpFunc(L"Code Exploded: 1\n");
        break;
        case OdTrVisRendition::kDisplayCodeNonExploded:
          pDumpFunc(L"Code NonExploded: 0\n");
        break;
        case OdTrVisRendition::kDisplayCodeSelStyle:
          pDumpFunc(OdString().format(L"Code SelStyle: %u\n", (unsigned)it.next()));
        break;
      }
    }
    else
    {
      pDumpFunc(OdString().format(L"Metafile: %" PRIu64W L"\n", it.cur()));
    }
    it.step();
  }
}

#include "TD_PackPop.h"

#endif // ODTRVISDISPLAYCODEPROC
