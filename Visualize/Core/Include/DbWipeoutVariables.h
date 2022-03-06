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




#ifndef OD_DBWIPEOUTVARIABLES_H
#define OD_DBWIPEOUTVARIABLES_H

#include "TD_PackPush.h"

#include "DbObject.h"
#include "RxDictionary.h"


#ifdef WIPEOUT_EXPORTS
#define WIPEOUT_EXPORT           OD_TOOLKIT_EXPORT
#define WIPEOUT_EXPORT_STATIC    OD_STATIC_EXPORT
#else
#define WIPEOUT_EXPORT           OD_TOOLKIT_IMPORT
#define WIPEOUT_EXPORT_STATIC    OD_STATIC_IMPORT
#endif



class OdTvDbWipeoutVariables;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbWipeoutVariables object pointers.
*/
typedef OdSmartPtr<OdTvDbWipeoutVariables> OdTvDbWipeoutVariablesPtr;

/** \details
    Represents the Wipeout Variables object in an OdTvDbDatabase instance.
    
    Corresponding C++ library: WipeOut
  
    <group OdTvDb_Classes>
*/
class WIPEOUT_EXPORT OdTvDbWipeoutVariables : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbWipeoutVariables);

  OdTvDbWipeoutVariables();

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** \details
    Returns the frame display flag for this Variables object (DXF 70).
  */
  virtual bool showFrame() const;

  /** \details
    Sets the frame display flag for this Variables object (DXF 70).
    \param showFrame [in]  Controls frame visibility
    \param bUpdateWIPEOUTFRAME [in]  Controls if WIPEOUTFRAME system variable is also updated.

    \remarks
    WIPEOUTFRAME was introduced in 2013 file format and should be used to control
    frame visiblity. bUpdateWIPEOUTFRAME argument added to keep existing code working.
  */
  virtual void setShowFrame(bool showFrame, bool bUpdateWIPEOUTFRAME = true);

  /** \details
    Opens the Wipeout Variables object in the specified database.
    \param openMode [in]  Mode in which to open the wipeout variables object.
    \param pDb [in]  Pointer to the database that contains the wipeout variables object.

    \remarks
    If the Wipeout Variables object does not exist in the specified database
    it is created.
    
    Returns a SmartPointer to the Wipeout Variables object.
  */
  static OdTvDbWipeoutVariablesPtr openWipeoutVariables(OdTvDbDatabase* pDb,
    OdDb::OpenMode openMode = OdDb::kForRead);
};


inline OdTvDbWipeoutVariablesPtr OdTvDbWipeoutVariables::openWipeoutVariables(OdTvDbDatabase* pDatabase, OdDb::OpenMode mode) {
  OdTvDbWipeoutVariablesPtr pWpVars;
  ODA_ASSERT(pDatabase);
  if (pDatabase) {
    OdTvDbDictionaryPtr pRootDict = pDatabase->getNamedObjectsDictionaryId().openObject();
    OdString AcTvDbWipeoutVariables(L"AcTvDbWipeoutVariables");
    pWpVars = ::odrxCastByClassName<OdTvDbWipeoutVariables>(pRootDict->getAt(TV_ACAD_WIPEOUT_VARS).openObject(mode), AcTvDbWipeoutVariables);
    if (pWpVars.isNull() && mode == OdDb::kForWrite) {
      pRootDict->upgradeOpen();
      pWpVars = ::odrxSafeCreateObject<OdTvDbWipeoutVariables>(AcTvDbWipeoutVariables);
      pRootDict->setAt(TV_ACAD_WIPEOUT_VARS, pWpVars);
    }
  }
  return pWpVars;
}


#include "TD_PackPop.h"

#endif //OD_DBWIPEOUTVARIABLES_H

