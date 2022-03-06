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
  PROPERTIES_REQUEST: "PROPERTIES_REQUEST",
  PROPERTIES_RESPONSE: "PROPERTIES_RESPONSE",
  PROPERTIES_ERROR: "PROPERTIES_ERROR",
  PROPERTIES_CLEAR: "PROPERTIES_CLEAR",
};

export const actions = {
  getProperties: (file, entity) => (dispatch) => {
    dispatch({ type: TYPES.PROPERTIES_REQUEST });
    return Promise.resolve(file)
      .then((file) => file.getProperty(entity))
      .then((result) => dispatch({ type: TYPES.PROPERTIES_RESPONSE, payload: result }))
      .catch((err) => {
        dispatch({ type: TYPES.PROPERTIES_ERROR, payload: err });
      });
  },
  clearProperties: () => (dispatch) => {
    dispatch({ type: TYPES.PROPERTIES_CLEAR, payload: null });
  },
};

export const reducer = (
  state = {
    current: {
      loading: false,
      error: null,
      data: {},
    },
  },
  action
) => {
  switch (action.type) {
    case TYPES.PROPERTIES_REQUEST:
      return { ...state, current: { loading: true, error: null, data: null } };
    case TYPES.PROPERTIES_RESPONSE:
      return {
        ...state,
        current: { loading: false, error: null, data: action.payload },
      };
    case TYPES.PROPERTIES_ERROR:
      return {
        ...state,
        current: { loading: false, error: action.payload, data: null },
      };
    case TYPES.PROPERTIES_CLEAR:
      return { ...state, current: { loading: false, error: null, data: {} } };

    default:
      return state;
  }
};
