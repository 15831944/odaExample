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
  ADD_NOTIFICATION: "ADD_NOTIFICATION",
  REMOVE_NOTIFICATION: "REMOVE_NOTIFICATION",
};

export const actions = {
  addNotification: (type, text) => (dispatch) => {
    dispatch({ type: TYPES.ADD_NOTIFICATION, payload: { type, text } });
  },
  removeNotification: (id) => (dispatch) => {
    dispatch({ type: TYPES.REMOVE_NOTIFICATION, payload: id });
  },
};

export const reducer = (
  state = {
    list: [],
    nextId: 0,
  },
  action
) => {
  switch (action.type) {
    case TYPES.ADD_NOTIFICATION:
      return {
        ...state,
        list: state.list.concat({ ...action.payload, id: state.nextId }),
        nextId: ++state.nextId,
      };
    case TYPES.REMOVE_NOTIFICATION:
      return {
        ...state,
        list: state.list.filter((item) => item.id !== action.payload),
      };
    default:
      return state;
  }
};
