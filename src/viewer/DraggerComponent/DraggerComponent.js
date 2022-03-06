import { Component } from "react";
import { SubscribeSubjectContext } from "../../utils/SubscribeSubjectContext";

const defaultState = {
  is3D: false,
  activeDraggerName: "Pan",
  hasViewPointToSave: false,
  isEnable: false,
  cuttingChoose: false,
  isSupportViewPoint: true,
};

export class DraggerComponent extends Component {
  state = { ...defaultState };

  constructor(props) {
    super(props);
    this.eventsConnection = props.eventsConnection;
    this.subscribeSubjectContext = new SubscribeSubjectContext();

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeInitialization, () => {
      this.onClearViewer();
      this.setState({ ...defaultState });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.change3dMode, (is3D) => {
      if (is3D === false) {
        this.onPan();
      } else if (is3D === true) {
        this.onOrbit();
      }
      this.setState({ is3D });
    });

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeEnable, (isEnable) =>
      this.setState({ isEnable })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeSupportViewPoint, (isSupportViewPoint) =>
      this.setState({ isSupportViewPoint })
    );
  }

  componentWillUnmount() {
    this.subscribeSubjectContext.unsubscribe();
  }

  activateDraggerByName = (name, hasViewPointToSave) => {
    this.eventsConnection.onActivateDraggerByName.next(name);
    this.setState({
      activeDraggerName: name,
      hasViewPointToSave: hasViewPointToSave,
    });
  };

  toggle = (name) => () => this.setState({ [name]: !this.state[name] });

  onPan = () => this.activateDraggerByName("Pan");

  onOrbit = () => this.activateDraggerByName("Orbit");

  onZoom = () => this.activateDraggerByName("Zoom");

  onMeasuring = () => this.activateDraggerByName("MeasureLine");

  onSlicePlaneX = () => {
    this.activateDraggerByName("CuttingPlaneXAxis", true);
    this.setState({ activeDraggerName: "Cutting" });
    this.toggle("cuttingChoose")();
  };

  onSlicePlaneY = () => {
    this.activateDraggerByName("CuttingPlaneYAxis");
    this.setState({ activeDraggerName: "Cutting" });
    this.toggle("cuttingChoose")();
    this.setState({ hasViewPointToSave: true });
  };

  onSlicePlaneZ = () => {
    this.activateDraggerByName("CuttingPlaneZAxis");
    this.setState({ activeDraggerName: "Cutting" });
    this.toggle("cuttingChoose")();
    this.setState({ hasViewPointToSave: true });
  };

  onDrawLine = () => this.activateDraggerByName("Line", true);

  onDrawText = () => this.activateDraggerByName("Text", true);

  onSave = () => {
    this.eventsConnection.onSaveViewPoint.next();
  };

  onClearViewer = () => {
    this.eventsConnection.onClearViewPoint.next();
    this.onPan();
    this.setState({ hasViewPointToSave: false });
  };

  onWalk = () => {
    this.onClearViewer();
    this.activateDraggerByName("Walk", true);
  };

  render() {
    const { is3D, activeDraggerName, hasViewPointToSave, isEnable, cuttingChoose, isSupportViewPoint } = this.state;

    return (
      <div>
        <div
          style={{
            zIndex: 4,
            position: "absolute",
            bottom: "1%",
            display: "flex",
            width: "100%",
            justifyContent: "center",
          }}
        >
          <div
            className="p-1"
            style={{
              display: "flex",
              flexWrap: "wrap",
              gap: "0.2em",
              border: "1px solid #F6F6F6",
              boxSizing: "border-box",
              background: "#FFFFFF",
              boxShadow: "0px 0px 4px rgba(0, 0, 0, 0.25)",
              justifyContent: "center",
              padding: "0.1em",
            }}
          >
            <button
              disabled={!isEnable}
              type="button"
              onClick={this.onPan}
              className={
                "btn btn-outline-secondary d-flex flex-column " + (activeDraggerName === "Pan" ? "active-dragger" : "")
              }
            >
              <img src="icons/pan.svg" alt="" />
              Pan
            </button>
            {is3D ? (
              <button
                disabled={!isEnable}
                type="button"
                onClick={this.onOrbit}
                className={
                  "btn btn-outline-secondary d-flex flex-column " +
                  (activeDraggerName === "Orbit" ? "active-dragger" : "")
                }
              >
                <img src="icons/orbit.svg" alt="" />
                Orbit
              </button>
            ) : null}
            <button
              disabled={!isEnable}
              type="button"
              onClick={this.onZoom}
              className={
                "btn btn-outline-secondary d-flex flex-column " + (activeDraggerName === "Zoom" ? "active-dragger" : "")
              }
            >
              <img src="icons/zoom_window.svg" alt="" />
              Zoom
            </button>
            <button
              disabled={!isEnable}
              type="button"
              onClick={this.onMeasuring}
              className={
                "btn btn-outline-secondary d-flex flex-column " +
                (activeDraggerName === "Measuring" ? "active-dragger" : "")
              }
            >
              <img src="icons/ruler.svg" alt="" />
              Ruler
            </button>
            {is3D ? (
              <button
                disabled={!isEnable}
                type="button"
                onClick={this.onWalk}
                className={
                  "btn btn-outline-secondary d-flex flex-column " +
                  (activeDraggerName === "Walk" ? "active-dragger" : "")
                }
              >
                <span className="material-icons" style={{ fontSize: "34px", color: "#05093B" }}>
                  directions_walk
                </span>
                Walk
              </button>
            ) : null}
            <button
              disabled={!isEnable}
              type="button"
              onClick={this.toggle("cuttingChoose")}
              className={
                "btn btn-outline-secondary d-flex flex-column " +
                (activeDraggerName === "Cutting" ? "active-dragger" : "")
              }
            >
              <img src="icons/cutting.svg" alt="" />
              Cutting
            </button>

            <button
              disabled={!isEnable}
              type="button"
              onClick={this.onClearViewer}
              className="btn btn-outline-secondary d-flex flex-column"
            >
              <img src="icons/clear.svg" alt="" />
              Clear
            </button>
            {isSupportViewPoint ? (
              <>
                <button
                  disabled={!isEnable}
                  type="button"
                  onClick={this.onDrawLine}
                  className={
                    "btn btn-outline-secondary d-flex flex-column " +
                    (activeDraggerName === "Line" ? "active-dragger" : "")
                  }
                >
                  <img src="icons/pen.svg" alt="" />
                  Pen
                </button>
                <button
                  disabled={!isEnable}
                  type="button"
                  onClick={this.onDrawText}
                  className={
                    "btn btn-outline-secondary d-flex flex-column " +
                    (activeDraggerName === "Text" ? "active-dragger" : "")
                  }
                >
                  <img src="icons/text.svg" alt="" />
                  Text
                </button>
                <button
                  disabled={!hasViewPointToSave}
                  type="button"
                  onClick={this.onSave}
                  className="btn btn-outline-secondary d-flex flex-column"
                >
                  <img src="icons/save_viewpoint.svg" alt="" />
                  Save
                </button>
              </>
            ) : null}
          </div>
        </div>

        {cuttingChoose ? (
          <div
            style={{
              position: "absolute",
              bottom: "85px",
              display: "flex",
              width: "100%",
              justifyContent: "center",
            }}
          >
            <div
              className="p-1"
              style={{
                display: "flex",
                flexWrap: "wrap",
                gap: "0.2em",
                border: "1px solid #F6F6F6",
                boxSizing: "border-box",
                background: "#FFFFFF",
                boxShadow: "0px 0px 4px rgba(0, 0, 0, 0.25)",
                justifyContent: "center",
              }}
            >
              <button
                disabled={!isEnable}
                type="button"
                onClick={this.onSlicePlaneX}
                className="btn btn-outline-secondary d-flex flex-column"
              >
                <img src="icons/cutting_x.svg" alt="" />X
              </button>
              <button
                disabled={!isEnable}
                type="button"
                onClick={this.onSlicePlaneY}
                className="btn btn-outline-secondary d-flex flex-column"
              >
                <img src="icons/cutting_y.svg" alt="" />Y
              </button>
              <button
                disabled={!isEnable}
                type="button"
                onClick={this.onSlicePlaneZ}
                className="btn btn-outline-secondary d-flex flex-column"
              >
                <img src="icons/cutting_z.svg" alt="" />Z
              </button>
            </div>
          </div>
        ) : null}
      </div>
    );
  }
}
