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
//
// OdqPropTab.h
//

#ifndef ODA_QT_PROP_TAB_H_
#define ODA_QT_PROP_TAB_H_

#include <QWidget> // <QObject>
//QT_BEGIN_NAMESPACE
//  class QDialog;
//  //class QScrollBar;
//QT_END_NAMESPACE

#include "OdaCommon.h"
#include "SharedPtr.h"

#include "OdqInterfaces.h"
#include "PropSourcesImpl.h"

//////////////////////////////////////////////////////////////////////////

class OdqPropTab : public QWidget
{
  Q_OBJECT

  OdqPropTab(QWidget* pParent, 
             OdEdCommandContext* pCtx);
  friend class OdqPropSystem; 
  
  void init();
public:
  void uninit();
  bool isInitialized() const;

  virtual ~OdqPropTab();

  // -----

  OdRxObject* getRxDatabase();
  class OdPropServices* propServices();

  void update(OdPropSource* pSourceOnly = NULL, // NULL - all if changed
              bool bRecreateWidgets = true,
              bool bForce = false); // true - to ignore unchanged state
  ObjectPropSourceImpl* getObjectSource();
  void setModalDialogObjectSourceToSet(ObjectPropSourceImpl* pObjectSource);

  ODGSPALETTE& cacheColors() const; // for color palette via ExtDb

private:
  OdEdCommandContext* m_pCtx;
  OdString m_sDlgKey; 

  OdSharedPtr<ToolPropSourceImpl> m_pToolSource;
  OdSharedPtr<EntityPropSourceImpl> m_pEntitySource;
  ObjectPropSourceImpl* m_pModalDialogObjectSourceToSet;

  mutable OdSharedPtr<ODGSPALETTE> m_pCacheColors;
};

#endif // ODA_QT_PROP_TAB_H_
