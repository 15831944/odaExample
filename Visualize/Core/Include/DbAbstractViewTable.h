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




#ifndef _ODDBABSTRACTVIEWTABLE_INCLUDED
#define _ODDBABSTRACTVIEWTABLE_INCLUDED

#include "DbSymbolTable.h"

class OdTvDbAbstractViewTableRecord;

/** \details
    This class is the base class for OdTvDbViewTable and OdTvDbViewportTable.

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class TOOLKIT_EXPORT OdTvDbAbstractViewTable : public OdTvDbSymbolTable
{
public:

  ODDB_DECLARE_MEMBERS(OdTvDbAbstractViewTable);

  /** \details
    Client applications typically do not use this constructor, insofar as 
    this class is a base class.
  */
  OdTvDbAbstractViewTable();

//  void getAt(const OdChar* entryName, OdTvDbAbstractViewTableRecord** pRec,
//    OdDb::OpenMode openMode, bool openErasedRec = false) const;

//  OdTvDbObjectId getAt(const OdChar* entryName, bool getErasedRecord = false) const;

//  bool has(const OdChar* name) const;
//  bool has(const OdTvDbObjectId& id) const;

//  void newIterator(OdTvDbAbstractViewTableIterator** pIterator,
//    bool atBeginning = true, bool skipDeleted = true) const;

//  virtual const OdTvDbObjectId& add(OdTvDbSymbolTableRecord* pRecord);

};

#endif // _ODDBABSTRACTVIEWTABLE_INCLUDED

