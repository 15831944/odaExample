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
import defaultPreview from "../../images/default-preview.png";
import { actions as notification } from "../../redux/notification";

import moment from "moment";
import { FileListService } from "./FileListService";

import ProgressBar from "../../components/ProgressBar";

import DrawingReference from "../../components/DrawingReference";
import CreateDrawing from "../../components/CreateDrawing";
import CreateAssembly from "../../components/CreateAssembly";
import ClientFactory from "./../../ClientFactory";

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
  FileAddOutlined,
  AppstoreAddOutlined,
  CloudDownloadOutlined,
} from "@ant-design/icons";

const defaultState = {
  files: [],
  name: "",
  ext: "",
  loading: true,
  uploadProgress: 0,
  pagination: {
    current: 1,
    pageSize: 20,
    total: 0,
    pageSizeOptions: [20, 50, 75],
    position: ["bottomCenter"],
    showSizeChanger: true,
  },

  showCreateDrawingComponent: false,
  showCreateReferenceComponent: false,
  showCreateAssemblyComponent: false,

  selectedFilesId: [],
};

const ICON_VERTICAL_ALIGN = {
  verticalAlign: "baseline",
};

const PREVIEW_IMG_STYLE = {
  width: "120px",
  height: "65px",
  objectFit: "cover",
};

const PREVIEW_STYLE = {
  width: "120px",
  minWidth: "65px",
};

const TABLE_RECT = {
  x: true,
  y: "calc(100vh - 210px)",
};

const BUTTON_PANEL = {
  padding: "5px 2px",
};

const JOB_STATE = {
  DONE: "done",
  FAILED: "failed",
  INPROGRESS: "inprogress",
};

class filesListComponent extends React.Component {
  state = { ...defaultState };

  columns = [
    {
      title: "",
      key: "preview",
      dataIndex: "preview",
      render: (preview) => {
        return (
          <div style={PREVIEW_STYLE}>
            {preview ? (
              <img src={preview} style={PREVIEW_IMG_STYLE} className="preview-icon" alt="preview"></img>
            ) : (
              <img src={defaultPreview} className="preview-icon" alt="preview"></img>
            )}
          </div>
        );
      },
      width: 74,
    },
    {
      title: "File name",
      key: "name",
      dataIndex: "name",
      render: (name, file) => {
        const isPropertyFinished =
          file.propertiesStatus === JOB_STATE.DONE || file.propertiesStatus === JOB_STATE.FAILED;
        const isGeometryFinished = file.geometryStatus === JOB_STATE.DONE;
        return isGeometryFinished && isPropertyFinished ? <a href={"#/file/" + file.id}>{name}</a> : name;
      },
      filterDropdown: ({ _, selectedKeys }) => (
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
      width: "50%",
    },
    {
      title: "",
      key: "status",
      dataIndex: "geometryStatus",
      render: (geometryStatus, file) => {
        if (
          geometryStatus === JOB_STATE.DONE &&
          (file.propertiesStatus === JOB_STATE.DONE || file.propertiesStatus === JOB_STATE.FAILED)
        ) {
          return (
            <Tooltip title="Done">
              <CheckCircleOutlined style={{ ...ICON_VERTICAL_ALIGN, color: "green" }} />
            </Tooltip>
          );
        } else if (geometryStatus === JOB_STATE.INPROGRESS || file.propertiesStatus === JOB_STATE.INPROGRESS) {
          return (
            <Tooltip title="In progress">
              <SyncOutlined spin style={{ ...ICON_VERTICAL_ALIGN, color: "#1890ff" }} />
            </Tooltip>
          );
        } else if (geometryStatus === JOB_STATE.FAILED && file.propertiesStatus === JOB_STATE.FAILED) {
          return (
            <Tooltip title="Failed">
              <CloseCircleOutlined style={{ ...ICON_VERTICAL_ALIGN, color: "#ff4d4f" }} />
            </Tooltip>
          );
        }
        return (
          <Tooltip title="Waiting">
            <ClockCircleOutlined style={{ ...ICON_VERTICAL_ALIGN, color: "black" }} />
          </Tooltip>
        );
      },
    },
    {
      title: "Type",
      dataIndex: "type",
      key: "type",
      render: (type) => {
        return type;
      },
      filters: ClientFactory.getConfig().supportFormats.map((item) => ({
        text: item,
        value: `${item.toLowerCase()}`,
      })),
      width: "10%",
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
      title: "Size",
      dataIndex: "size",
      key: "size",
      render: (size) => {
        return this.bytesToMegabytes(size);
      },
      width: "10%",
    },
    {
      title: "Actions",
      key: "actions",
      render: (_, file) => {
        return (
          <div>
            <Tooltip placement="leftBottom" title={"Download original file"}>
              <CloudDownloadOutlined
                style={{ fontSize: "24px", color: "#359eff" }}
                onClick={() => this.service.downloadOriginalFile(file)}
              />
            </Tooltip>
            <Tooltip placement="leftBottom" title={"Delete file"}>
              <DeleteTwoTone style={{ fontSize: "24px" }} onClick={() => this.removeById(file.id)} />
            </Tooltip>
            {file.geometryStatus === JOB_STATE.DONE ? (
              <Link to={`/file/${file.id}`}>
                <Tooltip placement="bottom" title={"Open file in viewer"}>
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
    this.service = new FileListService();
  }

  bytesToMegabytes(bytes) {
    if (bytes < 1000) {
      return `${bytes} bytes`;
    } else if (bytes >= 1000 && bytes < 1000000) {
      return `${(bytes / 1000).toFixed(2)} KB`;
    } else if (bytes >= 1000000 && bytes < 1000000000) {
      return `${(bytes / 1000000).toFixed(2)} MB`;
    }
    return `${(bytes / 1000000000).toFixed(2)} GB`;
  }

  removeById = async (id) => {
    try {
      await this.service.removeById(id);
      this.setState({
        files: this.state.files.filter((item) => item.id !== id),
      });
    } catch (e) {
      console.error(e);
      this.props.addNotification("error", "Cannot remove files");
    }
  };

  getFilePage = async (page, pageSize, name, ext) => {
    this.setState({ loading: true });

    const fixedName = name === undefined ? name || this.state.name || "" : name;
    const fixedExt = ext === undefined ? ext || this.state.ext || "" : ext;

    try {
      const { allSize, list } = await this.service.getPage(page, pageSize, fixedName, fixedExt);
      this.setState({
        files: list,
        loading: false,
        name: fixedName,
        ext: fixedExt,
        pagination: {
          ...this.state.pagination,
          total: allSize,
          current: page,
          pageSize: pageSize,
        },
      });
    } catch (e) {
      console.error(e);
      this.props.addNotification("error", "Cannot get files page");
    }
  };

  onUploadProgress = (ev) => {
    this.setState({ uploadProgress: ev.data * 100 });
  };

  onSelectChange = (selectedRowKeys) => {
    this.setState({ selectedFilesId: selectedRowKeys });
  };

  componentDidMount() {
    this.getFilePage(this.state.pagination.current, this.state.pagination.pageSize);

    const isNeedUpdate = () => {
      if (!this.supportFormatMapCache) {
        const supportFormats = ClientFactory.getConfig().supportFormats;
        this.supportFormatMapCache = new Map();
        for (let format of supportFormats) {
          this.supportFormatMapCache.set(`.${format.toLowerCase()}`, 0);
        }
      }

      for (let file of this.state.files) {
        if (this.supportFormatMapCache.has(file.type.toLowerCase()) && file.metadata === false) return true;
      }
      return false;
    };

    this.interval = setInterval(() => {
      if (isNeedUpdate()) {
        this.getFilePage(this.state.pagination.current, this.state.pagination.pageSize);
      }
    }, 5000);

    ClientFactory.get().on("upload-progress", this.onUploadProgress);
  }

  componentWillUnmount() {
    clearInterval(this.interval);
    ClientFactory.get().removeEventListener("upload-progress", this.onUploadProgress);
  }

  handleTableChange = (pagination, filters) => {
    const { name, type } = filters;
    this.getFilePage(pagination.current, pagination.pageSize, name || undefined, type ? type.join("|") : "");
  };

  onSearch = (value) => {
    const { pagination } = this.state;
    this.getFilePage(1, pagination.pageSize, value);
  };

  onShowCreateAssemblyDlg = () => {
    this.setState({
      showCreateAssemblyComponent: true,
    });
  };

  onCloseCreateAssemblyDlg = () => {
    this.setState({
      showCreateAssemblyComponent: false,
    });
  };

  onResolveCreateDrawing = (file) => {
    this.drawingFile = file;
    this.referenceFiles = [];
    this.setState({
      showCreateDrawingComponent: false,
      showCreateReferenceComponent: true,
    });
  };

  onRejectCreateDrawing = () => {
    this.setState({
      showCreateDrawingComponent: false,
      showCreateReferenceComponent: false,
    });
  };

  onResolveCreateReference = async (files) => {
    this.referenceFiles = files;
    this.setState({
      showCreateDrawingComponent: false,
      showCreateReferenceComponent: false,
    });
    try {
      await this.service.uploadFiles(this.drawingFile, this.referenceFiles, this.onUploadProgress);
      this.getFilePage(this.state.pagination.current, this.state.pagination.pageSize);
    } catch (e) {
      console.error(e);
      this.props.addNotification("error", "Cannot upload file");
    }
  };

  onRejectCreateReference = () => {
    this.drawingFile = null;
    this.referenceFiles = [];
    this.setState({
      showCreateDrawingComponent: false,
      showCreateReferenceComponent: false,
    });
  };

  onCreateAssembly = async (name, files) => {
    const fileIds = files.map((file) => file.id);
    try {
      await ClientFactory.get().createAssembly(fileIds, name);
      this.props.addNotification("success", "Create assembly done");
    } catch (e) {
      console.error(e);
      this.props.addNotification("error", "Cannot create assembly");
    }

    this.setState({ selectedFilesId: [], showCreateAssemblyComponent: false });
  };

  render() {
    const {
      showCreateDrawingComponent,
      showCreateReferenceComponent,
      showCreateAssemblyComponent,
      files,
      pagination,
      loading,
      uploadProgress,
      selectedFilesId,
    } = this.state;

    const rowSelection = {
      selectedRowKeys: selectedFilesId,
      onChange: this.onSelectChange,
    };

    const initializeCreateDrawingComponent = () => {
      return showCreateDrawingComponent ? (
        <CreateDrawing
          supportFormats={ClientFactory.getConfig().supportFormats}
          onResolve={this.onResolveCreateDrawing}
          onReject={this.onRejectCreateDrawing}
        ></CreateDrawing>
      ) : null;
    };

    const initializeCreateReferenceComponent = () => {
      return showCreateReferenceComponent ? (
        <DrawingReference
          onResolve={this.onResolveCreateReference}
          onReject={this.onRejectCreateReference}
        ></DrawingReference>
      ) : null;
    };

    const initializeCreateAssemblyComponent = () => {
      return showCreateAssemblyComponent ? (
        <CreateAssembly
          files={selectedFilesId}
          onResolve={this.onCreateAssembly}
          onCloseHandler={this.onCloseCreateAssemblyDlg}
        ></CreateAssembly>
      ) : null;
    };

    const initializeTable = () => {
      return (
        <div className="d-flex flex-column">
          <Table
            size="small"
            columns={this.columns}
            rowKey={(row) => row.id}
            dataSource={files}
            pagination={pagination}
            loading={loading}
            onChange={this.handleTableChange}
            scroll={TABLE_RECT}
            rowSelection={rowSelection}
          />
        </div>
      );
    };

    const initializeProgressBar = () => {
      return (
        <div>
          <ProgressBar progress={uploadProgress} />
        </div>
      );
    };

    const initializeActionButtonHeader = () => {
      return (
        <div className="d-flex flex-column">
          <div className="tools-panel d-flex flex-wrap justify-content-between gap-2" style={BUTTON_PANEL}>
            <div className="d-flex flex-wrap gap-2">
              <Button
                onClick={() => this.setState({ showCreateDrawingComponent: true })}
                icon={<FileAddOutlined style={{ ...ICON_VERTICAL_ALIGN }} />}
                size="large"
              >
                Upload file
              </Button>

              <Button
                disabled={selectedFilesId.length < 2}
                onClick={this.onShowCreateAssemblyDlg}
                size="large"
                style={{ marginLeft: "5px" }}
                icon={<AppstoreAddOutlined style={{ ...ICON_VERTICAL_ALIGN }} />}
              >
                Create assembly
              </Button>
            </div>
          </div>
        </div>
      );
    };

    return (
      <div style={{ overflow: "hidden" }}>
        {initializeProgressBar()}
        {initializeActionButtonHeader()}
        {initializeTable()}
        {initializeCreateDrawingComponent()}
        {initializeCreateReferenceComponent()}
        {initializeCreateAssemblyComponent()}
      </div>
    );
  }
}

export default connect(
  (state) => ({ ...state.files, ...state.plugins }),
  (dispatch) => ({
    addNotification: (type, text) => dispatch(notification.addNotification(type, text)),
  })
)(filesListComponent);
