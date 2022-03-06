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




#ifndef _ODDBUCSTABLERECORD_INCLUDED
#define _ODDBUCSTABLERECORD_INCLUDED

#include "TD_PackPush.h"

#include "DbSymbolTableRecord.h"
#include "ViewportDefs.h"
#include "DwgDeclareMembers.h"

/** \details
  <group OdTvDb_Classes>

  This class implements the UCS record object, which represents a UCS in the database. 
  The UCS is user coordinate system. This class inherits the base functionality of named 
  records. 

  \sa
  TD_Db
    
  \sa
  <link db_ucs_sample_table.html, Example of Working with the UCS Table Object>

  <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

  \sa
  <link db_ucs.html, Working with UCSs>

  OdTvDbUCSTable class
*/
class TOOLKIT_EXPORT OdTvDbUCSTableRecord: public OdTvDbSymbolTableRecord
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbUCSTableRecord);

  /** \details
    Builds an instance of the UCS record object.
    
    \remarks
    Use the static pseudo-constructor instead it.
    See: <link db_ucs_add_name.html, Adding and Naming UCSs>
  */
  OdTvDbUCSTableRecord();


  /** \details
    Returns three-dimensional point of the origin of the user coordinate system (UCS) 
    in the world coordinate system (WCS) for the UCS record object (DXF 10).

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::setOrigin() method
  */
  OdGePoint3d origin() const;


  /** \details
    Sets the origin of the user coordinate system (UCS) relative to the origin of the  
    world coordinate system (WCS) for the UCS record object (DXF 10).
    
    \param gePoint  [in] Three-dimensional point instance which stores the X,Y,Z coordinates of the origin.

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::origin() method
  */
  void setOrigin( const OdGePoint3d& gePoint );


  /** \details
    Returns three-dimensional vector of the X-axis of the user coordinate system (UCS) 
    in the world coordinate system (WCS) for the UCS record object (DXF 11).

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::setXAxis() method
  */
  OdGeVector3d xAxis() const;


  /** \details
    Sets the three-dimensional vector of the X-axis of the user coordinate system (UCS)
    relative to X-axis of the world coordinate system (WCS) for the UCS record object (DXF 11).
    
    \param geXVector [in] Three-dimensional vector instance which stores the X,Y,Z coordinates of the X-axis.

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::xAxis() method
  */
  void setXAxis( const OdGeVector3d& geXVector );


  /** \details
    Returns three-dimensional vector of the Y-axis of the user coordinate system (UCS) 
    in the world coordinate system (WCS) for the UCS record object (DXF 12).

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::setYAxis() method
  */
  OdGeVector3d yAxis() const;


  /** \details
    Sets the three-dimensional vector of the Y-axis of the user coordinate system (UCS)
    relative to Y-axis of the world coordinate system (WCS) for the UCS record object (DXF 12).
    
    \param geYVector [in] Three-dimensional vector instance which stores the X,Y,Z coordinates of the Y-axis.

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::yAxis() method
  */
  void setYAxis( const OdGeVector3d& geYVector );


  /** \details
    Returns the three-dimensional point of the origin of the user coordinate system (UCS)
    for the specified orthographic view in the world coordinate system (WCS) (DXF 13), when 
    the UCSBASE system variable is set to this UCS record object.
    
    \param nView [in]  Identifier of the orthographic view.

    \remarks
    The orthographic view identifier can take the following values: 1-Top, 2-Bottom, 3-Front, 
    4-Back, 5-Left, 6-Right.

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::setUcsBaseOrigin() method
  */
  OdGePoint3d ucsBaseOrigin(OdDb::OrthographicView nView) const;


  /** \details
    Sets the origin of the user coordinate system (UCS) (DXF 13) for the specified 
    orthographic view (DXF 71) in the world coordinate system (WCS), when the UCSBASE 
    system variable is set to this UCS record object.

    \param gePoint [in] Three-dimensional point instance which stores the X,Y,Z coordinates of  
                 the origin for the orthographic view.
    \param nView [in] Identifier of the orthographic view.

    \remarks
    The orthographic view identifier can take the following values: 1-Top, 2-Bottom, 3-Front, 
    4-Back, 5-Left, 6-Right.

    \sa
    <link db_ucs_sample_record.html, Example of Working with the UCS Record Object>

    \sa
    <link db_ucs_properties.html, Specific Properties of UCSs>

    OdTvDbUCSTableRecord::ucsBaseOrigin() method
  */
  void setUcsBaseOrigin( const OdGePoint3d& gePoint, OdDb::OrthographicView nView );


  //virtual OdResult subGetClassID( void* pClsid ) const;

  virtual OdResult dwgInFields( OdTvDbDwgFiler* pFiler );

  virtual void dwgOutFields( OdTvDbDwgFiler* pFiler ) const;

  virtual OdResult dxfInFields( OdTvDbDxfFiler* pFiler );

  virtual void dxfOutFields( OdTvDbDxfFiler* pFiler ) const;

  virtual OdResult dxfInFields_R12( OdTvDbDxfFiler* pFiler );

  virtual void dxfOutFields_R12( OdTvDbDxfFiler* pFiler ) const;
};

/** \details
  The typified smart pointer for the UCS record object. This template class is specialization 
  of the OdSmartPtr class for the OdTvDbUCSTableRecord object.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbUCSTableRecord> OdTvDbUCSTableRecordPtr;

#include "TD_PackPop.h"

#endif // _ODDBUCSTABLERECORD_INCLUDED
