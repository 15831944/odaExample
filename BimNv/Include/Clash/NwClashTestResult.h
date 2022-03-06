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

#ifndef _NW_CLASHTESTRESULT_H_
#define _NW_CLASHTESTRESULT_H_
#include "NwSavedItem.h"
#include "Clash/NwClashTypes.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeExtents3d.h"

/** \details
  This class represents clash test results.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwClashTestResult : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwClashTestResult);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwClashTestResult object.
  */
  OdNwClashTestResult();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwClashTestResult();

public:
  /** \details
    Returns the description.

    \returns OdString with the description.
  */
  OdString getDescription() const;

  /** \details
    Returns the distance.

    \returns Double precision floating point value for the distance.
  */
  double getDistance() const;

  /** \details
    Returns the first position.

    \returns OdGePoint3d of the first point.
  */
  OdGePoint3d getPoint1() const;

  /** \details
    Returns the second position.

    \returns OdGePoint3d of the second point.
  */
  OdGePoint3d getPoint2() const;

  /** \details
    Returns the bounding box.

    \returns OdGeExtents3d of the bounding box.
  */
  OdGeExtents3d getBoundingBox() const;

  /** \details
    Returns the result status.

    \returns Value specified by the NwClashTestResultStatusType::Enum
    enumeration for the result status.

    \remarks
    Test result status type can be one of the following:

    <table>
    Name                                    Value     Description
    NwClashTestResultStatusType::NEW        0x00      New
    NwClashTestResultStatusType::ACTIVE     0x01      Active
    NwClashTestResultStatusType::APPROVED   0x02      Approved
    NwClashTestResultStatusType::RESOLVED   0x03      Resolved
    NwClashTestResultStatusType::REVIEWED   0x04      Reviewed
    NwClashTestResultStatusType::NUM        0x04      Num
    NwClashTestResultStatusType::UNMERGED   0x100     Unmerged
    </table>
  */
  NwClashTestResultStatusType::Enum getResultStatus() const;

  /** \details
    Returns time when the clash test result was created.

    \returns A tm time structure.
  */
  tm getCreatedTime() const;

  /** \details
    Returns time when the clash test result was approved.

    \returns A tm time structure.
  */
  tm getApprovedTime() const;

  /** \details
    Returns the simulation start time.

    \returns A tm time structure.
  */
  tm getSimulationStartTime() const;

  /** \details
    Returns the simulation end time.

    \returns A tm time structure.
  */
  tm getSimulationEndTime() const;

  /** \details
    Returns the simulation minimal time offset.

    \returns Double value for the minimal time offset.
  */
  double getSimulationMinTimeOffset() const;

  /** \details
    Returns the simulation event name.

    \returns Name of the simulation event.
  */
  OdString getSimulationEventName() const;

  /** \details
    Returns the approver's name.

    \returns Name of the approver.
  */
  OdString getApprovedBy() const;

  /** \details
    Returns the assignee's name.

    \returns Name of the assignee.
  */
  OdString getAssignedTo() const;

  /** \details
    Returns the simulation type.

    \returns OdUInt32 with the type of the simulation.
  */
  OdUInt32 getSimulationType() const;

  /** \details
    Returns the test type.

    \returns Value specified by the NwClashTestType::Enum enumeration for the
    type of the test.

    \remarks
    Test type can be one of the following:

    <table>
    Name                                 Value     Description
    NwClashTestType::HARD                0x00      Hard
    NwClashTestType::HARD_CONSERVATIVE   0x01      Hard (Conservative)
    NwClashTestType::CLEARANCE           0x02      Clearance
    NwClashTestType::DUPLICATES          0x03      Duplicates
    NwClashTestType::CUSTOM              0x04      Custom
    </table>
  */
  NwClashTestType::Enum getTestType() const;

  /** \details
    Returns an object ID of the view point for this test result.

    \returns Object ID of the OdNwViewpoint object with the view point for this
    test result.
  */
  OdNwObjectId getViewPointId() const;

  /** \details
    Gets the array with red lines.

    \param list [out] OdArray with object IDs of OdNwRedLinePtr objects.

    \returns eOk if the operation is successful; appropriate error code
    otherwise.
  */
  OdResult getRedlineList(OdNwObjectIdArray& list) const;

  /** \details
    Returns the object ID of the first model item node for this test result.

    \returns Object ID of the OdNwModelItemPtr object.
  */
  OdNwObjectId getFirstNodeId() const;

  /** \details
    Returns the object ID of the second model item node for this test result.

    \returns Object ID of the OdNwModelItemPtr object.
  */
  OdNwObjectId getSecondNodeId() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwClashTestResult object pointers.
*/
typedef OdSmartPtr<OdNwClashTestResult> OdNwClashTestResultPtr;

#endif // _NW_CLASHTESTRESULT_H_
