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

export const TYPES = {
  SET_VISUALIZEJS_INSTANCE: "SET_VISUALIZEJS_INSTANCE",
  SET_OBJECT_TREE: "SET_OBJECT_TREE",
  SET_PROPERTIES: "SET_PROPERTIES",
  SET_NATIVE_PROPERTIES: "SET_NATIVE_PROPERTIES",
  SET_FPS: "SET_FPS",
  SET_WCS: "SET_WCS",
  SET_ANIMATION: "SET_ANIMATION",
  SET_VS_HIGHLIGHT: "SET_VS_HIGHLIGHT",
  SET_ANTI_ALIASING: "SET_ANTI_ALIASING",
  SELECT_ENTITY: "SELECT_ENTITY",
  UPDATE_PREVIEW: "UPDATE_PREVIEW",

  CONFIG_RESPONSE: "CONFIG_RESPONSE",

  SET_SHADOWS: "SET_SHADOWS",
  SET_GROUND_SHADOWS: "SET_GROUND_SHADOWS",

  ADD_NOTIFICATION: "ADD_NOTIFICATION",
};

export const actions = {
  applySettings: () => (dispatch, getState) => {
    const props = getState().viewer;
    const { visualizeJS } = props;
    const viewer = visualizeJS.getViewer();

    if (viewer) {
      if (props.fps !== viewer.getEnableFPS()) {
        viewer.setEnableFPS(props.fps);
      }

      if (props.wcs !== viewer.getEnableWCS()) {
        viewer.setEnableWCS(props.wcs);
        viewer.update();
      }

      if (props.vsHighlight !== viewer.getEnableVisualStyleHighlight()) {
        viewer.setEnableVisualStyleHighlight(props.vsHighlight);
        viewer.update();
      }

      if (props.animation !== viewer.getEnableAnimation()) {
        viewer.setEnableAnimation(props.animation);
      }

      if (props.antiAliasing !== viewer.fxaaAntiAliasing3d) {
        //viewer.enableAntiaiasing = props.antiAliasing;
        viewer.fxaaAntiAliasing3d = props.antiAliasing;
        viewer.fxaaQuality = 5;
      }

      if (props.shadows !== viewer.shadows) {
        viewer.shadows = props.shadows;
        const canvas = visualizeJS.canvas;
        viewer.getActiveDevice().invalidate([0, canvas.clientWidth, canvas.clientHeight, 0]);
      }

      if (props.groundShadows !== viewer.groundShadow) {
        viewer.groundShadow = props.groundShadows;
      }
    }
  },

  updatePreview: (fileId, viewer, visualizeJS) => (dispatch) => {
    console.log("Not implemented yet");
    //const img = visualizeJS.canvas.toDataUrl()
    // createPreview(viewer, visualizeJS).then((preview) => {
    //   return api.updatePreview(fileId, preview)
    // }).then(() => { dispatch({ type: TYPES.UPDATE_PREVIEW }) })
    //   .catch(err => console.error(err));
  },

  setVisualizeJS: (instane) => (dispatch) => {
    dispatch({ type: TYPES.SET_VISUALIZEJS_INSTANCE, payload: instane });
  },
};

export const reducer = (
  state = {
    visualizejs_url: "./visualizeJS.js",
    visualizeJS: null,

    fps: false,
    wcs: true,
    vsHighlight: false,
    animation: true,
    antiAliasing: true,
    shadows: false,
    groundShadows: false,
  },
  action
) => {
  switch (action.type) {
    case TYPES.SET_VISUALIZEJS_INSTANCE:
      return { ...state, visualizeJS: action.payload };
    case TYPES.SET_OBJECT_TREE:
      return { ...state, objectTree: action.payload };
    case TYPES.SET_PROPERTIES:
      return { ...state, properties: action.payload };
    case TYPES.SET_FPS:
      return { ...state, fps: action.payload };
    case TYPES.SET_WCS:
      return { ...state, wcs: action.payload };
    case TYPES.SET_ANIMATION:
      return { ...state, animation: action.payload };
    case TYPES.SET_VS_HIGHLIGHT:
      return { ...state, vsHighlight: action.payload };
    case TYPES.SET_ANTI_ALIASING:
      return { ...state, antiAliasing: action.payload };
    case TYPES.SET_SHADOWS:
      return { ...state, shadows: action.payload };
    case TYPES.SET_GROUND_SHADOWS:
      return { ...state, groundShadows: action.payload };
    case TYPES.CONFIG_RESPONSE:
      return {
        ...state,
        visualizejs_url: action.payload.visualizejs_url || state.visualizejs_url,
      };
    default:
      return state;
  }
};
