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

#if !defined(ODA_ODMVDXMLCOMMON_H_INCLUDED_)
#define ODA_ODMVDXMLCOMMON_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OdaCommon.h"
#include "IfcCommon.h"
#include "RxObject.h"
#include "RxObjectImpl.h"
#include "OdArray.h"
#include "OdAnsiString.h"

// Generate error if item more than one.
// #define MORE_THAN_ONE_ERROR

#ifdef MVDXM_MORE_THAN_ONE_ERROR
#define MVDXM_MORE_THAN_ONE(parent, text, caption) appendXmlErrorMessage(parent, text, caption); return eSyntaxError;
#else
#define MVDXM_MORE_THAN_ONE(parent, text, caption) appendXmlWarningMessage(parent, text, caption)
#endif

#define RETURNNOTOK(expr) {OdResult odResult;if (odResult=expr) return odResult;};
#define RETURNNOTCHECK(expr) {OdResult odResult;if (odResult=expr) return odResult;};

namespace OdMvdXml
{
  enum OdMvdStatus
  {
    OdMvdStatusUnset = -1,
    OdMvdSample = 0,
    OdMvdProposal,
    OdMvdDraft,
    OdMvdCandidate,
    OdMvdFinal,
    OdMvdDeprecated
  };

  class OdMvdOperator
  {
  public:
    enum Operator
    {
      kUnset = -1,
      kAND = 0,
      kOR,
      kNOT,
      kNAND,
      kNOR,
      kXOR,
      kNXOR
    };
    OdMvdOperator()
      :m_operator(kUnset)
    {
    }
    const Operator get() const
    {
      return m_operator;
    }
    const bool IsUnset() const
    {
      return (m_operator == kUnset);
    }
    const bool performBoolean(const bool first, const bool second) const
    {
      switch (m_operator) {
      case kAND:  return first && second;
      case kOR:   return first || second;
      case kNOT:  return !first;
      case kNAND: return !(first && second);
      case kNOR:  return !(first || second);
      case kXOR:  return first != second;
      case kNXOR: return first == second;
      default: return false;
      }
    }
    OdAnsiString toString()
    {
      switch (m_operator) {
      case kAND:  return "AND";
      case kOR:   return "OR";
      case kNOT:  return "NOT";
      case kNAND: return "NAND";
      case kNOR:  return "NOR";
      case kXOR:  return "XOR";
      case kNXOR: return "NXOR";
      default: return "";
      }
    }
    bool operator==(const OdMvdOperator& other) const
    {
      return (*this).m_operator == other.m_operator;
    }
    bool operator==(const Operator other) const
    {
      return (*this).m_operator == other;
    }
    OdMvdOperator& operator=(const OdMvdOperator& other)
    {
      m_operator = other.m_operator;
      return (*this);
    }
    OdMvdOperator& operator=(const OdAnsiString& other)
    {
      return (*this) = other.c_str();
    }
    OdMvdOperator& operator=(const char* other)
    {
      m_operator = kUnset;
      if (other)
      {
        OdAnsiString str(other);
        str.makeUpper();
        if (str.iCompare("AND") == 0)
          m_operator = kAND;
        else if (str.iCompare("OR") == 0)
          m_operator = kOR;
        else if (str.iCompare("NOT") == 0)
          m_operator = kNOT;
        else if (str.iCompare("NAND") == 0)
          m_operator = kNAND;
        else if (str.iCompare("NOR") == 0)
          m_operator = kNOR;
        else if (str.iCompare("XOR") == 0)
          m_operator = kXOR;
        else if (str.iCompare("NXOR") == 0)
          m_operator = kNXOR;
      }
      return (*this);
    }

  private:
    Operator m_operator;
  };

  class OdMvdApplicability
  {
  public:
    enum Applicability
    {
      kUnset = -1,
      kImport = 0,
      kExport,
      kBoth
    };

    OdMvdApplicability()
      : m_applicability(kUnset)
    {}
    const Applicability get() const
    {
      return m_applicability;
    }
    const bool IsUnset() const
    {
      return (m_applicability == kUnset);
    }
    OdAnsiString toString()
    {
      switch (m_applicability) {
      case kImport: return "import";
      case kExport: return "export";
      case kBoth:   return "both";
      default: return "";
      }
    }
    bool operator==(const OdMvdApplicability& other) const
    {
      return (*this).m_applicability == other.m_applicability;
    }
    bool operator==(const Applicability other) const
    {
      return (*this).m_applicability == other;
    }
    OdMvdApplicability& operator=(const OdMvdApplicability& other)
    {
      m_applicability = other.m_applicability;
      return (*this);
    }
    OdMvdApplicability& operator=(const OdAnsiString& other)
    {
      return (*this) = other.c_str();
    }
    OdMvdApplicability& operator=(const char* other)
    {
      m_applicability = kUnset;
      if (other)
      {
        OdAnsiString str(other);
        str.makeLower();
        if (str.iCompare("import") == 0)
          m_applicability = kImport;
        else if (str.iCompare("export") == 0)
          m_applicability = kExport;
        else if (str.iCompare("both") == 0)
          m_applicability = kBoth;
      }
      return (*this);
    }

  private:
    Applicability m_applicability;
  };

  class OdMvdRequirement
  {
  public:
    enum Requirement
    {
      kUnset = -1,
      kMandatory = 0,
      kRecommended,
      kNotRelevant,
      kNotRecommended,
      kExcluded
    };
    OdMvdRequirement()
      : m_requirement(kUnset)
    {}
    const Requirement get() const
    {
      return m_requirement;
    }
    const bool IsUnset() const
    {
      return (m_requirement == kUnset);
    }
    OdAnsiString toString()
    {
      switch (m_requirement) {
      case kMandatory:      return "mandatory";
      case kRecommended:    return "recommended";
      case kNotRelevant:    return "not-relevant";
      case kNotRecommended: return "not-recommended";
      case kExcluded:       return "excluded";
      default: return "";
      }
    }
    bool operator==(const OdMvdRequirement& other) const
    {
      return (*this).m_requirement == other.m_requirement;
    }
    bool operator==(const Requirement other) const
    {
      return (*this).m_requirement == other;
    }
    OdMvdRequirement& operator=(const OdMvdRequirement& other)
    {
      m_requirement = other.m_requirement;
      return (*this);
    }
    OdMvdRequirement& operator=(const OdAnsiString& other)
    {
      return (*this) = other.c_str();
    }
    OdMvdRequirement& operator=(const char* other)
    {
      m_requirement = kUnset;
      if (other)
      {
        OdAnsiString str(other);
        str.makeLower();
        if (str.iCompare("mandatory") == 0)
          m_requirement = kMandatory;
        else if (str.iCompare("recommended") == 0)
          m_requirement = kRecommended;
        else if ((str.iCompare("not-relevant") == 0) || (str.iCompare("not relevant") == 0))
          m_requirement = kNotRelevant;
        else if ((str.iCompare("not-recommended") == 0) || (str.iCompare("not recommended") == 0))
          m_requirement = kNotRecommended;
        else if (str.iCompare("excluded") == 0)
          m_requirement = kExcluded;
      }
      return (*this);
    }
  private:
    Requirement m_requirement;
  };
} // namespace OdMvdXml

#endif // !defined(ODA_ODMVDXMLCOMMON_H_INCLUDED_)

