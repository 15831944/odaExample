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

#ifndef _DAI_HOST_APP_SERVICES_BASE_H
#define _DAI_HOST_APP_SERVICES_BASE_H

#include "OdaCommon.h"
#include "DbBaseHostAppServices.h"

#include "daiBuildOptions.h"

namespace OdDAI {
  class OdHeaderSection;
  typedef OdSmartPtr<OdHeaderSection> OdHeaderSectionPtr;
}

class ODRX_ABSTRACT DAI_EXPORT OdDAIHostAppServicesBase : public OdDbBaseHostAppServices
{
public:

  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdDAIHostAppServicesBase);
  //DOM-IGNORE-END

  /** \details
  Retrieves the Data Access Interface database class description.
  \returns Returns the desc() method's result of the <link OdIfcFile, OdIfcFile> object.
  */
  virtual OdRxClass* databaseClass() const = 0;

  /** \details
  Retrieves the Data Access Interface model class description.
  \returns Returns the desc() method's result of the <link OdDAI::Model, Model> object.
  */
  virtual OdRxClass* modelClass() const;

  virtual OdString findFile(const OdString& fileName, OdDbBaseDatabase* pDb = nullptr, FindFileHint hint = kDefault);

  /** \details
  Returns name of file that contains EXPRESS schema definition associated with schemaIdentifier.
  \returns Returns the OdAnsiString that contains name of file that contains EXPRESS schema definition.
  \remarks
  Default implementation contains mapping for following supported schemas:

  <table>
  Identifier                                      Protocol
  CONFIG_CONTROL_DESIGN                           AP203
  AUTOMOTIVE_DESIGN                               AP214
  INTEGRATED_CNC_SCHEMA                           AP238
  AP242_MANAGED_MODEL_BASED_3D_ENGINEERING_MIM_LF AP242
  STRUCTURAL_FRAME_SCHEMA                         CIS/2
  </table>

  */
  virtual const OdAnsiString& findSchemaFileName(const OdAnsiString &schemaIdentifier) const;

  /** \details
  Retrieves the header section of the specified IFC file.
  \param filename [in] A string that contains the full path to the input IFC file.
  \returns Returns a smart pointer to the <link OdDAI::OdHeaderSection, OdHeaderSection> object that contains header section data.
  */
  OdDAI::OdHeaderSectionPtr getHeaderSection(const OdString& filename);
};

#endif // _DAI_HOST_APP_SERVICES_BASE_H
