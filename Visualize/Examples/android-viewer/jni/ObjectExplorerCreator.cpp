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
#include "ObjectExplorerCreator.h"

ObjectExplorerCreator::ObjectExplorerCreator() : m_root(NULL)
{

}

void ObjectExplorerCreator::clear()
{
  m_root.reset();
}

ObjectNodePtr ObjectExplorerCreator::getRoot()
{
  return m_root;
}

void ObjectExplorerCreator::create(const OdTvDatabaseId& db_id)
{
  m_dbId = db_id;
  m_root = createNode("Database");
  addToRootIfHaveChilds(addDevices(db_id));
  addToRootIfHaveChilds(addModels(db_id));
  addToRootIfHaveChilds(addLineTypes(db_id));
  addToRootIfHaveChilds(addTextStyles(db_id));
  addToRootIfHaveChilds(addLayers(db_id));
  addToRootIfHaveChilds(addMaterials(db_id));
  addToRootIfHaveChilds(addRasterImage(db_id));
  m_dbId.setNull();
}

ObjectNodePtr ObjectExplorerCreator::addDevices(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr devices = createNode("Devices");

  OdTvDevicesIteratorPtr itr = db_id.openObject()->getDevicesIterator();
  OdTvGsDevicePtr dev_ptr;
  ObjectNodePtr   device_node;

  for (; !itr->done(); itr->step()) {
    dev_ptr = itr->getDevice().openObject();
    device_node = createNode("Device", toStdString(dev_ptr->getName()));
    for (int i = 0; i < dev_ptr->numViews(); i++) {
      device_node->addChild(createNode("View", toStdString(dev_ptr->viewAt(i).openObject()->getName())));
    }
    devices->children.push_back(device_node);
    device_node->parent = devices.get();
  }

  return devices;
}

void ObjectExplorerCreator::addGeometryData(const ObjectNodePtr& parent, OdTvEntityPtr& ent)
{
  ObjectNodePtr      sub_node;
  OdTvEntityPtr      sub_ent;
  OdTvGeometryDataId geom_id;

  for (OdTvGeometryDataIteratorPtr itr = ent->getGeometryDataIterator(); !itr->done(); itr->step()) {
    geom_id = itr->getGeometryData();

    switch (geom_id.getType()) {
    case OdTv::kPolyline:
      sub_node = createNode("Polyline");
      break;
    case OdTv::kCircle:
      sub_node = createNode("Circle");
      break;
    case OdTv::kCircleWedge:
      sub_node = createNode("Circle wedge");
      break;
    case OdTv::kCircularArc:
      sub_node = createNode("Circular arc");
      break;
    case OdTv::kEllipse:
      sub_node = createNode("Ellipse");
      break;
    case OdTv::kEllipticArc:
      sub_node = createNode("Elliptic arc");
      break;
    case OdTv::kPolygon:
      sub_node = createNode("Polygon");
      break;
    case OdTv::kText:
      sub_node = createNode("Text");
      break;
    case OdTv::kShell:
      sub_node = createNode("Shell");
      break;
    case OdTv::kSphere:
      sub_node = createNode("Sphere");
      break;
    case OdTv::kCylinder:
      sub_node = createNode("Cylinder");
      break;
    case OdTv::kSubInsert:
      sub_node = createNode("Insert");
      break;
    case OdTv::kSubEntity:
      sub_ent = geom_id.openAsSubEntity();
      sub_node = createNode("Entity", toStdString(sub_ent->getName()));
      addGeometryData(sub_node, sub_ent);
      break;
    case OdTv::kNurbs:
      sub_node = createNode("Nurbs");
      break;
    case OdTv::kRasterImage:
      sub_node = createNode("Raster image");
      break;
    case OdTv::kInfiniteLine:
      sub_node = createNode("Infinite line");
      break;
    case OdTv::kMesh:
      sub_node = createNode("Mesh");
      break;
    case OdTv::kPointCloud:
      sub_node = createNode("Point cloud");
      break;
    case OdTv::kGrid:
      sub_node = createNode("Grid");
      break;
    case OdTv::kColoredShape:
      sub_node = createNode("Colored shape");
      break;
    default:
      sub_node = ObjectNodePtr();
    }

    if (sub_node) {
      parent->addChild(sub_node);
    }
  }
}

void ObjectExplorerCreator::addEntity(const ObjectNodePtr& parent, const OdTvEntityId& id)
{
  ObjectNodePtr node;
  OdUInt64 handle = 0;
  OdString regAppName = L"ExGsVisualizeDevice";
  OdTvEntityPtr ent;

  switch (id.getType()) {
  case OdTvEntityId::kEntity: {
    bool exits;
    ent   = id.openObject();
    OdTvRegAppId regId         = m_dbId.openObject()->registerAppName(regAppName, exits);
    OdTvByteUserData *userData = static_cast<OdTvByteUserData*>(ent->getUserData(regId));

    if (userData  && userData->getSize() == sizeof(OdUInt64)) {
      memcpy(&handle, userData->getData(), userData->getSize());
    }

    if (handle == 0) {
      node = createNode("Entity", toStdString(ent->getName()));
    } else {
      node = createNode("Entity", toStdString(ent->getName()), handle);
    }

    addGeometryData(node, ent);
  } break;
  case OdTvEntityId::kInsert: {
    OdTvInsertPtr insert = id.openObjectAsInsert();
    node = createNode("Insert", toStdString(insert->getName()));
  } break;
  case OdTvEntityId::kLight: {
    OdTvLightPtr light = id.openObjectAsLight();
    node = createNode("Light", toStdString(light->getName()));
  } break;
  }
  parent->addChild(node);
}

ObjectNodePtr ObjectExplorerCreator::addModels(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr models_node = createNode("Models");

  OdTvModelPtr  model;
  ObjectNodePtr model_node;
  OdTvModelsIteratorPtr itr = db_id.openObject()->getModelsIterator();

  for (; !itr->done(); itr->step()) {
    model = itr->getModel().openObject();
    model_node = createNode("Model", toStdString(model->getName()));

    for (OdTvEntitiesIteratorPtr itr = model->getEntitiesIterator(); !itr->done(); itr->step()) {
      addEntity(model_node, itr->getEntity());
    }

    models_node->addChild(model_node);
  }

  return models_node;
}

ObjectNodePtr ObjectExplorerCreator::addLineTypes(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr line_types_node = createNode("Line types");

  OdTvLinetypePtr line_type_ptr;
  OdTvLinetypesIteratorPtr itr = db_id.openObject()->getLinetypesIterator();
  for (; !itr->done(); itr->step()) {
    line_type_ptr = itr->getLinetype().openObject();
    line_types_node->addChild(createNode("Line type", toStdString(line_type_ptr->getName())));
  }

  return line_types_node;
}

ObjectNodePtr ObjectExplorerCreator::addTextStyles(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr text_styles_node = createNode("Text styles");

  OdTvTextStylePtr text_style;
  OdTvTextStylesIteratorPtr itr = db_id.openObject()->getTextStylesIterator();
  for (; !itr->done(); itr->step()) {
    text_style = itr->getTextStyle().openObject();
    text_styles_node->addChild(createNode("Text styles", toStdString(text_style->getName())));
  }
  return text_styles_node;
}

ObjectNodePtr ObjectExplorerCreator::addLayers(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr layers_node = createNode("Layers");

  OdTvLayerPtr layer_ptr;
  OdTvLayersIteratorPtr itr = db_id.openObject()->getLayersIterator();

  for (; !itr->done(); itr->step()) {
    layer_ptr = itr->getLayer().openObject();
    layers_node->addChild(createNode("Layer", toStdString(layer_ptr->getName())));
  }

  return layers_node;
}

ObjectNodePtr ObjectExplorerCreator::addMaterials(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr material_node = createNode("Materials");

  OdTvMaterialPtr material_ptr;
  OdTvMaterialsIteratorPtr itr = db_id.openObject()->getMaterialsIterator();

  for (; !itr->done(); itr->step()) {
    material_ptr = itr->getMaterial().openObject();
    material_node->addChild(createNode("Material", toStdString(material_ptr->getName())));
  }

  return material_node;
}

ObjectNodePtr ObjectExplorerCreator::addRasterImage(const OdTvDatabaseId& db_id)
{
  ObjectNodePtr raster_node = createNode("Raster Images");

  OdTvRasterImagePtr raster_ptr;
  OdTvRasterImagesIteratorPtr itr = db_id.openObject()->getRasterImagesIterator();

  for (; !itr->done(); itr->step()) {
    raster_ptr = itr->getRasterImage().openObject();
    raster_node->addChild(createNode("Image", toStdString(raster_ptr->getSourceFileName())));
  }

  return raster_node;
}

ObjectNodePtr ObjectExplorerCreator::createNode(const std::string& name)
{
  return std::make_shared<ObjectNode>(name);
}

ObjectNodePtr ObjectExplorerCreator::createNode(const std::string &titel, const std::string& name)
{
  return std::make_shared<ObjectNode>(titel + "[" + name + "]");
}

ObjectNodePtr ObjectExplorerCreator::createNode(const std::string &titel, const std::string& name, OdUInt64 handle)
{
  return std::make_shared<ObjectNode>(titel + "[" + name + "]", handle);
}

std::string ObjectExplorerCreator::toStdString(const OdString& str)
{
  return std::string((const char*)str, str.getLength());
}

void ObjectExplorerCreator::addToRootIfHaveChilds(const ObjectNodePtr& node)
{
  if (node->children.size() != 0) {
    m_root->children.push_back(node);
    node->parent = m_root.get();
  }
}
