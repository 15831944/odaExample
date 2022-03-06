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
import ClientFactory from "../ClientFactory";

export const TYPES = {
  ADD_FILE: "ADD_FILE",
  REMOVE_FILE: "REMOVE_FILE",
  FILES_REQUEST: "FILES_REQUEST",
  FILES_RESPONSE: "FILES_RESPONCE",
  FILES_ERROR: "FILES_ERROR",

  SET_TOKEN: "SET_TOKEN",
  SET_PAGE: "SET_PAGE",
  SET_SUPPORT_FORMATS: "SET_SUPPORT_FORMATS",

  CONFIG_RESPONSE: "CONFIG_RESPONSE",
  ADD_NOTIFICATION: "ADD_NOTIFICATION",
};

function calcMaxPage(allSize, limit) {
  return Math.ceil(allSize / limit);
}

export const reducer = (
  state = {
    page: 0,
    maxPage: 0,
    pageSize: 16,
    totalFiles: 0,
    list: [],
    filterType: "",
    filterWord: "",
    supportFormats: ["DWG", "DGN", "DWF", "DXF", "OBJ", "PDF", "RCS", "RFA", "RVT", "STL", "VSF"],
    error: null,
    refreshFilesTimeout: 5000,
  },
  action
) => {
  switch (action.type) {
    case TYPES.FILES_REQUEST:
      return { ...state, error: null };
    case TYPES.FILES_ERROR:
      return { ...state, error: action.payload };
    case TYPES.FILES_RESPONSE:
      const { allSize, limit, list, filterWord, filterType } = action.payload;
      return {
        ...state,
        totalFiles: allSize,
        pageSize: limit,
        list: list,
        maxPage: calcMaxPage(allSize, limit),
        error: null,
        filterWord: filterWord,
        filterType: filterType,
      };
    case TYPES.ADD_FILE:
      if (state.totalFiles === 0 || state.page === calcMaxPage(state.totalFiles + 1, state.pageSize) - 1) {
        return {
          ...state,
          list: [].concat(action.payload, state.list),
          maxPage: calcMaxPage(state.totalFiles + 1, state.pageSize),
          totalFiles: state.totalFiles + 1,
        };
      } else {
        return {
          ...state,
          maxPage: calcMaxPage(state.totalFiles + 1, state.pageSize),
          totalFiles: state.totalFiles + 1,
        };
      }
    case TYPES.REMOVE_FILE:
      return {
        ...state,
        list: state.list.filter((file) => file.id !== action.payload),
        maxPage: calcMaxPage(state.totalFiles - 1, state.pageSize),
        totalFiles: state.totalFiles - 1,
      };
    case TYPES.SET_SUPPORT_FORMATS:
      return { ...state, supportFormats: action.payload };

    case TYPES.SET_PAGE:
      return { ...state, page: action.payload };
    case TYPES.CONFIG_RESPONSE:
      return {
        ...state,
        pageSize: action.payload.pageSize || state.pageSize,
        refreshFilesTimeout: action.payload.refreshFilesTimeout || state.refreshFilesTimeout,
        supportFormats: action.payload.supportFormats || state.supportFormats,
      };
    default:
      return state;
  }
};

export const actions = {
  getFiles: (name, ext) => (dispatch, getState) => {
    dispatch({ type: TYPES.FILES_REQUEST });
    const state = getState();

    return ClientFactory.get()
      .getFileList(state.files.page * state.files.pageSize, state.files.pageSize, name, ext, null, true)
      .then((result) => {
        dispatch({
          type: TYPES.FILES_RESPONSE,
          payload: { ...result, filterWord: name, filterType: ext },
        });
      })
      .catch((err) => {
        dispatch({ type: TYPES.FILES_ERROR, payload: err });
      });
  },

  setPage: (page) => (dispatch, getState) => {
    const state = getState();
    dispatch({ type: TYPES.SET_PAGE, payload: page });
    dispatch(actions.getFiles(state.files.filterWord, state.files.filterType));
  },

  setFileInfo: (info) => {
    return { type: TYPES.SET_FILE_INFO, payload: info };
  },

  removeFile: (file) => (dispatch) => {
    return file
      .delete()
      .then((_) => {
        dispatch({ type: "REMOVE_FILE", payload: file.id });
      })
      .catch((err) =>
        dispatch({
          type: TYPES.ADD_NOTIFICATION,
          payload: { type: "error", text: err.message },
        })
      );
  },
  downloadOriginalFile: (file) => (dispatch, getState) => {
    return file
      .downloadResource(`${file.id}${file.type}`)
      .then((arrayBuffer) => new Blob([arrayBuffer]))
      .then((blob) => window["download"](blob, file.name))
      .catch((err) => console.log(err));
  },
  downloadFile: (file, fileName) => (dispatch) => {
    return file
      .downloadResource(`${fileName}`)
      .then((arrayBuffer) => new Blob([arrayBuffer]))
      .then((blob) => window["download"](blob, fileName))
      .catch((err) => console.log(err));
  },

  uploadFiles: (drawingFile, references) => (dispatch, getState) => {
    const file = drawingFile;

    return Promise.resolve()
      .then(() => {
        const state = getState();
        const extRegex = /^.*\.([\w\d]+)$/;
        const match = extRegex.exec(file.name);
        const postJob =
          match &&
          match[1] &&
          state.files.supportFormats.find((format) => format.toLowerCase() === match[1].toLowerCase());
        return { file, postJob, references };
      })
      .then(async ({ file, postJob, references }) => {
        const refFileInfoList = [];

        for (let refFileData of references) {
          const response = await ClientFactory.get().uploadFile(refFileData, {
            geometry: false,
            properties: false,
          });
          refFileInfoList.push(response);
        }

        const result = await ClientFactory.get().uploadFile(file, {
          geometry: false,
          properties: false,
        });

        const refInfo = {
          references: [],
        };

        for (let refFile of refFileInfoList) {
          refInfo.references.push({ name: refFile.name, id: refFile.id });
        }

        await result.createReferences(refInfo);

        if (postJob) {
          await result.extractGeometry();
          await result.extractProperties();
        }
        dispatch({ type: TYPES.ADD_FILE, payload: result });
      })
      .catch((err) => {
        console.log(err);
        return dispatch({
          type: TYPES.ADD_NOTIFICATION,
          payload: {
            type: "error",
            text: err.message || "Failed to load file",
          },
        });
      });
  },

  requestSupportFormats: () => (dispatch) => {
    //todo add fetch formats from server
    dispatch({
      type: TYPES.SET_SUPPORT_FORMATS,
      payload: ["DWG", "DGN", "DWF", "DXF", "OBJ", "PDF", "RCS", "RFA", "RVT"],
    });
  },
};
