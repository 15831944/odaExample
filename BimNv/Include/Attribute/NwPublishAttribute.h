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

#ifndef __TNW_PUBLISH_ATTRIBUTE_H__
#define __TNW_PUBLISH_ATTRIBUTE_H__

#include "NwAttribute.h"

/** \details
  This class represents an attribute with publish data.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPublishAttribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwPublishAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwPublishAttribute
    class.
  */
  OdNwPublishAttribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPublishAttribute();

public:
  /** \details
    Returns the title of the publish.
    
    \returns Title of the publish.
  */
  OdString getTitle() const;

  /** \details
    Returns the subject of publish.
    
    \returns Subject of publish.
  */
  OdString getSubject() const;

  /** \details
    Returns the author of publish.
    
    \returns Author of publish.
  */
  OdString getAuthor() const;

  /** \details
    Returns the publisher of publish.
    
    \returns Publisher of publish.
  */
  OdString getPublisher() const;

  /** \details
    Returns publish dat.
    
    \returns Datetime value of publish date.
  */
  tm getPublishDate() const;

  /** \details
    Returns expiry dat.
    
    \returns Datetime value of expiry date.
  */
  tm getExpiryDate() const;

  /** \details
    Returns the copyright of publish.
    
    \returns Copyright of publish.
  */
  OdString getCopyright() const;

  /** \details
    Returns the published for is this publish.
    
    \returns Published for of publish.
  */
  OdString getPublishedFor() const;

  /** \details
    Returns the comments of publish.
    
    \returns Comments of publish.
  */
  OdString getComments() const;

  /** \details
    Returns the keywords of publish.
    
    \returns Keywords of publish.
  */
  OdString getKeywords() const;

  /** \details
    Returns the password for is this publish.
    
    \returns Password for of publish.
  */
  OdString getPassword() const;

public:
  /** \details
    Returns the flag that this attribute has expiry date.
  
    \returns True if attribute has expiry date, or false if not.
  */
  bool hasExpiryDate() const;
  
  /** \details
    Returns the flag that this attribute has password.
  
    \returns True if attribute has password, or false if not.
  */
  bool hasPassword() const;
    
  /** \details
    Returns the flag that publish can be displayed while open.
  
    \returns True if publish can be displayed while open, or false if not.
  */
  bool displayOnOpen() const;
    
  /** \details
    Returns the flag that password can be displayed.
  
    \returns True if password can be displayed, or false if not.
  */
  bool displayAtPassword() const;
    
  /** \details
    Returns the flag that publish was edited.
  
    \returns True if  publish was edited, or false if not.
  */
  bool isEdited() const;
    
  /** \details
    Returns the flag that this publish can be resaved.
  
    \returns True if publish can be resaved, or false if not.
  */
  bool canBeResaved() const;
    
  /** \details
    Returns the flag that publish contain embed ReCap and Textures.
  
    \returns True if publish contain embed ReCap and Textures, or false if not.
  */
  bool embedRecapAndTextures() const;
    
  /** \details
    Returns the flag that publish contain embed database properties.
  
    \returns True if publish contain embed database properties, or false if not.
  */
  bool embedDbProperties() const;
    
  /** \details
    Returns the flag that publish contain prevent object property export.
  
    \returns True if publish contain prevent object property export, or false if not.
  */
  bool preventObjectPropertyExport() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwPublishAttribute object pointers.
*/
typedef OdSmartPtr<OdNwPublishAttribute> OdNwPublishAttributePtr;

#endif //__TNW_PUBLISH_ATTRIBUTE_H__
