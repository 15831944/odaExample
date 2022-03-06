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

#ifndef _DBANNOTATIVEOBJECTPE_H_INCLUDED_
#define _DBANNOTATIVEOBJECTPE_H_INCLUDED_

#include "RxObject.h"

class OdTvDbViewport;

/** \details
    This class must be implemented for objects that use annotation scaling.
    
    \sa
    TD_Db
   
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbAnnotativeObjectPE : public OdRxObject
{
public:

  ODRX_DECLARE_MEMBERS(OdTvDbAnnotativeObjectPE);

  /** \details
    Returns whether a specified object supports annotation scaling.
  
	\param pObject [in]  Pointer to the object.
  */
    virtual bool annotative(const OdTvDbObject* pObject) const = 0;

  /** \details
    Sets whether an object supports annotation scaling.
  
	\param pObject [in]  Pointer to the object.
	\param bAnnotative [in]  The annotative property value.

	\returns
	Returns eOk if successful, or an appropriate error code if not.
  */
    virtual OdResult setAnnotative( 
    OdTvDbObject* pObject,
    bool bAnnotative ) = 0;

   /** \details
    Sets the annotative property of an object according to its corresponding
	style, such as styles of text objects.
  
	\param pObject [in]  Pointer to the object.
	\param bUpdated [out]  Returns True if the annotative property changes.

	\returns
	Returns eOk if successful, or an appropriate error code if not.
   */
    virtual OdResult setFromStyle(
    OdTvDbObject* pObject, 
    bool&       bUpdated) = 0;

   /** \details
    Not implemented. Returns whether the specified object is set to
	display regardless of the ANNOALLVISIBLE system variable setting.
   */
     virtual bool forceAnnoAllVisible(const OdTvDbObject* /*pObject*/) const { return false;} ;

   /** \details
    Not implemented. Sets whether the specified object displays regardless
	of the ANNOALLVISIBLE system variable setting.
   */
    virtual OdResult setForceAnnoAllVisible(OdTvDbObject* /*pObj*/, bool /*bForce*/) const {return eNotImplemented;}

   /** \details
    Not implemented.
   */
    virtual OdResult resetScaleDependentProperties(OdTvDbObject* /*pObject*/) {return eNotImplemented;}

   /** \details
    Not implemented.
   */
    virtual bool decompose(OdTvDbObject* /*pObj*/, OdDb::SaveType /*format*/, OdDb::DwgVersion /*version*/) { return false; }
};
typedef OdSmartPtr<OdTvDbAnnotativeObjectPE> OdTvDbAnnotativeObjectPEPtr;

   /** \details
    This class is a Protocol Extension class for objects, such as annotative objects,
	that support a paper orientation property.

    \sa
    TD_Db

    <group OdTvDb_Classes> 
   */
class TOOLKIT_EXPORT OdTvDbPaperOrientationPE : public OdRxObject
{
public:

  ODRX_DECLARE_MEMBERS(OdTvDbPaperOrientationPE);

   /** \details
    Returns whether the specified object is currently oriented with the paper.
  
	\param pObject [in]  Pointer to the object that supports the paper orientation property.
   */
    virtual bool paperOrientation(OdTvDbObject* pObject) const = 0;

   /** \details
    Sets the paper orientation property of a specified object.
  
	\param pObject [in]  Pointer to the object that supports the paper orientation property.
	\param bPaperOrientation [in]  Value of the paper orientation property.

	\returns
	Returns eOk if successful, or an appropriate error code if not.
   */
    virtual OdResult setPaperOrientation( 
    OdTvDbObject* pObject,
    const bool  bPaperOrientation ) = 0;

   /** \details
    Not implemented.
   */
    virtual OdResult applyPaperOrientationTransform ( 
    OdTvDbObject* /*pObject*/,
    const OdTvDbViewport* /*pVport*/ ) const
  { return eNotImplemented; }
};
typedef OdSmartPtr<OdTvDbPaperOrientationPE> OdTvDbPaperOrientationPEPtr;

#endif //_DBANNOTATIVEOBJECTPE_H_INCLUDED_
