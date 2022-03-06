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
import { connect } from "react-redux";
import { withRouter } from "react-router";
import { actions as notification } from "../redux/notification";
import { actions } from "../redux/viewer";

import ProgressBar from "../components/ProgressBar";
import Header from "../components/Header";
import UserMenu from "../containers/UserMenu";

import { VisualizeProgress } from "./VisualizeJSProgress";
import ClientFactory from "../ClientFactory";

import ViewPointHelper from "./ViewPointHelper";

import { DraggerComponent } from "./DraggerComponent/DraggerComponent";
import { DraggerComponentEvent } from "./DraggerComponent/DraggerComponentEvent";

import { ViewActionComponentEvent } from "./ViewActionComponent/ViewActionComponentEvent";
import { ViewActionComponent } from "./ViewActionComponent/ViewActionComponent";

import { HeaderComponent } from "./HeaderComponent/HeaderComponent";
import { HeaderComponentEvent } from "./HeaderComponent/HeaderComponentEvent";

import { ViewpointListEvent } from "./ViewpointListComponent/ViewpointListEvent";
import { ViewpointListComponent } from "./ViewpointListComponent/ViewpointListComponent";

import { PropertiesComponent } from "./PropertiesComponent/PropertiesComponent";
import { PropertiesEvent } from "./PropertiesComponent/PropertiesEvent";

import { ContextMenu } from "./ContextMenu/ContextMenu";
import { ContextMenuEvent } from "./ContextMenu/ContextMenuEvent";

import ObjectExplorer from "./ObjectExplorer";

import { SubscribeSubjectContext } from "../utils/SubscribeSubjectContext";
import { ModelContextFactory } from "./ModelContexts/ModelContextFactory";

import { AssemblyTransformComponent } from "./AssemblyTransformComponent/AssemblyTransformComponent";

import { WalkHelperComponent } from "./WalkHelperComponent/WalkHelperComponent";

const defaultState = {
  modelList: [],
  activeModel: null,
  file: null,
  geometryProgress: 0,
  visualizeProgress: 0,
  databaseLoaded: false,

  isVisibleObjectExplorer: false,
  isVisibleProperties: false,
  isVisibleViewPointView: false,
  isVisibleTransformView: false,

  geometryLoaded: false,
  isCDA: false,
  isLoadIndicatorVisible: false,
  canvasClassName: "default-cursor",
  activeDraggerName: "",
  isWalkHelperComponent: false,
};

class Viewer extends Component {
  state = { ...defaultState };

  isInitialize = null;
  defaultVisualStyle = "";
  odaApp = null;
  modelContext = null;

  constructor(props) {
    super(props);
    this.subscribeSubjectContext = new SubscribeSubjectContext();
    this.connectDraggerComponentEvents();
    this.connectViewActionComponentEvents();
    this.connectHeaderComponentEvents();
    this.connectViewpointListComponentEvents();
    this.connectPropertiesEvents();
  }

  toggle = (name) => () => this.setState({ [name]: !this.state[name] });

  connectPropertiesEvents() {
    this.propertiesEvents = new PropertiesEvent();
    this.subscribeSubjectContext.subscribe(this.propertiesEvents.onClose, () => this.toggle("isVisibleProperties")());
  }

  connectViewpointListComponentEvents() {
    this.viewpointListEvents = new ViewpointListEvent();

    this.subscribeSubjectContext.subscribe(this.viewpointListEvents.onClose, () =>
      this.toggle("isVisibleViewPointView")()
    );
    this.subscribeSubjectContext.subscribe(this.viewpointListEvents.onRemoveViewpoint, async (vp) => {
      try {
        await this.state.activeModel.deleteViewpoint(vp.guid);
        this.props.addNotification("success", "Viewpoint deleted successfully");
      } catch (e) {
        this.props.addNotification("error", "Error delete view point");
      }
    });

    this.subscribeSubjectContext.subscribe(this.viewpointListEvents.onSelectViewpoint, async (vp) => {
      const viewpointModelId = vp.custom_fields && vp.custom_fields.modelId;
      const viewPointPlugin = new ViewPointHelper(this.odaApp.visLib());

      if (viewpointModelId !== undefined && this.state.activeModel && this.state.activeModel.id !== viewpointModelId) {
        const model = this.state.modelList.find((model) => model.id === viewpointModelId);
        if (model) {
          try {
            await this.openModel(model);
            viewPointPlugin.drawViewPoint(vp);
          } catch {
            this.props.addNotification("error", "Cannot open model");
          }
        }
      } else {
        viewPointPlugin.drawViewPoint(vp);
      }
    });
  }

  connectHeaderComponentEvents() {
    this.headerEventsConnection = new HeaderComponentEvent();

    this.subscribeSubjectContext.subscribe(this.headerEventsConnection.onOpenModel, (model) => this.openModel(model));

    this.subscribeSubjectContext.subscribe(this.headerEventsConnection.onOpenObjectExplorer, () =>
      this.toggle("isVisibleObjectExplorer")()
    );

    this.subscribeSubjectContext.subscribe(this.headerEventsConnection.onOpenProperties, () => {
      this.toggle("isVisibleProperties")();
      if (this.lastProperties) {
        setTimeout(() => {
          this.propertiesEvents.completeLoadProperties.next(this.lastProperties);
        }, 0);
      }
    });

    this.subscribeSubjectContext.subscribe(this.headerEventsConnection.onOpenViewpointView, async () => {
      this.setState({ isVisibleViewPointView: true });

      const viewPoints = await this.state.activeModel.getViewpoints();
      this.viewpointListEvents.changeViewpoints.next(viewPoints);

      for (let vp of viewPoints) {
        if (!vp.snapshot) {
          vp.snapshot = await this.state.activeModel.getSnapshot(vp.guid);
          this.viewpointListEvents.modifyViewpoint.next(vp);
        }
      }
    });
    this.subscribeSubjectContext.subscribe(this.headerEventsConnection.onOpenEdit, () => {
      this.setState({ isVisibleTransformView: true });
    });
  }

  changeVisibleForHelp() {
    if (this.state.activeDraggerName === "Walk") {
      this.viewActionEvents.changeEnableHelp.next(true);
    } else {
      this.viewActionEvents.changeEnableHelp.next(false);
    }
  }

  connectDraggerComponentEvents() {
    this.draggerEventsConnection = new DraggerComponentEvent();
    this.subscribeSubjectContext.subscribe(this.draggerEventsConnection.onActivateDraggerByName, (draggerName) => {
      this.setState({ activeDraggerName: draggerName }, () => {
        this.changeCursorWhenActivateDragger();
        this.changeVisibleForHelp();
      });

      this.odaApp.setActiveDragger(draggerName);
    });

    this.subscribeSubjectContext.subscribe(this.draggerEventsConnection.onClearViewPoint, () => {
      this.odaApp.clearSlices();
      this.odaApp.clearOverlay();
    });

    this.subscribeSubjectContext.subscribe(this.draggerEventsConnection.onSaveViewPoint, async () => {
      const viewPointPlugin = new ViewPointHelper(this.odaApp.visLib());
      const vp = viewPointPlugin.getViewPoint(this.odaApp.visLib().canvas);

      !vp.custom_fields && (vp.custom_fields = {});
      this.state.activeModel && (vp.custom_fields.modelId = this.state.activeModel.id);

      vp.description = new Date().toDateString();
      let newVp = null;
      try {
        newVp = await this.state.activeModel.saveViewpoint(vp);
        this.props.addNotification("success", "Viewpoint saved successfully");
      } catch (e) {
        this.props.addNotification("error", "Error save view point");
      }

      if (this.state.isVisibleViewPointView && newVp) {
        if (!newVp.snapshot) {
          newVp.snapshot = await this.state.activeModel.getSnapshot(newVp.guid);
        }
        this.viewpointListEvents.addViewpoint.next(newVp);
      }
    });
  }

  connectViewActionComponentEvents() {
    this.explodeIndex = 1;
    this.viewActionEvents = new ViewActionComponentEvent();
    this.contextMenuEvents = new ContextMenuEvent();

    const execWithLoadIndicator = (cb) => {
      this.setState({ isLoadIndicatorVisible: true }, () => {
        setTimeout(() => {
          cb();
          this.setState({ isLoadIndicatorVisible: false });
        }, 10);
      });
    };

    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onChangeVisualStyle, (name) => {
      execWithLoadIndicator(() => this.odaApp.visViewer().setActiveVisualStyle(name));
    });

    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onChangeViewType, (type) => {
      const defViewPos = this.odaApp.visLib().DefaultViewPosition;
      this.odaApp.visViewer().setDefaultViewPositionWithAnimation(defViewPos[type]);
    });

    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onChangeViewToDefaultValue, () =>
      this.odaApp.visViewer().zoomExtents()
    );

    const onUnselect = () => execWithLoadIndicator(() => this.odaApp.visViewer().unselect());
    const onIsolateSelectedObjects = () =>
      execWithLoadIndicator(() => this.odaApp.visViewer().isolateSelectedObjects(false));
    const onHideSelectedObjects = () => execWithLoadIndicator(() => this.odaApp.visViewer().hideSelectedObjects());
    const onShowAll = () => execWithLoadIndicator(() => this.odaApp.visViewer().unisolateSelectedObjects(false));

    const onExplode = () =>
      execWithLoadIndicator(() => {
        this.explodeIndex++;
        this.odaApp.visViewer().explode(this.explodeIndex);
      });

    const onCollect = () =>
      execWithLoadIndicator(() => {
        this.explodeIndex = 1;
        this.odaApp.visViewer().explode(1);
      });

    const onRegeneration = () =>
      execWithLoadIndicator(() => {
        this.odaApp.visViewer().regenAll();
      });

    const onCreatePreview = async () => {
      const canvas = this.odaApp.visLib().canvas;
      const base64Img = canvas.toDataURL("image/jpeg", 0.25);

      const item = this.modelContext.get();

      item.preview = base64Img;
      item.save();

      this.props.addNotification("success", "Update file preview done");
    };

    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onUnselect, onUnselect);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onIsolateSelectedObjects, onIsolateSelectedObjects);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onHideSelectedObjects, onHideSelectedObjects);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onShowAll, onShowAll);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onExplode, onExplode);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onCollect, onCollect);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onRegeneration, onRegeneration);
    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onCreatePreview, onCreatePreview);

    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onUnselect, onUnselect);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onIsolateSelectedObjects, onIsolateSelectedObjects);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onHideSelectedObjects, onHideSelectedObjects);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onShowAll, onShowAll);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onExplode, onExplode);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onCollect, onCollect);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onRegeneration, onRegeneration);
    this.subscribeSubjectContext.subscribe(this.contextMenuEvents.onCreatePreview, onCreatePreview);

    this.subscribeSubjectContext.subscribe(this.viewActionEvents.onHelp, () => {
      this.setState({ isWalkHelperComponent: true });
    });
  }

  resetVisualStyleInformation = () => {
    this.viewActionEvents.changeDefaultVisualStyle.next(this.odaApp.visViewer().getActiveVisualStyle());
  };

  changeCursorWhenDrag = () => {
    if (this.state.activeDraggerName === "Pan") {
      this.setState({ canvasClassName: "pan-active-cursor" });
    } else if (this.state.activeDraggerName === "Orbit") {
      this.setState({ canvasClassName: "orbit-active-cursor" });
    } else {
      this.setState({ canvasClassName: "default-cursor" });
    }
  };

  changeCursorWhenActivateDragger = () => {
    if (this.state.activeDraggerName === "Pan") {
      this.setState({ canvasClassName: "pan-cursor" });
    } else if (this.state.activeDraggerName === "Orbit") {
      this.setState({ canvasClassName: "orbit-cursor" });
    } else {
      this.setState({ canvasClassName: "default-cursor" });
    }
  };

  async componentDidMount() {
    const canvas = document.getElementById("canvas");
    canvas.addEventListener("mousedown", this.changeCursorWhenDrag);
    canvas.addEventListener("mouseup", this.changeCursorWhenActivateDragger);

    const setState = (name, value) => {
      this.setState({ [name]: value });
      return value;
    };

    const contextFactory = new ModelContextFactory();
    this.modelContext = contextFactory.create(this.props.match);

    await this.modelContext.initialize();

    this.headerEventsConnection.changeEnableProperties.next(this.modelContext.getHaveProperties());

    this.odaApp = await ClientFactory.get().createViewer({
      target: canvas,
      visualizeJsUrl: this.props.config.data.visualizejs_url,
      onprogress: (ev) =>
        this.setState({
          visualizeProgress: ((100 * ev.loaded) / ev.total) | 0,
        }),
    });
    this.setState({ visualizeProgress: null });

    this.odaApp.addEventListener("ChangeWalkDraggerSpeed", (speed) => {
      this.props.addNotification("success", `Move speed ${speed.data}`);
    });

    this.odaApp.addEventListener("select", async (ev) => {
      const sSet = ev.data;
      const itr = sSet.getIterator();
      if (!itr.done()) {
        const entityId = itr.getEntity();
        let handle = -1;
        if (entityId.getType() === 1) {
          handle = entityId.openObject().getNativeDatabaseHandle();
        } else if (entityId.getType() === 2) {
          handle = entityId.openObjectAsInsert().getNativeDatabaseHandle();
        }
        if (this.modelContext.getHaveProperties()) {
          await this.getProperties(handle);
        }
      }
    });

    this.props.setVisualizeJS(this.odaApp.visLib());
    setState("viewer", this.odaApp.visViewer());

    this.odaApp.visViewer().setExperimentalFunctionalityFlag("gpu_select", false);
    const models = setState("modelList", await this.modelContext.getModels());

    this.headerEventsConnection.changeModelList.next(models);

    await this.openModel(models.find((model) => model.default) || models[0]);
  }

  getProperties = async (handle) => {
    try {
      this.propertiesEvents.loadingProperties.next(true);
      const props = await this.modelContext.getPropertiesByHandle(handle);
      if (this.state.isVisibleProperties) {
        this.propertiesEvents.completeLoadProperties.next(props);
        this.lastProperties = null;
      } else {
        this.lastProperties = props;
      }
    } catch (e) {
      this.propertiesEvents.loadingProperties.next("Not found properties");
    }
  };

  openModel = async (model) => {
    try {
      if (this.odaApp) {
        this.odaApp.cancel();
        this.odaApp.visViewer().unselect();
      }

      this.draggerEventsConnection.changeInitialization.next();
      this.viewActionEvents.changeEnable.next(false);
      this.headerEventsConnection.changeEnable.next(false);
      this.draggerEventsConnection.changeSupportViewPoint.next(this.modelContext.isSupportViewPoint());
      this.headerEventsConnection.changeSupportViewPoint.next(this.modelContext.isSupportViewPoint());
      this.headerEventsConnection.changeSupportTransform.next(this.modelContext.isSupportTransform());

      await this.odaApp.loadReferences(model);

      this.setState({
        activeModel: model,
        displayObjectExplorer: false,
        properties: false,
        settings: false,
      });

      const progress = (event) => this.setState({ geometryProgress: event.data });
      const databaseChunk = () => {
        this.setState({ databaseLoaded: true });

        this.draggerEventsConnection.changeEnable.next(true);
        this.viewActionEvents.changeEnable.next(true);
        this.headerEventsConnection.changeEnable.next(true);

        this.resetVisualStyleInformation();
      };

      this.odaApp.addEventListener("geometry-progress", progress);
      this.odaApp.addEventListener("database-chunk", databaseChunk);

      await this.odaApp.open(model);

      this.odaApp.removeEventListener("database-chunk", databaseChunk);
      this.odaApp.removeEventListener("geometry-progress", progress);

      {
        const itr = this.odaApp.visViewer().getCDATreeIterator();
        this.headerEventsConnection.changeEnableObjectExplorer.next(!itr.done());
        this.setState({
          geometryLoaded: true,
          isCDA: !itr.done() && ClientFactory.getConfig().cda,
        });
      }

      this.odaApp.visViewer().setEnableSceneGraph(true);

      const extFile = this.modelContext.getExtension();
      if (extFile === ".obj" || extFile === ".ifc") this.odaApp.visViewer().setBackgroundColor([255, 255, 255]);

      const ext = this.odaApp.visViewer().getActiveExtents();
      const min = ext.min();
      const max = ext.max();
      const extHeight = max[2] - min[2];

      this.draggerEventsConnection.change3dMode.next(extHeight !== 0);
    } catch (err) {
      console.error(err);
    }
  };

  render() {
    const fileInfo = (this.modelContext && this.modelContext.get()) || {};

    return (
      <div
        style={{
          minWidth: "100%",
          height: "100%",
          position: "absolute",
          display: "flex",
          flexDirection: "column",
          overflow: "hidden",
        }}
      >
        <Header fileInfo={fileInfo}>
          <UserMenu></UserMenu>
        </Header>
        <div>
          <ProgressBar progress={this.state.geometryProgress * 100} />
        </div>

        {/* Content */}
        <div
          style={{
            minWidth: "100%",
            height: "100%",
            display: "flex",
            flexDirection: "column",
          }}
        >
          <HeaderComponent
            isAssembly={this.props.match.params.assemblyId}
            eventsConnection={this.headerEventsConnection}
          />

          <div
            style={{
              width: "100%",
              height: "100%",
              boxSizing: "border-box",
              overflow: "hidden",
            }}
          >
            <div style={{ height: "100%", display: "flex" }}>
              <canvas
                id="canvas"
                className={this.state.canvasClassName}
                style={{ width: "100%", height: "100%" }}
              ></canvas>
            </div>

            {this.state.visualizeProgress && <VisualizeProgress value={this.state.visualizeProgress} />}

            <DraggerComponent eventsConnection={this.draggerEventsConnection}></DraggerComponent>

            <ViewActionComponent eventsConnection={this.viewActionEvents}></ViewActionComponent>

            <ContextMenu eventsConnection={this.contextMenuEvents}></ContextMenu>
          </div>
        </div>

        {this.state.isLoadIndicatorVisible ? (
          <div
            style={{
              position: "absolute",
              top: "calc(50% - 100px)",
              left: "calc(50% - 100px)",
              width: "200px",
              height: "200px",
              color: "#05093B",
            }}
            className="spinner-border"
            role="status"
          ></div>
        ) : null}

        {this.state.isVisibleObjectExplorer ? (
          <ObjectExplorer
            lib={this.odaApp.visLib()}
            viewer={this.odaApp.visViewer()}
            cda={this.state.isCDA}
            getProperties={this.getProperties}
            onClose={this.toggle("isVisibleObjectExplorer")}
          />
        ) : null}
        {this.state.isVisibleProperties ? <PropertiesComponent eventsConnection={this.propertiesEvents} /> : null}
        {this.state.isVisibleViewPointView ? (
          <ViewpointListComponent eventsConnection={this.viewpointListEvents} />
        ) : null}
        {this.state.isVisibleTransformView ? (
          <AssemblyTransformComponent
            viewer={this.odaApp}
            assembly={this.modelContext.get()}
            onClose={this.toggle("isVisibleTransformView")}
          ></AssemblyTransformComponent>
        ) : null}
        {this.state.isWalkHelperComponent ? (
          <WalkHelperComponent onClose={this.toggle("isWalkHelperComponent")}></WalkHelperComponent>
        ) : null}
      </div>
    );
  }

  componentWillUnmount() {
    const canvas = document.getElementById("canvas");
    canvas.removeEventListener("mousedown", this.changeCursorWhenDrag);
    canvas.removeEventListener("mouseup", this.changeCursorWhenActivateDragger);
    if (this.odaApp) {
      this.odaApp.cancel();
      this.odaApp.dispose();
    }
    this.subscribeSubjectContext.unsubscribe();
  }
}

export default connect(
  (state) => ({ ...state, openCloud: state.login.data.openCloud }),
  (dispatch) => ({
    addNotification: (type, text) => dispatch(notification.addNotification(type, text)),
    setVisualizeJS: (visualizeJS) => dispatch(actions.setVisualizeJS(visualizeJS)),
    applySettings: () => dispatch(actions.applySettings()),
  })
)(withRouter(Viewer));
