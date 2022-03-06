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

#ifndef _BFC_HEADER_H
#define _BFC_HEADER_H

#include "BcfCommon.h"
#include "OdArray.h" 

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfFile;
  typedef OdSmartPtr<OdBcfFile> OdBcfFilePtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfFile, OdBcfFile> objects.
  */
  typedef OdArray<OdBcfFilePtr> OdBcfFileArray;

  /** \details
  A class that stores and operates header data of a BCF file.
  */
  class BCF_EXPORT OdBcfHeader : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfHeader);
    //DOM-IGNORE-END

    /** \details
    Creates a new header object from specified BCF files.
    \param file [in] An array of smart pointers to BCF files objects.
    \returns A smart pointer to the created <link OdBcf::OdBcfHeader, OdBcfHeader> instance.
    */
    static OdSmartPtr<OdBcfHeader> createObject(const OdBcfFileArray &file);

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
    Checks whether the header instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Sets file associated with the header object.
    \param fileValue [in] An array of smart pointers to <link OdBcf::OdBcfFile, OdBcfFile> objects to be set.
    */
    void setFile(const OdBcfFileArray &fileValue);

    /** \details
    Retrieves files associated with the header object.
    \returns An array of smart pointers to <link OdBcf::OdBcfFile, OdBcfFile> objects.
    \remarks 
    The array returned by the method can be modified in the calling subroutine.
    */
    OdBcfFileArray& getFile();

    /** \details
    Retrieves files associated with the header object.
    \returns An array of smart pointers to <link OdBcf::OdBcfFile, OdBcfFile> objects.
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfFileArray& getFile() const;

    /** \details
    Defines whether the array of file object associated with the header is not initialized.
    \returns true if the file array is not initialized; otherwise, the method returns false.
    */
    bool isFileUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfFileArray m_file;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfHeader, OdBcfHeader> object.
  */
  typedef OdSmartPtr<OdBcfHeader> OdBcfHeaderPtr;

} //namespace OdBcf

#endif // _BFC_HEADER_H
