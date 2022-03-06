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
import { TYPES, reducer } from "./config";

describe("config", () => {
  it("CONFIG_REQUEST", () => {
    const state = reducer(undefined, { type: TYPES.CONFIG_REQUEST });
    expect(state).toEqual({ loading: true, error: null, data: null });
  });

  it("CONFIG_RESPONCE", () => {
    const config = {
      api_host: "api_host",
      registration_host: "registration_host",
    };
    const state = reducer(undefined, {
      type: TYPES.CONFIG_RESPONSE,
      payload: config,
    });
    expect(state).toEqual({ loading: false, error: null, data: config });
  });

  it("CONFIG_ERROR", () => {
    const error = {};
    const state = reducer(undefined, {
      type: TYPES.CONFIG_ERROR,
      payload: error,
    });
    expect(state).toEqual({ loading: false, error: error, data: null });
  });
});
