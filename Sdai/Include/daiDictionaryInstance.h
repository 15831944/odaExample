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

#ifndef _DAI_DICTIONARY_INSTANCE_H
#define _DAI_DICTIONARY_INSTANCE_H

#include "OdaCommon.h"
#include "RxDictionary.h"
#include "SharedPtr.h"

#include "daiBuildOptions.h"
#include "daiSDAIInstance.h"

#define STL_USING_MAP
#define STL_USING_SET
#define STL_USING_LIST
#define STL_USING_STRING
#include "OdaSTL.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  The base class for dictionary instances that can be manipulated with the Data Access Interface (DAI).
  */
  class DAI_EXPORT DictionaryInstance : public OdSDAIInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(DictionaryInstance);
    //DOM-IGNORE-END

  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::DictionaryInstance, dictionary instance> object.
  */
  typedef OdSmartPtr<DictionaryInstance> DictionaryInstancePtr;

}

#endif // _DAI_DICTIONARY_INSTANCE_H
