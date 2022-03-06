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

#ifndef _ODTV_ERRORIMPL_H_INCLUDED_
#define _ODTV_ERRORIMPL_H_INCLUDED_

#include "TD_PackPush.h"
#include "Tv.h"
#include "TvError.h"
#include "RxObject.h"

//******************************************************************************
//*** TV internal result codes ************************************************
//******************************************************************************

enum OdTvInternalResult
{
  tvSuccess                              = 0x0000,
  tvErased                               = 0x0001,
  tvNullObjectId                         = 0x0002,
  tvNotOpenForRead                       = 0x0003,
  //tvNotOpenForWrite                      = 0x0004,
  tvKeyNotFound                          = 0x0005,
  tvNullEntityPointer                    = 0x0006,
  tvNotInDatabase                        = 0x0007,
  tvNoDatabase                           = 0x0008,
  tvWrongDatabase                        = 0x0009,
  tvImposibleToDefineParentObj           = 0x000A,
  tvAlreadyInDb                          = 0x000B,
  tvDeviceHasNoContext                   = 0x000C,
  tvContextHasNoDatabase                 = 0x000D,
  tvCannotCreateDbDatabase               = 0x000E,
  tvCannotWriteDbDatabase                = 0x000F,
  tvCannotReadDbDatabase                 = 0x0010,
  tvDummyInternalLastError
};


/** \details
    This class implements a node in an ErrorContext stack.
*/

class OdTvErrorContext : public OdRxObject
{
  OdTvResult m_res;
  OdTvInternalResult m_internalRes;
  OdError m_internalDbError;

protected:
  OdTvErrorContext* m_pPreviousError;
  OdTvErrorContext() : m_pPreviousError(0), m_internalDbError(OD_T("")) {}
  /** \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  OdTvErrorContext(OdTvErrorContext* pPreviousError);
public:
  virtual ~OdTvErrorContext();

  OdSmartPtr<OdTvErrorContext> init(OdTvResult err, OdTvErrorContext* prev = 0);
  OdSmartPtr<OdTvErrorContext> init(OdTvInternalResult err, const OdError& e, OdTvErrorContext* prev = 0);
  
  /** \details
    Returns the description of this ErrorContext object.
  */
  virtual OdString description() const;
  
  /** \details
    Returns the OdTvResult code of this ErrorContext object.
  */
  virtual OdTvResult code() const {return m_res; }
  
  /** \details
    Returns the complete description of this ErrorContext object.
    \remarks
    completeDescription() returns a string containing the concatination of
    all of the description strings in the ErrorContext stack.
    
    The default implementation of this function returns a string in the following format:
            
                   <Description n-1>\n
                    Previous error: <Description n-2>\n
                    Previous error: <Description n-3>\n
                    ...
                    Previous error: <Description 0>\n
  */
  OdString completeDescription() const;
  /** \details
    Returns the ErrorContext object previous to this one in this ErrorContext stack.
  */
  OdTvErrorContext* getPreviousError() const { return m_pPreviousError; }

  /** \details
    Sets the ErrorContext object previous to this one in this ErrorContext stack.
    \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  void setPreviousError(OdTvErrorContext* pPreviousError);
};



/** \details
This class implement OdTvErrorImpl node objects in an OdTvErrorImplNode stack..

*/
class OdTvErrorImpl : public OdTvError
{
  OdTvErrorContext* m_pContext;
public:
  void setContext(OdTvErrorContext* pErrorContext);
  const OdTvErrorContext* context() const;
  OdTvErrorContext* context();

  /** \param code [in]  Error code.
  */
  explicit OdTvErrorImpl(OdTvResult code);
  explicit OdTvErrorImpl(OdTvInternalResult code, const OdError& e);
  OdTvErrorImpl(const OdTvErrorImpl& source);

  /** \param pErrorContext [in]  Pointer to the ErrorContext.
  */
  explicit OdTvErrorImpl(OdTvErrorContext* pErrorContext);

  /** \destructor
  */
  ~OdTvErrorImpl();

  OdTvErrorImpl& operator = (const OdTvErrorImpl& source);

  /** \details
  Returns the OdTvResult code of this Error object.
  */
  virtual OdTvResult code() const;

  /** \details
  Returns the description of this Error object.
  */
  virtual OdString description() const;

  /** \details
  Sets the Error object previous to this one in this Error stack.
  \param previousError [in]  Previous Error object.
  */
  void attachPreviousError(const OdTvErrorImpl& previousError);
};

#include "TD_PackPop.h"

#endif //_ODTV_ERRORIMPL_H_INCLUDED_
