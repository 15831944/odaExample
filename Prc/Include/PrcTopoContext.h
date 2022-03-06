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

#ifndef _PRCTOPOCONTEXT_INCLUDED_
#define _PRCTOPOCONTEXT_INCLUDED_ 
 

#include "PrcBase.h"

SMARTPTR(OdPrcTopoContext);

/** \details 
<group PRC_Topology_Classes> 

Class representing a set of geometry and topology. It contains topological bodies that 
are represented as entry elements and points to geometry and topological items. 
  */
class PRC_TOOLKIT OdPrcTopoContext : public OdPrcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcTopoContext);
  //DOM-IGNORE-END
 
  /** \details
  Sets a new behavior value for a body.

  \param behaviour [in] A new behavior value to be set.
    */
  void setBehaviour(OdInt8 behaviour);
  
  /** \details
  Retrieves the current body's behavior value. 
  \returns An 8-bit unsigned integer value that represents the body's behavior.
  */
  OdInt8 behaviour() const;
  
  /** \details
  Sets a new minimum size of an edge.

  \param granularity [in] A new minimum size to be set.
  */
  void setGranularity(double granularity);
  
  /** \details
  Retrieves the current minimum size of an edge.
  \returns A double value that contains the current minimum size of an edge.
  */
  double granularity() const;
  
  /** \details
  Sets a new tolerance value used for topological elements.

  \param tolerance [in] A new tolerance value.
  */
  void setTolerance(double tolerance);
  
  /** \details
  Retrieves the current tolerance value.
  \returns A double value that contains the current tolerance.
  */
  double tolerance() const;
  
  /** \details
  Sets a new smallest face thickness value.

  \param smallest_thickness [in] A new value of the smallest face thickness to be set.
  */
  void setSmallestThickness(double smallest_thickness);
  
  /** \details
  Retrieves the current smallest face's thickness value.
  \returns A double value that contains the smallest face's thickness.
  */
  double smallestThickness() const;
  
  /** \details
  Sets a new scale used to interpret context data.

  \param scale [in] A new scale value to be set.
  */
  void setScale(double scale);
  
  /** \details
  Retrieves the current scale value used to interpret context data.
  \returns A double value that contains the current scale.
  */
  double scale() const;

  /** \details
  Sets the current scale value to 1.
  */
  void clearScale();

  /** \details
  Determines whether a scale is used.
  \returns true if the scale is used; otherwise, the method returns false.
  */
  bool haveScale() const;
  
  /** \details
  Sets the smallest face thickness value to (granularity * 100).
  */
  void clearSmallestFaceThickness();

  /** \details
  Determines whether the smallest face's thickness is used.
  \returns true if the smallest face's thickness is used; otherwise, the method returns false.
  */
  bool haveSmallestFaceThickness() const;

  /** \details
  Clears topological context data.
  */
  void clear();

  /** \details
  Sets content of the current topological body identifiers array to the user-specified.
  \param bodies [in] An array of <link OdPrcBody, OdPrcBody> object <link OdPrcObjectId, identifiers> to be applied.
   */
  void setBodies(const OdPrcObjectIdArray& bodies);

  /** \details
  Adds specified body to the end of the current topological body identifiers array.
  \param body [in] An array of <link OdPrcBody, OdPrcBody> object <link OdPrcObjectId, identifiers> to be added.
   */
  void appendBody(const OdPrcObjectId& body);

  /** \details
  Retrieves topological bodies.
  \returns The array with <link OdPrcObjectId, identifiers> of topological body objects.
  */
  const OdPrcObjectIdArray &bodies() const;
};

#endif // _PRCTOPOCONTEXT_INCLUDED_

