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

#ifndef _DbLayoutPaperPE_h_Included_
#define _DbLayoutPaperPE_h_Included_

#include "SmartPtr.h"

class OdTvDbLayout;
class OdGePoint3d;

/** \details
    This class is the Protocol Extension class for OdTvDbLayout objects.
    
    \remarks
    The Protocol Extension class can be registered on the OdTvDbLayout class 
    to provide a vectorization client the opportunity to customize the drawing
    of the background paper during PaperSpace vectorization.
    
    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class TOOLKIT_EXPORT OdTvDbLayoutPaperPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbLayoutPaperPE);

  /** \details
      This function is called during vectorization to draw the paper.  

      \param pThis [in]  The layout that is being vectorized.
      \param pWd [in/out] Draw object that can be used by this function to set the 
        necessary attributes and create the necessary geometry.
      \param points [in] Contains the 4 corners of the paper.

      \returns
      true if the paper was successfully drawn, otherwise false, in which case
      the layout will do a default rendering of the paper.
  */
  virtual bool drawPaper(const OdTvDbLayout* pThis, OdGiWorldDraw* pWd, OdGePoint3d* points) = 0;

  /** \details
      This function is called during vectorization to draw the paper border.

      \param pThis [in]  The layout that is being vectorized.
      \param pWd [in/out] Draw object that can be used by this function to set the 
        necessary attributes and create the necessary geometry.
      \param points [in] Contains the 4 corners of the paper.

      \returns
      true if the border was successfully drawn, otherwise false, in which case
      the layout will do a default rendering of the border.
  */
  virtual bool drawBorder(const OdTvDbLayout* pThis, OdGiWorldDraw* pWd, OdGePoint3d* points) = 0;

  /** \details
      This function is called during vectorization to draw the paper margins.

      \param pThis [in]  The layout that is being vectorized.
      \param pWd [in/out] Draw object that can be used by this function to set the 
        necessary attributes and create the necessary geometry.
      \param points [in] Contains the 4 margin points.

      \returns
      true if the margins were successfully drawn, otherwise false, in which case
      the layout will do a default rendering of the margins.
  */
  virtual bool drawMargins(const OdTvDbLayout* pThis, OdGiWorldDraw* pWd, OdGePoint3d* points) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbLayoutPaperPE object pointers.
*/
typedef OdSmartPtr<OdTvDbLayoutPaperPE> OdTvDbLayoutPaperPEPtr;

#endif //_DbLayoutPaperPE_h_Included_
