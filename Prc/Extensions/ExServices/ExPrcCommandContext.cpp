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

#include "PrcCommon.h"
#include "DbBaseDatabase.h"
#include "ExPrcHostAppServices.h"
#include "ExPrcCommandContext.h"
#include "Ge/GeVector3d.h"
#include "Ge/GePlane.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeLineSeg2d.h"
#include "StaticRxObject.h"
#include "Gi/GiDrawableImpl.h"
#include "Gi/GiWorldDraw.h"
#include "Gi/GiViewportDraw.h"
#include "Gi/GiUtils.h"
#include "OdDToStr.h"
#include "Gs/Gs.h"
#include "Ed/EdLispEngine.h"
#include "ExTrackers.h"
#include "DbAux/PrcCommandContext.h"

#include <math.h>

#define DBCC_PAGE_EACH_OBJECT 200

inline OdString next(OdString& list, const OdChar* delim = (const OdChar*)L",")
{
  OdString res = list.spanExcluding(delim);
  if(res.getLength() != list.getLength())
    list = list.mid(res.getLength()+1);
  else
    list.empty();
  return res;
}

OdRxDictionaryPtr ExPrcCommandContext::arbDataDic() const
{
  if(m_pArbDataDic.isNull())
    m_pArbDataDic = odrxCreateRxDictionary();
  return m_pArbDataDic;
}

void ExPrcCommandContext::setParam(OdRxObject* pParamObj)
{
  setArbitraryData(OD_T("ExPrcCommandContext_FuncParamObj"), pParamObj);
}

OdRxObjectPtr ExPrcCommandContext::param()
{
  return arbitraryData(OD_T("ExPrcCommandContext_FuncParamObj"));
}

void ExPrcCommandContext::setResult(OdRxObject* pResultObj)
{
  setArbitraryData(OD_T("ExPrcCommandContext_FuncResultObj"), pResultObj);
}

OdRxObjectPtr ExPrcCommandContext::result()
{
  return arbitraryData(OD_T("ExPrcCommandContext_FuncResultObj"));
}

void ExPrcCommandContext::setArbitraryData(const OdString& szPathName, OdRxObject* pDataObj)
{
  if (pDataObj)
    arbDataDic()->putAt(szPathName, pDataObj);
  else
    arbDataDic()->remove(szPathName);
}


OdRxObjectPtr ExPrcCommandContext::arbitraryData(const OdString& szPathName) const
{
  return arbDataDic()->getAt(szPathName);
}

OdSelectionSetPtr ExPrcCommandContext::previousSelection()
{
  return arbitraryData(OD_T("ExPrcCommandContext_PreviousSSet"));
}

void ExPrcCommandContext::setPreviousSelection(OdSelectionSet* pSSet)
{
  setArbitraryData(OD_T("ExPrcCommandContext_PreviousSSet"), pSSet);
}

OdUnitsFormatter& ExPrcCommandContext::baseFormatter()
{
  OdDbBaseDatabasePEPtr pDbPE = OdDbBaseDatabasePE::cast(baseDatabase());
  if (!pDbPE.get())
    throw OdError(eNoDatabase); 
  return *pDbPE->baseFormatter(baseDatabase());
}

OdPrcCommandContextPtr ExPrcCommandContext::createObject(OdEdBaseIO* pIOStream, OdPrcFile* pDb) 
{
  return ExPrcCommandContext::createObject(pIOStream, static_cast<OdRxObject*>(pDb));
}

OdPrcCommandContextPtr ExPrcCommandContext::createObject(OdEdBaseIO* pIOStream, OdRxObject* pRxDb)
{
  OdPrcCommandContextPtr pRes = OdRxObjectImpl<ExPrcCommandContext, OdPrcCommandContext>::createObject();
  ExPrcCommandContext* pDbCmdCtx = static_cast<ExPrcCommandContext*>(pRes.get());

  pDbCmdCtx->m_pDb = pRxDb;
  pDbCmdCtx->m_pIoStream = pIOStream;
  return pRes;
}

OdRxObject* ExPrcCommandContext::baseDatabase()
{
  return m_pDb;
}

static OdUInt32 getGripObjLimit(const OdRxObject* cpRxDb)
{
  return 100;
}


OdString ExPrcCommandContext::getStringInternal(const OdString& prompt, int options, OdEdStringTracker* pTracker)
{
  return m_pIoStream->getString(prompt, options, pTracker);
}


double ExPrcCommandContext::getDist(const OdString& sPrompt,
                                   int options,
                                   double defVal,
                                   const OdString& sKeywords,
                                   OdEdRealTracker* pTracker)
{
  /*OdString prompt( sPrompt );
  if(prompt.isEmpty())
    prompt = OD_T("Enter a distance:");

  return getReal(prompt, options, defVal, OdResBuf::kDxfXdDist, sKeywords, pTracker);*/
  //TODO
  return 0;
}

double ExPrcCommandContext::getAngle(const OdString& sPrompt,
                                    int options,
                                    double defVal,
                                    const OdString& sKeywords,
                                    OdEdRealTracker* pTracker)
{
  OdString prompt(sPrompt);

  if (prompt.isEmpty())
    prompt = OD_T("Specify an angle:");

  double ANGBASE = 0.0;
  /*if (GETBIT(options, OdEd::kGanNoAngBase))
  {
    if (OdDbDatabase::cast(baseDatabase()).get())
      ANGBASE = database()->getANGBASE();
  }*/

  for (;;)
  {
    OdString sInput = ExPrcCommandContext::getString(prompt, options, OdString::kEmpty, sKeywords);
    if (sInput.isEmpty())
      return defVal;
    try
    {
      double dAngle = baseFormatter().unformatAngle(sInput);
      dAngle -= ANGBASE;
      return dAngle;
    }
    catch (const OdError& e)
    {
      if (e.code() != eInvalidInput)
        throw;
      if (GETBIT(options, OdEd::kInpThrowOther))
        throw OdEdOtherInput(sInput);
      putString(sKeywords.find(L' ') < 0 ? L"Requires valid numeric angle."
                                         : L"Requires valid numeric angle or optional keyword.");
    }
  }
}

OdEdPointDefTrackerPtr ExPrcCommandContext::createRubberBand(const OdGePoint3d& base,
                                                            OdGsModel* pModel) const // = NULL
{
  return RubberBand::create(base, pModel);
}

OdEdPointDefTrackerPtr ExPrcCommandContext::createRectFrame(const OdGePoint3d& base,
                                                           OdGsModel* pModel) const // = NULL
{
  return RectFrame::create(base, pModel);
}

OdGePoint3d ExPrcCommandContext::getLASTPOINT() const
{
  return m_LASTPOINT;
}

void ExPrcCommandContext::setLASTPOINT(const OdGePoint3d& pt)
{
  m_LASTPOINT = pt;
}

OdGePoint3d ExPrcCommandContext::getPoint(const OdString& sPrompt,
                                         int options,
                                         const OdGePoint3d* pDefVal,
                                         const OdString& keywords,
                                         OdEdPointTracker* pTracker)
{
  OdString prompt(sPrompt);

  if(prompt.isEmpty())
    prompt = OD_T("Enter a point:");

  OdEdPointTrackerPtr pPredef;
  if(!pTracker)
  {
    if(GETBIT(options, OdEd::kGptRectFrame))
    {
      pTracker = pPredef = createRectFrame(dbUserIO()->getLASTPOINT());
    }
    else if(GETBIT(options, OdEd::kGptRubberBand))
    {
      pTracker = pPredef = createRubberBand(dbUserIO()->getLASTPOINT());
    }
  }

  for(;;)
  {
    OdGePoint3d res;
    try
    {
      res = m_pIoStream->getPoint( prompt, options, pTracker );
    }
    catch(const OdEdEmptyInput&)
    {
      if(GETBIT(options, OdEd::kInpThrowEmpty))
        throw;
    }
    catch(const OdEdOtherInput& other)
    {
      if(!other.string().isEmpty())
      {
        if(!keywords.isEmpty())
          KWIndex(keywords).check(other.string());
        try
        {
          res = OdGePoint3d::kOrigin;
          OdString sInput(other.string());
          int i = 0;
          for (; i < 3 && !sInput.isEmpty(); ++i)
          {
            OdString sCoord = ::next(sInput);
            res[i] = baseFormatter().unformatLinear(sCoord);
          }
          if (i < 2)
            throw;
        }
        catch(const OdError& e)
        {
          if(e.code()!=eInvalidInput)
            throw;
          
          if(GETBIT(options, OdEd::kInpThrowOther))
            throw other;
          
          m_pIoStream->putString(keywords.isEmpty() ? OD_T("Invalid point.") : OD_T("Point or option keyword required."));
          continue;
        }
      }
      else if (GETBIT(options, OdEd::kInpThrowEmpty))
      {
        throw OdEdEmptyInput();
      }
      else if(pDefVal) {
        res = *pDefVal;
      }
      else
      {
        continue;
      }
    }
    /*if(!GETBIT(options, OdEd::kGptNoLimCheck) && database()->getLIMCHECK())
    {
      OdGeExtents2d ext(database()->getLIMMIN(), database()->getLIMMAX());
      if(!ext.contains((const OdGePoint2d&)res))
      {
        putString(OD_T("**Outside limits"));
        continue;
      }
    }*/
    
    dbUserIO()->setLASTPOINT(res);
    return res;
  }
}

int ExPrcCommandContext::getInt(const OdString& sPrompt,
                               int options,
                               int defVal,
                               const OdString& sKeywords,
                               OdEdIntegerTracker* pTracker)
{
  OdString prompt(sPrompt);

  if(prompt.isEmpty())
    prompt = OD_T("Enter an integer value:");
  OdString sInput = ExPrcCommandContext::getString(prompt, 0, OdString::kEmpty, sKeywords);
  if (sInput.isEmpty())
    return defVal;
  return ::odStrToInt(sInput);
}

int ExPrcCommandContext::getKeyword(const OdString& sPrompt,
                                   const OdString& sKeywords,
                                   int defVal,
                                   int options,
                                   OdEdIntegerTracker* pTracker)
{
  OdString prompt(sPrompt);

  KWIndex kwIndex(sKeywords);
  OdString pmt;
  if(prompt.isEmpty())
  {
    pmt = OD_T("Enter one of keywords [");
    for(OdUInt32 i=0; i<kwIndex.size(); ++i)
    {
      pmt += kwIndex.at(i).keyword();
      pmt += OD_T("/");
    }
    pmt += OD_T("]");
    if(!GETBIT(options, OdEd::kInpThrowEmpty))
    {
      pmt += OD_T("<");
      pmt += kwIndex.at(defVal).keyword();
      pmt += OD_T(">");
    }
    pmt += OD_T(":");
    prompt = pmt;
  }

  bool bDef = (OdUInt32(defVal) < kwIndex.size());
  for(;;)
  {
    SETBIT(options, OdEd::kGstNoEmpty, !bDef);
    OdString sInput = ExPrcCommandContext::getString(prompt, options);
    if(bDef && sInput.isEmpty())
      return defVal;
    OdUInt32 n = kwIndex.find(sInput);
    if(n < kwIndex.size())
      return n;
    putString(OD_T(""));
    putString(OD_T("Invalid option keyword."));
  }
}

double ExPrcCommandContext::getReal(const OdString& sPrompt, 
                                   int options,
                                   double defVal,
                                   const OdString& sKeywords,
                                   OdEdRealTracker* pTracker)
{
  OdString prompt(sPrompt);

  if(prompt.isEmpty())
    prompt = OD_T("Enter a real value:");
  for(;;)
  {
    OdString sInput = ExPrcCommandContext::getString(prompt, options, OdString::kEmpty, sKeywords);
    if (sInput.isEmpty())
      return defVal;
    try
    {
      return baseFormatter().unformatLinear(sInput);
    }
    catch(const OdError& e)
    {
      if(e.code()!=eInvalidInput)
        throw;
      if(GETBIT(options, OdEd::kInpThrowOther))
        throw OdEdOtherInput(sInput);
      putString(sKeywords.find(L' ') < 0 ? L"Requires real value." 
                                         : L"Requires real value or optional keyword.");
    }
  }
}

OdString ExPrcCommandContext::getString(const OdString& sPrompt, 
                                       int options, 
                                       const OdString& pDefVal,
                                       const OdString& sKeywords,
                                       OdEdStringTracker* pTracker)
{
  OdString res = getStringInternal(sPrompt, options, pTracker);

  if(res.isEmpty())
  {
    if(GETBIT(options, OdEd::kInpThrowEmpty))
      throw OdEdEmptyInput();

    if(!pDefVal.isEmpty())
      return pDefVal;

    if(GETBIT(options, OdEd::kGstNoEmpty))
    {
      do
      {
        putString(OD_T("Enter non-empty value"));
        res = getStringInternal(sPrompt, options, pTracker);
      }
      while(res.isEmpty());
    }
    else
      return res;
  }

  if(!sKeywords.isEmpty())
    KWIndex(sKeywords).check(res);

  return res;
}

OdString ExPrcCommandContext::getFilePath(const OdString& prompt, 
                                         int options,
                                         const OdString& dialogCaption, 
                                         const OdString& defExt,
                                         const OdString& fileName,
                                         const OdString& filter,
                                         const OdString& keywords,
                                         OdEdStringTracker* pTracker)
{
  return OdEdUserIO::getFilePath(prompt, options, dialogCaption, defExt, fileName, filter, keywords, pTracker);
}

void ExPrcCommandContext::putString(const OdString& string)
{
  m_pIoStream->putString(string);
}

OdSharedPtr<OdCmColorBase> ExPrcCommandContext::getCmColor(const OdString& sPrompt,
                                                          int options,
                                                          const OdCmColorBase* pDefVal,
                                                          const OdString& sKeywords,
                                                          OdEdColorTracker* pTracker)
{
  OdString prompt(sPrompt);

  if(prompt.isEmpty())
    prompt = OD_T("Specify a color:");

  for(;;)
  {
    OdString sInput = ExPrcCommandContext::getString(
                          prompt, options,
                          pDefVal ? (const OdString&)baseFormatter().formatCmColor(*pDefVal) 
                                  : OdString::kEmpty, sKeywords);
    try
    {
      return baseFormatter().unformatCmColor(sInput);
    }
    catch(const OdError& e)
    {
      if(e.code()!=eInvalidInput)
        throw;
      if(GETBIT(options, OdEd::kInpThrowOther))
        throw OdEdOtherInput(sInput);
      putString(sKeywords.find(L' ') < 0 ? L"Invalid color value."
                                         : L"Requires color value or optional keyword.");
    }
  }
}
#undef DBCC_PAGE_EACH_OBJECT
