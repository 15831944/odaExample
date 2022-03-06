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

#ifndef _OD_DB_DGNLS_PE_
#define _OD_DB_DGNLS_PE_

#include "DbLinetypeTableRecord.h"

struct OdGiDgLinetypeModifiers;
class OdGiSubEntityTraits;

/** \details
    This class defines the interface for the Linetype Table Record Protocol Extension classes.
    
    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDgnLSPE : public OdRxObject
{
  public:
    ODRX_DECLARE_MEMBERS(OdTvDbDgnLSPE);

    enum DgnLSSetupFlags
    {
      kDgnLSProcessed = 1
    };

    /** \details
      Checks does Linetype Table Record contain attached DgnLS data.

      \param pLTR [in]  Pointer to the Linetype Table Record.
      \returns
      Returns true if Linetype Table Record have attached DgnLS data.
    */
    virtual bool hasDgnLSData(const OdTvDbLinetypeTableRecord *pLTR) const = 0;

    /** \details
      Setup traits by DgnLS data.

      \param pLTR [in]  Pointer to the Linetype Table Record.
      \param nResFlags [out]  setAttributes return flags.
      \param pTraits [in]  Traits pointer which will be filled by DgnLS data.
      \returns
      Returns kDgnLSProcessed if DgnLS data completely processed. Returns 0 if standard processing is required.
    */
    virtual OdUInt32 setupDgnLSData(const OdTvDbLinetypeTableRecord *pLTR, OdUInt32 &nResFlags, OdGiDrawableTraits *pTraits) const = 0;

    /** \details
      Prepare cache for DgnLS data.

      \param pLTR [in]  Pointer to the Linetype Table Record.
      \param pCache [out]  Pointer to cache object which will be filled by DgnLS data.
      \returns
      Returns kDgnLSProcessed if DgnLS data completely processed. Returns 0 if standard processing is required.
    */
    virtual OdUInt32 prepareDgnLSCache(const OdTvDbLinetypeTableRecord *pLTR, OdRxObjectPtr &pCache) const = 0;

    /** \details
      Setup traits from DgnLS cache.

      \param pCache [in]  Pointer to the DgnLS cache.
      \param nResFlags [out]  setAttributes return flags.
      \param pTraits [in]  Traits pointer which will be filled by DgnLS data.
      \returns
      Returns kDgnLSProcessed if DgnLS data completely processed. Returns 0 if standard processing is required.
    */
    virtual OdUInt32 setupDgnLSCache(const OdRxObject *pCache, OdUInt32 &nResFlags, OdGiDrawableTraits *pTraits) const = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbDgnLSPE object pointers.
*/
typedef OdSmartPtr<OdTvDbDgnLSPE> OdTvDbDgnLSPEPtr;

/** \details
    This class defines the interface for the Entity Protocol Extension classes.
    
    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDgnLSModifiersPE : public OdRxObject
{
  public:
    ODRX_DECLARE_MEMBERS(OdTvDbDgnLSModifiersPE);

    /** \details
      Checks does Entity contain attached DgnLSModifiers data.

      \param pEntity [in]  Pointer to the Entity.
      \returns
      Returns true if Entity have attached DgnLSModifiers data.
    */
    virtual bool hasDgnLSModifiersXData(const OdTvDbEntity *pEntity) const = 0;

    /** \details
      Read DgnLSModifiers data from the Entity.

      \param pEntity [in]  Pointer to the Entity.
      \param pModifiers [out]  DgnLSModifiers read results.
      \param pScale [out]  Optionally return linetype scale.
      \returns
      Returns true if DgnLSModifiers data reading process successfully completed.
    */
    virtual bool readDgnLSModifiersXData(const OdTvDbEntity *pEntity, OdGiDgLinetypeModifiers &pModifiers, double *pScale = NULL) const = 0;

    /** \details
      Read and draw DgnLSModifiers data for the Entity.

      \param pEntity [in]  Pointer to the Entity.
      \param pTraits [out]  Traits where to place DgnLSModifiers read results.
      \returns
      Returns true if DgnLSModifiers data reading process successfully completed.
    */
    virtual bool readDgnLSModifiersXData(const OdTvDbEntity *pEntity, OdGiSubEntityTraits *pTraits) const = 0;

    /** \details
      Write DgnLSModifiers data into the Entity.

      \param pEntity [in]  Pointer to the Entity.
      \param pModifiers [in]  DgnLSModifiers for write.
      \param pScale [in]  Optional linetype scale.
      \returns
      Returns true if DgnLSModifiers data writing process successfully completed.
    */
    virtual bool writeDgnLSModifiersXData(OdTvDbEntity *pEntity, const OdGiDgLinetypeModifiers &pModifiers, const double *pScale = NULL) const = 0;

    /** \details
      Remove DgnLSModifiers data from the Entity.

      \param pEntity [in]  Pointer to the Entity.
      \returns
      Returns true if DgnLSModifiers data removed from the Entity.
    */
    virtual bool removeDgnLSModifiersXData(OdTvDbEntity *pEntity) const = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbDgnLSModifiersPE object pointers.
*/
typedef OdSmartPtr<OdTvDbDgnLSModifiersPE> OdTvDbDgnLSModifiersPEPtr;

#endif //_OD_DB_DGNLS_PE_
