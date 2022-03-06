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
import { TYPES, reducer } from "./notification";

describe("notification", () => {
  it("ADD_NOTIFICATION", () => {
    const notification = { type: "error", text: "text" };
    const state = reducer(undefined, {
      type: TYPES.ADD_NOTIFICATION,
      payload: notification,
    });
    expect(state).toEqual({ nextId: 1, list: [{ ...notification, id: 0 }] });
  });

  it("REMOVE_NOTIFICATION", () => {
    const notification = { type: "error", text: "text" };
    let state = reducer(undefined, {
      type: TYPES.ADD_NOTIFICATION,
      payload: notification,
    });
    state = reducer(state, { type: TYPES.REMOVE_NOTIFICATION, payload: 0 });
    expect(state).toEqual({ nextId: 1, list: [] });
  });
});
