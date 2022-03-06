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

#ifndef __TNW_VARIANT_H__
#define __TNW_VARIANT_H__

#include "RxVariant.h"
#include "NwExport.h"

class OdNwVariant;
class OdNwColor;
class OdGeMatrix3d;
class OdGePoint3d;
class OdGePoint2d;

/** \details
  A class that implements an extension of the <exref target="https://docs.opendesign.com/tkernel/OdVariant.html">OdVariant</exref> 
  class that can be used as universal storage of typified data.
  Corresponding C++ library: Od_Nw
  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwVariant : public OdVariant
{
public:

  /** \details
  Creates a factory (if it was not created previously) for variant objects of a specified data type.
  \param type [in] A data type of objects that are created by the factory.
  \returns Returns a raw pointer to a factory object.
  */
  static const OdVariant::TypeFactory* typeFactory(int type);

  /** \details
    Defines data types for OdNwVariant objects.
    <group OdNw_Types>
  */
  typedef enum 
  {
    /** A color data type. */
    kColor = OdVariant::kNextType, 
    /** A matrix3d data type. */
    kMatrix3d,
    /** A date/time data type. */ 
    kTime,
    /** A 3d pont data type. */
    kPoint3d,
    /** A 2d pointe data type. */
    kPoint2d,
    /** A system data type (for internal use only). */
    kNextType
  } Type;


  /** \details
  Creates an empty OdNwVariant object. 
  */
  OdNwVariant();
  
  /** \details
  Creates a new OdNwVariant object that is a copy of another variant object represented with the OdVariant class instance. 
  \param value [in] An OdVariant object that is copied to a created OdNwVariant object.
  */
  OdNwVariant(const OdVariant& value);
  
  /** \details
  Creates a new OdNwVariant object that is a copy of another Tf variant object (copy constructor). 
  \param value [in] An OdNwVariant object that is copied to a created OdNwVariant object.
  */
  OdNwVariant(const OdNwVariant& value);

  /** \details
  Creates a new OdNwVariant object with a specified OdNwColor.
  \param value [in] An OdNwColor value.
  */
  OdNwVariant(const OdNwColor& value);

  /** \details
  Creates a new OdNwVariant object with a specified OdGeMatrix3d.
  \param value [in] An OdGeMatrix3d value.
  */
  OdNwVariant(const OdGeMatrix3d& value);

  /** \details
  Creates a new OdNwVariant object with a specified time value.
  \param value [in] A time value.
  */
  OdNwVariant(const tm& value);

  /** \details
  Creates a new OdNwVariant object with a specified 3d point value.
  \param value [in] A OdGePoint3d value.
  */
  OdNwVariant(const OdGePoint3d& value);

  /** \details
  Creates a new OdNwVariant object with a specified 2d point value.
  \param value [in] A OdGePoint2d value.
  */
  OdNwVariant(const OdGePoint2d& value);

  /** \details
  The assignment operator for two OdNwVariant objects.
  \param value [in] A right operand of the assignment operation.
  \returns Returns this variant object after the assignment operation.
  */
  OdNwVariant& operator =(const OdNwVariant& value);

  /** \details
  Destroys the variant object.
  */
  virtual ~OdNwVariant();
  
  /** \details
  Retrieves the current color of the variant object.
  \returns Returns the current color of the variant object.
  */
  const OdNwColor& getColor() const;
  
  /** \details
  Retrieves the current matrix3d of the variant object.
  \returns Returns the current matrix3d of the variant object.
  */
  const OdGeMatrix3d& getMatrix3d() const;

  /** \details
  Retrieves the current time of the variant object.
  \returns Returns the current time of the variant object as tm.
  */
  const tm& getTime() const;

  /** \details
    Returns a reference to the value of this variant object as an OdArray<OdNwColor> object.
    
    \remarks
    No check is made to determine whether this variant object is of the specified type.
  */
  const OdArray<OdNwColor>& getColorArray() const;

  /** \details
  Retrieves the 3d point of the variant object.
  \returns Returns the current 3d point of the variant object as OdGePoint3d.
  */
  const OdGePoint3d& getPoint3d() const;

  /** \details
  Retrieves the 2d point of the variant object.
  \returns Returns the current 2d point of the variant object as OdGePoint2d.
  */
  const OdGePoint2d& getPoint2d() const;

  /** \details
    Sets a new color for the variant object.
  
    \param value [in] A new color value to set.
    \returns Returns the reference to the modified variant object.
  */
  OdNwVariant& setColor(const OdNwColor& value);

  /** \details
    Sets a new matrix3d for the variant object.
  
    \param value [in] A new matrix3d value.
    \returns Returns the reference to the modified variant object.
  */
  OdNwVariant& setMatrix3d(const OdGeMatrix3d& value);

  /** \details
    Sets a new time for the variant object.
  
    \param value [in] A new time value to set.
    \returns Returns the reference to the modified variant object.
  */
  OdNwVariant& setTime(const tm& value);

  /** \details
    Sets the given color array for this variant object.

    \param val [in] A new array of colors to set.

    \returns
    Returns a reference to this variant object.
  */
  OdVariant& setColorArray(const OdArray<OdNwColor>& array);

  /** \details
    Sets a new 3d point for the variant object.

    \param value [in] A new 3d point value as OdGePoint3d to set.
    \returns Returns the reference to the modified variant object.
  */
  OdNwVariant& setPoint3d(const OdGePoint3d& value);
  /** \details
    Sets a new 2d point for the variant object.

    \param value [in] A new 2d point value as OdGePoint2d to set.
    \returns Returns the reference to the modified variant object.
  */
  OdNwVariant& setPoint2d(const OdGePoint2d& value);

protected:
  /** \details
    Sets a new type for the variant object.
    
    \param newType [in] New variant type to set.
    \param type [in] Old variant type.
    \param data [in] Pointer to data.
  */
  void setVarType(int newType, int& type, void* data);
};

/** \details
The comparison operator for two Nw variant data types.
\param lhs [in] A left-hand operand for the comparison operation.
\param rhs [in] A right-hand operand for the comparison operation.
\returns Returns true if the specified data types can be cast to each other; otherwise returns false.
*/
inline bool operator==(OdNwVariant::Type lhs, OdVariant::Type rhs)
{
  return lhs == static_cast<OdNwVariant::Type>(rhs);
}

/** \details
The non-equality operator for two Nw variant data types.
\param lhs [in] A left-hand operand.
\param rhs [in] A right-hand operand.
\returns Returns true if the specified data types are not equal; otherwise returns false.
*/
inline bool operator!=(OdNwVariant::Type lhs, OdVariant::Type rhs)
{
  return !(lhs == rhs);
}

/** \details
The comparison operator for two OdVariant data types.
\param lhs [in] A left-hand operand for the comparison operation.
\param rhs [in] A right-hand operand for the comparison operation.
\returns Returns true if the specified data types are equal; otherwise returns false.
*/
inline bool operator==(OdVariant::Type lhs, OdNwVariant::Type rhs)
{
  return rhs == lhs;
}

/** \details
The non-equality operator for two OdVariant data types.
\param lhs [in] A left-hand operand.
\param rhs [in] A right-hand operand.
\returns Returns true if the specified data types are not equal; otherwise returns false.
*/
inline bool operator!=(OdVariant::Type lhs, OdNwVariant::Type rhs)
{
  return rhs != lhs;
}

#endif //__TNW_VARIANT_H__
