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
import propTypes from "prop-types";
//import searchIcon from '../images/file-list/ic_search_24px.png';

export class SearchPanel extends Component {
  state = {
    extFilter: "*",
    wordFilter: "",
  };

  handleChangeFilter = (nextState) => {
    this.setState(nextState, () => {
      if (this.props.onChangeFilter) {
        this.props.onChangeFilter({
          wordFilter: this.state.wordFilter,
          extFilter: this.state.extFilter === "*" ? "" : this.state.extFilter,
        });
      }
    });
  };

  render() {
    const filterTypes = ["*", ...this.props.supportFormats].map((name, index) => (
      <a href="#/" className="dropdown-item" key={index} onClick={() => this.handleChangeFilter({ extFilter: name })}>
        {name}
      </a>
    ));

    return (
      <div className="search-box">
        <span className="material-icons">search</span>

        <input
          id="file-search-box"
          type="text"
          className="file-list-input ml-2"
          required=""
          onChange={(ev) => this.handleChangeFilter({ wordFilter: ev.target.value })}
        />
        <div className="dropdown dropleft">
          <button
            className="btn btn-outline-secondary text-dark bg-white dropdown-toggle"
            type="button"
            id="file-filter"
            data-toggle="dropdown"
            aria-haspopup="true"
            aria-expanded="false"
          >
            Type: {this.state.extFilter}
          </button>

          <div className="dropdown-menu" aria-labelledby="file-filter">
            {filterTypes}
          </div>
        </div>
      </div>
    );
  }
}

SearchPanel.propTypes = {
  supportFormats: propTypes.array.isRequired,
  onChangeFilter: propTypes.func.isRequired,
};
