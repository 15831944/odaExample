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


#ifndef __OD_DB_UNDERLAY_DEFINITION__
#define __OD_DB_UNDERLAY_DEFINITION__

#include "TD_PackPush.h"

#include "DbObject.h"
#include "DbUnderlayHost.h"

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbUnderlayDefinition : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbUnderlayDefinition);

  void setSourceFileName(const OdString& name);
  OdString getSourceFileName() const;

  OdString getActiveFileName() const;

  void setItemName(const OdString& item);
  OdString getItemName() const;

  void setUnderlayItem(const OdString& sourceFileName, const OdString& activeFileName, OdTvDbUnderlayItemPtr pItem);
  OdTvDbUnderlayItemPtr getUnderlayItem() const;

  OdResult load(const OdString& password);
  void unload();
  bool isLoaded() const;
  static OdString dictionaryKey(const OdRxClass* underlayDefinitionType);

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual OdTvDbObjectId postDefinitionToDb(OdTvDbDatabase* pDb, const OdString& defName);

  void applyPartialUndo(OdTvDbDwgFiler* pFiler, OdRxClass* pClass);
};

typedef OdSmartPtr<OdTvDbUnderlayDefinition> OdTvDbUnderlayDefinitionPtr;


// These inheritants are for registering OdTvDbUnderlayHostPE protocol extension

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbDwfDefinition : public OdTvDbUnderlayDefinition
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDwfDefinition);
  
  OdTvDbDwfDefinition();

  bool isDWFx() const;
};

typedef OdSmartPtr<OdTvDbDwfDefinition> OdTvDbDwfDefinitionPtr;


/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbDgnDefinition : public OdTvDbUnderlayDefinition
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDgnDefinition);

  OdTvDbDgnDefinition();

  // Specific DGNUnderlay functions
  bool useMasterUnits() const;
  void setUseMasterUnits(bool useMaster);

  int xrefDepth() const;
  void setXrefDepth(int depth);

  bool showRasterRef() const;
  void setShowRasterRef(bool bShow);
};

typedef OdSmartPtr<OdTvDbDgnDefinition> OdTvDbDgnDefinitionPtr;

/** \details
The class that implements PDF underlay definition functionality.
<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbPdfDefinition : public OdTvDbUnderlayDefinition
{
public:
  //DOM-IGNORE-BEGIN
  ODDB_DECLARE_MEMBERS(OdTvDbPdfDefinition);
  //DOM-IGNORE-END

  /** \details 
  Creates a new instance of PDF underlay definition with default parameters.
  */
  OdTvDbPdfDefinition();

  /** \details 
  Loads a PDF underlay module.
  \returns Returns a smart pointer to the PDF underlay module instance.
  */
  static OdRxModulePtr loadPdfUnderlayModule();
};

/** \details
A data type that represents a smart pointer to an <link OdTvDbPdfDefinition, OdTvDbPdfDefinition> object.
*/
typedef OdSmartPtr<OdTvDbPdfDefinition> OdTvDbPdfDefinitionPtr;

/** \details

<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbNavisworksDefinition : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS( OdTvDbNavisworksDefinition );

  OdTvDbNavisworksDefinition();

  void setSourceFileName( const OdString& fname );
  OdString sourceFileName() const;

  OdString activeFileName() const;
  OdResult setActiveFileName( const OdString& fname );

  bool getDWGModelItemVisible() const;
  void setDWGModelItemVisible( bool bVisible );

  OdGeExtents3d getExtents() const;

  OdResult load();
  void unload();
  bool isLoaded() const;

  OdString fileType() const;

  int entityCount( int *pLockCount ) const;

  int fileFound() const;

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler );

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler ) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler );

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler ) const;


};

typedef OdSmartPtr<OdTvDbNavisworksDefinition> OdTvDbNavisworksDefinitionPtr;

#include "TD_PackPop.h"

#endif // __OD_DB_UNDERLAY_DEFINITION__
