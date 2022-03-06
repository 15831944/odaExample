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


#ifndef _NWOBJECT_H_
#define _NWOBJECT_H_
#include "DbHandle.h"
#include "Gi/GiDrawable.h"
#include "NwExport.h"

class OdNwObject;
class OdNwDatabase;
class OdNwObjectReactor;
class OdNwObjectImpl;

/** \details
  Open mode used for openning objects from OdNwObjectId.

  <group TNW_Namespaces>
*/
namespace NwOpenMode
{
  /** \details
    This enumeration defines open modes. Open modes are used for openning
    objects from OdNwObjectId.
  */
  enum Enum
  {
    /** Object is not opened. */
    kNotOpen           = -1,
    /** Object is opened for reading. */
    kForRead           = 0,
    /** Object is opened for reading and/or writing. */
    kForWrite          = 1,
  };
}

/** \details
  This class represents a wrapper for an OdDbStub-type database ID of an object.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwObjectId
{
public: 
  /** \details
    Defines new operators for the class and deletes operators derived from the
    OdRxObject class.
  */
  ODRX_HEAP_OPERATORS();

  /** \details
    Default constructor. Creates a new object of the OdNwObjectId class with the
    ID set to NULL.
  */
  OdNwObjectId() : m_Id(NULL) {}

  /** \details
    Creates a new OdNwObjectId object with the specified OdDbStub object.

    \param id [in]  Pointer to the OdDbStub object to create a new OdNwObjectId object.
  */
  OdNwObjectId(OdDbStub* id) : m_Id(id) {}

  /** \details
    Default destructor.
  */
  ~OdNwObjectId();

  /** \details
    Defines the kNull object ID.
  */
  NWDBEXPORT_STATIC static const OdNwObjectId kNull;

  /** \details
    Copy operator.

    \param id [in]  Pointer to an OdDbStub object to copy.
  */
  OdNwObjectId& operator=(OdDbStub* id) { m_Id = id; return *this; }

  /** \details
    Performs the ! operator.

    \returns True if ID is NULL.
  */
  bool operator!() const { return isNull(); }

  /** \details
    Performs the OdDbStub* operator.

    \returns Object ID.
  */
  operator OdDbStub*() const { return m_Id; }

  /** \details
    Performs the -> operator.

    \return Object ID.
  */
  OdDbStub* operator->() const { return reinterpret_cast<OdDbStub*>(m_Id); }

  /** \details
    Checks whether the ID is empty.

    \returns True if the ID is empty, or false otherwise.
  */
  bool isNull() const { return m_Id == NULL; }

  /** \details
    Resets the ID value.
  */
  void setNull() { m_Id = 0; }

  /** \details
    Checks whether the ID is not empty.

    \returns True if the ID is not empty, or false otherwise.
  */
  bool isValid() const { return m_Id != NULL; }

  /** \details
    Returns the database with which this NwObjectId object is associated.

    \returns Pointer to the OdNwDatabase object.
  */
  OdNwDatabase* database() const;

  /** \details
    Returns the database handle of the object referenced by this ObjectId
    object.

    \returns OdDbHandle object with the handle of the database ID.
  */
  OdDbHandle getHandle() const;

  /** \details
    Sets the object of a database's ID.

    \param pObj [in]  Pointer to the object.
  */
  void setObject(OdRxObject* pObj);

  /** \details
    Returns a pointer to the database ID of the object's owner.

    \returns Pointer to the OdDbStub object.
  */
  OdDbStub* owner();

  /** \details
    Returns a pointer to the database ID of the object's owner.

    \returns Constant pointer to the OdDbStub object.
  */
  const OdDbStub* owner() const;

  /** \details
    Sets the object's owner to the database ID.

    \param pOwner [in]  Pointer to the object's owner.
  */
  void setOwner(OdDbStub* pOwner);

  /** \details
    Opens the database object associated with this NwObjectId object.

    \param mode [in]  Object opening mode.

    \returns Smart pointer to the opened object if successful, or a NULL smart
    pointer otherwise.

    \remarks
    The mode must be one of the following:

    <table>
    Name                    Value   Description
    NwOpenMode::kNotOpen    -1      Object is not opened.
    NwOpenMode::kForRead    0       Object is opened for reading.
    NwOpenMode::kForWrite   1       Object is opened for reading and/or writing.
    </table>
  */
  OdSmartPtr<OdNwObject> openObject(NwOpenMode::Enum mode = NwOpenMode::kForRead) const;

  /** \details
    Opens the database object associated with this NwObjectId object, or throws
    an exception if the operation is unsuccessful.

    \param mode [in]  Object opening mode.

    \returns Smart pointer to the opened object.

    \remarks
    Throws:

    <table>
    Exception           Cause
    eInvalidOpenState   Invalid open state.
    </table>

    The mode must be one of the following:

    <table>
    Name                    Value   Description
    NwOpenMode::kNotOpen    -1      Object is not opened.
    NwOpenMode::kForRead    0       Object is opened for reading.
    NwOpenMode::kForWrite   1       Object is opened for reading and/or writing.
    </table>
  */
  OdSmartPtr<OdNwObject> safeOpenObject(NwOpenMode::Enum mode = NwOpenMode::kForRead) const;

  /** \details
    Returns true if and only if the object associated with this NwObjectId
    object is erased.

    \returns True if the object associated with this NwObjectId object is
    erased; false otherwise.
  */
  bool isErased() const;

protected:
  //DOM-IGNORE-BEGIN
  OdDbStub* id() const { return m_Id; }
  class OdDbStub* m_Id;
  //DOM-IGNORE-END
};

/** \details
  This template class is a specialization of the OdArray class for an
  OdNwObjectId collection.
*/
typedef OdArray<OdNwObjectId, OdMemoryAllocator<OdNwObjectId> > OdNwObjectIdArray;

/** \details
  This class represents the GI interface for a database's object.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwObject : public OdGiDrawable
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwObject);
  //DOM-IGNORE-END

protected:
  /** \details
    Default constructor. Creates a new OdNwObject instance.
  */
  OdNwObject();

  /** \details
    Constructor. Creates a new OdNwObject instance.

    \param pImpl [in] Implementation object for this object.
  */
  explicit OdNwObject(OdNwObjectImpl* pImpl);
public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwObject();
  
  /** \details
    Declares the method incrementing the reference counter in objects derived from this class.
  */
  void addRef() override;

  /** \details
    Declares the method decrementing the reference counter in objects derived from this class.
  */
  void release() override;

  /** \details
    Returns the value of the reference counter, that is, the number of references to an instance of this class.
  */
  long numRefs() const override;

  /** \details
    Returns the object's ID from the database.

    \returns OdNwObjectId object with the object's ID.
  */
  virtual OdNwObjectId objectId() const;

  /** \details
    Returns a pointer to the database ID of the object's owner.

    \returns Pointer to the OdDbStub object.
  */
  virtual OdDbStub* ownerId() const;

  /** \details
    Adds the specified reactor to this object's reactor list.

    \param pReactor [in]  Pointer to the reactor object.
  */
  virtual void addReactor(OdNwObjectReactor* pReactor);

  /** \details
    Removes the specified reactor from this object's reactor list.

    \param pReactor [in]  Pointer to the reactor object.
  */
  virtual void removeReactor(OdNwObjectReactor* pReactor);

  /** \details
    Sets the vectorization attributes of the object, and returns its attribute
    flags.

    \param pTraits [in]  Pointer to an OdGiDrawableTraits object from which and to which the attributes are to be set.
    \returns Attribute flags value.
    \remarks
    This is the overridden method from the OdGiDrawable class.
    \sa
    SetAttributesFlags.
  */
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  /** \details
    Creates a viewport-independent geometric representation of this object.

    \param pWd [in]  Pointer to the OdGiWorldDraw interface.
    \returns True if the operation is successful; false otherwise.
    \remarks
    This is the overridden method from the OdGiDrawable class.
  */
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

  /** \details
    Creates a viewport-dependent geometric representation of the object.

    \param pVd [in]  Pointer to the OdGiViewportDraw interface.
    \remarks
    This is the overridden method from the OdGiDrawable class.
  */
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  /** \details
    Checks whether the object is persistent (stored in a database).

    \returns True if the object is persistent, or false otherwise.
    \remarks
    This is the overridden method from the OdGiDrawable class.
  */
  virtual bool isPersistent() const;

  /** \details
    Returns the database ID of the object.

    \returns Pointer to the OdDbStub object with the database ID of the object.
    Returns a NULL pointer if the object is not persistent.
    \remarks
    This is the overridden method from the OdGiDrawable class.
  */
  virtual OdDbStub* id() const;

  /** \details
    Assigns the specified OdGsCache object to the object.

    \param pGsNode [in] Pointer to the OdGsCache object to be assigned.
    \remarks
    This is the overridden method from the OdGiDrawable class.
  */
  virtual void setGsNode(OdGsCache* pGsNode);

  /** \details
    Returns the OdGsCache associated with the object.

    \returns Pointer to the OdGsCache associated with the object.
    \remarks
    This is the overridden method from the OdGiDrawable class.
  */
  virtual OdGsCache* gsNode() const;

  /** \details
    Returns the drawable type that should be used during rendering with Gi.

    \returns DrawableType value with the drawable type of the object.
    \remarks
    The returned type must be one of the following:

    <table>
    Name                                          Value   Description
    DrawableType::kGeometry                       0       Geometry.
    DrawableType::kDistantLight                   1       Distant light.
    DrawableType::kPointLight                     2       Point light.
    DrawableType::kSpotLight                      3       Spot light.
    DrawableType::kAmbientLight                   4       Ambient light.
    DrawableType::kSolidBackground                5       Solid background.
    DrawableType::kGradientBackground             6       Gradient background.
    DrawableType::kImageBackground                7       Image background.
    DrawableType::kGroundPlaneBackground          8       Ground Plane Background.
    DrawableType::kViewport                       9       Viewport.
    DrawableType::kWebLight                       10      Web light.
    DrawableType::kSkyBackground                  11      Sky background.
    DrawableType::kImageBasedLightingBackground   12      Image based lighting background.
    </table>
  */
  virtual DrawableType drawableType() const;

  /** \details
    Applies the default properties of the specified database to this entity.

    \param pDb       [in]  Pointer to the database whose default values are to be used.
    \param doSubents [in]  Set to true if subentities should be processed.
    \remarks
    If pDb is NULL, the database containing this entity is used.
  */
  void setDatabaseDefaults(
    OdNwDatabase* pDb = 0,
    bool doSubents = false);

  /** \details
    Called by setDatabaseDefaults() after the values are set.

    \param pDb       [in]  Pointer to the database whose default values are to be used.
    \param doSubents [in]  Set to true if subentities should be processed.
    \remarks
    If pDb is NULL, the database containing this entity is used.
    This function allows custom classes to inspect and modify the values set by
    setDatabaseDefaults.
    The default implementation of this function is empty. This function can be
    overridden in custom classes.

    \remarks
    This function is not intended to be called by the user.
  */
  virtual void subSetDatabaseDefaults(
    OdNwDatabase* pDb,
    bool doSubents);
  
  /** \details
    Throws an exception if this object is not open NwOpenMode::kForRead.
    
    \remarks
    This function should be used only inside member functions that do not modify this object. 
    It should be the first function called by these functions.
    
    Throws:
    <table>
    Exception             Cause
    eNotOpenForRead       !isReadEnabled()
    </table>
  */
  void assertReadEnabled() const;
  
  /** \details
    Throws an exception if this object is not open NwOpenMode::kForWrite,
    and controls automatic undo and notification of modifications.
    
    \remarks
    This function should be used only inside member functions that modify this object. 
    It should be the first function called by these functions.
    
    Throws:
    <table>
    Exception             Cause
    eNotOpenForWrite     !isWriteEnabled()
    </table>
  */
  void assertWriteEnabled();

protected:
  //DOM-IGNORE-BEGIN
  friend class OdNwObjectImpl;
  OdNwObjectImpl* m_pImpl;
  //DOM-IGNORE-END
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwObject
  object pointers.
*/
typedef OdSmartPtr<OdNwObject> OdNwObjectPtr;

#endif // _NWOBJECT_H_
