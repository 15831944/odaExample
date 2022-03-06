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

#ifndef _DAI_ERROR_ID_H_
#define _DAI_ERROR_ID_H_

#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

/** \details
  A data type that is used to represent an error code that is used for event handling or events within the SDAI module.
*/
typedef unsigned int SdaiErrorId;

/* SDAI C late binding error codes: *********************************/
#define sdaiNO_ERR 0 /* No error */
#define sdaiSS_OPN 10 /* Session open */
#define sdaiSS_NAVL 20 /* SDAI not available */
#define sdaiSS_NOPN 30 /* Session is not open */
#define sdaiRP_NEXS 40 /* Repository does not exist */
#define sdaiRP_NAVL 50 /* Repository not available */
#define sdaiRP_OPN 60 /* Repository open */
#define sdaiRP_NOPN 70 /* Repository is not open */
#define sdaiTR_EAB 80 /* Transaction ended abnormally */
#define sdaiTR_EXS 90 /* Transaction exists */
#define sdaiTR_NAVL 100 /* Transaction currently not available */
#define sdaiTR_RW 110 /* Transaction read-write */
#define sdaiTR_NRW 120 /* Transaction not read-write */
#define sdaiTR_NEXS 130 /* Transaction does not exist */
#define sdaiMO_NDEQ 140 /* SDAI-model not domain equivalent */
#define sdaiMO_NEXS 150 /* SDAI-model does not exist */
#define sdaiMO_NVLD 160 /* SDAI-model invalid */
#define sdaiMO_DUP 170 /* SDAI-model duplicate */
#define sdaiMX_NRW 180 /* SDAI-model access not read-write */
#define sdaiMX_NDEF 190 /* SDAI-model access not defined */
#define sdaiMX_RW 200 /* SDAI-model access read-write */
#define sdaiMX_RO 210 /* SDAI-model access read-only */
#define sdaiSD_NDEF 220 /* Schema definition not defined */
#define sdaiED_NDEF 230 /* Entity definition not defined */
#define sdaiED_NDEQ 240 /* Entity definition not domain equiv.*/
#define sdaiED_NVLD 250 /* Entity definition invalid */
#define sdaiRU_NDEF 260 /* Rule not defined */
#define sdaiEX_NSUP 270 /* Expression evaluation not supported */
#define sdaiAT_NVLD 280 /* Attribute invalid */
#define sdaiAT_NDEF 290 /* Attribute not defined */
#define sdaiSI_DUP 300 /* Schema instance duplicate */
#define sdaiSI_NEXS 310 /* Schema instance does not exist */
#define sdaiEI_NEXS 320 /* Entity instance does not exist */
#define sdaiEI_NAVL 330 /* Entity instance not available */
#define sdaiEI_NVLD 340 /* Entity instance invalid */
#define sdaiEI_NEXP 350 /* Entity instance not exported */
#define sdaiSC_NEXS 360 /* Scope does not exist */
#define sdaiSC_EXS 370 /* Scope exists */
#define sdaiAI_NEXS 380 /* Aggregate instance does not exist */
#define sdaiAI_NVLD 390 /* Aggregate instance invalid */
#define sdaiAI_NSET 400 /* Aggregate instance is empty */
#define sdaiVA_NVLD 410 /* Value invalid */
#define sdaiVA_NEXS 420 /* Value does not exist */
#define sdaiVA_NSET 430 /* Value not set */
#define sdaiVT_NVLD 440 /* Value type invalid */
#define sdaiIR_NEXS 450 /* Iterator does not exist */
#define sdaiIR_NSET 460 /* Current member is not defined */
#define sdaiIX_NVLD 470 /* Index invalid */
#define sdaiER_NSET 480 /* Event recording not set */
#define sdaiOP_NVLD 490 /* Operator invalid */
#define sdaiFN_NAVL 500 /* Function not available */
#define sdaiAB_NEXS 800 /* ADB does not exist */
#define sdaiSY_ERR 1000 /* Underlying system error */

namespace OdDAI {
  
  /** \details
    A data type that is used to represent an error code that is used for event handling or events within the DAI module.
  */
  typedef unsigned int daiErrorId;
  
  /** \details
    Returns description of the specified error code.
    
    \param errorId              [in] Error code for which to get description.
    \returns
    Const char pointer to description of the specified error code.
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  DAI_EXPORT const char* errorToDescription(daiErrorId errorId);
  
  /** \details
    Returns character representation of the specified error code.
    
    \param errorId              [in] Error code for which to get character representation.
    \returns
    Const char pointer to the converted error code.
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  DAI_EXPORT const char* errorCodeToStr(daiErrorId errorId);
}
#endif
