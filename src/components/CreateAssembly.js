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
import Window from "./Window";

import ClientFactory from "./../ClientFactory";

class CreateAssembly extends Component {
  state = {
    files: [],
    isValid: true,
  };

  windowStyle = {
    left: "calc(50% - 300px)",
    top: "calc(50% - 275px)",
    width: "600px",
    height: "550px",
  };

  title = "Create new assembly";

  constructor(props) {
    super(props);
    this.nameInput = React.createRef();
  }

  async componentDidMount() {
    const files = await ClientFactory.get().getFileList(0, this.props.files.length, null, null, this.props.files);
    this.setState({ files: files.list });
  }

  onRemove = (index) => {
    this.setState({
      files: this.state.files.filter((_, i) => i !== index),
    });
  };

  onSubmit = () => {
    if (this.nameInput.current.value === "") {
      this.setState({ isValid: false });
    } else {
      this.props.onResolve(this.nameInput.current.value, this.state.files);
    }
  };

  render() {
    const filesList = this.state.files.map((file, index) => {
      return (
        <li className="list-group-item" key={index}>
          {file.name}
          {this.state.files.length > 2 ? (
            <span
              className="material-icons"
              style={{ cursor: "pointer", float: "right" }}
              onClick={() => this.onRemove(index)}
            >
              close
            </span>
          ) : null}
        </li>
      );
    });

    return (
      <Window
        className="object-explorer"
        title={this.title}
        resizable={false}
        style={this.windowStyle}
        onClose={this.props.onCloseHandler}
      >
        <div style={{ padding: "5px" }}>
          <div style={{ marginBottom: "10px", height: "90px" }}>
            <label htmlFor="input-name-assembly" className="form-label">
              Name:
            </label>
            <input
              type="text"
              className={this.state.isValid ? "form-control" : "form-control is-invalid"}
              id="input-name-assembly"
              ref={this.nameInput}
            />
            <div className="invalid-feedback">Please choose a assembly name</div>
          </div>

          <div>Files:</div>

          <div className="d-flex flex-row justify-content-center" style={{ height: "270px", overflowY: "auto" }}>
            <ul className="list-group" style={{ width: "100%", padding: "0" }}>
              {filesList}
            </ul>
          </div>

          <div className="d-flex flex-row justify-content-center" style={{ padding: "10px", color: "#05093B" }}>
            <button
              type="button"
              className="btn btn-default button-upload-file d-flex align-items-center"
              style={{ paddingLeft: "20px", paddingRight: "20px" }}
              onClick={this.onSubmit}
            >
              Create
            </button>
          </div>
        </div>
      </Window>
    );
  }
}

export default CreateAssembly;
