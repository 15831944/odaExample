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

// IfcCurve.h: interface for the Od wrapper over IfcCurve and subtypes.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_CURVE_H_
#define _IFC_CURVE_H_

#include "Ge/GePolyline3d.h"
#include "Ge/GeCircArc3d.h"
#include "Ge/GeEllipArc3d.h"
#include "Ge/GeLineSeg3d.h"
#include "Ge/GeCompositeCurve3d.h"

#include "IfcGeometricRepresentationItem.h"

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details
  A base class that implements storing and handling data about a definition of an IfcCurve.
  */
  class IFCGEOM_EXPORT OdIfcCurve : public OdIfcGeometricRepresentationItem
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcCurve);
    //DOM-IGNORE-END

  public:

    /** \details
    Retrieves the identifier of an underlying Ge curve.
    \returns An <exref target="OdGe::EntityId"></exref> object that contains the underlaying Ge curve indentifier.
    */
    virtual OdGe::EntityId entityId() const { return m_pCurve->type(); }
    
    /** \details
    Returns a copy of the underlying Ge curve.
    \returns A raw pointer to the <exref target="OdGeCurve3d.html">OdGeCurve3d</exref> object that represents the copy of the underlaying Ge curve.
    */
    virtual OdGeCurve3d* getGeCurveCopy() const { return static_cast<OdGeCurve3d*>(m_pCurve->copy()); }

    /** \details
    Retrieves the underlaying Ge curve object in read-only mode.
    \returns A constant raw pointer to the underlying Ge curve represented with an <exref target="OdGeCurve3d.html">OdGeCurve3d</exref> object.
    */
    const OdGeCurve3d* getGeCurve() const { return m_pCurve.get(); }

    /** \details 
    Applies the specified transformation to the object.
    \param transform [in] A transformation matrix to be applied.
    \returns eOk value if the transformation operation was successful; otherwise, the method returns an appropriate error code.
    */
    OdResult transfromBy(const OdGeMatrix3d &transform) ODRX_OVERRIDE;

    /** \details 
    Defines whether the curve is a 3D object.
    \returns true if the curve is a 3D object; otherwise, the method returns false.
    */
    inline virtual bool is3d() const { return m_is3d; }

    /** \details 
    Sets a new value of the 3D flag for the curve.
    3D flag determines whether the curve is a 3D object (if it equals true) or not (in this case the flag value equals false).
    \param val [in] A new value of the flag to be set.
    */
    inline void setIs3d(bool val) { m_is3d = val; }

  //DOM-IGNORE-BEGIN
  protected:

    OdGeMatrix3d m_transform;

    OdGeCurve3dPtr m_pCurve;

    void getMatrix(OdIfcEntityPtr pPosition, OdGeMatrix3d& matr);

  private:
    bool m_is3d;
  //DOM-IGNORE-END
  };
  
  /** \details
  A data type that represents a smart pointer to an <link OdIfc::OdIfcCurve, OdIfcCurve> object.
  */
  typedef OdSmartPtr<OdIfcCurve> OdIfcCurvePtr;

} // namespace

#endif // _IFC_CURVE_H_
