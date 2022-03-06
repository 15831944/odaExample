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

#ifndef _DbBlockRepresentation_h_Included_
#define _DbBlockRepresentation_h_Included_

#include "TD_PackPush.h"

#include "RxObjectImpl.h"
#include "DbBlockReference.h"
#include "DbEvalGraph.h"
#define STL_USING_MAP
#include "OdaSTL.h"

class OdTvDbBlockParameter;
class OdTvDbDynBlockReference;
class OdTvDbAttributeDefinition;
class OdTvDbAttribute;

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockRepresentationContext : public OdRxObject
{
  OdTvDbObjectId m_pDynamicBlock;
  OdTvDbObjectId m_pAnonymousBlock;
  OdTvDbObjectId m_pBlockData;
  OdTvDbObjectId m_pRef;
  OdTvDbObjectId m_pGraph;
  OdTvDbBlockReference* m_pNDBROBlockRef;
  OdTvDbEvalGraphPtr m_NDBRO_Graph;
  bool m_bBlockUpdateMode;
  void eraseOldArrayClones();
  void updateAttributeMap();
  bool m_bNDBROAttributes;
  std::map<OdTvDbAttributeDefinition*, void*> m_pAttributeMap;
  void updateCachedData(OdTvDbBlockReference* ref);
public:
  OdTvDbBlockRepresentationContext();
  ~OdTvDbBlockRepresentationContext();
  void init(const OdTvDbDynBlockReference* ref, OdTvDbBlockReference* dbref, OdTvDbEvalGraph* gr, bool bRequireEvaluate = false, bool loadIndstanceData = true);
  void loadInstanceData(bool bRequireEvaluate = false);
  void compactRepresentation();
  bool originalPathToRepresentationPath(const OdTvDbObjectIdArray&, OdTvDbEntityPtrArray& res)const;
  bool representationPathToOriginalPath(OdTvDbObjectIdArray&)const;
  // set RepBTag on representation block
  static void tagBlockRecord(OdTvDbBlockTableRecord* repBTR, const OdDbHandle& originalBlockHandle);
  // remove dynamic block related xdata && xdictionary entries
  static void clearRepBlock(OdTvDbBlockTableRecord* repRTR);
  // create representation block for the insert
  void createRepresentation(bool copied = true);
  void addHistoryRecord(const OdString& name, const OdTvResBuf* value, OdTvDbEvalNodeId node);
  // 
  OdTvDbXrecordPtr getHistoryRecord() const;
  // update parameter value from the history record
  bool applyHistory(OdTvResBufPtr pRb);
  // check if instance data records contain the same parameters values as in actual graph (used to verify updateAnonymousBlocks result)
  bool compareInstanceData() const;
  void updateRepresentation();
  OdTvDbObjectId getRepresentation() const { return m_pAnonymousBlock.isErased() ? OdTvDbObjectId::kNull : m_pAnonymousBlock; }
  OdTvDbObjectId getOriginal() const { return m_pDynamicBlock; }
  OdTvDbEvalExprPtr getRepresentationNode(OdTvDbEvalNodeId id);
  OdTvDbBlockReferencePtr getReference();
  OdTvDbEvalGraphPtr getGraph()
  {
    return m_NDBRO_Graph;
  }
  OdTvDbBlockTableRecordPtr getBlock();
  void writeUndo(OdTvDbEvalGraph* gr);
  void readUndo(OdTvDbObjectId refId, OdTvDbDwgFiler* pFiler);
  static OdTvDbBlockRepresentationContext* getRepresentationContext(OdTvDbBlockReference* br);
  OdTvDbAttributePtr getAttribute(OdTvDbAttributeDefinition*);
  OdGeMatrix3d getRelativeMatrix(const OdGeMatrix3d& m);
  OdGeVector3d getRelativeOffset(const OdGeVector3d& v);
  OdTvDbObjectId getBlockData() const { return m_pBlockData; }
  void setBlockUpdateMode(bool b) { m_bBlockUpdateMode = b; }
  bool blockUpdateMode() const { return m_bBlockUpdateMode; }
};

#include "TD_PackPop.h"

#endif // _DbBlockRepresentation_h_Included_
