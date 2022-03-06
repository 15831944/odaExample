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

#ifndef _PRCCONTENTWIREEDGE_INCLUDED_
#define _PRCCONTENTWIREEDGE_INCLUDED_ 
 

#include "PrcCurve.h"
#include "PrcInterval.h"
#include "PrcBaseTopology.h"

class OdPrcContentWireEdge;

SMARTPTR(OdPrcContentWireEdge);

/** \details 
<group PRC_Topology_Classes> 

Class representing data defining a wire edge. It contains information about a 3D curve, which defines the geometrical shape of the edge.
*/
class PRC_TOOLKIT OdPrcContentWireEdge
{
private:
  OdPrcBaseTopology   m_BaseTopology;
  OdPrcInterval      *m_curve_trim_interval;
  OdPrcCurvePtr       m_curve;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcContentWireEdge)
  //DOM-IGNORE-END

  /** \details
  Destroys the wire edge definition object.
  */
  ~OdPrcContentWireEdge();
  
  /** \details
  Returns current base topology data (such as attributes, name and so on).
  Base topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new base topology data.
  */
  OdPrcBaseTopology &baseTopology();

  /** \details
  Returns current base topology data (such as attributes, name and so on).
  */
  const OdPrcBaseTopology &baseTopology() const;

  /** \details
  Sets a new trimming interval for the wire edge.
  Trimming interval is used to limit the part of a curve used to define the edge.    

  \param pInterval [in] A pointer to an OdPrcInterval object. Null value will remove trimming.
  */
  void setTrimInterval(const OdPrcInterval *pInterval);

  /** \details
  Returns the current trimming interval of the wire edge.
  The trimming interval is used to limit the part of a curve used to define the edge. 
  */
  const OdPrcInterval *trimInterval() const;

  /** \details
  Returns the current curve (3D or 2D) which is used to define the geometry of the wire edge.
  The 3D curve is returned as a reference to an OdPrcCurvePtr object, therefore it can be used to set a new curve.
  */
  OdPrcCurvePtr &curve();

  /** \details
  Returns the current curve (3D or 2D) which is used to define the geometry of the wire edge.
  */
  const OdPrcCurvePtr &curve() const;
};

#endif // _PRCWIREEDGE_INCLUDED_

