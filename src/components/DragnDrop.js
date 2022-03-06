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

export class DragnDrop extends Component {
  constructor(props) {
    super(props);

    this.state = {
      style: {
        width: "100%",
        height: "100%",
        position: "fixed",
        zIndex: -9999,
        top: 0,
        left: 0,
        overflow: "auto",
        backgroundColor: "none",
        outline: "none",
        outlineOffset: "0",
        opacity: "0.0",
      },
    };
  }

  onDragOver = (ev) => {
    this.setState({
      style: {
        width: "100%",
        height: "100%",
        position: "fixed",
        zIndex: 9999,
        top: 0,
        left: 0,
        overflow: "auto",
        backgroundColor: "white",
        outline: "2px dashed black",
        outlineOffset: "-10px",
        opacity: "0.5",
      },
    });
    ev.preventDefault();
  };

  onDragLeave = (ev) => {
    this.setState({
      style: {
        width: "100%",
        height: "100%",
        position: "fixed",
        zIndex: -9999,
        top: 0,
        left: 0,
        overflow: "auto",
        backgroundColor: "none",
        outline: "none",
        outlineOffset: "0",
        opacity: "0.0",
      },
    });
    ev.preventDefault();
  };

  onSelfDrag = (ev) => {
    this.onDragLeave(ev);
    this.props.onDrop(ev);
  };

  render() {
    const { children } = this.props;

    return (
      <div
        style={this.state.style}
        onDrop={this.onSelfDrag}
        onDragOver={this.onDragOver}
        onDragLeave={this.onDragLeave}
      >
        {children}
      </div>
    );
  }
}
