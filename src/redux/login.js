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
  LOGIN_REQUEST: "LOGIN_REQUEST",
  LOGIN_RESPONSE: "LOGIN_RESPONSE",
  LOGIN_ERROR: "LOGIN_ERROR",
  LOGOUT: "LOGOUT",

  ADD_NOTIFICATION: "ADD_NOTIFICATION",
};

export const actions = {
  loginFromLocalStorage: () => async (dispatch) => {
    try {
      const json = window.localStorage.getItem("user");
      if (json) {
        let userData = JSON.parse(json);
        return dispatch(actions.loginFromUserData(userData));
      }
    } catch (err) {
      localStorage.removeItem("user");
    }
  },

  loginFromUserData: (userData) => async (dispatch) => {
    try {
      await ClientFactory.get().loginWithToken(userData.tokenInfo.token);
      const user = ClientFactory.get().getCurrentUser();
      dispatch({ type: TYPES.LOGIN_RESPONSE, payload: user });
    } catch (err) {
      localStorage.removeItem("user");
    }
  },

  login:
    ({ email, password, remember }) =>
    async (dispatch) => {
      dispatch({ type: TYPES.LOGIN_REQUEST });
      try {
        const user = await ClientFactory.get().signInWithEmail(email, password);
        remember && localStorage.setItem("user", JSON.stringify(user.data));
        dispatch({ type: TYPES.LOGIN_RESPONSE, payload: user });
      } catch (err) {
        localStorage.removeItem("user");
        dispatch({ type: TYPES.LOGIN_ERROR, payload: err.message });
        dispatch({
          type: TYPES.ADD_NOTIFICATION,
          payload: { type: "error", text: err.message },
        });
      }
    },

  clearError: () => (dispatch) => {
    dispatch({ type: TYPES.LOGIN_ERROR, payload: null });
  },

  logout: () => (dispatch) => {
    localStorage.removeItem("user");
    dispatch({ type: TYPES.LOGOUT });
  },
};

export const reducer = (
  state = {
    loading: false,
    error: null,
    data: null,
  },
  action
) => {
  switch (action.type) {
    case TYPES.LOGIN_REQUEST:
      return { ...state, loading: true, error: null, data: null };
    case TYPES.LOGIN_RESPONSE:
      return { ...state, loading: false, error: null, data: action.payload };
    case TYPES.LOGIN_ERROR:
      return { ...state, loading: false, error: action.payload, data: null };
    case TYPES.LOGOUT:
      return { ...state, loading: false, error: null, data: null };
    default: {
      if (action.type && action.type.match(/_?error_?/gi)) {
        if (action.payload && action.payload.code === 401) {
          return reducer(state, { type: TYPES.LOGOUT });
        }
      }
      return state;
    }
  }
};
