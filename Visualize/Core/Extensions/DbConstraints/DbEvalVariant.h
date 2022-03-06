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

#ifndef OdTvDbEvalVariant_INCLUDED_
#define OdTvDbEvalVariant_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "ResBuf.h"
#include "DbFiler.h"

#include "TD_PackPush.h"

class OdTvDbEvalVariant;

typedef OdSmartPtr<OdTvDbEvalVariant> OdTvDbEvalVariantPtr;

/** \details
  Declares the data types.
*/
enum DwgDataType {
  kDwgNull = 0,
  kDwgReal = 1,
  kDwgInt32 = 2,
  kDwgInt16 = 3,
  kDwgInt8 = 4,
  kDwgText = 5,
  kDwgBChunk = 6,
  kDwgHandle = 7,
  kDwgHardOwnershipId = 8,
  kDwgSoftOwnershipId = 9,
  kDwgHardPointerId = 10,
  kDwgSoftPointerId = 11,
  kDwg3Real = 12,
  kDwgInt64 = 13,
  kDwg2Real = 14,
  kDwgNotRecognized = 19
};

/** \details
  This class represents a wrapper for a resbuf structure.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbEvalVariant : public OdTvResBuf
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbEvalVariant );

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbEvalVariant();

  /** \details
    Destructor destroys an instance of this class.
  */
  ~OdTvDbEvalVariant();

  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdTvDbEvalVariant& other); 
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdTvDbEvalVariant* pOther);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(double       dVal);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(short        iVal);
//static OdTvDbEvalVariantPtr init(const ACHAR*  szVal);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(int         lVal);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdTvDbObjectId& id);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdGePoint2d&  pt);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdGePoint3d&  pt);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdTvResBuf& rb);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdTvDbEvalVariantPtr init(const OdString& str);

  /** \details
    Sets the content of this variable using a given value.
  */
  OdTvDbEvalVariant& operator=(const OdTvResBuf& rb);
  OdTvDbEvalVariant& operator=(double      dVal);
  OdTvDbEvalVariant& operator=(short       iVal);
  OdTvDbEvalVariant& operator=(int        lVal);
//OdTvDbEvalVariant& operator=(const ACHAR* szVal);
  OdTvDbEvalVariant& operator=(const OdTvDbEvalVariant& other);
  OdTvDbEvalVariant& operator=(const OdTvDbObjectId& id);
  OdTvDbEvalVariant& operator=(const OdGePoint2d&  pt);
  OdTvDbEvalVariant& operator=(const OdGePoint3d&  pt);
  OdTvDbEvalVariant& operator=(const OdString&  str);

  /** \details
    Clears the content of this variable and frees any allocated memory.
  */
  void clear();

  /** \details
    Copies the content of the variable from another rx-object.
  */
  void copyFrom(const OdRxObject* pOther);//eWrongObjectType 

  /** \details
    Checks whether content of this variable less than content of a given variable.
  */
  bool operator <  ( const OdTvDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable more than content of a given variable.
  */
  bool operator >  ( const OdTvDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable equal to or less than content of a given variable.
  */
  bool operator <= ( const OdTvDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable equal to or more than content of a given variable.
  */
  bool operator >= ( const OdTvDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable is equal to the content of a given variable.
  */
  bool operator == ( const OdTvDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable is not equal to the content of a given variable.
  */
  bool operator != ( const OdTvDbEvalVariant& val ) const;

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** \details
    Returns the data type of this variable.
  */
  DwgDataType getType() const;

  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const double value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const short value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const int value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdString& value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdTvDbObjectId value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdGePoint3d& value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdGePoint2d& value);

  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(double& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(short& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(int& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdString& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdTvDbObjectId& value, OdTvDbDatabase *pDb = NULL) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdGePoint3d& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdGePoint2d& value) const;

  /** \details
    Gets the value of this variable transformed to 'int'.
  */
  int getAsInt() const;

  /** \details
    Gets the value of this variable transformed to 'double'.
  */
  double getAsDouble() const;

protected:
  /*!DOM*/
  DwgDataType m_type;

};

#include "TD_PackPop.h"

#endif
