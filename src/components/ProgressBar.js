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

export default class ProgressBar extends Component {
  render() {
    let { progress } = this.props;

    return (
      <div className={"col-12 upload-progress"} style={{ opacity: !progress || progress >= 100 ? 0 : 1 }}>
        <div className="progress" style={{ height: "2px" }}>
          <div
            className="progress-bar"
            role="progressbar"
            aria-valuenow={progress}
            style={{ width: progress + "%" }}
            aria-valuemin="0"
            aria-valuemax="100"
          ></div>
        </div>
      </div>
    );
  }
}

ProgressBar.propTypes = {
  progress: PropTypes.number.isRequired,
};
