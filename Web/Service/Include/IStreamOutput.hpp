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

#pragma once
#define OD_STREAM_OUTPUT_ATTRIBUTE_NAME L"$$OD_STREAM_OUTPUT_ATTRIBUTE"
#define OD_NATIVE_HANDLE_ENTITY_STORE L"$$OD_NATIVE_HANDLE_ENTITY_STORE"

enum Order
{
  MoveFront,
  MoveBottom
};

class IStreamOutput {
public:
  virtual void orderModify(const OdTvModelId& modelId, const OdArray<OdTvEntityId>& entitiesArray, Order direction) = 0;
};

class INativeHandleEntityStore {
public:
  virtual bool getByNativeHandle(OdDbHandle handle, OdTvEntityId& entityId) = 0;

  virtual bool bind(OdDbHandle handle, OdTvEntityId entityId) = 0;

  virtual void remove(OdDbHandle handle) = 0;
};