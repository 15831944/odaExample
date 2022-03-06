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

#ifndef __OD_EXPIRATIONDATE__H__
#define __OD_EXPIRATIONDATE__H__

// Conditionally set an expiration date in the registry, 
// and disable toolkit 30 days after it was first used.
#ifdef EXPIRATION_DATE
namespace OdExpirationDate
{

#include <time.h>

#define THIRTY_DAY_KEYSTASH "CLSID\\{a5ade793-52d4-4b4d-9a46-54df5aa4db36}\\ProgID"
#define BURNED "burned"
#ifndef EXPIRATION_KEYSTASH
  #define EXPIRATION_KEYSTASH THIRTY_DAY_KEYSTASH
#endif

inline LONG setStamp(BOOL burn)
{
  char buffer[30];
  if (burn)
  {
    strcpy(buffer, BURNED);
  }
  else
  {
    time_t timer;
    time(&timer);
    tm * pTime = localtime(&timer);
    sprintf(buffer, "%d %d %d", pTime->tm_year, pTime->tm_mon, pTime->tm_mday);
  }

  HKEY key;
  DWORD disp;
  LONG retValue;
  retValue = RegCreateKeyExA(HKEY_CLASSES_ROOT,
                            EXPIRATION_KEYSTASH,         
                            0,
                            "",
                            0, 
                            KEY_ALL_ACCESS, 
                            NULL, 
                            &key, 
                            &disp);
  if (retValue == eOk)
  {
    retValue = RegSetValueExA(key,
                      "",         
                      0,
                      REG_SZ,
                      (const unsigned char*)buffer,
                      strlen(buffer) + 1);
    RegCloseKey(key);
  }
  return retValue;
}

inline int validate()
{
  HKEY hk = NULL;
  LONG l;
  l = RegOpenKeyExA(HKEY_CLASSES_ROOT, EXPIRATION_KEYSTASH, 0, KEY_QUERY_VALUE, &hk);
  if (l != eOk) 
  {
    if(!setStamp(FALSE))
    {
      return FALSE; // Should never happen.
    }
    return TRUE; // First use of DD.
  }
  DWORD lpType, size = 30; //sizeof(DWORD),value;
  char buffer[30];
  l = RegQueryValueExA(
    hk,               //HKEY      handle of key to query
    "",               //LPTSTR    address of name of value to query
    NULL,             //LPDWORD   reserved
    &lpType,          //LPDWORD   address of buffer for value type
    (LPBYTE)buffer,   //&value,//AutoCADpath,//(LPBYTE)path ,    //LPBYTE    address of data buffer
    &size);           //LPDWORD   address of data buffer size

  if(l != eOk)
  {
    return FALSE; // Should never happen.
  }
  RegCloseKey(hk);

  if (strcmp(buffer, BURNED) == 0)
  {
    return FALSE;
  }

  int year = 0, month = 0, day = 0;
  sscanf(buffer, "%d %d %d", &year, &month, &day);

  time_t timer;
  time(&timer);
  tm * pTime = localtime(&timer);

  int used = (pTime->tm_year - year) * 365
      + (pTime->tm_mon - month) * 30
      + (pTime->tm_mday - day);

  return used <= 30;
}

}       // namespace OdExpirationDate

#define VERIFY_EXPIRATION_DATE()                                         \
  if ( !OdExpirationDate::validate() )                                   \
  {                                                                      \
    OdExpirationDate::setStamp(TRUE);                                    \
    OdString msg(EXPIRATION_PRODUCT_NAME);                               \
    msg += L" Evaluation Expired";                                       \
    MessageBox(NULL, msg, EXPIRATION_PRODUCT_NAME, MB_OK | MB_ICONSTOP); \
    exit(0);                                                             \
  }

#else

#define VERIFY_EXPIRATION_DATE()

#endif  // EXPIRATION_DATE


#endif // __OD_EXPIRATIONDATE__H__
