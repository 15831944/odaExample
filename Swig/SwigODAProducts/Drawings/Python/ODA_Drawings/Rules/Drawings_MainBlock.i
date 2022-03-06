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

%include "ODA_SimpleTypesPython.i"
%include "ODA_StringsPython.i"
%include "Drawings_SmartPtrList.i"
%include "Drawings_DefaultIgnores.i"
%include "Drawings_RXDirectorList.i"
%include "Drawings_PythonEnumRules.i"
%include "Drawings_Defines.i"
%include "Drawings_OdArrayList.i"

%feature("compactdefaultargs") ExHostAppServices::readFile;

%inline %{
namespace OdDbHistoryInternal {
}
%}

%rename (createPdfImporter) createImporter();
%rename (createDwfImporter) TD_DWF_IMPORT::createImporter();
%rename (createColladaImporter) TD_COLLADA_IMPORT::createImporter();


CHANGE_CTOR(OdVLObject)
CHANGE_CTOR(OdDbEvalGraph)
CHANGE_CTOR(OdDbEvalExpr)
CHANGE_CTOR(OdDbBlockGripExpr)
CHANGE_CTOR(OdDbBlockGrip)
CHANGE_CTOR(OdDbBlockXYGrip)
CHANGE_CTOR(OdDbBlockPolarGrip)
CHANGE_CTOR(OdDbBlockRotationGrip)
CHANGE_CTOR(OdDbBlockLinearGrip)
CHANGE_CTOR(OdDbBlockFlipGrip)
CHANGE_CTOR(OdDbBlockLookupGrip)
CHANGE_CTOR(OdDbBlockAlignmentGrip)
CHANGE_CTOR(OdDbBlockVisibilityGrip)
CHANGE_CTOR(OdDbBlockFlipParameter)
CHANGE_CTOR(OdDbBlockLinearParameter)
CHANGE_CTOR(OdDbBlockLookUpParameter)
CHANGE_CTOR(OdDbBlockPointParameter)
CHANGE_CTOR(OdDbBlockPolarParameter)
CHANGE_CTOR(OdDbBlockRotationParameter)
CHANGE_CTOR(OdDbBlockVisibilityParameter)
CHANGE_CTOR(OdDbBlockMoveAction)
CHANGE_CTOR(OdDbBlockStretchAction)
CHANGE_CTOR(OdDbBlockScaleAction)
CHANGE_CTOR(OdDbBlockRotateAction)
CHANGE_CTOR(OdDbBlockFlipAction)
CHANGE_CTOR(OdDbBlockArrayAction)
CHANGE_CTOR(OdDbBlockLookupAction)
CHANGE_CTOR(OdDbBlockPolarStretchAction)
CHANGE_CTOR(OdDbBlockRepresentationData)
CHANGE_CTOR(OdDbDynamicBlockPurgePreventer)
CHANGE_CTOR(OdDbShHistory)
CHANGE_CTOR(OdDbShBoolean)
CHANGE_CTOR(OdDbShSubentColor)
CHANGE_CTOR(OdDbShSubentMaterial)
CHANGE_CTOR(OdDbShChamfer)
CHANGE_CTOR(OdDbShFillet)
CHANGE_CTOR(OdDbShBox)
CHANGE_CTOR(OdDbShBrep)
CHANGE_CTOR(OdDbShCylinder)
CHANGE_CTOR(OdDbShCone)
CHANGE_CTOR(OdDbShExtrusion)
CHANGE_CTOR(OdDbShLoft)
CHANGE_CTOR(OdDbShPyramid)
CHANGE_CTOR(OdDbShRevolve)
CHANGE_CTOR(OdDbShSphere)
CHANGE_CTOR(OdDbShSweep)
CHANGE_CTOR(OdDbShTorus)
CHANGE_CTOR(OdDbShWedge)
CHANGE_CTOR(OdDbAssocPersSubentManager)
CHANGE_CTOR(OdDbPersSubentManager)

%SPEC_CREATION(ExDbCommandContext, OdDbCommandContext)

%feature("action") OdPdfImport::~OdPdfImport
{
  arg1->release();
}
%feature("action") OdPdfImportModule::~OdPdfImportModule
{
  arg1->release();
}

PROTECTED_DTOR_AUX_PYTHON(OdDbDynBlockReference,OdDbObjectId)
PROTECTED_DTOR_AUX_PYTHON(OdDbDynBlockTableRecord,OdDbObjectId)

%{
typedef OdGiDrawable::DrawableType DrawableType;
typedef OdGiContext::ImageQuality ImageQuality;
typedef OdGiContext::FadingType FadingType;
typedef OdGiContext::PStyleType PStyleType;
typedef OdGiDefaultContext::SolidHatchAsPolygonMode SolidHatchAsPolygonMode;
typedef OdDbRasterVariables::FrameSettings FrameSettings;
%}
