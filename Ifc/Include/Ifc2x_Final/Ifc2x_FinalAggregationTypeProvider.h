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

#ifndef _IFC2X_FINAL_INTERNAL_TYPES_H
#define _IFC2X_FINAL_INTERNAL_TYPES_H

#include "Ifc2x_FinalBuildOption.h"
#include "daiValueTypes.h"

namespace OdIfc2x_final {

class IfcDocumentInformationAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Editors();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Editors;
};

class IfcGeometricSetAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Elements();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Elements;
};

class IfcShellBasedSurfaceModelAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Sbsmboundary();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_SbsmBoundary;
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

class IfcMaterialClassificationRelationshipAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Materialclassifications();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_MaterialClassifications;
};

class IfcUnitAssignmentAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Units();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Units;
};

class IfcPropertyEnumeratedValueAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Enumerationvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_EnumerationValues;
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

class IfcPropertyEnumerationAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Enumerationvalues();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_EnumerationValues;
};

class IfcTableRowAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Rowcells();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_RowCells;
};

class IfcSurfaceStyleUsageAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Appliedto();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_AppliedTo;
};

class IfcTaskAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Milestones();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Milestones;
};

class IfcAssetAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Assetrisks();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_AssetRisks;
};

class IfcCostScheduleAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Approvedby();
  static const OdDAI::AggregationType* Targetusers();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_ApprovedBy;
  static const OdDAI::AggregationType* m_TargetUsers;
};

class IfcProjectOrderAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Issuedto();
  static const OdDAI::AggregationType* Additionalcontacts();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_IssuedTo;
  static const OdDAI::AggregationType* m_AdditionalContacts;
};

class IfcWorkOrderAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Workorderrisktype();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_WorkOrderRiskType;
};

class IfcCMDocPackageAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Authors();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Authors;
};

class IfcConstructionMaterialResourceAggregationTypeProvider
{
public: 
  static const OdDAI::AggregationType* Suppliers();
  static void uninitProvider();
private: 
  static const OdDAI::AggregationType* m_Suppliers;
};


} // namespace

#endif // _IFC2X_FINAL_INTERNAL_TYPES_H

