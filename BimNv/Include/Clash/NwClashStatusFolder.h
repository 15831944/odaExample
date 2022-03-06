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

#ifndef _NW_CLASHSTATUSFOLDER_H_
#define _NW_CLASHSTATUSFOLDER_H_
#include "NwSavedFolderItem.h"

/** \details
  This class represents a folder for clash status objects.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwClashStatusFolder : public OdNwSavedFolderItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwClashStatusFolder);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwClashStatusFolder object.
  */
  OdNwClashStatusFolder();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwClashStatusFolder();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwClashStatusFolder object pointers.
*/
typedef OdSmartPtr<OdNwClashStatusFolder> OdNwClashStatusFolderPtr;

#endif // _NW_CLASHSTATUSFOLDER_H_
