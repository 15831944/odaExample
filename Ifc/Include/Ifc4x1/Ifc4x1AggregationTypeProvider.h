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

// This file is generated automatically.

#ifndef _IFC4X1_INTERNAL_TYPES_H
#define _IFC4X1_INTERNAL_TYPES_H

#include "Ifc4x1BuildOption.h"
#include "daiValueTypes.h"

namespace OdIfc4x1 {

class IfcBSplineSurfaceAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Controlpointslist();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ControlPointsList;
};

class IfcCartesianPointList2DAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Coordlist();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_CoordList;
};

class IfcCartesianPointList3DAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Coordlist();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_CoordList;
};

class IfcColourRgbListAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Colourlist();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ColourList;
};

class IfcDocumentInformationAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Editors();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Editors;
};

class IfcExternalReferenceRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Relatedresourceobjects();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RelatedResourceObjects;
};

class IfcFillAreaStyleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Fillstyles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_FillStyles;
};

class IfcGeometricSetAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Elements();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Elements;
};

class IfcIndexedPolyCurveAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Segments();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Segments;
};

class IfcIndexedPolygonalFaceWithVoidsAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Innercoordindices();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_InnerCoordIndices;
};

class IfcIndexedTriangleTextureMapAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Texcoordindex();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_TexCoordIndex;
};

class IfcIrregularTimeSeriesValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Listvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ListValues;
};

class IfcMaterialClassificationRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Materialclassifications();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_MaterialClassifications;
};

class IfcMaterialLayerWithOffsetsAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Offsetvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_OffsetValues;
};

class IfcMaterialProfileWithOffsetsAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Offsetvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_OffsetValues;
};

class IfcPresentationLayerAssignmentAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Assigneditems();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_AssignedItems;
};

class IfcPresentationStyleAssignmentAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Styles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Styles;
};

class IfcPropertyEnumeratedValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Enumerationvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_EnumerationValues;
};

class IfcPropertyEnumerationAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Enumerationvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_EnumerationValues;
};

class IfcPropertyListValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Listvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ListValues;
};

class IfcPropertyTableValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Definingvalues();
  static const OdDAI::AggregationType* Definedvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_DefiningValues;
  static const OdDAI::AggregationType* m_DefinedValues;
};

class IfcRationalBSplineSurfaceWithKnotsAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Weightsdata();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_WeightsData;
};

class IfcReinforcingBarTypeAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Bendingparameters();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_BendingParameters;
};

class IfcReinforcingMeshTypeAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Bendingparameters();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_BendingParameters;
};

class IfcRelAssociatesAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Relatedobjects();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RelatedObjects;
};

class IfcRelDeclaresAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Relateddefinitions();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RelatedDefinitions;
};

class IfcResourceApprovalRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Relatedresourceobjects();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RelatedResourceObjects;
};

class IfcResourceConstraintRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Relatedresourceobjects();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RelatedResourceObjects;
};

class IfcShellBasedSurfaceModelAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Sbsmboundary();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_SbsmBoundary;
};

class IfcStructuralLoadConfigurationAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Locations();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Locations;
};

class IfcStyledItemAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Styles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Styles;
};

class IfcSurfaceStyleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Styles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Styles;
};

class IfcTableRowAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Rowcells();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RowCells;
};

class IfcTextureVertexListAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Texcoordslist();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_TexCoordsList;
};

class IfcTimeSeriesValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Listvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ListValues;
};

class IfcTriangulatedFaceSetAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Normals();
  static const OdDAI::AggregationType* Coordindex();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Normals;
  static const OdDAI::AggregationType* m_CoordIndex;
};

class IfcTrimmedCurveAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Trim1();
  static const OdDAI::AggregationType* Trim2();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Trim1;
  static const OdDAI::AggregationType* m_Trim2;
};

class IfcUnitAssignmentAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Units();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Units;
};


} // namespace

#endif // _IFC4X1_INTERNAL_TYPES_H

