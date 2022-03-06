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

#ifndef _ALIGNMENT_GEOMETRY_BUILDER_H
#define _ALIGNMENT_GEOMETRY_BUILDER_H

#include "IfcBuilder.h"

#include "Ge/GePolyline2d.h"

class OdAlignmentGeometryBuilder
{
  OdDAI::ModelPtr m_model;
  OdDAI::ApplicationInstancePtr m_ctxModel;
  OdDAI::ApplicationInstancePtr m_ctxPlan;

  OdDAI::ApplicationInstancePtr m_alignment;

  OdDAI::ApplicationInstancePtr m_horizontal;
  OdDAI::ApplicationInstancePtr m_vertical;
  OdDAI::ApplicationInstancePtr m_cant;

  OdDAI::ApplicationInstancePtr setRepresentation(OdDAI::ApplicationInstancePtr product)
  {
    OdDAI::ApplicationInstancePtr productDefinitionShape = m_model->createEntityInstance("ifcproductdefinitionshape");
    OdDAIObjectId idProductDefinitionShape = m_model->appendEntityInstance(productDefinitionShape);
    product->putAttr("representation", idProductDefinitionShape);

    return productDefinitionShape;
  }

  OdDAIObjectIds extractRelNests(OdDAI::ApplicationInstancePtr product)
  {
    OdDAIObjectIds related;

    OdDAIObjectIds isNestedBy;
    if (product->getAttr("isnestedby") >> isNestedBy && !isNestedBy.isEmpty())
    {
      OdDAI::ApplicationInstancePtr relNests = isNestedBy[0].openObject();
      if (!relNests.isNull())
      {
        relNests->getAttr("relatedobjects") >> related;
      }
    }

    return related;
  }

  OdDAI::ApplicationInstancePtr createVector(OdDAIObjectId orientation, double magnitude)
  {
    OdDAI::ApplicationInstancePtr vector = m_model->createEntityInstance("ifcvector");
    vector->putAttr("orientation", orientation);
    vector->putAttr("magnitude", magnitude);
    m_model->appendEntityInstance(vector);
    return vector;
  }

  OdDAI::ApplicationInstancePtr createCartesianPoint2d(double x, double y)
  {
    OdDAI::ApplicationInstancePtr cp = m_model->createEntityInstance("ifccartesianpoint");
    OdArray<double> coordinates;
    coordinates.append(x);
    coordinates.append(y);
    cp->putAttr("coordinates", coordinates);
    m_model->appendEntityInstance(cp);
    return cp;
  }

  OdDAI::ApplicationInstancePtr createCartesianPoint3d(double x, double y, double z)
  {
    OdDAI::ApplicationInstancePtr cp = m_model->createEntityInstance("ifccartesianpoint");
    OdArray<double> coordinates;
    coordinates.append(x);
    coordinates.append(y);
    coordinates.append(z);
    cp->putAttr("coordinates", coordinates);
    m_model->appendEntityInstance(cp);
    return cp;
  }

  OdDAI::ApplicationInstancePtr createDirection2d(double x, double y)
  {
    OdDAI::ApplicationInstancePtr dir = m_model->createEntityInstance("ifcdirection");
    OdArray<double> directionRatios;
    directionRatios.append(x);
    directionRatios.append(y);
    dir->putAttr("directionratios", directionRatios);
    m_model->appendEntityInstance(dir);
    return dir;
  }

  OdDAI::ApplicationInstancePtr createDirection3d(double x, double y, double z)
  {
    OdDAI::ApplicationInstancePtr dir = m_model->createEntityInstance("ifcdirection");
    OdArray<double> directionRatios;
    directionRatios.append(x);
    directionRatios.append(y);
    directionRatios.append(z);
    dir->putAttr("directionratios", directionRatios);
    m_model->appendEntityInstance(dir);
    return dir;
  }

  OdDAI::ApplicationInstancePtr createAxis2Placement2d(const OdGePoint2d &location, const OdGeVector2d &refRirection)
  {
    OdDAI::ApplicationInstancePtr placement = m_model->createEntityInstance("ifcaxis2placement2d");
    placement->putAttr("location", OdDAIObjectId(createCartesianPoint2d(location.x, location.y)->id()));
    placement->putAttr("refdirection", OdDAIObjectId(createDirection2d(refRirection.x, refRirection.y)->id()));
    m_model->appendEntityInstance(placement);
    return placement;
  }

  OdDAI::ApplicationInstancePtr createAxis2Placement3d(const OdGePoint3d &location, const OdGeVector3d *axis, const OdGeVector3d *refDirection)
  {
    OdDAI::ApplicationInstancePtr placement = m_model->createEntityInstance("ifcaxis2placement3d");
    placement->putAttr("location", OdDAIObjectId(createCartesianPoint3d(location.x, location.y, location.z)->id()));
    if (axis)
      placement->putAttr("axis", OdDAIObjectId(createDirection3d(axis->x, axis->y, axis->z)->id()));
    if (refDirection)
      placement->putAttr("refdirection", OdDAIObjectId(createDirection3d(refDirection->x, refDirection->y, refDirection->z)->id()));
    m_model->appendEntityInstance(placement);
    return placement;
  }

public:

  OdAlignmentGeometryBuilder(OdDAI::ModelPtr model)
    : m_model(model)
  {
    OdDAI::OdDAIObjectIdSet *contexts = m_model->getEntityExtent("ifcgeometricrepresentationcontext");
    ODA_ASSERT(!contexts->isNil());
    const OdDAIObjectIds &ids = contexts->getArray();
    for (const auto &id : ids)
    {
      OdDAI::ApplicationInstancePtr ctx = id.openObject();
      OdAnsiString identifier;
      ctx->getAttr("contextidentifier") >> identifier;
      OdAnsiString type;
      ctx->getAttr("contexttype") >> type;

      if (type.iCompare("plan") == 0)
        m_ctxPlan = ctx;
      else
      if (type.iCompare("model") == 0)
        m_ctxModel = ctx;
    }
  }

  OdDAI::ApplicationInstancePtr processHorizontalSegment(const OdDAI::ApplicationInstance *alignmentHorizontalSegment);

  OdDAI::ApplicationInstancePtr processVerticalSegment(const OdDAI::ApplicationInstance *alignmentVerticalSegment);

  OdDAI::ApplicationInstancePtr processCantSegment(const OdDAI::ApplicationInstance *alignmentCantSegment, double railHeadDistance, bool last);

  OdDAI::ApplicationInstancePtr processHorizontal()
  {
    if (m_horizontal.isNull())
      return OdDAI::ApplicationInstancePtr();

    OdDAIObjectIds segments = extractRelNests(m_horizontal);
    if (segments.isEmpty())
    {
      ODA_ASSERT(!segments.isEmpty());
      return OdDAI::ApplicationInstancePtr();
    }

    OdDAI::ApplicationInstancePtr productDefinitionShape = setRepresentation(m_horizontal);
    OdDAIObjectIds representations;

    OdDAI::ApplicationInstancePtr shapeRepresentation = m_model->createEntityInstance("ifcshaperepresentation");
    OdDAIObjectId idShapeRepresentation = m_model->appendEntityInstance(shapeRepresentation);
    representations.append(idShapeRepresentation);
    productDefinitionShape->putAttr("representations", representations);

    shapeRepresentation->putAttr("contextofitems", OdDAIObjectId(m_ctxModel->id()));
    shapeRepresentation->putAttr("representationidentifier", (const char*)"Axis");
    shapeRepresentation->putAttr("representationtype", (const char*)"Curve");
    OdDAIObjectIds items;

    OdDAI::ApplicationInstancePtr compositeCurve = m_model->createEntityInstance("ifccompositecurve");
    OdDAIObjectId idCompositeCurve = m_model->appendEntityInstance(compositeCurve);
    items.append(idCompositeCurve);
    shapeRepresentation->putAttr("items", items);

    compositeCurve->putAttr("selfintersect", OdDAI::Logical::False);
    OdDAI::OdDAIObjectIdList *compositeCurveSegments = nullptr;
    compositeCurve->getAttr("segments") >> compositeCurveSegments;
    ODA_ASSERT(compositeCurveSegments->isNil());
    compositeCurveSegments->createEmpty();

    for (const auto &idSegment : segments)
    {
      if (idSegment.isValid())
      {
        OdDAI::ApplicationInstancePtr alignmentSegment = idSegment.openObject();

        OdDAIObjectId idAlignmentHorizontalSegment;
        alignmentSegment->getAttr("designparameters") >> idAlignmentHorizontalSegment;
        if (idAlignmentHorizontalSegment.isValid())
        {
          OdDAI::ApplicationInstancePtr alignmentHorizontalSegment = idAlignmentHorizontalSegment.openObject();
          OdDAI::ApplicationInstancePtr curveSegment = processHorizontalSegment(alignmentHorizontalSegment);
          if (!curveSegment.isNull())
          {
            compositeCurveSegments->addByIndex(
              compositeCurveSegments->getMemberCount(),
              curveSegment->id()
            );
          }
        }
        else
        {
          ODA_ASSERT_ONCE(idAlignmentHorizontalSegment.isValid());
        }
      }
      else
      {
        ODA_ASSERT_ONCE(idSegment.isValid());
      }
    }

    return compositeCurve;
  }

  OdDAI::ApplicationInstancePtr processVertical(const OdDAI::ApplicationInstance *baseCurve)
  {
    if (m_vertical.isNull())
      return OdDAI::ApplicationInstancePtr();

    OdDAIObjectIds segments = extractRelNests(m_vertical);
    if (segments.isEmpty())
    {
      ODA_ASSERT(!segments.isEmpty());
      return OdDAI::ApplicationInstancePtr();
    }

    OdDAI::ApplicationInstancePtr productDefinitionShape = setRepresentation(m_vertical);
    OdDAIObjectIds representations;

    OdDAI::ApplicationInstancePtr shapeRepresentation = m_model->createEntityInstance("ifcshaperepresentation");
    OdDAIObjectId idShapeRepresentation = m_model->appendEntityInstance(shapeRepresentation);
    representations.append(idShapeRepresentation);
    productDefinitionShape->putAttr("representations", representations);

    shapeRepresentation->putAttr("contextofitems", OdDAIObjectId(m_ctxModel->id()));
    shapeRepresentation->putAttr("representationidentifier", (const char*)"Axis");
    shapeRepresentation->putAttr("representationtype", (const char*)"Curve");
    OdDAIObjectIds items;

    OdDAI::ApplicationInstancePtr gradientCurve = m_model->createEntityInstance("ifcgradientcurve");
    OdDAIObjectId idCompositeCurve = m_model->appendEntityInstance(gradientCurve);
    items.append(idCompositeCurve);
    shapeRepresentation->putAttr("items", items);

    gradientCurve->putAttr("basecurve", OdDAIObjectId(baseCurve->id()));
    gradientCurve->putAttr("selfintersect", OdDAI::Logical::False);

    OdDAI::OdDAIObjectIdList *gradientCurveSegments = nullptr;
    gradientCurve->getAttr("segments") >> gradientCurveSegments;
    ODA_ASSERT(gradientCurveSegments->isNil());
    gradientCurveSegments->createEmpty();

    for (const auto &idSegment : segments)
    {
      if (idSegment.isValid())
      {
        OdDAI::ApplicationInstancePtr alignmentSegment = idSegment.openObject();

        OdDAIObjectId idAlignmentVerticalSegment;
        alignmentSegment->getAttr("designparameters") >> idAlignmentVerticalSegment;
        if (idAlignmentVerticalSegment.isValid())
        {
          OdDAI::ApplicationInstancePtr alignmentVerticalSegment = idAlignmentVerticalSegment.openObject();
          OdDAI::ApplicationInstancePtr curveSegment = processVerticalSegment(alignmentVerticalSegment);
          if (!curveSegment.isNull())
          {
            gradientCurveSegments->addByIndex(
              gradientCurveSegments->getMemberCount(),
              curveSegment->id()
            );
          }
        }
        else
        {
          ODA_ASSERT_ONCE(idAlignmentVerticalSegment.isValid());
        }
      }
      else
      {
        ODA_ASSERT_ONCE(idSegment.isValid());
      }
    }

    // Seems vertical alignment can not be closed!
    OdDAIObjectId idLastSegment = gradientCurveSegments->getByIndex<OdDAIObjectId>(gradientCurveSegments->getMemberCount() - 1);
    OdDAI::ApplicationInstancePtr lastSegment = idLastSegment.openObject();
    lastSegment->putAttr("transition", (const char *)"DISCONTINUOUS");

    return gradientCurve;
  }

  OdDAI::ApplicationInstancePtr processCant(OdDAI::ApplicationInstance *baseCurve)
  {
    if (m_cant.isNull())
      return OdDAI::ApplicationInstancePtr();

    double railHeadDistance = 0.;
    m_cant->getAttr("railheaddistance") >> railHeadDistance;

    OdDAIObjectIds segments = extractRelNests(m_cant);
    if (segments.isEmpty())
    {
      ODA_ASSERT(!segments.isEmpty());
      return OdDAI::ApplicationInstancePtr();
    }

    OdDAI::ApplicationInstancePtr productDefinitionShape = setRepresentation(m_cant); // m_alignment
    OdDAIObjectIds representations;

    OdDAI::ApplicationInstancePtr shapeRepresentation = m_model->createEntityInstance("ifcshaperepresentation");
    OdDAIObjectId idShapeRepresentation = m_model->appendEntityInstance(shapeRepresentation);
    representations.append(idShapeRepresentation);
    productDefinitionShape->putAttr("representations", representations);

    shapeRepresentation->putAttr("contextofitems", OdDAIObjectId(m_ctxModel->id()));
    shapeRepresentation->putAttr("representationidentifier", (const char*)"Axis");
    shapeRepresentation->putAttr("representationtype", (const char*)"Curve");
    OdDAIObjectIds items;

    OdDAI::ApplicationInstancePtr segmentedReferenceCurve = m_model->createEntityInstance("ifcsegmentedreferencecurve");
    OdDAIObjectId idSegmentedReferenceCurve = m_model->appendEntityInstance(segmentedReferenceCurve);
    items.append(idSegmentedReferenceCurve);
    shapeRepresentation->putAttr("items", items);

    segmentedReferenceCurve->putAttr("basecurve", OdDAIObjectId(baseCurve->id()));
    segmentedReferenceCurve->putAttr("selfintersect", OdDAI::Logical::False);

    OdDAI::OdDAIObjectIdList *segmentedReferenceCurveSegments = nullptr;
    segmentedReferenceCurve->getAttr("segments") >> segmentedReferenceCurveSegments;
    ODA_ASSERT(segmentedReferenceCurveSegments->isNil());
    segmentedReferenceCurveSegments->createEmpty();

    for (const auto &idSegment : segments)
    {
      if (idSegment.isValid())
      {
        OdDAI::ApplicationInstancePtr alignmentSegment = idSegment.openObject();

        OdDAIObjectId idAlignmentCantSegment;
        alignmentSegment->getAttr("designparameters") >> idAlignmentCantSegment;
        if (idAlignmentCantSegment.isValid())
        {
          OdDAI::ApplicationInstancePtr alignmentCantSegment = idAlignmentCantSegment.openObject();
          OdDAI::ApplicationInstancePtr curveSegment = processCantSegment(alignmentCantSegment, railHeadDistance, idSegment == segments.last());
          if (!curveSegment.isNull())
          {
            segmentedReferenceCurveSegments->addByIndex(
              segmentedReferenceCurveSegments->getMemberCount(),
              curveSegment->id()
            );
          }
        }
        else
        {
          ODA_ASSERT_ONCE(idAlignmentCantSegment.isValid());
        }
      }
      else
      {
        ODA_ASSERT_ONCE(idSegment.isValid());
      }
    }

    return segmentedReferenceCurve;
  }

  bool process(OdDAI::ApplicationInstancePtr alignment, OdDAI::ApplicationInstancePtr &resultCurve, bool withCant = true)
  {
    if (alignment.isNull())
    {
      return false;
    }

    if (!alignment->isKindOf("ifcalignment"))
    {
      return false;
    }

    if (m_model.get() != alignment->owningModel())
    {
      return false;
    }

    m_alignment = alignment;

    OdDAIObjectIds related = extractRelNests(m_alignment);
    for (const auto &part : related)
    {
      OdDAI::ApplicationInstancePtr inst = part.openObject();
      if (inst->isKindOf("ifcalignmenthorizontal"))
        m_horizontal = inst;
      else
        if (inst->isKindOf("ifcalignmentvertical"))
          m_vertical = inst;
        else
          if (inst->isKindOf("ifcalignmentcant"))
            m_cant = inst;
    }

    if (m_horizontal.isNull())
    {
      ODA_ASSERT(!m_horizontal.isNull());
      return false;
    }

    OdDAI::ApplicationInstancePtr compositeCurve = processHorizontal();
    if (compositeCurve.isNull())
    {
      ODA_ASSERT(!compositeCurve.isNull());
      return false;
    }

    OdDAI::ApplicationInstancePtr gradientCurve = processVertical(compositeCurve);
    OdDAI::ApplicationInstancePtr segmentedReferenceCurve;
    if (withCant)
      segmentedReferenceCurve = processCant(gradientCurve.isNull() ? compositeCurve : gradientCurve);

    if (!segmentedReferenceCurve.isNull())
      resultCurve = segmentedReferenceCurve;
    else
      if (!gradientCurve.isNull())
        resultCurve = gradientCurve;
      else
        resultCurve = compositeCurve;
    return !resultCurve.isNull();
  }
};


#endif // _ALIGNMENT_GEOMETRY_BUILDER_H
