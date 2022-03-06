import { Component } from "react";

import Header from "../components/Header";

export class SideNavigateMenu extends Component {
  render() {
    return (
      <>
        <div>
          <Header></Header>
        </div>
        <div className="d-flex" style={{ gap: "5px" }}>
          <div
            className="d-flex flex-column justify-content-center"
            style={{
              width: "300px",
              boxShadow: "0 3px 6px rgba(0,0,0,0.16), 0 3px 6px rgba(0,0,0,0.23)",
            }}
          >
            <div
              class="list-group list-group-flush"
              style={{
                padding: "5px",
                transition: "all 200ms",
                color: "rgb(5, 9, 59)",
              }}
            >
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid rgb(24, 32, 138)",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">description</span>
                <div>Files</div>
              </div>
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">backup_table</span>
                <div>Assemblies</div>
              </div>
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">work</span>
                <div>Projects</div>
              </div>
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">history_edu</span>
                <div>Sand box</div>
              </div>
            </div>

            <div
              class="list-group list-group-flush"
              style={{
                padding: "5px",
                transition: "all 200ms",
                color: "rgb(5, 9, 59)",
                marginTop: "auto",
              }}
            >
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">dashboard</span>
                <div>Dash board (only admin)</div>
              </div>
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">settings</span>
                <div>Settings</div>
              </div>
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">account_circle</span>
                <div>Account</div>
              </div>
              <div
                class="list-group-item d-flex"
                style={{
                  gap: "5px",
                  borderLeft: "5px solid white",
                  cursor: "pointer",
                }}
              >
                <span class="material-icons">logout</span>
                <div>Logout</div>
              </div>
            </div>
          </div>
          <div
            style={{
              width: "calc(100% - 300px)",
              background: "white",
              padding: "5px",
            }}
          >
            {this.props.children}
          </div>
        </div>
      </>
    );
  }
}
