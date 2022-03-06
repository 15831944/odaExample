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

#ifndef _PRCREFERENCEDATA_INCLUDED_
#define _PRCREFERENCEDATA_INCLUDED_ 
 

#include "PrcObjectId.h"

/** \details 
<group PRC_Miscellaneous_Classes>

Class representing a reference entity. 
*/
class PRC_TOOLKIT OdPrcReferenceData
{
private:
  // ReferenceOnTopology
  // Represents a topological entity's reference. 
  // In current version of PRC this is a reference to a face of the body 
  OdPrcObjectId   m_referenceTopology; // object id of body that has referenced topology
  OdUInt32Array   m_indexes;

  // reference of PRC Base
  OdPrcObjectId   m_referencePRCBase;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcReferenceData)
  //DOM-IGNORE-END

  /** \details
  Returns the current identifier of the reference to topology data.
  The identifier of the reference to topology data is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a new identifier of the reference.
  */
  OdPrcObjectId &referenceOnTopology (void);
  
   /** \details
  Returns the current identifier of the reference to topology data.
  */
  const OdPrcObjectId &referenceOnTopology (void) const;

  /** \details
  Returns the current indexes array.
  */
  const OdUInt32Array & indexes() const;

  /** \details
  Returns the current indexes array.
  Indexes array is returned as a reference to an OdUInt32Array object, therefore it can be used to set a new indexes array.
  */
  OdUInt32Array & indexes();

  /** \details
  Returns the current identifier of the reference to base body data.
  The identifier of the reference to base body data is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a new identifier of the reference.
  */
  OdPrcObjectId &referenceOnPRCBase (void);

  /** \details
  Returns the current identifier of the reference to base body data.
  */
  const OdPrcObjectId &referenceOnPRCBase (void) const;
};

typedef OdArray<OdPrcReferenceData> OdPrcReferenceDataArray;

#endif // _PRCREFERENCEDATA_INCLUDED_

