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

#ifndef _BFC_FILE_H
#define _BFC_FILE_H

#include "BcfCommon.h"

#include "BcfElement.h"
#include "BcfFileAttributesGroup.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfTimeStamp;
  typedef OdSmartPtr<OdBcfTimeStamp> OdBcfTimeStampPtr;

  /** \details
  A class that stores metadata about a BCF file.
  */
  class OdBcfFileData
  {
  public:
    /** \details
    A file full name.
    */
    OdString                 m_filename;
    
    /** \details 
    A file reference.
    */
    OdString                 m_reference;
    
    /** \details 
    A <link OdBcf::OdBcfFileAttributesGroup, file attributes>.
    */
    OdBcfFileAttributesGroup m_fileAttributes;
    
    /** \details 
    A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> instance that contains the file creation timestamp.
    */
    OdBcfTimeStampPtr        m_pDate;
  };

  class OdBcfSession;

  /** \details
  A class that stores and operates data about a BCF file.
  */
  class BCF_EXPORT OdBcfFile : public OdBcfElement, protected OdBcfFileData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfFile);
    //DOM-IGNORE-END

    /** \details
    Creates a new file object with default parameters.
    */
    OdBcfFile();

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
    Checks whether the file instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Sets a new name of the related BIM file.
    \param filenameValue [in] A string that contains the new full name of an IFC file.
    \remarks 
    The related BIM file can have different extensions: IFC, IfcZip, IfcXML, hdf5 and other supported file types.
    */
    void setFilename(const OdString &filenameValue);

    /** \details
    Retrieves the related BIM file name.
    \returns A string that contains the full name of the file.
    \remarks 
    The related BIM file can have different extensions: IFC, IfcZip, IfcXML, hdf5 and other supported file types.
    The filename returned by the method can be modified in the calling subroutine.
    */
    OdString& getFilename();

    /** \details
    Retrieves the related BIM file name.
    \returns A string that contains the full name of the file.
    \remarks 
    The related BIM file can have different extensions: IFC, IfcZip, IfcXML, hdf5 and other supported file types.
    The filename returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getFilename() const;

    /** \details
    Defines whether the name of the related BIM file is not initialized.
    \returns true if the filename is not initialized; otherwise, the method returns false.
    */
    bool isFilenameUnset() const;

    /** \details
    Sets a new reference value for the file object.
    \param referenceValue [in] A string that contains the new reference value.
    */
    void setReference(const OdString &referenceValue);

    /** \details
    Retrieves the reference for the file object.
    \returns A string that contains the reference value.
    \remarks 
    The reference value returned by the method can be modified in the calling subroutine.
    */
    OdString& getReference();

    /** \details
    Retrieves the reference for the file object.
    \returns A string that contains the reference value.
    \remarks 
    The reference value returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getReference() const;

    /** \details
    Defines whether the reference value is not initialized.
    \returns true if the reference value is not initialized; otherwise, the method returns false.
    */
    bool isReferenceUnset() const;

    /** \details
    Sets file attributes.
    \param fileAttributesValue [in] An <link OdBcf::OdBcfFileAttributesGroup, OdBcfFileAttributesGroup> object that contains the file attributes.
    */
    void setFileAttributes(const OdBcfFileAttributesGroup &fileAttributesValue);

    /** \details
    Retrieves the file attributes.
    \returns An <link OdBcf::OdBcfFileAttributesGroup, OdBcfFileAttributesGroup> object that contains the file attributes.
    \remarks 
    The file attribute object returned by the method can be modified in the calling subroutine.
    */
    OdBcfFileAttributesGroup& getFileAttributes();

    /** \details
    Retrieves the file attributes.
    \returns An <link OdBcf::OdBcfFileAttributesGroup, OdBcfFileAttributesGroup> object that contains the file attributes.
    \remarks 
    The file attribute object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfFileAttributesGroup& getFileAttributes() const;

    /** \details
    Defines whether the file attributes are not initialized.
    \returns true if the file attributes are not initialized; otherwise, the method returns false.
    */
    bool isFileAttributesUnset() const;

    /** \details
    Sets a new date of creation for the file object.
    \param dateValue [in] An <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the new date value to be set.
    */
    void setDate(const OdBcfTimeStampPtr &dateValue);

    /** \details
    Retrieves the date of creation of the file object.
    \returns An <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the creation date.
    \remarks 
    The timestamp object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTimeStampPtr& getDate();

    /** \details
    Retrieves the date of creation of the file object.
    \returns An <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the creation date.
    \remarks 
    The timestamp object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTimeStampPtr& getDate() const;

    /** \details
    Defines whether the file creation date is not initialized.
    \returns true if the file creation date is not initialized; otherwise, the method returns false.
    */
    bool isDateUnset() const;


    /** \details 
    An assignment operator for BCF file objects.
    It assigns the \specified content represented with an <link OdBcf::OdBcfFileData, OdBcfFileData> class instance to the file object.
    \param val [in] An <link OdBcf::OdBcfFileData, OdBcfFileData> object that contains data to be assigned with the file object.
    \returns The reference to the file object after the assignment operation ends.
    */
    OdBcfFile& operator = (const OdBcfFileData& val);

    //DOM-IGNORE-BEGIN
  protected:

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfFile, OdBcfFile> object.
  */
  typedef OdSmartPtr<OdBcfFile> OdBcfFilePtr;

} //namespace OdBcf

#endif // _BFC_FILE_H
