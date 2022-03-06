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
import { TYPES, reducer } from "./viewer";

describe("viewer test", () => {
  function ViewerMock(result) {
    this.clear = () => (result.clear = true);
    this.parseStream = (data) => (result.parseStream = data);
    this.setActiveVisualStyle = (style) => (result.setActiveVisualStyle = style);
    this.setEnableSceneGraph = (value) => (result.setEnableSceneGraph = value);
    this.setHighlightColor = (...args) => (result.setHighlightColor = args);
    this.getActiveModel = () => {};
  }

  it("SET_VISUALIZEJS_INSTANCE", () => {
    const state = reducer(undefined, {});
    const visualizeJS = {};
    const nextState = reducer(state, {
      type: TYPES.SET_VISUALIZEJS_INSTANCE,
      payload: visualizeJS,
    });
    expect(nextState.visualizeJS).toEqual(visualizeJS);
  });
  it("SET_OBJECT_TREE", () => {
    const objectTree = {};
    const state = reducer(undefined, {
      type: TYPES.SET_OBJECT_TREE,
      payload: objectTree,
    });
    expect(state.objectTree).toEqual(objectTree);
  });

  it("SET_PROPERTIES", () => {
    const properties = {};
    const state = reducer(undefined, {
      type: TYPES.SET_PROPERTIES,
      payload: properties,
    });
    expect(state.properties).toEqual(properties);
  });

  it("SET_FPS", () => {
    const fps = true;
    const state = reducer(undefined, {
      type: TYPES.SET_FPS,
      payload: fps,
    });

    expect(state.fps).toEqual(fps);
  });

  it("SET_WCS", () => {
    const wcs = true;
    const state = reducer(undefined, {
      type: TYPES.SET_WCS,
      payload: wcs,
    });

    expect(state.wcs).toEqual(wcs);
  });

  it("SET_ANIMATION", () => {
    const animation = true;
    const state = reducer(undefined, {
      type: TYPES.SET_ANIMATION,
      payload: animation,
    });

    expect(state.animation).toEqual(animation);
  });

  it("CONFIG_RESPONSE", () => {
    const config = {
      visualizejs_url: "url",
    };
    const state = reducer(undefined, {
      type: TYPES.CONFIG_RESPONSE,
      payload: config,
    });

    expect(state.visualizejs_url).toEqual(config.visualizejs_url);
  });
});
