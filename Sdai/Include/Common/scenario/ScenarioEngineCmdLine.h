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

#ifndef _SCENARIO_ENGINE_CMD_LINE_H_
#define _SCENARIO_ENGINE_CMD_LINE_H_


#include "SharedPtr.h"
#include "ScenarioEngineDeclarations.h"

namespace ScenarioEngine
{
  class CmdParam
  {
  public:
    CmdParam() {}
    virtual ~CmdParam() {}

    virtual bool parse(test_arg_char* valueToParse) = 0;
    virtual void resetToDefault() = 0;

  private:
    CmdParam(const CmdParam&) {}
    CmdParam& operator=(const CmdParam&) {}

  };

  template<class TType>
  class CmdParamBaseWithDefaultValue
    : public CmdParam
  {// workaround for GCC
  protected:
    static const TType& getDefaultValue()
    {
      // all nullable
      static const TType defaultValue = 0;
      return defaultValue;
    }
  };

  template<>
  class CmdParamBaseWithDefaultValue<OdString>
    : public CmdParam
  {// workaround for GCC
  protected:
    static const OdString& getDefaultValue()
    {
      // all nullable
      static const OdString defaultValue = L"";
      return defaultValue;
    }
  };

  template<>
  class CmdParamBaseWithDefaultValue<OdAnsiString>
    : public CmdParam
  {// workaround for GCC
  protected:
    static const OdAnsiString& getDefaultValue()
    {
      // all nullable
      static const OdAnsiString defaultValue = "";
      return defaultValue;
    }
  };


  template<class TType>
  class CmdParamTyped
    : public CmdParamBaseWithDefaultValue<TType>
  {
  public:
    CmdParamTyped(TType& valueToWrite, const TType& defaultValue = CmdParamBaseWithDefaultValue<TType>::getDefaultValue())
      : m_value(valueToWrite)
      , m_defaultValue(defaultValue)
    {
      resetToDefault();
    }

    virtual bool parse(test_arg_char* valueToParse)
    {
      return tryParse(valueToParse, m_value);
    }

    virtual void resetToDefault()
    {
      m_value = m_defaultValue;
    }

  private:
    TType&  m_value;
    TType   m_defaultValue;
  };


  enum CmdParseRuleMode
  {
    cmdParamStrictCompliance,
    cmdParamPartCompliance,
  };

  class CmdParseRule
  {
  public:
    CmdParseRule(CmdParseRuleMode mode, int mandatoryPartSize = -1)
      : m_mode(mode),
      m_mandatoryPartSize(mandatoryPartSize)
    {
    }

    template<class TType>
    CmdParseRule& operator << (TType& valueToWrite)
    {
      m_paramsCollection.push_back(OdSharedPtr<CmdParam>(new CmdParamTyped<TType>(valueToWrite)));
      return *this;
    }

    void setMandatoryPartSize(int mandatoryPartSize)
    {
      m_mandatoryPartSize = mandatoryPartSize;
    }

    bool parse(int argc, test_arg_char* argv[])
    {
      bool parseOperationResult = true;

      std::vector<OdSharedPtr<CmdParam> >::iterator nextParam = m_paramsCollection.begin();
      for (int argIndex = 0; argIndex < argc; ++argIndex)
      {
        if (nextParam == m_paramsCollection.end())
        {
          parseOperationResult = false;
          break;
        }

        if (!(*nextParam)->parse(argv[argIndex]))
        {
          if (m_mandatoryPartSize >=0 && (*nextParam).get() < (m_paramsCollection.at(m_mandatoryPartSize).get()))
            parseOperationResult = false;
          break;
        }
        ++nextParam;
      }

      

      if (nextParam != m_paramsCollection.end() || !parseOperationResult)
      {
        if (m_mode == cmdParamStrictCompliance)
        {
          nextParam = m_paramsCollection.begin();
          parseOperationResult = false;
        }

        while (nextParam != m_paramsCollection.end())
        {
          (*nextParam)->resetToDefault();
          ++nextParam;
        }
      }

      return parseOperationResult;
    }

  private:
    CmdParseRule(const CmdParseRule&) {}
    CmdParseRule& operator=(const CmdParseRule&) {}

  private:
    std::vector<OdSharedPtr<CmdParam> >   m_paramsCollection;
    CmdParseRuleMode m_mode;
    int m_mandatoryPartSize;
  };
}

#endif
