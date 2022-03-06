import { Component } from "react";

import "antd/dist/antd.css";
import { Modal, Button, Row, Col, Tooltip } from "antd";
import { VideoCameraOutlined } from "@ant-design/icons";

export class WalkHelperComponent extends Component {
  render() {
    return (
      <Modal
        title="Navigation in first person mode"
        visible={true}
        onOk={this.props.onClose}
        onCancel={this.props.onClose}
        footer={false}
      >
        <Row>
          <Col span={12}>
            <h4>Walk</h4>
            <div style={{ padding: "5px" }}>
              <Tooltip title="Key press W to move forward">
                <Button style={{ marginLeft: "55px", width: "50px" }} size={"large"}>
                  W
                </Button>
              </Tooltip>
            </div>
            <div style={{ padding: "5px" }}>
              <Tooltip title="Key press A to move left">
                <Button size={"large"} style={{ marginRight: "5px", width: "50px" }}>
                  A
                </Button>
              </Tooltip>
              <Tooltip title="Key press S to move back">
                <Button size={"large"} style={{ marginRight: "5px", width: "50px" }}>
                  S
                </Button>
              </Tooltip>
              <Tooltip title="Key press D to move right">
                <Button size={"large"} style={{ marginRight: "5px", width: "50px" }}>
                  D
                </Button>
              </Tooltip>
            </div>
            <p>Key press W, S, A, D - to move forward, back, left, right</p>
          </Col>
          <Col span={12}>
            <h4>Look Around</h4>
            <Tooltip title="Drag mouse with left key on view">
              <Button
                size={"large"}
                style={{
                  verticalAlign: "baseline",
                  marginLeft: "85px",
                  width: "50px",
                }}
                icon={<VideoCameraOutlined style={{ verticalAlign: "baseline" }} />}
              ></Button>
            </Tooltip>
            <p>Drag mouse with left key on view</p>
          </Col>
        </Row>
        <Row>
          <Col span={12}>
            <h4>Adjust Speed</h4>
            <div style={{ padding: "5px" }}>
              <div style={{ marginLeft: "20px" }}>
                <Tooltip title="Key press - to reduce movement speed">
                  <Button size={"large"} style={{ marginRight: "5px", width: "50px" }}>
                    -
                  </Button>
                </Tooltip>
                <Tooltip title="Key press - to increase movement speed">
                  <Button size={"large"} style={{ verticalAlign: "baseline", width: "50px" }}>
                    +
                  </Button>
                </Tooltip>
              </div>
            </div>
            <p>Key press + or - to change move speed</p>
          </Col>
          <Col span={12}>
            <h4>Go Up and Down</h4>
            <div style={{ padding: "5px" }}>
              <div style={{ marginLeft: "50px" }}>
                <Tooltip title="Key press - to move up">
                  <Button size={"large"} style={{ marginRight: "5px", width: "50px" }}>
                    Q
                  </Button>
                </Tooltip>
                <Tooltip title="Key press - to move down">
                  <Button size={"large"} style={{ verticalAlign: "baseline", width: "50px" }}>
                    E
                  </Button>
                </Tooltip>
              </div>
              <p>Key press Q, E - to move up, down </p>
            </div>
          </Col>
        </Row>
      </Modal>
    );
  }
}
