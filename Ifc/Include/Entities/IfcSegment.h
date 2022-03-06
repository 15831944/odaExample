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

// OdIfcSegment.h: interface for the OdIfcSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODA_ODIFCSEGMENT_H_INCLUDED_)
#define ODA_ODIFCSEGMENT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcGeometricRepresentationItem.h"

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc
{
  /** \details
  A base class that implements storing and handling geometrical data about a definition of an IfcSegment.
  */
  class IFCGEOM_EXPORT OdIfcSegment : public OdIfcGeometricRepresentationItem
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcSegment);
    //DOM-IGNORE-END

  public:
  
    /** \details
    Composes geometry for the curve segment object.
    */
    void compose() ODRX_OVERRIDE;
    
    /** \details
    Returns a copy of the underlying Ge curve.
    \returns A raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGeCurve3d.html">OdGeCurve3d</exref> object that represents the copy of the underlaying Ge curve.
    */
    virtual OdGeCurve3d* getGeCurveCopy();
    
    /** \details
    Retrieves the underlying Ge curve object in read-only mode.
    \returns A constant raw pointer to the underlying Ge curve represented with an <exref target="https://docs.opendesign.com/tkernel/OdGeCurve3d.html">OdGeCurve3d</exref> object .
    */    
    virtual const OdGeCurve3d* getGeCurve() = 0;
    
    /** \details 
    Retrieves the current value of the 3D segment flag.
    3D segment flag determines whether the segment object is a 3D segment (if the flag value equals true) or not (in this case the flag value equals false).
    \returns true if the segment object is a 3D segment; otherwise, the method returns false.
    */
    bool is3dSeg() const;
    
    /** \details
    Returns the current value of the same sence flag.
    \returns true if the same sense flag is on; otherwise the method returns false.
    */
    virtual bool isSameSense() const = 0;
    
    /** \details 
    Draws the segment to the <exref target="https://docs.opendesign.com/tv/OdGiWorldDraw.html">OdGiWorldDraw interface</exref>.
    \param pWd [in] A raw pointer to the object for the entity-level vectorization.
    \returns true if the segment was successfully drawn; otherwise, the method returns false.
    */
    bool draw(OdGiWorldDraw* pWd) const = 0;
  };
  
  /** \details
  A data type that represents a smart pointer to an <link OdIfc::OdIfcSegment, OdIfcSegment> object.
  */
  typedef OdSmartPtr<OdIfcSegment> OdIfcSegmentPtr;
}


#endif // !defined(ODA_ODIFCSEGMENT_H_INCLUDED_)

