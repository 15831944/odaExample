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

export class ContextMenu extends Component {
  constructor(props) {
    super(props);
    this.state = {
      visible: false,
      x: 0,
      y: 0,
    };
    this.eventsConnection = props.eventsConnection;
  }

  handleClick = () => {
    if (this.state.visible) {
      this.setState({ visible: false });
    }
  };

  onContextMenu = (event) => {
    event.preventDefault();

    function clamp(val, min, max) {
      return Math.min(Math.max(val, min), max);
    }

    const width = event.target.clientWidth;
    const height = event.target.clientHeight;

    let clickX = clamp(event.clientX, 0, width - 200);
    let clickY = clamp(event.clientY, 0, height - 200);

    this.setState({ visible: true, x: clickX, y: clickY });
  };

  componentDidMount() {
    this.canvas = document.getElementById("canvas");
    this.canvas.addEventListener("click", this.handleClick);
    this.canvas.addEventListener("contextmenu", this.onContextMenu);
  }

  componentWillUnmount() {
    this.canvas.removeEventListener("click", this.handleClick);
    this.canvas.removeEventListener("contextmenu", this.onContextMenu);
  }

  returnMenu(items) {
    const myStyle = {
      position: "absolute",
      top: `${this.state.y}px`,
      left: `${this.state.x + 5}px`,
      zIndex: "2000",
    };

    return (
      <div className="context-menu" style={myStyle}>
        {items.map((item) => {
          return (
            <div
              key={item.label}
              className="context-menu-item"
              onClick={() => {
                item.action();
                this.handleClick();
              }}
            >
              {" "}
              <img src={item.icons} alt="" width="30" height="30" /> {item.label}
            </div>
          );
        })}
      </div>
    );
  }

  actionsList = [
    {
      label: "Unselect",
      icons: "icons/unselected.svg",
      action: () => this.eventsConnection.onUnselect.next(),
    },
    {
      label: "Isolate",
      icons: "icons/isolate.svg",
      action: () => this.eventsConnection.onIsolateSelectedObjects.next(),
    },
    {
      label: "Hide",
      icons: "icons/hide.svg",
      action: () => this.eventsConnection.onHideSelectedObjects.next(),
    },
    {
      label: "Show all",
      icons: "icons/unisolate.svg",
      action: () => this.eventsConnection.onShowAll.next(),
    },
    {
      label: "Explode",
      icons: "icons/explode.svg",
      action: () => this.eventsConnection.onExplode.next(),
    },
    {
      label: "Collect",
      icons: "icons/collect.svg",
      action: () => this.eventsConnection.onCollect.next(),
    },
    {
      label: "Regeneration",
      icons: "icons/regen.svg",
      action: () => this.eventsConnection.onRegeneration.next(),
    },
    {
      label: "Create preview",
      icons: "icons/preview.svg",
      action: () => this.eventsConnection.onCreatePreview.next(),
    },
  ];

  render() {
    return (
      <div onMouseEnter={this.mouseEnter} onMouseLeave={this.mouseLeave}>
        {this.state.visible ? this.returnMenu(this.actionsList) : null}
      </div>
    );
  }
}
