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

#ifndef OD_DBGEODATADRAWINGPE_H
#define OD_DBGEODATADRAWINGPE_H

#include "Gi/GiDrawable.h"
#include "Gs/GsModel.h"

/** \details
An abstract class that represents a protocol extension for an OdTvDbGeoData object to draw chunks images for OdTvDbGeoData.

<group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGeoDataChunksPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbGeoDataChunksPE);

  /** \details
    Virtual destructor.
  */
  virtual ~OdTvDbGeoDataChunksPE() {};
  /** \details
    Draws chunks images for OdTvDbGeoData.
    
    \param pWd [in] Pointer to the OdGiWorldDraw interface.
    
    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  virtual OdResult drawGeoDataChunks(OdGiViewportDraw* pVd) const = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbGeoDataChunksPE object pointers.
*/
typedef OdSmartPtr<OdTvDbGeoDataChunksPE> OdTvDbGeoDataChunksPEPtr;

/** \details
An abstract class that represents a protocol extension for an OdTvDbGeoData object to draw providers string for OdTvDbGeoData.

<group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGeoDataProvidersStringPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbGeoDataProvidersStringPE);

  /** \details
    Virtual destructor.
  */
  virtual ~OdTvDbGeoDataProvidersStringPE() {};
  /** \details
    Draws providers string for currently drawn OdTvDbGeoData chuncks.

    \param pWd [in] Pointer to the OdGiWorldDraw interface.

    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  virtual OdResult drawGeoDataProvidersString(OdGiViewportDraw* pVd) const = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbGeoDataProvidersStringPE object pointers.
*/
typedef OdSmartPtr<OdTvDbGeoDataProvidersStringPE> OdTvDbGeoDataProvidersStringPEPtr;

class OdTvDbGeoDataChunks;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbGeoDataChunks object pointers.
*/
typedef OdSmartPtr<OdTvDbGeoDataChunks> OdTvDbGeoDataChunksPtr;

/** \details
  This class represents implementation of OdGiDrawable, that is used to draw chucks images of OdTvDbGeoData.

  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGeoDataChunks : public OdGiDrawable
{
  OdTvDbGeoDataChunks& operator = (const OdTvDbGeoDataChunks&);
  OdGsCache* m_pGsNode;
  OdRefCounter m_nRefCounter;
protected:
  OdTvDbGeoDataChunks();
public:
  void addRef()
  {
    ++m_nRefCounter;
  }
  void release()
  {
    ODA_ASSERT((m_nRefCounter > 0));
    if (!(--m_nRefCounter))
    {
      delete this;
    }
  }
  long numRefs() const { return m_nRefCounter; }

  void setGsNode(OdGsCache* pGsNode) { m_pGsNode = pGsNode; }
  OdGsCache* gsNode() const { return m_pGsNode; }
  bool isPersistent() const { return false; }
  OdDbStub* id() const { return 0; }

public:
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  bool subWorldDraw(OdGiWorldDraw* pWd) const;
  void subViewportDraw(OdGiViewportDraw* pVd) const;

  /** \details
    Virtual destructor.
  */
  ~OdTvDbGeoDataChunks();

  /** \details
    It is the pseudo-constructor that creates an instance of this class and returns the typified smart pointer to it.
  */
  static OdTvDbGeoDataChunksPtr createObject()
  {
    return OdRxObjectImpl<OdTvDbGeoDataChunks>::createObject();
  }
};


class OdTvDbGeoDataProvidersString;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbGeoDataProvidersString object pointers.
*/
typedef OdSmartPtr<OdTvDbGeoDataProvidersString> OdTvDbGeoDataProvidersStringPtr;

/** \details
  This class represents implementation of OdGiDrawable, that is used to draw providers string for OdTvDbGeoData.

  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGeoDataProvidersString : public OdGiDrawable
{
  OdTvDbGeoDataProvidersString& operator = (const OdTvDbGeoDataProvidersString&);
  OdGsCache* m_pGsNode;
  OdRefCounter m_nRefCounter;
protected:
  OdTvDbGeoDataProvidersString();
public:
  void addRef()
  {
    ++m_nRefCounter;
  }
  void release()
  {
    ODA_ASSERT((m_nRefCounter > 0));
    if (!(--m_nRefCounter))
    {
      delete this;
    }
  }
  long numRefs() const { return m_nRefCounter; }

  void setGsNode(OdGsCache* pGsNode) { m_pGsNode = pGsNode; }
  OdGsCache* gsNode() const { return m_pGsNode; }
  bool isPersistent() const { return false; }
  OdDbStub* id() const { return 0; }

public:
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  bool subWorldDraw(OdGiWorldDraw* pWd) const;
  void subViewportDraw(OdGiViewportDraw* pVd) const;

  /** \details
    Virtual destructor.
  */
  ~OdTvDbGeoDataProvidersString();

  /** \details
    It is the pseudo-constructor that creates an instance of this class and returns the typified smart pointer to it.
  */
  static OdTvDbGeoDataProvidersStringPtr createObject()
  {
    return OdRxObjectImpl<OdTvDbGeoDataProvidersString>::createObject();
  }
};
#endif
