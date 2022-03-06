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
import { connect } from "react-redux";
import { actions as notification } from "../redux/notification";

const types = {
  error: "danger",
  success: "success",
  warning: "warning",
};

class Notification extends Component {
  state = { show: true };

  close = () => {
    this.setState({ show: false });
    clearTimeout(this.timeoutID);
    if (this.props.onClose) {
      this.props.onClose();
    }
  };
  timeoutID = -1;
  timeout = 5000;

  componentDidMount() {
    this.timeoutID = setTimeout(() => {
      if (this.props.onClose) this.props.onClose();
    }, this.timeout);
  }

  componentWillUnmount() {
    clearTimeout(this.timeoutID);
  }

  render() {
    return (
      <div
        ref={this.ref}
        className={`alert alert-${types[this.props.type]} alert-dismissible fade ${this.state.show ? "show" : "hide"}`}
        role="alert"
      >
        <strong>{this.props.type}:</strong> {this.props.text}
        <button type="button" className="close" data-dismiss="alert" aria-label="Close" onClick={this.close}>
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
    );
  }
}

class Notifications extends Component {
  render() {
    const items = this.props.list.map((item, index) => (
      <Notification key={item.id} {...item} onClose={() => this.props.removeNotification(item.id)} />
    ));

    return <div className="notifications">{items}</div>;
  }
}

export default connect(
  (state) => state.notifications,
  (dispatch) => ({
    removeNotification: (id) => dispatch(notification.removeNotification(id)),
  })
)(Notifications);
