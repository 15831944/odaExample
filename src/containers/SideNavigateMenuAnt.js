import { Component } from "react";
import { Link } from "react-router-dom";

import "antd/dist/antd.css";
import { Menu, Layout } from "antd";
import Icon from "@ant-design/icons";
import { withRouter } from "react-router";

import { MaterialIcon } from "./../utils/IconUtils";

const { Sider } = Layout;

const defaultState = {
  isCollapsed: false,
};

class SideNavigateMenuAnt extends Component {
  state = { ...defaultState };

  createMenuItem(routeTo, iconName, name) {
    return (
      <Menu.Item
        key={routeTo}
        title={name}
        style={{ marginBottom: 0, marginTop: 0 }}
        icon={<Icon component={MaterialIcon(iconName, 20)}></Icon>}
      >
        <Link to={routeTo}>{name}</Link>
      </Menu.Item>
    );
  }

  render() {
    const sideMenuLayoutStyle = {
      height: "calc(100vh - 70px)",
      background: "white",
      border: "1px solid #eeeeee",
      marginRight: "2px",
    };
    /*
          {this.createMenuItem("/projects", 'work', 'Projects', isCollapsed)}
          {this.createMenuItem("/sandbox", 'history_edu', 'Sand box', isCollapsed)}
          {this.createMenuItem("/dashboard", 'dashboard', 'Dash board', isCollapsed)}
          {this.createMenuItem("/settings", 'settings', 'Settings', isCollapsed)}
*/

    return (
      <>
        <div>
          <Sider collapsible style={sideMenuLayoutStyle} theme="light">
            <Menu
              defaultSelectedKeys={[this.props.location.pathname]}
              mode={"inline"}
              theme={this.props.theme || "light"}
            >
              {this.createMenuItem("/", "description", "Files")}
              {this.createMenuItem("/assemblies", "backup_table", "Assemblies")}
              {this.createMenuItem("/settings", "settings", "Settings")}
              {this.createMenuItem("/jobs", "work", "Jobs")}
            </Menu>
          </Sider>
        </div>
      </>
    );
  }
}

export default withRouter(SideNavigateMenuAnt);
