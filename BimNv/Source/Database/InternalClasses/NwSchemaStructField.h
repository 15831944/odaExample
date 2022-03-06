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

#ifndef __NWSCHEMASTRUCTFIELD_INCLUDED_
#define __NWSCHEMASTRUCTFIELD_INCLUDED_

//#include "NwExport.h"
#include "NwSchemaField.h"
//#define STL_USING_VECTOR
//#include "OdaSTL.h"
//#include "NwXRefTableElement.h"

class OdNwSchemaStructField : public OdNwSchemaField
{
public:
  OdNwSchemaStructField();
  virtual ~OdNwSchemaStructField() = default;

public:
  //OdString getSavedFilename() const;
  //const std::vector<OdNwSchemaStructFieldElement>& getXRef() const;
  //bool isInTable(const OdString& xRef) const;

public:
  //void setSavedFilename(const OdString& name);
  void addChildSchema(OdNwSchemaFieldPtr&& pSchema);

protected:
  //OdString m_SavedFilename;
  std::vector<OdNwSchemaFieldPtr> m_vChildren;
};

typedef std::shared_ptr<OdNwSchemaStructField> OdNwSchemaStructFieldPtr;

#endif //__NWSCHEMASTRUCTFIELD_INCLUDED_
