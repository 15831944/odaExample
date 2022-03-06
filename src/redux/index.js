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
import { createStore, applyMiddleware } from "redux";
import { combineReducers } from "redux";
import thunk from "redux-thunk";
import logger from "redux-logger";

import * as login from "./login";
import * as registration from "./registration";
import * as files from "./files";
import * as properties from "./properties";
import * as notifications from "./notification";
import * as viewer from "./viewer";
import * as config from "./config";
import * as objectTree from "./objectTree";

const reducer = combineReducers({
  files: files.reducer,
  viewer: viewer.reducer,
  objectTree: objectTree.reducer,
  properties: properties.reducer,
  notifications: notifications.reducer,
  login: login.reducer,
  registration: registration.reducer,
  config: config.reducer,
});

const middlewares = [thunk];
if (process.env.NODE_ENV === "development") {
  middlewares.push(logger);
}

export const store = createStore(reducer, applyMiddleware(...middlewares));
