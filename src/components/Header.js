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
import logo from "../images/logo-full.svg";
import ExamplesLink from "../components/ExamplesLink";
import DocLink from "../components/DocLink";
import { SpinnerWithText } from "../components/SpinnerWithText";

function expression(selector, ...array) {
  // eslint-disable-next-line
  return (props) => (props && array[selector(props)](props)) || null;
}

function firstTrueIndex(...array) {
  const index = array.findIndex((el) => el);
  return index === -1 ? 0 : index;
}

export default function Header(props) {
  const fileInfo = props.fileInfo;

  const fileName = expression(
    (file) => firstTrueIndex(!file, file, false),
    (fileInfo) => (
      <SpinnerWithText>
        <span>Loading file info ...</span>
      </SpinnerWithText>
    ),
    (fileInfo) => <span className="px-2">{fileInfo.name}</span>,
    (fileInfo) => <span className="px-2">File not found</span>
  );

  return (
    <div
      className="col mb-1 py-1"
      style={{
        display: "flex",
        justifyContent: "space-between",
        flexWrap: "wrap",
        boxSizing: "border-box",
        borderBottom: "1px solid secondarygrey",
        gap: "1em",
        boxShadow: "0px 2px 4px rgba(0, 0, 0, 0.35)",
      }}
    >
      {/* Left side */}
      <div style={{ display: "flex", alignItems: "center" }}>
        <img src={logo} className="logo-icon" alt="Open Design"></img>
        {fileInfo ? <img className="col" src="icons/file_pointer.svg" alt="" /> : null}
        {fileInfo ? fileName(fileInfo) : null}
      </div>

      {/* Right side */}
      <div style={{ display: "flex", gap: "0.2em" }}>
        <ExamplesLink />
        <DocLink />
        {props.children}
      </div>
    </div>
  );
}
