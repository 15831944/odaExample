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
import React from "react";
import { Link } from "react-router-dom";

import { connect } from "react-redux";
import defaultPreview from "../../images/assembly-preview.png";
import * as login from "../../redux/login";
import { actions as notification } from "../../redux/notification";

import moment from "moment";
import { AssembliesListService } from "./AssembliesListService";

import "antd/dist/antd.css";

import { Table, Input, Tooltip, Space, Button } from "antd";

import {
  CheckCircleOutlined,
  SyncOutlined,
  CloseCircleOutlined,
  ClockCircleOutlined,
  DeleteTwoTone,
  RightSquareTwoTone,
  SearchOutlined,
} from "@ant-design/icons";

const defaultState = {
  assemblies: [],
  name: "",
  loading: true,

  pagination: {
    current: 1,
    pageSize: 20,
    total: 0,
    pageSizeOptions: [20, 50, 75],
    position: ["bottomCenter"],
    showSizeChanger: true,
  },
};

const iconStyleFix = {
  verticalAlign: "baseline",
};

class AssembliesListComponent extends React.Component {
  state = { ...defaultState };

  columns = [
    {
      title: "",
      key: "preview",
      dataIndex: "status",
      render: (_) => {
        return (
          <div style={{ width: "74px", minWidth: "74px" }}>
            <img src={defaultPreview} className="preview-icon" alt="preview"></img>
          </div>
        );
      },
      width: 74,
    },
    {
      title: "Assembly name",
      key: "name",
      dataIndex: "name",
      render: (name, assembly) => {
        return assembly.status === "done" ? <a href={"#/assembly/" + assembly.id}>{name}</a> : `${name}`;
      },
      filterDropdown: ({ setSelectedKeys, selectedKeys, confirm, clearFilters }) => (
        <div style={{ padding: 8 }}>
          <Input
            ref={(node) => {
              this.searchInput = node;
            }}
            placeholder={`Search by name`}
            value={selectedKeys[0]}
            onPressEnter={() => this.onSearch(this.searchInput.state.value)}
            style={{ marginBottom: 8, display: "block" }}
          />
          <Space>
            <Button
              type="primary"
              onClick={() => this.onSearch(this.searchInput.state.value)}
              size="small"
              style={{ width: 90 }}
            >
              Search
            </Button>
            <Button
              onClick={() => {
                this.searchInput.setState({ value: "" });
                this.onSearch("");
              }}
              size="small"
              style={{ width: 90 }}
            >
              Reset
            </Button>
          </Space>
        </div>
      ),
      filterIcon: (_) => (
        <SearchOutlined
          style={{
            fontSize: "18px",
            color: (this.searchInput ? this.searchInput.state.value : "") ? "green" : "#1890ff",
          }}
        />
      ),
      width: "70%",
    },
    {
      title: "",
      key: "status",
      dataIndex: "status",
      render: (status) => {
        if (status === "done") {
          return (
            <Tooltip title="Done">
              <CheckCircleOutlined style={{ ...iconStyleFix, color: "green" }} />
            </Tooltip>
          );
        } else if (status === "inprogress") {
          return (
            <Tooltip title="In progress">
              <SyncOutlined spin style={{ ...iconStyleFix, color: "#1890ff" }} />
            </Tooltip>
          );
        } else if (status === "failed") {
          return (
            <Tooltip title="Failed">
              <CloseCircleOutlined style={{ ...iconStyleFix, color: "#ff4d4f" }} />
            </Tooltip>
          );
        }
        return (
          <Tooltip title="Waiting">
            <ClockCircleOutlined style={{ ...iconStyleFix, color: "black" }} />
          </Tooltip>
        );
      },
    },
    {
      title: "Created",
      dataIndex: "created",
      key: "created",
      render: (created) => {
        return `${moment(created).format("L")}`;
      },
      width: "10%",
    },
    {
      title: "Actions",
      key: "actions",
      render: (_, assembly) => {
        return (
          <div>
            <Tooltip placement="leftBottom" title={"Delete assembly"}>
              <DeleteTwoTone style={{ fontSize: "24px" }} onClick={() => this.removeAssemblyById(assembly.id)} />
            </Tooltip>
            {assembly.status === "done" ? (
              <Link to={`#/assembly/${assembly.id}`}>
                <Tooltip placement="bottom" title={"Open assembly in viewer"}>
                  <RightSquareTwoTone style={{ fontSize: "24px" }} />
                </Tooltip>
              </Link>
            ) : null}
          </div>
        );
      },
      width: "10%",
    },
  ];

  constructor(props) {
    super(props);
    this.service = new AssembliesListService();
  }

  removeAssemblyById = (id) => {
    try {
      this.service.removeById(id);
      this.setState({
        assemblies: this.state.assemblies.filter((assemblyItem) => assemblyItem.id !== id),
      });
    } catch (e) {
      console.error(e);
      this.props.addNotification("error", "Cannot remove assemblies");
    }
  };

  getAssemblyPage = async (page, pageSize, name) => {
    this.setState({ loading: true });
    const fixedName = name === undefined ? name || this.state.name || "" : name;
    try {
      const { allSize, list } = await this.service.getPage(page, pageSize, fixedName);
      this.setState({
        assemblies: list,
        loading: false,
        name: fixedName,
        pagination: {
          ...this.state.pagination,
          total: allSize,
          current: page,
          pageSize: pageSize,
        },
      });
    } catch (e) {
      console.error(e);
      this.props.addNotification("error", "Cannot get assembly page");
    }
  };

  componentDidMount() {
    this.getAssemblyPage(this.state.pagination.current, this.state.pagination.pageSize);

    const isNeedUpdate = () => {
      return this.state.assemblies.filter(
        (assemblies) => assemblies.status === "waiting" || assemblies.status === "inprogress"
      ).length;
    };

    this.interval = setInterval(() => {
      if (isNeedUpdate()) {
        this.getAssemblyPage(this.state.pagination.current, this.state.pagination.pageSize);
      }
    }, 5000);
  }

  componentWillUnmount() {
    clearInterval(this.interval);
  }

  handleTableChange = (pagination) => {
    this.getAssemblyPage(pagination.current, pagination.pageSize);
  };

  onSearch = (value) => {
    const { pagination } = this.state;
    this.getAssemblyPage(1, pagination.pageSize, value);
  };

  render() {
    return (
      <div style={{ overflow: "hidden" }}>
        <div className="d-flex flex-column">
          <Table
            size="small"
            columns={this.columns}
            rowKey={(row) => row.id}
            dataSource={this.state.assemblies}
            pagination={this.state.pagination}
            loading={this.state.loading}
            onChange={this.handleTableChange}
            scroll={{ x: true, y: "calc(100vh - 160px)" }}
          />
        </div>
      </div>
    );
  }
}

export default connect(
  (state) => ({ ...state.files, ...state.plugins }),
  (dispatch) => ({
    logout: () => dispatch(login.actions.logout()),
    addNotification: (type, text) => dispatch(notification.addNotification(type, text)),
  })
)(AssembliesListComponent);
