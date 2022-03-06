///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance").
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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
import React, { Component } from "react";
import Window from "./../components/Window";
import PropTypes from "prop-types";

const EntityTypes = {
  kUndefined: 0, // An undefined type
  kEntity: 1, // An entity type.
  kInsert: 2, // An insert object.
  kLight: 3, // A light object.
};

const OdTvGeometryDataType = {
  kUndefinied: 0, // Undefined geometry.
  kPolyline: 1, // A polyline.
  kCircle: 2, // A circle.
  kCircleWedge: 3, // A circle wedge.
  kCircularArc: 4, // A circular arc.
  kEllipse: 5, // An ellipse.
  kEllipticArc: 6, // An elliptical arc.
  kPolygon: 7, // A polygon.
  kText: 8, // Text.
  kShell: 9, // A shell.
  kSphere: 10, // A sphere.
  kCylinder: 11, // A cylinder.
  kSubInsert: 12, // An insert sub-entity.
  kSubEntity: 13, // A sub-entity.
  kNurbs: 14, // A NURBS curve.
  kRasterImage: 15, // A raster image.
  kInfiniteLine: 16, // An infinite line.
  kMesh: 17, // A mesh.
  kPointCloud: 18, // A point cloud.
  kGrid: 19, // A grid.
  kColoredShape: 20, // A colored shape.
  kBox: 21, // A box.
  kBrep: 22, // A boundary representation object.
};

const TypeNameBinding = {
  0: "Undefined", // Undefined geometry.
  1: "Polyline", // A polyline.
  2: "Circle", // A circle.
  3: "CircleWedge", // A circle wedge.
  4: "CircularArc", // A circular arc.
  5: "Ellipse", // An ellipse.
  6: "EllipticArc", // An elliptical arc.
  7: "Polygon", // A polygon.
  8: "Text", // Text.
  9: "Shell", // A shell.
  10: "Sphere", // A sphere.
  11: "Cylinder", // A cylinder.
  12: "SubInsert", // An insert sub-entity.
  13: "kSubEntity", // A sub-entity.
  14: "Nurbs", // A NURBS curve.
  15: "RasterImage", // A raster image.
  16: "InfiniteLine", // An infinite line.
  17: "Mesh", // A mesh.
  18: "PointCloud", // A point cloud.
  19: "Grid", // A grid.
  20: "ColoredShape", // A colored shape.
  21: "Box", // A box.
  22: "Brep", // A boundary representation object.
};

const iterators = {
  Model: { pointer: (it) => it.getModel() },
  Block: { pointer: (it) => it.getBlock().openObject() },
  Layers: { pointer: (it) => it.getLayer().openObject() },
  Materials: { pointer: (it) => it.getMaterial().openObject() },
  VisualStyles: { pointer: (it) => it.getVisualStyle().openObject() },
  TextStyles: { pointer: (it) => it.getTextStyle().openObject() },
  Devices: { pointer: (it) => it.getDevice() },
  RasterImages: { pointer: (it) => it.getRasterImage().openObject() },
  Linetype: { pointer: (it) => it.getLinetype().openObject() },
  GeometryData: {
    pointer: (it) => {
      const geomId = it.getGeometryData();
      const type = geomId.getType();
      if (type === OdTvGeometryDataType.kSubEntity) {
        return geomId.openAsSubEntity();
      } else {
        return geomId;
      }
    },
    getName: (pointer) => {
      if (pointer["getType"]) {
        return TypeNameBinding[pointer.getType()];
      } else if (pointer["getName"]) {
        return `SubEntity ${pointer.getName()}`;
      }
      return pointer.$$.ptrType.registeredClass.name;
    },
  },
  Entities: {
    pointer: (it) => {
      const entityId = it.getEntity();
      if (entityId.getType() === EntityTypes.kEntity) {
        return entityId.openObject();
      } else if (entityId.getType() === EntityTypes.kInsert) {
        return entityId.openObjectAsInsert();
      } else {
        return entityId.openObjectAsLight();
      }
    },
    id: (it) => it.getEntity(),
  },
  CDATree: {
    pointer: (it) => {
      return it.getCDATreeStorage().getTree().getDatabaseNode();
    },
    getName: (pointer) => pointer.getNodeName(),
    id: (it) => {
      return null;
    },
  },
  children: {
    pointer: (it) => {
      return it.current();
    },
    getName: (pointer) => pointer.getNodeName(),
    id: (it) => it.current().getTvEntityId(),
  },
};

const ObjectExplorerContext = React.createContext("objectExplorer");

class ObjectExplorer extends Component {
  selected = null;

  selectEntity = (id) => {
    this.props.getProperties(id);
  };

  render() {
    const { viewer, cda, lib } = this.props;
    return (
      <Window className="object-explorer" title="Object Explorer" onClose={this.props.onClose}>
        <ObjectExplorerContext.Provider value={this}>
          {cda ? <CDATreeViewer lib={lib} viewer={viewer} /> : <OdNode pointer={viewer} viewer={viewer} />}
        </ObjectExplorerContext.Provider>
      </Window>
    );
  }
}
ObjectExplorer.propTypes = {
  onClose: PropTypes.func,
};

function CDATreeViewer(props) {
  const { viewer, lib } = props;
  const itr = viewer.getCDATreeIterator();
  return <CDAStorage storage={itr.getCDATreeStorage()} lib={lib} viewer={viewer} />;
}

function CDAStorage(props) {
  const { storage, viewer, lib } = props;
  const tree = storage.getTree();
  const node = tree.getDatabaseNode();
  return <CDANode node={node} viewer={viewer} lib={lib} name={"CDA"} />;
}

class CDANode extends Component {
  static contextType = ObjectExplorerContext;

  state = { show: false, hilight: false };
  toggle = () => this.setState({ show: !this.state.show });
  toggleHilight = (active) => this.setState({ hilight: active });
  select = (node) => {
    if (this.context && node) {
      this.context.selected && this.context.selected.toggleHilight(false);
      this.context.selected = this;
      this.toggleHilight(true);
      node.getUniqueSourceID && this.context.selectEntity(node.getUniqueSourceID());
    }

    if (!this.props.viewer) return;

    const entityId = node.getTvEntityId(this.props.viewer.activeView);

    if (node.getChildren().length() === 0) {
      this.props.viewer.setSelectedEntity(entityId);
    } else {
      const set = new this.props.lib.OdTvSelectionSet();

      const childrens = node.getChildren();
      for (let i = 0; i < childrens.length(); i++) {
        const subNode = childrens.get(i);
        const subEntityId = subNode.getTvEntityId(this.props.viewer.activeView);

        if (!subEntityId.isNull()) {
          set.appendEntity(subEntityId);
        }
      }
      this.props.viewer.setSelected(set);
    }
  };
  zoomIn = (node) => {
    if (!this.props.viewer) return;
    const entityId = node.getTvEntityId(this.props.viewer.activeView);
    if (!entityId.isNull()) {
      this.props.viewer.zoomToEntity(entityId);
    }
  };

  generateChildrens = (childrens) => {
    const list = [];
    const length = childrens.length();
    for (let i = 0; i < length; i++) {
      list.push(
        <li key={i}>
          <CDANode node={childrens.get(i)} lib={this.props.lib} viewer={this.props.viewer} />
        </li>
      );
    }
    return list;
  };

  render() {
    const node = this.props.node;
    const childrens = node.getChildren();
    const childrensLen = childrens.length();
    const name = this.props.name || node.getNodeName();
    const show = this.state.show;

    return (
      <div style={{ cursor: "pointer" }}>
        <div className={`d-flex ${this.state.hilight ? "active" : ""}`}>
          {childrensLen > 0 ? (
            <i onClick={this.toggle} className="material-icons">
              {show ? "keyboard_arrow_down" : "keyboard_arrow_right"}
            </i>
          ) : null}
          <span onClick={() => this.select(node)} onDoubleClick={() => this.zoomIn(node)}>
            {name}
          </span>
        </div>
        {show ? <ul>{this.generateChildrens(childrens)}</ul> : null}
      </div>
    );
  }
}

class Iterator extends Component {
  state = { count: 10, show: false };

  static contextType = ObjectExplorerContext;

  toggle = () => this.setState({ show: !this.state.show });
  select = (id, pointer) => {
    if (id && this.props.viewer) {
      this.props.viewer.setSelectedEntity(id);

      if (this.context && pointer) {
        pointer.getNativeDatabaseHandle && this.context.selectEntity(pointer.getNativeDatabaseHandle());
        pointer.getUniqueSourceID && this.context.selectEntity(pointer.getUniqueSourceID());
      }
    }
  };
  result = [];

  render() {
    const type = this.props.type;
    const itr = this.props.itr;

    const show = this.state.show;
    if (show) {
      for (let i = 0; !itr.done() && i < 100; itr.step(), i++) {
        const handler = iterators[type];
        const pointer = handler ? handler.pointer(itr) : null;
        let name = pointer && pointer.getName ? pointer.getName() : null;
        if (!name && handler.getName) {
          name = handler.getName(pointer);
        }
        if (!name) {
          name = pointer.$$.ptrType.registeredClass.name;
        }
        // eslint-disable-next-line
        const id = (handler.id && handler.id(itr)) || null;

        if (name !== "$M_View_0_WCS_MODEL" && name !== "$FOR_EFFECT") {
          this.result.push(
            <li key={pointer.$$.ptr}>
              <OdNode pointer={pointer} viewer={this.props.viewer} onClick={() => this.select(id, pointer)}>
                {name}
              </OdNode>
            </li>
          );
        }
      }
    }

    return (
      <>
        <div style={{ cursor: "pointer", verticalAlign: "middle" }}>
          <i onClick={this.toggle} className="material-icons">
            {show ? "keyboard_arrow_down" : "keyboard_arrow_right"}
          </i>
          {type}
        </div>
        {show ? <ul>{this.result}</ul> : null}
      </>
    );
  }
}

class CDAChildrenIterator {
  constructor(pointer) {
    this.pointer = pointer;
    this.index = 0;
  }
  done() {
    return !(this.index < this.pointer.length());
  }
  step() {
    this.index++;
  }
  current() {
    return this.done() ? null : this.pointer.get(this.index);
  }
}

class OdNode extends Component {
  state = { show: false };

  toggle = () => {
    this.setState({ show: !this.state.show });
  };

  render() {
    const pointer = this.props.pointer || null;
    const showCDA = this.props.showCDA || false;
    let name = this.props.children || null;

    if (!this.list) {
      if (pointer) {
        if (pointer.getChildren) {
          console.log("pointer.getChildren", pointer.getChildren);
          const children = pointer.getChildren();
          this.list = [
            <li key={0}>
              <Iterator itr={new CDAChildrenIterator(children)} type={"children"} viewer={this.props.viewer} />
            </li>,
          ];
        } else {
          this.list = Object.keys(pointer.__proto__);
          if (!showCDA) {
            this.list = this.list.filter((key) => key !== "getCDATreeIterator");
          }
          this.list = this.list.filter((key) => /get\w+Iterator/gi.test(key));

          this.list = this.list.map((funcName, index) => {
            const regex = /get(\w+)Iterator/gi;
            const match = regex.exec(funcName);
            const name = match ? match[1] : null;
            return (
              <li key={index}>
                <Iterator itr={pointer[funcName]()} type={name} viewer={this.props.viewer} />
              </li>
            );
          });
        }
      }
    }

    const show = this.state.show;
    return (
      <div style={{ cursor: "pointer" }}>
        <div className="d-flex">
          {this.list && this.list.length && name && name.length !== 0 ? (
            <i onClick={this.toggle} className="material-icons">
              {show ? "keyboard_arrow_down" : "keyboard_arrow_right"}
            </i>
          ) : null}
          <span onClick={this.props.onClick}>{name}</span>
        </div>
        {show || !name ? <ul>{this.list}</ul> : null}
      </div>
    );
  }
}

export default ObjectExplorer;
