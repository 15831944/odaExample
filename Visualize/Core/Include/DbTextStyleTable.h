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




#ifndef _ODDBTEXTSTYLETABLE_INCLUDED
#define _ODDBTEXTSTYLETABLE_INCLUDED

#include "TD_PackPush.h"

#include "DbSymbolTable.h"
#include "DwgDeclareMembers.h"

class OdTvDbTextStyleTableRecord;

/** \details
  <group OdTvDb_Classes>

  This class implements the text style table object, which represents a container for 
  storing and accessing of text style record objects in the database. This class inherits 
  the base functionality of predefined tables.

  \sa
  TD_Db

  \sa
  <link db_textstyle_sample_table.html, Example of Working with the Text Style Table Object>

  <link db_textstyle_sample_record.html, Example of Working with the Text Style Record Object>

  \sa
  <link db_textstyle.html, Working with Text Styles>

  OdTvDbTextStyleTableRecord class
*/
class TOOLKIT_EXPORT OdTvDbTextStyleTable: public OdTvDbSymbolTable
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbTextStyleTable);

  /** \details
    Builds an instance of the text style table object.
    
    Applications typically will not use this constructor, insofar as the database object 
    creates own instance of the text style table. The text style table object exists in 
    the database a prior.
  */
  OdTvDbTextStyleTable();

  typedef OdTvDbTextStyleTableRecord RecordType;

 /* virtual OdResult subGetClassID(
    void* pClsid) const;*/

  /** \details
    Adds an instance of the text style record object in the container of the text style table 
    object. This method is inherited from the OdTvDbSymbolTable class which is base class for all 
    predefined tables. For more details, see: OdTvDbSymbolTable::add() method.
  */
  virtual OdTvDbObjectId add( OdTvDbSymbolTableRecord* pRecord );
};

/** \details
  The typified smart pointer for the text style table object. This template class is specialization 
  of the OdSmartPtr class for the OdTvDbTextStyleTable object.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbTextStyleTable> OdTvDbTextStyleTablePtr;

#include "TD_PackPop.h"

#endif // _ODDBTEXTSTYLETABLE_INCLUDED

