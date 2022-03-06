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

#ifndef __NW_SAVEDANIMSCENE_H__
#define __NW_SAVEDANIMSCENE_H__

#include "NwSavedAnimGroup.h"

/**
 This class represents animation scene.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedAnimScene : public OdNwSavedAnimGroup
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimScene);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwSavedAnimScene();

  /** \details
    Constructor for objects of the OdNwSavedAnimScene class. Creates a new
    OdNwSavedAnimScene object for the specified item.

    \param pImpl [in] Item to create an OdNwSavedAnimScene object for.
  */
  explicit OdNwSavedAnimScene(OdNwObjectImpl* pImpl);

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedAnimScene();
  
  /** \details
    Returns time of the end of the all animations.

   \returns Time of the end of the all animations as an double.
  */
  double getEndTime() const;
  
  /** \details
   Determines whether the animation is in Infinite mode.

   \returns True if the animation is in Infinite mode, or false otherwise.
  */
  bool isInfinite() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSavedAnimScene object pointers.
*/
typedef OdSmartPtr<OdNwSavedAnimScene> OdNwSavedAnimScenePtr;

#endif /* __NW_SAVEDANIMSCENE_H__ */
