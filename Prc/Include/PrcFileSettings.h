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

#ifndef _PRCFILESETTINGS_INCLUDED_
#define _PRCFILESETTINGS_INCLUDED_
 

/** \details
<group PRC_Files_Structures_Assemblies>

Class implements .prc file settings. 
*/
class PRC_TOOLKIT OdPrcFileSettings
{
private:
  double   m_dCompressTopoBrepTolerance;
  bool     m_bCompressTopoBreps;
  bool     m_bCompressTessellation;
public:

  /** \details 
  Creates a .prc file settings instance.
  */
  OdPrcFileSettings();

  /** \details
  Returns the current value of the compression flag for the topology boundary representation data.
  If the flag is equal to true, the compression algorithm is applied for the topology boundary representation data, and it is not applied when the flag value is false.
  The default flag value is false.
  */
  bool   getCompressTopoBrepsFlag() const;
  
  /** \details
  Sets a new value of the compression flag for the topology boundary representation data.
  If the flag is equal to true, the compression algorithm is applied for the topology boundary representation data, and it is not applied when the flag value is false.
  The default flag value is false.
  
  \param bSet [in] A new flag value to be set.
  */
  void   setCompressTopoBrepsFlag( bool bSet );
  
  /** \details
  Returns the current value of the tolerance for compressing the topology boundary representation data.
  The default tolerance value is 0.01.
  */  
  double getCompressTopoBrepTolerance() const;
  
  /** \details
  Sets a new value of the tolerance for compressing the topology boundary representation data.
  The default tolerance value is 0.01.
  
  \param dTolerance [in] A new tolerance value to be set.
  \returns Returns eOk if new value wes successfully set or an appropriate error code in the other case.
  */
  OdResult   setCompressTopoBrepTolerance( double dTolerance );
  
  /** \details
  Returns the current value of the compression flag for the tessellation data.
  If the flag is equal to true, the compression algorithm is applied for the tessellation data, and it is not applied when the flag value is false.
  The default flag value is false.
  */
  bool   getCompressTessellationFlag() const;

  /** \details
  Sets a new value of the compression flag for the tessellation data.
  If the flag is equal to true, the compression algorithm is applied for the tessellation data, and it is not applied when the flag value is false.
  The default flag value is false.

  \param bSet [in] A new flag value to be set.
  */
  void   setCompressTessellationFlag(bool bSet);
};

#endif // _PRCFILESETTINGS_INCLUDED_

