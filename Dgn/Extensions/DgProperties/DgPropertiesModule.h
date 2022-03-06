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
#ifndef __DGPROPERTIES_MODULE__H__
#define __DGPROPERTIES_MODULE__H__

#include "RxModule.h"
#include "DgExport.h"

#include "RxSystemServices.h"

/** \details
  Facet class, complements OdDgElement RxProperties list by the dynamically
  built list depending on object's.
  
  <group Dg_Extension_Classes>
*/
class OdDgElementPropertyFacet : public OdRxClass
{
public:
  /** \details
    Facet RxProperties list builder, calls by OdRxMemberCollectionImpl::collectMembers() when
    RxMemberQueryEngine creates a new iterator for object's RxProperties.

    Receives a raw pointer to the OdDgElement object in void *pUserData.
  */
  static void makeMembers(OdRxMemberCollectionBuilder& collectionBuilder, void* pUserData);

  /** \details
    Empty constructor.
  */
  OdDgElementPropertyFacet() {}
  /** \details
    Empty destructor.
  */
  virtual ~OdDgElementPropertyFacet() {}
};

/** \details
  Facet class, complements OdDgECClassInstance RxProperties list by the dynamically
  built list depending on object's.
  
  <group Dg_Extension_Classes>
*/
class OdDgECClassInstancePropertyFacet : public OdRxClass
{
public:
  /** \details
    Facet RxProperties list builder, calls by OdRxMemberCollectionImpl::collectMembers() when
    RxMemberQueryEngine creates a new iterator for object's RxProperties.

    Receives a raw pointer to the OdDgElement object in void *pUserData.
  */
  static void makeMembers(OdRxMemberCollectionBuilder& collectionBuilder, void* pUserData);

  /** \details
    Empty constructor.
  */
  OdDgECClassInstancePropertyFacet() {}
  /** \details
    Empty destructor.
  */
  virtual ~OdDgECClassInstancePropertyFacet() {}
};

/** \details
  Facet provider class for DGN objects.
  
  <group Dg_Extension_Classes>
*/
class OdDgCDAFacetProvider : public OdRxFacetProvider
{
  static OdRxFacetProviderPtr instance;
public:

  /** \details
    Returns an instance of the OdDgCDAFacetProvider class.
  */
  static OdRxFacetProviderPtr createObject();

  /** \details
    Assigns a facet provider to an instance of the OdDgCDAFacetProvider class.
  */
  static void addProvider();

  /** \details
    Removes a facet provider from an instance of the OdDgCDAFacetProvider class.
  */
  static void removeProvider();

  /** \details
    Adds properties list (facets) depending on the object type.

    \param pO [in] Input object. Possible object types: DgElement.
    \param pContext [in] Context.
    \param facets [in/out] Array of facets.
  */
  virtual void getFacets(const OdRxObject* pO, const OdRxMemberQueryContext* pContext, OdArray<OdRxClassPtr>& facets) ODRX_OVERRIDE;
};

TG_EXPORT void odrxSetMemberConstructor(OdRxClass* pClass, OdRxMemberCollectionConstructorPtr pc, void* data = 0);

/** \details
  Corresponding C++ library: TG_Db 
  <group Dg_Extension_Classes>
*/
class OdDgPropertiesModule : public OdRxModule
{
  static OdArray<OdRxMemberPtr> properties;
  static void constructOdDgElementProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDatabaseProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgGraphicsElementProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLevelTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLineStyleTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgMaterialTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgModelTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDisplayStyleTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLevelFilterTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDimStyleTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgMultilineStyleTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgViewGroupTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgPrintStyleTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgTagDefinitionSetTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLinkSetTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgEnvironmentMapTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgPrototypeElementTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDictionaryTableProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLevelProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLineStyleProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgMaterialProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDisplayStyleProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLevelFilterProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDimStyleProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgMultilineStyleProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgViewGroupProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgPrintStyleProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgTagDefinitionSetProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLinkSetProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgPrototypeElementProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDictionaryProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgCurveElement2dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgCurveElement3dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLine2dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLine3dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgArc2dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgArc3dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgCellHeader2dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgCellHeader3dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgShape2dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgShape3dProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgSharedCellDefinitionProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgLinearHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgCrossHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgSymbolHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgDWGHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgModelProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgSharedCellReferenceProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgComplexCurveProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgReferenceAttachmentHeaderProperties(OdRxMemberCollectionBuilder& b, void*);
  static void constructOdDgECClassInstanceProperties(OdRxMemberCollectionBuilder& b, void*);

public:

  void initApp();
  void uninitApp();
};

OdArray<OdRxMemberPtr> OdDgPropertiesModule::properties;

ODRX_DEFINE_DYNAMIC_MODULE(OdDgPropertiesModule);
DISABLE_THREAD_LIBRARY_CALLS()

#endif // __DGPROPERTIES_MODULE__H__
