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

#ifndef __TNW_BACKGROUNDELEMENT_H__
#define __TNW_BACKGROUNDELEMENT_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwCategory.h"
#include "NwBackgroundType.h"
#include "NwGraphicJsonBundle.h"

class OdNwColor;

/** \details
  This class represents a background element with colors.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwBackgroundElement : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwBackgroundElement);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwBackgroundElement
    class.
  */
  OdNwBackgroundElement();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwBackgroundElement();

public:

  /** \details
    Returns the displayed background type that should be used for rendering.

    \returns NwBackgroundType::Enum value with the displayed background type.

    \remarks
    The returned type must be one of the following:

    <table>
    Name                             Value     Description
    NwBackgroundType::PLAIN          0         Plain background
    NwBackgroundType::GRADUATED      1         Graduated background
    NwBackgroundType::HORIZON        2         Horizon background
    </table>
  */
  NwBackgroundType::Enum getBackgroundType() const;

  /** \details
    Returns the background plain color.

    \param color [out] Object of OdNwColor with the plain color.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getPlainColor(OdNwColor& color) const;

  /** \details
    Returns the background graduated color.

    \param top    [out] OdNwColor object with the top color.
    \param bottom [out] OdNwColor object with the bottom color.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getGraduatedColor(OdNwColor& top, OdNwColor& bottom) const;

  /** \details
    Returns the background horizon color.

    \param skyColor           [out] OdNwColor object with the sky color.
    \param horizonSkyColor    [out] OdNwColor object with the horizon sky color.
    \param horizonGroundColor [out] OdNwColor object with the horizon ground color.
    \param groundColor        [out] OdNwColor object with the ground color.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getHorizonColor(OdNwColor& skyColor, OdNwColor& horizonSkyColor, OdNwColor& horizonGroundColor, OdNwColor& groundColor) const;

  /** \details
    Returns the material data for a complex background.

    \returns Smart pointer to the OdNwCategory object if successful, or an empty
    smart pointer if the complex background data does not exist.
  */
  OdNwCategoryPtr getMaterial() const;

  /** \details
    Returns a graphic JSON object for a complex background.

    \returns Smart pointer to the OdNwGraphicJsonBundle object, or an empty
    smart pointer if the object does not exist.
  */
  OdNwGraphicJsonBundlePtr getGraphicJson() const;

  /** \details
    Sets the background type as plain.

    \param plainColor [in] OdNwColor object with the plain color.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult setPlainBackground(const OdNwColor& plainColor);

  /** \details
    Sets the background type as graduated.

    \param topColor    [in] OdNwColor object with the top color.
    \param bottomColor [in] OdNwColor object with the bottom color.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult setGraduatedBackground(const OdNwColor& topColor, const OdNwColor& bottomColor);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwBackgroundElement object pointers.
*/
typedef OdSmartPtr<OdNwBackgroundElement> OdNwBackgroundElementPtr;

#endif //__TNW_BACKGROUNDELEMENT_H__
