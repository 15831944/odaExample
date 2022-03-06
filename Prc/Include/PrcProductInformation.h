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

#ifndef _PRCPRODUCTINFORMATION_INCLUDED_
#define _PRCPRODUCTINFORMATION_INCLUDED_ 
 

#include "PrcUnit.h"

/** \details 
<group PRC_Files_Structures_Assemblies>

Class stores product occurrence information.
*/
class PRC_TOOLKIT OdPrcProductInformation
{
private:
  OdPrcUnit   m_unit_information;
  OdInt8      m_product_information_flags;
  OdUInt32    m_product_load_status;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcProductInformation)
  //DOM-IGNORE-END

  /** \details 
  Returns information about units used for the product occurrence.
  Units are measured in mm. 
  Unit information is returned as a reference to an OdPrcUnit object, therefore it can be used to set new unit information.
  */
  OdPrcUnit &unitInformation();
  
  /** \details 
  Returns information about units used for the product occurrence.
  Units are measured in mm. 
  */
  const OdPrcUnit &unitInformation() const;
  
  /** \details 
  Sets a new value of the product information flag.
  
  \param product_information_flags [in] A new value of the flag to be set.
  
  \remarks 
  Flag values can be one (or several) of the following list:
  <table>
    Value  Occurrence Type  Description
    0x00  Regular           Regular product occurrence.
    0x01  Default           Default container, configuration view that can be loaded by default by the original CAD application.
    0x02  Internal          Product occurrence belongs to the same file structure and can be used as a template for another product occurrence.
    0x04  Container         A collection of child product occurrences.
    0x08  Configuration     A special arrangement of a product in which some components can differ or can be placed in different positions. But hierarchical integrity of the product occurrence is strictly respected.
    0x10  View              Product occurrence which refers to another product occurrence or its prototype as a view to provide special visibility parameters within the same hierarchy. 
  </table>
  
  Note that parentless product occurrences are similar to Configuration and lead to a different file structure (except cases when product occurrence is internal).
  If the flag Regular or the flag Container is switched on, other flag's values are ignored. Any combination of the flags is acceptable.
  */
  void setProductInformationFlags(OdInt8 product_information_flags);
  
  /** \details  
  Returns the current value of the product information flags.
  \remarks 
  Flag values can be one (or several) of the following list:
  <table>
    Value  Occurrence Type  Description
    0x00  Regular           Regular product occurrence
    0x01  Default           Default container, configuration view that can be loaded by default by the original CAD application
    0x02  Internal          Product occurrence belongs to the same file structure and can be used as a template of another product occurrence
    0x04  Container         A collection of child product occurrences
    0x08  Configuration     A special arrangement of a product in which some components can differ or can be placed in different positions. But hierarchical integrity of the product occurrence is strictly respected
    0x10  View              Product occurrence which refers to another product occurrence or its prototype as a view due to provide a special visibility parameters within the same hierarchy. 
  </table>
  
  Note that parentless product occurrences are similar to Configuration and lead to a different file structure (except cases when product occurrence is internal).
  If flag Regular or flag Container is switched on, other flag's values are ignored. Any combination of the flags is acceptable.
  */
  OdInt8 productInformationFlags() const;
  
  /** \details 
  Sets a new value of the loading status for the product occurrence.
  
  \param product_load_status [in] A new value of the loading status to be set. 
  
   \remarks  
  Loading status determines the possibility of loading external elements of the product occurrence and can be one of the following values:
  <table>
    Value   Description
    0       Status is unknown
    1       Loading failed: missed file
    2       File can't be loaded 
    3       Loading successfully finished
  </table>
  */
  void setProductLoadStatus(OdUInt32 product_load_status);
  
  /** \details 
  Returns the current value of the loading status for the product occurrence. 
  
  \remarks 
  Loading status determines the possibility of loading external elements of the product occurrence and can be one of the following values:
  <table>
    Value   Description
    0       Status is unknown
    1       Loading failed: missed file
    2       File can't be loaded 
    3       Loading successfully finished
  </table>
  */
  OdUInt32 productLoadStatus() const;
};

#endif // _PRCPRODUCTINFORMATION_INCLUDED_

