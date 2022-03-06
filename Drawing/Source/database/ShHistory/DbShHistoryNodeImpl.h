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

#ifndef _OD_DB_SHHISTORYNODE_IMPL_
#define _OD_DB_SHHISTORYNODE_IMPL_

#include <ShHistory/DbShHistoryNode.h>
#include "../DynBlocks/DbEvalGraphImpl.h"
#include "../Entities/DbModelerGeometryImpl.h"

class OdDbShHistoryNodeImpl : public OdDbEvalExprImpl
{
  OdCmColor   m_color;
  OdInt32     m_iStepId; //It depend on OdDbPersSubentManager. 
  //OdDbShBoolean - always 0
  OdDbObjectId m_materialId;
  OdModelerGeometryPtr m_Model; //acis model
  bool        m_bValidate;      //after modification (node transformaion) sets to true.
  friend class OdDbShHistoryNode;
protected:
  OdInt32 m_nVersionMajor;
  OdInt32 m_nVersionMinor;
  OdGeMatrix3d m_matrix;
  double getScaleAndTransformBy(const OdGeMatrix3d& mat);
public:
  OdDbShHistoryNodeImpl();
  virtual ~OdDbShHistoryNodeImpl();

  OdResult  dwgInFields( OdDbDwgFiler* pFiler );
  void      dwgOutFields( OdDbDwgFiler* pFiler ) const;
  OdResult  dxfInFields( OdDbDxfFiler* pFiler );
  void      dxfOutFields( OdDbDxfFiler* pFiler ) const;

  OdResult  postInDatabase( OdDbObjectId& objId, OdDbDatabase* pDatabase );
  const OdModelerGeometryPtr& getModeler() const { return m_Model; };
  OdModelerGeometryPtr& getModeler() { return m_Model; };
  void      setValidate(bool bValidate) { m_bValidate = bValidate; };
  bool      getValidate() const { return m_bValidate; };
  OdCmColor getColor() const { return m_color; };
  OdDbObjectId getMaterial() const { return m_materialId; };
  //virtual OdResult getGripPoints( OdDbGripDataPtrArray& gripsData, 
  //                                const double curViewUnitSize, 
  //                                const int gripSize, 
  //                                const OdGeVector3d& curViewDir, 
  //                                const int bitFlags );

  //OdResult getSubentPathGeomExtents(class OdDbExtents &)const

  //BODY* bodyForSharing();
  //BODY* bodyForTaking()
  //BODY* copyOfBody()
  //bool isEmptyBody() const

  //OdResult evaluate(class OdDbEvalContext const *)
  //OdResult getClassID(void* )
  //virtual OdResult moveGripPointsAt(const OdDbVoidPtrArray& grips, const OdGeVector3d& offset, int bitFlags );
  //void remappedNodeIds(OdDbEvalIdMap &)
  //void setBody(BODY *)
  virtual OdResult transformBy(const OdGeMatrix3d& mx);
  virtual bool evaluate(OdDbEvalContext const* ctx) = 0;
  

  DECLARE_GET_IMPL(OdDbShHistoryNode);
};
#endif
