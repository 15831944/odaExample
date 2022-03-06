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
  CONFIG_REQUEST: "CONFIG_REQUEST",
  CONFIG_RESPONSE: "CONFIG_RESPONSE",
  CONFIG_ERROR: "CONFIG_ERROR",
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
    case TYPES.CONFIG_REQUEST:
      return { loading: true, error: null, data: null };
    case TYPES.CONFIG_RESPONSE:
      return { loading: false, error: null, data: action.payload };
    case TYPES.CONFIG_ERROR:
      return { loading: false, error: action.payload, data: null };
    default:
      return state;
  }
};

export const actions = {
  loadConfig: () => async (dispatch) => {
    try {
      dispatch({ type: TYPES.CONFIG_REQUEST });
      const response = await fetch("./config.json");
      if (response.status !== 200) {
        throw new Error(response.statusText);
      }
      const config = await response.json();
      await ClientFactory.initialize(config.api_host);
      ClientFactory.setConfig(config);
      dispatch({ type: TYPES.CONFIG_RESPONSE, payload: config });
    } catch (err) {
      dispatch({ type: TYPES.CONFIG_ERROR, payload: err });
    }
  },
};
