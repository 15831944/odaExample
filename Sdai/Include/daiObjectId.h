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

#ifndef _DAI_OBJECT_ID_H_
#define _DAI_OBJECT_ID_H_

#include "DbHandle.h"
#include "RxObject.h"

#include "daiBuildOptions.h"

template <class T> class OdSmartPtr;

class OdDbStub;

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  Object open modes.
  */
  enum OpenMode {
    //kForInitializing = -2,
    kNotOpen = -1, // Object is not open.
    kForRead = 0//,  // Object is open for reading.
    //kForWrite = 1, // Object is open for reading and/or writing.
    //kForNotify = 2 // Object is open for notifying.
  };

  class ModelContents;

  class ApplicationInstance;
  typedef OdSmartPtr<ApplicationInstance> ApplicationInstancePtr;
}

/** \details 
A data type represents an instance of the base database class.
*/
typedef OdRxObject OdDbBaseDatabase;

  /** \details
  A class that implements an identifier of the Data Access Interface (DAI) object functionality.
  */
  class DAI_EXPORT OdDAIObjectId {
  public:

    /** \details 
    A data type represents a database handle to the same object that is referred to by the identifier.
    */
    typedef OdDbHandle handle_type;

    /** \details 
    A NULL object identifier.
    */
    DAI_EXPORT_STATIC static const OdDAIObjectId kNull;
    
    /** \details 
    A NULL object database handle.
    */
    DAI_EXPORT_STATIC static const handle_type kNullHandle;

    /** \details 
    Creates a new empty object identifier.
    */
    OdDAIObjectId();
    
    /** \details 
    Creates a new object identifier based on a specified value.
    \param objectId [in] A pointer to an OdDbStub object that stores data for the newly created identifier.
    */
    OdDAIObjectId(OdDbStub* objectId);
    
    /** \details 
    Returns whether the identifier is NULL.
    \returns Returns true if the identifier is NULL; otherwise, the method returns false.
    */
    bool isNull() const;

    /** \details 
    Sets the identifier to the NULL state.
    */
    void setNull();
    
    /** \details 
    Retrieves whether the identifier is valid.
    \returns Returns true if the identifier is valid; otherwise, the method returns false.
    */
    bool isValid() const;

    /** \details
    Retrieves whether the identifier's instance is non-persistent.
    \returns Returns true if and only if non-null identifier doesn't belong to any owning model and has a link
    to owner's identifier.
    \remarks 
    Object identifiers for non-persistent instances are created during owning instance's derived
    attributes evaluation only. Such identifiers have handle which isn't equal to zero, don't have owning model
    and have link to owning instance's object identifier simultaneously.
    */
    bool isNonPersistent() const;

    /** \details
    Checks whether the object was unloaded from memory and left on disk.
    \returns true if the object was unloaded from memory and left on the disk; otherwise, the method returns false. 
    */
    bool objectLeftOnDisk() const;

    /** \details 
    The assignment operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the assignment operation).
    \returns Returns the reference to the object identifier after the assignment operation is finished.
    */
    OdDAIObjectId& operator=(const OdDAIObjectId& objectId);
    
    /** \details 
    The assignment operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the assignment operation) represented with a raw pointer to an OdDbStub object.
    \returns Returns the reference to the object identifier after the assignment operation is finished.
    */
    OdDAIObjectId& operator=(OdDbStub* objectId);

    /** \details 
    The &quot;less than&quot; operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the operation) to be compared with.
    \returns Returns true if the object identifier is less than another one; otherwise, the method returns false.
    */
    bool operator<(const OdDAIObjectId& objectId) const;
    
    /** \details 
    The &quot;more than&quot; operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the operation) to be compared with.
    \returns Returns true if the object identifier is more than another one; otherwise, the method returns false.
    */
    bool operator>(const OdDAIObjectId& objectId) const;
    
    /** \details 
    The &quot;more or equal than&quot; operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the operation) to be compared with.
    \returns Returns true if the object identifier is more or equal than another one; otherwise, the method returns false.
    */
    bool operator>=(const OdDAIObjectId& objectId) const;
    
    /** \details 
    The &quot;less or equal than&quot; operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the operation) to be compared with.
    \returns Returns true if the object identifier is less or equal than another one; otherwise, the method returns false.
    */
    bool operator<=(const OdDAIObjectId& objectId) const;
    
    /** \details 
    The equality operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the operation) to be compared with.
    \returns Returns true if the object identifier is equal to another one; otherwise, the method returns false.
    */
    bool operator==(const OdDAIObjectId& objectId) const;
    
    /** \details 
    The non-equality operator for the object identifier.
    \param objectId [in] Another identifier (right-hand operand of the operation) to be compared with.
    \returns Returns true if the object identifier is not equal to another one; otherwise, the method returns false.
    */
    bool operator!=(const OdDAIObjectId& objectId) const;
    
    
    /** \details 
    The negation operator for the object identifier.
    \returns Returns true if the object identifier is NULL; otherwise, the method returns false.
    */
    bool operator!() const { return isNull(); }

    /** \details 
    The operator for convertion to a raw pointer to the OdDbStub object.
    \remarks 
    This method is for internal use.
    */
    inline operator OdDbStub*() const { return m_Id; }

    /** \details 
    The operator for the access through a pointer to an identifier.
    \returns A raw pointer to an OdDbStub object that represents the identifier.
    \remarks 
    This operator is for internal use only; do NOT use it in your ODA-based applications.
    */
    inline OdDbStub* operator->() const {
      return reinterpret_cast<OdDbStub*>(m_Id);
    }

    /**
    \details 
    Retrieves the model identifier object is associated with.
    \returns Returns a raw pointer to the database object.
    \remarks 
    Returns a NULL pointer if the identifier object is not associated with any database.
    */
    OdDbBaseDatabase* model() const;

    /** \details 
    Determines whether the object associated with the identifier was erased.
    \returns Returns true if the object associated with the identifier was erased; otherwise, the method returns false.
    */
    bool isErased() const;

    /** \details
    Retrieves the database handle of the object referenced by the identifier.
    \returns Returns the object's database handle.
    \remarks 
    Returns a NULL handle if no database object is referenced by the identifier. The handle equals the file's step-id if
    the owning model of the entity was loaded from a file.*/
    const OdDbHandle& getHandle() const;

    /** \details 
    Opens the database object referenced by the identifier in a specified mode.
    \param openMode [in] An <link OdDAI::OpenMode, open mode>.
    \param openErasedOne [in] A flag that determines whether erased objects are open (equal to true) or not (equal to false).
    \returns Returns a smart pointer to the <link OdDAI::ApplicationInstance, entity instance> if the object was successfull opened; otherwise, the method returns a NULL smart pionter.
    \remarks 
    The open mode parameter must have one of the following values:
    <table>
    Name                Value     Description
    OdDb::kForRead      0         Object is open for reading.
    OdDb::kForWrite     1         Object is open for reading and/or writing.
    OdDb::kForNotify    2         Object is open for notifying.
    </table>
    */
    OdDAI::ApplicationInstancePtr openObject(OdDAI::OpenMode openMode = OdDAI::kForRead,
      bool openErasedOne = false) const;
    
    /** \details 
    Retrieves the object that is referenced by the identifier (without open of unloaded entity instance).
    \returns Returns a smart pointer to the <link OdDAI::ApplicationInstance, entity instance>.
    */
    OdDAI::ApplicationInstancePtr getNested() const;

  private:

    /** \details
    Erases the object associated with the identifier.
    \remarks Objects can be erased by calling Model::deleteInstance() method only.
    */
    void erase() const;

//DOM-IGNORE-BEGIN
  protected:

    OdDbStub* id() const;
    friend class OdDbStub;
    OdDbStub* m_Id;

    friend class OdDAI::ModelContents;
//DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents an array of Data Access Interface (DAI) object <link OdDAIObjectId, identifiers>.
  */
  typedef OdArray<OdDAIObjectId> OdDAIObjectIds;

#endif // _DAI_OBJECT_ID_H_
