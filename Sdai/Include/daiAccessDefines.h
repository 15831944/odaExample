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

#ifndef _DAI_ACCESSS_DEFINES_H_
#define _DAI_ACCESSS_DEFINES_H_

#include "daiModel.h"
#include "daiError/daiException.h"

namespace OdDAI
{
  enum NullModelAction
  {
    exceptionAction,
    assertApproveAccessAction,
    silentApproveAccessAction,
  };


  inline void checkReadMode(const Model* model, const char* functionName, NullModelAction nullModelAction = exceptionAction)
  {
    if (model == NULL)
    {
      switch (nullModelAction)
      {
        case exceptionAction:
        {
          throw DaiException(sdaiMO_NVLD, "SDAI-model invalid", functionName);
        }
        break;
        case assertApproveAccessAction:
        {
          ODA_ASSERT_ONCE(0 && "Model is null. Abnoraml situation. Try to fix it yourself.");
          return;
        }
        break;
        case silentApproveAccessAction:
        {
          return;
        }
        break;
      }
    }

    if (model->mode() == Access_type_unset)
    {
      throw DaiException(sdaiMX_NDEF, "SDAI-model access not defined", functionName);
    }
  }

  inline void checkWriteMode(const Model* model, const char* functionName, NullModelAction nullModelAction = exceptionAction)
  {
    if (model == nullptr)
    {
      switch (nullModelAction)
      {
        case exceptionAction:
        {
          throw DaiException(sdaiMO_NVLD, "SDAI-model invalid", functionName);
        }
        break;
        case assertApproveAccessAction:
        {
          ODA_ASSERT_ONCE(0 && "Model is null. Abnoraml situation. Try to fix it yourself.");
          return;
        }
        break;
        case silentApproveAccessAction:
        {
          return;
        }
        break;
      }
    }

    if (model->mode() != sdaiRW)
    {
      throw DaiException(sdaiMX_NRW, "SDAI-model access not read-write", functionName);
    }
  }


  inline void checkReadModePtr(const ModelPtr& model, const char* functionName, NullModelAction modelAction = exceptionAction)
  {
    checkReadMode(model.get(), functionName, modelAction);
  }

  inline void checkWriteModePtr(const ModelPtr& model, const char* functionName, NullModelAction modelAction = exceptionAction)
  {
    checkWriteMode(model.get(), functionName, modelAction);
  }

#define DAI_ENTITY_ACCESSORS_GET_CHECK() checkReadModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_ACCESSORS_SET_CHECK() checkWriteModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)

#define DAI_ENTITY_GET_ATTR_CHECK()  checkReadModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_PUT_ATTR_CHECK()  checkWriteModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_TEST_ATTR_CHECK() checkReadModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_UNSET_ATTR_CHECK()  checkWriteModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)

#define DAI_ENTITY_GET_ATTR_DEF_CHECK()  //checkReadModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_PUT_ATTR_DEF_CHECK()  checkWriteModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_TEST_ATTR_DEF_CHECK() //checkReadModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_UNSET_ATTR_DEF_CHECK()  checkWriteModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)

#define DAI_ENTITY_OUT_FIELDS_CHECK() checkReadModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)
#define DAI_ENTITY_IN_FIELDS_CHECK() checkWriteModePtr(owningModel(), TD_FUNC, silentApproveAccessAction)

#define DAI_ENTITY_SET_INVERSE_COUNTER_PARTS_CHECK() checkWriteModePtr(owningModel(), TD_FUNC, assertApproveAccessAction)

#define DAI_MODEL_TRY_READ()  checkReadMode(this, TD_FUNC)
#define DAI_MODEL_TRY_WRITE()  checkWriteMode(this, TD_FUNC)
}


#endif 

