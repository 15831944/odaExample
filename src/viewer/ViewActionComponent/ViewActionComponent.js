import { Component } from "react";
import { SubscribeSubjectContext } from "../../utils/SubscribeSubjectContext";

const defaultState = {
  activeVSName: "",
  isEnable: false,
  isEnableHelp: false,
  defaultVisualStyle: "",
};

export class ViewActionComponent extends Component {
  state = { ...defaultState };

  constructor(props) {
    super(props);

    this.eventsConnection = props.eventsConnection;
    this.subscribeSubjectContext = new SubscribeSubjectContext();

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeDefaultVisualStyle, (defaultVisualStyle) =>
      this.setState({ defaultVisualStyle, activeVSName: defaultVisualStyle })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeEnable, (isEnable) =>
      this.setState({ isEnable })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeEnableHelp, (isEnableHelp) =>
      this.setState({ isEnableHelp })
    );

    const actionsList = [
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

    this.actionsListTemplate = actionsList.map((data, index) => {
      return (
        <div className="d-flex" key={index}>
          <div className={"dropdown-item p-2"} onClick={data.action}>
            <img src={data.icons} alt="" width="30" height="30" /> {data.label}
          </div>
        </div>
      );
    });
  }

  componentWillUnmount() {
    this.subscribeSubjectContext.unsubscribe();
  }

  setVisualStyleByName = (name) => {
    this.setState({ activeVSName: name });
    this.eventsConnection.onChangeVisualStyle.next(name);
  };

  setView = (viewType) => {
    this.eventsConnection.onChangeViewType.next(viewType);
  };

  onHome = () => {
    this.eventsConnection.onChangeViewToDefaultValue.next();
  };

  onHelp = () => {
    this.eventsConnection.onHelp.next();
  };

  isNeedShowDefaultVisualStyle = () => {
    const { defaultVisualStyle } = this.state;
    return (
      defaultVisualStyle !== "2dWireframe" &&
      defaultVisualStyle !== "Wireframe" &&
      defaultVisualStyle !== "Hidden" &&
      defaultVisualStyle !== "Shaded" &&
      defaultVisualStyle !== "Shaded with edges" &&
      defaultVisualStyle !== "Sketchy" &&
      defaultVisualStyle !== "X-Ray"
    );
  };

  render() {
    const { activeVSName, isEnable, defaultVisualStyle, isEnableHelp } = this.state;

    /*const actionsListTemplate */

    return (
      <div
        style={{
          zIndex: 4,
          position: "absolute",
          right: 10,
          top: "20%",
          display: "flex",
          flexDirection: "column",
          gap: "0.2em",
          padding: "0.2em",
          border: "1px solid #F6F6F6",
          boxSizing: "border-box",
          background: "#FFFFFF",
          boxShadow: "0px 0px 4px rgba(0, 0, 0, 0.25)",
        }}
      >
        <div className="dropleft d-flex flex-column">
          <button
            disabled={!isEnable}
            className="btn btn-outline-secondary d-flex flex-column"
            type="button"
            id="dropdownMenuButtonForStyle"
            data-toggle="dropdown"
            aria-haspopup="true"
            aria-expanded="false"
          >
            <img src="icons/style.svg" alt="" />
            Style
          </button>
          <div
            className="dropdown-menu"
            aria-labelledby="dropdownMenuButtonForStyle"
            style={{ minWidth: "initial", padding: "0px", cursor: "pointer" }}
          >
            {this.isNeedShowDefaultVisualStyle() ? (
              <div className="d-flex">
                <div
                  className={"dropdown-item p-2" + (activeVSName === defaultVisualStyle ? " active-dragger" : "")}
                  onClick={() => this.setVisualStyleByName(defaultVisualStyle)}
                >
                  <img src="icons/default.svg" alt="" width="30" height="30" /> Default
                </div>
              </div>
            ) : null}

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "2dWireframe" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("2dWireframe")}
              >
                <img src="icons/2dwireframe.svg" alt="" width="30" height="30" /> 2D Wireframe
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "Wireframe" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("Wireframe")}
              >
                <img src="icons/3dwireframe.svg" alt="" width="30" height="30" /> 3D Wireframe
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "Hidden" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("Hidden")}
              >
                <img src="icons/hidden_line.svg" alt="" width="30" height="30" /> Hidden line
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "Realistic" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("Realistic")}
              >
                <img src="icons/shaded.svg" alt="" width="30" height="30" /> Shaded
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "Shaded with edges" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("Shaded with edges")}
              >
                <img src="icons/shaded_with_edges.svg" alt="" width="30" height="30" /> Shaded with edges
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "Sketchy" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("Sketchy")}
              >
                <img src="icons/sketchy.svg" alt="" width="30" height="30" /> Sketchy
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "X-Ray" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("X-Ray")}
              >
                <img src="icons/xray.svg" alt="" width="30" height="30" /> X-Ray
              </div>
            </div>

            <div className="d-flex">
              <div
                className={"dropdown-item p-2" + (activeVSName === "Conceptual" ? " active-dragger" : "")}
                onClick={() => this.setVisualStyleByName("Conceptual")}
              >
                <img src="icons/conceptual.svg" alt="" width="30" height="30" /> Conceptual
              </div>
            </div>
          </div>
        </div>

        <div className="dropleft d-flex flex-column">
          <button
            disabled={!isEnable}
            className="btn btn-outline-secondary d-flex flex-column"
            type="button"
            id="dropdownMenuButtonForView"
            data-toggle="dropdown"
            aria-haspopup="true"
            aria-expanded="false"
          >
            <img src="icons/view.svg" alt="" />
            View
          </button>
          <div
            className="dropdown-menu"
            aria-labelledby="dropdownMenuButtonForView"
            style={{ minWidth: "initial", padding: "0px", cursor: "pointer" }}
          >
            <div className="d-flex">
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewTop")}>
                <img src="icons/top.svg" alt="" width="30" height="30" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewBottom")}>
                <img src="icons/bottom.svg" alt="" width="30" height="30" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewLeft")}>
                <img src="icons/left.svg" alt="" width="30" height="30" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewSW")}>
                <img src="icons/sw.svg" alt="" width="35" height="35" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewSE")}>
                <img src="icons/se.svg" alt="" width="35" height="35" />
              </div>
            </div>

            <div className="d-flex">
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewRight")}>
                <img src="icons/right.svg" alt="" width="30" height="30" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewFront")}>
                <img src="icons/front.svg" alt="" width="30" height="30" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewBack")}>
                <img src="icons/back.svg" alt="" width="30" height="30" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewNE")}>
                <img src="icons/ne.svg" alt="" width="35" height="35" />
              </div>
              <div className="dropdown-item p-2" onClick={() => this.setView("k3DViewNW")}>
                <img src="icons/nw.svg" alt="" width="35" height="35" />
              </div>
            </div>
          </div>
        </div>

        <div className="dropleft d-flex flex-column">
          <button
            disabled={!isEnable}
            className="btn btn-outline-secondary d-flex flex-column"
            type="button"
            id="dropdownMenuButtonForActions"
            data-toggle="dropdown"
            aria-haspopup="true"
            aria-expanded="false"
          >
            <img src="icons/actions.svg" alt="" />
            Actions
          </button>
          <div
            className="dropdown-menu"
            aria-labelledby="dropdownMenuButtonForActions"
            style={{ minWidth: "initial", padding: "0px", cursor: "pointer" }}
          >
            {this.actionsListTemplate}
          </div>
        </div>

        <button
          disabled={!isEnable}
          type="button"
          onClick={this.onHome}
          className="btn btn-outline-secondary d-flex flex-column"
        >
          <img src="icons/home.svg" alt="" />
          Home
        </button>
        {isEnableHelp ? (
          <button
            disabled={!isEnable}
            type="button"
            onClick={this.onHelp}
            className="btn btn-outline-secondary d-flex flex-column"
          >
            <span className="material-icons" style={{ fontSize: "34px", color: "#05093B" }}>
              help_center
            </span>
            Help
          </button>
        ) : null}
      </div>
    );
  }
}
