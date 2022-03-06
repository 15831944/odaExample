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

#ifndef _PRCUSERDATA_INCLUDED_
#define _PRCUSERDATA_INCLUDED_ 
 

#include "OdBinaryData.h"

/** \details 
<group PRC_Datatypes_Classes> 

Class implements operations with user defined data. 
*/
class PRC_TOOLKIT OdPrcUserData
{
private:
  OdBitBinaryData m_bitData;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcUserData)
  //DOM-IGNORE-END

  /** \details
  Returns the current binary stream of user defined data.
  The binary stream of user defined data is returned as a reference to an OdBitBinaryData object, therefore it can be used to set a new binary stream.
  */
  OdBitBinaryData &bitData();
  
  /** \details
  Returns the current binary stream of user defined data.
  */
  const OdBitBinaryData &bitData() const;
};

#endif // _PRCUSERDATA_INCLUDED_

