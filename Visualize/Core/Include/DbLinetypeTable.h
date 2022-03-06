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




#ifndef _ODDBLINETYPETABLE_INCLUDED
#define _ODDBLINETYPETABLE_INCLUDED

#include "TD_PackPush.h"

#include "DbSymbolTable.h"
#include "DwgDeclareMembers.h"

class OdTvDbLinetypeTableRecord;

/** \details
  <group OdTvDb_Classes>

  This class implements bidirectional iterator for instances of the linetype record object
  within the linetype table object.

  Corresponding C++ library: TD_Db

  \sa
  <link db_linetype_sample_table.html, Example of Working with the Linetype Table Object>

  \sa
  <link db_linetype_iterate.html, Iterating through Linetypes>

  OdTvDbSymbolTableIterator class
*/
class TOOLKIT_EXPORT OdTvDbLinetypeTableIterator : public OdTvDbSymbolTableIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbLinetypeTableIterator);

protected:
  /** \details
    Builds an instance of the linetype iterator object.
    
    \remarks
    Use the OdTvDbLinetypeTable::newIterator() method instead it.
  */
  OdTvDbLinetypeTableIterator();
  OdTvDbLinetypeTableIterator( OdTvDbSymbolTableIteratorImpl* pImpl );
};

/** \details
  The typified smart pointer for the linetype iterator object. This template class is specialization 
  of the OdSmartPtr class for the OdTvDbLinetypeTableIterator object.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbLinetypeTableIterator> OdTvDbLinetypeTableIteratorPtr;


/** \details
  <group OdTvDb_Classes>

  This class implements the linetype table object, which represents a container for storing 
  and accessing of linetype record objects in the database. This class inherits the base 
  functionality of predefined tables.

  \sa
  TD_Db

  \sa
  <link db_linetype_sample_table.html, Example of Working with the Linetype Table Object>

  <link db_linetype_sample_record.html, Example of Working with the Linetype Record Object>

  \sa
  <link db_linetype.html, Working with Linetypes>

  OdTvDbLinetypeTableRecord class
*/
class TOOLKIT_EXPORT OdTvDbLinetypeTable : public OdTvDbSymbolTable
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbLinetypeTable);

  /** \details
    Builds an instance of the linetype table object.
    
    Applications typically will not use this constructor, insofar as the database object 
    creates own instance of the linetype table. The linetype table object exists in the  
    database a prior.
  */
  OdTvDbLinetypeTable();


  /** \details
    Gets a linetype record object from the linetype table object. This method is inherited
    from the OdTvDbSymbolTable class which is base class for all predefined tables. For more details, 
    see: OdTvDbSymbolTable::getAt() method.
  */
  virtual OdTvDbObjectId getAt( const OdString& recordName, 
                              bool getErasedRecord = false) const;
  OdTvDbSymbolTableRecordPtr getAt( const OdString& recordName,
                                  OdDb::OpenMode openMode, 
                                  bool getErasedRecord = false) const;

  /** \details
    Checks whether the linetype table object contains the linetype record object specified by 
    the name. This method is inherited from the OdTvDbSymbolTable class which is base 
    class for all predefined tables. For more details, see: OdTvDbSymbolTable::has() method.
  */
  bool has( const OdString& recordName ) const;
  
  /** \details
    Checks whether the linetype table object contains the linetype record object specified by 
    the Object ID. This method is inherited from the OdTvDbSymbolTable class which is base 
    class for all predefined tables. For more details, see: OdTvDbSymbolTable::has() method.
  */
  bool has( const OdTvDbObjectId& objectId ) const;


  /** \details
    Adds an instance of the linetype record object in the container of the linetype table object.
    This method is inherited from the OdTvDbSymbolTable class which is base class for all predefined 
    tables. For more details, see: OdTvDbSymbolTable::add() method.
  */
  virtual OdTvDbObjectId add( OdTvDbSymbolTableRecord* pRecord );


  /** \details
    Creates an instance of the linetype iterator object which is the bidirectional iterator for 
    traversing through linetype record objects in the container of the linetype table object.
    This method is inherited from the OdTvDbSymbolTable class which is base class for all predefined 
    tables. For more details, see: OdTvDbSymbolTable::newIterator() method.
  */
  OdTvDbSymbolTableIteratorPtr newIterator( 
    bool atBeginning = true, 
    bool skipDeleted = true) const;


  /** \details
    Returns the Object ID of the predefined linetype record object assigned as "ByLayer" linetype 
    in the database.

    \sa
    <link db_linetype_collection.html, Organization of Linetypes>

    OdTvDbDatabase::getLinetypeByLayerId(), OdTvDbDatabase::getLinetypeByBlockId(), 
    OdTvDbDatabase::getLinetypeContinuousId() methods
  */
  const OdTvDbObjectId& getLinetypeByLayerId() const;

  /** \details
    Returns the Object ID of the predefined linetype record object assigned as "ByBlock" linetype 
    in the database.

    \sa
    <link db_linetype_collection.html, Organization of Linetypes>

    OdTvDbDatabase::getLinetypeByLayerId(), OdTvDbDatabase::getLinetypeByBlockId(), 
    OdTvDbDatabase::getLinetypeContinuousId() methods
  */
  const OdTvDbObjectId& getLinetypeByBlockId() const;


  /*virtual OdResult subGetClassID( void* pClsid ) const;*/

  virtual OdResult dwgInFields( OdTvDbDwgFiler* pFiler );

  virtual void dwgOutFields( OdTvDbDwgFiler* pFiler ) const;

  virtual void dxfOut( OdTvDbDxfFiler* pFiler ) const;

  /*
    virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
    virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  */
};

/** \details
  The typified smart pointer for the linetype table object. This template class is specialization 
  of the OdSmartPtr class for the OdTvDbLinetypeTable object.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbLinetypeTable> OdTvDbLinetypeTablePtr;

#include "TD_PackPop.h"

#endif // _ODDBLINETYPETABLE_INCLUDED

