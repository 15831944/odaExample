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

#ifndef _PRCMARKUP_INCLUDED_
#define _PRCMARKUP_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcBaseWithGraphics.h"
#include "PrcUserData.h"
#include "PrcBaseTessData.h"

SMARTPTR(OdPrcMarkup);

/** \details 
<group PRC_Markup_Classes> 

Class stores data of markups.
*/
class PRC_TOOLKIT OdPrcMarkup : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcMarkup);
  //DOM-IGNORE-END

  /** \details
  Returns current common tessellation data.
  Common tessellation data is returned as a reference to an OdPrcBaseTessDataPtr object, therefore it can be used to set new tessellation data.
  */
  OdPrcBaseTessDataPtr &tessellation();
  
  /** \details
  Returns current common tessellation data.
  */
  const OdPrcBaseTessDataPtr &tessellation() const;
  
  /** \details
  Returns current user defined data.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();
  
  /** \details
  Returns current user defined data.
  */
  const OdPrcUserData &userData() const;
  
  /** \details
  Returns the current array of leader identifiers.
  The array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new leader identifiers.
  */
  OdPrcObjectIdArray &leader();
  
  /** \details
  Returns the current array of leader identifiers.
  */
  const OdPrcObjectIdArray &leader() const;
  
  /** \details
  Returns the current array of linked item identifiers.
  The array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new linked item identifiers.
  */
  OdPrcObjectIdArray &linkedItem();
  
  /** \details
  Returns the current array of linked item identifiers.
  */
  const OdPrcObjectIdArray &linkedItem() const;


  /** \details
  Enumeration represents available markup types according to the ISO document.
  */
  enum MarkupType {
    /** Unknown type.*/
    kUnknown = 0,
    /** Plain text.*/
    kText,
    /** Dimension.*/
    kDimension,
    /** Arrow.*/
    kArrow,
    /** Balloon.*/
    kBalloon,
    /** Circle's center.*/
    kCircleCenter,
    /** Coordinate.*/
    kCoordinate,
    /** Datum.*/
    kDatum,
    /** Fastener.*/
    kFastener,
    /** Geometric Dimensioning and Tolerance Block.*/
    kGdt,
    /** Locator.*/
    kLocator,
    /** Measurement point.*/
    kMeasurementPoint,
    /** Roughness.*/
    kRoughness,
    /** Welding.*/
    kWelding = 13,
    /** Table.*/
    kTable = 15, 
    /** Other type.*/
    kOther
  };

  /** \details
  Enumeration represents available markup subtypes.
  */
  enum MarkupSubType {
    /** Unknown subtype.*/
    kUnknownSubtype = 0,
    /** For internal use.*/
    kEnumMax,

    /** Datum identifier subtype */
    kDatum_Ident = 1,
    /** Datum target subtype */
    kDatum_Target = 2,
    /** For internal use.*/
    kDatum_EnumMax,

    /** Distance dimension subtype */
    kDimension_Distance = 1,
    /** Dimension offset distance subtype */
    kDimension_Distance_Offset = 2,
    /** Dimension cumulative distance subtype */
    kDimension_Distance_Cumulate = 3,
    /** Dimension chamfer callout subtype */
    kDimension_Chamfer = 4,
    /** Dimension slope subtype */
    kDimension_Slope = 5,
    /** Dimension ordinate subtype */
    kDimension_Ordinate = 6,
    /** Dimension radius subtype */
    kDimension_Radius = 7,
    /** Tangent radius dimension subtype */
    kDimension_Radius_Tangent = 8,
    /** Cylinder radius dimension subtype */
    kDimension_Radius_Cylinder = 9,
    /** Radius edge dimension subtype */
    kDimension_Radius_Edge = 10,
    /** Diameter dimension subtype */
    kDimension_Diameter = 11,
    /** Tangent diameter dimension subtype */
    kDimension_Diameter_Tangent = 12,
    /** Cylinder diameter dimension subtype */
    kDimension_Diameter_Cylinder = 13,
    /** Diameter edge dimension subtype */
    kDimension_Diameter_Edge = 14,
    /** Cone diameter dimension subtype */
    kDimension_Diameter_Cone = 15,
    /** Length dimension subtype */
    kDimension_Length = 16,
    /** Curvilinear length dimension subtype */
    kDimension_Length_Curvilinear = 17,
    /** Circular length dimension subtype */
    kDimension_Length_Circular = 18,
    /** Angle dimension subtype */
    kDimension_Angle = 19,
    /** For internal use.*/
    kDimension_EnumMax,

    /** Geometric Dimensioning and Tolerancing subtype */
    kGdt_Fcf = 1,
    /** For internal use.*/
    kGdt_EnumMax,

    /** Welding line subtype */
    kWelding_Line = 1,
    /** Welding spot subtype */
    kWelding_Spot = 2,
    /** For internal use.*/
    kWelding_EnumMax,

    /** Symbol user subtype */
    kOther_Symbol_User,
    /** Symbol utility subtype */
    kOther_Symbol_Utility = 2,
    /** Symbol custom subtype */
    kOther_Symbol_Custom = 3,
    /** Geometric reference subtype */
    kOther_GeometricReference = 4,
    /** For internal use.*/
    kOther_EnumMax
  };

  /** \details
  Sets a new markup type and sub type.

  \param type [in] A new markup type to be set.
  \param subType [in] A new markup sub-type to be set.
  \param validate [in] Enable validation of type and sub type values.
  */
  OdResult setType(OdPrcMarkup::MarkupType type, OdPrcMarkup::MarkupSubType subType = kUnknownSubtype, bool validate = true);
  
  /** \details
  Returns the current markup type.
  */
  MarkupType type() const;

  /** \details
  Returns the current markup sub-type.
  */
  MarkupSubType subType() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
  virtual void subViewportDraw (OdGiViewportDraw * pVd) const;
};

#endif // _PRCMARKUP_INCLUDED_

