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




#ifndef OD_DBSORTENTSTABLE_H
#define OD_DBSORTENTSTABLE_H

#include "TD_PackPush.h"

#include "DbObject.h"

#define STL_USING_UTILITY
#include "OdaSTL.h"

/** \details
    This template class is a specialization of the std::pair class for OdDbHandle-OdTvDbSoftPointerId pairs.
*/
typedef std::pair<OdDbHandle, OdTvDbSoftPointerId> TvHandlePair;

/** \details
    This template class is a specialization of the OdArray class for OdDbHandle-OdTvDbSoftPointerId pairs.
*/
typedef OdArray<TvHandlePair> TvHandlePairsArray;


/** \details
    This class implements the SortentsTable, which specifies the DrawOrder 
    of entities in an OdTvDbDatabase instance.

    \remarks
    Each instance of this class contains the DrawOrder for a single OdTvDbBlockRecord. 
    
    When drawing entities in a Block Table Record, an iterator traverses the Block Table Record 
    in the order of ascending handles. If there is a TvHandlePair in the SortentsTable corresponding
    to the handle of the object about to be drawn, the entity specified by the entity ID in the TvHandlePair is
    drawn in its stead. If there is no such TvHandlePair, the entity referenced by the iterator is drawn.
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbSortentsTable : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSortentsTable);

  OdTvDbSortentsTable();

  /** \details
    Function returns the handle that indicates the draw order.
  */
  void getSortHandle(const OdTvDbObjectId& id, OdDbHandle& h) const;

  /** \details
    Moves the entities with specified entity IDs to the bottom of this SortentsTable.

    \param entityIds [in]  Entity IDs.
  */
  void moveToBottom(
    OdTvDbObjectIdArray& entityIds);

  /** \details
    Moves the entities with specified entity IDs to the top of this SortentsTable.

    \param entityIds [in]  Entity IDs.
  */
  void moveToTop(
    OdTvDbObjectIdArray& entityIds); 

  /** \details
    Moves the entities with specified entity IDs below the target entity in this SortentsTable.

    \param entityIds [in]  Entity IDs.
    \param targetId [in]  Target entity ID.
  */
  void moveBelow(
    OdTvDbObjectIdArray& entityIds, 
    OdTvDbObjectId targetId);

  /** \details
    Moves the entities with specified entity IDs above  the target entity in this SortentsTable.

    \param entityIds [in]  Entity IDs.
    \param targetId [in]  Target entity ID.
  */
  void moveAbove(
    OdTvDbObjectIdArray& entityIds, 
    OdTvDbObjectId targetId);

  /** \details
    Swaps the DrawOrder of the specified entities in this SortentsTable.
    
    \param firstId [in]  First entity ID.
    \param secondId [in]  Second entity ID.
  */
  void swapOrder(
    OdTvDbObjectId firstId, 
    OdTvDbObjectId secondId);

  /** \details
    Returns the Object ID of the Block Table Record to which this SortentsTable belongs.
  */
  OdTvDbObjectId  blockId() const; 
        
  ///  2005 functions
  ///

  /** \details
    Returns true if and only if the first entity is drawn before the second with this SortentsTable.

    \param firstID [in]  First entity ID.
    \param secondID [in]  Second entity ID.
    
    \returns
    Returns eOk if successful, or an appropriate error code if not.
  */
  bool firstEntityIsDrawnBeforeSecond(
    OdTvDbObjectId firstID, 
    OdTvDbObjectId secondID) const;

  /** \details
    Returns an array of the entity IDs of the entities in the associated Block Table Record,
    in the DrawOrder for this SortentsTable.

    \param entityIds [out]  Entity IDs.
    \param honorSortentsMask [in]  SORTENTS mask. 

    \remarks
    If (honorSortentsMask ^ SORTENTS) != honorSortentsMask, the entities are returned unsorted.
    \returns
    Returns eOk if successful, or an appropriate error code if not.
    
    \remarks
    As implemented, honorSortentsMask is ignored.
    It will be fully implemented in a future release.
  */
  void getFullDrawOrder(
    OdTvDbObjectIdArray& entityIds, 
    OdUInt8 honorSortentsMask = 0) const;

  /** \details
    Rearranges the specified entity IDs into their current relative DrawOrder for this SortentsTable.
    
    \param entityIds [in/out] Entity IDs.
    \param honorSortentsMask [in] SORTENTS mask. 

    \remarks
    If (honorSortentsMask ^ SORTENTS) != honorSortentsMask, the entities are returned unsorted.
    \returns
    Returns eOk if successful, or an appropriate error code if not.

    \remarks
    As implemented, honorSortentsMask is ignored.
    It will be fully implemented in a future release.
  */
  void getRelativeDrawOrder(
    OdTvDbObjectIdArray& entityIds, 
    OdUInt8 honorSortentsMask = 0) const;


  /** \details
    Sets the relative DrawOrder for the specified entities in this SortentsTable.

    \param entityIds [in]  Entity IDs in DrawOrder.

    \remarks
    The DrawOrder of other entities are unaffected.
    
    Returns eOk if successful, or an appropriate error code if not.
  */
  void setRelativeDrawOrder(
    const OdTvDbObjectIdArray& entityIds);

  /** \details
    Sets this SortentsTable from an array of TvHandlePair pairs.
    
    \param handlePairs [in]  HandlePairs.
    
    \remarks
    Use of this function is not recommended.
  */
  void setAbsoluteDrawOrder(
    const TvHandlePairsArray& handlePairs);

  /** \details
    Returns this SortentsTable as an array of TvHandlePair pairs.
    
    \param handlePairs [out]  Receives an array of HandlePairs.
    
    \remarks
    Use of this function is not recommended.
  */
  void getAbsoluteDrawOrder(
    TvHandlePairsArray& handlePairs);

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  /*virtual OdResult subGetClassID(
    void* pClsid) const;*/
};


/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbSortentsTable object pointers.
*/
typedef OdSmartPtr<OdTvDbSortentsTable> OdTvDbSortentsTablePtr;

#include "TD_PackPop.h"

#endif //OD_DBSORTENTSTABLE_H

