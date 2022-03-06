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

#ifndef OdLicense_h__
#define OdLicense_h__

#include <RootExport.h>
#include <OdResult.h>
#include <OdString.h>
#include <OdError.h>

#ifdef ODA_LICENSING_DEBUG
#include <cstdlib>
#endif

class FIRSTDLL_EXPORT OdLicenseError : public virtual OdError {
public:
    OdLicenseError(OdResult res, const OdString& message);
    OdLicenseError(const OdError& err);
    OdResult code() const;
};

#if defined(ODA_LICENSING_ENABLED) || defined(ODA_LICENSING_DEBUG)

#ifdef __BORLANDC__

#define REG_CRYPT_BEGIN1 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x01);
#define REG_CRYPT_END1   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x01);

#define REG_CRYPT_BEGIN2 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x02);
#define REG_CRYPT_END2   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x02);

#define REG_CRYPT_BEGIN3 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x03);
#define REG_CRYPT_END3   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x03);

#define REG_CRYPT_BEGIN4 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x04);
#define REG_CRYPT_END4   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x04);

#define REG_CRYPT_BEGIN5 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x05);
#define REG_CRYPT_END5   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x05);

#define REG_CRYPT_BEGIN6 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x06);
#define REG_CRYPT_END6   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x06);

#define REG_CRYPT_BEGIN7 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x07);
#define REG_CRYPT_END7   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x07);

#define REG_CRYPT_BEGIN8 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x08);
#define REG_CRYPT_END8   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x08);

#define REG_CRYPT_BEGIN9 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x09);
#define REG_CRYPT_END9   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x09);

#define REG_CRYPT_BEGIN10 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x0A);
#define REG_CRYPT_END10   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x0A);

#define REG_CRYPT_BEGIN11 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x0B);
#define REG_CRYPT_END11   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x0B);

#define REG_CRYPT_BEGIN12 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x0C);
#define REG_CRYPT_END12   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x0C);

#define REG_CRYPT_BEGIN13 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x0D);
#define REG_CRYPT_END13   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x0D);

#define REG_CRYPT_BEGIN14 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x0E);
#define REG_CRYPT_END14   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x0E);

#define REG_CRYPT_BEGIN15 __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x0F);
#define REG_CRYPT_END15   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x0F);

#else

#define REG_CRYPT_BEGIN1 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x01

#define REG_CRYPT_END1 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x01

#define REG_CRYPT_BEGIN2 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x02

#define REG_CRYPT_END2 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x02

#define REG_CRYPT_BEGIN3 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x03

#define REG_CRYPT_END3 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x03

#define REG_CRYPT_BEGIN4 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x04

#define REG_CRYPT_END4 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x04

#define REG_CRYPT_BEGIN5 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x05

#define REG_CRYPT_END5 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x05

#define REG_CRYPT_BEGIN6 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x06

#define REG_CRYPT_END6 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x06

#define REG_CRYPT_BEGIN7 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x07

#define REG_CRYPT_END7 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x07

#define REG_CRYPT_BEGIN8 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x08

#define REG_CRYPT_END8 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x08

#define REG_CRYPT_BEGIN9 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x09

#define REG_CRYPT_END9 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x09 

#define REG_CRYPT_BEGIN10 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x0A

#define REG_CRYPT_END10 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x0A

#define REG_CRYPT_BEGIN11 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x0B

#define REG_CRYPT_END11 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x0B

#define REG_CRYPT_BEGIN12 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x0C

#define REG_CRYPT_END12 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x0C

#define REG_CRYPT_BEGIN13 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x0D

#define REG_CRYPT_END13 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x0D

#define REG_CRYPT_BEGIN14 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x0E

#define REG_CRYPT_END14 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x0E

#define REG_CRYPT_BEGIN15 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x0F

#define REG_CRYPT_END15 \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x0F

#endif

// Mode status

typedef struct _MODE_STATUS {
    BYTE ModeId;
    bool IsRegistered,
        IsKeyPresent,
        IsWrongHardwareID,
        IsKeyExpired,
        IsModeExpired,
        IsBlackListedKey,
        IsModeActivated;
}MODE_STATUS, *PMODE_STATUS;

#ifdef __BORLANDC__

extern "C"  char*   __declspec(dllimport) _stdcall GetRegistrationKeys();
extern "C" _stdcall __declspec(dllimport) BOOL GetRegistrationInformation( BYTE ModeId, char** Key, char** Name);
extern "C" _stdcall __declspec(dllimport) BOOL RemoveKey( BYTE ModeId );
extern "C" _stdcall __declspec(dllimport) BOOL CheckKey( char* Key, char* Name, PMODE_STATUS mode_status );
extern "C" _stdcall __declspec(dllimport) BOOL CheckKeyAndDecrypt( char* Key, char* Name, BOOL SaveKey );
extern "C" _stdcall __declspec(dllimport) BOOL GetKeyDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
extern "C" _stdcall __declspec(dllimport) BOOL GetKeyExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
extern "C" _stdcall __declspec(dllimport) BOOL GetTrialDays( BYTE ModeId, DWORD* Total, DWORD* Left );
extern "C" _stdcall __declspec(dllimport) BOOL GetTrialExecs( BYTE ModeId, DWORD* Total, DWORD* Left );
extern "C" _stdcall __declspec(dllimport) BOOL GetExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
extern "C" _stdcall __declspec(dllimport) BOOL GetModeInformation( BYTE ModeID, char** ModeName, PMODE_STATUS mode_status);
extern "C"  char*   __declspec(dllimport) _stdcall GetHardwareID();
extern "C"  char*   __declspec(dllimport) _stdcall GetHardwareIDEx( BYTE ModeID );
extern "C" _stdcall __declspec(dllimport) BOOL SetUserKey( char* Key, DWORD KeySize );

#else

extern "C" char* __stdcall GetRegistrationKeys();
extern "C" BOOL  __stdcall GetRegistrationInformation( BYTE ModeId, char** Key, char** Name);
extern "C" BOOL  __stdcall RemoveKey( BYTE ModeId );
extern "C" BOOL  __stdcall CheckKey( char* Key, char* Name, PMODE_STATUS mode_status );
extern "C" BOOL  __stdcall CheckKeyAndDecrypt( char* Key, char* Name, BOOL SaveKey );
extern "C" BOOL  __stdcall GetKeyDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
extern "C" BOOL  __stdcall GetKeyExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
extern "C" BOOL  __stdcall GetTrialDays( BYTE ModeId, DWORD* Total, DWORD* Left );
extern "C" BOOL  __stdcall GetTrialExecs( BYTE ModeId, DWORD* Total, DWORD* Left );
extern "C" BOOL  __stdcall GetExpirationDate( BYTE ModeId, WORD* Day, WORD* Month, WORD* Year );
extern "C" BOOL  __stdcall GetModeInformation( BYTE ModeID, char** ModeName, PMODE_STATUS mode_status);
extern "C" char* __stdcall GetHardwareID();
extern "C" char* __stdcall GetHardwareIDEx( BYTE ModeID );
extern "C" BOOL  __stdcall SetUserKey( char* Key, DWORD KeySize );

#endif

#define CHECK_ANY_VALID_LICENSE           \
{                                         \
    static int anyLicenseFound = 0;       \
    if (!anyLicenseFound) {               \
        {REG_CRYPT_BEGIN1}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END1}                  \
        {REG_CRYPT_BEGIN2}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END2}                  \
        {REG_CRYPT_BEGIN3}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END3}                  \
        {REG_CRYPT_BEGIN4}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END4}                  \
        {REG_CRYPT_BEGIN5}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END5}                  \
        {REG_CRYPT_BEGIN6}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END6}                  \
        {REG_CRYPT_BEGIN7}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END7}                  \
        {REG_CRYPT_BEGIN8}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END8}                  \
        {REG_CRYPT_BEGIN9}                \
        anyLicenseFound++;                \
        {REG_CRYPT_END9}                  \
        {REG_CRYPT_BEGIN10}               \
        anyLicenseFound++;                \
        {REG_CRYPT_END10}                 \
        {REG_CRYPT_BEGIN11}               \
        anyLicenseFound++;                \
        {REG_CRYPT_END11}                 \
        {REG_CRYPT_BEGIN12}               \
        anyLicenseFound++;                \
        {REG_CRYPT_END12}                 \
        {REG_CRYPT_BEGIN13}               \
        anyLicenseFound++;                \
        {REG_CRYPT_END13}                 \
        {REG_CRYPT_BEGIN14}               \
        anyLicenseFound++;                \
        {REG_CRYPT_END14}                 \
        {REG_CRYPT_BEGIN15}               \
        anyLicenseFound++;                \
        {REG_CRYPT_END15}                 \
        if (!anyLicenseFound) {           \
              printf("Warning! No any valid license found. Will throw OdError now.\n"); \
              throw OdLicenseError(eInvalidLicense, OD_T("No any valid license found."));\
        }                                 \
	}                                     \
}
// end of CHECK_ANY_VALID_LICENSE

// ODA NwInterop SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_NWINTEROP_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_NWINTEROP_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_NWINTEROP_BEGIN(x)  if (getenv("REG_CRYPT_NWINTEROP")) {
#define REG_CRYPT_NWINTEROP_END(x)    } if (!getenv("REG_CRYPT_NWINTEROP")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA Civil SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_CIVIL_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_CIVIL_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_CIVIL_BEGIN(x)  if (getenv("REG_CRYPT_CIVIL")) {
#define REG_CRYPT_CIVIL_END(x)    } if (!getenv("REG_CRYPT_CIVIL")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif
// ODA Kernel SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_CORE_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_CORE_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_CORE_BEGIN(x)  if (getenv("REG_CRYPT_CORE")) {
#define REG_CRYPT_CORE_END(x)    } if (!getenv("REG_CRYPT_CORE")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA BimRv protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_BIMRV_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_BIMRV_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_BIMRV_BEGIN(x)  if (getenv("REG_CRYPT_BIMRV")) {
#define REG_CRYPT_BIMRV_END(x)    } if (!getenv("REG_CRYPT_BIMRV")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA PRC SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_PRC_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_PRC_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_PRC_BEGIN(x)  if (getenv("REG_CRYPT_PRC")) {
#define REG_CRYPT_PRC_END(x)    } if (!getenv("REG_CRYPT_PRC")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA Mechanical SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_TM_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_TM_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_TM_BEGIN(x)  if (getenv("REG_CRYPT_TM")) {
#define REG_CRYPT_TM_END(x)    } if (!getenv("REG_CRYPT_TM")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA Publish SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_PUBLISH_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_PUBLISH_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_PUBLISH_BEGIN(x)  if (getenv("REG_CRYPT_PUBLISH")) {
#define REG_CRYPT_PUBLISH_END(x)    } if (!getenv("REG_CRYPT_PUBLISH")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA Visualize SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_VISUALIZE_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_VISUALIZE_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_VISUALIZE_BEGIN(x)  if (getenv("REG_CRYPT_VISUALIZE")) {
#define REG_CRYPT_VISUALIZE_END(x)    } if (!getenv("REG_CRYPT_VISUALIZE")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

// ODA Cloud SDK protection
#ifndef ODA_LICENSING_DEBUG
#define REG_CRYPT_CLOUD_BEGIN(x) bool _teigha_license_found_##x = false; REG_CRYPT_BEGIN2; _teigha_license_found_##x = true;
#define REG_CRYPT_CLOUD_END(x)   REG_CRYPT_END2; if (!_teigha_license_found_##x) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#else
#define REG_CRYPT_CLOUD_BEGIN(x)  if (getenv("REG_CRYPT_CLOUD"))  {
#define REG_CRYPT_CLOUD_END(x)    } if (!getenv("REG_CRYPT_CLOUD")) { throw OdLicenseError(eInvalidLicense, OD_T(#x)); }
#endif

#else // ODA_LICENSING_ENABLED

#define REG_CRYPT_BEGIN1 
#define REG_CRYPT_END1   

#define REG_CRYPT_BEGIN2 
#define REG_CRYPT_END2   

#define REG_CRYPT_BEGIN3 
#define REG_CRYPT_END3   

#define REG_CRYPT_BEGIN4 
#define REG_CRYPT_END4   

#define REG_CRYPT_BEGIN5 
#define REG_CRYPT_END5   

#define REG_CRYPT_BEGIN6 
#define REG_CRYPT_END6   

#define REG_CRYPT_BEGIN7 
#define REG_CRYPT_END7   

#define REG_CRYPT_BEGIN8 
#define REG_CRYPT_END8   

#define REG_CRYPT_BEGIN9 
#define REG_CRYPT_END9   

#define REG_CRYPT_BEGIN10 
#define REG_CRYPT_END10   

#define REG_CRYPT_BEGIN11 
#define REG_CRYPT_END11   

#define REG_CRYPT_BEGIN12 
#define REG_CRYPT_END12   

#define REG_CRYPT_BEGIN13 
#define REG_CRYPT_END13   

#define REG_CRYPT_BEGIN14 
#define REG_CRYPT_END14   

#define REG_CRYPT_BEGIN15 
#define REG_CRYPT_END15   

#define CHECK_ANY_VALID_LICENSE

#define REG_CRYPT_NWINTEROP_BEGIN(x)
#define REG_CRYPT_NWINTEROP_END(x)

#define REG_CRYPT_CIVIL_BEGIN(x)
#define REG_CRYPT_CIVIL_END(x)

#define REG_CRYPT_CORE_BEGIN(x)
#define REG_CRYPT_CORE_END(x)

#define REG_CRYPT_BIMRV_BEGIN(x)
#define REG_CRYPT_BIMRV_END(x)

#define REG_CRYPT_PRC_BEGIN(x)
#define REG_CRYPT_PRC_END(x)

#define REG_CRYPT_TM_BEGIN(x)
#define REG_CRYPT_TM_END(x)

#define REG_CRYPT_PUBLISH_BEGIN(x)
#define REG_CRYPT_PUBLISH_END(x)

#define REG_CRYPT_VISUALIZE_BEGIN(x)
#define REG_CRYPT_VISUALIZE_END(x)

#define REG_CRYPT_CLOUD_BEGIN(x)
#define REG_CRYPT_CLOUD_END(x)

#endif // ODA_LICENSING_ENABLED

#endif // OdLicense_h__
