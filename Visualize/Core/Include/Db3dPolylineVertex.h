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




#ifndef _OD_DB_3DPOLYLINE_VERTEX_
#define _OD_DB_3DPOLYLINE_VERTEX_

#include "TD_PackPush.h"

#include "DbVertex.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents OdTvDb3dPolyline vertices in an OdTvDbDatabase instance.
  
    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDb3dPolylineVertex : public OdTvDbVertex
{
public:

  DWGMAP_DECLARE_MEMBERS(OdTvDb3dPolylineVertex);

 /** \remarks
    Newly created vertices are of type OdDb::k3dSimpleVertex.
 */
  OdTvDb3dPolylineVertex();

  /** \details
    Returns the type of this Vertex entity.  
    
    \remarks
    vertexType() returns one of the following:

    <table>
    Name                     Value   DXF 70   Description
    OdDb::k3dSimpleVertex    0       0x40     Standard vertex.
    OdDb::k3dControlVertex   1       0x10     Spline-fit or curve-fit control point.
    OdDb::k3dFitVertex       2       0x08     Spline-fit or curve-fit generated vertex.
    </table>
  */
  OdDb::Vertex3dType vertexType() const;

  /** \details
    Sets the type of this Vertex entity.

    \param vertexType [in]  Vertex type.

    \remarks
    vertexType type must be one of the following:

    <table>
    Name                     Value   DXF 70   Description
    OdDb::k3dSimpleVertex    0       0x40     Standard vertex.
    OdDb::k3dControlVertex   1       0x10     Spline-fit or curve-fit control point.
    OdDb::k3dFitVertex       2       0x08     Spline-fit or curve-fit generated vertex.
    </table>
  */
  void setVertexType(
    OdDb::Vertex3dType vertexType);

  /** \details
    Returns the WCS position of this entity (DXF 10).
  */
  OdGePoint3d position() const;

  /** \details
    Sets the WCS position of this entity (DXF 10).
    \param position [in]  Position.
  */
  void setPosition(
    const OdGePoint3d& position);

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields_R12(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdTvDbDxfFiler* pFiler) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDb3dPolylineVertex object pointers.
*/
typedef OdSmartPtr<OdTvDb3dPolylineVertex> OdTvDb3dPolylineVertexPtr;

#include "TD_PackPop.h"

#endif

