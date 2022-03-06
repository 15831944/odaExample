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

#ifndef __TNW_SHEETINFO_H__
#define __TNW_SHEETINFO_H__

#include "NwSavedItem.h"
#include "NwSheetType.h"

/** \details
  This class represents saved viewpoint animations.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSheetInfo : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSheetInfo);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor.
  */
  OdNwSheetInfo();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSheetInfo();

public:

  /** \details
    Returns the sheet ID of this sheet.

    \returns Returns string value with the ID of this sheet.
  */
  OdString getSheetId() const;

  /** \details
    Returns the sheet type of this sheet.

    \remarks
    getSheetType() Returns one of the following:

    <table>
    Name                           Value   Description
    NwSheetType::Sheet3d           0x00    3D type of sheet
    NwSheetType::Sheet2d           0x01    2D type of sheet
    </table>
  */
  NwSheetType::Enum getSheetType() const;

  /** \details
    Returns the readiness status of the sheet for loading.

    \returns Returns a boolean value with the readiness status of the sheet: true if the sheet is ready for loading, false if the sheet contains only reference information to the file.
  */
  bool isEnabled() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSheetInfo object pointers.
*/
typedef OdSmartPtr<OdNwSheetInfo> OdNwSheetInfoPtr;

#endif //__TNW_SHEETINFO_H__
