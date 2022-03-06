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

#ifndef DbAssocArrayParameters_INCLUDED_
#define DbAssocArrayParameters_INCLUDED_ /*!DOM*/

#include "DbAssocArrayItem.h"
#include "DbEvalVariant.h"
#include "DbFiler.h"
#include "DbGeomRef.h"
#include "OdValue.h"
#include "StringArray.h"
#include "DbEntity.h"
#include "DbGrip.h"

#include "TD_PackPush.h"

/** \details
  This is the base abstract class which declares an interface for an array of associated parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdTvDbAssocArrayParameters : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocArrayParameters);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocArrayParameters();

  /** \details
    Sets the value, expression and evaluator of the parameter using its name.
  */
  OdResult setValueParam(const OdString& paramName,
                         const OdTvDbEvalVariant& value,
                         const OdString& expression,
                         const OdString& evaluatorId,
                         OdString& errorMessage,
                         OdValue::UnitType* pUnitType = NULL);

  /** \details
    Gets a value for the parameter using its name.
  */
  OdResult getValueParam(const OdString& paramName,
                         OdTvDbEvalVariant& value,
                         OdString& expression,
                         OdString& evaluatorId,
                         OdValue::UnitType& unitType) const;

  /** \details
    Sets the geometry parameter.
  */
  OdResult setGeomParam(const OdString& paramName,
                        const OdTvDbGeomRef* pGeomRef,
                        OdTvDbObjectId& paramId);

  /** \details
    Gets the geometry parameter.
  */
  OdResult getGeomParam(const OdString& paramName,
                        OdTvDbGeomRefPtr& pGeomRef,
                        OdTvDbObjectId& paramId) const;

  /** \details
    Gets an array of the owned parameter names.
  */
  void ownedValueParamNames(OdStringArray& paramNames) const;

  /** \details
    Gets an array of the owned geometry parameter names.
  */
  void ownedGeomParamNames(OdStringArray& paramNames) const;

  /** \details
    Sets the owner for this array of parameters.
  */
  virtual OdResult setOwner(class OdTvDbAssocArrayActionBody* pOwner);

  /** \details
    Gets the owner of this array.
  */
  OdSmartPtr<class OdTvDbAssocArrayActionBody> owner() const;

  /** \details
    Copies the content in this array from a given rx-object.
  */
  virtual void copyFrom(const OdRxObject* other);

  /** \details
    Gets an array of items. This method is pure and must be overridden in derived classes.
  */
  virtual OdResult getItems(OdArray<OdTvDbAssocArrayItemPtr>& items) const = 0;

  /** \details
    Gets the item locator, position, and transformation matrix. This method is pure and 
    must be overridden in derived classes.
  */
  virtual OdResult getItemPosition(const OdTvDbItemLocator& locator,
                                   OdGePoint3d& position, 
                                   OdGeMatrix3d& xform) const = 0;

  /** \details
    Gets the item locator. This method is pure and must be overridden in derived classes.
  */
  virtual OdTvDbItemLocator getCanonicalForm(const OdTvDbItemLocator& locator) const = 0;
  
  /** \details
    Gets a grip point for specified mode.
  */
  virtual OdResult getGripPointAt(unsigned int mode, OdDbGripDataPtrArray& pGrip) const;

  /** \details
    Gets an array of grip points.
  */
  virtual OdResult getGripPoints(OdArray<OdDbGripDataPtrArray>& grips) const;

  /** \details
    Moves an array of grip points.
  */
  virtual OdResult moveGripPointAt(const OdDbGripDataPtrArray pGrip,
                                            const OdGeVector3d &offset, 
                                            int& modificationBit);

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

protected:
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocArrayParameters(class OdTvDbImpAssocArrayParameters* pImpl = NULL);  // disabled Copy constructor

  /*!DOM*/
  friend class OdTvDbImpAssocArrayActionBody;
  friend class OdTvDbImpAssocArrayParameters;
  class OdTvDbImpAssocArrayParameters* m_pImpl;
};

/** \details
  The typified smart pointer for the array of parameters. This template class 
  is specialization of the OdSmartPtr class for the OdTvDbAssocArrayParameters class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocArrayParameters> OdTvDbAssocArrayParametersPtr;

#include "TD_PackPop.h"

#endif
