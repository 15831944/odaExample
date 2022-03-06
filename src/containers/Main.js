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
import React, { Component } from "react";
import ViewerPage from "./../viewer/ViewerPage";
import Notifications from "./Notifications";
import { HashRouter, Switch, Route, Redirect } from "react-router-dom";
import RegisterPage from "./RegisterPage";
import LoginPage from "./LoginPage";
import { connect } from "react-redux";
import { actions as config } from "../redux/config";
import UserMenu from "./UserMenu";
import Header from "../components/Header";

import { Layout } from "antd";

import SideNavigateMenuAnt from "./SideNavigateMenuAnt";
import AssembliesListComponent from "./AssembliesListComponent/AssembliesListComponent";
import { OptionComponent } from "./OptionComponent";
import JobsComponent from "./JobsComponent/JobsComponent";
import FilesListComponent from "./FilesListComponent/FilesListComponent";

const { Content } = Layout;

class Main extends Component {
  componentDidMount() {
    this.props.loadConfig();
  }

  render() {
    if (!this.props.loaded) {
      return null;
    }

    const user = this.props.login.data;

    return (
      <>
        <HashRouter>
          <Switch>
            <PublicRoute path="/login" fallback="/" user={user}>
              <LoginPage />
            </PublicRoute>
            <PublicRoute path="/register" fallback="/" user={user}>
              <RegisterPage />
            </PublicRoute>
            <PrivateRoute path="/file/:fileId" fallback="/login" user={user}>
              <ViewerPage />
            </PrivateRoute>
            <PrivateRoute path="/assembly/:assemblyId" fallback="/login" user={user}>
              <ViewerPage />
            </PrivateRoute>

            <PrivateRoute exact path="*" fallback="/login" user={user}>
              <Header>
                <UserMenu></UserMenu>
              </Header>
              <Layout style={{ background: "white" }}>
                <SideNavigateMenuAnt active="Files"></SideNavigateMenuAnt>
                <Content>
                  <PrivateRoute exact path="/jobs" fallback="/login" user={user}>
                    <JobsComponent></JobsComponent>
                  </PrivateRoute>
                  <PrivateRoute exact path="/assemblies" fallback="/login" user={user}>
                    <AssembliesListComponent></AssembliesListComponent>
                  </PrivateRoute>
                  <PrivateRoute exact path="/settings" fallback="/login" user={user}>
                    <OptionComponent></OptionComponent>
                  </PrivateRoute>
                  <PrivateRoute exact path="/" fallback="/login" user={user}>
                    <FilesListComponent></FilesListComponent>
                  </PrivateRoute>
                </Content>
              </Layout>
            </PrivateRoute>
            <Redirect from="*" to="/" />
          </Switch>
        </HashRouter>
        <Notifications />
      </>
    );
  }
}

function PublicRoute({ path, fallback, user, exact, children }) {
  return (
    <Route
      path={path}
      exact={exact}
      render={({ location }) => {
        if (user) {
          if (location.state && location.state.from) {
            return <Redirect to={{ pathname: location.state.from.pathname }} />;
          } else {
            return <Redirect to={fallback} />;
          }
        } else {
          return children;
        }
      }}
    />
  );
}

function PrivateRoute({ path, fallback, user, exact, children }) {
  return (
    <Route
      push
      exact={exact}
      path={path}
      render={({ location }) => {
        if (!user) {
          return <Redirect to={{ pathname: fallback, state: { from: location } }} />;
        } else {
          return children;
        }
      }}
    />
  );
}

export default connect(
  (state) => ({
    login: state.login,
    loaded: state.config.data,
  }),
  (dispatch) => ({
    loadConfig: () => dispatch(config.loadConfig()),
  })
)(Main);
