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

%include "ODA_OdArray_Python.i"

DEF_ODARRAY_MEMORY_ALLOCATOR(OdGeVector3dArray,OdGeVector3d)
DEF_ODARRAY_MEMORY_ALLOCATOR(OdGePoint3dArray, OdGePoint3d)
DEF_ODARRAY_MEMORY_ALLOCATOR(OdGePoint2dArray, OdGePoint2d)
DEF_ODARRAY_MEMORY_ALLOCATOR(OdGeDoubleArray, double)
DEF_ODARRAY_MEMORY_ALLOCATOR(OdInt32Array, OdInt32)
DEF_ODARRAY_OBJECTS_ALLOCATOR(OdRxObjectPtrArray,OdRxObjectPtr)


%inline %{
  typedef OdArray<OdGeNurbCurve2d*> OdGeNurbCurve2dArrayPtr;
  typedef OdArray<OdGeNurbCurve2dArrayPtr> OdGeNurbCurve2dArray2d;
 %}
DEF_ODARRAY_OBJECTS_ALLOCATOR(OdGeNurbCurve2dArrayPtr, OdGeNurbCurve2d*)
DEF_ODARRAY_OBJECTS_ALLOCATOR(OdGeNurbCurve2dArray2d, OdGeNurbCurve2dArrayPtr)

%inline %{
  typedef OdArray<OdGeNurbCurve3d*> OdGeNurbCurve3dArrayPtr;
  typedef OdArray<OdGeNurbCurve3dArrayPtr> OdGeNurbCurve3dArray2d;
 %}
DEF_ODARRAY_OBJECTS_ALLOCATOR(OdGeNurbCurve3dArrayPtr, OdGeNurbCurve3d*)
DEF_ODARRAY_OBJECTS_ALLOCATOR(OdGeNurbCurve3dArray2d, OdGeNurbCurve3dArrayPtr)