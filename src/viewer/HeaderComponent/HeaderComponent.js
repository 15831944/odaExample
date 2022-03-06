import { Component } from "react";
import { Link } from "react-router-dom";

import { SubscribeSubjectContext } from "../../utils/SubscribeSubjectContext";

import "antd/dist/antd.css";
import { Menu, Dropdown, Button } from "antd";
import Icon from "@ant-design/icons";
import { MaterialIcon, SvgIcon } from "./../../utils/IconUtils";

const defaultState = {
  modelList: [],
  activeModel: {},
  isEnableObjectExplorer: false,
  isEnableProperties: false,
  isEnable: false,
  isSupportViewPoint: true,
  isSupportTransform: false,
};

const verticalIcon = {
  verticalAlign: "baseline",
};

export class HeaderComponent extends Component {
  state = { ...defaultState };

  constructor(props) {
    super(props);
    this.eventsConnection = props.eventsConnection;
    this.subscribeSubjectContext = new SubscribeSubjectContext();

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeModelList, (value) => {
      this.setState({ modelList: value, activeModel: value[0] });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeEnableObjectExplorer, (value) => {
      this.setState({ isEnableObjectExplorer: value });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeEnableProperties, (value) => {
      this.setState({ isEnableProperties: value });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeEnable, (value) => {
      this.setState({ isEnable: value });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeSupportViewPoint, (isSupportViewPoint) => {
      this.setState({ isSupportViewPoint });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeSupportTransform, (isSupport) => {
      this.setState({ isSupportTransform: isSupport });
    });
  }

  componentWillUnmount() {
    this.subscribeSubjectContext.unsubscribe();
  }

  onOpenModel = (model) => {
    this.setState({ activeModel: model });
    this.eventsConnection.onOpenModel.next(model);
  };

  render() {
    const {
      modelList,
      activeModel,
      isEnableObjectExplorer,
      isEnableProperties,
      isEnable,
      isSupportViewPoint,
      isSupportTransform,
    } = this.state;

    const modelListTemplate = modelList.map((model) => {
      return (
        <Menu.Item key={model.name} onClick={() => this.onOpenModel(model)}>
          {model.name || "Default"}
        </Menu.Item>
      );
    });

    const modelChooseTemplate = (
      <Menu defaultSelectedKeys={[activeModel.name]} selectedKeys={[activeModel.name]}>
        {modelListTemplate}
      </Menu>
    );

    const mainPanelStyle = {
      display: "flex",
      justifyContent: "space-between",
      flexWrap: "wrap",
      boxShadow: "0 3px 3px 0px #dddddd",
    };

    return (
      <div className="col py-1" style={mainPanelStyle}>
        {/* Left side */}
        <div style={{ display: "flex" }}>
          {this.props.isAssembly ? (
            <Link to="/assemblies">
              <Button
                style={verticalIcon}
                icon={<Icon component={SvgIcon("icons/back_files.svg", 20, 20)} />}
                size="large"
              >
                Back to assemblies
              </Button>
            </Link>
          ) : (
            <Link to="/">
              <Button
                style={verticalIcon}
                icon={<Icon component={SvgIcon("icons/back_files.svg", 20, 20)} />}
                size="large"
              >
                Back to files
              </Button>
            </Link>
          )}
        </div>

        {/* Right side */}
        <div style={{ display: "flex", gap: "0.2em", flexWrap: "wrap" }}>
          {isSupportTransform ? (
            <Button
              size="large"
              disabled={!isEnable}
              style={verticalIcon}
              icon={<Icon component={MaterialIcon("transform", 20)} />}
              onClick={() => this.eventsConnection.onOpenEdit.next()}
            >
              Transform
            </Button>
          ) : null}
          {isSupportViewPoint ? (
            <Button
              size="large"
              disabled={!isEnable}
              style={verticalIcon}
              icon={<Icon component={SvgIcon("icons/view_point.svg", 20, 20)} />}
              onClick={() => this.eventsConnection.onOpenViewpointView.next()}
            >
              Viewpoint
            </Button>
          ) : null}
          <Button
            size="large"
            disabled={!isEnableObjectExplorer}
            style={verticalIcon}
            icon={<Icon component={SvgIcon("icons/object_explorer.svg", 20, 20)} />}
            onClick={() => this.eventsConnection.onOpenObjectExplorer.next()}
          >
            Explorer
          </Button>

          <Button
            size="large"
            disabled={!isEnableProperties}
            style={verticalIcon}
            icon={<Icon component={SvgIcon("icons/properties.svg", 20, 20)} />}
            onClick={() => this.eventsConnection.onOpenProperties.next()}
          >
            Properties
          </Button>
          {modelList.length > 1 ? (
            <Dropdown overlay={modelChooseTemplate} placement="topRight">
              <Button
                size="large"
                disabled={!isEnable}
                style={verticalIcon}
                icon={<Icon component={SvgIcon("icons/layouts.svg", 20, 20)} />}
              >
                Models
              </Button>
            </Dropdown>
          ) : null}
        </div>
      </div>
    );
  }
}
