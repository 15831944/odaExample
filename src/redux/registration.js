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
  REGISTER_REQUEST: "REGISTER_REQUEST",
  REGISTER_RESPONSE: "REGISTER_RESPONSE",
  REGISTER_ERROR: "REGISTER_ERROR",
  ADD_NOTIFICATION: "ADD_NOTIFICATION",
};

export const actions = {
  register:
    ({ email, username, password }) =>
    async (dispatch, getState) => {
      const state = getState();
      const config = state.config;

      dispatch({ type: TYPES.REGISTER_REQUEST });

      const json = JSON.stringify({ username, email, password });

      return fetch(`${config.data.registration_host}/register`, {
        method: "POST",
        body: json,
        headers: { "Content-Type": "application/json" },
      })
        .then((responce) => responce.json())
        .then((responce) => {
          if (responce.isOk === false && responce.description) {
            dispatch({
              type: TYPES.REGISTER_ERROR,
              payload: responce.description,
            });
            dispatch({
              type: TYPES.ADD_NOTIFICATION,
              payload: { type: "error", text: responce.description },
            });
          } else {
            dispatch({ type: TYPES.REGISTER_RESPONSE, payload: responce });
            dispatch({
              type: TYPES.ADD_NOTIFICATION,
              payload: { type: "success", text: "User has been registered" },
            });
          }
        })
        .catch((err) => {
          dispatch({ type: TYPES.REGISTER_ERROR, payload: err.message });
          dispatch({
            type: TYPES.ADD_NOTIFICATION,
            payload: { type: "error", text: err.message },
          });
        });
    },

  clearError: () => (dispatch) => {
    dispatch({ type: TYPES.REGISTER_ERROR, payload: null });
  },
};

export const reducer = (
  state = {
    loading: false,
    error: null,
    data: null,
    emailVerify: false,
  },
  action
) => {
  switch (action.type) {
    case TYPES.REGISTER_REQUEST:
      return {
        ...state,
        loading: true,
        error: null,
        data: null,
        emailVerify: false,
      };
    case TYPES.REGISTER_RESPONSE:
      return {
        ...state,
        loading: false,
        error: null,
        data: action.payload,
        emailVerify: action.payload.emailVerify,
      };
    case TYPES.REGISTER_ERROR:
      return {
        ...state,
        loading: false,
        error: action.payload,
        data: null,
        emailVerify: false,
      };

    default:
      return state;
  }
};
