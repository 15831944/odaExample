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

#ifndef DbAssocSurfacesParameters_INCLUDED_
#define DbAssocSurfacesParameters_INCLUDED_ /*!DOM*/

#include "DbAssocArrayParameters.h"
#include "DbAssocArrayCommonParameters.h"
#include "DbImpAssocSurfacesParameters.h"

#include "TD_PackPush.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
This class represents an array of assoc loft parameters.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocLoftParameters : public OdTvDbAssocArrayParameters
{
public:
  /** Casts the specified pointer to an ClassName SmartPointer. **/
  static OdSmartPtr<OdTvDbAssocLoftParameters> cast(const OdRxObject* pObj)
  {
    if (pObj)
      return OdSmartPtr<OdTvDbAssocLoftParameters>(((OdTvDbAssocLoftParameters*)pObj->queryX(OdTvDbAssocLoftParameters::desc())), kOdRxObjAttach);

    return (OdTvDbAssocLoftParameters*)0;
  }

  static OdRxClass* g_pDesc;

  /** Returns the static ClassType description object associated with this object. **/
  /** This function is for use only when the class type of this object is known.          **/
  /** If the class type of this object is unknown, use instead isA().                           **/
  static OdRxClass* desc();
  /** Returns the ClassType description instance associated with this object.      **/
  /** This function is for use only when the class type of this object is unknown.        **/
  /** If the class type of this object is known, use instead desc().                            **/
  virtual OdRxClass* isA() const;
  /** Returns the Protocol Extension object for this object.        **/
  /** Return null if there is no Protocol Extension object is found.    **/
  virtual OdRxObject* queryX(const OdRxClass* protocolClass) const;
  /** Creates a new instance of this object type.                   **/
  /** Returns a SmartPointer to the new instance.                       **/
  static OdRxObjectPtr pseudoConstructor();
  /** Creates a new instance of this object type.                   **/
  /** Returns a SmartPointer to the new instance.                       **/
  static OdSmartPtr<OdTvDbAssocLoftParameters> createObject()
  {
    if (!desc())
      throw OdError(eNotInitializedYet);
    return desc()->create();
  }
  /** Registers ClassName with the Drawings SDK.                           **/
  static void rxInit();
  static void rxInit(AppNameChangeFuncPtr appNameChangeFunc);
  /* Unregisters ClassName with the Drawings SDK.                          **/
  static void rxUninit();

  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbAssocLoftParameters
    (
      int continuity = 1,
      double bulge = 0.5
      );

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocLoftParameters();

  virtual OdTvDbItemLocator getCanonicalForm(const OdTvDbItemLocator& locator) const;
  virtual OdResult getItems(OdArray<OdTvDbAssocArrayItemPtr>& items) const;
  virtual OdResult getItemPosition(const OdTvDbItemLocator &, OdGePoint3d &, OdGeMatrix3d &) const;

  virtual OdResult setOwner(class OdTvDbAssocActionBody* pOwner);
  void setInputVariables(const OdTvDbObjectIdArray& sourceEntites, short continuity, double bulge);

protected:
  OdTvDbAssocLoftParameters(class OdTvDbImpAssocLoftParameters* pImpl);
};

typedef OdSmartPtr<OdTvDbAssocLoftParameters> OdTvDbAssocLoftParametersPtr;

#include "TD_PackPop.h"

#endif

