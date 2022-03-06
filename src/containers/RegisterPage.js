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
import { Link, Redirect } from "react-router-dom";
import { connect } from "react-redux";
import { actions } from "../redux/registration";
import Header from "../components/Header";

import clientFactory from "./../ClientFactory";

import "antd/dist/antd.css";
import { Form, Input, Button } from "antd";

const validateEmail = (email) => {
  return email.match(
    // eslint-disable-next-line
    /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/
  );
};

class RegisterPage extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      user: {
        email: { value: "", isError: false },
        username: { value: "", isError: false },
        password: { value: "", isError: false },
      },
      submitted: false,
      error: "",
      isLoading: false,
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  async registeredNewUser() {
    this.setState({ isLoading: true });

    const { user } = this.state;

    const userModel = {
      email: user.email.value,
      username: user.username.value,
      password: user.password.value,
    };

    const url = `${clientFactory.getConfig().registration_host}/register`;
    const request = {
      method: "POST",
      body: JSON.stringify(userModel),
      headers: {
        "Content-Type": "application/json",
      },
    };

    try {
      const response = await fetch(url, request);
      const answer = await response.json();

      if (response.ok) {
        this.setState({ submitted: true });
      } else if (answer.isOk === false && answer.description) {
        const userWithError = { ...user };
        userWithError.email.isError = true;
        this.setState({ user: userWithError, error: answer.description });
      } else {
        this.setState({
          error: "Registration server unavailable, please try again later",
        });
      }
    } catch (err) {
      this.setState({
        error: "Registration server unavailable, please try again later",
      });
    } finally {
      this.setState({ isLoading: false });
    }
  }

  handleChange(event) {
    const { name, value } = event.target;

    const { user } = this.state;
    const newUser = { ...user };

    if (name !== "email") {
      newUser[name] = { value: value, isError: !value };
    } else {
      newUser[name] = { value: value, isError: !validateEmail(value) };
      this.setState({
        error: !validateEmail(value) ? "Invalid email format" : "",
      });
    }
    this.setState({ user: newUser });
  }

  async handleSubmit() {
    const { user } = this.state;

    if (!user.email.isError && !user.username.isError && !user.password.isError) {
      await this.registeredNewUser();
    }
  }

  checkIsInvalid() {
    const { user } = this.state;

    return !(
      !user.email.isError &&
      !user.username.isError &&
      !user.password.isError &&
      user.email.value &&
      user.username.value &&
      user.password.value
    );
  }

  componentDidMount() {
    this.props.clearError();
  }

  render() {
    //const { registering } = this.props;
    const { user, submitted, error, isLoading } = this.state;

    if (!this.props.emailVerify && submitted) {
      return <Redirect to="/" />;
    }
    return (
      <div>
        <Header></Header>
        <div className="oda-content container-fluid">
          <div className="row">
            <div className="col-xs-12 col-md-6 offset-md-3 col-lg-4 offset-lg-4 auth-box">
              <h2 className="text-left" style={{ padding: "20px", color: "#18208a" }}>
                Register
              </h2>
              <Form layout="vertical" onFinish={this.handleSubmit}>
                <Form.Item
                  required
                  label="Email"
                  validateStatus={user.email.isError || error ? "error" : "success"}
                  help={error}
                >
                  <Input placeholder="Input you email" name="email" onChange={this.handleChange} />
                </Form.Item>

                <Form.Item required label="Name" validateStatus={user.username.isError ? "error" : "success"} help="">
                  <Input placeholder="Input you name" name="username" onChange={this.handleChange} />
                </Form.Item>

                <Form.Item
                  required
                  label="Password"
                  validateStatus={user.password.isError ? "error" : "success"}
                  help=""
                >
                  <Input.Password name="password" onChange={this.handleChange} />
                </Form.Item>

                <Form.Item>
                  <Button type="primary" loading={isLoading} disabled={this.checkIsInvalid()} htmlType="submit">
                    Register
                  </Button>
                  <Button htmlType="button" style={{ marginLeft: "10px" }}>
                    <Link to="/login">Cancel</Link>
                  </Button>
                </Form.Item>
              </Form>
            </div>
          </div>
          <div className="row">
            <div className="col-xs-12 col-md-6 offset-md-3 col-lg-4 offset-lg-4 text-center">
              {this.props.emailVerify && (
                <span className="text-green text-center">
                  {" "}
                  User has been registered. To verify the data provided we have sent you a confirmation email. Please
                  read your email, and click on the web link it contains. A registered user without verification will
                  have access for several days.
                </span>
              )}
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default connect(
  (state) => state.registration,
  (dispatch) => ({
    register: (user) => dispatch(actions.register(user)),
    clearError: () => dispatch(actions.clearError()),
  })
)(RegisterPage);
