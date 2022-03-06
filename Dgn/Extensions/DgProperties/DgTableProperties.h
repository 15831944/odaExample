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
#ifndef __DGTABLEPROPS__H__
#define __DGTABLEPROPS__H__

#include "DgProperties.h"
#include "DgTable.h"
#include "DgEnvironmentMap.h"

// Class OdDgLevelTable properties. Category "Level Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgLevelTable,Items,OdDgElementId,"Level Table",1,"Array of level ids", false);

// Class OdDgLineStyleTable properties. Category "Line Style Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgLineStyleTable,Items,OdDgElementId,"Line Style Table",1,"Array of line style ids", true);

// Class OdDgMaterialTable properties. Category "Material Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgMaterialTable,Items,OdDgElementId,"Material Table",1,"Array of material ids", false);

// Class OdDgModelTable properties. Category "Model Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgModelTable, Items, OdDgElementId, "Model Table", 1, "Array of model ids", false);

// Class OdDgDisplayStyleTable properties. Category "Display Style Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDisplayStyleTable,Items,OdDgElementId,"Display Style Table",1,"Array of display style ids", false);

// Class OdDgLevelFilterTable properties. Category "Level Filter Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgLevelFilterTable,Items,OdDgElementId,"Level Filter Table",1,"Array of level filter ids", false);

// Class OdDgDimStyleTable properties. Category "DimStyle Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDimStyleTable,Items,OdDgElementId,"Level Filter Table",1,"Array of dimstyle ids", false);

// Class OdDgMultilineStyleTable properties. Category "Multiline Style Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgMultilineStyleTable,Items,OdDgElementId,"Multiline Style Table",1,"Array of multiline style ids", false);

// Class OdDgViewGroupTable properties. Category "View Group Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgViewGroupTable,Items,OdDgElementId,"View Group Table",1,"Array of view group ids", false);

// Class OdDgPrintStyleTable properties. Category "Print Style Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgPrintStyleTable,Items,OdDgElementId,"Print Style Table",1,"Array of print style ids", false);

// Class OdDgTagDefinitionSetTable properties. Category "Tag Definition Set Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgTagDefinitionSetTable,Items,OdDgElementId,"Tag Definition Set Table",1,"Array of tag definition set ids", false);

// Class OdDgLinkSetTable properties. Category "Link Set Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgLinkSetTable,Items,OdDgElementId,"Link Set Table",1,"Array of link set ids", false);

// Class OdDgEnvironmentMapTable properties. Category "Environment Map Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgEnvironmentMapTable,Items, OdDgEnvironmentMap,"Environment Map Table",1,"Array of environment map names", false);

// Class OdDgPrototypeElementTable properties. Category "Prototype Element Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgPrototypeElementTable,Items, OdDgElementId,"Prototype Element Table",1,"Array of prototype element ids", false);

// Class OdDgDictionaryTable properties. Category "Dictionary Table":

/* 1 - Items      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDictionaryTable,Items, OdDgElementId,"Dictionary Table",1,"Array of dictionary ids", false);

// Class OdDgLevelTableRecord properties. Category "Level":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgLevelTableRecord,Index,OdUInt32,"Level",1,"Level entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgLevelTableRecord,Name,OdString,"Level",2,"Level name", "");

// Class OdDgLineStyleTableRecord properties. Category "Line Style":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgLineStyleTableRecord,Index,OdUInt32,"Line Style",1,"Line style entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgLineStyleTableRecord,Name,OdString,"Line Style",2,"Line style name", "");

// Class OdDgMaterialTableRecord properties. Category "Material":

/* 1 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgMaterialTableRecord,Name,OdString,"Material",1,"Material name", "");

// Class OdDgDisplayStyleTableRecord properties. Category "Display Style":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDisplayStyleTableRecord,Index,OdUInt32,"Display Style",1,"Display style entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgDisplayStyleTableRecord,Name,OdString,"Display Style",2,"Display style name", "");

// Class OdDgLevelFilterRecord properties. Category "Level Filter":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgLevelFilterTableRecord,Index,OdUInt32,"Level Filter",1,"Level filter entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgLevelFilterTableRecord,Name,OdString,"Level Filter",2,"Level filter name", "");

// Class OdDgOdDgDimStyleRecord properties. Category "DimStyle":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDimStyleTableRecord,Index,OdUInt32,"DimStyle",1,"Dimstyle entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgDimStyleTableRecord,Name,OdString,"DimStyle",2,"Dimstyle name", "");

// Class OdDgMultilineStyleRecord properties. Category "Multiline Style":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgMultilineStyleTableRecord,Index,OdUInt32,"Multiline Style",1,"Multiline style entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgMultilineStyleTableRecord,Name,OdString,"Multiline Style",2,"Multiline style name", "");

// Class OdDgViewGroup properties. Category "View group":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgViewGroup,Index,OdUInt32,"View group",1,"View group entry id");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgViewGroup,Name,OdString,"View group",2,"View group name", "");

// Class OdDgPrintStyleRecord properties. Category "Print Style":

/* 1 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgPrintStyleTableRecord,Name,OdString,"Print style",1,"Print style name", "");

// Class OdDgTagDefinitionSet properties. Category "Tag Definition Set":

/* 1 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgTagDefinitionSet,Name,OdString,"Tag definition set",1,"Tag definition set name", "");

// Class OdDgLinkSet properties. Category "Link Set":

/* 1 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgLinkSet,Name,OdString,"Link set",1,"Link set name", "");

// Class OdDgEnvironmentMap properties. Category "Environment Map":

///* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgEnvironmentMap, Index, OdUInt32, "Environment Map", 1, "Environment map index");
///* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgEnvironmentMap, Name, OdString, "Environment Map", 2, "Environment map name", "");

// Class OdDgPrototypeElement properties. Category "Prototype Element":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgPrototypeElement, Index, OdUInt16, "Prototype element", 1, "Prototype element index");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgPrototypeElement, Name, OdString, "Prototype element", 2, "Prototype element name", "");

// Class OdDgDictionaryTableRecord properties. Category "Dictionary":

/* 1 - Index      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDictionaryTableRecord, Index, OdUInt16, "Dictionary", 1, "Dictionary index");
/* 2 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgDictionaryTableRecord, Name, OdString, "Dictionary", 2, "Dictionary name", "");

// Class OdDgSharedCellDefinition properties. Category "General":

/* 1 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgSharedCellDefinition,Name,OdString,"General",1,"Shared cell definition name", "");
/* 3 - Elements   */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_TREE(OdDgSharedCellDefinition, Elements, OdDgElementId, "",3, "Shared cell definition children","Entity");

// Class OdDgModel properties. No category:

/* 1 - Name       */ ODRX_DECLARE_RX_PROPERTY(OdDgModel, Name, OdString, "General",1, "Model name", "");
/* 3 - Elements   */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_TREE(OdDgModel, Elements, OdDgElementId, "",3, "Collection of model elements. Include all graphics elements and reference attachments.","Entity");

#endif // __DGTABLEPROPS__H__
