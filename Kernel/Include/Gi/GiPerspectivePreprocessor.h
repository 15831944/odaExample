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


#ifndef __OD_GI_PERSPECT_PREP__
#define __OD_GI_PERSPECT_PREP__

#include "Gi/GiConveyorNode.h"
#include "Gi/GiDeviation.h"

#include "Ge/GeDoubleArray.h"

#include "TD_PackPush.h"

/** \details

    <group OdGi_Classes>
    This class preprocesses geometry before xforming it by 
    perspective matrix.
    \remarks
    Circles, arcs, ellipses, texts are tesselated, although for export tasks 
    it may be more useful to switch arcs to nurbs curves.
    
    Polylines, polygons, meshes, shells, xlines, rays, and NURBS curves are passed through.
    
    Images and metafiles are not passed.
*/
class ODGI_EXPORT OdGiPerspectivePreprocessor : public OdGiConveyorNode
{
public:
  ODRX_DECLARE_MEMBERS(OdGiPerspectivePreprocessor);

  /** \details
  Sets max deviation for curve tessellation.
  
  \param deviations [in]  Array with deviation values.
  */
  virtual void setDeviation(const OdGeDoubleArray& deviations) = 0;

  /** \details
  Sets deviation object to obtain max deviation for curve tessellation.
  
  \param pDeviation [in]  Pointer to the deviation object.
  */
  virtual void setDeviation(const OdGiDeviation* pDeviation) = 0;

  /** \details
    Sets the draw context object (to access to traits, etc).
    \param pDrawCtx [in]  Pointer to the draw context.
  */
  virtual void setDrawContext(OdGiConveyorContext* pDrawCtx) = 0;

  /** \details
  Enables or disables perspective processor.
  \param enabled [in]  Flag that specifies whether to enable perspective processor.
  */
  virtual void enable(bool enabled) = 0;

  /** \details
  Checks whether perspective processor is enabled.
  \returns
  true if perspective processor is enabled, false otherwise.
  */
  virtual bool enabled() const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiPerspectivePreprocessor, OdGiPerspectivePreprocessor> object.
*/
typedef OdSmartPtr<OdGiPerspectivePreprocessor> OdGiPerspectivePreprocessorPtr;

#include "TD_PackPop.h"


#endif // __OD_GI_PERSPECT_PREP__
