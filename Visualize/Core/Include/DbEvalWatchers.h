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


#ifndef _ODDB_EVALWATCHERS_H_
#define _ODDB_EVALWATCHERS_H_

#include "RxObject.h"
#include "RxModule.h"
#include "DbEntity.h"
#include "DbHatch.h"

/** \details
    This class is the base Protocol Extension class for classes used for catching 
    evaluation requests from associated objects.

    \sa
    TD_Db

    \remarks
    This class can be used for OdTvDbHatch, OdTvDbDimAssoc, OdTvDbLeader and OdTvDbDimension classes.

    <group OdTvDb_Classes> 
*/
class TOOLKIT_EXPORT OdTvDbEvalWatcherPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbEvalWatcherPE);

  /** \details
    Notification function called whenever an object receives a modified notification 
    from an associated object.

    \param pObj [in]  Pointer to the object that received the notification.
    \param pAssocObj [in]  Pointer to the associated object.
    
    \remarks
    This function is called whenever the associated object is being closed after being modified.

    The default implementation of this function does nothing.
    This function can be overridden in custom classes.
  */
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pAssocObj) = 0;
  virtual void openedForModify(OdTvDbObject* pObj, const OdTvDbObject* pAssocObj);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbEvalWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbEvalWatcherPE> OdTvDbEvalWatcherPEPtr;


/** \details
    This class is the Protocol Extension class for updating OdTvDbHatch objects.

    \sa
    TD_Db

    \remarks
    This protocol extension is added to the OdTvDbHatch class by the Drawings while initializing.
    
    <group OdTvDb_Classes> 
*/
class DBENT_EXPORT OdTvDbHatchWatcherPE : public OdTvDbEvalWatcherPE
{
public:
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pAssocObj);

  /** \details
    Notification function called whenever an OdTvDbHatch object is modified.

    \param pHatch [in]  Pointer to the hatch object.
    
    \remarks
    This function is called whenever the hatch object is being closed after being modified.

    \remarks
    This protocol extension is added to the OdTvDbHatch class by the Drawings during initialization.

    The default implementation of this function does nothing.
    This function can be overridden in custom classes.
  */
  virtual void modifiedItself(OdTvDbHatch* pHatch);

  /** \details
    Updates the boundary of an OdTvDbHatch object.
    
      \param pHatch [in]  Pointer to the hatch object.
      \param assocObjIds [in]  Array of modified associated OdTvDbEntity object IDs.
  */
  virtual void evaluate(OdTvDbHatch* pHatch, const OdTvDbObjectIdArray& assocObjIds);

  /** \details
    Returns a loop from the specified OdTvDbEntity object IDs for the specified OdTvDbHatch entity.

    \param pHatch [in]  The OdTvDbHatch object.
    \param loopType [in/out] Type of loop being updated.
    \param objectIds [in] Array of OdTvDbEntity object IDs that comprise the loop.
    \param edges [in/out] Array of edges that comprise the loop.
  */
  virtual void getLoopFromIds(const OdTvDbHatch* pHatch, 
    OdUInt32& loopType, 
    OdTvDbObjectIdArray& objectIds, 
    EdgeArray& edges);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbHatchWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbHatchWatcherPE> OdTvDbHatchWatcherPEPtr;


/** \details
    This class is the Protocol Extension class for updating OdTvDbLeader objects.

    \sa
    TD_Db

    \remarks
    This protocol extension is added to the OdTvDbLeader class by the Drawings while initializing.
    
    <group OdTvDb_Classes> 
*/
class DBDIM_EXPORT OdTvDbLeaderWatcherPE : public OdTvDbEvalWatcherPE
{
public:
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pAssocObj);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbLeaderWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbLeaderWatcherPE> OdTvDbLeaderWatcherPEPtr;


/** \details
    This class is the Protocol Extension class for updating OdTvDbDimension objects when their
    associated OdTvDbDimStyleTableRecord objects are modified.

    \sa
    TD_Db

    \remarks
    This protocol extension is added to the OdTvDbDimension class by the Drawings while initializing.
    
    <group OdTvDb_Classes> 
*/
class DBDIM_EXPORT OdTvDbDimensionWatcherPE : public OdTvDbEvalWatcherPE
{
public:
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pDimStyle);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDimensionWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbDimensionWatcherPE> OdTvDbDimensionWatcherPEPtr;

/** \details
    This class is the Protocol Extension class for updating OdTvDbBreakData objects when their
    associated OdTvDbEntity objects are modified.

    \sa
    TD_Db

    \remarks
    This protocol extension is added to the OdTvDbBreakData class by the Drawings while initializing.

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbBreakDataWatcherPE : public OdTvDbEvalWatcherPE
{
public:
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pEnt);
  virtual void erased(OdTvDbObject* pObj, const OdTvDbObject* pEnt, bool bErasing);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDimensionWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbBreakDataWatcherPE> OdTvDbBreakDataWatcherPEPtr;

/** \details
    This class is the Protocol Extension class for updating OdTvDbFcf objects when their
    associated OdTvDbDimStyleTableRecord objects are modified.

    \sa
    TD_Db

    \remarks
    This protocol extension is added to the OdTvDbFcf class by the Drawings while initializing.
    
    <group OdTvDb_Classes> 
*/
class DBDIM_EXPORT OdTvDbFcfWatcherPE : public OdTvDbEvalWatcherPE
{
public:
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pDimStyle);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbFcfWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbFcfWatcherPE> OdTvDbDFcfWatcherPEPtr;

/** \details
    This class is the base Protocol Extension class for updating OdTvDbDimAssoc objects when their
    associated objects are copied or erased.

    \sa
    TD_Db

    \remarks
    This class can be used for OdTvDbDimAssoc class.
    
    <group OdTvDb_Classes> 
*/
class TOOLKIT_EXPORT OdTvDbDimAssocWatcherPE : public OdTvDbEvalWatcherPE
{
public:
    virtual void copied(OdTvDbObject *pObj, const OdTvDbObject *pAssocObj, const OdTvDbObject *pNewObj) = 0;
    virtual void erased(OdTvDbObject *pObj, const OdTvDbObject *pAssocObj, bool erasing = true) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDimAssocWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbDimAssocWatcherPE> OdTvDbDimAssocWatcherPEPtr;

/** \details
    This class is the Protocol Extension class for updating OdTvDbTable objects when their
    associated OdTvDbTableStyle objects are modified.

    \sa
    TD_Db

    \remarks
    This protocol extension is added to the OdTvDbDimension class by the Drawings while initializing.
    
    <group OdTvDb_Classes> 
*/
class DBENT_EXPORT OdTvDbTableWatcherPE : public OdTvDbEvalWatcherPE
{
public:
  virtual void modified(OdTvDbObject* pObj, const OdTvDbObject* pTableStyle);
};
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbTableWatcherPE object pointers.
*/
typedef OdSmartPtr<OdTvDbTableWatcherPE> OdTvDbTableWatcherPEPtr;


#endif // _ODDB_EVALWATCHERS_H_
