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

// OdIfcCurveSegment.h: interface for the OdIfcCurveSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODA_ODIFCCURVESEGMENT_H_INCLUDED_)
#define ODA_ODIFCCURVESEGMENT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcSegment.h"

#define TEST

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc
{
  /** \details
  A base class that implements storing and handling data about a definition of an IfcCurveSegment.
  */
  class IFCGEOM_EXPORT OdIfcCurveSegment : public OdIfcSegment
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcCurveSegment);
    //DOM-IGNORE-END

  public:
    /** \details
    Composes the curve segment object.
    */
    void compose() ODRX_OVERRIDE;
    
    /** \details
    Returns a copy of the underlying Ge curve.
    \returns A raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGeCurve3d.html">OdGeCurve3d</exref> object that represents the copy of the underlying Ge curve.
    */
    virtual OdGeCurve3d* getGeCurveCopy() ODRX_OVERRIDE;
    
    /** \details
    Retrieves the underlying Ge curve object in read-only mode.
    \returns A constant raw pointer to the underlying Ge curve represented with an <exref target="https://docs.opendesign.com/tkernel/OdGeCurve3d.html">OdGeCurve3d</exref> object.
    */
    virtual const OdGeCurve3d* getGeCurve() ODRX_OVERRIDE;
    
    /** \details 
    Returns the current value of the same sence flag.
    \returns true if the same sense flag is on; otherwise the method returns false.
    */
    bool isSameSense() const ODRX_OVERRIDE;
    
    /** \details 
    Draws the curve segment to the <exref target="https://docs.opendesign.com/tv/OdGiWorldDraw.html">OdGiWorldDraw interface</exref>.
    \param pWd [in] A raw pointer to the object for the entity-level vectorization.
    \returns true if the curve segment was successfully drawn; otherwise, the method returns false.
    */
    bool draw(OdGiWorldDraw* pWd) const ODRX_OVERRIDE;
    
    /** \details 
    Calculates the height of the curve segment.
    \param len    [in] A length of the curve segment.
    \param height [out] A placeholder for a double value that contains the calculated height.
    \returns true of the height was successfully calculated; otherwise, the method returns false.
    \remarks 
    The method calculates the height value, stores it in the passed placeholder parameter, and returns it to a calling subroutine.
    */
    bool calculateHeights(double len, double& height) const;
    
    /** \details 
    Retrieves the start length of the curve segment.
    \param len [out] A placeholder for a double value that contains the start length. 
    \returns true if the start length was successfully calculated and returned to a calling subroutine; otherwise, the method returns false.
    \remarks 
    The method calculates the start length, stores it in the passed parameter, and returns it to a calling subroutine.
    The start length is calculated accordingly to the segment placement location.
    */
    bool getStartLength(double& len) const;

  //DOM-IGNORE-BEGIN
  private:
    void convertParam(const OdAnsiString& type, const double curveStartParam, double& param) const;
#ifdef TEST
    void trimBaseCurve();
#endif

    /** \details
    Moves base curve start point into origin point of local CS and rotates it due to the direction 
    in start point becomes equal to xAxis direction.
    */
    void translateBaseCurve();

    OdGeCurve3dPtr m_pCurve;
    bool           m_bSameSense;
    OdGeMatrix3d   m_matrix;
    double         m_startParam;
    double         m_endParam;
  //DOM-IGNORE-END
  };
  
  /** \details
  A data type that represents a smart pointer to an <link OdIfc::OdIfcCurveSegment, OdIfcCurveSegment> object.
  */
  typedef OdSmartPtr<OdIfcCurveSegment> OdIfcCurveSegmentPtr;
}


#endif // !defined(ODA_ODIFCCURVESEGMENT_H_INCLUDED_)

