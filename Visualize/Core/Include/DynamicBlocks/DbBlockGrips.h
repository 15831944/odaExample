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

#ifndef _DbBlocksGrips_h_Included_
#define _DbBlocksGrips_h_Included_

#include "DbEvalGraph.h"
#include "DbBlockParameter.h"
#include "DbBlockElement.h"
#include "DbBlockFlipParameter.h"
#include "DbBlockLookUpParameter.h"

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockGripExpr : public OdTvDbEvalExpr
{
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockGripExpr);
  OdTvDbBlockGripExpr();
};
typedef OdSmartPtr<OdTvDbBlockGripExpr> OdTvDbBlockGripExprPtr;

class OdTvDbGripData;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockGrip : public OdTvDbBlockElement
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockGrip);
  OdTvDbBlockGrip();
  virtual void addedToGraph( OdTvDbEvalGraph* );
  virtual void removedFromGraph( OdTvDbEvalGraph* );
  OdGeVector3d definitionGripOffset() const;
  OdGePoint3d displayLocation() const;
  void setDisplayLocation(class OdGePoint3d const &);
  OdTvDbBlockParameterPtr getAssociatedParameter(OdDb::OpenMode mode = OdDb::kForRead) const;
  OdTvDbBlockParameter::ParameterComponent getAssociatedParameterComponent() const;
  OdGeVector3d gripOffset();
  bool insertionCycling() const;
  void setInsertionCycling(bool);
  OdInt32 insertionCyclingWeight() const;
  void setInsertionCyclingWeight(OdInt32);
  OdGePoint3d location() const;
  OdGePoint3d paramBasePoint() const;
  void setUpdatedLocation(class OdGePoint3d const &);
  OdGePoint3d updatedLocation();
};
typedef OdSmartPtr<OdTvDbBlockGrip> OdTvDbBlockGripPtr;

//class OdTvDbBlockPointParameter;
//typedef OdSmartPtr<OdTvDbBlockPointParameter>OdTvDbBlockPointParameterPtr;
//class OdTvDbBlockXYParameter
//typedef OdSmartPtr<OdTvDbBlockXYParameter>OdTvDbBlockXYParameterPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockXYGrip : public OdTvDbBlockGrip
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockXYGrip);
  OdTvDbBlockXYGrip();
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  //OdTvDbBlockPointParameterPtr getAssociatedPointParameter( OdDb::OpenMode )
  //OdTvDbBlockXYParameterPtr getAssociatedXYParameter( OdDb::OpenMode )
};
typedef OdSmartPtr<OdTvDbBlockXYGrip> OdTvDbBlockXYGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockPolarGrip : public OdTvDbBlockGrip
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockPolarGrip);
  OdTvDbBlockPolarGrip();
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  //OdTvDbBlockPolarParameterPtr getAssociatedPolarParameter( OdDb::OpenMode );
};
typedef OdSmartPtr<OdTvDbBlockPolarGrip> OdTvDbBlockPolarGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockRotationGrip : public OdTvDbBlockGrip
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockRotationGrip);
  OdTvDbBlockRotationGrip();
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  //AcTvDbBlockRotationParameterPtr AcTvDbBlockRotationGrip::getAssociatedRotationParameter( OdDb::OpenMode );
};
typedef OdSmartPtr<OdTvDbBlockRotationGrip> OdTvDbBlockRotationGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockLinearGrip : public OdTvDbBlockGrip
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockLinearGrip);
  OdTvDbBlockLinearGrip();
  //OdTvDbBlockLinearParameterPtr getAssociatedLinearParameter( OdDb::OpenMode );
  OdGeVector3d orientation() const;
  void setOrientation( const OdGeVector3d& );
};
typedef OdSmartPtr<OdTvDbBlockLinearGrip> OdTvDbBlockLinearGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockFlipGrip : public OdTvDbBlockGrip
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockFlipGrip);
  OdTvDbBlockFlipGrip();
  //void cycleFlipState();
  OdTvDbBlockFlipParameter::FlipState flipState() const;
  void setFlipState( OdTvDbBlockFlipParameter::FlipState );
  void setUpdatedFlipState( OdTvDbBlockFlipParameter::FlipState );
  OdTvDbBlockFlipParameter::FlipState updatedFlipState();
  //OdTvDbBlockFlipParameterPtr getAssociatedFlipParameter( OdDb::OpenMode );
  OdGeVector3d orientation();
  void setOrientation( const OdGeVector3d& );
  virtual void graphEvalEnd(bool);
};
typedef OdSmartPtr<OdTvDbBlockFlipGrip> OdTvDbBlockFlipGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockLookupGrip : public OdTvDbBlockGrip
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockLookupGrip);
  OdTvDbBlockLookupGrip();
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  //OdTvDbBlockLookUpParameterPtr getAssociatedLookupParameter( OdDb::OpenMode );
  //void getValueList( OdTvResBufArray& );
  //bool showGrip() const;
};
typedef OdSmartPtr<OdTvDbBlockLookupGrip> OdTvDbBlockLookupGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockAlignmentGrip : public OdTvDbBlockGrip
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockAlignmentGrip);
  OdTvDbBlockAlignmentGrip();
  //OdTvDbBlockAlignmentParameterPtr getAssociatedAlignmentParameter( OdDb::OpenMode );
  OdGeVector3d orientation();
  void setOrientation(const OdGeVector3d&);
};
typedef OdSmartPtr<OdTvDbBlockAlignmentGrip> OdTvDbBlockAlignmentGripPtr;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockVisibilityGrip : public OdTvDbBlockGrip
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockVisibilityGrip);
  OdTvDbBlockVisibilityGrip();
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  virtual void setMemberOfCurrentVisibilitySet(bool) ODRX_OVERRIDE;
  //void getValueList( OdTvResBufArray& );
  //bool showGrip() const;
};

typedef OdSmartPtr<OdTvDbBlockVisibilityGrip> OdTvDbBlockVisibilityGripPtr;

#endif // _DbBlocksGrips_h_Included_
