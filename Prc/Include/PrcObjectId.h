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

#ifndef _PRCOBJECTID_
#define _PRCOBJECTID_

#include "DbHandle.h"
#include "SmartPtr.h"
#include "PrcToolkitExportDef.h"
#include "Gi/GiCommonDraw.h"

class OdDbStub;

class OdPrcStub;
class OdPrcBase;
typedef OdSmartPtr<OdPrcBase> OdPrcObjectPtr;

/** \details
Open mode enumerator. Determines the result of opening a PRC object.
*/
enum OpenMode
{
  /** Object is not open.*/
  kNotOpen           = -1,  
  /** Object is open for reading.*/
  kForRead           = 0,   
  /** Object is open for reading and/or writing.*/
  kForWrite          = 1,   
  /** Object is open for notifying.*/
  kForNotify         = 2    
};

/** \details 
<group PRC_Datatypes_Classes> 

Class implements PRC object identifier (ID) functionality.
*/
class PRC_TOOLKIT OdPrcObjectId
{
public:
  
  /** \details
  Creates a PRC object identifier.
  */
  OdPrcObjectId() : m_Id (0) { }
  
  /** \details
  Creates a PRC object identifier based on a specified stub.
  
  \param objectId [in] A raw pointer to the stub object.
  */
  OdPrcObjectId (OdDbStub* objectId) : m_Id (objectId) { }

  //PRC_TOOLKIT static const OdPrcObjectId kNull;

  /** \details
  Returns true if the PRC object identifier is empty (NULL) or false in the other case.
  */
  bool isNull() const     { return m_Id == 0; }

  /** \details
  Sets the PRC object identifier to NULL.
  */
  void setNull()          { m_Id = 0; }

  /** \details
  Returns true if the PRC object identifier is a valid object or false in the other case.
  */
  bool isValid() const;

  /** \details
  Returns true if the PRC object associated with the identifier is erased or false in the other case.
  */
  bool isErased() const;

  /** \details
  Assigns another ID value to the PRC object identifier.
  
  \param elementId [in] A reference to a PRC object identifier to assign.
  */  
  OdPrcObjectId& operator = (const OdPrcObjectId& elementId)     { m_Id = elementId.m_Id; return *this; }

  /** \details
  Assigns the PRC object identifier with a specified stub.
  
  \param objectId [in] A stub to assign with.
  */  
  OdPrcObjectId& operator = (OdDbStub* objectId)               { m_Id = objectId; return *this; }

  /** \details
  Compares the PRC object identifier with another and returns true if the PRC object identifier is equal to another ID or false in the other case.
  
  \param elementId [in] A reference to a PRC object identifier to compare with.
  */    
  bool operator == (const OdPrcObjectId& elementId) const;

  /** \details
  Compares the PRC object identifier with another and returns true if the PRC object identifier is more than another ID or false in the other case.
  
  \param elementId [in] A reference to a PRC object identifier to compare with.
  */    
  bool operator > (const OdPrcObjectId& elementId) const;

  /** \details
  Compares the PRC object identifier with another and returns true if the PRC object identifier is less than another ID or false in the other case.
  
  \param elementId [in] A reference to a PRC object identifier to compare with.
  */    
  bool operator < (const OdPrcObjectId& elementId) const;

  /** \details
  Checks if the PRC object identifier is NULL. Returns true if the identifier is NULL or false in the other case.
  */    
  bool operator !() const { return isNull(); }

  /**\details 
  For PRC SDK internal use only.
  */
  inline operator OdDbStub*() const   { return (OdDbStub*) m_Id; }

  /** \details
  Returns a pointer to the database with which the PRC object identifier is associated.
  Returns NULL if the identifier is not associated with any database.
  */
  OdDbBaseDatabase* database() const;

  /**!DOM \details
  Returns the original database with which the PRC object identifier is associated.
  If the object associated with the identifier has been redirected to
  a host database from an Xref database, the method returns
  a pointer to the Xref database. 
  Otherwise, it returns a pointer to the database with which identifier is associated.
  */
  //OdBmDatabase* originalDatabase () const;

  /**!DOM \details
  If the identifier has been redirected from another database (for an example, Xref), the method 
  returns the actual identifier from the original database.
  */
  //void convertToRedirectedId ();

  /**!DOM \details
  Returns true if an object associated with the identifier has been erased.
  */
  //bool isErased () const;

  /**!DOM \details
  Returns true if an PRC object, associated with the identifier, or any object from its ownership hierarchy, has been erased.
  */
  //bool isEffectivelyErased () const;

  /** \details
  Returns the database handle of the object referenced by the PRC object identifier.
  Returns NULL if no database object is referenced by this PRC object identifier.
    
  \remarks
  If the identifier has been redirected from another database (for example, an Xref), the method 
  returns the handle from the original database.
  */
  const OdDbHandle& getHandle() const;

  /**!DOM \details
  Returns the database handle of the object referenced by the identifier.
  
  \remarks
  Returns NULL if no database object is referenced by the identifier.

  If this identifier has been redirected from another database (for example, an Xref), the method 
  returns the handle from the original database.
  */
  //const OdDbHandle& getNonForwardedHandle () const;

  /**!DOM \details
  Opens the database object associated with the identifier.

  \param pObj [out]  Smart pointer to the object to be opened.
  \param openMode [in]  Mode in which the object must be opened.
  \param openErasedOne [in]  Specifies whether erased objects are also opened (true) or not (false).

  \returns Returns eOk if successful, otherwise returns an Error Code.
  
  \remarks
  openMode must be one of the following:
  <table>
    Identifier    Value     Description
    kNotOpen      -1        Object is open for reading.
    kForRead      0         Object is open for reading.
    kForWrite     1         Object is open for reading and/or writing.
    kForNotify    2         Object is open for notifying.    
  </table>
  */
  //OdResult openObject (
  //  OdBmObjectPtr& pObj,
  //  OdBm::OpenMode openMode = OdBm::kForRead, 
  //  bool openErasedOne = false) const;
  
  /** \details
  Opens the database object associated with the identifier.
  
  \param pObj [out]  Smart pointer that must be used for returning the opened object.
  \param openMode [in]  Mode in which the object must be opened.
  \param openErasedOne [in]  Specifies whether erased objects are also opened (true) or not (false).

  \returns Returns eOk if object was successfully opened, or an appropriate error code in the other case.
  
  \remarks
  openMode must be one of the following:
  <table>
    Identifier    Value     Description
    kNotOpen      -1        Object is open for reading.
    kForRead      0         Object is open for reading.
    kForWrite     1         Object is open for reading and/or writing.
    kForNotify    2         Object is open for notifying.    
  </table>
  */
  OdResult openObject(
    OdPrcObjectPtr& pObj,
    OpenMode openMode = kForRead, 
    bool openErasedOne = false) const;
    
  /** \details
    Opens the database object associated with the identifier.

    \param openMode [in]  Mode in which the object must be opened.
    \param openErasedOne [in]  Specifies whether erased objects are also opened (true) or not (false).

    \returns Returns a smart pointer to the opened object if successful, otherwise returns NULL.
    
    \remarks 
    openMode must be one of the following:
    <table>
      Identifier    Value     Description
      kNotOpen      -1        Object is open for reading.
      kForRead      0         Object is open for reading.
      kForWrite     1         Object is open for reading and/or writing.
      kForNotify    2         Object is open for notifying.    
    </table>    
  */
  OdPrcObjectPtr openObject(
    OpenMode openMode = kForRead, 
    bool openErasedOne = false) const;
    
  /** \details
  Safely opens the database object associated with the identifier.

  \param openMode [in]  Mode in which the object must be opened.
  \param openErasedOne [in]  Specifies whether erased objects are also opened (true) or not (false).

  \returns Returns a smart pointer to the opened object if successful or throws an exception in other case.
  
  \remarks
  openMode must be one of the following:
  <table>
    Identifier    Value     Description
    kNotOpen      -1        Object is open for reading.
    kForRead      0         Object is open for reading.
    kForWrite     1         Object is open for reading and/or writing.
    kForNotify    2         Object is open for notifying.    
  </table>    

  Can throw one of the following exceptions:
  <table>
  Exception           Cause
  eNullObjectId       The identifier is null.
  ePermanentlyErased  Object was not opened (in case when openErasedOne is true)
  eWasErased          Not was not opened (in case when openErasedOne is false)
  </table>
  */
  OdPrcObjectPtr safeOpenObject(OpenMode openMode = kForRead, 
                              bool openErasedOne = false) const;

protected:
  friend class OdPrcStub;
  OdDbStub* m_Id;
};

typedef OdArray<OdPrcObjectId> OdPrcObjectIdArray;

#endif // _PRCOBJECTID_

