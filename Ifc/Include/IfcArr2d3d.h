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

#ifndef _IFC_ARR2D3D_H_
#define _IFC_ARR2D3D_H_

#include "IfcBuildOptions.h"

#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeVector2d.h"
#include "Ge/GeVector3d.h"

/** \details 
Contains declarations related to working with IFC files content.
*/
namespace OdIfc {

  /** \details 
  A class that stores an array of two- and three-dimensional geometric coordinates.
  */
  class IFCCORE_EXPORT OdIfcArr2d3d
  {
  public:

    double m_Coordinates[3]; // An array of coordinates.

  public:

    /** \details 
    Creates a new array of coordinates with default values.
    */
    OdIfcArr2d3d();

    /** \details 
    An operator that returns a raw pointer to the coordinates array.
    */
    operator double*() { return m_Coordinates; };

    /** \details
    An operator that returns a raw pointer to the const coordinates array.
    */
    operator const double*() const { return m_Coordinates; };

    /** \details 
    Clears coordinates. 
    After clearing, coordinate values become equal to an <link OdDAI::Consts::OdNan, OdNan> constant.
    */
    void clear();

    /** \details 
    Retrieves the current size of the coordinate array.
    \returns Returns the current size of the array (2 for 2D objects, 3 for 3D objects).
    */
    int size() const;
    
    /** \details 
    Retrieves whether the coordinate array is empty or not.
    \returns Returns true if the coordinate array is empty; otherwise, the method returns false.
    */
    bool empty() const;

    /** \details
    Creates a new two-dimensional point object from the coordinate array. 
    \returns Returns a raw pointer to the created <exref target="https://docs.opendesign.com/tkernel/OdGePoint2d.html">OdGePoint2d</exref> object.
    */
    OdGePoint2d* createPoint2d();
    
    /** \details
    Creates a new three-dimensional point object from the coordinate array. 
    \returns Returns a raw pointer to the created <exref target="https://docs.opendesign.com/tkernel/OdGePoint3d.html">OdGePoint3d</exref> object.
    */
    OdGePoint3d* createPoint3d();
    
    /** \details
    Creates a new two-dimensional vector object from the coordinate array. 
    \returns Returns a raw pointer to the created <exref target="https://docs.opendesign.com/tkernel/OdGeVector2d.html">OdGeVector2d</exref> object.
    */    
    OdGeVector2d* createVector2d();
    
    /** \details
    Creates a new three-dimensional vector object from the coordinate array. 
    \returns Returns a raw pointer to the created <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> object.
    */    
    OdGeVector3d* createVector3d();

    /** \details
    Initializes the coordinate array from an <exref target="https://docs.opendesign.com/tkernel/OdArray.html">OdArray</exref> object that is contained in an OdRxValue.
    \param val [in] An OdRxValue object that contains the array of doubles inside.
    \returns Returns true if the operation succeeds; otherwise returns false.
    */
    bool initFromOdArray(const OdRxValue & val);
  };

}

#endif // _IFC_ARR2D3D_H_

