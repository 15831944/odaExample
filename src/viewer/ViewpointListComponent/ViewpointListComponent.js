import { Component } from "react";
import Window from "../../components/Window";
import { SubscribeSubjectContext } from "../../utils/SubscribeSubjectContext";

const defaultState = {
  viewpoints: [],
};

export class ViewpointListComponent extends Component {
  state = { ...defaultState };

  constructor(props) {
    super(props);
    this.eventsConnection = props.eventsConnection;
    this.subscribeSubjectContext = new SubscribeSubjectContext();

    this.subscribeSubjectContext.subscribe(this.eventsConnection.changeViewpoints, (viewpoints) =>
      this.setState({ viewpoints })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.addViewpoint, (viewpoint) =>
      this.setState({ viewpoints: this.state.viewpoints.concat([viewpoint]) })
    );

    this.subscribeSubjectContext.subscribe(this.eventsConnection.modifyViewpoint, (viewpoint) => {
      const index = this.state.viewpoints.findIndex((vp) => vp.guid === viewpoint.guid);
      if (index !== -1) {
        this.state.viewpoints[index] = viewpoint;
        this.setState({ viewpoints: [...this.state.viewpoints] });
      }
    });
  }

  componentWillUnmount() {
    this.subscribeSubjectContext.unsubscribe();
  }

  onRemoveViewpoint(data, index) {
    this.eventsConnection.onRemoveViewpoint.next(data);
    this.setState({
      viewpoints: this.state.viewpoints.filter((_, i) => i !== index),
    });
  }

  render() {
    const { viewpoints } = this.state;

    const viewPointsListTemplate = viewpoints.map((data, index) => {
      return (
        <div className="card" key={index} style={{ borderRadius: "0" }}>
          <img
            src={data.snapshot ? data.snapshot : "icons/default.svg"}
            style={{ width: "256px", height: "192px", cursor: "pointer" }}
            className="card-img-top"
            alt="..."
            onClick={() => this.eventsConnection.onSelectViewpoint.next(data)}
          ></img>

          <div className="card-body" style={{ padding: "0.1em" }}>
            <h5 style={{ color: "#05093B", align: "center" }} className="card-title">
              {data.description}
              <img
                src="icons/remove.svg"
                style={{ cursor: "pointer", float: "right" }}
                width="25px"
                height="25px"
                alt="..."
                onClick={() => this.onRemoveViewpoint(data, index)}
              ></img>
            </h5>
          </div>
        </div>
      );
    });

    return (
      <Window
        className="object-explorer"
        title="View points"
        onClose={() => {
          this.eventsConnection.onClose.next();
        }}
      >
        {viewPointsListTemplate}
      </Window>
    );
  }
}
