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

export class DropUp extends Component {
  constructor(props) {
    super(props);
    this.state = { current: this.props.list[0] || {} };
  }

  render() {
    const { changeCurrent = false, hideCurrent = true, list, title, className } = this.props;
    const current = this.state.current;

    const handleAction = (dropdown) => {
      if (changeCurrent) {
        this.setState({ current: dropdown }, () => {
          if (this.state.current.handle) {
            this.state.current.handle();
          }
        });
      } else {
        if (dropdown.handle) {
          dropdown.handle();
        }
      }
    };

    const droplist = !hideCurrent ? list : list.filter((dropdown) => dropdown !== current);
    const dropDownList = droplist.map((dropdown, index) => {
      return (
        <div
          key={index}
          title={dropdown.title}
          className="dropdown-item"
          style={{ padding: "0.15rem 0.5rem" }}
          onClick={() => handleAction(dropdown)}
        >
          <div className={dropdown.className}>{dropdown.text ? dropdown.text : null}</div>
        </div>
      );
    });

    return (
      <div title={current.title || title} className="btn-group dropup">
        <div className="dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
          <div className="d-flex justify-content-center p-1">
            <div className={current.className || className}></div>
            <div className="action-item-indicator"></div>
          </div>
        </div>
        <div className="dropdown-menu" style={{ minWidth: "inherit" }}>
          {dropDownList}
        </div>
      </div>
    );
  }
}
DropUp.propTypes = {
  list: propTypes.array.isRequired,
};
