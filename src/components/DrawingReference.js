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

import Window from "./Window";
import UploadButton from "./UploadButton";
import { DragnDrop } from "../components/DragnDrop";

class DrawingReference extends Component {
  state = {
    refs: [],
  };

  windowStyle = {
    left: "calc(50% - 300px)",
    top: "calc(50% - 265px)",
    width: "600px",
    height: "530px",
  };

  title = "Set references";

  supportFormat = ["ttf", "ttc", "otf", "shx"];

  acceptFormat = this.supportFormat.map((value) => "." + value).join(",");

  references = [];

  onCloseHandler = () => {
    if (this.props.onReject) {
      this.props.onReject();
    }
  };

  addReference = (refFile) => {
    if (!this.state.refs.find((element) => element === refFile.name)) {
      this.state.refs.push(refFile.name);
      this.references.push(refFile);
      this.setState({ refs: this.state.refs });
    }
  };

  onSelectHandler = (filesList) => {
    for (let file of filesList) {
      this.addReference(file);
    }
  };

  onRemove = (index) => {
    this.references.splice(index);
    this.setState({ refs: this.state.refs.filter((_, i) => i !== index) });
  };

  onDropHandler = (ev) => {
    ev.preventDefault();
    if (this.props.onResolve && ev.dataTransfer.files.length !== 0) {
      this.addReference(ev.dataTransfer.files[0]);
    }
  };

  onSubmits = () => {
    if (this.props.onResolve) {
      this.props.onResolve(this.references);
      this.references = [];
    }
  };

  render() {
    const supportFormats = this.supportFormat.join(" ,");

    const refsList = this.state.refs.map((name, index) => {
      return (
        <li className="list-group-item" key={index}>
          {name}
          <img
            src="icons/remove.svg"
            style={{ cursor: "pointer", float: "right" }}
            width="25px"
            height="25px"
            alt="..."
            onClick={() => this.onRemove(index)}
          ></img>
        </li>
      );
    });

    return (
      <Window
        className="object-explorer"
        title={this.title}
        resizable={false}
        style={this.windowStyle}
        onClose={this.onCloseHandler}
      >
        <DragnDrop onDrop={this.onDropHandler} />

        {this.state.refs.length === 0 ? (
          <div className="d-flex flex-row justify-content-center" onDragOver={(e) => e.preventDefault()}>
            <img src="icons/reference.svg" alt="" width="300px" height="300px"></img>
          </div>
        ) : (
          <div
            className="d-flex flex-row justify-content-center"
            onDragOver={(e) => e.preventDefault()}
            style={{ height: "300px", overflowY: "auto" }}
          >
            <ul className="list-group" style={{ width: "100%" }}>
              {refsList}
            </ul>
          </div>
        )}

        <div className="d-flex flex-row justify-content-center" style={{ marginBottom: "5px" }}>
          <UploadButton
            btnText={" or drag it here."}
            accept={this.acceptFormat}
            onSelect={this.onSelectHandler}
            multiple={true}
          ></UploadButton>
        </div>
        <div className="d-flex flex-row justify-content-center" style={{ color: "#05093B" }}>
          Supported format: {supportFormats}
        </div>

        <div className="d-flex flex-row justify-content-center" style={{ padding: "10px", color: "#05093B" }}>
          <button
            type="button"
            className="btn btn-default button-upload-file d-flex align-items-center"
            style={{ paddingLeft: "20px", paddingRight: "20px" }}
            onClick={this.onSubmits}
          >
            Upload
          </button>
        </div>
      </Window>
    );
  }
}

DrawingReference.propTypes = {
  onResolve: propTypes.func,
  onReject: propTypes.func,
};

export default DrawingReference;
