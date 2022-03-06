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


#ifndef _DBVALUETYPES_H_INCLUDED_
#define _DBVALUETYPES_H_INCLUDED_

#include "DbRootValueTypes.h"
#include "DbDatabase.h"
#include "DbObjectId.h"
#include "CmColor.h"
#include "DbDate.h"
#include "DbBlockTableRecord.h"
#include "DbMLeaderStyle.h"
#include "DbMText.h"
#include "Db2dPolyline.h"
#include "Db3dPolyline.h"
#include "Db3dPolylineVertex.h"
#include "DbLeader.h"
#include "DbTable.h"
#include "DbSpline.h"
#include "DbHelix.h"
#include "DbGeoPositionMarker.h"
#include "DbHatch.h"
#include "DbLight.h"
#include "DbLoftOptions.h"
#include "DbSweepOptions.h"
#include "DbOle2Frame.h"
#include "DbPolygonMesh.h"
#include "DbSection.h"
#include "Db2dVertex.h"
#include "ViewportDefs.h"
#include "DbViewport.h"
#include "DbPlotSettings.h"
#include "DbRenderSettings.h"
#include "DbOle2Frame.h"

/** \details
  This class is a specialization of OdTvDbObjectId for OdTvDbBlockTableRecord.

  \remarks
  An OdTvDbBlockTableRecordId reference to OdTvDbBlockTableRecord for creating a
  ValueType with subproperties.
  Corresponding C++ library: TD_DbEntities

  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbBlockTableRecordId : public OdTvDbObjectId
{
public:

  /** \details
    Default constructor for objects of the OdTvDbBlockTableRecordId class.
  */
  OdTvDbBlockTableRecordId() {}

  /** \details
    Copy constructor for objects of the OdTvDbBlockTableRecordId class. Clones an
    existing instance of the class.

    \param objectId [in] Object to be cloned.
  */
  OdTvDbBlockTableRecordId(
    const OdTvDbObjectId& objectId) : OdTvDbObjectId(objectId) {}

//DOM-IGNORE-BEGIN
  OdTvDbBlockTableRecordId(
    OdDbStub* objectId) : OdTvDbObjectId(objectId) {}
//DOM-IGNORE-END

  /** \details
    Assignment operator.

    \param objectId [in] Object ID to be assigned to this OdTvDbBlockTableRecordId.
  */
  OdTvDbBlockTableRecordId& operator = (
    const OdTvDbBlockTableRecordId& objectId) {
    OdTvDbObjectId::operator= (objectId); return *this;
  }

  /** \details
    Assignment operator.

    \param objectId [in] Object ID to be assigned to this OdTvDbBlockTableRecordId.
  */
  OdTvDbBlockTableRecordId& operator = (
    const OdTvDbObjectId& objectId) {
    OdTvDbObjectId::operator= (objectId); return *this;
  }

//DOM-IGNORE-BEGIN
  OdTvDbBlockTableRecordId& operator = (
    OdDbStub* objectId) {
    m_Id = (OdDbStub*)objectId; return *this;
  }
//DOM-IGNORE-END

  /** \details
    Negative comparison operator.

    \param objectId [in] Object ID to compare with this OdTvDbBlockTableRecordId.

    \returns
    True if object IDs are not equal; false otherwise.
  */
  bool operator != (
    const OdTvDbObjectId& objectId) const {
    return OdTvDbObjectId::operator!= (objectId);
  }

//DOM-IGNORE-BEGIN
  bool operator != (
    OdDbStub* objectId) const {
    return OdTvDbObjectId::operator!= (objectId);
  }
//DOM-IGNORE-END

  /** \details
    Comparison operator.

    \param objectId [in] Object ID to compare with this OdTvDbBlockTableRecordId.

    \returns
    True if object IDs are equal; false otherwise.
  */
  bool operator == (
    const OdTvDbObjectId& objectId) const {
    return OdTvDbObjectId::operator== (objectId);
  }

//DOM-IGNORE-BEGIN
  bool operator == (
    OdDbStub* objectId) const {
    return OdTvDbObjectId::operator== (objectId);
  }
//DOM-IGNORE-END

};

/** \details
  OdRxValueType specialization for 'OdTvDbBlockTableRecordId' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbBlockTableRecordId, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbObjectId' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbObjectId, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvCmColor' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvCmColor, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbSweepOptions' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbSweepOptions, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbDate' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbDate, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdCellRange' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdCellRange, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDb3dPolylineVertexPtr' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDb3dPolylineVertexPtr, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdRectangle3d' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdRectangle3d, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::DuplicateRecordCloning' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::DuplicateRecordCloning, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::LineSpacingStyle' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::LineSpacingStyle, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::JoinStyle' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::JoinStyle, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::EndCaps' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::EndCaps, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::DwgVersion' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::DwgVersion, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::LoftNormalsType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::LoftNormalsType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::MeasurementValue' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::MeasurementValue, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::MaintReleaseVer' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::MaintReleaseVer, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::Visibility' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::Visibility, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::CollisionType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::CollisionType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::Poly2dType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::Poly2dType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::Poly3dType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::Poly3dType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::TableBreakFlowDirection' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::TableBreakFlowDirection, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::TableBreakOption' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::TableBreakOption, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::FlowDirection' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::FlowDirection, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::PolyMeshType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::PolyMeshType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::TextHorzMode' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::TextHorzMode, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::TextVertMode' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::TextVertMode, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::Vertex2dType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::Vertex2dType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::Vertex3dType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::Vertex3dType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::OrthographicView' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::OrthographicView, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdDb::XrefStatus' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdDb::XrefStatus, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbBlockTableRecord::BlockScaling' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbBlockTableRecord::BlockScaling, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::ContentType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::ContentType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::LeaderType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::LeaderType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::TextAngleType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::TextAngleType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::BlockConnectionType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::BlockConnectionType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::DrawLeaderOrderType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::DrawLeaderOrderType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::DrawMLeaderOrderType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::DrawMLeaderOrderType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::TextAttachmentDirection' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::TextAttachmentDirection, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::TextAlignmentType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::TextAlignmentType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::TextAttachmentType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::TextAttachmentType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMLeaderStyle::SegmentAngleType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMLeaderStyle::SegmentAngleType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMText::FlowDirection' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMText::FlowDirection, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMText::AttachmentPoint' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMText::AttachmentPoint, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMText::ColumnType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMText::ColumnType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMTextPtr' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMTextPtr, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLeader::AnnoType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLeader::AnnoType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbSpline::SplineType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbSpline::SplineType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbHelix::ConstrainType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbHelix::ConstrainType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbGeoPositionMarker::OdTextAlignmentType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbGeoPositionMarker::OdTextAlignmentType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbHatch::GradientPatternType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbHatch::GradientPatternType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbHatch::HatchObjectType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbHatch::HatchObjectType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbHatch::HatchStyle' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbHatch::HatchStyle, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbHatch::HatchPatternType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbHatch::HatchPatternType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLight::LampColorType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLight::LampColorType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLight::LampColorPreset' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLight::LampColorPreset, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLight::GlyphDisplayType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLight::GlyphDisplayType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLight::PhysicalIntensityMethod' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLight::PhysicalIntensityMethod, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLoftOptions::NormalOption' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLoftOptions::NormalOption, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbLoftOptions' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbLoftOptions, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbOle2Frame::Type' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbOle2Frame::Type, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbOle2Frame::PlotQuality' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbOle2Frame::PlotQuality, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbSection::State' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbSection::State, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbViewport::ShadePlotType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbViewport::ShadePlotType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbViewport::StandardScaleType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbViewport::StandardScaleType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbPlotSettings::PlotRotation' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbPlotSettings::PlotRotation, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbPlotSettings::ShadePlotResLevel' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbPlotSettings::ShadePlotResLevel, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbPlotSettings::ShadePlotType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbPlotSettings::ShadePlotType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbPlotSettings::PlotPaperUnits' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbPlotSettings::PlotPaperUnits, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbPlotSettings::PlotType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbPlotSettings::PlotType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbPlotSettings::StdScaleType' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbPlotSettings::StdScaleType, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbRenderGlobal::Procedure' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbRenderGlobal::Procedure, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbRenderGlobal::Destination' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbRenderGlobal::Destination, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbMentalRayRenderSettings::ShadowSamplingMultiplier' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbMentalRayRenderSettings::ShadowSamplingMultiplier, DBENT_EXPORT);

/** \details
  OdRxValueType specialization for 'OdTvDbRapidRTRenderSettings::RenderTarget' value type.
*/
ODRX_DECLARE_VALUE_TYPE(OdTvDbRapidRTRenderSettings::RenderTarget, DBENT_EXPORT);


#endif
