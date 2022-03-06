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

#ifndef _DGN2PRC_CONTEXT_FOR_PDF_EXPORT_IMPL_INCLUDED_
#define _DGN2PRC_CONTEXT_FOR_PDF_EXPORT_IMPL_INCLUDED_

#include "PrcContextForPdfExport.h"
#include "DgGraphicsElement.h"

/** \details 
A class that implements the functionality for working with the context of exporting a .dgn database to the PDF format with PRC support.
This class supports export in one viewport in the output PDF document (Single View Mode).
<group PRC_Export_Import_Classes>
*/
class OD_TOOLKIT_EXPORT OdPrcContextForPdfExport_AllInSingleView_DGN : public OdPrcContextForPdfExport
{
  ODRX_DECLARE_MEMBERS(OdPrcContextForPdfExport_AllInSingleView_DGN);

public:

  /** \details
  Determines whether the entity should be exported to a PDF document as a PRC object.
  \param pDrawable   [in] A raw pointer to an entity that is checked whether it can/should be exported as PRC object or not.
  \param pGiPath     [in] A raw pointer to a path node of the entity.
  \param pView       [in] A raw pointer to an object that contains information about the GS client view object.
  \param viewportidx [out] A placeholder for the index of the viewport (with the PRC content) in the PDF document where the entity should be exported to.
  \returns true if the entity should be exported to PDF document as a PRC object; otherwise, the method returns false.
  \remarks 
  The default implementation returns false.
  */
  virtual bool shouldExportAsPRC (const OdGiDrawable *pDrawable,
    const OdGiPathNode *pGiPath,
    const OdGsClientViewInfo *pView,
    OdUInt32 &viewportidx) const
  {
    // index of viewport (prc file in pdf) where current entity will be exported
    viewportidx = 0;

    // can entity be exported to prc or not
    OdDgGraphicsElementPtr ptrEntity = OdDgGraphicsElement::cast(pDrawable);
    bool isEntity = !ptrEntity.isNull();

//     if (pDrawable->desc() == OdDgBlock::desc())
//     {
//       return false;
//     }

    return isEntity;
  }
};
ODRX_CONS_DEFINE_MEMBERS(OdPrcContextForPdfExport_AllInSingleView_DGN, OdPrcContextForPdfExport, RXIMPL_CONSTR);

#endif //_DGN2PRC_CONTEXT_FOR_PDF_EXPORT_IMPL_INCLUDED_
