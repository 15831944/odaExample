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

#include "TviImportParameters.hpp"

// obj
#define OBJ_CALC_NORMALS_KEY @"Obj_CalcNormals_Key"
#define OBJ_FLIP_UV_KEY @"Obj_FlipUV_Key"
// drw
#define DRW_OBJ_NAMING_KEY @"Drw_ObjNaming_Key"
#define DRW_STORE_SOURCE_KEY @"Drw_StoreSource_Key"
#define DRW_CLEAR_EMPTY_OBJECTS_KEY @"Drw_ClearEmptyObj_Key"
#define DRW_ENABLE_MT_KEY @"Drw_EnableMT_Key"
#define DRW_MAX_THREADS_KEY @"Drw_MaxThreads_Key"
#define DRW_USE_ADV_TESS_KEY @"Drw_UseAdvTess_Key"
#define DRW_FACET_RES_KEY @"Drw_FacetRes_Key"
#define DRW_USE_LOW_MEMORY_KEY @"Drw_UseLowMemory_Key"
// dgn
#define DGN_OBJ_NAMING_KEY @"Dgn_ObjNaming_Key"
#define DGN_STORE_SOURCE_KEY @"Dgn_StoreSource_Key"
#define DGN_CLEAR_EMPTY_OBJECTS_KEY @"Dgn_ClearEmptyObj_Key"
// stl
#define STL_FIX_NORMALS_KEY @"Stl_FixNormals_Key"
#define STL_UNIFY_DUPLICATED_VERTICES_KEY @"Stl_UnifyDuplicatedVert_Key"
#define STL_CALC_NORMALS_KEY @"Stl_CalcNormals_Key"
// prc
#define PRC_OBJ_NAMING_KEY @"Prc_ObjNaming_Key"
#define PRC_STORE_SOURCE_KEY @"Prc_StoreSource_Key"
#define PRC_CLEAR_EMPTY_OBJECTS_KEY @"Prc_ClearEmptyObj_Key"

void TviObjImportParams::readFromDefaults()
{
    NSArray* keys = [[m_userDef dictionaryRepresentation] allKeys];
    if([keys containsObject:OBJ_CALC_NORMALS_KEY])
        setCalculateNormals([m_userDef boolForKey:OBJ_CALC_NORMALS_KEY]);
    if([keys containsObject:OBJ_FLIP_UV_KEY])
        setBrepFlipUVCoordinates([m_userDef boolForKey:OBJ_FLIP_UV_KEY]);
}

void TviObjImportParams::writeToDefaults()
{
    [m_userDef setBool:getCalculateNormals() forKey:OBJ_CALC_NORMALS_KEY];
    [m_userDef setBool:getBrepFlipUVCoordinates() forKey:OBJ_FLIP_UV_KEY];
}

void TviDrwImportParams::readFromDefaults()
{
    NSArray* keys = [[m_userDef dictionaryRepresentation] allKeys];
    if([keys containsObject:DRW_OBJ_NAMING_KEY])
        setObjectNaming([m_userDef boolForKey:DRW_OBJ_NAMING_KEY]);
    if([keys containsObject:DRW_STORE_SOURCE_KEY])
        setStoreSourceObjects([m_userDef boolForKey:DRW_STORE_SOURCE_KEY]);
    if([keys containsObject:DRW_CLEAR_EMPTY_OBJECTS_KEY])
        setClearEmptyObjects([m_userDef boolForKey:DRW_CLEAR_EMPTY_OBJECTS_KEY]);
    if([keys containsObject:DRW_ENABLE_MT_KEY])
        setMultithreading([m_userDef boolForKey:DRW_ENABLE_MT_KEY]);
    if([keys containsObject:DRW_MAX_THREADS_KEY])
        setCountOfThreads([m_userDef integerForKey:DRW_MAX_THREADS_KEY]);
    if([keys containsObject:DRW_USE_ADV_TESS_KEY])
        setUseAdvancedTess([m_userDef boolForKey:DRW_USE_ADV_TESS_KEY]);
    if([keys containsObject:DRW_FACET_RES_KEY])
        setFacetRes([m_userDef doubleForKey:DRW_FACET_RES_KEY]);
    if([keys containsObject:DRW_USE_LOW_MEMORY_KEY])
        setOpenSourcePartial([m_userDef boolForKey:DRW_USE_LOW_MEMORY_KEY]);
}

void TviDrwImportParams::writeToDefaults()
{
    [m_userDef setBool:getObjectNaming() forKey:DRW_OBJ_NAMING_KEY];
    [m_userDef setBool:getStoreSourceObjects() forKey:DRW_STORE_SOURCE_KEY];
    [m_userDef setBool:getClearEmptyObjects() forKey:DRW_CLEAR_EMPTY_OBJECTS_KEY];
    [m_userDef setBool:getMultithreading() forKey:DRW_ENABLE_MT_KEY];
    [m_userDef setInteger:getCountOfThreads() forKey:DRW_MAX_THREADS_KEY];
    [m_userDef setBool:getUseAdvancedTess() forKey:DRW_USE_ADV_TESS_KEY];
    [m_userDef setDouble:getFacetRes() forKey:DRW_FACET_RES_KEY];
    [m_userDef setBool:getOpenSourcePartial() forKey:DRW_USE_LOW_MEMORY_KEY];
}

void TviDgnImportParams::readFromDefaults()
{
    NSArray* keys = [[m_userDef dictionaryRepresentation] allKeys];
    if([keys containsObject:DGN_OBJ_NAMING_KEY])
        setObjectNaming([m_userDef boolForKey:DGN_OBJ_NAMING_KEY]);
    if([keys containsObject:DGN_STORE_SOURCE_KEY])
        setStoreSourceObjects([m_userDef boolForKey:DGN_STORE_SOURCE_KEY]);
    if([keys containsObject:DGN_CLEAR_EMPTY_OBJECTS_KEY])
        setClearEmptyObjects([m_userDef boolForKey:DGN_CLEAR_EMPTY_OBJECTS_KEY]);
}

void TviDgnImportParams::writeToDefaults()
{
    [m_userDef setBool:getObjectNaming() forKey:DGN_OBJ_NAMING_KEY];
    [m_userDef setBool:getStoreSourceObjects() forKey:DGN_STORE_SOURCE_KEY];
    [m_userDef setBool:getClearEmptyObjects() forKey:DGN_CLEAR_EMPTY_OBJECTS_KEY];
}

void TviStlImportParams::readFromDefaults()
{
    NSArray* keys = [[m_userDef dictionaryRepresentation] allKeys];
    if([keys containsObject:STL_FIX_NORMALS_KEY])
        setFixNormals([m_userDef boolForKey:STL_FIX_NORMALS_KEY]);
    if([keys containsObject:STL_UNIFY_DUPLICATED_VERTICES_KEY])
        setUnifyDuplicatedVertices([m_userDef boolForKey:STL_UNIFY_DUPLICATED_VERTICES_KEY]);
    if([keys containsObject:STL_CALC_NORMALS_KEY])
        setCalcNormalsAtVertices([m_userDef boolForKey:STL_CALC_NORMALS_KEY]);
}

void TviStlImportParams::writeToDefaults()
{
    [m_userDef setBool:getFixNormals() forKey:STL_FIX_NORMALS_KEY];
    [m_userDef setBool:getUnifyDuplicatedVertices() forKey:STL_UNIFY_DUPLICATED_VERTICES_KEY];
    [m_userDef setBool:getCalcNormalsAtVertices() forKey:STL_CALC_NORMALS_KEY];
}

void TviPrcImportParams::readFromDefaults()
{
    NSArray* keys = [[m_userDef dictionaryRepresentation] allKeys];
    if([keys containsObject:PRC_OBJ_NAMING_KEY])
        setObjectNaming([m_userDef boolForKey:PRC_OBJ_NAMING_KEY]);
    if([keys containsObject:PRC_STORE_SOURCE_KEY])
        setStoreSourceObjects([m_userDef boolForKey:PRC_STORE_SOURCE_KEY]);
    if([keys containsObject:PRC_CLEAR_EMPTY_OBJECTS_KEY])
        setClearEmptyObjects([m_userDef boolForKey:PRC_CLEAR_EMPTY_OBJECTS_KEY]);
}

void TviPrcImportParams::writeToDefaults()
{
    [m_userDef setBool:getObjectNaming() forKey:PRC_OBJ_NAMING_KEY];
    [m_userDef setBool:getStoreSourceObjects() forKey:PRC_STORE_SOURCE_KEY];
    [m_userDef setBool:getClearEmptyObjects() forKey:PRC_CLEAR_EMPTY_OBJECTS_KEY];
}


TviImportParamsController::TviImportParamsController()
{
    
}

void TviImportParamsController::setRect(int w, int h)
{
    OdTvDCRect rect = OdTvDCRect(0, (long)w, (long)h, 0);
    m_dwgParams.setDCRect(rect);
    m_dgnParams.setDCRect(rect);
    m_prcParams.setDCRect(rect);
}

