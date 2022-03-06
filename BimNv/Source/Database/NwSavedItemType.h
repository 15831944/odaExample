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


#ifndef TNW_SAVED_ITEM_TYPE_H_
#define TNW_SAVED_ITEM_TYPE_H_

namespace NwSavedItemType
{
  enum Enum
  {
    VIEW                  = 0x00,
    ANIMATION             = 0x01,
    CUT                   = 0x02,
    EMPTY                 = 0x03,// this value is writing if SavedItem object is null. It is GROUP_ITEM
    FOLDER                = 0x04,
    SELECTION_SET         = 0x05,
    // 0x06..0x1F - no
    ANIMATION_SCENE                 = 0x20,
    ANIMATION_FOLDER                = 0x21,
    ANIMATION_ROOT_FOLDER           = 0x22,
    ANIMATION_SCENE_FOLDER          = 0x23,
    ANIMATION_CAMERA_ANIMATION      = 0x24,
    ANIMATION_SELECTION_ANIMATION   = 0x25,
    ANIMATION_CLIP_ANIMATION        = 0x26,
    ANIMATION_CAMERA_KEYFRAME       = 0x27,
    ANIMATION_SELECTION_KEYFRAME    = 0x28,
    ANIMATION_CLIP_KEYFRAME         = 0x29,

    ANIMATION_SCRIPT                = 0x30,
    // 0x2A..0x31 - no
    CLASH_TEST                      = 0x32,
    CLASH_TEST_RESULT               = 0x33,
    CLASH_TEST_RESULT_GROUP         = 0x34,
    CLASH_TEST_FOLDER               = 0x35,
    CLASH_FIELD_FOLDER              = 0x36,
    CLASH_STATUS_FOLDER             = 0x37,
    // 0x38..0x39 - no
    CLASH_VALIDATION_ITEM           = 0x3A,
    // 0x3B - no
    TIMELINE_DATA_SOURCE_ITEM       = 0x3C,
    TIMELINE_TASK_ITEM              = 0x3D,
    TIMELINE_SIMULATION_TASK_TYPE   = 0x3E,
    TIMELINE_SIMULATION_APPEARENCE  = 0x3F,
    TIMELINE_SETTINGS_ITEM          = 0x40,
    // 0x41..0x45 - no
    FILE_INFO             = 0x46,
    SHEET_INFO            = 0x47,
    // 0x48..0x4F - no
    RE_MATERIAL           = 0x50,
    LIGHT_ITEM            = 0x51,
    LIGHT_ITEM_POINT      = 0x52,
    LIGHT_ITEM_DISTANT    = 0x53,
    LIGHT_ITEM_SPOT       = 0x54,
    LIGHT_ITEM_WEB        = 0x55,
    ZONE_ITEM             = 0x56,
    // 0x57..0x60 -no
  };
}
#endif  // TNW_SAVED_ITEM_TYPE_H_

