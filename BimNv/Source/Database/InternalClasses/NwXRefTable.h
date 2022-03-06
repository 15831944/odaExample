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

#ifndef __NWXREFTABLE_INCLUDED_
#define __NWXREFTABLE_INCLUDED_

#include "NwExport.h"
#include "SharedPtr.h"
#include "OdString.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "NwXRefTableElement.h"

class NWDBEXPORT OdNwXRefTable
{
public:
  OdNwXRefTable();
  ~OdNwXRefTable() = default;

public:
  OdString getSavedFilename() const;
  const std::vector<OdNwXRefTableElement>& getXRef() const;
  bool isInTable(const OdString& xRef) const;
  bool getXRefByKey(OdString& xRef) const;

public:
  void setSavedFilename(const OdString& name);
  void addXRef(OdNwXRefTableElement&& xRef);

protected:
  OdString m_SavedFilename;
  std::vector<OdNwXRefTableElement> m_vXRef;
};

typedef OdSharedPtr<OdNwXRefTable> OdNwXRefTablePtr;

#endif //__NWXREFTABLE_INCLUDED_
