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

#ifndef _ExPrcCommandContext_h_Included_
#define _ExPrcCommandContext_h_Included_

#include "TD_PackPush.h"

#include "Ed/EdFunctionIO.h"
#include "SSet.h"
#include "DbAux/PrcCommandContext.h"
#include "StaticRxObject.h"
#include "Ed/EdBaseUserIO.h"
#include "DbAux/PrcUnitsFormatterImpl.h"
#include "ExEdBaseIO.h"
#include "ExKWIndex.h"
//#include "ResBuf.h"
#include "RxDictionary.h"


/** \details
This class defines the interface for input/output operations and database access for samples of custom commands during their execution.

<group PRC_Protocol_Extensions_Classes>

\sa 
For additional information, see <link OdPrcCommandContext, OdPrcCommandContext> class documentation. 
*/
class ExPrcCommandContext : public OdPrcCommandContext
                          , protected OdEdBaseUserIO
                          , protected OdEdFunctionIO
{
protected:
  //DOM-IGNORE-BEGIN
  ODRX_USING_HEAP_OPERATORS(OdPrcCommandContext);
  //DOM-IGNORE-END

  OdSmartPtr<OdEdBaseIO>      m_pIoStream;
  OdRxObject*                 m_pDb;
  OdGePoint3d                 m_LASTPOINT;
  mutable OdRxDictionaryPtr   m_pArbDataDic;

  /** \details 
    Returns a smart pointer to an arbitrary data dictionary for the ExPrcCommandContext object.
    \remarks 
    A dictionary is created if it does not exist.
  */
  OdRxDictionaryPtr arbDataDic() const;

  OdString getStringInternal(const OdString& prompt, int options = OdEd::kInpDefault, OdEdStringTracker* pTracker = 0);

protected:
//DOM-IGNORE-BEGIN  
/** \details 
  // Leave this here--DO NOT move it out of the class definition.  Moving it 
  // outside causes an "internal compiler error" in CodeWarrior 8 & 9 on the mac.
*/
  ExPrcCommandContext()
    : m_pDb(0)
  {
  }
//DOM-IGNORE-END

public:
  /** \details 
    Creates an instance of the ExPrcCommandContext class.
    \param pIOStream [in] A pointer to a stream buffer for user input/output operations.
    \param pDb       [in] A pointer to a .prc database.
    \returns Returns a smart pointer to the newly created object.
  */
  static OdPrcCommandContextPtr createObject(OdEdBaseIO* pIOStream, OdPrcFile* pDb);

  /** \details 
    Creates an instance of the ExPrcCommandContext class.
    \param pIOStream [in] A pointer to a stream buffer for user input/output operations.
    \param pRxDb     [in] A pointer to a database represented as an OdRxObject.
    \returns Returns a smart pointer to the newly created object.
  */
  static OdPrcCommandContextPtr createObject(OdEdBaseIO* pIOStream, OdRxObject* pRxDb = 0);

  /** \details 
    Returns the database associated with the command context object.
  */
  OdRxObject* baseDatabase();
  
  /** \details 
    Returns the current object for implementing user input/output operations for the command context. 
  */
  OdEdUserIO* userIO() { return this; }

  /** \details 
    Returns the current object for implementing non-geometric interactive user input/output functionality for the command context.
  */
  OdEdFunctionIO* funcIO() { return this; }

  /** \details 
    Sets the parameter object for the command context object.
    \param pParamObj [in] A pointer to the parameter object.
  */
  virtual void setParam(OdRxObject* pParamObj);

  /** \details
    Returns a parameter object for the command context object.
  */
  virtual OdRxObjectPtr param();

  /** \details 
    Sets the result object for the command context object.
    \param pResultObj [in] A pointer to an OdRxObject for storing the result.
  */
  virtual void setResult(OdRxObject* pResultObj);

  /** \details
    Returns the current result object for the command context object.
  */
  virtual OdRxObjectPtr result();
  
  /** \details 
    Writes arbitrary data to the specified file with the command context object.
    \param fileName [in] A full filename.
    \param pDataObj [in] A pointer to the data object.
  */
  virtual void setArbitraryData(const OdString& fileName, OdRxObject* pDataObj);

  /** \details
    Reads the arbitrary data from the specified file within the command context object.
    \param fileName [in] A full filename to read data from.
    \returns Returns a smart pointer to the data object.
  */
  virtual OdRxObjectPtr arbitraryData(const OdString& fileName) const;

  /** \details 
    Returns the selection set containing the previous selection data with the command context object.
  */
  virtual OdSelectionSetPtr previousSelection();

  /** \details 
    Sets the previous selection set for the command context object.
    \param pSSet [in] A pointer to the previous selection set.
  */
  virtual void setPreviousSelection(OdSelectionSet* pSSet);

  /** \details 
  Returns the current unit base formatter for the command context object. 
  The formatter is returned as a reference, therefore it can be used to change formatter settings. 
  */
  virtual OdUnitsFormatter& baseFormatter();

/** \details
    Writes the specified string to the command's output.
    \param string [in]  A string to write.
  */
  virtual void putString(const OdString& string);

  /** \details
    Gets user input of an integer value from the command's input. 
    \param prompt         [in] A prompt string with text printed before waiting for user input.
    \param options        [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param defVal         [in] A default value returned if user inputs nothing.
    \param keywords       [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered integer value.
  */
  virtual int getInt(const OdString& prompt,
                     int options = OdEd::kInpDefault,
                     int defVal = 0,
                     const OdString& keywords = OdString::kEmpty,
                     OdEdIntegerTracker* pTracker = 0);

  /** \details
    Gets user input of a real value from the command's input. 
    \param prompt         [in] A prompt string with text printed before waiting for user input.
    \param options        [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param defVal         [in] A default value returned if user inputs nothing.
    \param keywordList    [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered double value.
  */
  virtual double getReal(const OdString& prompt, 
                         int options = OdEd::kInpDefault,
                         double defVal = 0.0,
                         const OdString& keywordList = OdString::kEmpty,
                         OdEdRealTracker* pTracker = 0);

  /** \details
    Gets user input of a string value from the command's input. 
    \param prompt         [in] A prompt string with text printed before waiting for user input.
    \param options        [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param pDefVal        [in] A default value returned if user inputs nothing.
    \param keywords       [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered string.
  */
  virtual OdString getString(const OdString& prompt, 
                             int options = OdEd::kInpDefault, 
                             const OdString& pDefVal = OdString::kEmpty,
                             const OdString& keywords = OdString::kEmpty,
                             OdEdStringTracker* pTracker = 0);

    /** \details
    Gets user input of a keyword value from the command's input. 
    \param prompt  [in]  A prompt string with text printed before waiting for user input.
    \param keywords [in]  A keyword list.
    \param options  [in]  A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param defRes   [in]  A default value returned if user inputs a keyword that does not in the keywords list.
    \param pTracker [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the index of the entered keyword in the keyword list or -1 if it's not there.
  */
  virtual int getKeyword(const OdString& prompt,
                         const OdString& keywords,
                         int defRes = -1,
                         int options = OdEd::kInpDefault,
                         OdEdIntegerTracker* pTracker = 0);

  /** \details
    Gets the angle value from the command's input.
    \param prompt         [in] A prompt string.
    \param options        [in] A set of input options. 
    \param defVal         [in] A default value. 
    \param keywords       [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered angle value.
  */

  /** \details
    Gets user input of an angle value from the command's input. 
    \param prompt         [in] A prompt string with text printed before waiting for user input.
    \param options        [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param defVal         [in] A default value returned if user inputs nothing.
    \param keywords       [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered double value of an angle.
  */
  virtual double getAngle(const OdString& prompt,
                          int options = OdEd::kInpDefault,
                          double defVal = 0.0,
                          const OdString& keywords = OdString::kEmpty,
                          OdEdRealTracker* pTracker = 0);

  /** \details
    Returns the LASTPOINT system variable value for the command context object.
  */
  virtual OdGePoint3d getLASTPOINT() const;

  /** \details 
    Sets a new value of the LASTPOINT system variable for this CommandContext object.
    \param val [in] A new value to be set for the LASTPOINT system variable. 
  */
  virtual void setLASTPOINT(const OdGePoint3d& val);

  /** \details 
    Creates a rubberband line from the specified point (base point) to the user input.
    \param base   [in] A base point.
    \param pModel [in] A raw pointer to a GS model object that should include created rubberband.
  */
  virtual OdEdPointDefTrackerPtr createRubberBand(const OdGePoint3d& base,
                                                  OdGsModel* pModel = NULL) const;
  /** \details 
    Creates a rectangular frame from the specified point (base point) to the user input.
    \param base   [in] A base point.
    \param pModel [in] A raw pointer to a GS model object that should include created frame.
  */
  virtual OdEdPointDefTrackerPtr createRectFrame(const OdGePoint3d& base,
                                                 OdGsModel* pModel = NULL) const;

  /** \details
    Gets user input of a point  from the command's input. 
    \param prompt   [in] A prompt string with text printed before waiting for user input.
    \param options  [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param pDefVal  [in] A default value returned if user inputs nothing.
    \param keywords [in] A string with a keywords list. 
    \param pTracker [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered 3D point.
  */
  virtual OdGePoint3d getPoint(const OdString& prompt,
                               int options = OdEd::kGptDefault,
                               const OdGePoint3d* pDefVal = 0,
                               const OdString& keywords = OdString::kEmpty,
                               OdEdPointTracker* pTracker = 0);

  /** \details
    Gets user input of a distance value from the command's input. 
    \param prompt         [in] A prompt string with text printed before waiting for user input.
    \param options        [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param defVal         [in] A default value returned if user inputs nothing.
    \param keywords       [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered double value for a distance.
  */
  virtual double getDist(const OdString& prompt,
                         int options = OdEd::kInpDefault,
                         double defVal = 0.0,
                         const OdString& keywords = OdString::kEmpty,
                         OdEdRealTracker* pTracker = 0);

  /** \details
    Gets user input of a distance value from the command's input. 
    \param prompt         [in] A prompt string with text printed before waiting for user input.
    \param options        [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param dialogCaption  [in] Text for the dialog caption.
    \param defExt         [in] A default file extension. 
    \param fileName       [in] A file name. 
    \param filter         [in] A filter for files (*.*, *.txt, etc).
    \param keywords       [in] A string with a keywords list. 
    \param pTracker       [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered file path.
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
    Gets user input of a color value from the command's input. 
    \param sPrompt   [in] A prompt string with text printed before waiting for user input.
    \param options   [in] A set of input options (bitwise or combination of the OdEd::CommonInputOptions enum). 
    \param pDefVal   [in] Text for the dialog caption.
    \param sKeywords [in] A string with a keywords list. 
    \param pTracker  [in] A pointer to a notification interface for tracking changes in the command context object.
    \returns Returns the entered color value.
  */
  virtual OdSharedPtr<OdCmColorBase> getCmColor(const OdString& sPrompt,
                                                int options = OdEd::kInpDefault,
                                                const OdCmColorBase* pDefVal = 0,
                                                const OdString& sKeywords = OdString::kEmpty,
                                                OdEdColorTracker* pTracker = 0);
};

#include "TD_PackPop.h"

#endif // _ExPrcCommandContext_h_Included_
