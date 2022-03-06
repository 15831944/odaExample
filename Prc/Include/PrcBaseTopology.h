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

#ifndef _PRCBASETOPOLOGY_INCLUDED_
#define _PRCBASETOPOLOGY_INCLUDED_ 
 

#include "PrcAttributeData.h"
#include "PrcName.h"

/** \details
<group PRC_Base_Classes>
Class implements storing base topology information of a PRC entity.
Base topology information contains name, attributer data, and identifier for an original CAD application. 
*/
class PRC_TOOLKIT OdPrcBaseTopology
{
private:
  OdPrcName           m_name;
  OdPrcAttributeData  m_AttributeData;
  OdUInt32            m_identifier;
  bool                m_base_information;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcBaseTopology)
  //DOM-IGNORE-END

  /** \details
  Returns the current name of the PRC base topology.
  The name is returned as a reference to an OdPrcName object, therefore it can be used to set a new value of the topology name.
  */
  OdPrcName &name();
  
  /** \details
  Returns the current name of the PRC base topology.
  */
  const OdPrcName &name() const;
  
  /** \details 
  Returns current attribute data associated with the PRC base topology. 
  Attribute data is returned as a reference to an OdPrcAttributeData object, therefore it can be used to set new topology attribute data. 
  */
  OdPrcAttributeData &attributeData();
  
  /** \details
  Returns current attribute data associated with the PRC base topology.
  */
  const OdPrcAttributeData &attributeData() const;
  
  /** \details
  Sets a new identifier for the PRC base topology.
  Identifier is used to reference the topology in the original CAD application and should not be used for referencing topology in the PRC entity.
  
  \param identifier [in] A new identifier value to be set.
  */
  void setIdentifier(OdUInt32 identifier);
  
  /** \details
  Returns the current value of the PRC base topology identifier.
  Identifier is used to reference the topology in the original CAD application and should not be used for referencing topology in a PRC entity.
  */
  OdUInt32 identifier() const;
  
  /** \details 
  Sets a new value of the base information flag.
  The base information flag determines whether the entity has base topology information. If it is equal to true, the information is available; if such information is not available the flag is equal to false.
  
  \param base_information [in] A new value of the base information flag.
  */
  void setBaseInformation(bool base_information);
  
  /** \details
  Returns the current value of the base information flag.
  The base information flag determines whether the entity has base topology information. If it is equal to true, the information is available; if such information is not available the flag is equal to false.
  */
  bool baseInformation() const;
};

typedef OdArray<OdPrcBaseTopology> OdPrcBaseTopologyArray;

#endif // _PRCBASETOPOLOGY_INCLUDED_

