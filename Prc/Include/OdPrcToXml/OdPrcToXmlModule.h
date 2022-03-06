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

#ifndef _PRCTOXML_DEFINED_
#define _PRCTOXML_DEFINED_

#include "PrcToXmlExportDef.h"
#include "RxModule.h"
#include "ControlFlags.h"

/** \details 
<group PRC_Export_Import_Classes> 

Class representing functions of writing PRC data to an output .xml file. 
*/
class PRCTOXML_TOOLKIT OdPrcToXmlModule : public OdRxModule
{
public:

  /** \details
  Initializes an application.
  */
  virtual void initApp();
  
  /** \details
  Uninitializes an application.
  */
  virtual void uninitApp();

  /** \details
  Writes PRC data to a specified output stream.

  \param pPrcStream [in] A smart pointer to an input stream with PRC data.
  \param pXmlStream [in] A smart pointer to an output stream (.xml file) to write to.
  \param flags [in] A group of flags to control output in an .xml file.   
  
  \returns Returns eOk if PRC data was written successfully to an .xml file or an appropriate error code in the other case.
  */
  virtual OdResult prcToXml(OdStreamBufPtr pPrcStream, OdStreamBufPtr pXmlStream, ControlFlags flags = ControlFlags::kDefaultMode);
  
  /** \details
  Writes PRC data to a specified output stream.

  \param pPrcStream [in] A smart pointer to an input stream with PRC data.
  \param pXmlStream [in] A smart pointer to an output stream (.txt file) to write to.
  \param flags [in] A group of flags to control output in a .txt file.   
  
  \returns Returns eOk if PRC data was written successfully to an .xml file or an appropriate error code in the other case.
*/
  virtual OdResult prcToTxt(OdStreamBufPtr pPrcStream, OdStreamBufPtr pXmlStream, ControlFlags flags = ControlFlags::kDefaultMode);
};

SMARTPTR(OdPrcToXmlModule);

#endif //_PRCTOXML_DEFINED_

