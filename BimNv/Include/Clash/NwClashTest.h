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

#ifndef _NW_CLASHTEST_H_
#define _NW_CLASHTEST_H_
#include "NwSavedItem.h"
#include "Clash/NwClashTypes.h"

/** \details
  This class represents clash test objects with all parameters and test results.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwClashTest : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwClashTest);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwClashTest object.
  */
  OdNwClashTest();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwClashTest();

  /** \details
    Returns the type of clash test.

    \returns Value, specified by the NwClashTestType::Enum enumeration.

    \remarks
    Test type can be one of the following:

    <table>
    Name                                 Value   Description
    NwClashTestType::HARD                0x00    Hard
    NwClashTestType::HARD_CONSERVATIVE   0x01    Hard (Conservative)
    NwClashTestType::CLEARANCE           0x02    Clearance
    NwClashTestType::DUPLICATES          0x03    Duplicates
    NwClashTestType::CUSTOM              0x04    Custom
    </table>
  */
  NwClashTestType::Enum getTestType() const;
  /** \details
    Returns the clash test status.

    \returns Value, specified by the NwClashTestStatusType::Enum enumeration.

    \remarks
    Test status type can be one of the following:

    <table>
    Name                             Value   Description
    NwClashTestStatusType::NEW       0x00    New
    NwClashTestStatusType::OLD       0x01    Old
    NwClashTestStatusType::PARTIAL   0x02    Partial
    NwClashTestStatusType::OK        0x03    Ok
    </table>
  */
  NwClashTestStatusType::Enum getStatus() const;

  /** \details
    Returns the type of simulation for the clash test.

    \returns OdInt32 value.
  */
  OdInt32 getSimulationType() const;

  /** \details
    Returns the relative touch tolerance flag for the clash test.

    \returns True if the touch tolerance is relative.
  */
  bool getIsRelativeTouchTolerance() const;

  /** \details
    Returns the relative touch tolerance value for the clash test.

    \returns Floating point value with double precision.
  */
  double getRelativeTouchTolerance() const;

  /** \details
    Returns the absolute touch tolerance value for the clash test.

    \returns Floating point value with double precision.
  */
  double getAbsoluteTouchTolerance() const;

  /** \details
    Returns the tolerance value for the clash test.

    \returns Floating point value with double precision.
  */
  double getTolerance() const;

  /** \details
    Returns the simulation step value for the clash test.

    \returns Floating point value  with double precision.
  */
  double getSimulationStep() const;

  /** \details
    Returns the time of the last run for this test.

    \returns The tm time structure.
  */
  tm getLastRunTime() const;

  /** \details
    Returns the composites merging flag.

    \returns True if the merge of composites is required.
  */
  bool getMergeComposites() const;

  /** \details
    Returns the ID of clash test results.

    \returns OdNwObjectId of OdNwSavedItemsElementPtr object which contains a
    list of OdNwClashTestResults objects.
  */
  OdNwObjectId getTestResultsId() const;

  /** \details
    Returns the list of clash test rules.

    \returns List of OdNwObjectId of OdNwRulePtr objects which contain a list of
    OdNwRulePtr objects.
  */
  OdNwObjectIdArray getRules() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwClashTest object pointers.
*/
typedef OdSmartPtr<OdNwClashTest> OdNwClashTestPtr;

#endif // _NW_CLASHTEST_H_
