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

// IfcModelContext.h: interface for the OdIfcModelContext class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_MODEL_CONTEXT_H
#define _IFC_MODEL_CONTEXT_H

#include "IfcBuildOptions.h"
#include "IfcEntityTypes.h"
#include "IfcDeviationParams.h"

    /** \details 
  A class that implements working with an IFC model context.
  */
  class IFCCORE_EXPORT OdIfcModelContext
  {
  public:

    /** \details 
    Creates a new model context object with specified deviation parameters and color.
    \param params [in] Deviation parameters.
    \param color  [in] Default model color value.
    */
    OdIfcModelContext(OdIfcDeviationParams params = OdIfcDeviationParams(), OdCmEntityColor color = OdCmEntityColor::kNone);

    /** \details 
    Retrieves the current set of deviation parameters assigned with the model context.
    \returns Returns an instance of the <link OdIfc::OdIfcDeviationParams, OdIfcDeviationParams> class that contains the current deviation parameters.
    */
    OdIfcDeviationParams getDeviationParams() const;
    
    /** \details 
    Sets new deviation parameters for the model context.
    \param params [in] Deviation parameters to be set.
    */
    void setDeviationParams(OdIfcDeviationParams params);

    /** \details 
    Retrieves the current default model color.
    \returns Returns an instance of the <exref target="https://docs.opendesign.com/tkernel/OdCmEntityColor.html">OdCmEntityColor</exref> object that contains the current default color for the model.
    */
    OdCmEntityColor getDefaultEntityColor() const;
    
    /** \details 
    Sets a new default model color.
    \param color [in] An instance of the <exref target="https://docs.opendesign.com/tkernel/OdCmEntityColor.html">OdCmEntityColor</exref> object that represents the new default color.
    */
    void setDefaultEntityColor(const OdCmEntityColor& color);

    /** \details
    Retrieves an array of types which instances should participate in geometry compose process.
    \returns an array of IFC entity types for geometry compose.
    \remarks
    Types should be derived from IfcProduct.
    */
    OdArray<OdIfc::OdIfcEntityType>& getGeometryComposeTypes();

    /** \details
    Sets an array of types which instances should participate in geometry compose process to this IFC model context.
    \param geometryComposeTypes [in] an array of IFC entity types for geometry compose.
    \remarks
    Types should be derived from IfcProduct.
    */
    void setGeometryComposeTypes(const OdArray<OdIfc::OdIfcEntityType> &geometryComposeTypes);

    void setSkipComposeIds(const OdDAIObjectIds& notComposeContext);

    bool checkSkipComposeId(const OdDAIObjectId& id) const;

    void setInterruptCallback(OdDAI::InterruptCallback callbackFunction);

    OdDAI::InterruptCallback getInterruptCallback();

//DOM-IGNORE-BEGIN
  private:
    OdIfcDeviationParams m_deviationParams;
    OdCmEntityColor m_defaultEntityColor;
    OdDAIObjectIds m_selContexts;
    OdDAI::InterruptCallback m_interrupt = nullptr;
    OdArray<OdIfc::OdIfcEntityType> m_composeTypes;
    OdDAIObjectIds m_skipComposeIds;
//DOM-IGNORE-END
  };

#endif // _IFC_MODEL_CONTEXT_H
