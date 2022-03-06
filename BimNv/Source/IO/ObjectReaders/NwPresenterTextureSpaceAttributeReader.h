  /////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2018, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related Textures are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2019 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related Textures, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#ifndef __NW_PRESENTER_TEXTURE_SPACE_ATTRIBUTE_REDAER_H__
#define __NW_PRESENTER_TEXTURE_SPACE_ATTRIBUTE_REDAER_H__

#include "NwObjectReaderManager.h"
#include "NwObjectReader.h"
#include "TD_PackPush.h"

class OdNwPresenterTextureSpaceAttributeReader : public OdNwObjectReader
{
public:
  OdNwPresenterTextureSpaceAttributeReader();
  explicit OdNwPresenterTextureSpaceAttributeReader(OdNwObjectPtr pElement);
  virtual ~OdNwPresenterTextureSpaceAttributeReader() override;
  OdResult readFromStream(OdNwObjectReaderManager* stream) override;

protected:
  OdResult readShader(OdString& sRes, OdNwObjectReaderManager* stream);
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwPresenterTextureSpaceAttributeReader object pointers.
*/
typedef OdSharedPtr<OdNwPresenterTextureSpaceAttributeReader> OdNwPresenterTextureAttributeReaderPtr;

#include "TD_PackPop.h"

#endif // __NW_PRESENTER_TEXTURE_SPACE_ATTRIBUTE_REDAER_H__
