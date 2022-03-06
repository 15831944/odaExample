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
import { TYPES, reducer } from "./files";

const file = {
  id: "5de915aecb19f3000842f640",
  name: "3D_TEST.dwg",
  size: 34240,
  type: ".dwg",
  owner: "5de915a4cb19f3000842f63f",
  metadata: [
    {
      name: "Model",
      database: "a559b87068921eec05086ce5485e9784.vsf.db.tcs",
      geometry: [
        "a559b87068921eec05086ce5485e9784.vsf.0.tcs",
        "a559b87068921eec05086ce5485e9784.vsf.1.tcs",
        "a559b87068921eec05086ce5485e9784.vsf.2.tcs",
      ],
      default: true,
    },
    {
      name: "Paper 1",
      database: "836f20593bb9d816c11b5b89a3321d02.vsf.db.tcs",
      geometry: ["836f20593bb9d816c11b5b89a3321d02.vsf.0.tcs"],
      default: false,
    },
  ],
  exports: [],
  properties: false,
  created: "2019-12-05T14:35:26.152Z",
  preview: "",
  version: 0,
};

describe("files test", () => {
  it("ADD_FILE", () => {
    const state = reducer(undefined, {});
    const nextState = reducer(state, {
      type: TYPES.ADD_FILE,
      payload: file,
    });

    expect(nextState.list[0]).toMatchObject(file);
  });

  it("FILES_REQUEST", () => {
    const state = reducer(undefined, {});
    state.error = {};

    const nextState = reducer(state, {
      type: TYPES.FILES_REQUEST,
    });
    expect(nextState.error).toBeNull();
  });

  it("FILES_ERROR", () => {
    const state = reducer(undefined, {});
    state.error = null;

    const nextState = reducer(state, {
      type: TYPES.FILES_ERROR,
      payload: { message: "Test Error" },
    });
    expect(nextState.error).toEqual({ message: "Test Error" });
  });

  it("FILES_RESPONSE", () => {
    const state = reducer(undefined, {});
    state.error = {};
    const result = {
      allSize: 1,
      limit: 1,
      size: 1,
      start: 0,
      list: [file],
    };

    const nextState = reducer(state, {
      type: TYPES.FILES_RESPONSE,
      payload: result,
    });

    expect(nextState.list.length).toBeGreaterThan(0);
    expect(nextState.error).toBeNull();
  });

  it("REMOVE_FILE", () => {
    const state = reducer(undefined, {});

    let nextState = reducer(state, {
      type: TYPES.ADD_FILE,
      payload: file,
    });

    nextState = reducer(nextState, {
      type: TYPES.REMOVE_FILE,
      payload: file.id,
    });
    expect(nextState.list.length).toEqual(0);
  });

  it("SET_SUPPORT_FORMATS", () => {
    const state = reducer(undefined, {});
    const formats = ["DWG", "DGN"];
    let nextState = reducer(state, {
      type: TYPES.SET_SUPPORT_FORMATS,
      payload: formats,
    });

    expect(nextState.supportFormats).toEqual(expect.arrayContaining(formats));
  });

  it("SET_PAGE", () => {
    const state = reducer(undefined, {});
    const page = 0;
    const nextState = reducer(state, {
      type: TYPES.SET_PAGE,
      payload: page,
    });
    expect(nextState.page).toEqual(page);
  });

  it("CONFIG_RESPONSE", () => {
    const state = reducer(undefined, {});
    const config = {
      pageSize: 1,
      refreshFilesTimeout: 10000,
    };
    const nextState = reducer(state, {
      type: TYPES.SET_PAGE,
      payload: { ...config },
    });
    expect(nextState.page).toEqual(config);
  });
});
