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

#ifndef _DbBlockPropertiesTable_h_Included_
#define _DbBlockPropertiesTable_h_Included_

#include "DbBlock1PtParameter.h"
#include "DbBlockGrips.h"

/** \details
    Corresponding C++ library:  TD_DynBlocks
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockUserParameter : public OdTvDbBlock1PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockUserParameter);
  OdTvDbBlockUserParameter();
  enum UserParameterType 
  {
    kDistance = 0,
    kArea = 1,
    kVolume = 2,
    kReal = 3,
    kAngle = 4,
    kString = 5
  };

  OdTvDbObjectId assocVarId() const;
  void setAssocVarId(OdTvDbObjectId);

  OdString userVarName() const;
  //OdResult setUserVarName(const OdString&);

  /*

  virtual OdString expression()const;
  virtual void setExpression(const OdString&);

  virtual UserParameterType userParameterType()const;
  virtual void setUserParameterType(UserParameterType t);

  virtual OdString userVarDescription()const;
  virtual void setUserVarDescription(const OdString&);


  OdResult convertValue(OdTvResBuf*)const;
*/
};
typedef OdSmartPtr<OdTvDbBlockUserParameter> OdTvDbBlockUserParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockPropertiesTable : public OdTvDbBlock1PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockPropertiesTable);
  OdTvDbBlockPropertiesTable();
  
  /** \details
    Returns the number of columns in the table.
  */
  int numberOfColumns() const;
  
  /** \details
    Returns the number of rows in the table.
  */
  int numberOfRows() const;
  
  /** \details
    Returns the value of the specified cell.

    \param column [in] Column index.
    \param row [in] Row index.
    \param rb [out] Receives a copy of the cell value.
    \returns Returns eOk if the indices are valid, eInvalidIndex otherwise.
  */
  OdResult getCellValue(int column, int row, OdTvResBufPtr &rb) const;

  OdResult getCellValueString(int column, int row, OdString &) const;

  // column flags
  bool constant(int column) const;
  OdResult setConstant(int column, bool);
  bool editable(int column) const;
  OdResult setEditable(int column, bool);
  bool removable(int column) const;
  OdResult setRemovable(int column, bool);
  bool isAngular(int column) const;
  bool isAttribute(int) const;

  // column properties
  OdTvDbObjectId customProperties(int column) const;
  void setCustomProperties(int column, const OdTvDbObjectId& id);
  OdTvResBufPtr defaultValue(int column) const;
  void setDefaultValue(int column, const OdTvResBuf*);
  OdString format(int column) const;
  void setFormat(int column, const OdString&);
  void setUnmatchedValue(int column, const OdTvResBuf*);
  OdTvResBufPtr unmatchedValue(int column) const;

  OdString getColumnName(int column) const;

  // all the rest of the API is not implemented
  /*
  OdResult getFirstKeyColumn(int &) const;
  OdResult appendColumn(OdTvDbObjectId const &, const OdString&);
  OdResult appendRow();
  OdResult setCellValue(int column, int row, const OdTvResBuf*);
  OdResult getNextKeyColumn(int column, int &) const;
  int idOfRow(int index) const;
  int indexOfRow(int id) const;
  OdResult insertColumn(OdTvDbObjectId const &, const OdString&, int);
  OdResult insertRow(int after);
  OdResult moveColumn(int from, int to);
  OdResult moveRow(int from, int to);
  OdResult removeColumn(int column);
  OdResult removeRow(int row);
  bool mustMatch() const;
  void setMustMatch(bool);
  OdResult sortRows(int, bool);
  OdString tableDescription() const;
  OdResult setTableDescription(const OdString&);
  OdString tableName() const;
  OdResult setTableName(const OdString&);
  bool getKeyValue(int, unsigned int &) const;
  OdResult setKeyValue(int, unsigned int);
  OdResult unsetKeyValue(int);
  OdResult getDefaultActiveRow(int &) const;
  OdResult setDefaultActiveRow(int);
  */
};
typedef OdSmartPtr<OdTvDbBlockPropertiesTable> OdTvDbBlockPropertiesTablePtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockPropertiesTableGrip : public OdTvDbBlockGrip
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockPropertiesTableGrip);
  OdTvDbBlockPropertiesTableGrip();
};
typedef OdSmartPtr<OdTvDbBlockPropertiesTableGrip> OdTvDbBlockPropertiesTableGripPtr;

#endif //_DbBlockPropertiesTable_h_Included_
