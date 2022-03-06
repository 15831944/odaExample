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

#ifndef _NW_PLOTBRUSH_H_
#define _NW_PLOTBRUSH_H_
#include "NwObject.h"

/** \details
  This class represents plot brush.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPlotBrush : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwPlotBrush);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwPlotBrush object.
  */
  OdNwPlotBrush();
  
  /** \details
    Constructor for objects of the OdNwPlotBrush class. Creates a new
    OdNwPlotBrush object for the specified item.

    \param pImpl [in] Item to create a OdNwPlotBrush object for.
  */
  explicit OdNwPlotBrush(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPlotBrush();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwPlotBrush object pointers.
*/
typedef OdSmartPtr<OdNwPlotBrush> OdNwPlotBrushPtr;

#endif // _NW_PLOTBRUSH_H_
