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
import { actions as geometryLoader } from "../redux/geometryLoader";

function LayoutsBar(props) {
  const { geometryLoaded } = props;
  const metadata = props.metadata || [];

  const getStyleForMetadata = (mdata) => {
    const isActive = props.activeLayout && mdata.name === props.activeLayout.name;
    return {
      cursor: "pointer",
      backgroundColor: isActive ? "rgb(64,64,64)" : "white",
      color: isActive ? "white" : "black",
    };
  };

  const list = metadata.map((data, index) => {
    return (
      <div
        key={index}
        style={getStyleForMetadata(data)}
        className="dropdown-item"
        onClick={() => props.selectLayout(data)}
      >
        {data.name}
      </div>
    );
  });

  return (
    <div className={geometryLoaded ? "dropdown" : "dropdown text-disabled"} disabled={geometryLoaded}>
      <div
        className={geometryLoaded ? "viewer-button d-flex" : "viewer-button d-flex text-disabled"}
        id="layoutsBar"
        data-toggle={geometryLoaded ? "dropdown" : ""}
        aria-haspopup="true"
        aria-expanded="false"
      >
        <i className="material-icons mi-dark">assignment</i>
        <span> Layouts</span>
      </div>
      <div
        className="dropdown-menu"
        style={{
          top: "90px",
          left: "0px",
          maxHeight: "500px",
          overflow: "auto",
        }}
        aria-labelledby="layoutsBar"
      >
        {list}
      </div>
    </div>
  );
}

export default connect(
  (state) => ({
    geometryLoaded: state.viewer.geometryLoaded,
    metadata: state.geometry.metadata,
    activeLayout: state.geometry.activeLayout,
  }),
  (dispatch, props) => ({
    //selectLayout: (metadata)=> dispatch({type:"SELECT_LAYOUT", payload: metadata})
    selectLayout: (metadata) => {
      dispatch(geometryLoader.loadLayout(props.fileInfo.data.id, metadata));
    },
  })
)(LayoutsBar);
