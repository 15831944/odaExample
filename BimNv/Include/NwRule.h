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

#ifndef _NW_RULE_H_
#define _NW_RULE_H_
#include "NwProperty.h"


/** \details
  This class represents custom rules.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwRule : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwRule);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwRule object.
  */
  OdNwRule();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwRule();

  /** \details
    Returns the array of rule's parameters.

    \returns OdArray of OdNwObjectId objects.
  */
  OdNwObjectIdArray getParameters() const;

  /** \details
    Returns the name of the rule.

    \returns OdString object with the name of the rule.
  */
  OdString getName() const;

  /** \details
    Returns the description of the rule.

    \returns OdString object with the description of the rule.
  */
  OdString getDescription() const;

  /** \details
    Returns the enabling flag for the rule.

    \returns True if the rule is enabled.
  */
  bool isEnabled() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwRule
  object pointers.
*/
typedef OdSmartPtr<OdNwRule> OdNwRulePtr;

#endif // _NW_RULE_H_
