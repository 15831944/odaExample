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


#ifndef _DbRevolveOptions_h_Included_
#define _DbRevolveOptions_h_Included_

#include "TD_PackPush.h"
#include "DbSurface.h"

class OdTvDbRevolveOptionsImpl;

/** \details
Class for setting options used for creating revolving surfaces and revolving solids 
(by calling OdTvDbRevolvedSurface::createRevolvedSurface() or OdTvDb3dSolid::createRevolvedSolid() methods).
Revolve options are used to control the shape of the resulting surface or solid object.

<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbRevolveOptions
{
public:
  /** \details 
  Creates an instance of revolving surface options.
  */
  OdTvDbRevolveOptions();
  
  /** \details 
  Creates a copy of another instance of revolving surface options (copy constructor).
  
  \param src [in] An instance of revolving surface options to be copied.
  */
  OdTvDbRevolveOptions(const OdTvDbRevolveOptions& src);
  
  /** \details 
  Destroys the instance of revolving surface options.
  */
  ~OdTvDbRevolveOptions();
  
  /** \details 
  Assigning operator for revolving surface options.
  
  \param src [in] An instance of revolving surface options to be assigned to this instance.
  */
  OdTvDbRevolveOptions& operator =(const OdTvDbRevolveOptions& src);

  /** \details
  Returns the draft angle in radians. 
 
  Draft angle is an angle of a profile's taper relative to the axis while the profile is revolving around the axis.
  The default value is equal to 0.0. 
  */
  double draftAngle() const;
  
  /** \details
  Sets the draft angle.
  
  Draft angle is an angle of a profile's taper relative to the axis while the profile is revolving around the axis.
  The default value is equal to 0.0. 
  
  \param ang [in]  A new draft angle (radians).
  */
  void setDraftAngle(double ang);

  /** \details
  Returns the twist angle in radians.

  Twist angle is the angle of a profile's twisting while the profile is revolving around the axis in radians. 
  The default value is equal to 0.0.
  */
  double twistAngle() const;
  
  /** \details
  Sets the twist angle.
  
  Twist angle is the angle of a profile's twisting while the profile is revolving around the axis in radians. 
  The default value is equal to 0.0.
  
  \param ang [in]  A new twist angle (radians).
  */
  void setTwistAngle(double ang);

  /** \details
  Returns the value of the close to axis option.
  
  If the close to axis option is equal to true, then the ends of the profile will be extended to the axis of revolution before revolving. 
  The default value of the option is false.
  */
  bool closeToAxis() const;
  
  /** \details
  Sets the value of the close to axis option.
  
  If the close to axis option is equal to true, then the ends of the profile will be extended to the axis of revolution before revolving. 
  The default value of the option is false.
  
  \param val [in]  A new value of the close to axis option.

  */
  void setCloseToAxis(bool val);

  /** \details
  Checks whether a specified entity is valid for the revolve operation.
  
  \param pRevEnt              [in]  A pointer to the entity (curve or region) to be revolved.
  \param axisPnt              [in]  A point on the axis of revolution.
  \param axisDir              [in]  A vector determining the direction of the revolution axis.
  \param closed               [out] A passed-in parameter for returning the indicator determining whether the revolved entity is closed.
  \param endPointsOnAxis      [out] A passed-in parameter for returning the indicator determining whether the revolved entity is open and whether its endpoints lie on the axis of revolution.
  \param planar               [out] A passed-in parameter for returning the indicator determining whether the revolved entity is planar.
  \param displayErrorMessages [in]  Indicates whether error messages are displayed. Default value is false.
  
  \returns Returns eOk if a specified entity is valid for revolving, or eInvalidInput otherwise.
  
  \remarks
  The method is called by OdTvDbRevolvedSurface:: createRevolvedSurface() and OdTvDb3dSolid::createRevolvedSolid() methods, so it is not necessary for a client application to call it. 
  */
  OdResult checkRevolveCurve(
    OdTvDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    bool& closed,
    bool& endPointsOnAxis,
    bool& planar,
    bool displayErrorMessages = false);

private:
  friend class OdTvDbRevolveOptionsImpl;
  OdTvDbRevolveOptionsImpl* m_pImpl;
};

#include "TD_PackPop.h"
#endif //_DbRevolveOptions_h_Included_
