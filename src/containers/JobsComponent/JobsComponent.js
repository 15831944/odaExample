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
import { connect } from "react-redux";
import { actions as notification } from "../../redux/notification";

import moment from "moment";
import { JobsService } from "./JobsService";

import "antd/dist/antd.css";

import { Table, Tag, Tooltip } from "antd";

import {
  CheckCircleOutlined,
  SyncOutlined,
  CloseCircleOutlined,
  ClockCircleOutlined,
  FileTwoTone,
  AppstoreTwoTone,
} from "@ant-design/icons";

const defaultState = {
  records: [],
  filters: [],
  loading: true,
  pagination: {
    current: 1,
    pageSize: 25,
    total: 0,
    pageSizeOptions: [25, 50, 75],
    position: ["bottomCenter"],
    showSizeChanger: true,
  },
};

const iconStyleFix = {
  verticalAlign: "baseline",
};

const tagStyle = {
  padding: "5px",
  fontSize: "16px",
  width: "100px",
};

const statusColorMap = {
  waiting: {
    color: "default",
    icon: <ClockCircleOutlined style={iconStyleFix} />,
  },
  running: { color: "processing", icon: <SyncOutlined style={iconStyleFix} /> },
  failed: {
    color: "error",
    icon: <CloseCircleOutlined style={iconStyleFix} />,
  },
  done: {
    color: "success",
    icon: <CheckCircleOutlined style={iconStyleFix} />,
  },
};

const statusFilterList = [
  {
    text: "waiting",
    value: "waiting",
  },
  {
    text: "running",
    value: "running",
  },
  {
    text: "failed",
    value: "failed",
  },
  {
    text: "done",
    value: "done",
  },
];

const createTag = (state) => {
  return (
    <Tag style={tagStyle} icon={statusColorMap[state].icon} color={statusColorMap[state].color}>
      {state}
    </Tag>
  );
};

const createDateTimeLabel = (dateTime) => {
  return `${moment(dateTime).format("L")} - ${moment(dateTime).format("LT")}`;
};

const crateFileOrAssemblyName = (record) => {
  if (record.assemblyName)
    return (
      <div>
        <Tooltip placement="right" title={`Assembly: ${record.assemblyName}`}>
          <AppstoreTwoTone style={iconStyleFix} /> {`${record.assemblyName}`}
        </Tooltip>
      </div>
    );
  else if (record.fileName)
    return (
      <div>
        <Tooltip placement="right" title={`File: ${record.fileName}`}>
          <FileTwoTone style={iconStyleFix} /> {`${record.fileName}`}
        </Tooltip>
      </div>
    );
  return "";
};

class JobsComponent extends React.Component {
  state = { ...defaultState };

  columns = [
    {
      title: "State",
      key: "state",
      dataIndex: "state",
      render: (state) => createTag(state),
      width: "5%",
      filters: statusFilterList,
    },
    {
      title: "Id",
      dataIndex: "id",
      key: "id",
      render: (id) => {
        return (
          <Tooltip placement="right" title={id}>
            {`${id.substring(0, 2)}...${id.substring(id.length - 5, id.length)}`}
          </Tooltip>
        );
      },
      width: "5%",
    },
    {
      title: "Name",
      key: "assemblyName",
      render: (_, record) => crateFileOrAssemblyName(record),
      width: "30%",
    },
    {
      title: "Created at",
      dataIndex: "createdAt",
      key: "createdAt",
      render: (createdAt) => createDateTimeLabel(createdAt),
      width: "13%",
    },
    {
      title: "Started at",
      dataIndex: "startedAt",
      key: "startedAt",
      render: (startedAt) => createDateTimeLabel(startedAt),
      width: "13%",
    },
    {
      title: "Last update",
      dataIndex: "lastUpdate",
      key: "lastUpdate",
      render: (lastUpdate) => createDateTimeLabel(lastUpdate),
      width: "13%",
    },
  ];

  constructor(props) {
    super(props);
    this.service = new JobsService();
  }

  getPage = async (page, pageSize, filters) => {
    this.setState({ loading: true });
    try {
      const { allSize, result } = await this.service.getPage(page, pageSize, filters);

      this.setState({
        records: result,
        loading: false,
        filters: filters,
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
    this.getPage(this.state.pagination.current, this.state.pagination.pageSize);

    const isNeedUpdate = () => {
      return this.state.records.filter((record) => record.status === "waiting" || record.status === "running").length;
    };

    this.interval = setInterval(() => {
      if (isNeedUpdate()) {
        this.getPage(this.state.pagination.current, this.state.pagination.pageSize);
      }
    }, 5000);
  }

  componentWillUnmount() {
    clearInterval(this.interval);
  }

  handleTableChange = (pagination, filters) => {
    this.getPage(pagination.current, pagination.pageSize, filters ? filters.state : []);
  };

  render() {
    const { records, pagination, loading } = this.state;
    return (
      <div style={{ overflow: "hidden" }}>
        <Table
          size="small"
          columns={this.columns}
          rowKey={(row) => row.id}
          dataSource={records}
          pagination={pagination}
          loading={loading}
          onChange={this.handleTableChange}
          scroll={{ x: true, y: "calc(100vh - 180px)" }}
        ></Table>
      </div>
    );
  }
}

export default connect(
  (state) => ({ ...state.plugins }),
  (dispatch) => ({
    addNotification: (type, text) => dispatch(notification.addNotification(type, text)),
  })
)(JobsComponent);
