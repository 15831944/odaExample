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

#ifndef _BFC_LINE_H
#define _BFC_LINE_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfPoint;
  typedef OdSmartPtr<OdBcfPoint> OdBcfPointPtr;

  /** \details
  A class that stores and operates a markup line data within the BCF format.
  */
  class BCF_EXPORT OdBcfLine : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfLine);
    //DOM-IGNORE-END

    /** \details
    Creates a new markup line object.
    \param pStartPoint [in] A pointer to start point of the markup line.
    \param pEndPoint   [in] A pointer to end point of the markup line.
    \returns A smart pointer to the created <link OdBcf::OdBcfLine, OdBcfLine> instance.
    */
    static OdSmartPtr<OdBcfLine> createObject(
      const OdBcfPointPtr &pStartPoint,
      const OdBcfPointPtr &pEndPoint);

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
    Checks whether the line instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the start point of the line.
    \returns A smart pointer to the <link OdBcf::OdBcfPoint, OdBcfPoint> object that represents the start point.
    \remarks 
    The start point object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPointPtr& getStartPoint() const;

    /** \details
    Defines whether the object that represents the line start point is not initialized.
    \returns true if the start point object is not initialized; otherwise, the method returns false.
    */
    bool isStartPointUnset() const;

    /** \details
    Retrieves the endpoint of the line.
    \returns A smart pointer to the <link OdBcf::OdBcfPoint, OdBcfPoint> object that represents the end point.
    \remarks 
    The endpoint object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPointPtr& getEndPoint() const;

    /** \details
    Defines whether the object that represents the line end point is not initialized.
    \returns true if the end point object is not initialized; otherwise, the method returns false.
    */
    bool isEndPointUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfPointPtr m_pStartPoint;
    OdBcfPointPtr m_pEndPoint;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfLine, OdBcfLine> object.
  */
  typedef OdSmartPtr<OdBcfLine> OdBcfLinePtr;

} //namespace OdBcf

#endif // _BFC_LINE_H
