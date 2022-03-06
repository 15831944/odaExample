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

#ifndef _DbBlockElement_h_Included_
#define _DbBlockElement_h_Included_

#include "DbEvalGraph.h"
#include "IntArray.h"
#include "Ge/GePoint3dArray.h"

class OdTvDbBlockTableRecord;
class OdTvDbBlockRepresentationContext;

#define ODDB_EVAL_DECLARE_MEMBERS(ClassName) \
  ODDB_DECLARE_MEMBERS(ClassName);\
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);\
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;\
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);\
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const

// #define DEBUG_EVALGRAPH 1

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockElement : public OdTvDbEvalConnectable
{
public:
  enum HistoryCompression{kHistoryCompression0,kHistoryCompression1,kHistoryCompression2,kHistoryCompression3};
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockElement);
  //!DOM EvalExpr interface
  //!DOM virtual void adjacentNodeRemoved( const OdTvDbEvalNodeId& );
  virtual bool evaluate( const OdTvDbEvalContext* );
  //!DOM OdTvDbEvalConnectable interface
  virtual bool connectionAllowed(const OdString&,OdTvDbEvalNodeId,const OdString&) const;
  virtual bool connectTo(const OdString&,OdTvDbEvalNodeId,const OdString&);
  virtual bool disconnectFrom(const OdString&,OdTvDbEvalNodeId,const OdString&);
  virtual bool hasConnectionNamed(const OdString&) const;
  virtual bool getConnectedNames(const OdString&,unsigned long,OdStringArray&) const;
  virtual bool getConnectedObjects(const OdString&,OdTvDbEvalNodeIdArray&) const;
  virtual void getConnectionNames(OdStringArray&) const;
  virtual bool getConnectionType  (const OdString& name, OdTvResBuf::ValueType& type) const;
  virtual OdTvResBufPtr getConnectionValue (const OdString& name) const;
  //!DOM  
  virtual OdString name() const;
  virtual void setName( const OdString& );
  //!DOM virtual unsigned long alertState() const;
  //!DOM virtual void auditAlertState();
  //!DOM OdTvDbObjectId getEntity();
  //!DOM class AcRxClass * getRxEntity(void)
  virtual OdDb::MaintReleaseVer getInstanceMaintenanceVersion();
  virtual OdDb::DwgVersion  getInstanceVersion();
  virtual void getStretchPoints( OdGePoint3dArray& )const;
  virtual void moveStretchPointsAt( const OdIntArray &, const OdGeVector3d &);
  virtual HistoryCompression historyCompression() const;
  virtual bool historyRequired() const;
  //!DOM static bool isNameUnique(class OdTvDbEvalGraph* graph, const OdString& name, OdString* result );
  virtual bool hasInstanceData()const; // has instance data loaded
  virtual bool loadInstanceData(const OdTvResBuf*, bool bRequireEvaluate = false); // loads instance data from xdata chain
  virtual OdTvResBufPtr saveInstanceData()const; // saves instance data to xdata chain
  virtual void updateConnections();
  //!DOM virtual bool onBeginEdit( OdTvDbBlockTableRecord* );
  //!DOM virtual bool onEndEdit(OdTvDbBlockTableRecord*);
    /*!DOM 
  void OnBeginEditCancelled(class AcTvDbObjectId,class AcTvDbObjectId)
  void OnBeginEditEnded(class AcTvDbObjectId,class AcTvDbObjectId)
  void OnBeginSaveCancelled(class AcTvDbObjectId,class AcTvDbObjectId)
  void OnBeginSaveEnded(class AcTvDbObjectId,class AcTvDbObjectId)
  void OnBeginSaveStarted(class AcTvDbObjectId,class AcTvDbObjectId)
  void OnEndEditCancelled(class AcTvDbObjectId,class AcTvDbObjectId)
  void OnEndEditStarted(class AcTvDbObjectId,class AcTvDbObjectId)
  */
  virtual bool isMemberOfCurrentVisibilitySet()const;
  virtual void setMemberOfCurrentVisibilitySet(bool);
  //!DOM   enum Acad::ErrorStatus  AcTvDbBlockElement::sync(class AcTvDbBlockElementEntity *)
  //!DOM  virtual void transformDefinitionBy( const OdGeMatrix3d &);
  virtual OdResult transformBy( const OdGeMatrix3d& );
};
typedef OdSmartPtr<OdTvDbBlockElement>OdTvDbBlockElementPtr;

#endif // _DbBlockElement_h_Included_
