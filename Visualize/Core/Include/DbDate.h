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




#ifndef _ODDBDATE_INCLUDED_
#define _ODDBDATE_INCLUDED_

#include "TD_PackPush.h"

#include "OdTimeStamp.h"

class OdTvDbDwgFiler;

/** \details
    This class represents Date objects in an OdTvDbDatabase instance.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDate : public OdTimeStamp
{
public:
  /** \param tStamp [in]  TimeStamp.
    \param init [in]  Initial value.
    
    \remarks
    The default constructor initializes the Julian date and time to zero.
    
    init must be one of the following:
    
    <table>
    Name                 Value    Description
    kInitZero            1        Zero.
    kInitLocalTime       2        Workstation date in local time.
    kInitUniversalTime   3        Workstation date in Universal (Greenwich Mean) Time..
    </table>
  */
   OdTvDbDate();
  OdTvDbDate(
    const OdTimeStamp& tStamp);
  OdTvDbDate(
    InitialValue init);

  OdTvDbDate operator=(
    const OdTimeStamp& tStamp);

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  void dwgIn(
    OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  void dwgOut(
    OdTvDbDwgFiler* pFiler) const;
};

#include "TD_PackPop.h"

#endif // _ODDBDATE_INCLUDED_

