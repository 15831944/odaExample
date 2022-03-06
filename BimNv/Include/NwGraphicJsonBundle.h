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

#ifndef __TNW_GRAPHICJSONBUNDLE_H__
#define __TNW_GRAPHICJSONBUNDLE_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"

class OdBinaryData;

/** \details
  This class represents a background element with colors.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGraphicJsonBundle : public OdNwObject
{
  ODRX_DECLARE_MEMBERS(OdNwGraphicJsonBundle);

public:
  /** \details
    Default constructor. Creates a new OdNwGraphicJsonBundle object.
  */
  OdNwGraphicJsonBundle();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGraphicJsonBundle();

public:
  /** \details
    Returns the main json of the objects.

    \returns Returns an OdString with json content.
  */
  OdString getJson() const;
  /** \details
    Sets the main json string.

    \param json [in] String with the main json.
  */
  void setJson(OdString json);
  /** \details
    Sets the material json string.

    \param json [in] String with the material json.
  */
  void setMaterialJson(OdString json);
  /** \details
    Returns the material json of the objects.

    \returns Returns an OdString with material json content.
  */
  OdString getMaterialJson() const;
  /** \details
    Sets a file reference.

    \param key [in] String with the file's key.
    \param name [in] String with the file's path.
  */
  void setFileRef(OdString key, OdString name);
  /** \details
    Returns the file reference by key.

    \returns Returns an OdString with the file path if it exists or an empty string otherwise.
  */
  OdString getFileRef(OdString key) const;
  /** \details
    Sets a temporary file.

    \param key [in] String with the file's key.
    \param cantent [in] OdBinaryData with the file's content.
  */
  void setFileEmbedded(OdString key, const OdBinaryData& content);
  /** \details
    Returns the temporary file content by key.

    \returns Returns an OdBinaryData with the temporary file content.
  */
  OdBinaryData getFileEmbedded(OdString key) const;
  /** \details
    Returns the file reference keys.

    \returns Returns an array of strings with the file reference keys.
  */
  OdArray<OdString> getFileRefKeys() const;
  /** \details
    Returns the embedded file keys.

    \returns Returns an array of strings with embedded file keys.
  */
  OdArray<OdString> getFileEmbeddedKeys() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGraphicJsonBundle object pointers.
*/
typedef OdSmartPtr<OdNwGraphicJsonBundle> OdNwGraphicJsonBundlePtr;

#endif //__TNW_GRAPHICJSONBUNDLE_H__
