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




#ifndef _ODDBLAYOUTMANAGER_INCLUDED_
#define _ODDBLAYOUTMANAGER_INCLUDED_

#include "TD_PackPush.h"

#include "RxObject.h"
#include "DbDatabase.h"
#include "DbLayout.h"

class OdTvDbLayoutManagerImpl;

/** \details
    This class is the base class for custom classes that receive notification
    of OdTvDbLayout events.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbLayoutManagerReactor : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbLayoutManagerReactor);
  /** \details
    Notification function called whenever a layout has been added to an OdTvDbDatabase.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of layout.
    
 	  \remarks
	  This function is called after the operation.
  */
    virtual void layoutCreated(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);
    
  /** \details
    Notification function called whenever a layout is about to be removed from an OdTvDbDatabase.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of layout.
    
 	  \remarks
	  This function is called before the operation.
  */
  virtual void layoutToBeRemoved(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);

  /** \details
    Notification function called whenever a layout has been removed from an OdTvDbDatabase.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called before the operation.
  */
  virtual void layoutRemoved(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);
    
  /** \details
    Notification function called whenever the removal of a layout has been terminated.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called before the operation.
  */
  virtual void abortLayoutRemoved(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);

  /** \details
    Notification function called whenever a layout is about to be copied.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called before the operation.
  */
  virtual void layoutToBeCopied(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);
    
  /** \details
    Notification function called whenever a layout has been copied.
    
    \param oldLayoutName [in]  Old layout name.
    \param oldLayoutId [in]  Object ID of the old layout.
    \param newLayoutName [in]  New layout name.
    \param newLayoutId [in]  Object ID of the new layout.
    
 	  \remarks
	  This function is after the operation.
  */
  virtual void layoutCopied(
    const OdString& oldLayoutName, 
    const OdTvDbObjectId& oldLayoutId,
    const OdString& newLayoutName, 
    const OdTvDbObjectId& newLayoutId);

  /** \details
    Notification function called whenever the copying of a layout has been terminated.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called after the operation.
  */
  virtual void abortLayoutCopied(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);

  /** \details
    Notification function called whenever a layout is about to be renamed.
    
    \param oldLayoutName [in]  Old layout name.
    \param newLayoutName [in]  New layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called before the operation.
  */
  virtual void layoutToBeRenamed(
    const OdString& oldLayoutName,
    const OdString& newLayoutName, 
    const OdTvDbObjectId& layoutId);

  /** \details
    Notification function called whenever a layout has been renamed.
    
    \param oldLayoutName [in]  Old layout name.
    \param newLayoutName [in]  New layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called after the operation.
  */
  virtual void layoutRenamed(
    const OdString& oldLayoutName,
    const OdString& newLayoutName, 
    const OdTvDbObjectId& layoutId);
    
  /** \details
    Notification function called whenever the renaming of a layout has been terminated.
    
    \param oldLayoutName [in]  Old layout name.
    \param newLayoutName [in]  New layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called after the operation.
  */
  virtual void abortLayoutRename(
    const OdString& oldLayoutName,
    const OdString& newLayoutName, 
    const OdTvDbObjectId& layoutId);
    
  /** \details
    Notification function called whenever the active layout has changed.
    
    \param newLayoutName [in]  New layout name.
    \param newLayoutId [in]  Object ID of the new layout.
    
 	  \remarks
	  This function is called after the operation.
  */
  virtual void layoutSwitched(
    const OdString& newLayoutName, 
    const OdTvDbObjectId& newLayoutId);
    
  /** \details
    Notification function called whenever the plot style table associated with a layout has changed.
    
    \param newTableName [in]  New PlotStyleTable name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called after the operation.
  */
  virtual void plotStyleTableChanged(
    const OdString& newTableName, 
    const OdTvDbObjectId& layoutId);

  /** \details
    Notification function called before the active layout gets deactivated.
    
    \param layoutName [in]  Layout name.
    \param layoutId [in]  Object ID of the layout.
    
 	  \remarks
	  This function is called after the operation.
  */
  virtual void layoutToBeDeactivated(
    const OdString& layoutName, 
    const OdTvDbObjectId& layoutId);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbLayoutManagerReactor object pointers. 
*/
typedef OdSmartPtr<OdTvDbLayoutManagerReactor> OdTvDbLayoutManagerReactorPtr;

/** \details
    This class modifies and accesses Layout objects in an OdTvDbDatabase instance.
    
    \sa
    TD_Db
   
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbLayoutManager : public OdRxObject  
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbLayoutManager);

  OdTvDbLayoutManager();
  virtual ~OdTvDbLayoutManager();
  virtual void setCurrentLayout(OdTvDbDatabase* pDb, const OdTvDbObjectId& layoutId);
  virtual OdString findActiveLayout(const OdTvDbDatabase* pDb, bool allowModel) const;
  virtual OdTvDbObjectId getActiveLayoutBTRId(const OdTvDbDatabase* pDb) const;
  virtual OdTvDbObjectId findLayoutNamed(const OdTvDbDatabase* pDb, const OdString& name) const;
  virtual void deleteLayout(OdTvDbDatabase* pDb, const OdString& delname);
  virtual OdTvDbObjectId createLayout(OdTvDbDatabase* pDb, const OdString& newname, OdTvDbObjectId* pBlockTableRecId = 0);
  virtual void renameLayout(OdTvDbDatabase* pDb, const OdString& oldname, const OdString& newname);
  virtual OdTvDbObjectId cloneLayout(OdTvDbDatabase* pDb, const OdTvDbLayout* pLayout, const OdString& newname, int newTabOrder = 0);

  virtual OdTvDbObjectId getNonRectVPIdFromClipId(const OdTvDbObjectId& clipId) const;
  virtual bool isVpnumClipped(const OdTvDbDatabase* pDb, int index) const;
  virtual int countLayouts(const OdTvDbDatabase* pDb) const;
  virtual void addReactor(OdTvDbLayoutManagerReactor * newObj);
  virtual void removeReactor(OdTvDbLayoutManagerReactor * delObj);
private:
  friend class OdTvDbLayoutManagerImpl;
protected:
  OdTvDbLayoutManager(OdTvDbLayoutManagerImpl* pImpl);
  OdTvDbLayoutManagerImpl* m_pImpl;
};

typedef OdSmartPtr<OdTvDbLayoutManager> OdTvDbLayoutManagerPtr;

#include "TD_PackPop.h"

#endif //_ODDBLAYOUTMANAGER_INCLUDED_
