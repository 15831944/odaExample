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
import { actions } from "../redux/login";
import Header from "../components/Header";

class LoginPage extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      email: "",
      password: "",
      submitted: false,
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  componentDidMount() {
    this.props.clearError();
    this.props.loginFromLocalStorage();
  }

  handleChange(e) {
    const { name, value } = e.target;
    this.setState({ [name]: value });
  }

  handleSubmit(e) {
    e.preventDefault();
    this.setState({ submitted: true });
    const { email, password } = this.state;
    if (email && password) {
      this.props.login({ email, password, remember: true });
    }
  }

  render() {
    const { data, error } = this.props;
    const { email, password, submitted } = this.state;

    return (
      <div>
        <Header></Header>
        <div className="oda-content container-fluid">
          <div className="row">
            <div className="col-xs-12 col-md-6 offset-md-3 col-lg-4 offset-lg-4 auth-box">
              <h2 className="text-left" style={{ padding: "20px", color: "#18208a" }}>
                Authentication
              </h2>
              <form name="form" onSubmit={this.handleSubmit} style={{ width: "70%" }}>
                <div className={"form-group" + (submitted && !email ? " has-error" : "")}>
                  <label htmlFor="email" style={{ color: "#18208a" }}>
                    E-mail
                  </label>
                  <input
                    type="text"
                    className="form-control auth-input "
                    name="email"
                    placeholder="Email"
                    value={email}
                    onChange={this.handleChange}
                    style={{ borderRadius: 0 }}
                  />
                  {submitted && !email && <div className="help-block">email is required</div>}
                </div>
                <div className={"form-group" + (submitted && !password ? " has-error" : "")}>
                  <label htmlFor="password" style={{ color: "#18208a" }}>
                    Password
                  </label>
                  <input
                    type="password"
                    className="form-control auth-input"
                    name="password"
                    placeholder="Password"
                    value={password}
                    onChange={this.handleChange}
                    style={{ borderRadius: 0 }}
                  />
                  {submitted && !password && <div className="help-block">Password is required</div>}
                </div>
                <div className="form-group d-flex justify-content-start" style={{ columnGap: "1em" }}>
                  <button className="btn btn-outline-primary auth-input" style={{ flexGrow: 0.5, height: "40px" }}>
                    LOG IN
                  </button>
                  {data && (
                    // eslint-disable-next-line
                    <img src="data:image/gif;base64,R0lGODlhEAAQAPIAAP///wAAAMLCwkJCQgAAAGJiYoKCgpKSkiH/C05FVFNDQVBFMi4wAwEAAAAh/hpDcmVhdGVkIHdpdGggYWpheGxvYWQuaW5mbwAh+QQJCgAAACwAAAAAEAAQAAADMwi63P4wyklrE2MIOggZnAdOmGYJRbExwroUmcG2LmDEwnHQLVsYOd2mBzkYDAdKa+dIAAAh+QQJCgAAACwAAAAAEAAQAAADNAi63P5OjCEgG4QMu7DmikRxQlFUYDEZIGBMRVsaqHwctXXf7WEYB4Ag1xjihkMZsiUkKhIAIfkECQoAAAAsAAAAABAAEAAAAzYIujIjK8pByJDMlFYvBoVjHA70GU7xSUJhmKtwHPAKzLO9HMaoKwJZ7Rf8AYPDDzKpZBqfvwQAIfkECQoAAAAsAAAAABAAEAAAAzMIumIlK8oyhpHsnFZfhYumCYUhDAQxRIdhHBGqRoKw0R8DYlJd8z0fMDgsGo/IpHI5TAAAIfkECQoAAAAsAAAAABAAEAAAAzIIunInK0rnZBTwGPNMgQwmdsNgXGJUlIWEuR5oWUIpz8pAEAMe6TwfwyYsGo/IpFKSAAAh+QQJCgAAACwAAAAAEAAQAAADMwi6IMKQORfjdOe82p4wGccc4CEuQradylesojEMBgsUc2G7sDX3lQGBMLAJibufbSlKAAAh+QQJCgAAACwAAAAAEAAQAAADMgi63P7wCRHZnFVdmgHu2nFwlWCI3WGc3TSWhUFGxTAUkGCbtgENBMJAEJsxgMLWzpEAACH5BAkKAAAALAAAAAAQABAAAAMyCLrc/jDKSatlQtScKdceCAjDII7HcQ4EMTCpyrCuUBjCYRgHVtqlAiB1YhiCnlsRkAAAOwAAAAAAAAAAAA==" />
                  )}
                  <Link
                    to="/register"
                    className="btn btn-outline-info auth-input"
                    style={{ flexGrow: 0.5, height: "40px" }}
                  >
                    Register
                  </Link>
                </div>
              </form>
            </div>
          </div>
          <div className="row">
            <div className="col-xs-12 col-md-6 offset-md-3 col-lg-4 offset-lg-4 text-center">
              <span className="text-danger">{error}</span>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default connect(
  (state) => state.login,
  (dispatch) => ({
    login: (user) => dispatch(actions.login(user)),
    logout: () => dispatch(actions.logout()),
    loginFromLocalStorage: () => dispatch(actions.loginFromLocalStorage()),
    clearError: () => dispatch(actions.clearError()),
  })
)(LoginPage);
