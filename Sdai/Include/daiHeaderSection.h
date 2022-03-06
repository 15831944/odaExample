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

#ifndef _DAI_HEADER_SECTION_H_
#define _DAI_HEADER_SECTION_H_

#define STL_USING_MAP
#include "OdaSTL.h"

#include "RxObject.h"
#include "daiHeader/daiHeaderEntityTypes.h"
#include "daiBuildOptions.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class OdHeaderSection;
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::OdHeaderSection, OdHeaderSection> object.
  */
  typedef OdSmartPtr<OdHeaderSection> OdHeaderSectionPtr;

  class OdSpfFilerBase;
  typedef OdSmartPtr<OdSpfFilerBase> OdSpfFilerBasePtr;

  class ApplicationInstance;
  typedef OdSmartPtr<ApplicationInstance> ApplicationInstancePtr;

  /** \details
  A class that represents a header section of a STEP Physical File.
  */
  class DAI_EXPORT OdHeaderSection : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdHeaderSection);
    //DOM-IGNORE-END

    /** \details
    Appends a new header section entity into the header section.
    \param headerEntityType [in] A <link OdDAI::HeaderEntityType, type> of appending header entity.
    \param pEntity          [in] A smart pointer to an entity instance where the new header section should be appended.
    */
    void appendEntity(OdHeaderEntityType headerEntityType, ApplicationInstancePtr pEntity);

    /** \details
    Retrieves an entity instance of a specified type from the header section.
    \param headerEntityType [in] A <link OdDAI::HeaderEntityType, type> of header entity to retrieve.
    \returns Returns a smart pointer to the entity instance of the specified type.
    */
    ApplicationInstancePtr getEntityByType(OdHeaderEntityType headerEntityType);

    /** \details
    Initializes the header section entity based on data loaded from a file using a specified filer object.
    \param rdFiler [in] A smart pointer to the reading filer object.
    */
    virtual OdResult initialize(OdSpfFilerBasePtr& rdFiler);

    /** \details
    Initializes the empty header section object with three mandatory empty entities.
    */
    virtual void initialize();

    /** \details
    Writes entities of the header section entity into a file using a specified filer object.
    \param wrFiler [in] A smart pointer to a writing filer object.
    */
    virtual void out(OdSpfFilerBasePtr& wrFiler);

//DOM-IGNORE-BEGIN
  private:
    std::map<OdHeaderEntityType, ApplicationInstancePtr>  m_entities;
//DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::OdHeaderSection, OdHeaderSection> object.
  */
  typedef OdSmartPtr<OdHeaderSection> OdHeaderSectionPtr;

  void daiHeaderRxClassesInit();
  void daiHeaderRxClassesUninit();

} //namespace OdDAI

#endif // _DAI_HEADER_SECTION_H_
