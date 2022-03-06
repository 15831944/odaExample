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

// OdIfcDeviationParams.h: interface for the OdIfcDeviationParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODA_ODIFCDEVIATIONPARAMS_H_INCLUDED_)
#define ODA_ODIFCDEVIATIONPARAMS_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

  #include "IfcBuildOptions.h"

  /** \details 
  A class that implements working with IFC deviation parameters.
  */
  class IFCCORE_EXPORT OdIfcDeviationParams
  {
  public:
  
    /** \details 
    Creates a new set of deviation parameters with the specified values.
    \param deviation    [in] A deviation value.
    \param minPerCircle [in] A minimum number of segments to divide the circle into.
    \param maxPerCircle  [in] A maximum number of segments to divide the circle into.
    */
    OdIfcDeviationParams(double deviation = 0.5, OdUInt16 minPerCircle = 8, OdUInt16 maxPerCircle = 128);

    /** \details 
    Retrieves the current deviation value.
    \returns Returns a double value that represents the current deviation value. 
    */
    double getDeviation() const;
    
    /** \details 
    Sets a new deviation value for the parameters set.
    \param deviation [in] A new deviation value to be set.
    */
    void setDeviation(double deviation);

    /** \details 
    Retrieves the current minimum number of circle segments.
    \returns Returns an unsigned 16-bit integer value that represents the current minimum quantity of circle segments.
    */
    OdUInt16 getMinPerCircle() const;
    
    /** \details 
    Sets a new minimum number of circle segments.
    \param minPerCircle [in] A new minimum quantity of circle segments to be set.
    */
    void setMinPerCircle(OdUInt16 minPerCircle);

    /** \details 
    Retrieves the current maximum number of circle segments.
    \returns Returns an unsigned 16-bit integer value that represents the current maximum quantity of circle segments.
    */
    OdUInt16 getMaxPerCircle() const;
    
    /** \details 
    Sets a new maximum number of circle segments.
    \param maxPerCircle [in] A new maximum quantity of circle segments to be set.
    */
    void setMaxPerCircle(OdUInt16 maxPerCircle);

//DOM-IGNORE-BEGIN
  private:
    double m_deviation;
    OdUInt16 m_minPerCircle;
    OdUInt16 m_maxPerCircle;
//DOM-IGNORE-END
  };

#endif // !defined(ODA_ODIFCDEVIATIONPARAMS_H_INCLUDED_)
