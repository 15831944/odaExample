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

#ifndef _OBJECT_EXPLORER_CREATOR_
#define _OBJECT_EXPLORER_CREATOR_

#include <string>
#include <vector>
#include <memory>

#include "OdaCommon.h"
#include "Tv.h"
#include "TvDatabase.h"
#include "TvGsDevice.h"

#include "TvEntity.h"
#include "TvLight.h"
#include "TvInsert.h"

struct ObjectNode;
typedef std::shared_ptr<ObjectNode> ObjectNodePtr;

struct ObjectNode {
  OdUInt64                   handle;
  std::string                name;
  std::vector<ObjectNodePtr> children;
  ObjectNode*                parent;

  ObjectNode()
    : parent(NULL) {}

  ObjectNode(const std::string& name, OdUInt64 handle = 0, ObjectNode* parent = NULL)
    : name(name), handle(handle), parent(parent) {}

  void addChild(const ObjectNodePtr& node) {
    children.push_back(node);
    node->parent = this;
  }

  ~ObjectNode() {
    children.clear();
  }
};

class ObjectExplorerCreator {
public:
  ObjectExplorerCreator();

  void clear();

  ObjectNodePtr getRoot();

  void create(const OdTvDatabaseId& db_id);

  std::string toJSON();

protected:

  ObjectNodePtr addDevices(const OdTvDatabaseId& db_id);

  void addGeometryData(const ObjectNodePtr& parent, OdTvEntityPtr& ent);

  void addEntity(const ObjectNodePtr& parent, const OdTvEntityId& id);

  ObjectNodePtr addModels(const OdTvDatabaseId& db_id);

  ObjectNodePtr addLineTypes(const OdTvDatabaseId& db_id);

  ObjectNodePtr addTextStyles(const OdTvDatabaseId& db_id);

  ObjectNodePtr addLayers(const OdTvDatabaseId& db_id);

  ObjectNodePtr addMaterials(const OdTvDatabaseId& db_id);

  ObjectNodePtr addRasterImage(const OdTvDatabaseId& db_id);

  ObjectNodePtr createNode(const std::string& name);

  ObjectNodePtr createNode(const std::string &titel, const std::string& name);

  ObjectNodePtr createNode(const std::string &titel, const std::string& name, OdUInt64 handle);

  std::string toStdString(const OdString& str);

  void addToRootIfHaveChilds(const ObjectNodePtr& node);

private:
  OdTvDatabaseId m_dbId;
  ObjectNodePtr  m_root;
};

#endif
