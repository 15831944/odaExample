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

#ifndef _DbBlocksActions_h_Included_
#define _DbBlocksActions_h_Included_

#include "DbEvalGraph.h"
#include "Ge/GePoint2dArray.h"
#include "DbBlockElement.h"
#include "DbBlockParameter.h"

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockAction : public OdTvDbBlockElement
{
public:
  enum OdTvDbBlockActionXYType{ XY, X, Y }; // not sure if the enum is the same in scale and polar stretch actions
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockAction);
  virtual OdGePoint3d displayLocation() const;
  virtual void setDisplayLocation( const OdGePoint3d& );
  virtual OdTvDbEvalNodeId drivingParameterNodeId()const;
  OdTvDbObjectIdArray elementSelectionSet() const;

  virtual OdTvDbObjectIdArray selectionSet() const;
  virtual OdTvDbBlockParameterPtr getAssociatedParameter( OdDb::OpenMode mode = OdDb::kForRead ) const;
  //virtual void setSelectionSet( const OdTvDbObjectIdArray& );
};

typedef OdSmartPtr<OdTvDbBlockAction> OdTvDbBlockActionPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockMoveAction : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockMoveAction);
  OdTvDbBlockMoveAction();
  //double angleOffset();
  //double distanceMultiplier();
  //OdTvDbBlockActionXYType distanceType();
  //void setAngleOffset(double);
  //void setDistanceMultiplier(double);
  //void setDistanceType(OdTvDbBlockActionXYType);
};

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockStretchAction : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockStretchAction);
  OdTvDbBlockStretchAction();
  //double angleOffset()const;
  //double distanceMultiplier()const;
  //OdTvDbBlockActionXYType distanceType()const;
  //void setAngleOffset(double);
  //void setDistanceMultiplier(double);
  //void setDistanceType(OdTvDbBlockActionXYType);
  //void setStretchFrame(const OdGePoint2dArray&);
  //OdGePoint2dArray stretchFrame() const;
};

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockActionWithBasePt : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockActionWithBasePt);
  //OdGePoint3d basePoint() const;
  //OdGeVector3d basePointOffset() const;
  //bool dependent() const;
  //void setBasePoint(OdGePoint3d const &);
  //void setBasePointOffset(OdGeVector3d const &);
  //void setDependent(bool);
};

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockScaleAction : public OdTvDbBlockActionWithBasePt
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockScaleAction);
  OdTvDbBlockScaleAction();
  //OdTvDbBlockActionXYType scaleType();
  //void setScaleType( OdTvDbBlockActionXYType );
};

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockRotateAction : public OdTvDbBlockActionWithBasePt
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockRotateAction);
  OdTvDbBlockRotateAction();
};

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockFlipAction : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockFlipAction);
  OdTvDbBlockFlipAction();
};

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockArrayAction : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockArrayAction);
  OdTvDbBlockArrayAction();
  //double columnOffset() const;
  //double rowOffset() const;
  //void setColumnOffset(double);
  //void setRowOffset(double);
};

class OdTvDbDataTable;
typedef OdSmartPtr<OdTvDbDataTable>OdTvDbDataTablePtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockLookupAction : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockLookupAction);
  OdTvDbBlockLookupAction();
  //bool duplicateCellsInLookupColumn(int,int *);
  //bool duplicateCellsInLookupColumn( const OdTvResBufArray&, const OdArray<void*>&,int,int *);
  //bool duplicateRowsOverInputColumns(int *);
  //bool duplicateRowsOverInputColumns( const OdTvResBufArray &, const OdArray<void*>&,int *);
  //OdTvDbDataTablePtr getLookupTable( OdArray<void*> & );

  void getLookupTable( OdTvResBufArray&,OdArray<void*>&);
  //bool nonSingletonRangeInInputColumns(int *);
  //bool nonSingletonRangeInInputColumns( const OdTvResBufArray &,const OdArray<void*>&,int *);
  //bool nullsInInputColumns(int *);
  //bool nullsInInputColumns( const OdTvResBufArray&, const OdArray<void*>&,int *);

  OdUInt32 numberOfInputColumns() const;
  OdUInt32 numberOfOutputColumns()const;
  OdUInt32 numberOfColumns() const;
  OdUInt32 numberOfRows()const;
  //void setLookupTable( const OdTvResBufArray &, OdArray<void*> const &);
  //void setLookupTable( const OdTvDbDataTable *, OdArray<void*>&);
};
typedef OdSmartPtr<OdTvDbBlockLookupAction>OdTvDbBlockLookupActionPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockPolarStretchAction : public OdTvDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockPolarStretchAction);
  OdTvDbBlockPolarStretchAction();
  //double angleOffset() const;
  //double distanceMultiplier() const;
  //OdTvDbObjectIdArray rotateOnlyElementSelectionSet();
  //OdTvDbObjectIdArray rotateOnlySelectionSet();
  //void setAngleOffset(double);
  //void setDistanceMultiplier(double);
  //void setRotateOnlySelectionSet(const OdTvDbObjectIdArray&);
  //void setStretchFrame(const OdGePoint2dArray &);
  //OdGePoint2dArray stretchFrame();
};

#endif // _DbBlocksActions_h_Included_
