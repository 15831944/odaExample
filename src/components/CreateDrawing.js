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

import "antd/dist/antd.css";
import { Alert } from "antd";

const WINDOW_STYLE = {
  left: "calc(50% - 250px)",
  top: "calc(50% - 225px)",
  width: "550px",
  height: "450px",
  maxWidth: "550px",
  maxHeight: "450px",
};

const SUPPORT_FORMAT_STYLE = {
  width: "50px",
  margin: 0,
  padding: "4px 8px",
  textAlign: "center",
};

class CreateDrawing extends Component {
  title = "Upload file";

  state = {
    isError: false,
  };

  constructor(props) {
    super(props);
    this.supportFormat = this.props.supportFormats;
    this.acceptFormat = this.supportFormat.map((value) => value.toLowerCase()).join(", ");
  }

  checkFileFormat = (name) => {
    const ext = name.split(".").pop();
    const upperExt = ext.toUpperCase();
    if (this.supportFormat.indexOf(upperExt) === -1) {
      this.setState({ isError: true });
      return false;
    }
    this.setState({ isError: false });
    return true;
  };

  onCloseHandler = () => {
    if (this.props.onReject) {
      this.props.onReject();
    }
  };

  onSelectHandler = (filesList) => {
    if (this.props.onResolve && filesList.length !== 0) {
      this.checkFileFormat(filesList[0].name) && this.props.onResolve(filesList[0]);
    }
  };

  onDropHandler = (ev) => {
    ev.preventDefault();
    if (this.props.onResolve && ev.dataTransfer.files.length !== 0) {
      this.checkFileFormat(ev.dataTransfer.files[0].name) && this.props.onResolve(ev.dataTransfer.files[0]);
    }
  };

  render() {
    const supportFormats = this.supportFormat.map((value, index) => {
      return (
        <div className="alert alert-secondary d-flex" style={SUPPORT_FORMAT_STYLE} key={index}>
          {value}
        </div>
      );
    });

    return (
      <Window
        className="object-explorer"
        title={this.title}
        resizable={false}
        style={WINDOW_STYLE}
        onClose={this.onCloseHandler}
      >
        <DragnDrop onDrop={this.onDropHandler} />
        <div className="d-flex flex-row justify-content-center" onDragOver={(e) => e.preventDefault()}>
          <img src="icons/upload.svg" alt="" width="256px" height="256px"></img>
        </div>
        <div className="d-flex flex-row justify-content-center" style={{ marginBottom: "5px" }}>
          <UploadButton btnText={" or drag it here."} onSelect={this.onSelectHandler}></UploadButton>
        </div>

        {!this.state.isError ? (
          <div
            className="d-flex flex-row flex-wrap justify-content-between"
            style={{
              color: "#05093B",
              gap: "8px",
              width: "400px",
              margin: "auto",
            }}
          >
            {supportFormats}
          </div>
        ) : (
          <Alert
            message="Unsupported format"
            description={`use ${this.acceptFormat}`}
            type="error"
            onClose={() => this.setState({ isError: false })}
            closable
          />
        )}
      </Window>
    );
  }
}

CreateDrawing.propTypes = {
  onResolve: propTypes.func,
  onReject: propTypes.func,
};

export default CreateDrawing;
