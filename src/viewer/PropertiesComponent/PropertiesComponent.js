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
import Window from "../../components/Window";
import { SpinnerWithText } from "../../components/SpinnerWithText";
import { SubscribeSubjectContext } from "../../utils/SubscribeSubjectContext";

const defaultState = {
  isLoading: false,
  properties: {},
  error: null,
};

export class PropertiesComponent extends Component {
  state = { ...defaultState };

  constructor(props) {
    super(props);
    this.eventsConnection = props.eventsConnection;
    this.subscribeSubjectContext = new SubscribeSubjectContext();

    this.subscribeSubjectContext.subscribe(this.eventsConnection.loadingProperties, (isLoading) =>
      this.setState({ isLoading, properties: {}, error: null })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.completeLoadProperties, (properties) =>
      this.setState({ isLoading: false, properties: properties, error: null })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.errorLoadProperties, (error) =>
      this.setState({ isLoading: false, properties: {}, error: error })
    );
  }

  componentWillUnmount() {
    this.subscribeSubjectContext.unsubscribe();
  }

  renderProperties(obj) {
    const properties = Object.keys(obj).map((name, index) => {
      let value = typeof obj[name] === "object" ? JSON.stringify(obj[name]).replace(/[{}"]/gi, "") : obj[name];
      return (
        <tr key={index}>
          <td>{name}</td>
          <td>{value}</td>
        </tr>
      );
    });

    return (
      <table className="table table-striped" style={{ color: "#05093B" }}>
        <tbody>{properties}</tbody>
      </table>
    );
  }

  renderError(error) {
    return (
      <div className="col p-2">
        <div className="d-flex justify-content-center text-danger">{error.message}</div>
      </div>
    );
  }

  renderLoading() {
    return (
      <div className="col justify-content-center">
        <SpinnerWithText>
          <span>Loading...</span>
        </SpinnerWithText>
      </div>
    );
  }

  render() {
    const { isLoading, properties, error } = this.state;

    let content = null;
    if (isLoading) {
      content = this.renderLoading();
    } else if (error) {
      content = this.renderError(error);
    } else {
      content = this.renderProperties(properties);
    }

    return (
      <Window className="properties-explorer" title="Properties" onClose={() => this.eventsConnection.onClose.next()}>
        {content}
      </Window>
    );
  }
}
