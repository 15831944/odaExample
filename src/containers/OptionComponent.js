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
import ClientFactory from "./../ClientFactory";

import { Component } from "react";

import "antd/dist/antd.css";

import { Switch } from "antd";
import { Row, Col } from "antd";
import { Card, Button } from "antd";

export class OptionComponent extends Component {
  state = {
    showFPS: false,
    showWCS: false,
    cameraAnimation: false,
    antialiasing: false,
    shadows: false,
    groundShadow: false,
    ambientOcclusion: false,
  };

  componentDidMount() {
    const client = ClientFactory.get();
    this.setState({
      showFPS: client.options.showFPS,
      showWCS: client.options.showWCS,
      cameraAnimation: client.options.cameraAnimation,
      antialiasing: client.options.antialiasing,
      shadows: client.options.shadows,
      groundShadow: client.options.groundShadow,
      ambientOcclusion: client.options.ambientOcclusion,
    });
  }

  onChange(name) {
    const client = ClientFactory.get();
    client.options[name] = !client.options[name];
    const changeState = {};
    changeState[name] = client.options[name];
    this.setState(changeState);
  }

  onResetToDefault = () => {
    const client = ClientFactory.get();
    this.setState({
      showFPS: false,
      showWCS: true,
      cameraAnimation: true,
      antialiasing: true,
      shadows: false,
      groundShadow: false,
      ambientOcclusion: false,
    });

    client.options.showFPS = false;
    client.options.showWCS = true;
    client.options.cameraAnimation = true;
    client.options.antialiasing = true;
    client.options.shadows = false;
    client.options.groundShadow = false;
    client.options.ambientOcclusion = false;
  };

  render() {
    return (
      <div style={{ overflow: "auto", height: "calc(100vh - 180px)" }}>
        <Row>
          <Card title="Viewer settings" bordered={true} style={{ width: "100%" }}>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.showFPS} onChange={() => this.onChange("showFPS")} />
              </Col>
              <Col span={8}>Enable FPS</Col>
            </Row>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.showWCS} onChange={() => this.onChange("showWCS")} />
              </Col>
              <Col span={8}>Enable WCS</Col>
            </Row>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.cameraAnimation} onChange={() => this.onChange("cameraAnimation")} />
              </Col>
              <Col span={8}>Enable camera animation</Col>
            </Row>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.antialiasing} onChange={() => this.onChange("antialiasing")} />
              </Col>
              <Col span={8}>Enable antialiasing</Col>
            </Row>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.shadows} onChange={() => this.onChange("shadows")} />
              </Col>
              <Col span={8}>Enable shadows</Col>
            </Row>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.groundShadow} onChange={() => this.onChange("groundShadow")} />
              </Col>
              <Col span={8}>Enable ground shadow</Col>
            </Row>
            <Row style={{ marginBottom: "10px" }}>
              <Col span={2}>
                <Switch checked={this.state.ambientOcclusion} onChange={() => this.onChange("ambientOcclusion")} />
              </Col>
              <Col span={8}>Ambient occlusion</Col>
            </Row>
          </Card>
        </Row>
        <Row>
          <Card title="" bordered={true} style={{ width: "100%" }}>
            <Row>
              <Col span={2}>
                <Button type="primary" onClick={this.onResetToDefault}>
                  Reset to default
                </Button>
              </Col>
            </Row>
          </Card>
        </Row>
      </div>
    );
  }
}
