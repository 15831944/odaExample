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

#ifndef __TNW_FILEINFO_H__
#define __TNW_FILEINFO_H__

#include "NwSavedGroupItem.h"

/** \details
  This class represents saved viewpoint animations.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwFileInfo : public OdNwSavedGroupItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwFileInfo);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwFileInfo class.
  */
  OdNwFileInfo();

public:
  
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwFileInfo();

public:
  /** \details
    Returns the index of the sheet by Id.

    \returns Returns the index of the sheet by Id. On fail it returns -1.
  */
  OdInt32 getIndexOfSheetId(const OdString& sheetId) const;
  /** \details
    Returns the id of current sheet.

    \returns Returns OdString representation of current sheet.
  */
  OdString getCurrentSheet() const;
  /** \details
    Returns source GUID for the document.

    \returns Returns OdGUID object for source GUID of the document.
  */
  OdGUID getSourceGuid() const;
};

typedef OdSmartPtr<OdNwFileInfo> OdNwFileInfoPtr;

#endif //__TNW_FILEINFO_H__
