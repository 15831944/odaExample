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

#ifndef _PRCAUDITINFOIMPL_INCLUDED_
#define _PRCAUDITINFOIMPL_INCLUDED_ 
 

#include "PrcAuditInfo.h"
#include "StringArray.h"

SMARTPTR(OdPrcAuditInfoImpl);

/** \details 
<group PRC_Files_Structures_Assemblies> 

Class implements functionality for working with audit log files.
*/
class PRC_TOOLKIT OdPrcAuditInfoImpl : public OdPrcAuditInfo
{
  OdStringArray m_log;
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcAuditInfoImpl);
  //DOM-IGNORE-END

  /** \details 
  Destroys an audit info implementation object.
  */
  virtual ~OdPrcAuditInfoImpl();

  /** \details
    Notification method, which should be called to print error information.
    Prints log information about an error detected or fixed during an audit.
    
    \param name [in] A type of erroneous data that is found.
    \param value [in] A value of the erroneous data.
    \param validation [in] A reason why the data was erroneous.
    \param defaultValue [in] A default value to which the data was set.
  */
  virtual void printError(
    const OdString& name,
    const OdString& value,
    const OdString& validation = OdString::kEmpty,
    const OdString& defaultValue = OdString::kEmpty );

  /** \details
    Adds error information to a log file.
    \param logInfo [in] A string with information about an error.
  */
  virtual void printInfo (
    const OdString& logInfo);

  /** \details
    Checks whether there is information about any errors in a log file.
    \returns Returns true if the log file is not empty or false in the other case.
  */
  virtual bool errorsFound() const;

  /** \details
    Clears a log file.
  */
  virtual void clearErrors();

  /** \details 
    Returns all error information from the audit log file as an OdStringArray object. 
  */
  virtual const OdStringArray &errorInfo() const;
};

#endif //_PRCAUDITINFOIMPL_INCLUDED_

