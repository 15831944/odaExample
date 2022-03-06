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




#ifndef _ODDBOBJECTITERATOR_INCLUDED_
#define _ODDBOBJECTITERATOR_INCLUDED_

#include "RxObject.h"
#include "DbObjectId.h"

class OdTvDbEntity;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbEntity object pointers.
*/
typedef OdSmartPtr<OdTvDbEntity> OdTvDbEntityPtr;

/** \details
    This class defines bidirectional Iterator objects that traverse entities contained in complex entities.
    
    
    OdTvDbBlock Table Records in an OdTvDbDatabase instance.

    \sa
    TD_Db
    
    \remarks
    Complex entities include the following:
    
    <table>
    Entity               Iterated entities
    OdTvDbBlockReference   All
    OdTvDb2dPolyline       Vertex
    OdTvDb3dPolyline       Vertex
    OdTvDbPolyFaceMesh     Vertex
    OdTvDbPolygonMesh      Vertex
    </table>

    This class cannot directly instantiated, but must be instantiated with the
    iterator creation methods of the class to be iterated through.

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectIterator : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectIterator);

  OdTvDbObjectIterator() {}

  /** \details
    Sets this Iterator object to reference the entity that it would normally return first.
     
    \remarks
    Allows multiple traversals of the iterator list.

    \param atBeginning [in]  True to start at the beginning, false to start at the end. 
    \param skipErased [in]  If and only if true, erased records are skipped.
  */
    virtual void start(
    bool atBeginning = true, 
    bool skipErased = true) = 0;

  /** \details
    Returns true if and only if the traversal by this Iterator object is complete.
  */
    virtual bool done() const = 0;

  /** \details
    Returns the Object ID of the entity currently referenced by this Iterator object.
  */
  virtual OdTvDbObjectId objectId() const = 0;

  /** \details
    Opens and returns the entity currently referenced by this Iterator object.

    \param openMode [in]  Mode in which to open the entity.
    \param openErasedEntity [in]  If and only if true, erased records will be opened or retrieved.

    \returns
    Returns a SmartPointer to the opened entity if successful, otherwise a null SmartPointer.
  */
  virtual OdTvDbEntityPtr entity(
    OdDb::OpenMode openMode = OdDb::kForRead, 
    bool openErasedEntity = false) = 0;

  /** \details
    Steps this Iterator object.

    \param forward [in]  True to step forward, false to step backward.
    \param skipErased [in]  If and only if true, erased records are skipped.
  */
  virtual void step(
    bool forward = true, 
    bool skipErased = true) = 0;

  /** \details
    Positions this Iterator object at the specified record.
    \param objectId [in]  Object ID of the entity.
  */
    virtual bool seek(
    OdTvDbObjectId objectId) = 0;
    
  /** \details
    Positions this Iterator object at the specified record.
    \param pEntity [in] Pointer to the entity.
  */
  virtual bool seek(
    const OdTvDbEntity* pEntity) = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbObjectIterator object pointers.
*/
typedef OdSmartPtr<OdTvDbObjectIterator> OdTvDbObjectIteratorPtr;

#endif //_ODDBOBJECTITERATOR_INCLUDED_

