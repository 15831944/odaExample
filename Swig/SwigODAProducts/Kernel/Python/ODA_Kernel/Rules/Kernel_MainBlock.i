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
%include "Kernel_OdRxObjectImplTemplates.i"
%include "Kernel_SmartPtrList.i"
%include "Kernel_TPtrList.i"
%include "Kernel_DefaultIgnores.i"
%include "Kernel_RXDirectorList.i"
%include "Kernel_PythonEnumRules.i"
%include "Kernel_Defines.i"
%include "Kernel_OdArrayList.i"

%rename(OdGiHlrResults_Data) OdGiHlrResults::Data;
%rename(OdGiPlanarClipBoundary_ClipPlane) OdGiPlanarClipBoundary::ClipPlane;

%{
typedef OdGiSubEntityTraits::ShadowFlags ShadowFlags;
typedef OdGiSubEntityTraits::SelectionFlags SelectionFlags;

typedef OdGiVisualStyle::Type Type;
typedef OdGiVisualStyleProperties::Property Property;
typedef OdGiVisualStyleOperations::Operation Operation;

typedef OdGiFaceStyle::LightingModel LightingModel;
typedef OdGiFaceStyle::LightingQuality LightingQuality;
typedef OdGiFaceStyle::FaceColorMode FaceColorMode;
typedef OdGiFaceStyle::FaceModifier FaceModifier;

typedef OdGiEdgeStyle::EdgeModel EdgeModel;
typedef OdGiEdgeStyle::EdgeStyle EdgeStyle;
typedef OdGiEdgeStyle::EdgeModifier EdgeModifier;
typedef OdGiEdgeStyle::JitterAmount JitterAmount;
typedef OdGiEdgeStyle::WiggleAmount WiggleAmount;
typedef OdGiEdgeStyle::LineType LineType;
typedef OdGiEdgeStyle::EdgeStyleApply EdgeStyleApply;

typedef OdGiDisplayStyle::DisplaySettings DisplaySettings;
typedef OdGiDisplayStyle::ShadowType ShadowType;
%}



%ignore GiMesh::TrMeshSew::m_aVertexSI;
%ignore GiMesh::TrMeshSew::m_aEdgeSI;
%extend GiMesh::TrMeshSew
{
    OdLinkedArray<TrVertex>& get_m_aVertexSI() { return self->m_aVertexSI; }
    OdLinkedArray<TrEdge>& get_m_aEdgeSI() { return self->m_aEdgeSI; }
}

%nodefaultctor OdGiFastExtCalcViewportDrawImpl;
%nodefaultdtor OdGiFastExtCalcViewportDrawImpl;
%ignore OdGiFastExtCalcViewportDrawImpl::~OdGiFastExtCalcViewportDrawImpl;
%ignore OdGiFastExtCalcViewportDrawImpl::~OdGiFastExtCalcViewportDrawImpl;

%feature("action") OdGiFastExtCalc::~OdGiFastExtCalc
{
	((OdGiWorldDraw*)arg1)->release();
}

%feature("action") OdGiBaseVectorizerImpl::~OdGiBaseVectorizerImpl()
%{
  ((OdGiViewport*)arg1)->release();
%}

%feature("action") OdGsBaseVectorizer::~OdGsBaseVectorizer()
%{ 
  ((OdGiViewport*)arg1)->release();
%}

%typemap(in) REFGUID %{ $1 = $input; /* %typemap(in) REFGUID*/%}
%typemap(out) REFGUID %{ $result = $1; /* %typemap(out) REFGUID*/%}

%feature("action") OdGsBaseMaterialVectorizer::~OdGsBaseMaterialVectorizer()
%{ 
  ((OdGiViewport*)arg1)->release();
%}

%feature("action") OdGsBaseMaterialViewPC::~OdGsBaseMaterialViewPC()
%{ 
  ((OdGiViewport*)arg1)->release();
%}


%rename(Mul_GeMatrix3d_GePoint3d) operator *(const OdGeMatrix3d& matrix, const OdGePoint3d& point);
%rename (AsOdDbStubPointer) operator OdDbStub*;

%rename(OdGiSubEntityTraitsData_InheritableFlags) OdGiSubEntityTraitsData::InheritableFlags;
%rename(OdGiBaseVectorizer_InheritableFlags) OdGiBaseVectorizer::InheritableFlags;

%rename(OdRxPropertyVariant_TypeFactory) OdRxPropertyVariant::TypeFactory;
%rename(OdVariant_TypeFactory) OdVariant::TypeFactory;