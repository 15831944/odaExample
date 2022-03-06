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
"use strict";

class Util {
  static point(point) {
    return `(${point[0].toFixed(2)}, ${point[1].toFixed(2)}, ${point[2].toFixed(2)})`;
  }

  static number(point) {
    return `(${point.toFixed(2)})`;
  }

  static firstPoint(points) {
    return `(${points[0][0].toFixed(2)}, ${points[0][1].toFixed(2)}, ${points[0][2].toFixed(2)})`;
  }

  static lastPoint(points) {
    return `(${points[points.length - 1][0].toFixed(2)}, ${points[points.length - 1][1].toFixed(2)}, ${points[
      points.length - 1
    ][2].toFixed(2)})`;
  }
}

export class OdReadOnlyProperties {
  constructor() {
    this.items = new Map();

    this.items.set("Model", (dataNode) => {
      const props = [];
      const model = dataNode.object;

      props.push({
        name: "Name",
        value: model.getName(),
      });

      props.push({
        name: "Position",
        value: Util.point(model.getExtents().center()),
      });

      return props;
    });

    this.items.set("Block", (dataNode) => {
      const props = [];
      const model = dataNode.object;

      props.push({
        name: "Name",
        value: model.getName(),
      });

      return props;
    });

    this.items.set("Entity", (dataNode) => {
      const props = [];
      const entityId = dataNode.object;
      const entity = entityId.openObject();

      props.push({
        name: "Name",
        value: entity.getName(),
      });

      props.push({
        name: "Handle",
        value: `0x${entity.getDatabaseHandle()}`,
      });

      props.push({
        name: "Position",
        value: Util.point(entity.getExtents().center()),
      });

      return props;
    });

    this.items.set("Sub Entity", (dataNode) => {
      const entity = dataNode.object;
      const props = [];

      props.push({
        name: "Name",
        value: entity.getName(),
      });

      props.push({
        name: "Handle",
        value: `0x${entity.getDatabaseHandle()}`,
      });

      props.push({
        name: "Position",
        value: Util.point(entity.getExtents().center()),
      });

      return props;
    });

    this.items.set("Device", (dataNode) => {
      const entity = dataNode.object;
      const props = [];

      props.push({
        name: "Name",
        value: entity.getName(),
      });

      props.push({
        name: "Count of views",
        value: entity.numViews(),
      });

      return props;
    });

    this.items.set("Polyline", (dataNode) => {
      const entity = dataNode.object.openAsPolyline();
      const props = [];

      props.push({
        name: "Points count",
        value: entity.getPointsCount(),
      });

      props.push({
        name: "First point",
        value: Util.firstPoint(entity.getPoints()),
      });

      props.push({
        name: "Last point",
        value: Util.lastPoint(entity.getPoints()),
      });

      props.push({
        name: "Normal",
        value: Util.point(entity.getNormal()),
      });

      return props;
    });

    this.items.set("Circle", (dataNode) => {
      const entity = dataNode.object.openAsCircle();
      const props = [];

      props.push({
        name: "Center",
        value: Util.point(entity.getCenter()),
      });

      props.push({
        name: "Normal",
        value: Util.point(entity.getNormal()),
      });

      props.push({
        name: "Radius",
        value: Util.point(entity.getRadius()),
      });

      props.push({
        name: "Filled",
        value: entity.getFilled(),
      });

      props.push({
        name: "Thickness",
        value: entity.getThickness(),
      });

      return props;
    });

    this.items.set("Circle Wedge", (dataNode) => {
      const entity = dataNode.object.openAsCircleWedge();
      const props = [];

      props.push({
        name: "Start",
        value: Util.point(entity.getStart()),
      });

      props.push({
        name: "Middle",
        value: Util.point(entity.getMiddle()),
      });

      props.push({
        name: "End",
        value: Util.point(entity.getEnd()),
      });

      props.push({
        name: "Filled",
        value: entity.getFilled(),
      });

      props.push({
        name: "Thickness",
        value: entity.getThickness(),
      });

      return props;
    });

    this.items.set("Circle Arc", (dataNode) => {
      const entity = dataNode.object.openAsCircleArc();
      const props = [];

      props.push({
        name: "Start",
        value: Util.point(entity.getStart()),
      });

      props.push({
        name: "Middle",
        value: Util.point(entity.getMiddle()),
      });

      props.push({
        name: "End",
        value: Util.point(entity.getEnd()),
      });

      props.push({
        name: "Filled",
        value: entity.getFilled(),
      });

      props.push({
        name: "Thickness",
        value: entity.getThickness(),
      });

      return props;
    });

    this.items.set("Ellipse", (dataNode) => {
      const entity = dataNode.object.openAsEllipse();
      const props = [];

      props.push({
        name: "Center",
        value: Util.point(entity.getCenter()),
      });

      props.push({
        name: "Major",
        value: Util.point(entity.getMajor()),
      });

      props.push({
        name: "Minor",
        value: Util.point(entity.getMinor()),
      });

      props.push({
        name: "Filled",
        value: entity.getFilled(),
      });

      props.push({
        name: "Thickness",
        value: entity.getThickness(),
      });

      return props;
    });

    this.items.set("Elliptic Arc", (dataNode) => {
      const entity = dataNode.object.openAsEllipticArc();
      const props = [];

      props.push({
        name: "Major",
        value: Util.point(entity.getMajor()),
      });

      props.push({
        name: "Minor",
        value: Util.point(entity.getMinor()),
      });

      props.push({
        name: "Start",
        value: Util.number(entity.getStart()),
      });

      props.push({
        name: "End",
        value: Util.number(entity.getEnd()),
      });

      props.push({
        name: "Filled",
        value: entity.getFilled(),
      });

      props.push({
        name: "Thickness",
        value: entity.getThickness(),
      });

      return props;
    });

    this.items.set("Polygon", (dataNode) => {
      const entity = dataNode.object.openAsPolygon();
      const props = [];

      props.push({
        name: "Points count",
        value: Util.point(entity.getPointsCount()),
      });

      props.push({
        name: "Filled",
        value: entity.getFilled(),
      });

      props.push({
        name: "Use Inverse Normal",
        value: entity.getUseInverseNormal(),
      });

      return props;
    });

    this.items.set("Text", (dataNode) => {
      const entity = dataNode.object.openAsText();
      const props = [];

      props.push({
        name: "Position",
        value: Util.point(entity.getPosition()),
      });

      props.push({
        name: "Alignment Point",
        value: Util.point(entity.getAlignmentPoint()),
      });

      props.push({
        name: "Normal",
        value: Util.point(entity.getNormal()),
      });

      props.push({
        name: "Rotation",
        value: entity.getRotation(),
      });

      props.push({
        name: "String",
        value: entity.getString(),
      });

      props.push({
        name: "Alignment mode",
        value: entity.getAlignmentMode(),
      });

      props.push({
        name: "Text size",
        value: entity.getTextSize(),
      });

      props.push({
        name: "Width factor",
        value: entity.getWidthFactor(),
      });

      props.push({
        name: "Text style",
        value: entity.getTextStyle(),
      });

      return props;
    });

    this.items.set("Shell", (dataNode) => {
      const entity = dataNode.object.openAsShell();
      const props = [];

      props.push({
        name: "Disable lighting",
        value: entity.getDisableLighting(),
      });

      props.push({
        name: "Faces count",
        value: entity.getFacesCount(),
      });

      props.push({
        name: "Edges count",
        value: entity.getEdgesCount(),
      });

      props.push({
        name: "Vertices count",
        value: entity.getVerticesCount(),
      });

      return props;
    });

    this.items.set("Sphere", (dataNode) => {
      const entity = dataNode.object.openAsSphere();
      const props = [];

      props.push({
        name: "Radius",
        value: Util.number(entity.getRadius()),
      });

      props.push({
        name: "Center",
        value: Util.point(entity.getCenter()),
      });

      props.push({
        name: "Basic axis",
        value: Util.point(entity.getBasisAxis()),
      });

      props.push({
        name: "Basis Prime Meridian",
        value: Util.point(entity.getBasisPrimeMeridian()),
      });

      return props;
    });

    this.items.set("Cylinder", (dataNode) => {
      const entity = dataNode.object.openAsCylinder();
      const props = [];

      props.push({
        name: "Radius",
        value: Util.number(entity.getRadius()),
      });

      props.push({
        name: "Center",
        value: Util.point(entity.getCenter()),
      });

      props.push({
        name: "Basic axis",
        value: Util.point(entity.getBasisAxis()),
      });

      props.push({
        name: "Basis Prime Meridian",
        value: Util.point(entity.getBasisPrimeMeridian()),
      });

      return props;
    });
    //TODO
    this.items.set("Sub Insert", (dataNode) => {
      const props = [];
      return props;
    });

    this.items.set("Nurbs", (dataNode) => {
      const entity = dataNode.object.openAsNurbs();
      const props = [];

      props.push({
        name: "Degree",
        value: Util.number(entity.getDegree()),
      });

      return props;
    });

    this.items.set("Raster Image", (dataNode) => {
      const entity = dataNode.object.openAsRasterImage();
      const props = [];

      props.push({
        name: "Alignment",
        value: entity.getAlignment(),
      });

      props.push({
        name: "Inverted",
        value: entity.getInverted(),
      });

      props.push({
        name: "Source file name",
        value: entity.getSourceFileName(),
      });

      return props;
    });

    this.items.set("Infinite Line", (dataNode) => {
      const entity = dataNode.object.openAsInfiniteLine();
      const props = [];

      props.push({
        name: "First",
        value: Util.point(entity.getFirst()),
      });

      props.push({
        name: "Second",
        value: Util.point(entity.getSecond()),
      });

      props.push({
        name: "Type",
        value: entity.getType(),
      });

      return props;
    });

    this.items.set("Mesh", (dataNode) => {
      const entity = dataNode.object.openAsMesh();
      const props = [];

      props.push({
        name: "Vertices count",
        value: entity.getVerticesCount(),
      });

      props.push({
        name: "Faces count",
        value: entity.getFacesCount(),
      });

      props.push({
        name: "Edges count",
        value: entity.getEdgesCount(),
      });

      props.push({
        name: "Rows count",
        value: entity.getRowsCount(),
      });

      props.push({
        name: "Columns count",
        value: entity.getColumnsCount(),
      });

      return props;
    });

    this.items.set("Point Cloud", (dataNode) => {
      const entity = dataNode.object.openAsPointCloud();
      const props = [];

      props.push({
        name: "Points count",
        value: entity.getPointsCount(),
      });

      props.push({
        name: "Second",
        value: Util.number(entity.getPointSize()),
      });

      props.push({
        name: "Point color",
        value: entity.getPointColor(),
      });

      return props;
    });

    this.items.set("Grid", (dataNode) => {
      const entity = dataNode.object.openAsPointCloud();
      const props = [];

      props.push({
        name: "Points count",
        value: entity.getPointsCount(),
      });

      props.push({
        name: "Second",
        value: Util.number(entity.getPointSize()),
      });

      props.push({
        name: "Point color",
        value: entity.getPointColor(),
      });

      return props;
    });

    this.items.set("Colored Shape", (dataNode) => {
      const entity = dataNode.object.openAsColoredShape();
      const props = [];

      props.push({
        name: "Vertices count",
        value: entity.getVerticesCount(),
      });

      return props;
    });

    this.items.set("Insert", (dataNode) => {
      const entity = dataNode.object.openObjectAsInsert();
      console.log(entity);
      const props = [];

      props.push({
        name: "Block",
        value: entity.getBlock(),
      });

      props.push({
        name: "Name",
        value: entity.getName(),
      });

      props.push({
        name: "Position",
        value: Util.point(entity.getPosition()),
      });

      props.push({
        name: "Rotation",
        value: Util.number(entity.getRotation()),
      });

      props.push({
        name: "Normal",
        value: Util.point(entity.getNormal()),
      });

      props.push({
        name: "Color",
        value: entity.getColor(),
      });

      props.push({
        name: "Color",
        value: entity.getVisibility(),
      });

      return props;
    });
  }

  has(type) {
    return this.items.has(type);
  }

  get(type, dataNode) {
    return this.has(type) ? this.items.get(type)(dataNode) : [];
  }

  formatNativeProperties(data) {
    const nativePropData = [];
    const nativePropCategory = [];

    for (let k in data) {
      if (Array.isArray(data[k])) {
        for (let i = 0; i < data[k].length; i++) {
          const prop = data[k][i];
          for (let key in prop) {
            const values = prop[key];

            const vlProp = [];
            for (let keyV in values) {
              vlProp.push({
                name: keyV,
                value: values[keyV],
              });
            }

            nativePropCategory.push({
              name: key,
              value: vlProp,
            });
          }
        }
      } else {
        nativePropData.push({
          name: k,
          value: data[k],
        });
      }
    }

    return { data: nativePropData, category: nativePropCategory };
  }
}
