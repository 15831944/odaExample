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

#ifndef _PRCAUDITINFO_INCLUDED_
#define _PRCAUDITINFO_INCLUDED_ 
 

SMARTPTR(OdPrcAuditInfo);
  
/** \details 
<group PRC_Files_Structures_Assemblies> 

Class implements base functionality for working with audit log files.
*/
class PRC_TOOLKIT OdPrcAuditInfo : public OdRxObject
{

  bool m_bFixErrors;

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcAuditInfo);
  //DOM-IGNORE-END

  /** \details 
  Destroys the audit information object.
  */
  virtual ~OdPrcAuditInfo();

  /** \details
    Retrieves the current value of the recovery flag.
    The recovery flag determines whether errors should be fixed during the audit process (the flag value is equal to true) or not (the flag value is equal to false).
  
    \returns true if the errors should be fixed; otherwise, the method returns false.
  */
  bool fixErrors() const;

  /** \details
    Sets a new value of the recovery flag.
    The recovery flag determines whether errors should be fixed during the audit process (the flag value is equal to true) or not (the flag value is equal to false).
  
    \param bFix [in] A new value of the recovery flag to be set.
  */
  void setFixErrors(bool bFix);

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
};

#endif //_PRCAUDITINFO_INCLUDED_

