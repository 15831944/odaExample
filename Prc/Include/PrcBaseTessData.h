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

#ifndef _PRCBASETESSDATA_INCLUDED_
#define _PRCBASETESSDATA_INCLUDED_ 
 

#include "RxObject.h"

SMARTPTR(OdPrcBaseTessData);
class OdPrcBaseTessDataImpl;

/** \details
<group PRC_Base_Classes>
Class stores base tessellation information.
*/
class PRC_TOOLKIT OdPrcBaseTessData : public OdRxObject
{
protected:
  OdPrcBaseTessData(OdPrcBaseTessDataImpl *pImpl);

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE_BASE_NOTYPE(OdPrcBaseTessData)
  //DOM-IGNORE-END
  
  /** \details
  Destroys the base tessellation information object.
  */
  virtual ~OdPrcBaseTessData();

  /** \details
  Reads tessellation data from a specified input stream and creates a tessellation object based on entity type read from the input stream.
  
  \param pStream [in] A pointer to an input stream to read data from.
  
  \returns Returns a smart pointer to the created entity.
  */
  static OdPrcBaseTessDataPtr read(OdPrcCompressedFiler *pStream);
  
  /** \details
  Reads tessellation data from a specified input stream and creates a tessellation object array based on entity types read from the input stream.
  
  \param array [out] An array of smart pointers to the created entities.
  \param pStream [in] A pointer to an input stream to read data from.
  */
  static void readArray(OdPrcBaseTessDataPtrArray &array, OdPrcCompressedFiler *pStream);
};

#endif // _PRCBASETESSDATA_INCLUDED_

