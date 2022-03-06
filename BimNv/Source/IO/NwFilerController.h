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

#ifndef __DGFILERCONTROLLER_H__
#define __DGFILERCONTROLLER_H__

#include "OdAuditInfo.h"
#include "DbHostAppProgressMeter.h"

class OdNwDatabase;

//----------------------------------------------------------
//
// OdNwFilerController
//
//----------------------------------------------------------
class OdNwFilerController : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdNwFilerController);

  inline void pmStart(const OdString& displayString = OdString::kEmpty);
  inline void pmStop();
  inline void pmMeterProgress();
  inline void pmSetLimit(int max);

  OdAuditInfo* getAuditInfo() const 
  {
    return m_pAuditInfo; 
  }
  OdNwDatabase* getDatabase() const
  {
    return m_pDatabase; 
  }

protected:
  OdNwFilerController();
  ~OdNwFilerController();

protected:

  void setDatabase(OdNwDatabase* pDb);

  void setProgressMeter(OdDbHostAppProgressMeter* pProgressMeter)
  {
    m_pProgressMeter = pProgressMeter; 
  }
  void setAuditInfo(OdAuditInfo* pAuditInfo)
  { 
    m_pAuditInfo = pAuditInfo;
  }

private:
  OdNwDatabase*             m_pDatabase;
  OdDbHostAppProgressMeter* m_pProgressMeter;
  OdAuditInfo*              m_pAuditInfo;
};

typedef OdSmartPtr<OdNwFilerController> OdNwFilerControllerPtr;


//----------------------------------------------------------
//
// OdNwFilerController inline implementations
//
//----------------------------------------------------------
inline void OdNwFilerController::pmStart(const OdString& displayString)
{
  if (m_pProgressMeter)
  {
    m_pProgressMeter->start(displayString);
  }
}

inline void OdNwFilerController::pmStop()
{
  if (m_pProgressMeter)
  {
    m_pProgressMeter->stop();
  }
}

inline void OdNwFilerController::pmMeterProgress()
{
  if(m_pProgressMeter)
  {
    m_pProgressMeter->meterProgress();
  }
}

inline void OdNwFilerController::pmSetLimit(int max)
{
  if (m_pProgressMeter)
  {
    m_pProgressMeter->setLimit(max);
  }
}


#endif // __DGFILERCONTROLLER_H__
