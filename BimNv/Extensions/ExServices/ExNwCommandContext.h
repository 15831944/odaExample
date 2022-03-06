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

#ifndef _ExBimNvCommandContext_h_Included_
#define _ExBimNvCommandContext_h_Included_

#include "TD_PackPush.h"

#include "Ed/EdFunctionIO.h"
#include "NwSSet.h"
#include "NwCommandContext.h"
#include "StaticRxObject.h"
#include "Ed/EdBaseUserIO.h"
#include "NwUnitsFormatterImpl.h"
#include "ExEdBaseIO.h"
#include "ExKWIndex.h"


/** \details
This class stores command context data.

<group Extension_Classes>
*/
class ExNwCommandContext : public OdNwCommandContext
  , protected OdNwUserIO
  , protected OdEdFunctionIO
{
protected:
  ODRX_USING_HEAP_OPERATORS(OdNwCommandContext);

  OdSmartPtr<OdEdBaseIO>      m_pIoStream;
  OdRxObject*                 m_pDb;
  OdGePoint3d                 m_LASTPOINT;
  mutable OdRxDictionaryPtr   m_pArbDataDic;

  /** \details
  Returns a SmartPointer to the arbitrary data dictionary for this CommandContext object.

  \remarks
  A dictionary is created if a dictionary does not exist.
  */
  OdRxDictionaryPtr arbDataDic() const;

  /** \details
  Returns internal string from input stream.

  \param prompt   [in]  Prompt output before pausing for user input.
  \param options  [in]  Input options.
  \param pTracker [in]  Pointer to an IO Tracker for this user input.
  */
  OdString getStringInternal(const OdString& prompt, int options = OdEd::kInpDefault, OdEdStringTracker* pTracker = 0);

  struct RealInput
  {
    double val;
  };

  /** \details
  Returns input of a point or a real from the StreamBuf associated with this CommandContext object.

  \param prompt     [in]  Prompt output before pausing for user input.
  \param options    [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param keywords   [in]  Keyword string.
  \param realType   [in]  Type of real.
  \param pPtTracker [in]  Pointer to a Point Tracker for this user input.

  \remarks
  If prompt is empty, a default prompt is used.

  realType can be one of the following:

  <table>
    Name
    OdResBuf::kDxfXdDist
    OdResBuf::kRtOrient
  </table>

  This function uses the underlying OdEdBaseIO functions putString and getPoint for low
  level output.
  */
  /*  OdGePoint3d getPointOrReal(const OdString& prompt,
                               int options,
                               const OdString& keywords,
                               OdResBuf::ValueType realType,
                               OdEdPointTracker* pPtTracker);*/

protected:


  // Leave this here--DO NOT move it out of the class definition.  Moving it
  // outside causes an "internal compiler error" in CodeWarrior 8 & 9 on the mac.

  ExNwCommandContext()
    : m_pDb(0)
  {
  }

public:

  /** \details
  Creates an instance of this CommandContext object.

  \param pIOStream  [in]  Pointer to the the stream buffer.
  \param pDb        [in]  Pointer to the database.

  \remarks
  Returns a smart pointer to the newly created object.
  */
  static OdNwCommandContextPtr createObject(OdEdBaseIO* pIOStream, OdNwDatabase* pDb);

  /** \details
  Creates an instance of this CommandContext object.

  \param pIOStream [in]  Pointer to the the stream buffer.
  \param pRxDb     [in]  Pointer to the OdRxObject.

  \remarks
  Returns a smart pointer to the newly created object.
  */
  static OdNwCommandContextPtr createObject(OdEdBaseIO* pIOStream, OdRxObject* pRxDb = 0);

  /** \details
  Returns pointer to the base database.
  */
  OdRxObject* baseDatabase();

  /** \details
  Returns pointer to the user I/O data.
  */
  OdEdUserIO* userIO() { return this; }

  /** \details
  Returns pointer to the I/O function.
  */
  OdEdFunctionIO* funcIO() { return this; }

  /** \details
  Sets the parameter object for this CommandContext object.

  \param pParamObj [in]  Pointer to the parameter object.
  */
  virtual void setParam(OdRxObject* pParamObj);

  /** \details
  Returns the parameter object for this CommandContext object.
  */
  virtual OdRxObjectPtr param();

  /** \details
  Sets the result object for this CommandContext object.

  \param pResultObj [in]  Pointer to the result object.
  */
  virtual void setResult(OdRxObject* pResultObj);

  /** \details
  Returns the result object for this CommandContext object.
  */
  virtual OdRxObjectPtr result();

  /** \details
  Writes arbitrary data to the specified file with this CommandContext object.

  \param fileName [in]  File name.
  \param pDataObj [in]  Pointer to the data object.
  */
  virtual void setArbitraryData(const OdString& fileName, OdRxObject* pDataObj);

  /** \details
  Reads arbitrary data from the specified file with this CommandContext object.

  \param fileName [in]  Filename.

  \remarks
  Returns a smart pointer to the data object.
  */
  virtual OdRxObjectPtr arbitraryData(const OdString& fileName) const;

  /** \details
  Returns a selection set containing previous selection data with this CommandContext object.
  */
  virtual OdSelectionSetPtr previousSelection();

  /** \details
  Sets the previous selection set for this CommandContext object.

  \param pSSet [in]  Pointer to the previous selection set.
  */
  virtual void setPreviousSelection(OdSelectionSet* pSSet);

  // OdEdUserIO interface:

  /** \details
  Returns base formatter of base database of this CommandContext object.
  */
  virtual OdUnitsFormatter& baseFormatter();

  /** \details
  Puts string to the stream.

  \param string [in]  Input string.
  */
  virtual void putString(const OdString& string);

  /** \details
  Gets integer value of this CommandContext object.

  \param prompt     [in]  Prompt output before pausing for user input.
  \param options    [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param defVal     [in]  Default value.
  \param keywords   [in]  Keyword string.
  \param pPtTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual int getInt(const OdString& prompt,
    int options = OdEd::kInpDefault,
    int defVal = 0,
    const OdString& keywords = OdString::kEmpty,
    OdEdIntegerTracker* pTracker = 0);

  /** \details
  Gets real value of this CommandContext object.

  \param prompt       [in]  Prompt output before pausing for user input.
  \param options      [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param defVal       [in]  Default value.
  \param keywordList  [in]  Keyword string.
  \param pTracker     [in]  Pointer to a Point Tracker for this user input.
  */
  virtual double getReal(const OdString& prompt,
    int options = OdEd::kInpDefault,
    double defVal = 0.0,
    const OdString& keywordList = OdString::kEmpty,
    OdEdRealTracker* pTracker = 0);

  /** \details
  Gets string value of this CommandContext object.

  \param prompt   [in]  Prompt output before pausing for user input.
  \param options  [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param pDefVal  [in]  Default value.
  \param keywords [in]  Keyword string.
  \param pTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual OdString getString(const OdString& prompt,
    int options = OdEd::kInpDefault,
    const OdString& pDefVal = OdString::kEmpty,
    const OdString& keywords = OdString::kEmpty,
    OdEdStringTracker* pTracker = 0);
  /** \details
  Gets keyword value of this CommandContext object.

  \param prompt   [in]  Prompt output before pausing for user input.
  \param keywords [in]  Keyword string.
  \param defRes   [in]  Default value.
  \param options  [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param pTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual int getKeyword(const OdString& prompt,
    const OdString& keywords,
    int defRes = -1,
    int options = OdEd::kInpDefault,
    OdEdIntegerTracker* pTracker = 0);

  /** \details
  Gets angle value of this CommandContext object.

  \param prompt   [in]  Prompt output before pausing for user input.
  \param options  [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param defVal   [in]  Default value.
  \param keywords [in]  Keyword string.
  \param pTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual double getAngle(const OdString& prompt,
    int options = OdEd::kInpDefault,
    double defVal = 0.0,
    const OdString& keywords = OdString::kEmpty,
    OdEdRealTracker* pTracker = 0);

  /** \details
  Returns the LASTPOINT system variable for this CommandContext object.
  */
  virtual OdGePoint3d getLASTPOINT() const;

  /** \details
  Sets the LASTPOINT system variable for this CommandContext object.

  \param val [in]  New value for LASTPOINT.
  */
  virtual void setLASTPOINT(const OdGePoint3d& val);

  /** \details
  Creates a rubberband line from the specified point to the user input.

  \param base   [in]  Base point.
  \param pModel [in]  set of drawable objects.
  */
  virtual OdEdPointDefTrackerPtr createRubberBand(const OdGePoint3d& base,
    OdGsModel* pModel = NULL) const;
  /** \details
  Creates a rectangular frame from the specified point to the user input.

  \param base   [in]  Base point.
  \param pModel [in]  set of drawable objects.
  */
  virtual OdEdPointDefTrackerPtr createRectFrame(const OdGePoint3d& base,
    OdGsModel* pModel = NULL) const;

  /** \details
  Gets point of this CommandContext object.

  \param prompt [in]  Prompt output before pausing for user input.
  \param options [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param pDefVal [in]  Default value.
  \param keywords [in]  Keyword string.
  \param OdEdPointTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual OdGePoint3d getPoint(const OdString& prompt,
    int options = OdEd::kGptDefault,
    const OdGePoint3d* pDefVal = 0,
    const OdString& keywords = OdString::kEmpty,
    OdEdPointTracker* = 0);

  /** \details
  Gets distance of this CommandContext object.

  \param prompt [in]  Prompt output before pausing for user input.
  \param options [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param defVal [in]  Default value.
  \param keywords [in]  Keyword string.
  \param pTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual double getDist(const OdString& prompt,
    int options = OdEd::kInpDefault,
    double defVal = 0.0,
    const OdString& keywords = OdString::kEmpty,
    OdEdRealTracker* pTracker = 0);

  /** \details
  Gets file path of this CommandContext object.

  \param prompt [in]  Prompt output before pausing for user input.
  \param options [in]  Input options.
  \param dialogCaption [in]  Dialog caption.
  \param defExt [in]  Default path.
  \param fileName [in]  File name.
  \param filter [in]  Filter.
  \param keywords [in]  Keyword string.
  \param pTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual OdString getFilePath(const OdString& prompt,
    int options,
    const OdString& dialogCaption,
    const OdString& defExt,
    const OdString& fileName,
    const OdString& filter,
    const OdString& keywords = OdString::kEmpty,
    OdEdStringTracker* pTracker = 0);

  /** \details
  Gets color of this CommandContext object.

  \param prompt [in]  Prompt output before pausing for user input.
  \param options [in]  Combination of OdEd::CommonInputOptions and OdEd::GetStringOptions enum values.
  \param OdCmColorBase [in]  Default color.
  \param sKeywords [in]  Keyword string.
  \param pTracker [in]  Pointer to a Point Tracker for this user input.
  */
  virtual OdSharedPtr<OdCmColorBase> getCmColor(const OdString& sPrompt,
    int options = OdEd::kInpDefault,
    const OdCmColorBase* pDefVal = 0,
    const OdString& sKeywords = OdString::kEmpty,
    OdEdColorTracker* pTracker = 0);

  virtual void setPickfirst(OdSelectionSet* pSSet);

  virtual OdSelectionSetPtr pickfirst();

  virtual OdNwCmColor getColor(const OdString& prompt,
    int options = OdEd::kInpDefault,
    const OdCmColorBase* pDefVal = 0,
    const OdString& keywordList = OdString::kEmpty,
    OdEdColorTracker* pTracker = 0);

  virtual OdSelectionSetPtr box(const OdGePoint3d& firstCorner, OdDbVisualSelection::SubentSelectionMode ssm);

  OdNwObjectId getDBViewportId(const OdNwDatabase* pDb);

  virtual OdNwSelectionSetPtr select(const OdString& sPrompt = OdString::kEmpty,
    int options = OdEd::kSelDefault,
    const OdNwSelectionSet* pDefVal = 0,
    const OdString& keywords = OdString::kEmpty,
    OdNwSSetTracker* pTracker = 0);

protected:
  void merge(OdNwSelectionSet* pRes,
    int options,
    const OdNwSelectionSet* pSSet,
    OdNwSSetTracker* pTracker,
    OdEdUserIO* pIO);

  virtual bool isPickadd() const;
  virtual void highlight(OdSelectionSet* pSSet, bool bDoIt = true) const;
  virtual void highlight(OdSelectionSetIterator* pIter, bool bDoIt = true) const;
};

#include "TD_PackPop.h"

#endif // _ExBimNvCommandContext_h_Included_
