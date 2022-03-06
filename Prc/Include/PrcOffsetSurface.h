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

#ifndef _PRCSRFOFFSET_INCLUDED_
#define _PRCSRFOFFSET_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcTransformation3d.h"
#include "PrcSurface.h"


/** \details 
<group PRC_Surface_Classes> 

Class stores information about a surface that is defined by a surface that is offset along its normal by a given distance.
*/
class PRC_TOOLKIT OdPrcOffsetSurface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcOffsetSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the offset surface.
  */
  ~OdPrcOffsetSurface();
  
  /** \details
  Sets a new offset distance value.

  \param offset_distance [in] A new offset distance value to be set.
  */
  void setOffsetDistance(double offset_distance);
  
  /** \details
  Returns the current offset distance value.
  */
  double offsetDistance() const;

  /** \details
  Sets new base surface data of the offset surface.

  \param value [in] New base surface data to be set.

  \returns Return eOk if new base surface data was successfully set or an appropriate error code in the other case.
  */
  OdResult setBaseSurface(const OdPrcSurfacePtr &value);
  
  /** \details
  Returns current base surface data of the offset surface.
  */
  const OdPrcSurfacePtr &baseSurface() const;
};

SMARTPTR(OdPrcOffsetSurface);

#endif // _PRCSRFOFFSET_INCLUDED_

