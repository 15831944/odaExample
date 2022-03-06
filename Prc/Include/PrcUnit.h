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

#ifndef _PRCUNIT_INCLUDED_
#define _PRCUNIT_INCLUDED_ 
 

  /** \details
  <group PRC_Base_Classes>

   Class representing the units used in a .prc file.
  */
class PRC_TOOLKIT OdPrcUnit
{
private:
  double m_unit;
  bool   m_unit_from_CAD_file;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcUnit)
  //DOM-IGNORE-END
  
  /** \details
  Sets a new value of the units.

  \param unit [in] A new unit value to be set.
  */
  void setUnit(double unit);
  
  /** \details
  Returns the current unit value.
  */
  double unit() const;
  
  /** \details
  Sets a new value of the actual flag. 
  The actual flag indicates whether the unit value came from an actual CAD file (if yes, the flag is equal to true).

  \param unit_from_CAD_file [in] A new value of the flag to be set.
  The actual flag indicates whether the unit value came from an actual CAD file (if yes, the flag is equal to true).
  */
  void setUnitFromCADFile(bool unit_from_CAD_file);
  
  /** \details
  Returns the current value the actual flag.
  The actual flag indicates whether the unit value came from an actual CAD file (if yes, the flag is equal to true).
  */
  bool unitFromCADFile() const;
};

typedef OdArray<OdPrcUnit> OdPrcUnitArray;

#endif // _PRCUNIT_INCLUDED_

