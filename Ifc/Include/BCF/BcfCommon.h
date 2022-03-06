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

#ifndef _BFC_COMMON_H
#define _BFC_COMMON_H

#include "OdPlatformSettings.h"
#include "IfcBuildOptions.h"

#include "RxObject.h"
#include "SmartPtr.h"

#include "BcfUnset.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

#define MAX_ENTITY_COLLECTION_SIZE  1024
#define FILE_BUFFER_SIZE            1024

#define PROJECT_FILE_NAME           "project.bcfp"
#define VERSION_FILE_NAME           "bcf.version"
#define MARKUP_FILE_NAME            "markup.bcf"
#define DEFAULT_VIEWPOINT_FILE_NAME "viewpoint.bcfv"
#define VIEWPOINT_FILE_EXTENSION    "bcfv"
#define DEFAULT_SNAPSHOT_FILE_NAME  "snapshot.png"
#define SNAPSHOT_FILE_EXTENSION     "png"

#define DECLARE_SET(MethodName, VariableType, VariableName)                       \
                                                                                  \
void set##MethodName(const VariableType &VariableName##Value);

#define DEFINE_SET(ClassName, MethodName, VariableType, VariableName)             \
                                                                                  \
void ClassName::set##MethodName(const VariableType &VariableName##Value)          \
{                                                                                 \
  VariableName = VariableName##Value;                                             \
}

#define DECLARE_GET(MethodName, VariableType, VariableName)                       \
                                                                                  \
VariableType& get##MethodName();

#define DEFINE_GET(ClassName, MethodName, VariableType, VariableName)             \
                                                                                  \
VariableType& ClassName::get##MethodName()                                        \
{                                                                                 \
  return VariableName;                                                            \
}

#define DECLARE_CONST_ACCESSORS(MethodName, VariableType, VariableName)           \
                                                                                  \
const VariableType& get##MethodName() const;                                      \
                                                                                  \
bool is##MethodName##Unset() const;

#define DEFINE_CONST_ACCESSORS(ClassName, MethodName, VariableType, VariableName) \
                                                                                  \
const VariableType& ClassName::get##MethodName() const                            \
{                                                                                 \
  return VariableName;                                                            \
}                                                                                 \
                                                                                  \
bool ClassName::is##MethodName##Unset() const                                     \
{                                                                                 \
  return OdBcf::Utils::isUnset(VariableName);                                     \
}

#define DECLARE_ACCESSORS(MethodName, VariableType, VariableName)                 \
                                                                                  \
DECLARE_SET(      MethodName, VariableType, VariableName)                         \
DECLARE_GET(      MethodName, VariableType, VariableName)                         \
DECLARE_CONST_ACCESSORS(MethodName, VariableType, VariableName)

#define DEFINE_ACCESSORS(ClassName, MethodName, VariableType, VariableName)       \
                                                                                  \
DEFINE_SET(      ClassName, MethodName, VariableType, VariableName)               \
DEFINE_GET(      ClassName, MethodName, VariableType, VariableName)               \
DEFINE_CONST_ACCESSORS(ClassName, MethodName, VariableType, VariableName)

#define INIT_RESULT(VariableName)                                                 \
                                                                                  \
OdResult VariableName##Local;                                                     \
if (VariableName == NULL)                                                         \
{                                                                                 \
  VariableName = &VariableName##Local;                                            \
}                                                                                 \
*VariableName = eOk;                                                         

} //namespace OdBcf

#endif // _BFC_COMMON_H
