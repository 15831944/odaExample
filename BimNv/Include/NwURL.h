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

#ifndef __NWURLDEF_INCLUDED_
#define __NWURLDEF_INCLUDED_

#include "NwObject.h"
#include "Ge/GePoint3dArray.h"

class OdNwName;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwName object pointers.
*/
typedef OdSmartPtr<OdNwName> OdNwNamePtr;

/** \details
  This structure represents url definition object.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwURL : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwURL);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwURL
    class.
  */
  OdNwURL();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwURL();

public:
  /** \details
    Returns the name of URL.
    
    \returns OdString value with URL name.
  */
  OdString getName() const;

  /** \details
    Returns the url.
    
    \returns OdString value with URL.
  */
  OdString getURL() const;

  /** \details
    Returns the URL category.
    
    \returns OdNwNamePtr object with URL category.
  */
  OdNwNamePtr getCategory() const;

  /** \details
    Returns the attachment to url points.
    
    \returns OdGePoint3dArray with attachment points.
  */
  OdGePoint3dArray getAttachmentPoints() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwURL object pointers.
*/
typedef OdSmartPtr<OdNwURL> OdNwURLPtr;

#endif //__NWURLDEF_INCLUDED_
