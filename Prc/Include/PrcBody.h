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

#ifndef _PRCBODY_INCLUDED_
#define _PRCBODY_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "Gi/GiDrawable.h"

SMARTPTR(OdPrcBody);
class OdPrcBodyImpl;

/** \details 
<group PRC_Base_Classes>

An abstract class which stores common information about a PRC body.
*/
class PRC_TOOLKIT OdPrcBody : public OdGiDrawable
{
protected:
  OdPrcBody(OdPrcBodyImpl *pImpl);

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_BASE_NOTYPE(OdPrcBody)
  //DOM-IGNORE-END

  /** \details
  Destroys a PRC body object.  
  */
  virtual ~OdPrcBody();

  /** \details
    Reads PRC body information from an input stream and returns a PRC object identifier.
    \param pStream [in] A pointer to a file stream for reading compressed data.
    \returns Returns the PRC object identifier represented by an OdPrcObjectId object.    
  */
  static OdPrcObjectId read(OdPrcCompressedFiler *pStream);
  
  /** \details
    Reads PRC bodies from an input stream into a specified PRC object identifier array.
    \param array    [out] A reference to an OdPrcObjectIdArray where information about bodies must be stored. 
    \param pStream  [in]  A pointer to a file stream for reading compressed data. 
  */
  static void readArray(OdPrcObjectIdArray &array, OdPrcCompressedFiler *pStream);
  
  /** \details 
  Sets a new PRC object ID. 
    \param stub [in] A pointer to a stub used to create a new PRC object ID.
  */
  void setObjectId (OdDbStub* stub);
  
  /** \details 
  Returns the PRC body object ID.
    \remarks 
    PRC body object ID is returned in read-only mode (as a constant reference).
  */
  const OdPrcObjectId& objectId() const;
  
  /** \details 
  Returns the PRC body's serial type.
  */
  virtual OdUInt32 getSerialType() const = 0;

public:
    /** \details 
  Returns true if the PRC body is persistent or false in the other case.
  */
  virtual bool isPersistent() const;

  /** \details 
  Returns true if the PRC body is persistent or false in the other case.
  */
  virtual OdDbStub* id() const;

  /** \details 
  Set a new graphical system cache object for the PRC body.
  \param pGsNode [in] A pointer to a new cache object to be set.
  */
  virtual void setGsNode(OdGsCache* pGsNode);

  /** \details 
  Returns the current graphical system cache object for the PRC body.
  */
  virtual OdGsCache* gsNode() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * wd) const;
  virtual void subViewportDraw (OdGiViewportDraw * vd) const;
};

#endif // _PRCBODY_INCLUDED_

