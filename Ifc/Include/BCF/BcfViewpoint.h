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

#ifndef _BFC_VIEWPOINT_H
#define _BFC_VIEWPOINT_H

#include "BcfCommon.h"
#include "OdGUID.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfSession;

  /** \details
  A class that stores viewpoint metadata within the BCF format.
  */
  class OdBcfViewPointData
  {
  protected:
    /** \details 
    A string that contains the information about the viewpoint.
    */
    OdString m_viewpoint;
    
    /** \details 
    A string that contains the viewpoint snapshot.
    */
    OdString m_snapshot;
    
    /** \details 
    A 32-bit signed integer value that contains the viewpoint index.
    */
    OdInt32  m_index;
    
    /** \details 
    A global unique identifier of the viewpoint.
    */
    OdGUID   m_guid;

    friend OdBcfSession;
  };

  /** \details
  A class that stores and operates a viewpoint data.
  */
  class BCF_EXPORT OdBcfViewPoint : public OdBcfElement, protected OdBcfViewPointData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfViewPoint);
    //DOM-IGNORE-END

    /** \details
    Creates a new viewpoint object with default parameters.
    */
    OdBcfViewPoint();

    /** \details
    Reads XML data into ODA data structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inFields(TiXmlElement *pParent) ODRX_OVERRIDE;

    /** \details
    Writes data into XML structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully written; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outFields(TiXmlElement *pParent) const ODRX_OVERRIDE;

    /** \details
    Checks whether the viewpoint instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the viewpoint of the viewport.
    \returns A string that contains information about the viewpoint.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getViewpoint() const;

    /** \details
    Defines whether the information about the viewpoint is not initialized.
    \returns true if the string with the information about the viewpoint is not initialized; otherwise, the method returns false.
    */
    bool isViewpointUnset() const;

    /** \details
    Retrieves the value of the Snapshot property of the viewport object.
    \returns A string that contains the Snapshot property value.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getSnapshot() const;

    /** \details
    Defines whether the value of the Snapshot property of the viewport object is not initialized.
    \returns true if the Snapshot property value is not initialized; otherwise, the method returns false.
    */
    bool isSnapshotUnset() const;

    /** \details
    Retrieves the viewport index.
    \returns A 32-bit integer value that contains the index value.
    \remarks 
    The index value returned by the method can't be modified in the calling subroutine.
    */
    const OdInt32& getIndex() const;

    /** \details
    Defines whether the index of the viewport object is not initialized.
    \returns true if the index value is not initialized; otherwise, the method returns false.
    */
    bool isIndexUnset() const;

    /** \details
    Retrieves the viewport's global unique identifier (GUID).
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the viewport GUID.
    \remarks 
    The GUID returned by the method can't be modified in the calling subroutine.
    */
    const OdGUID& getGuid() const;

    /** \details
    Defines whether the global unique identifier (GUID) of the viewport object is not initialized.
    \returns true if the GUID is not initialized; otherwise, the method returns false.
    */
    bool isGuidUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfViewPoint& operator = (const OdBcfViewPointData &val);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfViewPoint, OdBcfViewPoint> object.
  */
  typedef OdSmartPtr<OdBcfViewPoint> OdBcfViewPointPtr;

} //namespace OdBcf

#endif // _BFC_VIEWPOINT_H
