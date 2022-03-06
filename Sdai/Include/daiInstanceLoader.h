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

#ifndef _DAI_INSTANCE_LOADER_H_
#define _DAI_INSTANCE_LOADER_H_

#include "OdaCommon.h"
#include "daiApplicationInstance.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {
  
  class OdSpfFilerBase;

  /** \details
  The base class for application instances that can be manipulated with the Data Access Interface (DAI).
  */
  class DAI_EXPORT InstanceLoader 
    : public ApplicationInstance
  {
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(InstanceLoader);
    //DOM-IGNORE-END


    /** \details
    Reads values of the instance's explicit attribute fields from a file buffer that is associated with a specified filer object.
    \param rdFiler [in] A raw pointer to the filer object associated with the file buffer to read data from.
    \returns Returns eOk if the attribute fields values are successfully read; otherwise, the method returns an appropriate error.
    \remarks 
    The method's default implementation returns the eNotImplemented value.
    */
    virtual OdResult inFields(OdSpfFilerBase *rdFiler) { return eUnsupportedMethod; };

    /** \details
    Writes values of the instance's explicit attribute fields to a file buffer that is assigned to a specified filer object.
    \param wrFiler [in] A raw pointer to the filer object assigned with the file buffer to write data to.
    \returns Returns eOk if the attribute fields values are successfully written; otherwise, the method returns an appropriate error.
    \remarks 
    The method's default implementation returns the eNotImplemented value.
    */
    virtual OdResult outFields(OdSpfFilerBase *wrFiler) { return eUnsupportedMethod; };

    /** \details
    Retrieves the type of the sdai object.
    \returns Returns a raw pointer to the <link OdDAI::Entity, schema entity definition> of the sdai object.
    */
    Entity* getInstanceType() const override
    {
      return m_entity;
    }


    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param explicitAttrName [in] An ANSI string that contains the attribute name.
    \returns Returns true if the attribute has a value; otherwise, the method returns false (it means that the attribute value is not set).
    */
    bool testAttr(const char* attrName) const override;



//DOM-IGNORE-BEGIN
  private:
    friend class Pager;

  private:
    Entity* m_entity;



    //DOM-IGNORE-END
  };

  using InstanceLoaderPtr = OdSmartPtr<InstanceLoader>;
}

#endif // _DAI_APPLICATION_INSTANCE_H_
