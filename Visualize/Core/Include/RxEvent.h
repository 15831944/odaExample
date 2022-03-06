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




#ifndef   _ODRX_EVENT_H__
#define   _ODRX_EVENT_H__

#include "TD_PackPush.h"

#include "RxObject.h"
#include "IdArrays.h"
#include "StringArray.h"

#define ODRX_EVENT_OBJ OD_T("OdTvRxEvent")

class OdTvDbDatabase;
class OdGeMatrix3d;
class OdTvDbIdMapping;
class OdGePoint3d;
class OdTvDbObjectId;

enum OdXrefSubCommand
{
  kXrefAttach = 0,
  kXrefBind = 1,
  kXrefDetach = 2,
  kXrefOverlay = 3,
  kXrefPath = 4,
  kXrefReload = 5,
  kXrefResolve = 6,
  kXrefUnload = 7,
  kXrefXBind = 8
};

/** \details
    This class is the base class for custom classes that receive notification
    of OdTvRxEvent (application level) events.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    \sa
    TD_Db
  
    <group OdRx_Classes> 
*/
class TOOLKIT_EXPORT OdTvRxEventReactor : public OdRxObject 
{ 
public:
  ODRX_DECLARE_MEMBERS(OdTvRxEventReactor);
  
  /** \details
    Notification function called whenever a .dwg file is being read.
    
    \param pDb [in]  Pointer to the database being created.
    \param filename [in]  Name of the .dwg file.
    
    \remarks
    This function is called during the operation.
    
    \sa
    * databaseConstructed
    * initialDwgFileOpenComplete
  */
  virtual void dwgFileOpened(
    OdTvDbDatabase* pDb, 
    const OdString& filename);
    
  /** \details
    Notification function called whenever a .dwg file has been read.
    
    \param pDb [in]  Pointer to the database being created.
    
    \remarks
    This function is called after the read operation, but before the database is constructed.
    
    \sa
    * databaseConstructed
    * dwgFileOpened
  */
  virtual void initialDwgFileOpenComplete(
    OdTvDbDatabase* pDb);
    
  /** \details
    Notification function called whenever a database has been constructed from a file.
    
    \param pDb [in]  Pointer to the database constructed.
    
    \remarks
    This function is called after the operation.
    
    \sa
    * dwgFileOpened
    * initialDwgFileOpenComplete
  */
  virtual void databaseConstructed(
    OdTvDbDatabase* pDb);

  /** \details
    Notification function called whenever a database is about to be deleted from memory.  

    \param pDb [in]  Pointer to the database to be destroyed.
    
    \remarks
    This function is called before the operation.
  */
  virtual void databaseToBeDestroyed(
    OdTvDbDatabase* pDb);
  
  /** \details
    Notification function called whenever a database is about to be saved to a .dwg file.
    
    \param pDb [in]  Pointer to the database to be saved.
    \param intendedName [in]  Intended name of the .dwg file.
    
    \remarks
    This function is called before the operation, and before the user 
    has had a chance to modify the filename. The file may not have the intendedName.
    
    \sa
    * abortSave
    * saveComplete
  */
  virtual void beginSave(
    OdTvDbDatabase* pDb, 
    const OdString& intendedName);

  /** \details
    Notification function called whenever a database has been saved 
    to a .dwg file.
    
    \param pDb [in]  Pointer to the database saved.
    \param actualName [in]  Actual name of the .dwg file.
    
    \remarks
    This function is called after the operation, but before the database is constructed.
    
    \sa
    * abortSave
    * beginSave
  */
  virtual void saveComplete(
    OdTvDbDatabase* pDb, 
    const OdString& actualName);
    
  /** \details
    Notification function called whenever the save of a database has failed.
    
    \param pDb [in]  Pointer to the database being saved.
    
    \remarks
    This function is called after the operation.

    \sa
    * beginSave
    * saveComplete
  */
  virtual void abortSave(
    OdTvDbDatabase* pDb);
  
  // DXF In/Out Events.

  /** \details
    Notification function called whenever a database is about to be modified by a DXF input operation.
    
    \param pDb [in]  Pointer to the database to be modified.
    
    \remarks
    This function is called before the operation.
    
    \sa
    * abortDxfIn
    * dxfInComplete
  */
  virtual void beginDxfIn(
    OdTvDbDatabase* pDb);
    
  /** \details
    Notification function called whenever the DXF input to a database has failed.
    
    \param pDb [in]  Pointer to the database being modified.
    
    \remarks
    This function is called after the operation.
        
    \sa
    * beginDxfIn
    * dxfInComplete
  */
  virtual void abortDxfIn(
    OdTvDbDatabase* pDb);
 
  /** \details
    Notification function called whenever a database has been modified by a DXF input operation.
    
    \param pDb [in]  Pointer to the database modified.
    
    \remarks
    This function is called after the operation.
    
    \sa
    * abortDxfIn
    * beginDxfIn
  */
   virtual void dxfInComplete(
    OdTvDbDatabase* pDb);


  /** \details
    Notification function called whenever a database is about to be saved to a DXF file.
    
    \param pDb [in]  Pointer to the database to be saved.
    
    \remarks
    This function is called before the operation
    
    \sa
    * abortDxfOut
    * dxfOutComplete
  */
  virtual void beginDxfOut(
    OdTvDbDatabase* pDb);
    
    
  /** \details
    Notification function called whenever the DXF output from a database has failed.
    
    \param pDb [in]  Pointer to the database being saved.
    
    \remarks
    This function is called after the operation.
        
    \sa
    beginDxfOut
    dxfOutComplete
  */
  virtual void abortDxfOut(
    OdTvDbDatabase* pDb);
    
    
  /** \details
    Notification function called whenever a database has be saved to a DXF file.
       
    \param pDb [in]  Pointer to the database saved.
    
    \remarks
    This function is called after the operation.
    
    \sa
    * abortDxfOut
    * beginDxfOut
  */
  virtual void dxfOutComplete(
    OdTvDbDatabase* pDb);
  
  // Insert Events.
  
  /** \details
    Notification function called whenever one database is about to be inserted into another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    \param blockName [in]  Name of the block.
    
    \remarks
    This function is called before the operation.
    
    \remarks
    If blockName is specified, pFromDb was inserted into pToDb as a OdTvDbBlockTableRecord.
    
    \sa
    * abortInsert
    * endInsert
    * otherInsert
  */
  virtual void beginInsert(
    OdTvDbDatabase* pToDb, 
    const OdString& blockName, 
    OdTvDbDatabase* pFromDb);
    
  /** \details
    Notification function called whenever one database is about to be inserted into another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    \param xfm [in]  Transformation matrix.
    
    \remarks
    This function is called before the operation.
    
    \remarks
    If xfm is specified, pFromDb was inserted into pToDb as entities.
    
    \sa
    * abortInsert
    * endInsert
    * otherInsert
  */
  virtual void beginInsert(
    OdTvDbDatabase* pToDb, 
    const OdGeMatrix3d& xfm, 
    OdTvDbDatabase* pFromDb);
    
  /** \details
    Notification function called whenever one database has been inserted into another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    This function is called after the operation, and is sent just before 
    beginDeepCloneXlation. It is called before any Object IDs are translated.
    
    \remarks
    Object IDs of cloned objects do not point at the cloned objects, and
    must therefore not not be used at this point for any operations on
    those objects.
    
    \sa
    * abortInsert
    * beginInsert
    * endInsert
  */
  virtual void otherInsert(
    OdTvDbDatabase* pToDb, 
    OdTvDbIdMapping& idMap, 
    OdTvDbDatabase* pFromDb);
    
  /** \details
    Notification function called whenever the insertion of a database has failed.
    
    \param pToDb [in]  Destination database.
    
    \remarks
    This function is called after the operation.
        
    \sa
    * beginInsert
    * endInsert
    * otherInsert
  */
  virtual void abortInsert(
    OdTvDbDatabase* pToDb);
    
  /** \details
    Notification function called whenever the insertion of a database has succeeded.
    
    \param pToDb [in]  Destination database.
    
    \remarks
    This function is called after the operation.
        
    \sa
    * abortInsert
    * beginInsert
    * otherInsert
  */
  virtual void endInsert(
    OdTvDbDatabase* pToDb);
  
  // Wblock Events.

  /** \details
    Notification function called while one database is about to be wblocked to another.
    
    \param pFromDb [in]  Source database.
  */
  virtual void wblockNotice(
    OdTvDbDatabase* pFromDb);
  
  /** \details
    Notification function called while one database is being wblocked to another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    \param insertionPoint [in]  INSBASE of pToDb.
    
    \remarks
    This function is called during the operation.
    
    If insertionPoint is specified, the wblock operation is being performed on a set
    of entities in pFromDb.
    
    \sa
    * abortWblock
    * beginWblockObjects
    * endWblock
    * otherWblock
    * wblockNotice
  */
  virtual void beginWblock(
    OdTvDbDatabase* pToDb, 
    OdTvDbDatabase* pFromDb, 
    const OdGePoint3d& insertionPoint);
    
  /** \details
    Notification function called while one database is being wblocked to another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    \param blockId [in]  Object ID of OdTvDbBlockTableRecord being wblocked.
    
    \remarks
    This function is called during the operation.
    
    If blockId is specified, the wblock operation is being performed on a 
    BlockTableRecord in pFromDb.
    
    \sa
    * abortWblock
    * beginWblockObjects
    * endWblock
    * otherWblock
    * wblockNotice
  */
  virtual void beginWblock(
    OdTvDbDatabase* pToDb, 
    OdTvDbDatabase* pFromDb, 
    OdTvDbObjectId blockId);
    
  /** \details
    Notification function called while one database is being wblocked to another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    
    \remarks
    This function is called during the operation.
    
    The entire pFromDb database is wblocked to pToDb.  
    
    \sa
    * abortWblock
    * beginWblockObjects
    * endWblock
    * otherWblock
    * wblockNotice
  */
  virtual void beginWblock(
    OdTvDbDatabase* pToDb, 
    OdTvDbDatabase* pFromDb);

     
  /** \details
    Notification function called whenever one database is being wblocked to another.
    
    \param pToDb [in]  Destination database.
    \param pFromDb [in]  Source database.
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    idMap contains mapping of the original objects in pFromDb to the objects created in pToDb.

    This function is called after the operation, and is sent just before 
    beginDeepCloneXlation.
    
    \sa
    * abortWblock
    * beginWblock
    * beginWblockObjects
    * endWblock
    * wblockNotice
  */
  virtual void otherWblock(
    OdTvDbDatabase* pToDb, 
    OdTvDbIdMapping& idMap, 
    OdTvDbDatabase* pFromDb);
    
  /** \details
    Notification function called whenever the wblock of a database has failed.
    
    \param pToDb [in]  Destination database.
    
    \remarks
    This function is called after the operation.
        
    \sa
    beginWblock
    beginWblockObjects
    endWblock
    otherWblock
    wblockNotice
  */
  virtual void abortWblock(
    OdTvDbDatabase* pToDb);
    
  /** \details
    Notification function called whenever the wblock of a database has succeded.
    
    \param pToDb [in]  Destination database.
    
    \remarks
    This function is called after the operation.
        
    \sa
    * abortWblock
    * beginWblock
    * beginWblockObjects
    * otherWblock
    * wblockNotice
  */
  virtual void endWblock(
    OdTvDbDatabase* pToDb);
    
  /** \details
    Notification function called whenever one database is being wblocked to another.
    
    \param pFromDb [in]  Source database.
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    idMap contains mapping of the original objects in pFromDb to the objects created in pToDb.

    This notification function gives wblockCloneObjects a method
    of being notified before each pFrom database before the actual cloning begins.
    
    \sa
    * abortWblock
    * beginWblock
    * endWblock
    * otherWblock
    * wblockNotice
  */
  virtual void beginWblockObjects(
    OdTvDbDatabase* pFromDb, 
    OdTvDbIdMapping& idMap);
  
  // Deep Clone Events.
  
  /** \details
    Notification function called whenever a subDeepClone operation is about to be started on a database.
    
    \param pToDb [in]  Destination database.
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    idMap will always be empty.

    \sa
    * abortDeepClone
    * beginDeepCloneXlation
    * endDeepClone
  */
  virtual void beginDeepClone(
    OdTvDbDatabase* pToDb, 
    OdTvDbIdMapping& idMap);

  /** \details
    Notification function called whenever a the translation stage of a subDeepClone 
    operation is about to be started on a database.
    
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    This function is called after all objects, and their owned objects, have been cloned.
    It is called before any Object IDs are translated 
    
    \remarks
    Object IDs of cloned objects do not point at the cloned objects, and
    must therefore not not be used at this point for any operations on
    those objects.
    
    \sa
    * abortDeepClone
    * beginDeepClone
    * endDeepClone
  */
  virtual void beginDeepCloneXlation(
    OdTvDbIdMapping& idMap);

  /** \details
    Notification function called whenever a subDeepClone operation has failed.
    
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    This function is called after the operation.
   
    \remarks
    The objects involved in the subDeepClone operation are in an indeterminate state 
    and must be cleaned up.
   
    \sa
    * beginDeepClone
    * beginDeepCloneXlation
    * endDeepClone
  */
  virtual void abortDeepClone(
    OdTvDbIdMapping& idMap);

  /** \details
    Notification function called whenever a subDeepClone operation has succeeded.
    
    \param idMap [in]  ID Map source -> destination.
    
    \remarks
    This function is called after the operation.
   
    \sa
    * abortDeepClone
    * beginDeepClone
    * beginDeepCloneXlation
  */
  virtual void endDeepClone(
    OdTvDbIdMapping& idMap);
  
  // Partial Open Events.
  
  /** \details
    Notification function called before an attempt is made to partially open an OdTvDbDatabase.

    \param pDb [in]  Pointer to the database.
    
    \remarks
    To 
    veto the partial open, an application should override partialOpenNotice, and from it call
    
                pDb->disablePartialOpen()
    
  */
  virtual void partialOpenNotice(
    OdTvDbDatabase* pDb);
  
  virtual void xrefSubCommandStart(
    OdTvDbDatabase* pHostDb,
    OdXrefSubCommand subCmd,
    const OdTvDbObjectIdArray& btrIds,
    const OdStringArray& btrNames,
    const OdStringArray& paths,
    bool& vetoOp);

  virtual void xrefSubCommandEnd(
    OdTvDbDatabase* pHostDb,
    OdXrefSubCommand subCmd,
    const OdTvDbObjectIdArray& btrIds,
    const OdStringArray& btrNames,
    const OdStringArray& paths);

  virtual void xrefSubCommandAborted(
    OdTvDbDatabase* pHostDb,
    OdXrefSubCommand subCmd,
    const OdTvDbObjectIdArray& btrIds,
    const OdStringArray& btrNames,
    const OdStringArray& paths);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvRxEventReactor object pointers.
*/
typedef OdSmartPtr<OdTvRxEventReactor> OdRxEventReactorPtr;

/** \details
    This class manages OdTvRxEventReactor instances.
    
    \sa
    TD_Db
    <group OdRx_Classes> 
*/
class TOOLKIT_EXPORT OdTvRxEvent : public OdRxObject 
{ 
public:
  ODRX_DECLARE_MEMBERS(OdTvRxEvent);
  
  /** \details
    Adds the specified event reactor to the host application's event reactor list.
    \param pReactor [in]  Pointer to the event reactor.
  */
  virtual void addReactor(
    OdTvRxEventReactor* pReactor) = 0;

  /** \details
    Removes the specified event reactor from the host application's event reactor list.
    \param pReactor [in]  Pointer to the event reactor.
  */
  virtual void removeReactor(
    OdTvRxEventReactor* pReactor) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvRxEvent object pointers.
*/
typedef OdSmartPtr<OdTvRxEvent> OdRxEventPtr;


TOOLKIT_EXPORT OdRxEventPtr odtvrxEvent();

#include "TD_PackPop.h"

#endif //_ODRX_EVENT_H__

