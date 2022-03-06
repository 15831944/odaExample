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

#ifndef _NW_PLOTCORESHAPETEXT_H_
#define _NW_PLOTCORESHAPETEXT_H_
#include "NwObject.h"
#include "NwGeometry.h"
/** \details
  This class represents geometry.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPlotCoreShapeText : public OdNwGeometry
{
  ODRX_DECLARE_MEMBERS(OdNwPlotCoreShapeText);

  /** \details
    Default constructor. Creates a new OdNwPlotCoreShapeText object.
  */
  OdNwPlotCoreShapeText();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPlotCoreShapeText();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwPlotCoreShapeText object pointers.
*/
typedef OdSmartPtr<OdNwPlotCoreShapeText> OdNwPlotCoreShapeTextPtr;

#endif // _NW_PLOTCORESHAPETEXT_H_
