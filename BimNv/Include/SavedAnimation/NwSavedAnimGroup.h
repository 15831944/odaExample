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

#ifndef __NW_SAVEDANIMGROUP_H__
#define __NW_SAVEDANIMGROUP_H__

#include "NwSavedFolderItem.h"
/**
 This class represents animation camera.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedAnimGroup : public OdNwSavedGroupItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimGroup);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwSavedAnimGroup();

  /** \details
    Constructor for objects of the OdNwSavedAnimGroup class. Creates a new
    OdNwSavedAnimGroup object for the specified item.

    \param pImpl [in] Item to create a OdNwSavedAnimGroup object for.
  */
  explicit OdNwSavedAnimGroup(OdNwObjectImpl* pImpl);
  
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedAnimGroup();
  
  /** \details
   Determines whether the animation is in Loop mode.

   \returns True if the animation is in Loop mode, or false otherwise.
  */
  bool isLoop() const;
  
  /** \details
   Determines whether the animation is in Ping-Pong mode.
   
   \returns True if the animation is in Ping-Pong mode, or false otherwise.
  */
  bool isPingPong() const;
  
  /** \details
   Determines whether the animation is active in the scene.
   
   \returns True if the animation is active in the scene, or false otherwise.
  */
  bool isActive() const;

};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSavedAnimGroup object pointers.
*/
typedef OdSmartPtr<OdNwSavedAnimGroup> OdNwSavedAnimGroupPtr;

#endif /* __NW_SAVEDANIMGROUP_H__ */
