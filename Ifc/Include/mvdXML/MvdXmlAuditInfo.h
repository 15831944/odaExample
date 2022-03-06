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

#if !defined(ODA_ODMVDXMLAUDITINFO_H_INCLUDED_)
#define ODA_ODMVDXMLAUDITINFO_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OdaCommon.h"
#include "mvdXMLBuildOptions.h"

namespace OdMvdXml
{
  /** \details
    OdMvdXmlAuditInfo - class for storing a list of errors and warnings.
  */
  class MVDXML_EXPORT OdMvdXmlAuditInfo
  {
  public:
    /** \details
      Append message to the list of error messages.
      \param message [in] A string message to add to the error list.
    */
    void appendErrorMessage(const OdAnsiString& message);
    /** \details
      Append message to the list of warning messages.
      \param message [in] A string message to add to the warning list.
    */
    void appendWarningMessage(const OdAnsiString& message);
    /** \details
      Retrieves the list of error messages.

      \returns
      List of error messages.
    */
    const OdAnsiStringArray& getErrors() const;
    /** \details
      Retrieves the list of warning messages.

      \returns
      List of warning messages.
    */
    const OdAnsiStringArray& getWarnings() const;
    /** \details
      Retrieves the number of error messages.

      \returns
      Number of error messages.
    */
    OdUInt32 numOfErrors() const;
    /** \details
      Retrieves the number of warning messages.

      \returns
      Number of warning messages.
    */
    OdUInt32 numOfWarnings() const;
    /** \details
      Clear all messages.
    */
    void clear();

  private:
    /** \details
      List of error messages.
    */
    OdAnsiStringArray m_errors;
    /** \details
      List of warning messages.
    */
    OdAnsiStringArray m_warnings;
  }; 
}

#endif // !defined(ODA_ODMVDXMLAUDITINFO_H_INCLUDED_)
