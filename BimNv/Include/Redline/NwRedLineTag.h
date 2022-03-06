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

#ifndef __NWREDLINETAG_INCLUDED_
#define __NWREDLINETAG_INCLUDED_

#include "NwRedLine.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeExtents3d.h"

/** \details
  This class represents tag redline objects.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwRedLineTag : public OdNwRedLine
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwRedLineTag);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwRedLineTag object.
  */
  OdNwRedLineTag();
public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwRedLineTag();

public:
  /** \details
    Returns the direction flag.

    \returns Boolean value of the direction flag.
  */
  bool getDirectionFlag() const;
  /** \details
    Returns the direction vector.

    \returns Direction value as an OdGeVector3d object.
  */
  OdGeVector3d getDirection();
  /** \details
    Returns the bounding flag.

    \returns Boolean value of the bounding flag.
  */
  bool getBoundFlag() const;
  /** \details
    Returns the bounding box.

    \returns Bounding box as an OdGeExtents3d object.
  */
  OdGeExtents3d getBound() const;
  /** \details
    Returns the position.

    \returns Position as an OdGeExtents2d object.
  */
  OdGeExtents2d getPosition() const;
  /** \details
    Returns the tag's identifier.

    \returns ID of the tag as an OdUInt64 value.
  */
  OdUInt64 getTagId() const;
  /** \details
    Returns the comment's identifier.

    \returns ID of the comment as an OdUInt64 value.
  */
  OdUInt64 getCommentId() const;

public:
  /** \details
    Sets the direction flag.

    \param val [in] New direction flag value.
  */
  void setDirectionFlag(bool val);
  /** \details
    Sets the direction vector.

    \param val [in] New direction vector value.
  */
  void setDirection(const OdGeVector3d& val);
  /** \details
    Sets the bounding flag.

    \param val [in] New bounding flag value.
  */
  void setBoundFlag(bool val);
  /** \details
    Sets the bounding box.

    \param val [in] New bounding box extents.
  */
  void setBound(const OdGeExtents3d& val);
  /** \details
    Sets the position.

    \param val [in] New position extents.
  */
  void setPosition(const OdGeExtents2d& val);
  /** \details
    Sets the tag's identifier.

    \param val [in] New tag ID value.
  */
  void setTagId(OdUInt64 val);
  /** \details
    Sets the comment's identifier.

    \param val [in] New comment ID value.
  */
  void setCommentId(OdUInt64 val);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwRedLineTag object pointers.
*/
typedef OdSmartPtr<OdNwRedLineTag> OdNwRedLineTagPtr;

#endif //__NWREDLINETAG_INCLUDED_
