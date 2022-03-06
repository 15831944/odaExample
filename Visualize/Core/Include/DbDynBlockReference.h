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

#ifndef _DbDynBlock_h_Included_
#define _DbDynBlock_h_Included_


#include "DbEvalGraph.h"
#include "TD_PackPush.h"

// Forward class declarations

class OdTvDbBlockReference;
class OdTvDbDynBlockReference;
class OdTvDbDynBlockReferenceProperty;
class OdTvDbDynBlockReferencePropertyImpl;
class OdTvDbDynBlockReferenceImpl;
struct OdTvDbBlkParamPropertyDescriptor;
class OdTvDbBlockParameter;
class OdTvDbDynBlockTableRecordImpl;
class OdTvDbBlockRepresentationContext;
typedef OdSmartPtr<OdTvDbBlockParameter> OdTvDbBlockParameterPtr;

/** \details
    This class is a utility class referencing properties of dynamic blocks.
    
    \remarks
    
    Corresponding C++ library: TD_DynBlocks
    <group OdTvDb_Classes>
*/
class DYNBLOCKS_EXPORT OdTvDbDynBlockReferenceProperty : public OdRxObject
{
public:

  enum UnitsType {
    kNoUnits  = 0,  // No units defined.
    kAngular  = 1,  // Angle.
    kDistance = 2,  // Distance.
    kArea     = 3   // 2D area.
  };

  OdTvDbDynBlockReferenceProperty ();
  virtual ~OdTvDbDynBlockReferenceProperty ();

  /** 
    \param other [in]  Constant reference to the dynamic block reference property.
  */
  OdTvDbDynBlockReferenceProperty (const OdTvDbDynBlockReferenceProperty& other);

  OdTvDbDynBlockReferenceProperty& operator=(
    const OdTvDbDynBlockReferenceProperty& other);

  /** \details
    Returns the Object ID of the dynamic block reference that owns this property.
  */
  OdTvDbObjectId blockId() const;

  /** \details
    Returns the name of this property.
    \remarks
    All property names in a given block reference are guaranteed unique.
  */
  OdString propertyName()  const;

  /** \details
    Returns the type of the property value.
  */
  OdTvResBuf::ValueType propertyType() const;

  /** \details
    Returns true if and only if this property is Read-Only.
  */
  bool readOnly() const;

  
  /** \details
    Returns true if and only if this property is displayed on the Property Palette.
  */
  bool show() const;

  /** \details
    Returns true if and only if this property is visible in the current visibility state.
  */
  bool visibleInCurrentVisibilityState() const;

  /** \details
    Returns the description of this property.
  */
  OdString description () const;

  /** \details
    Returns the units of this property.
    
    \remarks
    This function may be used to format property values.
    
    unitsType() returns one of the following:
    
    <table>
    Name        Value   Description
    kNoUnits    0       No units defined.
    kAngular    1       Angle.
    kDistance   2       Distance.
    kArea       3       2D area.
    </table>
  */
  UnitsType             unitsType () const;


  /** \details
    Returns an array of allowed values for this property.
    \param allowedValues [out]  Receives an an array of allowed values.
  */
  void getAllowedValues(OdTvResBufArray& allowedValues);

  /** \details
    Returns the current value of the property on the dynamic block reference.
  */
  OdTvResBufPtr value () const;

  /** \details
    Sets the current value of the property on the dynamic block reference.
    \param value [in]  Value.
    \returns
    Returns true if and only if successful.
  */
  bool setValue (const OdTvResBufPtr& value);

  /** \details
    Returns a parameter smart pointer.
  */
  OdTvDbBlockParameterPtr getParameter();
  
  /** \details
    Returns a parameter descriptor.
    
    \param parameterId [out]  Parameter ID.
    \param pDescriptor [out]  Parameter descriptor.     
  */
  void getDescriptor(OdTvDbEvalNodeId& parameterId, OdTvDbBlkParamPropertyDescriptor& pDescriptor);

private:
  friend class OdTvDbDynBlockReferencePropertyImpl;
  OdTvDbDynBlockReferencePropertyImpl* m_pImpl;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDynBlockReferenceProperty object pointers.
*/
typedef OdSmartPtr<OdTvDbDynBlockReferenceProperty> OdTvDbDynBlockReferencePropertyPtr;
/** \details
    This template class is a specialization of the OdArray class for OdTvDbDynBlockReferencePropertyPtr objects.
*/
typedef OdArray<OdTvDbDynBlockReferencePropertyPtr> OdTvDbDynBlockReferencePropertyArray;

/** \details
    This class is a utility class providing access to information on dynamic block references. 
    Corresponding C++ library: TD_DynBlocks
    <group OdTvDb_Classes>
*/
class DYNBLOCKS_EXPORT OdTvDbDynBlockReference
{
  ODRX_HEAP_OPERATORS();
public:
  
  /** 
    \param blockRefId [in]  Object ID of the dynamic block reference.
  */
  OdTvDbDynBlockReference(const OdTvDbObjectId& blockRefId);

  /** 
    \param pRef [in]  Pointer to the dynamic block reference.
  */
  OdTvDbDynBlockReference(OdTvDbBlockReference* pRef);

  virtual ~OdTvDbDynBlockReference ();

  /** \details
    Returns true if and only if the specified Block Table Record 
    contains dynamic block information.
    
    \param blockTableRecordId [in]  Block Table Record Object ID.
    
    \remarks
    If blockTableRecordId is not specified, the Block Reference specified
    in the constructor will be used.
  */
  static bool isDynamicBlock (const OdTvDbObjectId& blockTableRecordId);
  
  /** \details
    Returns true if and only if the specified Block Table Record 
    contains dynamic block information.
    
    \remarks
    The Block Reference specified in the constructor will be used.
  */
  bool isDynamicBlock () const;

  /** \details
    Returns the Object ID of the block reference.
  */
  OdTvDbObjectId blockId() const;


  /** \details
    Returns an array of the dynamic block properties of the block reference.
    
    \param properties [out]  Receives an array of properties.
    
    \remarks
    An empty array will be returned if the block reference has no dynamic block properties.
  */
  void getBlockProperties(OdTvDbDynBlockReferencePropertyArray& properties) const;

  /** \details
    Resets all properties in the block reference to those of the block definition.
  */
  void resetBlock();

  /** \details
    Converts the dynamic block reference to a static block.
    
    \param newBlockName [in]  New block name.
    
    \remarks
    If newBlockName is not specified, an anonymous block is created.
  */
  bool convertToStaticBlock();
  bool convertToStaticBlock (const OdString& newBlockName);

  /** \details
    Returns the Object ID of the dynamic block BlockTableRecord.
    
    \returns
    Returns NULL if the block reference is not a dynamic block. 
  */
  OdTvDbObjectId dynamicBlockTableRecord () const;

  /** \details
    Returns the ObjectID of the anonymous representation block BlockTableRecord used to draw the dynamic block.
  */
  OdTvDbObjectId anonymousBlockTableRecord () const; 

  OdTvDbBlockRepresentationContext* getRepresentationContext() const;
private:
  OdTvDbDynBlockReference();
  OdTvDbDynBlockReferenceImpl* m_pImpl;
  friend class OdTvDbDynBlockTableRecord;
};

/** \details
  <group OdTvDb_Classes>
  Corresponding C++ library: TD_DynBlocks
*/
class DYNBLOCKS_EXPORT OdTvDbDynBlockTableRecord
{
  ODRX_HEAP_OPERATORS();
public:
  OdTvDbDynBlockTableRecord(OdTvDbObjectId blockId);
  ~OdTvDbDynBlockTableRecord();
  bool isDynamicBlock() const;
  OdTvDbObjectId blockTableRecordId() const;
  
  /** \details
    Gets an ObjectId array of all anonymous representation blocks created from the dynamic block definition.
    
    \param anonymousIds [out]  An output OdTvDbObjectIdArray.
  */
  void getAnonymousBlockIds(OdTvDbObjectIdArray& anonymousIds) const;
  void updateAnonymousBlocks() const;
private:
  OdTvDbDynBlockTableRecord();
  OdTvDbDynBlockTableRecordImpl* m_pImpl;
};

#include "TD_PackPop.h"

#endif
