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
import propTypes from "prop-types";

class UploadButton extends Component {
  inputRef = React.createRef();

  handleSelectFile = () => {
    if (this.props.onSelect) {
      this.props.onSelect(this.inputRef.current.files);
      this.inputRef.current.value = null;
    }
  };

  render() {
    return (
      <form className="box">
        <div className="box__input">
          <input
            ref={this.inputRef}
            type="file"
            className="d-none"
            onChange={this.handleSelectFile}
            multiple={this.props.multiple}
          />
          <label htmlFor="file">
            <strong className="choose-file" onClick={() => this.inputRef.current.click()}>
              Choose a file
            </strong>
          </label>
          <span className="ng-binding" style={{ color: "#05093B" }}>
            {this.props.btnText}
          </span>
        </div>
      </form>
    );
  }
}

UploadButton.propTypes = {
  onSelect: propTypes.func,
  btnText: propTypes.string,
  multiple: propTypes.bool,
};

export default UploadButton;
