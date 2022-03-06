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

#include "IfcCompositeCurveConsistencyValidationTask.h"

#include "daiValidationCommon.h"
#include "IfcEntity.h"
#include "IfcCurveSegment.h"
#include "IfcFile.h"
#include "IfcValidationTaskCommon.h"

#define BASE_COMPOSITE_CURVE_NAME "IfcCompositeCurve"
#define DEFAULT_TOLERANCE OdGeTol(1.e-6)

#define DISCONTINUOUS_ERROR "DISCONTINUOUS transition is permitted only at the last curve segment"
#define SEGMENTS_BORDER_ERROR "Segments end and start points are not equal"
#define SEGMENTS_TANGENTS_ERROR "Tangents at the segments end and start points are not codirectional"
#define NONDISCONTINUOUS_AT_THE_END_WARNING "Warning: non-DISCONTINUOUS transition at the end point indicates that the curve is closed"

using namespace OdIfc;
using namespace OdDAI;

ODRX_VALIDATION_CONS_DEFINE_MEMBERS(CompositeCurveConsistencyValidationTask, OdDAI::ExtentValidationTask, RXIMPL_CONSTR);

/// <summary>
/// TO DO: Add equality of curvatures at extreme points for CONTSAMEGRADIENTSAMECURVATURE. Need curvature in point
/// TO DO: validation of the last segment. Need drawing closed curves
/// </summary>

namespace {
  struct SegmentExtremePoints
  {
    OdIfcEntityPtr pSegmentEntity;

    OdGePoint3d startPoint;
    OdGePoint3d endPoint;

    OdGeVector3d startTangent;
    OdGeVector3d endTangent;
  };

  void unresolveEntity(OdIfcEntityPtr pEntity);
  void checkUnresolveAttrs(OdIfcEntityPtr pEntity, Entity* pInstance)
  {
    const AttributeSet& attributeSet = (pInstance)->attributes();

    if (attributeSet.getMemberCount() > 0)
    {
      const OdArray<AttributePtr>& attributes = attributeSet.getArray();
      for (OdArray<AttributePtr>::const_iterator it = attributes.begin(); it < attributes.end(); ++it)
      {
        ExplicitAttributePtr explicitAttr = ExplicitAttribute::cast(*it);

        if (!explicitAttr.isNull())
        {
          BaseTypePtr baseType = explicitAttr->domain();
          if (!pEntity->testAttr(explicitAttr->name()))
            continue;

          Select* select = nullptr;
          if (baseType->isNamedType())
          {
            NamedTypePtr namedType = baseType->namedType();

            EntityPtr entityCheck = Entity::cast(namedType);
            if (!entityCheck.isNull())
            {
              OdDAIObjectId id;
              if (pEntity->getAttr(explicitAttr->name()) >> id)
              {
                unresolveEntity(id.openObject());
                continue;
              }
            }

            DefinedTypePtr defType = DefinedType::cast(namedType);
            if (!defType.isNull())
            {
              UnderlyingTypePtr underlyingType = defType->domain();
              if (underlyingType->isConstructedType())
              {
                ConstructedTypePtr constructedType = underlyingType->constructedType();
                if (constructedType->isSelectType())
                {
                  SelectTypePtr selectType = constructedType->selectType();
                  OdDAIObjectId id;
                  if (pEntity->getAttr(explicitAttr->name()) >> id)
                  {
                    unresolveEntity(id.openObject());
                    continue;
                  }
                }
              }
            }
          }
          else if (baseType->isAggregationType())
          {
            AggregationTypePtr aggregationType = baseType->aggregationType();
            BaseTypePtr baseAggrType = aggregationType->elementType();
            if (baseAggrType->isNamedType())
            {
              NamedTypePtr namedType = baseAggrType->namedType();

              EntityPtr entityCheck = Entity::cast(namedType);
              if (!entityCheck.isNull())
              {
                OdDAIObjectIds ids;
                if (pEntity->getAttr(explicitAttr->name()) >> ids)
                {
                  for (const auto& id : ids)
                    unresolveEntity(id.openObject());
                  continue;
                }
              }
            }
            else if (baseAggrType->isAggregationType())
            {
              ODA_ASSERT_ONCE(!"Unresolving of AggregationTypes inside AggregationType is unsupporting yet");
              continue;
            }
          }
        }
      }
    }
  }

  void unresolveEntity(OdIfcEntityPtr pEntity)
  {
    pEntity->unresolve();

    Entity* pInstance = pEntity->getInstanceType();
    checkUnresolveAttrs(pEntity, pInstance);

    const OdArray<Entity*>& supertypes = pInstance->supertypes().getArray();
    for (OdArray<Entity*>::const_iterator it = supertypes.begin(); it < supertypes.end(); ++it)
    {
      checkUnresolveAttrs(pEntity , *it);
    }
  }

  bool getCurveData(OdDAIObjectId* id, OdIfcFile* file, SegmentExtremePoints* segment)
  {
    segment->pSegmentEntity = id->openObject();

    if (segment->pSegmentEntity.isNull())
      return false;

    bool isAlreadyResolved = false;
    if (segment->pSegmentEntity->resolved() == kUnresolved)
      file->get(*id);
    else
      isAlreadyResolved = true;

    OdIfc::OdIfcCompoundPtr compound = OdIfcEntity::asCompound(segment->pSegmentEntity);
    if (compound.isNull())
    {
      ODA_ASSERT_ONCE(!compound.isNull());
      return false;
    }
    OdIfc::OdIfcSegmentPtr curveSegment = OdIfcSegment::cast(compound);

    if (curveSegment.isNull())
    {
      ODA_ASSERT_ONCE(!curveSegment.isNull());
      return false;
    }

    const OdGeCurve3d* geCurve = curveSegment->getGeCurve();

    OdGeInterval interval;
    geCurve->getInterval(interval);

    OdGeVector3dArray tangents;
    segment->startPoint = geCurve->evalPoint(interval.lowerBound(), 1, tangents);
    segment->startTangent = tangents.first();
    tangents.clear();
    segment->endPoint = geCurve->evalPoint(interval.upperBound(), 1, tangents);
    segment->endTangent = tangents.first();

//    ODA_ASSERT_ONCE(geCurve->hasStartPoint(startPoint));
//    ODA_ASSERT_ONCE(geCurve->hasEndPoint(endPoint));

    if (!isAlreadyResolved)
    {
      unresolveEntity(segment->pSegmentEntity);
//      segment->pSegmentEntity->unresolve();
    }
    return true;
  }
}

OdIfc::CompositeCurveConsistencyValidationTask::CompositeCurveConsistencyValidationTask()
{
  m_extentName = BASE_COMPOSITE_CURVE_NAME;
}

OdDAI::Logical CompositeCurveConsistencyValidationTask::validate(OdDAI::OdBaseInstanceValidationContext* pInstanceCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams)
{
  InvalidRxArrayValidationParams* invalidInstances = new InvalidRxArrayValidationParams();
  invalidParams = invalidInstances;

  OdIfcInstanceValidationContext* pIfcCtx = dynamic_cast<OdIfcInstanceValidationContext*>(pInstanceCtx);

  if (!pIfcCtx)
    return Logical::False;

    OdDAIObjectIds segmentsIds;
    if (!(pIfcCtx->pInstance->getAttr("segments") >> segmentsIds))
    {
      ODA_ASSERT_ONCE(!"Error while processing segments ids!");
      return Logical::False;
    }
    if (segmentsIds.size() > 1)
    {
      OdSharedPtr<SegmentExtremePoints> pSegmentFirst = new SegmentExtremePoints();

      if (!getCurveData(segmentsIds.begin(), pIfcCtx->pFile, pSegmentFirst))
      {
        ODA_ASSERT_ONCE(!"Error while processing segments data!");
        return Logical::False;
      }
      for (auto seg = segmentsIds.begin() + 1; seg != segmentsIds.end(); ++seg)
      {
        ApplicationInstancePtr secondSeg = seg->getNested();
        OdAnsiString transition;
        if(!(pSegmentFirst->pSegmentEntity->getAttr("transition")>> transition))
        {
          ODA_ASSERT_ONCE(!"Error while processing transition!");
        }
        else if (transition == "DISCONTINUOUS")
        {
          if (!getCurveData(seg, pIfcCtx->pFile, pSegmentFirst))
          {
            ODA_ASSERT_ONCE(!"Error while processing segments data!");
            break;
          }
          invalidInstances->addData(InvalidRxObjectsValidationParams({ seg->getNested() }, DISCONTINUOUS_ERROR, Logical::False));
          continue;
        }

        OdSharedPtr<SegmentExtremePoints> pSegmentSecond = new SegmentExtremePoints();
        if (!getCurveData(seg, pIfcCtx->pFile, pSegmentSecond))
        {
          ODA_ASSERT_ONCE(!"Error while processing segments data!");
          break;
        }

        if (!pSegmentFirst->endPoint.isEqualTo(pSegmentSecond->startPoint, DEFAULT_TOLERANCE))
        {
          invalidInstances->addData(InvalidRxObjectsValidationParams({ (seg - 1)->getNested(), seg->getNested() }, SEGMENTS_BORDER_ERROR, Logical::False));
        }
        if (transition != "CONTINUOUS")
        {
          if (!pSegmentFirst->endTangent.isCodirectionalTo(pSegmentSecond->startTangent, DEFAULT_TOLERANCE))
          {
            invalidInstances->addData(InvalidRxObjectsValidationParams({ (seg - 1)->getNested(), seg->getNested() }, SEGMENTS_TANGENTS_ERROR, Logical::False));
          }
        }

        pSegmentFirst = pSegmentSecond;
      }

      OdAnsiString transition;
      if (!(pSegmentFirst->pSegmentEntity->getAttr("transition") >> transition))
      {
        ODA_ASSERT_ONCE(!"Error while processing transition!");
      }
      else if (transition != "DISCONTINUOUS")
      {
        invalidInstances->addData(InvalidRxObjectsValidationParams({ segmentsIds.last().getNested() }, NONDISCONTINUOUS_AT_THE_END_WARNING, Logical::Unknown));
        if (invalidInstances->invalidItemsCount() == 1)
          return Logical::Unknown;
      }
    }
    else if (segmentsIds.size() == 1)
    {
      ApplicationInstancePtr pSegment = segmentsIds.begin()->openObject();

      OdAnsiString transition;
      if (!(pSegment->getAttr("transition") >> transition))
      {
        ODA_ASSERT_ONCE(!"Error while processing transition!");
      }
      else if (transition != "DISCONTINUOUS")
      {
        invalidInstances->addData(InvalidRxObjectsValidationParams({ segmentsIds.last().getNested() }, NONDISCONTINUOUS_AT_THE_END_WARNING, Logical::Unknown));
        if (invalidInstances->invalidItemsCount() == 1)
          return Logical::Unknown;
      }
    }

  if (invalidInstances->invalidItemsCount() > 0)
    return Logical::False;
  return Logical::True;
}

OdAnsiString CompositeCurveConsistencyValidationTask::description() const
{
  return "Composite curve segments consistency validation";
}
