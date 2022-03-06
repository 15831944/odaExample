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

const OVERLAY_VIEW_NAME = "$OVERLAY_VIEW_NAME";
const MARKUP_ENTITY_LINE = "$MarkupTempEntity_Line";
const MARKUP_ENTITY_TEXT = "$MarkupTempEntity_Text";

function getActiveMarkupEntity(viewer, type) {
  const model = viewer.getMarkupModel();
  const entityName = "$MarkupTempEntity" + type;

  let res = model.appendEntity(entityName);
  res.openObject().setColor(255, 0, 0);
  res.openObject().setLineWeight(2);

  return res;
}

function logicalPoint3dToArrayValue(point) {
  return [point.x, point.y, point.z];
}

function arrayPointToLogicalPoint3d(array) {
  return { x: array[0], y: array[1], z: array[2] };
}

function createPreview(canvas, type, quality) {
  return canvas.toDataURL(type, quality);
}

function clearOldViewPoint(viewer) {
  const markupCtrl = viewer.getMarkupController();
  markupCtrl.clear();
  viewer.activeView.removeCuttingPlanes();
}

function syncOverlayView(viewer) {
  let overlayView = viewer.getViewByName(OVERLAY_VIEW_NAME);
  const activeView = viewer.activeView;

  if (!overlayView) {
    const overlayModel = viewer.getMarkupModel();
    const pDevice = viewer.getActiveDevice();

    overlayView = pDevice.createView(OVERLAY_VIEW_NAME, false);

    overlayView.addModel(overlayModel);

    activeView.addSibling(overlayView);
    pDevice.addView(overlayView);
  }

  overlayView.viewPosition = activeView.viewPosition;
  overlayView.viewTarget = activeView.viewTarget;
  overlayView.upVector = activeView.upVector;
  overlayView.viewFieldWidth = activeView.viewFieldWidth;
  overlayView.viewFieldHeight = activeView.viewFieldHeight;

  const viewPort = overlayView.getViewport();
  overlayView.setViewport(viewPort.lowerLeft, viewPort.upperRight);

  overlayView.vportRect = activeView.vportRect;

  return overlayView;
}

function deleteAll(objects) {
  for (let obj of objects) {
    obj.delete();
  }
}

function toPoint(module, gePoint) {
  return module.Point3d.createFromArray(gePoint);
}

function toGePoint(point) {
  return [point.x, point.y, point.z];
}

function createPlane(module) {
  return new module.OdTvPlane();
}

export default class ViewPointHelper {
  constructor(module) {
    this.m_viewer = module.getViewer();
    this.m_module = module;
  }

  drawViewPoint(viewPoint) {
    const viewer = this.m_viewer;
    const view = viewer.activeView;

    clearOldViewPoint(viewer);

    if (viewPoint.orthogonal_camera) {
      view.setView(
        logicalPoint3dToArrayValue(viewPoint.orthogonal_camera.view_point),
        logicalPoint3dToArrayValue(viewPoint.orthogonal_camera.direction),
        logicalPoint3dToArrayValue(viewPoint.orthogonal_camera.up_vector),
        viewPoint.orthogonal_camera.field_width,
        viewPoint.orthogonal_camera.field_height,
        true
      );
    }

    syncOverlayView(viewer);

    if (viewPoint.lines) {
      for (let line of viewPoint.lines) {
        const entityData = [];
        for (let point of line.points) {
          entityData.push(point.x, point.y, point.z);
        }

        const entity = getActiveMarkupEntity(viewer, "Line");
        const entityPtr = entity.openObject();

        entityPtr.appendPolyline(entityData);

        deleteAll([entityPtr, entity]);
      }
    }

    const pos = toPoint(this.m_module, view.viewPosition);
    const target = toPoint(this.m_module, view.viewTarget);
    const normal = pos.sub(target).asVector();

    if (viewPoint.texts) {
      for (var text of viewPoint.texts) {
        const entity = getActiveMarkupEntity(viewer, "Text");
        const entityPtr = entity.openObject();
        const geomData = entityPtr.appendText(logicalPoint3dToArrayValue(text.position), text.text);
        const textPtr = geomData.openAsText();

        textPtr.setNormal(toGePoint(normal));
        textPtr.setRotation(text.angle);
        textPtr.setTextSize(text.text_size);

        deleteAll([textPtr, geomData, entityPtr, entity]);
      }
    }

    if (viewPoint.clipping_planes) {
      for (let clippingPlane of viewPoint.clipping_planes) {
        const plane = createPlane(this.m_module);
        plane.set(
          logicalPoint3dToArrayValue(clippingPlane.location),
          logicalPoint3dToArrayValue(clippingPlane.direction)
        );

        view.addCuttingPlane(plane);
        view.setEnableCuttingPlaneFill(true, 0x66, 0x66, 0x66);
      }
    }
  }

  getViewPoint(canvas, opt) {
    const viewer = this.m_viewer;
    const view = viewer.activeView;

    const viewPointData = {};
    viewPointData.orthogonal_camera = {
      view_point: arrayPointToLogicalPoint3d(view.viewPosition),
      direction: arrayPointToLogicalPoint3d(view.viewTarget),
      up_vector: arrayPointToLogicalPoint3d(view.upVector),
      field_width: view.viewFieldWidth,
      field_height: view.viewFieldHeight,
    };

    viewPointData.lines = [];
    viewPointData.texts = [];
    viewPointData.clipping_planes = [];

    {
      const model = viewer.getMarkupModel();
      for (const itr = model.getEntitiesIterator(); !itr.done(); itr.step()) {
        const entity = itr.getEntity();
        const entityPtr = entity.openObject();

        const geomItr = entityPtr.getGeometryDataIterator();

        if (geomItr.done()) {
          continue;
        }

        const geometryId = geomItr.getGeometryData();

        if (entityPtr.getName() === MARKUP_ENTITY_LINE) {
          const polyLinePtr = geometryId.openAsPolyline();
          const points = polyLinePtr.getPoints();

          const newLineItem = {
            points: [],
          };

          for (const point of points) {
            newLineItem.points.push(arrayPointToLogicalPoint3d(point));
          }

          viewPointData.lines.push(newLineItem);
          deleteAll([polyLinePtr]);
        } else if (entityPtr.getName() === MARKUP_ENTITY_TEXT) {
          const textPtr = geometryId.openAsText();
          const position = textPtr.getPosition();

          const newLineItem = {
            position: arrayPointToLogicalPoint3d(position),
            text: textPtr.getString(),
            angle: textPtr.getRotation(),
            text_size: textPtr.getTextSize(),
          };

          viewPointData.texts.push(newLineItem);

          deleteAll([textPtr]);
        }

        deleteAll([entityPtr, entity]);
      }
    }

    const cuttingPlaneSize = view.numCuttingPlanes();
    for (let i = 0; i < cuttingPlaneSize; i++) {
      const cuttingPlane = view.getCuttingPlane(i);
      viewPointData.clipping_planes.push({
        location: arrayPointToLogicalPoint3d(cuttingPlane.getOrigin()),
        direction: arrayPointToLogicalPoint3d(cuttingPlane.normal()),
      });
    }

    const fixOpt = opt || { type: "image/jpeg", quality: 0.25 };
    fixOpt.type = fixOpt.type || "image/jpeg";
    fixOpt.quality = fixOpt.quality || 0.25;

    viewPointData.snapshot = {
      data: createPreview(canvas, fixOpt.type, fixOpt.quality),
    };

    return viewPointData;
  }
}
