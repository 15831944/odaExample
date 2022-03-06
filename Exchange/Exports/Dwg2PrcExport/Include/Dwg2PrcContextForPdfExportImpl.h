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

#ifndef _DWG2PRC_CONTEXT_FOR_PDF_EXPORT_IMPL_INCLUDED_
#define _DWG2PRC_CONTEXT_FOR_PDF_EXPORT_IMPL_INCLUDED_

#include "PrcContextForPdfExport.h"
#include "DbBlockReference.h"
#include "Db3dSolid.h"
#include "DbRegion.h"
#include "DbSurface.h"
#include "DbBody.h"

/** \details
A class that implements the functionality for working with the context of exporting a .dwg database to the PDF format with PRC support.
This class supports export in one viewport in the output PDF document (Single View Mode).
*/
class OD_TOOLKIT_EXPORT OdPrcContextForPdfExport_AllInSingleView : public OdPrcContextForPdfExport
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcContextForPdfExport_AllInSingleView);
  

private:
  mutable std::map<OdDbStub *, OdUInt32> m_mapViewport;
  mutable OdUInt32 m_nextAvailableVp;
//DOM-IGNORE-END

public:

  /** \details 
  Creates a new instance of the context with default parameters.
  */
  OdPrcContextForPdfExport_AllInSingleView()
    : m_nextAvailableVp(0)
  {}

  /** \details
  Determines whether the entity should be exported to a PDF document as a PRC object.
  \param pDrawable   [in] A raw pointer to an entity that is checked whether it can/should be exported as PRC object or not.
  \param pGiPath     [in] A raw pointer to a path node of the entity.
  \param pView       [in] A raw pointer to an object that contains information about the GS client view object.
  \param viewportidx [out] A placeholder for the index of the viewport (with the PRC content) in the PDF document where the entity should be exported to.
  \returns true if the entity should be exported to PDF document as a PRC object; otherwise, the method returns false.
  */
  virtual bool shouldExportAsPRC (const OdGiDrawable *pDrawable,
    const OdGiPathNode *pGiPath,
    const OdGsClientViewInfo *pView,
    OdUInt32 &viewportidx) const
  {
    // viewportidx - index of viewport (prc file in pdf) where current entity will be exported

    // can entity be exported to prc or not
    OdDbEntityPtr ptrEntity = OdDbEntity::cast(pDrawable);
    bool isEntity = !ptrEntity.isNull();
    
    if (pDrawable->isKindOf(OdDbBlockReference::desc()))
    {
      return false;
    }

    if (isEntity)
    {
      OdDbStub *pVpId = pView->viewportObjectId;
      std::map< OdDbStub *, OdUInt32> ::iterator it = m_mapViewport.find(pVpId);
      if (it != m_mapViewport.end())
      {
        viewportidx = m_mapViewport[pVpId];
      }
      else
      {
        viewportidx = m_nextAvailableVp;
        m_mapViewport.insert(std::pair<OdDbStub *, OdUInt32>(pVpId, m_nextAvailableVp));
        m_nextAvailableVp++;
      }
    }
    return isEntity;
  }
};
ODRX_CONS_DEFINE_MEMBERS(OdPrcContextForPdfExport_AllInSingleView, OdPrcContextForPdfExport, RXIMPL_CONSTR);


/** \details
A class that implements the functionality for working with the context of exporting a .dwg database to the PDF format with PRC support.
This class supports the export of solid entities into individual viewport in the output PDF document (one viewport per one entity).
The two-dimensional geometry is exported into PDF without PRC support.
*/
class OD_TOOLKIT_EXPORT OdPrcContextForPdfExport_OnlySolidsMultiView : public OdPrcContextForPdfExport
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcContextForPdfExport_OnlySolidsMultiView);

private:
  mutable OdUInt32 m_count_vports;
  //DOM-IGNORE-END

public:

  /** \details 
  Creates a new instance of the context with default parameters.
  */
  OdPrcContextForPdfExport_OnlySolidsMultiView()
    : m_count_vports(0)
  {}

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
    viewportidx = m_count_vports++;

    // can entity be exported to prc or not
    if ( pDrawable->isKindOf(OdDb3dSolid::desc())
      || pDrawable->isKindOf(OdDbRegion::desc())
      || pDrawable->isKindOf(OdDbSurface::desc())
      || pDrawable->isKindOf(OdDbBody::desc()))
    {
      return true;
    }

    return false;
  }
};
ODRX_CONS_DEFINE_MEMBERS(OdPrcContextForPdfExport_OnlySolidsMultiView, OdPrcContextForPdfExport, RXIMPL_CONSTR);


/** \details
A class that implements the functionality for working with the context of exporting a .dwg database to the PDF format with PRC support.
This class supports the export of all solids entities in one viewport in the output PDF document (Single View Mode). 
The two-dimensional geometry is exported into PDF without PRC support.
*/
class OD_TOOLKIT_EXPORT OdPrcContextForPdfExport_OnlySolidsSingleView : public OdPrcContextForPdfExport
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcContextForPdfExport_OnlySolidsSingleView);
  //DOM-IGNORE-END

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
    if ( pDrawable->isKindOf(OdDb3dSolid::desc())
      || pDrawable->isKindOf(OdDbRegion::desc())
      || pDrawable->isKindOf(OdDbSurface::desc())
      || pDrawable->isKindOf(OdDbBody::desc()))
    {
      return true;
    }

    return false;
  }
};
ODRX_CONS_DEFINE_MEMBERS(OdPrcContextForPdfExport_OnlySolidsSingleView, OdPrcContextForPdfExport, RXIMPL_CONSTR);


/** \details
A class that implements the functionality for working with the context of exporting a .dwg database to the PDF format with PRC support.
This class supports export into individual viewport in the output PDF document (one viewport per one entity).
*/
class OD_TOOLKIT_EXPORT OdPrcContextForPdfExport_Default : public OdPrcContextForPdfExport
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcContextForPdfExport_Default);

private:
  mutable OdUInt32 m_count_vports;
  //DOM-IGNORE-END

public:

  /** \details 
  Creates a new instance of the context with default parameters.
  */
  OdPrcContextForPdfExport_Default()
    : m_count_vports(0)
  {}

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
    viewportidx = m_count_vports++;

    // can entity be exported to prc or not
    OdDbEntityPtr ptrEntity = OdDbEntity::cast(pDrawable);
    bool isEntity = !ptrEntity.isNull();

    if (pDrawable->isKindOf(OdDbBlockReference::desc()))
    {
      return false;
    }

    return isEntity;
  }
};
ODRX_CONS_DEFINE_MEMBERS(OdPrcContextForPdfExport_Default, OdPrcContextForPdfExport, RXIMPL_CONSTR);

#endif //_DWG2PRC_CONTEXT_FOR_PDF_EXPORT_IMPL_INCLUDED_
