

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Mon Jan 18 20:14:07 2038
 */
/* Compiler settings for ..\..\..\..\..\..\Drawing\Examples\win\ExCustObjCOM\ExCustObjCOM.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_ExCustObjCOMLib,0x6F10A128,0xFA75,0x4A88,0x82,0x3A,0x37,0xFB,0x0F,0x16,0xA4,0x1D);


MIDL_DEFINE_GUID(IID, IID_IExCustEntityWrapper,0xBFF2426C,0xA401,0x45D2,0xA5,0xCA,0x63,0xC7,0x56,0xB4,0x98,0x3E);


MIDL_DEFINE_GUID(CLSID, CLSID_ExCustEntityWrapper,0x8D0E4AE8,0xD8B1,0x4C26,0x92,0xE9,0x26,0x4D,0x1C,0x9D,0x5C,0x79);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



