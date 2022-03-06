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

#ifndef __TNW_GEOMETRYTEXT_H__
#define __TNW_GEOMETRYTEXT_H__

#include "NwGeometry.h"

class OdNwTextFontInfo;
class OdGeVector3d;

/** \details
  This class represents geometry with the text type.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryText : public OdNwGeometry
{
  ODRX_DECLARE_MEMBERS(OdNwGeometryText);

  /** \details
    Default constructor. Creates a new object of the OdNwGeometryText class.
  */
  OdNwGeometryText();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryText();

public:

  /** \details
    Returns the left point of the text geometry data.

    \returns OdGePoint3d of the object with the left point of the text geometry data.
  */
  OdGePoint3d getLeftPoint() const;

  /** \details
    Returns the right point of the text geometry data.

    \returns OdGePoint3d of the object with the right point of the text geometry data.
  */
  OdGePoint3d getRightPoint() const;

  /** \details
    Returns the normal of the text geometry data.

    \returns OdGeVector3d of the object with the normal of the text geometry data.
  */
  OdGeVector3d getNormal() const;

  /** \details
    Returns the text of the text geometry data.

    \returns OdString of the object with the text of the text geometry data.
  */
  OdString getText() const;

  /** \details
    Returns the rotation of the text geometry data.

    \returns The current rotation angle of the text geometry data in radians as a float value.
  */
  float getRotation() const;

  /** \details
    Returns the font of the text geometry data.

    \returns OdNwTextFontInfo of the object with the font of the text geometry data.

    \remarks
    The method is deprecated. Use getTextStyleId() instead.
  */
  OdNwTextFontInfo getFont() const;

  /** \details
    Returns the scale of the text geometry data.

    \returns The current scale of the text geometry data as a float value.
  */
  float getScale() const;

  /** \details
    Returns the objectId of the text style for the text geometry data.

    \returns OdNwObjectId of the object with the text style for the text geometry data.
  */
  OdNwObjectId getTextStyleId() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGeometryText object pointers.
*/
typedef OdSmartPtr<OdNwGeometryText> OdNwGeometryTextPtr;

#endif //__TNW_GEOMETRYTEXT_H__
