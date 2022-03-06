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
#ifndef __DG_TABLE_H__
#define __DG_TABLE_H__


#include "TD_PackPush.h"

#include "DgElement.h"
#include "DgCellHeader.h"
#include "DgLineStyleDefTableRecord.h"
#include "UInt32Array.h"
#include <set>

class OdDgTableRecord;
typedef OdSmartPtr<OdDgTableRecord> OdDgTableRecordPtr;

class OdDgElementIterator;
typedef OdSmartPtr<OdDgElementIterator> OdDgElementIteratorPtr;

class OdDgTextStyleTableRecord;
typedef OdSmartPtr<OdDgTextStyleTableRecord> OdDgTextStyleTableRecordPtr;

class OdDgFontTableRecord;
typedef OdSmartPtr<OdDgFontTableRecord> OdDgFontTableRecordPtr;

class OdDgDimStyleTableRecord;
typedef OdSmartPtr<OdDgDimStyleTableRecord> OdDgDimStyleTableRecordPtr;

class OdDgMultilineStyleTableRecord;
typedef OdSmartPtr<OdDgMultilineStyleTableRecord> OdDgMultilineStyleTableRecordPtr;

/** \details
    This class is the base class for all Table objects in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgTable : public OdDgElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgTable);
public:

  /** \details
    Searches the Table object for the specified TableRecord.

    \param recordName [in]  Record name.
    \param getErasedRecord [in]  If and only if true, erased records will be opened or retrieved.

    \returns
    Returns a OdDgElementId of the object if successful, otherwise a null element id.
  */
  virtual OdDgElementId getAt(
    const OdString& recordName, 
    bool getErasedRecord = false) const;
    
  /** \details
    Searches the Table object for the specified TableRecord.

    \param recordEntryId [in]  Record entry id.
    \param getErasedRecord [in]  If and only if true, erased records will be opened or retrieved.

    \returns
    Returns a OdDgElementId of the object if successful, otherwise a null element id.
  */
  virtual OdDgElementId getAt(
    OdUInt32 recordEntryId, 
    bool getErasedRecord = false) const;

  /** \details
    Returns true if and only if this Table object has a record with the specified ElementId.

    \param elementId [in]  Element ID.
  */
  virtual bool has(
    const OdDgElementId& elementId) const;

  /** \details
    Adds the specified record to this Table object.

    \param pRecord [in]  Pointer to the record to add.
    \param bCheckData [in]  If it false then check only record name, not editional properties

    \returns
    Returns the Element ID of the newly added record.
  */
  virtual void add(
    OdDgTableRecordPtr pRecord, bool bCheckData = true );

  /** \details
    Returns an Iterator object that can be used to traverse this Table object.

    \param atBeginning [in]  True to start at the beginning, false to start at the end. 
    \param skipDeleted [in]  If and only if true, deleted records are skipped.
  */
  virtual OdDgElementIteratorPtr createIterator( bool atBeginning = true, bool skipDeleted = true ) const;

  virtual OdRxObjectPtr clone() const;

  /** \details
  Move table record from the table to the start position of the table.

  \param idTableRecord [in]  element id of the table record to move.
  \param bSkipDeleted  [in]  skip erased elements.

  \returns
  eOk if table record was moved to the start position of the table.

  \remarks
  1) The table record must be from the table. The function is only change position
  of the table record and doesn't add it to the table.
  2) Start position is not always first position. Some tables store their default data
  on the first element.
  */
  virtual OdResult moveToStart(OdDgElementId& idTableRecord, bool bSkipDeleted = true);

  /** \details
  Move table record from the table to the end position of the table.

  \param idTableRecord [in]  element id of the table record to move.
  \param bSkipDeleted  [in]  skip erased elements.

  \returns
  eOk if table record was moved to the end position of the table.

  \remarks
  The table record must be from the table. The function is only change position
  of the table record and doesn't add it to the table.
  */
  virtual OdResult moveToEnd(OdDgElementId& idTableRecord, bool bSkipDeleted = true);

  /** \details
  Move table record from the table to the position with defined index of the table.

  \param uIndex [in]  number from the start position into the table.
  \param idTableRecord [in]  element id of the table record to move.
  \param bSkipDeleted  [in]  skip erased elements.

  \returns
  eOk if table record was moved to the index position of the table.

  \remarks
  The table record must be from the table. The function is only change position
  of the table record and doesn't add it to the table.
  */
  virtual OdResult moveToIndex(OdUInt32 uIndex, OdDgElementId& idTableRecord, bool bSkipDeleted = true);

  /** \details
  Return maximum index into the table.

  \param bSkipDeleted  [in]  skip erased elements.

  */
  virtual OdUInt32 getItemCount(bool bSkipDeleted = true) const;

  /** \details
  Return if first index of table used as default value.

  \remarks
  If first index is default value then it can't be moved to another position and start index of 
  the table is 1.
  */

  virtual bool     firstIndexIsDefaultValue() const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgTable object pointers.
*/
typedef OdSmartPtr<OdDgTable> OdDgTablePtr;


/** \details
    This class implements the LevelTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLevelTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLevelTable);
public:

  /** \details
    Searches the Level object for the specified user-assigned level number.

    \param levelNumber [in]  User-assigned number.
    \param getErasedRecord [in]  If and only if true, erased records will be opened or retrieved.

    \returns
    Returns a OdDgElementId of the object if successful, otherwise a null element id.
  */
  OdDgElementId getAtNumber(
    OdUInt32 levelNumber, 
    bool getErasedRecord = false) const;

  /** \details
    OdDgTable overridden. Add level table record to level table.

    \param pRecord [in]  Level table record to add.
    \param bKeepLevelMask [in]  If true (default value), level masks of all views has NOT been updated after
                       adding of level table record, otherwise level masks has been updated automatically.
  */

  virtual void add(
    OdDgTableRecordPtr pRecord,  bool bKeepLevelMask = true );


  /** \details
    Get/set read only flag for level table.

    \remarks
    If read only flag is true than no level of the level table can be modified.
  */

  virtual bool getReadOnlyFlag() const;
  virtual void setReadOnlyFlag( bool bSet );

  /** \details
    Generates usage data for each record in the level table object.
    
    \remarks
    Usage data can be accessed via the OdDbLevelTableRecord::isInUse() method.
  */
  void generateUsageData();
};

/** \details
This template class is a specialization of the OdSmartPtr class for OdDgLevelTable object pointers.
*/
typedef OdSmartPtr<OdDgLevelTable> OdDgLevelTablePtr;

/** \details
This class implements the LevelFilterTable, which represents level filters in an OdDgDatabase instance.

Corresponding C++ library: TG_Db

<group OdDg_Classes>
*/
class TG_EXPORT OdDgLevelFilterTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLevelFilterTable);
public:

  enum OdDgFilterMemberType
  {
    kMemberTypeNull   = 0,
    kMemberTypeShort  = 1,
    kMemberTypeInt    = 2,
    kMemberTypeBool   = 3,
    kMemberTypeChar   = 4,
    kMemberTypeWChar  = 5,
    kMemberTypeDouble = 6,
    kMemberTypeTime   = 7
  };

public:

  // OdDgTable overridden
  virtual void add(
    OdDgTableRecordPtr pRecord,  bool bCheckData = true );
  
  virtual bool addFilterMember( OdString strMemberName, OdDgFilterMemberType iMemberType );
  virtual bool deleteFilterMember( const OdString strMemberName );
  virtual OdUInt32 getFilterMemberCount() const;
  virtual bool getFilterMember( OdUInt32 uIndex, OdString& strMemberName, OdDgFilterMemberType& iMemberType ) const;
  virtual bool getFilterMember( const OdString& strMemberName, OdDgFilterMemberType& iMemberType ) const;
  virtual bool setFilterMember( OdUInt32 uIndex, OdString& strMemberName, OdDgFilterMemberType& iMemberType );
  virtual bool setFilterMember( const OdString& strMemberName, OdDgFilterMemberType& iMemberType );

  virtual OdUInt32 getActiveFilterId() const;
  virtual void     setActiveFilterId( OdUInt32 uActiveId );
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgLevelFilterTable object pointers.
*/
typedef OdSmartPtr<OdDgLevelFilterTable> OdDgLevelFilterTablePtr;


/** \details
    This class implements the FontTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgFontTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgFontTable);
public:

  /** \details
    Searches the Font object for the specified Font number.

    \param fontNumber [in]  The number of the font.

    \returns
    Returns the OdDgFontTableRecordPtr of the specific record if successful, otherwise a null pointer.
  */
  OdDgFontTableRecordPtr getFont(OdUInt32 fontNo) const;
  /** \details
    Searches the Font object for the specified Font number.

    \param fontNumber [in]  The name of the font.

    \returns
    Returns the OdDgFontTableRecordPtr of the specific record if successful, otherwise a null pointer.
  */
  OdDgFontTableRecordPtr getFont(const OdString& fontName) const;

  /** \details
    Searches the Font object for the specified Font number.

    \param fontNumber [in]  The name of the font.

    \returns
    Returns the OdDgFontTableRecordPtr of the specific record if successful, otherwise it try to get alternate font, then it try to get fast font.
  */
  static OdDgFontTableRecordPtr getFont(const OdDgDatabase* pDb, OdUInt32 uFontId);

  // OdDgTable overridden
  virtual void add( OdDgTableRecordPtr pRecord,  bool bCheckData = true );

  /** \details
    Return information ( numbers and names ) about loaded rsc fonts.

    \param arrNumbers [out]  The array of the rsc font numbers.
    \param arrNames   [out]  The array of the rsc font names.

    \returns
    Returns true if one or more rsc fonts was found, otherwise false.
  */
  virtual bool getLoadedRscFontInfo( OdUInt32Array& arrNumbers, OdArray<OdString>& arrNames ) const;

  static bool isShxRange(OdUInt32 fontNo);
  static bool isRscRange(OdUInt32 fontNo);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgFontTable object pointers.
*/
typedef OdSmartPtr<OdDgFontTable> OdDgFontTablePtr;

/** \details

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgFontTablePE : public OdRxObject
{
  ODRX_DECLARE_MEMBERS(OdDgFontTablePE);
  long        m_references;     //used by each object separately
public:

  OdDgFontTablePE();
  ~OdDgFontTablePE();

  //OdRxObject overridden
  virtual void addRef();
  virtual void release();
  virtual long numRefs() const;

  virtual bool convertRscFontToShxFont( OdDgFontTable* pFontTable, const OdString& strRscFontName, const OdString& strShxFontFileName );
  virtual void rscFontNotFound( OdUInt32 uFontIndex );
};

typedef OdSmartPtr<OdDgFontTablePE> OdDgFontTablePEPtr;


/** \details
    This class implements the TextStyleTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgTextStyleTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgTextStyleTable);
public:

  /** \details
    Returns the date of the default text style.
  */
  virtual OdDgTextStyleTableRecordPtr getDefaultData(OdDg::OpenMode uOpenMode = OdDg::kForRead) const;
  virtual void setDefaultData(OdDgTextStyleTableRecordPtr pRecord);

  // OdDgTable overridden
  virtual void add(
    OdDgTableRecordPtr pRecord, bool bCheckData = true );
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgTextStyleTable object pointers.
*/
typedef OdSmartPtr<OdDgTextStyleTable> OdDgTextStyleTablePtr;


/** \details
    This class implements the DimStyleTable, which represents dimension styles in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgDimStyleTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgDimStyleTable);

  // OdDgTable overridden
  virtual void add(
    OdDgTableRecordPtr pRecord,  bool bCheckData = true );

  /** \details
  Returns the date of the default dimension style. Use it to set dimension properties after creation of new dimension.
  */
  virtual OdDgDimStyleTableRecordPtr getActualDimensionSettings(OdDg::OpenMode openMode = OdDg::kForRead) const;

  /** \details
  Returns active dimension style. It may contains differences with actual dimension settings.
  */
  virtual OdDgDimStyleTableRecordPtr getActiveDimensionStyle(OdDg::OpenMode openMode = OdDg::kForRead) const;

  /** \details
  Set active dimension style and copy dimension style properties to actual dimension settings.
  */
  virtual bool setActiveDimensionStyle( const OdDgDimStyleTableRecordPtr& pDimStyle, bool bSetActualDimensionSettings = true);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgDimStyleTable object pointers.
*/
typedef OdSmartPtr<OdDgDimStyleTable> OdDgDimStyleTablePtr;


/** \details
    This class implements the MultilineStyleTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgMultilineStyleTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgMultilineStyleTable);

  /** \details
  Returns active multiline style.
  */
  virtual OdDgMultilineStyleTableRecordPtr getActiveMultilineStyle(OdDg::OpenMode openMode = OdDg::kForRead) const;

  /** \details
  Set active multiline style.
  */
  virtual void setActiveMultilineStyle(const OdDgMultilineStyleTableRecordPtr& pMLStyle);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgMultilineStyleTable object pointers.
*/
typedef OdSmartPtr<OdDgMultilineStyleTable> OdDgMultilineStyleTablePtr;


/** \details
    This class implements the LineStyleTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLineStyleTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLineStyleTable);
public:

  // OdDgTable overridden
  virtual void add(
    OdDgTableRecordPtr pRecord,  bool bCheckData = true );

  // Rsc Line Styles. 

  virtual OdUInt32 getRscLineStyleCount() const;
  virtual OdDgTableRecordPtr getRscLineStyle( OdUInt32 uIndex ) const;
  virtual OdDgTableRecordPtr getRscLineStyle( const OdString& strName ) const;

  static bool loadLineStylesFromRscFile( OdDgDatabase* pDb, const OdString& strFilename );
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgLineStyleTable object pointers.
*/
typedef OdSmartPtr<OdDgLineStyleTable> OdDgLineStyleTablePtr;

/** \details
    This class defines the interface for import of dgn custom line style to dwg database.

    \sa
    TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgImportLineStylePE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDgImportLineStylePE);

  virtual OdDbStub* importLineStyle(OdDgDatabase* pDgnDb, OdRxObject* pDwgDb, const OdString& strLineStyleName) = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class
  for OdDgImportLineStylePE object pointers.
*/
typedef OdSmartPtr<OdDgImportLineStylePE> OdDgImportLineStylePEPtr;

/** \details
    This class implements the LineStyleDefTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLineStyleDefTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLineStyleDefTable);
public:

  // OdDgTable overridden
  virtual void add(
    OdDgTableRecordPtr pRecord,  bool bCheckData = true );

  virtual void addSymbol(
    OdDgCellHeader2dPtr pCell2d);

  virtual void addSymbol(
    OdDgCellHeader3dPtr pCell3d);

  virtual OdDgElementId getAt( const OdString& recordName, bool getErasedRecord = false) const;

  // For rsc line styles. Read Only.
  OdDgLineStyleDefTableRecordPtr getRscLineStyleDef( const OdString& strLineStyleName ) const;
  OdDgLineStyleDefTableRecordPtr getRscLineStyleDef( OdUInt32 entryId, OdDgLineStyleResource::OdLsResourceType rscType ) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgLineStyleDefTable object pointers.
*/
typedef OdSmartPtr<OdDgLineStyleDefTable> OdDgLineStyleDefTablePtr;


/** \details
    This class implements the DictionaryTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgDictionaryTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgDictionaryTable);
public:

  OdDgElementId getDefaultId() const;
  void setDefaultId(const OdDgElementId& elementId);

  OdUInt16  getOwnerFlags() const;
  void      setOwnerFlags( OdUInt16 uFlags );

  OdUInt16  getCloneFlags() const;
  void      setCloneFlags( OdUInt16 uFlags );
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgDictionaryTable object pointers.
*/
typedef OdSmartPtr<OdDgDictionaryTable> OdDgDictionaryTablePtr;


/** \details
    This class implements the RegAppTable, which represents levels in an OdDgDatabase instance.

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgRegAppTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgRegAppTable);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgRegAppTable object pointers.
*/
typedef OdSmartPtr<OdDgRegAppTable> OdDgRegAppTablePtr;

/** \details

    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
struct OdDgEnvironmentCube
{
  OdString m_strTopFileName;
  OdString m_strBottomFileName;
  OdString m_strFrontFileName;
  OdString m_strBackFileName;
  OdString m_strLeftFileName;
  OdString m_strRightFileName;
};

/** \details
  This class implements the MaterialTable, which represents materials in an OdDgDatabase instance.

  Corresponding C++ library: TG_Db

  <group OdDg_Classes>
*/
class TG_EXPORT OdDgMaterialTable : public OdDgTable
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgMaterialTable);

  // OdDgTable overridden
  virtual void add( OdDgTableRecordPtr pRecord,  bool bCheckData = true );
  virtual OdDgElementId getAt( const OdString& recordName, bool getErasedRecord = false ) const;
  virtual void loadFromFile( OdString strFilename );
  virtual void saveToFile( OdString strFilename );
  virtual OdDgEnvironmentCube getEnvironmentCube() const;
  virtual void setEnvironmentCube( const OdDgEnvironmentCube& envCobe );
};

/** \details
This template class is a specialization of the OdSmartPtr class for OdDgMaterialTable object pointers.
*/
typedef OdSmartPtr<OdDgMaterialTable> OdDgMaterialTablePtr;

//========================================================================================

/** \details
    Corresponding C++ library: TG_Db 
    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLevelMaterialAssignmentData
{
public:
  OdDgLevelMaterialAssignmentData();
  virtual ~OdDgLevelMaterialAssignmentData() {}

  OdString getLevelName() const;
  void     setLevelName( const OdString& strName );

  bool     getColorAssignment( OdUInt8 uColorIndex ) const;
  void     setColorAssignment( OdUInt8 uColorIndex, bool bAssignWithMaterial = true );
  bool     getColorRgbAssignment(ODCOLORREF rgbColor) const;
  void     setColorRgbAssignment(ODCOLORREF rgbColor, bool bAssignWithMaterial = true);
  OdUInt32 getColorRgbAssignmentCount() const;
  ODCOLORREF getColorRgbAssignmentByIndex(OdUInt32 uIndex) const;
  void     merge( const OdDgLevelMaterialAssignmentData& levelData );
  bool     isEmpty();

private:
  OdString            m_strLevelName;
  bool                m_colorAssign[256];
  std::set<OdUInt32>  m_rgbAssign;
};

//========================================================================================

/** \details
    Corresponding C++ library: TG_Db 
    <group OdDg_Classes>
*/
class TG_EXPORT OdDgMaterialAssignment
{
public:
  OdDgMaterialAssignment();
  virtual ~OdDgMaterialAssignment() {}

  OdUInt64 getMaterialId() const;
  void     setMaterialId( OdUInt64 uId );

  OdString getMaterialName() const;
  void     setMaterialName( const OdString& strName );

  OdUInt32 getLevelAssignmentCount() const;
  OdDgLevelMaterialAssignmentData getLevelAssignment( OdUInt32 uIndex ) const;
  void setLevelAssignment( OdUInt32 uIndex, const OdDgLevelMaterialAssignmentData& levelData );
  void addLevelAssignment( const OdDgLevelMaterialAssignmentData& levelData );
  void deleteLevelAssignment( OdUInt32 uIndex );

private:
  OdUInt64 m_uMaterialId;
  OdString m_strMaterialName;
  OdArray<OdDgLevelMaterialAssignmentData> m_levelAssignments;
};

//========================================================================================

/** \details
    Corresponding C++ library: TG_Db 
    <group OdDg_Classes>
*/
class TG_EXPORT OdDgMaterialAssignmentElementPE : public OdRxObject
{
  ODRX_DECLARE_MEMBERS(OdDgMaterialAssignmentElementPE);
  long        m_references;     //used by each object separately
public:

  OdDgMaterialAssignmentElementPE();
  virtual ~OdDgMaterialAssignmentElementPE() {}

  //OdRxObject overridden
  virtual void addRef();
  virtual void release();
  virtual long numRefs() const;

  OdDgElementId          getAssignedMaterialId( const OdDgMaterialTable* obj, const OdDgElementId& idLevel, OdUInt32 uColorIndex ) const;
  OdDgElementId          getRgbColorAssignedMaterialId( const OdDgMaterialTable* obj, const OdDgElementId& idLevel, ODCOLORREF rgbColor) const;
  OdUInt32               getMaterialAssignmentCount( const OdDgMaterialTable* obj ) const;
  OdDgMaterialAssignment getMaterialAssignment( const OdDgMaterialTable* obj, const OdDgElementId& idMaterial ) const;
  OdDgMaterialAssignment getMaterialAssignment( const OdDgMaterialTable* obj, const OdString& strMatName ) const;
  OdDgMaterialAssignment getMaterialAssignment( const OdDgMaterialTable* obj, OdUInt32 uIndex ) const;
  void                   setMaterialAssignment( OdDgMaterialTable* obj, OdUInt32 uIndex, const OdDgMaterialAssignment& assignment );
  void                   setMaterialAssignment( OdDgMaterialTable* obj, const OdDgElementId& idMaterial, const OdDgMaterialAssignment& assignment );
  void                   setMaterialAssignment( OdDgMaterialTable* obj, const OdString& strMatName, const OdDgMaterialAssignment& assignment );
  void                   addMaterialAssignment( OdDgMaterialTable* obj, const OdDgMaterialAssignment& assignment );
  void                   deleteMaterialAssignment( OdDgMaterialTable* obj, OdUInt32 uIndex );
  void                   deleteMaterialAssignment( OdDgMaterialTable* obj, const OdDgElementId& idMaterial );
  void                   deleteMaterialAssignment( OdDgMaterialTable* obj, const OdString& strMatName );

  void assignMaterial( OdDgMaterialTable* obj, const OdDgElementId& idLevel, OdUInt32 uColorIndex, const OdString& strMatName );
  void assignMaterial( OdDgMaterialTable* obj, const OdDgElementId& idLevel, OdUInt32 uColorIndex, const OdDgElementId& idMaterial );
  void removeMaterialAssignment( OdDgMaterialTable* obj, const OdDgElementId& idLevel, OdUInt32 uColorIndex, const OdString& strMatName );
  void removeMaterialAssignment( OdDgMaterialTable* obj, const OdDgElementId& idLevel, OdUInt32 uColorIndex, const OdDgElementId& idMaterial );

  void assignMaterialRgb(OdDgMaterialTable* obj, const OdDgElementId& idLevel, ODCOLORREF rgbColor, const OdString& strMatName);
  void assignMaterialRgb(OdDgMaterialTable* obj, const OdDgElementId& idLevel, ODCOLORREF rgbColor, const OdDgElementId& idMaterial);
  void removeMaterialAssignmentRgb(OdDgMaterialTable* obj, const OdDgElementId& idLevel, ODCOLORREF rgbColor, const OdString& strMatName);
  void removeMaterialAssignmentRgb(OdDgMaterialTable* obj, const OdDgElementId& idLevel, ODCOLORREF rgbColor, const OdDgElementId& idMaterial);
};

typedef OdSmartPtr<OdDgMaterialAssignmentElementPE> OdDgMaterialAssignmentElementPEPtr;

#include "TD_PackPop.h"

#endif // __DG_TABLE_H__
