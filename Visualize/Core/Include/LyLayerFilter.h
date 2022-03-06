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



#ifndef _OD_LY_H
#define _OD_LY_H

#include "TD_PackPush.h"

#include "RxObject.h"
#include "OdArray.h"
#include "DbObjectId.h"
#include "IdArrays.h"


class OdTvLyLayerFilter;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvLyLayerFilter object pointers.
*/
typedef OdSmartPtr<OdTvLyLayerFilter> OdTvLyLayerFilterPtr;
/** \details
  This template class is a specialization of the OdArray class for OdTvLyLayerFilter object pointers.
*/
typedef OdArray<OdTvLyLayerFilterPtr> OdTvLyLayerFilterArray;

class OdTvDbLayerTableRecord;
class OdTvDbDxfFiler;
class OdTvLySystemInternals;

/** \details
            
    Corresponding C++ library: TD_Db

    <group OdTvLy_Classes> 
*/
class OdTvLyRelExpr
{
public:
    virtual ~OdTvLyRelExpr() {}
    virtual const OdString& getConstant() const = 0;
    virtual const OdString& getVariable() const = 0;
protected:
    OdTvLyRelExpr() {}
};

/** \details
            
    Corresponding C++ library: TD_Db

    <group OdTvLy_Classes> 
*/
class OdTvLyAndExpr
{
public:
    virtual ~OdTvLyAndExpr() {}
    virtual const OdArray<OdTvLyRelExpr*>& getRelExprs() const = 0;
protected:
    OdTvLyAndExpr() {}
};

/** \details
            
    Corresponding C++ library: TD_Db

    <group OdTvLy_Classes> 
*/
class OdTvLyBoolExpr
{
public:
    virtual ~OdTvLyBoolExpr() {}
    virtual const OdArray<OdTvLyAndExpr*>& getAndExprs() const = 0;
protected:
    OdTvLyBoolExpr() {}
};

/** \details
    This class implements LayerFilter objects. 

    \remarks
    This class allows the client to specify, retrieve, and nest and unnest LayerFilters,
    and to determine if a layer is visible with for LayerFilter object.
    
    All Layer Filters implement this interface.
    \sa
    TD_Db
    <group OdTvLy_Classes> 
*/
class TOOLKIT_EXPORT OdTvLyLayerFilter : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvLyLayerFilter);
  OdTvLyLayerFilter();
  virtual ~OdTvLyLayerFilter();
  
  /** \details
    Returns the name of this LayerFilter object.
  */
  virtual const OdString& name() const;
  
  /** \details
    Sets the name of this LayerFilter object.
    \param name [in]  Name.
    
    \returns
    Returns true if and only if successful.
    \remarks
    Some LayerFilter objects do not allow renamimg; e.g., "All", "Xref".

  */
  virtual bool setName(
    const OdString& name);
    
  /** \details
    Returns true if and only if this LayerFilter object can be renamed.

    \remarks
    Some LayerFilter objects do not allow renamimg; e.g., "All", "Xref".
  */
  virtual bool allowRename() const;

  /** \details
    Returns the parent LayerFilter of this LayerFilter object.

    \remarks
    All LayerFilter objects, except the top level, "ALL", have parents.
  */
  virtual OdTvLyLayerFilter* parent() const;
  
  /** \details
    Returns the nested LayerFilters of this LayerFilter object.
  */
  virtual const OdTvLyLayerFilterArray& getNestedFilters() const;

  /** \details
    Adds the specified LayerFilter as a nested LayerFilter to this LayerFilter object.
    \param pLayerFilter [in]  Pointer to the LayerFilter to nest.
  */
  virtual void addNested(
    OdTvLyLayerFilter* pLayerFilter);
    
  /** \details
    Removes the specified LayerFilter as a nested LayerFilter of this LayerFilter object.
    \param pLayerFilter [in]  Pointer to the LayerFilter to remove.
  */
  virtual void removeNested(
    OdTvLyLayerFilter* pLayerFilter);
  
  /** \details
    Notification function called after a LayerFilter is loaded.
    
    \remarks
    This is an opportunity for a LayerFilter to automatically generate its nested filters.
  */
  virtual OdResult generateNested();
  
  
  /** \details
    Returns true if and only if this LayerFilter was dynamically generated.
    
    \remarks
    True indicates that this LayerFilter should not be persisted.
  */
  virtual bool dynamicallyGenerated() const;
  
  /** \details
    Returns true if and only if this LayerFilter allows nested LayerFilters.
  */
  virtual bool allowNested() const;
  
  /** \details
    Returns true if and only if this LayerFilter can be deleted.
  */
  virtual bool allowDelete() const;
  
  /** \details
    Returns true if and only if this LayerFilter is a proxy LayerFilter.
  */
  virtual bool isProxy() const;
  
  /** \details
    Returns true if and only if this LayerFilter filters for the Object ID of a LayerTableRecord.
    
    \remarks
    These filters are known as LayerGroups.
  */
  virtual bool isIdFilter() const;
  
  /** \details
    Returns true if and only if the specified layer is visible with this LayerFilter object.
    \param layer [in]  Layer.
  */
  virtual bool filter(
    OdTvDbLayerTableRecord* layer) const;
  
  /** \details
    Returns the filter expression for this LayerFilter object.
    
    BNF for the valid boolean expression:
    <bool_expr>::= <bool_expr> or <and_expr> | <and_expr>
    <and_expr>::=<and_expr> and <rel_expr> | <rel_expr>
    <rel_expr>::=<variable><rel_op><constant> 
    <rel_op>::= == | !=
    <constant>::=A-Z0-9*?~@.,-
    <variable>::=#A-Z0-9

    Supported variables are:

    NAME
    LOCKED
    PLOTTABLE
    LINETYPE
    LINEWEIGHT
    COLOR
    OFF
    FROZEN
    PLOTSTYLENAME
    NEWVPFROZEN
    VP
    VPFROZEN
    VPCOLOR
    VPLINETYPE
    VPLINEWEIGHT
  */
  virtual const OdString& filterExpression() const;

  /** \details
    Returns the filter expression for this LayerFilter object.
  */
  const OdTvLyBoolExpr* filterExpressionTree() const;
  
  /** \details
    Sets the filter expression for this LayerFilter object.
    \param filterExpression [in]  Filter expression.
  */
  virtual OdResult setFilterExpression(
     const OdString& filterExpression );
  
  
  /** \details
    Returns true if and only if this LayerFilter object and the specified LayerFilter
    object allow the same layers.
    \param pOther [in]  Pointer to the other LayerFilter.
  */
  virtual bool compareTo(
    const OdTvLyLayerFilter* pOther) const;
  
  /** \details
    Reads the DXF format data of this object from the specified filter.
    \param pFiler [in]  Pointer to the filer from which data are to be read.
  */
  virtual OdResult readFrom(
    OdTvDbDxfFiler* pFiler);
    
  /** \details
    Writes the DXF format data of this object to the specified filter.
    \param pFiler [in]  Pointer to the filer to which data are to be written.
  */
  virtual void writeTo(
    OdTvDbDxfFiler* pFiler) const;
  
private:
  void* m_pImpl;
  friend class OdTvLySystemInternals;
  
protected:
  OdTvLyLayerFilter( OdTvLySystemInternals* );
};


/** \details
    This class implements LayerGroup objects. 

    \remarks
    This class allows the client to specify, retrieve, and group and ungroup layers,
    and to determine if a layer is grouped within a LayerGroup object.

    \sa
    TD_Db
    <group OdTvLy_Classes> 
*/
class TOOLKIT_EXPORT OdTvLyLayerGroup : public OdTvLyLayerFilter
{
public:
  ODRX_DECLARE_MEMBERS(OdTvLyLayerGroup);
  OdTvLyLayerGroup();
  
  /** \details
    Adds the specified layer to this LayerGroup object.
    \param layerId [in]  Object ID of the OdTvDbLayerTableRecord.
  */
  virtual void addLayerId(
    const OdTvDbObjectId& layerId);
    
  /** \details
    Removes the specified layer to this LayerGroup object.
    \param layerId [in]  Object ID of the OdTvDbLayerTableRecord.
  */
  virtual void removeLayerId (
    const OdTvDbObjectId& layerId);
  
  /** \details
    Returns the LayerTableRecord Object IDs in this LayerGroup object.
  */
  virtual const OdTvDbObjectIdArray& layerIds() const;
  
protected:
  OdTvLyLayerGroup( OdTvLySystemInternals* );
};

typedef OdSmartPtr<OdTvLyLayerGroup> OdTvLyLayerGroupPtr;

/** \details
    This class simplifies accessing LayerFilter objects in the LayerTable extension dictionary.
    \sa
    TD_Db
    <group OdTvLy_Classes> 
*/
class OdTvLyLayerFilterManager : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvLyLayerFilterManager);
  /** \details
    Returns the root and current filters from the database containing this LayerFilterManager object.
    \param pRoot [out]  Receives a SmartPointer to the root filter.
    \param pCurrent [out]  Receives a SmartPointer to the filter current when setFilters() was last called.  
  */
  virtual OdResult getFilters(
    OdTvLyLayerFilterPtr& pRoot, 
    OdTvLyLayerFilterPtr& pCurrent ) = 0;
  
  /** \details
    Writes the filter tree and current filters to the database containing this LayerFilterManager object.
    \param pRoot [in]  Pointer to the root filter.
    \param pCurrent [in]  Pointer to the current filter to be persisted.  
  */
  virtual void setFilters(
    const OdTvLyLayerFilterPtr pRoot, 
    const OdTvLyLayerFilterPtr pCurrent ) = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvLyLayerFilterManager object pointers.
*/
typedef OdSmartPtr<OdTvLyLayerFilterManager> OdTvLyLayerFilterManagerPtr;

/** \details
  Returns a LayerFilterManager object for the specified database.
  \param pDb [in]  Pointer to the database.
*/
TOOLKIT_EXPORT OdTvLyLayerFilterManagerPtr odlyGetLayerFilterManager(
  OdTvDbDatabase* pDb );

#include "TD_PackPop.h"

#endif  // _OD_LY_H
