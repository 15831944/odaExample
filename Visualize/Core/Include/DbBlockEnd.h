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




#ifndef _OD_DB_BLOCK_END_
#define _OD_DB_BLOCK_END_

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents BlockEnd entities in an OdTvDbDatabase instance.  
    
    \remarks
    OdTvDbBlockEnd entities are created and handled automatically for
    each OdTvDbBlockTableRecord object.
     
    Client applications may add extended data or extension dictionaries to these 
    entities, but should not create or delete them.
    
    These entities have no associated geometries.

    \remarks
    Do not derive from this class.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbBlockEnd : public OdTvDbEntity
{
public:
  
  DWGMAP_DECLARE_MEMBERS(OdTvDbBlockEnd);

  OdTvDbBlockEnd();

  /** \details
    Reads the DXF data of this object. 
    
    \param pFiler [in] Pointer to the filer from which data are read.  
    
    \returns
    Returns the filer status. 

    This function is called by dxfIn() to allow the object to read its data. 

    When overriding this function: 
    1) Call assertWriteEnabled(). 2) Call the parent class's dwgInFields(pFiler). 
    3) If it returns eOK, continue; otherwise return whatever the parent's dxfInFields(pFiler) returned. 
    4) Call the OdTvDbDxfFiler(pFiler) methods to read each of the object's data items in the order they were written. 
    5) Return pFiler->filerStatus().
  */
  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the DXF data of this object. 
    
    \param pFiler [in] Pointer to the filer to which data are to be written.   
    
    \remarks
    This function is called by dxfOut() to allow the object to write its data. 

    When overriding this function: 
    1) Call assertReadEnabled(). 2) Call the parent class's dxfOutFields(pFiler).
    3) Use pFiler to call the OdTvDbDxfFiler methods to write each of the object's data items in the order they were written.
  */
  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  /** \details
    Reads the DXF R12 format data of this object.  
    
    \param pFiler [in] Pointer to the filer from which data are to be read.    
    
    \returns
    Returns the filer status. 

    This function is called by dxfIn() to allow the object to read its data. 

    When overriding this function: 
    1) Call assertWriteEnabled(). 2) Call the parent class's dxfInFields_R12(pFiler). 
    3) If it returns eOK, continue; otherwise return whatever the parent's dxfOutFields_R12(pFiler) returned. 
    4) Call the OdTvDbDxfFiler(pFiler) methods to read each of the object's data items in the order they were written. 
    5) Return pFiler->filerStatus().
 */
  virtual OdResult dxfInFields_R12(
    OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the DXF data of this object.   
    
    \param pFiler [in] Pointer to the filer to which data are to be written.     
    
    \returns
    Returns the filer status. 

    This function is called by dxfOut() to allow the object to write its data. 

    When overriding this function: 
    1) Call assertReadEnabled(). 2) Call the parent class's dxfOutFields(pFiler). 
    3) Use pFiler to call the OdTvDbDxfFiler methods to write each of the object's data items in the order they were written.
  */
  virtual void dxfOutFields_R12(
    OdTvDbDxfFiler* pFiler) const;

  /** \remarks
    Always returns eInvalidExtents.
  */
  virtual OdResult subGetGeomExtents(
    OdGeExtents3d& extents) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbBlockEnd object pointers.
*/
typedef OdSmartPtr<OdTvDbBlockEnd> OdTvDbBlockEndPtr;

#include "TD_PackPop.h"

#endif
