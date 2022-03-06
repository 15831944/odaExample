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
import PropTypes from "prop-types";

import jQuery from "jquery";
import "jquery-ui-bundle";

window.jQuery = window.$ = jQuery;

class Window extends Component {
  ref = React.createRef();
  close = () => {
    if (this.props.onClose) {
      this.props.onClose();
    }
  };

  componentDidMount() {
    const { resizable } = this.props;
    let resizableVar = resizable === undefined ? true : resizable;

    console.log("$(this.ref.current)", window.$(this.ref.current));
    if (resizableVar) {
      window.$(this.ref.current).resizable();
    }

    window.$(this.ref.current).draggable({
      handle: ".ui-draggable-handle",
      cursor: "move",
      containment: "window",
    });
  }

  render() {
    const { className, style } = this.props;
    return (
      <div
        ref={this.ref}
        className={"window-dialog card ui-resizable ui-draggable " + (className ? className : "")}
        style={style}
      >
        <div className="ui-draggable-handle card-header window-dialog-head">
          {this.props.title}
          <button
            type="button"
            className="close btn-close"
            data-dismiss="modal"
            aria-hidden="true"
            onClick={this.close}
          >
            ×
          </button>
        </div>
        <div className="card-body overflow-auto" style={{ padding: "5px" }}>
          {this.props.children}
        </div>
        <div className="ui-resizable-e ui-resizable-handle" style={{ zIndex: 9999 }}></div>
        <div className="ui-resizable-s ui-resizable-handle" style={{ zIndex: 9999 }}></div>
      </div>
    );
  }
}

Window.propTypes = {
  title: PropTypes.string.isRequired,
  onClose: PropTypes.func,
};

export default Window;
