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
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockUserParameter : public OdDbBlock1PtParameter
{
public:
  //DOM-IGNORE-BEGIN
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockUserParameter);
  //DOM-IGNORE-END

  /** \details
    Creates a new instance of an OdDbBlockUserParameter object with default parameters.
  */
  OdDbBlockUserParameter();

  /** \details
    Defines user parameter types.
  */
  enum UserParameterType 
  {
    /** User parameter type is distance. */
    kDistance = 0,
    /** User parameter type is area. */
    kArea = 1,
    /** User parameter type is volume. */
    kVolume = 2,
    /** User parameter type is floating point value. */
    kReal = 3,
    /** User parameter type is angle. */
    kAngle = 4,
    /** User parameter type is string. */
    kString = 5
  };

  /** \details
    Gets the associated variable ID.

    \returns Associated variable ID as an OdDbObjectId object.
  */
  OdDbObjectId assocVarId() const;

  /** \details
    Sets an associated variable ID.

    \param id [in] ID to set.
  */
  void setAssocVarId(OdDbObjectId id);

  /** \details
    Gets the user variable name.

    \returns User variable name as an OdString value.
    \remarks
    Returns OdString::kEmpty if variable is NULL or if there is no associated variable for this parameter.
  */
  OdString userVarName() const;
  //OdResult setUserVarName(const OdString&);

  /*

  virtual OdString expression()const;
  virtual void setExpression(const OdString&);

  virtual UserParameterType userParameterType()const;
  virtual void setUserParameterType(UserParameterType t);

  virtual OdString userVarDescription()const;
  virtual void setUserVarDescription(const OdString&);


  OdResult convertValue(OdResBuf*)const;
*/
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbBlockUserParameter objects.
*/
typedef OdSmartPtr<OdDbBlockUserParameter> OdDbBlockUserParameterPtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdDb_Classes>
*/
class OdDbBPTAuditError
{
public:
/** \details
  Defines the audit error types for a block properties table.
*/
  enum BPTAuditErrorType {
    /** Empty. */
    empty,
    /** No matching row. */
    noMatchingRow,
    /** Invalid cell. */
    invalidCell,
    /** No in value set. */
    notInValueSet,
    /** Non-constant attribute definition. */
    nonConstAttDef,
    /** Invalid unmatched value. */
    invalidUnmatchedValue,
    /** Duplicate rows. */
    duplicateRows,
    /** Expression external reference. */
    exprExternRef,
    /** Cell evaluation error. */
    cellEvalError
  };

  /** \details
    Gets the error type.

    \returns One of the enumerated items from the BPTAuditErrorType enumerated type.
  */
  BPTAuditErrorType errorType() const { return m_Type; }

  /** \details
    Gets the index of a cell.

    \param row [out] Receives the row of the cell.
    \param col [out] Receives the column of the cell.
  */
  void getCellIndex(int& row, int& col)const { row = m_nRow; col = m_nCol; }

  /** \details
    Gets the column index.

    \returns The column index as an integer value.
  */
  int getColumnIndex()const { return m_nCol; }

  /** \details
    Gets the row indices.

    \returns The array of row indices.
  */
  OdIntArray getRowIndex() const { return m_Rows; }

  /** \details
    Gets the unmatched value index.

    \returns The unmatched value index.
  */
  int getUnmatchedValueIndex()const { return m_nRow; }
protected:
  BPTAuditErrorType m_Type;
  int m_nRow;
  int m_nCol;
  OdIntArray m_Rows;
};

/** \details
    Corresponding C++ library:  TD_Db
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockPropertiesTable : public OdDbBlock1PtParameter
{
public:
  //DOM-IGNORE-BEGIN
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockPropertiesTable);
  //DOM-IGNORE-END

  /** \details
    Creates a new instance of an OdDbBlockPropertiesTable object with default parameters.
  */
  OdDbBlockPropertiesTable();
  
  /** \details
    Returns the number of columns in the table.

    \returns The number of columns in the table.
  */
  int numberOfColumns() const;
  
  /** \details
    Returns the number of rows in the table.

    \returns The number of rows in the table.
  */
  int numberOfRows() const;
  
  /** \details
    Returns the value of the specified cell.

    \param column [in] Column index.
    \param row [in] Row index.
    \param rb [out] Receives a copy of the cell value.
    \returns Returns eOk if the indices are valid, or eInvalidIndex otherwise.
  */
  OdResult getCellValue(int column, int row, OdResBufPtr &rb) const;

  /** \details
    Sets the value of the specified cell.

    \param column [in] Column index.
    \param row [in] Row index.
    \param rb [out] The cell value to set.
    \returns Returns eOk if the indices are valid, or eInvalidInput otherwise.
  */
  OdResult setCellValue(int column, int row, const OdResBuf* rb);

  /** \details
    Returns the value of the specified cell as an OdString value.

    \param column [in] Column index.
    \param row [in] Row index.
    \param s [out] Receives a copy of the cell value as an OdString value.
    \returns Returns eOk if the indices are valid, or eInvalidIndex otherwise.
  */
  OdResult getCellValueString(int column, int row, OdString &s) const;

  // column flags
  /** \details
    Checks whether the specified column is constant.

    \param column [in] Column index.
    \returns The true value if the specified column is constant, or false otherwise.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  bool constant(int column) const;

  /** \details
    Specifies whether the column is constant.

    \param column [in] Column index.
    \param val [in] Specify true to set that the column is constant, or false otherwise.
    \returns Returns eOk if the column is set to constant successfully, or eInvalidIndex otherwise.
  */
  OdResult setConstant(int column, bool val);

  /** \details
    Checks whether the specified column is editable.

    \param column [in] Column index.
    \returns The true value if the specified column is editable, or false otherwise.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  bool editable(int column) const;

  /** \details
    Specifies whether the column is editable.

    \param column [in] Column index.
    \param val [in] Specify true to set that the column is editable, or false otherwise.
    \returns Returns eOk if the index is valid, or eInvalidIndex otherwise.
  */
  OdResult setEditable(int column, bool val);
  
  /** \details
    Checks whether the specified column is removable.

    \param column [in] Column index.
    \returns The true value if the specified column is removable, or false otherwise.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  bool removable(int column) const;

  /** \details
    Specifies whether the column is removable.

    \param column [in] Column index.
    \param val [in] Specify true to mark the column as removable, or false otherwise.
    \returns Returns eOk if the index is valid, or eInvalidIndex otherwise.
  */
  OdResult setRemovable(int column, bool val);
  
  /** \details
    Checks whether the specified column is angular.

    \param column [in] Column index.
    \returns The true value if the specified column is angular, or false otherwise.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  bool isAngular(int column) const;

  /** \details
    Checks whether the specified column is an attribute.

    \param column [in] Column index.
    \returns The true value if the specified column is an attribute, or false otherwise.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  bool isAttribute(int) const;

  // column properties
  /** \details
    Gets the ID of the custom properties.

    \param column [in] Column index.
    \returns The ID of the custom properties.
    \remarks
    The ID of the custom properties is optional. The default value is NULL.
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  OdDbObjectId customProperties(int column) const;

  /** \details
    Sets the ID of the custom properties.

    \param column [in] Column index.
    \param id [in] ID of the custom properties.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  void setCustomProperties(int column, const OdDbObjectId& id);

  /** \details
    Gets the default value of the specified column.

    \param column [in] Column index.
    \returns Pointer to the default value of the specified column as an OdResBufPtr object.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  OdResBufPtr defaultValue(int column) const;

  /** \details
    Sets the default value of the specified column.

    \param column [in] Column index.
    \param rb [in] Pointer to the default value of the specified column.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  void setDefaultValue(int column, const OdResBuf* rb);
  
  /** \details
    Gets the format of the specified column.

    \param column [in] Column index.
    \returns Format of the specified column as an OdString object.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  OdString format(int column) const;

  /** \details
    Sets the format of the specified column.

    \param column [in] Column index.
    \param f [in] Format of the specified column.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  void setFormat(int column, const OdString& f);

  // if the values of the parameters must match some rows
  /** \details
    Checks whether the values of the parameters must match some rows.

    \returns The true value if the values of the parameters must match some rows, or false otherwise.
  */
  bool mustMatch() const;

  /** \details
    Specifies whether the values of the parameters must match some rows.

    \param b [in] Specify true to set that the values of the parameters must match some rows, or false otherwise.
  */
  void setMustMatch(bool b);

  // what is used in the context menu if parameter values do not match anything
  /** \details
    Sets the unmatched value of the specified column.

    \param column [in] Column index.
    \param rb [in] Unmatched value of the specified column.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  void setUnmatchedValue(int column, const OdResBuf* rb);

  /** \details
    Gets the unmatched value of the specified column.

    \param column [in] Column index.
    \returns Unmatched value of the specified column as an OdResBufPtr object.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  OdResBufPtr unmatchedValue(int column) const;

  /** \details
    Gets the name of the column.

    \param column [in] Column index.
    \returns The name of the column.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
    Returns OdString::kEmpty if the object specified with the column is NULL or if the object does not belong to any of these types: 
    * OdDbBlockUserParameter
    * OdDbBlockParameter
    * OdDbAttributeDefinition
    * OdDbAttributeDefinitionPtr
  */
  OdString getColumnName(int column) const;

  // Table description (used as a property description)
  /** \details
    Gets the table description.

    \returns The table description as an OdString value.
    \remarks
    The returned value is used as the corresponding UI property description.
  */
  OdString tableDescription() const;

  /** \details
    Sets the table description.

    \param s [in] The table description.
    \remarks
    The parameter value is used as the corresponding UI property description.
  */
  void setTableDescription(const OdString& s);

  // Table name (used as a property name)
  /** \details
    Gets the name of the table.

    \returns The name of the table as an OdString value.
    \remarks
    The returned value is used as the corresponding UI property name.
  */
  OdString tableName() const;
  /** \details
    Gets the name of the table.

    \param s [in] The name of the table.
    \remarks
    The parameter value is used as the corresponding UI property name.
  */
  void setTableName(const OdString& s);

  // rows may be reordered, but each row has unique (within the table) id that will not change
  /** \details
    Gets the ID of the specified row.

    \param index [in] Row index.
    \returns The ID of the specified row as an integer value.
    \remarks
    Returns -1 if the index is not valid.
    Rows may be reordered, but each row has a unique (within the table) ID that does not change.
  */
  int idOfRow(int index) const;

  /** \details
    Gets the index of the specified row ID.

    \param id [in] Row ID.
    \returns The index of the specified row ID.
    \remarks
    Returns -1 if the index is not valid.
    Rows may be reordered, but each row has a unique (within the table) ID that does not change.
  */
  int indexOfRow(int id) const;

  /** \details
    Inserts a column after the specified index.

    \param param [in] ID of the column.
    \param connection [in] Connection for the column.
    \param after [in] Index of the column after which to insert.
    \remarks
    Throws the eInvalidIndex exception if the specified index is not valid.
  */
  void insertColumn(const OdDbObjectId& param, const OdString& connection, int after);

  /** \details
    Inserts a row after the specified index.

    \param after [in] Index of the row after which to insert.
    \remarks
    Throws the eInvalidIndex exception if the specified index is not valid.
  */
  void insertRow(int after);

  /** \details
    Removes the column at the specified index.

    \param column [in] Index of column.
    \remarks
    Throws the eInvalidIndex exception if the specified index is not valid.
  */
  void removeColumn(int column);

  /** \details
    Removes the row at the specified index.

    \param row [in] Index of row.
    \remarks
    Throws the eInvalidIndex exception if the specified index is not valid.
  */
  void removeRow(int row);

  /** \details
    Appends the column.

    \param param [in] ID of the column.
    \param connection [in] Connection for the column.
  */
  void appendColumn(const OdDbObjectId& param, const OdString& connection);

  /** \details
    Appends the row.
  */
  void appendRow();

  /** \details
    Moves the column from the original position to a new position.

    \param from [in] Index from which to move the column.
    \param to [in] Index to which to move the column.
    \remarks
    Throws the eInvalidIndex exception if the from or to index is not valid.
    If the from and to indices are equal, exits the function.
  */
  void moveColumn(int from, int to);

  /** \details
    Moves the row from the original position to a new position.

    \param from [in] Index from which to move the row.
    \param to [in] Index to which to move the row.
    \remarks
    Throws the eInvalidIndex exception if the from or to indices are not valid.
    If the from and to indices are equal, exits the function.
  */
  void moveRow(int from, int to);
  
  /** \details
    Gets the node ID of a block properties table.

    \param gr [in] Eval graph.
    \returns The block properties table node ID.
    \remarks
    The block properties table node ID is stored in the eval graph xdata, and reactors keep it updated.
  */
  static OdDbEvalNodeId bptNodeId(const OdDbEvalGraph* gr);
  virtual void addedToGraph(OdDbEvalGraph* ) ODRX_OVERRIDE;
  virtual void erased(const OdDbObject* , bool) ODRX_OVERRIDE;
  virtual void removedFromGraph(OdDbEvalGraph* gr) ODRX_OVERRIDE;
  
  // Look for a row matching default parameter values
  /** \details
    Looks for a row that matches the default parameter values.

    \returns -1
    \remarks
    Always returns -1.
  */
  int getDefaultActiveRow() const;
  
  // this function actually changes default values of the parameters used in the table
  /** \details
    Changes the default values of the parameters used in the table.

    \param row [in] Row index.
    \remarks
    Throws the eNotImplemented exception.
  */
  void setDefaultActiveRow(int row);
  
  /** \details
    Checks whether the column values are unique.

    \param col [in] Column index.
    \returns The true value if the column values are unique, or false otherwise.
    \remarks
    Throws the eInvalidIndex exception if the column index is not valid.
  */
  bool columnValuesAreUnique(int col)const;
  // (not implemented, no idea what it does)

  /** \details
    Not implemented.

    \returns The false value.
  */
  bool disabledInDrawingEditor() const;
  
  // doesn't seem to have any effect besides the flag
  /** \details
    Checks whether the parameters are only runtime.

    \returns The true value if the parameters are only runtime, or false otherwise.
  */
  bool runtimeParametersOnly()const;

  /** \details
    Specifies whether the parameters are only runtime parameters.

    \param b [in] Specify true to set the parameters for only runtime, or false otherwise.
  */
  void setRuntimeParametersOnly(bool b);
  
  // look at the OdDbBPTAuditError::BPTAuditErrorType for possible error types
  /** \details
    Gets the column information into an array.

    \remarks
    Refer to the OdDbBPTAuditError::BPTAuditErrorType enumerated type for the available error types.
  */ 
  void tableAudit(OdArray<OdDbBPTAuditError>&);
  
  // sort the rows (duh)
  /** \details
    Sorts the rows.

    \param column [in] Column index.
    \param ascending [in] Specify true to sort by ascending, or false to sort by descending.
    \remarks
    Throws the eInvalidIndex exception if the from or to indcies are not valid.
  */
  void sortRows(int column, bool ascending);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbBlockPropertiesTable objects.
*/
typedef OdSmartPtr<OdDbBlockPropertiesTable> OdDbBlockPropertiesTablePtr;

/** \details
    Corresponding C++ library:  TD_Db
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockPropertiesTableGrip : public OdDbBlockGrip
{
public:
  //DOM-IGNORE-BEGIN
  ODDB_DECLARE_MEMBERS(OdDbBlockPropertiesTableGrip);
  //DOM-IGNORE-END

  /** \details
    Creates a new instance of an OdDbBlockPropertiesTableGrip object with default parameters.
  */
  OdDbBlockPropertiesTableGrip();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbBlockPropertiesTableGrip objects.
*/
typedef OdSmartPtr<OdDbBlockPropertiesTableGrip> OdDbBlockPropertiesTableGripPtr;

#endif //_DbBlockPropertiesTable_h_Included_
