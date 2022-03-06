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

static std::map<OdString, swig_type_info*> Class2SwigPythonTypeInfo;

void InitClass2SwigPythonTypeInfo()
{
  size_t countTypes = swig_module.size;
  for (int idx = 0; idx < countTypes; idx++)
  {
    swig_type_info* type = swig_module.types[idx];
    OdString preparedStr = type->name;
    preparedStr = preparedStr.mid(3);
    Class2SwigPythonTypeInfo.insert(std::pair<OdString, swig_type_info*>(preparedStr, type));
  }
}

swig_type_info* GetPythonTypeInfoFrom(const OdRxClass* _class,swig_type_info* defaultIfNotFound)
{
  OdString type_name = _class->name();
  if (type_name[0] == 'A' && type_name[1] == 'c')
  {
    type_name = type_name.mid(2);
    type_name = "Od" + type_name;
  }
  std::map<OdString, swig_type_info*>::iterator it = Class2SwigPythonTypeInfo.find(type_name);
  if (it != Class2SwigPythonTypeInfo.end()) {
    swig_type_info* found = it->second;
    if (found == SWIGTYPE_p_OdRxObject && found != defaultIfNotFound)
      return defaultIfNotFound;
    else
      return found;
  }
  else
    return defaultIfNotFound;
}

