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

// OdIfcProfileDefValidationTask.cpp: implementation of the OdIfcProfileDefValidationTask class.
//
//////////////////////////////////////////////////////////////////////

#include "OdaCommon.h"
#include "RxObjectImpl.h"
#include "IfcProfileDefValidationTask.h"
#include "Common/daiValidationCommon.h"
#include "IfcProfileDef.h"
#include "../DevInclude/Ge/GeValidationUtils.h"
#include "Ge/GeCurveCurveInt3d.h"
#include "daiSet.h"
#include "IfcValidationTaskCommon.h"
#include "daiValidationTask.h"

#define HAS_INTERSECTION "Profile contains intersected curves"
#define HAS_SELF_INTERSECTION "Profile contains self-intersected curve"
#define HAS_OVERLAP "Profile contains overlap"

using namespace OdIfc;

// Uncomment to enable IfcProfileDefValidationTask:
// ODRX_VALIDATION_CONS_DEFINE_MEMBERS(OdIfcProfileDefValidationTask, OdDAI::ModelValidationTask, RXIMPL_CONSTR)
ODRX_CONS_DEFINE_MEMBERS(OdIfcProfileDefValidationTask, OdDAI::ModelValidationTask, RXIMPL_CONSTR)

OdDAI::Logical OdIfc::OdIfcProfileDefValidationTask::validate(OdDAI::OdBaseModelValidationContext* pModelCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams)
{
  OdIfcModelValidationContext* pIfcContext = dynamic_cast<OdIfcModelValidationContext*>(pModelCtx);
  InvalidRxArrayValidationParams* pInvalidIds = new InvalidRxArrayValidationParams;
  OdDAI::OdDAIObjectIdSet* profileIds = pIfcContext->pModel->getEntityExtent("ifcprofiledef");
  OdDAI::IteratorPtr pIt = profileIds->createIterator();
  pIt->beginning();
  while (pIt->next())
  {
    OdDAIObjectId profileId; 
    if (pIt->getCurrentMemberValue() >> profileId)
    {
      OdDAI::ApplicationInstancePtr pProfile = profileId.openObject();
      OdIfcProfileDefPtr pIfcProfile = OdIfcEntity::asCompound(pIfcContext->pFile->get(profileId));
      if (!pIfcProfile.isNull())
      {
        const OdArray<OdGeCurve2dPtrArray>& pGeCurves = pIfcProfile->getContours();
        OdArray<OdGeCurve3dPtrArray> pContours3d(pGeCurves.size());
        for (auto pContour : pGeCurves)
        {
          OdGeCurve3dPtrArray pContour3d(pContour.size());
          for (auto pGeCurve : pContour)
            pContour3d.append(pGeCurve->convertTo3d());
          pContours3d.append(pContour3d);
        }
        for (auto pContour3d : pContours3d)
        {
          OdGeCurve3dArray curves(pContours3d.size());
          OdGeCurve3dPtr pPrevCurve;
          for (auto pCurve : pContour3d)
          {
            if (!pPrevCurve.isNull())
            {
              OdGeCurveCurveInt3d intersector(*pPrevCurve, *pCurve, OdGeVector3d::kZAxis);
              if (intersector.numIntPoints() > 1)
                pInvalidIds->addData(InvalidRxObjectsValidationParams({ profileId.openObject() }, HAS_INTERSECTION, OdDAI::Logical::False));
              if (intersector.overlapCount())
                pInvalidIds->addData(InvalidRxObjectsValidationParams({ profileId.openObject() }, HAS_OVERLAP, OdDAI::Logical::False));

            }
            pPrevCurve = pCurve;
            curves.append(pCurve);
          }
          if (OdGeValidationUtils::CheckSelfIntersectionCurve(curves))
            pInvalidIds->addData(InvalidRxObjectsValidationParams({ profileId.openObject() }, HAS_SELF_INTERSECTION, OdDAI::Logical::False));
        }
      }
    }
  }
  pIfcContext->pFile->unresolveEntities();
  invalidParams = pInvalidIds;
  return invalidParams->invalidItemsCount() ? OdDAI::Logical::False : OdDAI::Logical::True;
}

OdAnsiString OdIfc::OdIfcProfileDefValidationTask::description() const
{
  return "IfcProfileDef instance validation";
}
