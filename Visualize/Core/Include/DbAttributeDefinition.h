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




#ifndef _OD_DB_ATTRDEF_
#define _OD_DB_ATTRDEF_

#include "TD_PackPush.h"

#include "DbText.h"
#include "DbMText.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents attribute defintion (Attdef) entities in an OdTvDbDatabase instance.
  
    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbAttributeDefinition : public OdTvDbText
{
public:

  DWGMAP_DECLARE_MEMBERS(OdTvDbAttributeDefinition);
  OdTvDbAttributeDefinition();

  /** \details
    Returns the prompt string of this Attdef entity (DXF 3).
  */
  const OdString prompt() const;

  /** \details
    Sets the prompt string of this Attdef entity (DXF 3).
    \param promptString [in]  Prompt string
  */
  void setPrompt(
    const OdString& promptString);

  /** \details
    Returns the tag string of this Attdef entity (DXF 2).
  */
  const OdString tag() const;

  /** \details
    Sets the tag string of this Attdef entity (DXF 2).
    \param tagString [in]  Tag string.  
  */
  void setTag(
    const OdString& tagString);

  /** \details
    Returns true if and only if this Attdef entity is invisible (DXF 70, bit 0x01).
  */
  bool isInvisible() const;

  /** \details
    Controls the invisibility of this Attdef entity (DXF 70, bit 0x01).

    \param invisible [in]  Controls invisibility.
  */
  void setInvisible(
    bool invisible);

  /** \details
    Returns true if and only if this Attdef entity is constant (DXF 70, bit 0x02).
  */
  virtual bool isConstant() const;

  /** \details
    Controls the constant status of this Attdef entity (DXF 70, bit 0x02).
    \param constant [in]  Controls constant status.
  */
  void setConstant(bool constant);

  /** \details
    Returns true if and only if this Attdef entity is verifiable (DXF 70, bit 0x04).
  */
  bool isVerifiable() const;

  /** \details
    Controls the verifiable status of this Attdef entity (DXF 70, bit 0x04).
    \param verifiable [in]  Controls verifiable status.
  */
  void setVerifiable(bool);

  /** \details
    Returns true if and only if this Attdef entity is preset (DXF 70, bit 0x08).
  */
  bool isPreset() const;

  /** \details
    Controls the preset status of this Attdef entity (DXF 70, bit 0x08).
    \param preset [in]  Controls preset status.
  */
  void setPreset(bool);

  /** \details
    Returns the field length of this Attdef entity (DXF 73).
  */
  OdUInt16 fieldLength() const;

  /** \details
    Sets the field length of this Attdef entity (DXF 73).
    \param fieldLength [in]  Field length.
  */
  void setFieldLength(
    OdUInt16 fieldLength);

  virtual OdResult subGetClassID(
    void* pClsid) const;

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual OdResult dxfInFields_R12(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdTvDbDxfFiler* pFiler) const;

  bool subWorldDraw(
    OdGiWorldDraw* pWd) const;
  void subViewportDraw(
    OdGiViewportDraw* pVd) const;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  void appendToOwner(
    OdTvDbIdPair& Idpair, 
    OdTvDbObject* pOwnerObject, 
    OdTvDbIdMapping& ownerIdMap);

  bool lockPositionInBlock() const;
  void setLockPositionInBlock(bool bValue);
  // multiline attribute definition support
  bool isMTextAttributeDefinition() const;
  OdTvDbMTextPtr getMTextAttributeDefinition() const;
  void setMTextAttributeDefinition(OdTvDbMText*);
  void convertIntoMTextAttributeDefinition (bool val = true);
  void updateMTextAttributeDefinition();
  virtual void subClose() ODRX_OVERRIDE;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbAttributeDefinition object pointers.
*/
typedef OdSmartPtr<OdTvDbAttributeDefinition> OdTvDbAttributeDefinitionPtr;

#include "TD_PackPop.h"

#endif

