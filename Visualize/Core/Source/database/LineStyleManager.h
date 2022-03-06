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

// LineStyleManager.h: interface for the LStyleFilerController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LINESTYLEMANAGER_H_INCLUDED_)
#define _LINESTYLEMANAGER_H_INCLUDED_

#include "OdaCommon.h"
#include "DbDxfLoader.h"
#include "DbFilerController.h"


class LStyleFilerController;
typedef OdSmartPtr<LStyleFilerController> LStyleFilerControllerPtr;

class LStyleFilerController : public OdRxObjectImpl<OdTvDbFilerController>
{
protected:
    
    LStyleFilerController(OdTvDbDxfFiler *pFiler, OdTvDbDatabase *pDb)
    {
        pFiler->setController(this);
        m_SaveType = OdDb::kDxf;
        setDatabase(pDb);
    }
public:

    virtual OdTvDbObjectPtr loadObject(OdUInt64)
    { 
        OdTvDbObjectPtr pObj;
        return pObj; 
    };

    static LStyleFilerControllerPtr createObject(OdTvDbDxfFiler *pFiler, OdTvDbDatabase *pDb)
    {
        return LStyleFilerControllerPtr(new LStyleFilerController(pFiler, pDb), kOdRxObjAttach);
    }

};


#endif // !defined(_LINESTYLEMANAGER_H_INCLUDED_)
