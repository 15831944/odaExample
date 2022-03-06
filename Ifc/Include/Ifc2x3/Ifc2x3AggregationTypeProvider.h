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

#ifndef _IFC2X3_INTERNAL_TYPES_H
#define _IFC2X3_INTERNAL_TYPES_H

#include "Ifc2x3BuildOption.h"
#include "daiValueTypes.h"

namespace OdIfc2x3 {

class IfcConstraintClassificationRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Relatedclassifications();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RelatedClassifications;
};

class IfcConstructionMaterialResourceAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Suppliers();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Suppliers;
};

class IfcCostScheduleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Targetusers();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_TargetUsers;
};

class IfcDocumentInformationAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Editors();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Editors;
};

class IfcDraughtingCalloutAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Contents();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Contents;
};

class IfcFillAreaStyleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Fillstyles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_FillStyles;
};

class IfcFillAreaStyleTilesAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Tiles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Tiles;
};

class IfcGeometricSetAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Elements();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Elements;
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

class IfcPresentationLayerAssignmentAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Assigneditems();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_AssignedItems;
};

class IfcPresentationLayerWithStyleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Layerstyles();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_LayerStyles;
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

class IfcShellBasedSurfaceModelAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Sbsmboundary();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_SbsmBoundary;
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

class IfcTextureCoordinateGeneratorAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Parameter();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Parameter;
};

class IfcTimeSeriesReferenceRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Timeseriesreferences();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_TimeSeriesReferences;
};

class IfcTimeSeriesScheduleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Applicabledates();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ApplicableDates;
};

class IfcTimeSeriesValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Listvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ListValues;
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

#endif // _IFC2X3_INTERNAL_TYPES_H

