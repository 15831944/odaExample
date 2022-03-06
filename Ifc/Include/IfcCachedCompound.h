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

#ifndef _IFC_CACHED_COMPOUND_H_
#define _IFC_CACHED_COMPOUND_H_

#include "IfcCompound.h"

/** \details 
Contains declarations related to working with IFC files content.
*/
namespace OdIfc {

/** \details 
A class that implements working with a cached IFC compound object.
*/
class IFCCORE_EXPORT OdIfcCachedCompound : public OdIfcCompound
{
//DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcCachedCompound);
  

protected:

  OdGsCache   *m_pGsNode;
//DOM-IGNORE-END

public:

  /**\details 
  Creates a new cached compound object with default parameters.
  */
  OdIfcCachedCompound() : m_pGsNode(NULL) {};

  /** \details 
  Sets a new Gs node cache for the compound object.
  \param pGsNode [in] A raw pointer to an <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object.
  */
  virtual void setGsNode(OdGsCache* pGsNode);

  /** \details
  Retrieves the current Gs node object of the compound object.
  \returns Returns a raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object associated with the entity.
  */
  virtual OdGsCache* gsNode() const;

};

/** \details 
A data type that represents a smart pointer to an <link OdIfc::OdIfcCachedCompound, OdIfcCachedCompound> object.
*/
typedef OdSmartPtr<OdIfcCachedCompound> OdIfcCachedCompoundPtr;

} //namespace OdIfc

#endif // _IFC_CACHED_COMPOUND_H_
