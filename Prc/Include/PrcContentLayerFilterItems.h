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

#ifndef _PRCCONTENTLAYERFILTERITEMS_INCLUDED_
#define _PRCCONTENTLAYERFILTERITEMS_INCLUDED_ 
 

  /** \details
    <group PRC_Files_Structures_Assemblies>
    Class representing information for an entity filtered by layer.
  */
class PRC_TOOLKIT OdPrcContentLayerFilterItems
{
private:
  OdUInt32Array  m_layer_index;
  bool           m_isInclusive;
public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcContentLayerFilterItems)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of layer indexes.
  The array of layer indexes is returned as a reference to an OdUInt32Array object, therefore it can be used to set new layer indexes.
  */
  OdUInt32Array &layerIndex();
  
  /** \details
  Returns the current array of layer indexes.
  */
  const OdUInt32Array &layerIndex() const;

  /** \details
  Sets a new value of the inclusive flag. 
  The inclusive flag indicates whether the elements in the filter will be stored (if true) or not (if false).
  
  \param isInclusive [in] A new value of the inclusive flag to be set.
  */
  void setIsInclusive(bool isInclusive);

  /** \details
  Returns the current value of the inclusive flag. 
  The inclusive flag indicates whether the elements in the filter will be stored (if true) or not (if false).
  */
  bool isInclusive() const;
};

#endif // _PRCCONTENTLAYERFILTERITEMS_INCLUDED_

