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

#ifndef _PRCMODELFILEDATA_INCLUDED_
#define _PRCMODELFILEDATA_INCLUDED_ 
 

#include "PrcUnit.h"
#include "PrcUserData.h"
#include "PrcBase.h"
#include "PrcProductOccurrence.h"

SMARTPTR(OdPrcModelFileData);
class OdPrcFile;

typedef OdPrcObjectId OdPrcProductOccurrenceReference;
typedef OdArray<OdPrcProductOccurrenceReference> OdPrcProductOccurrenceReferenceArray;

/** \details 
<group PRC_Files_Structures_Assemblies> 

Class stores information about imported data from a CAD file.
*/
class PRC_TOOLKIT OdPrcModelFileData : public OdPrcBase
{
  friend class OdPrcFile;

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcModelFileData);
  //DOM-IGNORE-END

  /** \details
  Returns the current unit for the model.
  The unit is returned as a reference to an OdPrcUnit object, therefore it can be used to set a new unit for the model file.
  */
  OdPrcUnit &unit();
  
  /** \details
  Returns the current unit for the model.
  */
  const OdPrcUnit &unit() const;
  
  /** \details
  Returns current user defined data.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();
  
  /** \details
  Returns current user defined data.
  */
  const OdPrcUserData &userData() const;

  /** \details
  Clears the current list of product occurrences.
  */
  void clearRoots(void);

  /** \details
  Adds a new start root occurrence to the end of the occurrences list.

  \param pPO [in] A new start root occurrence to be set.
  */
  void addStartRootOccurrence(const OdPrcProductOccurrence &pPO);

  /** \details
  Returns the current list of product occurrences.
  The product occurrences list is returned as a reference to an OdPrcProductOccurrenceReferenceArray object, therefore it can be used to add new product occurrences.
  */
  OdPrcProductOccurrenceReferenceArray& getStartRootOccurrences(void);

  /** \details
  Returns the current list of product occurrences.
  */
  const OdPrcProductOccurrenceReferenceArray& getStartRootOccurrences(void) const;

protected:
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
};

#endif // _PRCMODELFILEDATA_INCLUDED_

