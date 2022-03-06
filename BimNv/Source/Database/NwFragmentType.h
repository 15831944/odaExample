/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
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
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////


#ifndef TNW_FRAGMENT_TYPE_H_
#define TNW_FRAGMENT_TYPE_H_

namespace NwFragmentType
{
  enum Enum
  {
    // Common
    FRAGMENT_LIGHT_DISTANCE = 0x1B,//old FRAGMENT_LIGHT_1B
    FRAGMENT_LIGHT_POINT = 0x1C,//old FRAGMENT_LIGHT_1C
    FRAGMENT_LIGHT_SPOT = 0x1D,//old FRAGMENT_LIGHT_1D
    FRAGMENT_MATERIAL_DOUBLE = 0x1F,
    FRAGMENT_TRANSFORMATION_DOUBLE = 0x27,
    FRAGMENT_TRANSLATION_DOUBLE = 0x28,
    FRAGMENT_ROTATION_DOUBLE = 0x29,
    FRAGMENT_NODETYPE = 0x34, // Such type is presented only in H_FRAGMENT_NODETYPE structure.
    FRAGMENT_KEYVALUE = 0x34,
    FRAGMENT_INSTANCEVALUE = 0x42,
    FRAGMENT_XREF = 0x46,
    FRAGMENT_TEXTBOXES = 0x4C, // Such tab in NWD is presented as couple of textboxes ("Name" and "Text").
    FRAGMENT_HYPERLINKS = 0x4F,
    FRAGMENT_GROUP_HEADER = 0x56,
    FRAGMENT_PUBLISH_OPTIONS = 0x5C,
    FRAGMENT_MATERIAL_PRESENTER = 0x61,
    FRAGMENT_AUTODESK_MATERIAL_PROPERTIES_SET = 0xB6, // Before nw 2016
    FRAGMENT_AUTODESK_MATERIAL_PROPERTIES_SET_TXT = 0xB9, // From nw 2016

    // For Geometry
    FRAGMENT_PARAMS_AND_FACES = 0x3A,
    FRAGMENT_VERTEXES = 0x3C,
    FRAGMENT_UVPARAMS = 0x3D,
    FRAGMENT_NORMALES_AND_FACES = 0x64,
    ELEMENT_FACESET = 0x5E,
    ELEMENT_LINESET = 0x5F,
    ELEMENT_POINTSET = 0x60,
    ELEMENT_TEXT = 0x67,
    ELEMENT_ELLIPTICAL_SHAPE = 0x68,
    ELEMENT_TUBE = 0x69,

    // For PartitionProps
    FRAGMENT_ARBITRARY_PLANE = 0x62,

    // For LogicalHierarchy
    FRAGMENT_GEOMETRY = 0x16,
    FRAGMENT_FILE = 0x20,
    FRAGMENT_NODE = 0x35,
    FRAGMENT_AUTODESK_MATERIAL = 0xC8,

    // For SharedNodes
    FRAGMENT_FONT = 0x66,

    // For Fragments
    FRAGMENT_COMPONENT_REFERENCE = 0x0D,
    FRAGMENT_REUSE_OPTIONS = 0x37,
    FRAGMENT_COLORS = 0x36,
    FRAGMENT_GEOMETRY_REFERENCE = 0x5D,
    FRAGMENT_TRANSFORMATION_TRS = 0x10,
    FRAGMENT_TRANSFORMATION_MATRIX = 0x11,
    FRAGMENT_MOVE_VECTOR = 0x0E,
    FRAGMENT_ROTATION = 0x0F,
    FRAGMENT_SCHEMA = 0xB7,

    // For SavedViews
    FRAGMENT_NODE_OVERRIDES_ELEMENT = 0x59,

    // Not supported data
    FRAGMENT_EMBEDDED_DATA = 0x7A, // it looks like embedded data (pdf?)
    FRAGMENT_INTERNAL_REFERENCE = 0xAC, // reference to some internal data (?). Found for input .pdf files.
    FRAGMENT_EXTERNAL_REFERENCE = 0xB5 // reference to external file. For example, .rcp.
  };

  static bool isDefined(NwFragmentType::Enum type)
  {
    return (type == FRAGMENT_LIGHT_DISTANCE)
      || (type == FRAGMENT_LIGHT_POINT)
      || (type == FRAGMENT_LIGHT_SPOT)
      || (type == FRAGMENT_MATERIAL_DOUBLE)
      || (type == FRAGMENT_TRANSFORMATION_DOUBLE)
      || (type == FRAGMENT_TRANSLATION_DOUBLE)
      || (type == FRAGMENT_ROTATION_DOUBLE)
      || (type == FRAGMENT_NODETYPE)
      || (type == FRAGMENT_KEYVALUE)
      || (type == FRAGMENT_INSTANCEVALUE)
      || (type == FRAGMENT_XREF)
      || (type == FRAGMENT_TEXTBOXES)
      || (type == FRAGMENT_HYPERLINKS)
      || (type == FRAGMENT_GROUP_HEADER)
      || (type == FRAGMENT_PUBLISH_OPTIONS)
      || (type == FRAGMENT_MATERIAL_PRESENTER)
      || (type == FRAGMENT_AUTODESK_MATERIAL_PROPERTIES_SET)
      || (type == FRAGMENT_AUTODESK_MATERIAL_PROPERTIES_SET_TXT)

      || (type == FRAGMENT_PARAMS_AND_FACES)
      || (type == FRAGMENT_VERTEXES)
      || (type == FRAGMENT_UVPARAMS)
      || (type == FRAGMENT_NORMALES_AND_FACES)
      || (type == ELEMENT_FACESET)
      || (type == ELEMENT_LINESET)
      || (type == ELEMENT_POINTSET)
      || (type == ELEMENT_TEXT)
      || (type == ELEMENT_ELLIPTICAL_SHAPE)
      || (type == ELEMENT_TUBE)

      || (type == FRAGMENT_ARBITRARY_PLANE)

      || (type == FRAGMENT_GEOMETRY)
      || (type == FRAGMENT_FILE)
      || (type == FRAGMENT_NODE)
      || (type == FRAGMENT_AUTODESK_MATERIAL)

      || (type == FRAGMENT_FONT)

      || (type == FRAGMENT_COMPONENT_REFERENCE)
      || (type == FRAGMENT_REUSE_OPTIONS)
      || (type == FRAGMENT_COLORS)
      || (type == FRAGMENT_GEOMETRY_REFERENCE)
      || (type == FRAGMENT_TRANSFORMATION_TRS)
      || (type == FRAGMENT_TRANSFORMATION_MATRIX)
      || (type == FRAGMENT_MOVE_VECTOR)
      || (type == FRAGMENT_ROTATION)
      || (type == FRAGMENT_SCHEMA)

      || (type == FRAGMENT_EMBEDDED_DATA)
      || (type == FRAGMENT_INTERNAL_REFERENCE)
      || (type == FRAGMENT_EXTERNAL_REFERENCE)
      ;
  }
}

#endif  // TNW_FRAGMENT_TYPE_H_

