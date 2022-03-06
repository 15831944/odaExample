

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Mon Jan 18 20:14:07 2038
 */
/* Compiler settings for ..\..\..\..\..\..\Drawing\Examples\ActiveX\ViewX\ViewX.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0626 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IOdaView,0x8C1328BF,0xAEE8,0x401F,0x96,0x5A,0xA8,0x0D,0x68,0xA5,0x91,0x74);


MIDL_DEFINE_GUID(IID, IID_IOdaDevice,0xFDFF0AAA,0x6631,0x4BDB,0x8A,0x89,0x77,0x99,0xB3,0x3F,0x3C,0x6B);


MIDL_DEFINE_GUID(IID, IID_IOdaViewer,0x3B08F722,0xE57E,0x4D0B,0xBC,0xF5,0x13,0x61,0xD1,0x2C,0xE8,0x17);


MIDL_DEFINE_GUID(IID, LIBID_VIEWXLib,0x889FF987,0x790F,0x4C87,0xBD,0xC6,0xE2,0x8C,0xAD,0x49,0xCD,0x67);


MIDL_DEFINE_GUID(IID, DIID__IOdaViewEvents,0x9BB70937,0x3D24,0x4706,0x87,0xCB,0x5E,0x72,0x0E,0xEF,0x1D,0x28);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaViewer,0xCA7B6EF1,0xCF63,0x4EE1,0xA4,0x45,0x7F,0xBF,0x6E,0x8E,0x18,0xB1);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaDevice,0xF95D4331,0x3F13,0x4ECF,0x9D,0xC0,0x71,0x5C,0x2D,0x50,0x6B,0x4B);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaView,0x10454FA3,0x4557,0x463B,0x9D,0xCF,0x39,0xDC,0x66,0x3C,0x07,0x6C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



