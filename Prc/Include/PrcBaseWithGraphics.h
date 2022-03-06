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

#ifndef _PRCPRCBASEWITHGRAPHICS_INCLUDED_
#define _PRCPRCBASEWITHGRAPHICS_INCLUDED_ 
 

#include "PrcGraphics.h"
#include "PrcBase.h"

SMARTPTR(OdPrcBaseWithGraphics)

/** \details
Class stores data of a referenced base entity with graphics.
<group PRC_Base_Classes>
*/
class PRC_TOOLKIT OdPrcBaseWithGraphics : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcBaseWithGraphics)
  //DOM-IGNORE-END

  /** \details
      Returns current graphics data.
      Graphics data is returned as a reference to an OdPrcGraphics object, therefore it can be used to set new graphics data.
  */
  OdPrcGraphics &graphics();
  
  /** \details
  Returns current graphics data.
  */
  const OdPrcGraphics &graphics() const;

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

#endif // _PRCPRCBASEWITHGRAPHICS_INCLUDED_

