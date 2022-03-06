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

#ifndef _PRCGRAPHICS_INCLUDED_
#define _PRCGRAPHICS_INCLUDED_ 
 

#include "PrcRgbColor.h"
#include "PrcObjectId.h"

/** \details 
<group PRC_Graphic_Classes> 

Class stores information about graphics.
*/
class PRC_TOOLKIT OdPrcGraphics
{
private:
  OdPrcObjectId m_LineStyle;
  OdUInt32      m_layer_index;
  OdUInt16      m_behaviour_bit_field;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcGraphics)
  //DOM-IGNORE-END

  /** \details
  Returns current line style id.
  Line style id is returned as a reference, therefore it can be used to set new data.
  */
  OdPrcObjectId &styleId();
  
  /** \details
  Returns current line style.
  */
  const OdPrcObjectId &styleId() const;
  
  /** \details
  Sets a new layer index.

  \param layer_index [in] A new layer index to be set.
  */
  void setLayerIndex(OdUInt32 layer_index);
  
  /** \details
  Returns the current layer index.
  */
  OdUInt32 layerIndex() const;
  
  /** \details
  Sets a new value of the behavior bit field.
  The behavior bit field controls visibility and removal of the entity.

  \param behaviour_bit_field [in] A new value of the behavior bit field.
  */
  void setBehaviourBitField(OdUInt16 behaviour_bit_field);
  
  /** \details
  Returns current behavior bit field.
  The behavior bit field controls visibility and removal of the entity.
  */
  OdUInt16 behaviourBitField() const;

  /** \details
  Comparison operator for graphics data.

  \param other [in] Other graphics data to be compared with.

  \returns Returns true if the graphic data is equal with the compared data
  or false in the other case.
  */
  bool operator ==(const OdPrcGraphics &other) const;
  
  /** \details
  The copy constructor for the OdPrcGraphics class.
  
  \param source [in] A reference to a graphic object to be copied.
  */
  OdPrcGraphics(const OdPrcGraphics &source);

  /** \details
  Returns the current value of the true color.
  
  \param rgb [out] A reference to store the current true color value.

  \returns Returns true if the color has been successfully returned or false in the other case.
  */
  bool getTrueColor(OdCmEntityColor &rgb) const;

  /** \details
  Returns the identifier of the current material.
  */
  OdPrcObjectId getMaterial() const;
};

typedef OdArray<OdPrcGraphics> OdPrcGraphicsArray;

#endif // _PRCGRAPHICS_INCLUDED_

