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

#include "OdaCommon.h"
#include "ExPrintConsole.h"
#include <ctime>

#include "daiModule.h"
#include "ValidationNotifiers.h"

using namespace OdDAI;

ODRX_CONS_DEFINE_MEMBERS(ConsoleValidationNotifier, ValidationNotifier, RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(TextValidationNotifier, ValidationNotifier, RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(HtmlValidationNotifier, ValidationNotifier, RXIMPL_CONSTR);

namespace{

  OdAnsiString getInctanceName(const OdDAIObjectId& id)
  {
    if (id)
    {
      OdAnsiString str;
      str.format("#%lu %s", (OdUInt64)id.getHandle(), id.getNested()->getInstanceType()->originalName().c_str());
      return str;
    }
    return "";
  }
    
  OdAnsiString translateObjectToText(OdRxObjectPtr obj)
{
  OdDAI::ApplicationInstancePtr instance = OdDAI::ApplicationInstance::cast(obj);
  if (!instance.isNull())
  {
    return getInctanceName(instance->id());
  }

  ODA_ASSERT_ONCE(!"Object type is not implemented yet.");

  return "";
}

OdAnsiString translateObjectsArrayToText(const OdRxObjectPtrArray& objects, OdAnsiString newLine = "\n")
{
  OdAnsiString str;
  for (auto obj : objects)
  {
    str += translateObjectToText(obj);
    if (obj != objects.last())
      str += newLine;
  }
  return str;
}
}

void ConsoleValidationNotifier::onValidationResult(OdDAIObjectId instanceId, ValidationTaskPtr validationTask, OdSharedPtr<ValidationTask::InvalidValidationParamsBase> invalidParams, Logical result)
{
  if (ValidationTask::InvalidValidationParams* invalidValidationParams = dynamic_cast<ValidationTask::InvalidValidationParams*>(invalidParams.get()))
  {
    if (invalidValidationParams->invalidAttributes.size() > 0 && invalidValidationParams->invalidWhereRules.size() > 0)
      for (int i = 0; i < invalidValidationParams->invalidAttributes.size(); ++i)
      {
        odPrintConsoleString(L"#%lu %s   %s   %s (WR: %s)   %s\n", (OdUInt64)instanceId.getHandle(), OdString(instanceId.getNested()->typeName()).c_str(), OdString(validationTask->description()).c_str(), OdString(invalidValidationParams->invalidAttributes.at(i)->originalName()).c_str(), OdString(invalidValidationParams->invalidWhereRules.at(i)->originalLabel()).c_str(), OdString(result2string(result)).c_str());
      }
    else if (invalidValidationParams->invalidAttributes.size() > 0)
    {
      for (auto it : invalidValidationParams->invalidAttributes)
      {
        odPrintConsoleString(L"#%lu %s   %s   %s   %s\n", (OdUInt64)instanceId.getHandle(), OdString(instanceId.getNested()->typeName()).c_str(), OdString(validationTask->description()).c_str(), OdString(it->originalName()).c_str(), OdString(result2string(result)).c_str());
      }
    }
    else if (invalidValidationParams->invalidWhereRules.size() > 0)
    {
      for (auto it : invalidValidationParams->invalidWhereRules)
      {
        odPrintConsoleString(L"#%lu %s   %s   WR: %s   %s\n", (OdUInt64)instanceId.getHandle(), OdString(instanceId.getNested()->typeName()).c_str(), OdString(validationTask->description()).c_str(), OdString(it->originalLabel()).c_str(), OdString(result2string(result)).c_str());
      }
    }
    else
    {
      odPrintConsoleString(L"#%lu %s   %s   %s\n", (OdUInt64)instanceId.getHandle(), OdString(instanceId.getNested()->typeName()).c_str(), OdString(validationTask->description()).c_str(), OdString(result2string(result)).c_str());
    }
  }
  else if (OdDAI::ValidationTask::InvalidRxArrayValidationParams* invalidValidationParams = dynamic_cast<OdDAI::ValidationTask::InvalidRxArrayValidationParams*>(invalidParams.get()))
  {
    for (const auto& params : invalidValidationParams->invalidParams)
    {
      for (auto obj : params.invalidObjects)
      {
        odPrintConsoleString(L"%s  ", OdString(translateObjectToText(obj)).c_str());
      }
      odPrintConsoleString(L"%s   %s   %s\n", OdString(validationTask->description()).c_str(), OdString(params.textMessage).c_str(),OdString(result2string(result)).c_str());
    }
  }
  else if (OdDAI::ValidationTask::InvalidRxObjectsValidationParams* invalidValidationParams = dynamic_cast<OdDAI::ValidationTask::InvalidRxObjectsValidationParams*>(invalidParams.get()))
  {
    for (auto obj : invalidValidationParams->invalidObjects)
    {
      odPrintConsoleString(L"%s  ", OdString(translateObjectToText(obj)).c_str());
    }
    odPrintConsoleString(L"%s   %s   %s\n", OdString(validationTask->description()).c_str(), OdString(invalidValidationParams->textMessage).c_str(), OdString(result2string(result)).c_str());
  }
  else
  if (instanceId.isValid())
  {
    odPrintConsoleString(L"#%lu %s   %s   %s\n", (OdUInt64)instanceId.getHandle(), OdString(instanceId.getNested()->typeName()).c_str(), OdString(validationTask->description()).c_str(), OdString(result2string(result)).c_str());
  }
  else
  {
    odPrintConsoleString(L"Invalid instanceId\n");
  }
}

void ConsoleValidationNotifier::onValidationResult(ValidationTaskPtr validationTask, const OdDAIObjectIds& invalidObjects, OdDAI::Logical result)
{
  if (invalidObjects.size() > 0)
  {
    for (auto it : invalidObjects)
    {
      odPrintConsoleString(L"#%lu %s ", (OdUInt64)it.getHandle(), OdString(it.getNested()->typeName()).c_str());
    }
    odPrintConsoleString(L"  %s  %s", OdString(validationTask->description()).c_str(), OdString(result2string(result)).c_str());
  }
  else
  {
    odPrintConsoleString(L"%s   %s\n", OdString(validationTask->description()).c_str(), OdString(result2string(result)).c_str());
  }
}

void ConsoleValidationNotifier::onStartValidation()
{
  if (m_extraInfo)
    odPrintConsoleString(L"File name: %s\nFile schema: %s\n", OdString(m_extraInfo->fileName).c_str(), OdString(m_extraInfo->schemaName).c_str());
}

void TextValidationNotifier::onValidationResult(OdDAIObjectId instanceId, ValidationTaskPtr validationTask, OdSharedPtr<ValidationTask::InvalidValidationParamsBase> invalidParams, Logical result)
{
  if (ValidationTask::InvalidValidationParams* invalidValidationParams = dynamic_cast<ValidationTask::InvalidValidationParams*>(invalidParams.get()))
  {
    if (invalidValidationParams->invalidAttributes.size() > 0 && invalidValidationParams->invalidWhereRules.size() > 0)
      for (int i = 0; i < invalidValidationParams->invalidAttributes.size(); ++i)
      {
        m_textOutFile << "#" << (OdUInt64)instanceId.getHandle() << " " << instanceId.getNested()->typeName().c_str() << " \t" << invalidValidationParams->invalidAttributes.at(i)->originalName().c_str() << " (WR:" << invalidValidationParams->invalidWhereRules.at(i)->originalLabel().c_str() << ")\t\t" << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
      }
    else if (invalidValidationParams->invalidAttributes.size() > 0)
      for (auto it : invalidValidationParams->invalidAttributes)
      {
        m_textOutFile << "#" << (OdUInt64)instanceId.getHandle() << " " << instanceId.getNested()->typeName().c_str() << " \t" << it->originalName().c_str() << " \t\t" << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
      }
    else if (invalidValidationParams->invalidWhereRules.size() > 0)
      for (auto it : invalidValidationParams->invalidWhereRules)
      {
        m_textOutFile << "#" << (OdUInt64)instanceId.getHandle() << " " << instanceId.getNested()->typeName().c_str() << " \tWR:" << it->originalLabel().c_str() << " \t\t" << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
      }
    else
    {
      m_textOutFile << "#" << (OdUInt64)instanceId.getHandle() << " " << instanceId.getNested()->typeName().c_str() << " \t\t" << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
    }
  }
  else if (OdDAI::ValidationTask::InvalidRxArrayValidationParams* invalidValidationParams = dynamic_cast<OdDAI::ValidationTask::InvalidRxArrayValidationParams*>(invalidParams.get()))
  {
    for (const auto& params : invalidValidationParams->invalidParams)
    {
      for (auto obj : params.invalidObjects)
      {
        m_textOutFile << translateObjectToText(obj) << "  ";
      }
      m_textOutFile << " \t\t" << validationTask->description().c_str() << " \t" << params.textMessage.c_str() << " \t" << result2string(params.validationResult).c_str() << "\n";
    }
  }
  else if (OdDAI::ValidationTask::InvalidRxObjectsValidationParams* invalidValidationParams = dynamic_cast<OdDAI::ValidationTask::InvalidRxObjectsValidationParams*>(invalidParams.get()))
  {
    for (auto obj : invalidValidationParams->invalidObjects)
    {
      m_textOutFile << translateObjectToText(obj) << "  ";
    }
    m_textOutFile << " \t\t" << validationTask->description().c_str() << " \t" << invalidValidationParams->textMessage.c_str() << " \t" << result2string(invalidValidationParams->validationResult).c_str() << "\n";
  }
  else
  if (instanceId.isValid())
  {
    m_textOutFile << "#" << (OdUInt64)instanceId.getHandle() << " " << instanceId.getNested()->typeName().c_str() << " \t\t" << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
  }
  else
  {
    m_textOutFile << "instanceId is invalid\n";
  }
}

void TextValidationNotifier::onValidationResult(ValidationTaskPtr validationTask, const OdDAIObjectIds& invalidObjects, OdDAI::Logical result)
{
  if (invalidObjects.size() > 0)
  {
    for (auto it : invalidObjects)
    {
      m_textOutFile << "#" << (OdUInt64)it.getHandle() << " " << it.getNested()->typeName().c_str() << " ";
    }
    m_textOutFile << "\t" << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
  }
  else
  {
    m_textOutFile << validationTask->description().c_str() << " \t" << result2string(result).c_str() << "\n";
  }
}

void TextValidationNotifier::onStartValidation()
{
  m_textOutFile.open(m_fileName.c_str());
  if (!m_textOutFile.is_open())
    throw("Wrong text file name");

  time_t seconds = time(NULL);
  m_textOutFile << "Automatically generated validation log file\n"
    << "This file contains information about results of validation tasks\n";
  
  if (m_extraInfo)
    m_textOutFile << "File name: " << m_extraInfo->fileName.c_str() << "\n"
    << "File schema: " << m_extraInfo->schemaName.c_str() << "\n";
  
  m_textOutFile << "Date: " << std::ctime(&seconds) <<"\n\n\n";
}

void TextValidationNotifier::onEndValidation()
{
  m_textOutFile.close();
}

void TextValidationNotifier::setFileName(const OdAnsiString& fileName)
{
  m_fileName = fileName;
}

void HtmlValidationNotifier::onValidationResult(OdDAIObjectId instanceId, ValidationTaskPtr validationTask, OdSharedPtr<ValidationTask::InvalidValidationParamsBase> invalidParams, Logical result)
{
  if (instanceId != m_actualInstanceId)
  {
    addInstanceToFile();
    m_actualInstanceId = instanceId;
    m_invalidAttributes.clear();
  }

  if (ValidationTask::InvalidValidationParams* invalidValidationParams = dynamic_cast<ValidationTask::InvalidValidationParams*>(invalidParams.get()))
  {
    if (invalidValidationParams->invalidAttributes.size() > 0 && invalidValidationParams->invalidWhereRules.size() > 0)
    {
      for (int i = 0; i < invalidValidationParams->invalidAttributes.size(); ++i)
      {
        m_invalidAttributes.insert(std::make_pair(invalidValidationParams->invalidAttributes.at(i)->originalName() + " (WR: " + invalidValidationParams->invalidWhereRules.at(i)->originalLabel() + ")", std::make_pair(validationTask->description(), result)));
      }
    }
    else if (invalidValidationParams->invalidAttributes.size() > 0)
    {
      for (auto it : invalidValidationParams->invalidAttributes)
      {
        m_invalidAttributes.insert(std::make_pair(it->originalName(), std::make_pair(validationTask->description(), result)));
      }
    }
    else if (invalidValidationParams->invalidWhereRules.size() > 0)
    {
      for (auto it : invalidValidationParams->invalidWhereRules)
      {
        m_invalidAttributes.insert(std::make_pair("WR:" + it->originalLabel(), std::make_pair(validationTask->description(), result)));
      }
    }
    else
    {
      m_invalidAttributes.insert(std::make_pair(nullptr, std::make_pair(validationTask->description(), result)));
    }
  }
  else if (OdDAI::ValidationTask::InvalidRxArrayValidationParams* invalidValidationParams = dynamic_cast<OdDAI::ValidationTask::InvalidRxArrayValidationParams*>(invalidParams.get()))
  {
    for (const auto& params : invalidValidationParams->invalidParams)
    {
      m_invalidAttributes.insert(std::make_pair(translateObjectsArrayToText(params.invalidObjects, "<br>"),
        std::make_pair((params.textMessage.isEmpty() ? validationTask->description() : validationTask->description() + "<br>" + params.textMessage),
          params.validationResult)));
    }
  }
  else if (OdDAI::ValidationTask::InvalidRxObjectsValidationParams* invalidValidationParams = dynamic_cast<OdDAI::ValidationTask::InvalidRxObjectsValidationParams*>(invalidParams.get()))
  {
    m_invalidAttributes.insert(std::make_pair(translateObjectsArrayToText(invalidValidationParams->invalidObjects, "<br>"),
      std::make_pair((invalidValidationParams->textMessage.isEmpty() ? validationTask->description() : validationTask->description() + "<br>" + invalidValidationParams->textMessage),
        invalidValidationParams->validationResult)));
  }
  else
  {
    m_invalidAttributes.insert(std::make_pair(nullptr, std::make_pair(validationTask->description(), result)));
  }
}

void HtmlValidationNotifier::onValidationResult(ValidationTaskPtr validationTask, const OdDAIObjectIds& invalidObjects, OdDAI::Logical result)
{
  if (invalidObjects.size() > 0)
  {
    m_htmlOutFile << "<tr><td>";
    for (auto it : invalidObjects)
    {
      m_htmlOutFile << "#" << (OdUInt64)it.getHandle() << " " << it.getNested()->typeName().c_str();
      if (&it != &invalidObjects.last())
        m_htmlOutFile << "<br>";
    }
    m_htmlOutFile << "</td><td></td><td>" << validationTask->description().c_str() << "</td><td>" << result2string(result).c_str() << "</td></tr>\n";
  }
  else
  {
    m_htmlOutFile << "<tr><td></td><td></td><td>" << validationTask->description().c_str() << "</td><td>" << result2string(result).c_str() << "</td></tr>\n";
  }
}

void HtmlValidationNotifier::addInstanceToFile()
{
  int ununicAttrCountdown = 0;
  for (auto it = m_invalidAttributes.cbegin(); it != m_invalidAttributes.cend(); ++it)
  {
    if (it == m_invalidAttributes.cbegin())
    {
      m_htmlOutFile
        << "<tr><td rowspan=" << m_invalidAttributes.size() << ">#"
        << (m_actualInstanceId.isValid() ? (OdUInt64)m_actualInstanceId.getHandle() : (OdUInt64)0)
        << " "
        << (m_actualInstanceId.isValid() ? m_actualInstanceId.getNested()->typeName().c_str() : "") << "</td>";
    }
    else
    {
      m_htmlOutFile << "<tr>";
    }
    if (!ununicAttrCountdown)
    {
      ununicAttrCountdown = m_invalidAttributes.count(it->first);
      m_htmlOutFile << "<td rowspan=" << ununicAttrCountdown << ">" << (it->first?it->first.c_str():"") << "</td>";
    }

    m_htmlOutFile << "<td>" << it->second.first.c_str() << "</td>";
    m_htmlOutFile << "<td>" << result2string(it->second.second).c_str() << "</td></tr>\n";

    --ununicAttrCountdown;
  }
}

void HtmlValidationNotifier::onStartValidation()
{
  m_htmlOutFile.open(m_fileName.c_str());
  if (!m_htmlOutFile.is_open())
    throw("Wrong html file name");

  if (m_htmlOutFile.is_open())
  {
    time_t seconds = time(NULL);

    m_htmlOutFile << "<!DOCTYPE HTML>\n"
      << "<html>\n"
      << "<head>\n"
      << "<title>Validation results</title>\n"
      << "</head>\n"
      << "<body>\n"
      << "<p>Automatically generated validation log file<br>"
      << "This file contains information about failed validation tasks<br>";

    if (m_extraInfo)
      m_htmlOutFile << "File name: " << m_extraInfo->fileName.c_str() << "<br>"
      << "File schema: " << m_extraInfo->schemaName.c_str() << "<br>";

    m_htmlOutFile << "Date: " << std::ctime(&seconds) << "<br><br></p>"
      << "<table border = \"1\" cellpadding=\"5\">\n"
      << "<caption>Validation tasks results</caption>\n"
      << "<tr>\n"
      << "<th>Instance</th>\n"
      << "<th>Attribute</th>\n"
      << "<th>Validation task</th>\n"
      << "<th>Result</th>\n"
      << "</tr>\n";
  }
}

void HtmlValidationNotifier::onEndValidation()
{
  addInstanceToFile();
  m_htmlOutFile << "</table>\n"
    << "</body>\n"
    << "</html>";

  m_htmlOutFile.close();
}

void HtmlValidationNotifier::setFileName(const OdAnsiString& fileName)
{
  m_fileName = fileName;
}
