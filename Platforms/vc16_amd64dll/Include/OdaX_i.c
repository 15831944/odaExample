

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Mon Jan 18 20:14:07 2038
 */
/* Compiler settings for ..\..\..\..\..\Drawing\ActiveX\OdaX\OdaX.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_OdaX,0xB51C79A0,0xB8BC,0x4904,0x81,0x25,0x1A,0xCB,0xE8,0xB5,0x5D,0x46);


MIDL_DEFINE_GUID(IID, IID_IAcadObject,0x153A7BFD,0xAB55,0x48D4,0x81,0xC7,0x22,0x25,0x2D,0x63,0x5E,0xCE);


MIDL_DEFINE_GUID(IID, IID_IAcadDatabase,0x236374B2,0xE248,0x484D,0x91,0xD4,0xC1,0x3F,0xA7,0x26,0x64,0x5D);


MIDL_DEFINE_GUID(IID, IID_IAcadBlock,0xA1F2F50A,0xDEC5,0x4d37,0xB6,0x2D,0x39,0x34,0x91,0xDA,0xCB,0x2E);


MIDL_DEFINE_GUID(IID, IID_IAcadModelSpace,0xECE694AB,0x7306,0x4687,0xAD,0x03,0xC7,0x01,0x7A,0xE8,0xDE,0xD1);


MIDL_DEFINE_GUID(IID, IID_IAcadEntity,0xFFE64704,0xCEBD,0x4C88,0xA8,0x67,0xE7,0xC8,0x21,0xAF,0xE4,0x88);


MIDL_DEFINE_GUID(IID, IID_IAcadAcCmColor,0x6F2B458D,0x6232,0x4085,0xAA,0x60,0xBD,0x5E,0x8A,0x96,0x77,0x22);


MIDL_DEFINE_GUID(IID, IID_IAcadHyperlinks,0xBBC2B22B,0xAE20,0x47B7,0x98,0xAC,0xA7,0x51,0x14,0xC6,0x2C,0xF9);


MIDL_DEFINE_GUID(IID, IID_IAcadHyperlink,0xCFC06944,0x7FD0,0x432E,0xA4,0x30,0xB7,0x7F,0x29,0x67,0xEB,0x4C);


MIDL_DEFINE_GUID(IID, IID_IAcad3DFace,0x7FBB52D0,0x2190,0x4A17,0x9A,0x16,0xCB,0x37,0x82,0x12,0x93,0xB5);


MIDL_DEFINE_GUID(IID, IID_IAcadPolygonMesh,0xCA0C9AB2,0x0AC7,0x47C1,0x98,0x77,0xFB,0xCD,0xCA,0x68,0xF4,0x03);


MIDL_DEFINE_GUID(IID, IID_IAcad3DPolyline,0xE82F96B5,0xBA0E,0x4569,0xBD,0x8A,0x59,0x64,0x95,0x94,0x7C,0x12);


MIDL_DEFINE_GUID(IID, IID_IAcadArc,0x426D2F0F,0x4A34,0x44D9,0x82,0xD4,0x37,0xE1,0xA5,0x56,0x05,0xD2);


MIDL_DEFINE_GUID(IID, IID_IAcadAttribute,0xE6A50EDF,0xA944,0x4172,0x8B,0x2B,0x73,0x7E,0xC0,0x47,0xAD,0x0F);


MIDL_DEFINE_GUID(IID, IID_IAcad3DSolid,0x34C7D347,0xD220,0x40C8,0xA8,0x1F,0x4B,0x76,0xED,0x6E,0x57,0x51);


MIDL_DEFINE_GUID(IID, IID_IAcadRegion,0xD9F13162,0x0CFA,0x4506,0xAA,0xAD,0xD4,0x67,0x24,0x40,0x78,0x77);


MIDL_DEFINE_GUID(IID, IID_IAcadCircle,0xE23D2B17,0x487F,0x4016,0xA5,0xD4,0x6C,0x27,0x64,0x3F,0x30,0x8F);


MIDL_DEFINE_GUID(IID, IID_IAcadDimension,0x91BBC3D7,0xF48C,0x4703,0x88,0x67,0x0F,0x02,0x5F,0x95,0xDD,0x56);


MIDL_DEFINE_GUID(IID, IID_IAcadDimAligned,0x9E7FFD46,0xF51C,0x44ce,0x9C,0x06,0x01,0xEF,0xE9,0x4B,0x7E,0x04);


MIDL_DEFINE_GUID(IID, IID_IAcadDimAngular,0x559F6310,0x4DB2,0x4b61,0x8B,0x4C,0x96,0xD8,0x90,0x06,0x71,0x1B);


MIDL_DEFINE_GUID(IID, IID_IAcadDimDiametric,0x0FB4DC41,0xB309,0x41c8,0xB5,0xE7,0x23,0xB2,0x84,0xC9,0x84,0x50);


MIDL_DEFINE_GUID(IID, IID_IAcadDimRotated,0xA7BDFAD9,0xF3EA,0x4b81,0xB0,0x3F,0x24,0xFA,0x2B,0xFF,0xA3,0x2B);


MIDL_DEFINE_GUID(IID, IID_IAcadDimOrdinate,0x5A31D60B,0x3F6D,0x45c2,0x8A,0x55,0x9C,0xC7,0x06,0x26,0xD2,0x0D);


MIDL_DEFINE_GUID(IID, IID_IAcadDimRadial,0x0F29A519,0xB989,0x4e81,0xB4,0x1F,0x33,0x46,0xF3,0xBE,0x65,0xCE);


MIDL_DEFINE_GUID(IID, IID_IAcadEllipse,0x5B4B058E,0xB8AA,0x4C76,0xB6,0x52,0x76,0xAF,0x10,0x1C,0x38,0x0F);


MIDL_DEFINE_GUID(IID, IID_IAcadLeader,0xA7072E19,0x38E6,0x4320,0x90,0x45,0xB6,0x7E,0x53,0x17,0x96,0x43);


MIDL_DEFINE_GUID(IID, IID_IAcadMText,0x21E0293A,0x4AAE,0x4049,0x87,0xD3,0x33,0x6F,0x8F,0x4D,0x2D,0x45);


MIDL_DEFINE_GUID(IID, IID_IAcadPoint,0xC0CA40EE,0x60A1,0x4E76,0xAA,0xEF,0x80,0x1E,0x2C,0xCC,0x97,0xA1);


MIDL_DEFINE_GUID(IID, IID_IAcadLWPolyline,0x037572DF,0x0207,0x4B27,0xBC,0xDA,0xC1,0x63,0x05,0x4A,0x21,0xDF);


MIDL_DEFINE_GUID(IID, IID_IAcadPolyline,0x8C60FDCD,0x785A,0x40EA,0x92,0xFE,0x6D,0xC1,0xDA,0xC2,0x9E,0x7B);


MIDL_DEFINE_GUID(IID, IID_IAcadRay,0xC888FAF5,0xE377,0x4624,0xA8,0xE2,0x89,0x80,0x31,0xAB,0x58,0xBB);


MIDL_DEFINE_GUID(IID, IID_IAcadShape,0x24F52F8C,0x7BC3,0x41CC,0x93,0xE7,0xAD,0xC6,0xA0,0xF7,0x5A,0x83);


MIDL_DEFINE_GUID(IID, IID_IAcadSolid,0xA2F8C6B2,0xC9D6,0x4A48,0x9B,0x9D,0x8C,0xA3,0xE6,0x04,0x16,0x6C);


MIDL_DEFINE_GUID(IID, IID_IAcadSpline,0xB05C2404,0x6A45,0x4A57,0x80,0x75,0xF9,0x84,0x64,0xC3,0x50,0xBE);


MIDL_DEFINE_GUID(IID, IID_IAcadText,0x9CD7E38D,0x0003,0x410D,0xB6,0xDF,0xDE,0x36,0xFD,0x19,0x08,0x50);


MIDL_DEFINE_GUID(IID, IID_IAcadTolerance,0xC7ECDEAB,0x7E7A,0x40DE,0x90,0xD4,0x7D,0x00,0x9D,0x03,0x26,0x6D);


MIDL_DEFINE_GUID(IID, IID_IAcadTrace,0x128CC5FA,0xD347,0x4DCF,0xB0,0xEA,0x57,0x4B,0xAD,0xC9,0x46,0x1A);


MIDL_DEFINE_GUID(IID, IID_IAcadXline,0x703DF76F,0x5C64,0x414A,0xB2,0x71,0x45,0x20,0xE1,0x24,0x43,0x53);


MIDL_DEFINE_GUID(IID, IID_IAcadBlockReference,0xA40DEA37,0x8356,0x415A,0xB3,0xAC,0xE0,0x87,0x81,0x9C,0x63,0x01);


MIDL_DEFINE_GUID(IID, IID_IAcadHatch,0x173ED161,0x3D64,0x4EF5,0x85,0xF4,0x6A,0xAC,0xA8,0x3C,0xD3,0x82);


MIDL_DEFINE_GUID(IID, IID_IAcadLine,0x34257E2A,0x6A0C,0x4DEF,0xA7,0x40,0x65,0x45,0x5A,0xC0,0x5B,0x1D);


MIDL_DEFINE_GUID(IID, IID_IAcadPlotConfiguration,0x3648ECB5,0xD174,0x4212,0x8D,0x3F,0x27,0x3D,0xB1,0x2C,0x4E,0xAC);


MIDL_DEFINE_GUID(IID, IID_IAcadLayout,0x50D89DB1,0xE146,0x428F,0x92,0xBD,0x87,0xF4,0xEB,0x9A,0x46,0xB4);


MIDL_DEFINE_GUID(IID, IID_IAcadMInsertBlock,0xA6653F5A,0x001E,0x4125,0x8B,0xB0,0x59,0x7E,0x96,0xCD,0xE4,0x98);


MIDL_DEFINE_GUID(IID, IID_IAcadPolyfaceMesh,0x5BBFB818,0x58E4,0x466A,0xBC,0xBF,0x27,0xCF,0x88,0xE2,0xFE,0x08);


MIDL_DEFINE_GUID(IID, IID_IAcadMLine,0xC35F5577,0x83CE,0x43C7,0xB1,0x0E,0xAF,0xEF,0x9E,0x34,0x57,0x39);


MIDL_DEFINE_GUID(IID, IID_IAcadDim3PointAngular,0xB0E595FE,0x21A5,0x4c67,0xA9,0x16,0x46,0x89,0xAB,0xA3,0x7E,0x62);


MIDL_DEFINE_GUID(IID, IID_IAcadExternalReference,0xCD8AF174,0x69E8,0x4044,0x84,0x1A,0x7C,0xDC,0x34,0xFE,0x43,0xBF);


MIDL_DEFINE_GUID(IID, IID_IAcadPaperSpace,0x39377F68,0x1F53,0x4433,0x90,0xAE,0x05,0x52,0x6F,0xEA,0x4F,0xE5);


MIDL_DEFINE_GUID(IID, IID_IAcadPViewport,0x894A0DA6,0xC91F,0x458c,0xAC,0x86,0x7F,0xED,0xBF,0x35,0xCD,0x30);


MIDL_DEFINE_GUID(IID, IID_IAcadBlocks,0x98F7CE82,0x8E41,0x4D58,0xA7,0x84,0x30,0xB3,0xF3,0x3F,0x78,0x53);


MIDL_DEFINE_GUID(IID, IID_IAcadGroups,0x973585F9,0xD300,0x4BA7,0x9D,0x0F,0x6E,0xE5,0x95,0x33,0xA0,0xDC);


MIDL_DEFINE_GUID(IID, IID_IAcadGroup,0x5AF2F067,0xC79B,0x4C61,0xB0,0xEF,0x95,0x0C,0x44,0x99,0x0D,0xAA);


MIDL_DEFINE_GUID(IID, IID_IAcadDimStyles,0xDAB1760C,0x8402,0x4520,0xAD,0x32,0x93,0x96,0xAE,0xF1,0xC6,0x77);


MIDL_DEFINE_GUID(IID, IID_IAcadDimStyle,0xF1E716A4,0xFBC3,0x4893,0xA8,0xC4,0x5E,0x59,0xA5,0x37,0xD7,0xCE);


MIDL_DEFINE_GUID(IID, IID_IAcadLayers,0xEA5AF871,0xE4B9,0x4903,0x95,0x09,0xDF,0x62,0x2C,0x0D,0xC6,0xE7);


MIDL_DEFINE_GUID(IID, IID_IAcadLayer,0xA5484251,0xD4DF,0x4F32,0xA2,0x3F,0x44,0x58,0x82,0xF4,0x8F,0x1B);


MIDL_DEFINE_GUID(IID, IID_IAcadLineTypes,0x669E518F,0x46F5,0x4E21,0x84,0x47,0x7F,0x8D,0x14,0x35,0xAE,0x94);


MIDL_DEFINE_GUID(IID, IID_IAcadLineType,0x908A55EF,0x9ED0,0x4A36,0xBD,0x47,0xAD,0x08,0x18,0xAF,0x93,0x17);


MIDL_DEFINE_GUID(IID, IID_IAcadDictionaries,0xB6D57083,0x036D,0x48AB,0x8B,0xF4,0x09,0x02,0xB5,0xC8,0x8B,0xFF);


MIDL_DEFINE_GUID(IID, IID_IAcadDictionary,0x542B5C1D,0x3280,0x4154,0xB3,0xC6,0xB9,0xD5,0x5E,0x9A,0x15,0x3B);


MIDL_DEFINE_GUID(IID, IID_IAcadXRecord,0x30EDB9F1,0x6E3A,0x4428,0x9D,0xA5,0xBF,0xCD,0xFE,0xF0,0x7D,0x75);


MIDL_DEFINE_GUID(IID, IID_IAcadRegisteredApplications,0xAD2DE5AD,0x7787,0x4890,0xA8,0x18,0xBF,0x9E,0x0B,0x1D,0x4F,0x43);


MIDL_DEFINE_GUID(IID, IID_IAcadRegisteredApplication,0xCEE7E95F,0x2FDC,0x4E74,0xB8,0x7C,0x94,0x43,0xB5,0xEC,0x02,0x9D);


MIDL_DEFINE_GUID(IID, IID_IAcadTextStyles,0x2D0D8EA6,0x992A,0x4CF8,0x96,0x6F,0x3D,0xE3,0x9A,0x3B,0xF2,0x2F);


MIDL_DEFINE_GUID(IID, IID_IAcadTextStyle,0xEE473D68,0xC42F,0x4A9D,0x83,0x93,0xC3,0x97,0x5C,0x17,0xBC,0x4A);


MIDL_DEFINE_GUID(IID, IID_IAcadUCSs,0xB07B7A4C,0xA7D7,0x4116,0xBD,0x27,0xD4,0x60,0x30,0xFD,0xFE,0x1B);


MIDL_DEFINE_GUID(IID, IID_IAcadUCS,0xF5F78A02,0x09C6,0x49EB,0x81,0x2A,0x04,0xB5,0xAC,0xC4,0x6F,0x71);


MIDL_DEFINE_GUID(IID, IID_IAcadViews,0xE1673534,0x4417,0x4D0A,0x95,0xFB,0x6E,0x02,0x24,0x60,0x96,0xD6);


MIDL_DEFINE_GUID(IID, IID_IAcadView,0x13AC5968,0x504B,0x4C8D,0xBE,0xD6,0x20,0x8B,0x3A,0x56,0x2D,0x90);


MIDL_DEFINE_GUID(IID, IID_IAcadViewports,0x181E70E5,0xA50B,0x46DA,0x93,0xEE,0xBC,0xC0,0x68,0xBF,0xEB,0xEC);


MIDL_DEFINE_GUID(IID, IID_IAcadViewport,0xA9B1F951,0x1AA7,0x4C23,0x8D,0x57,0xAA,0x19,0x98,0x03,0xD3,0x81);


MIDL_DEFINE_GUID(IID, IID_IAcadLayouts,0x88CC8ED5,0x7AEF,0x459A,0xBE,0x86,0x45,0xC7,0xAF,0xD8,0xEA,0xE8);


MIDL_DEFINE_GUID(IID, IID_IAcadPlotConfigurations,0x38436519,0xBF47,0x4848,0xB6,0xB2,0xCB,0x69,0x44,0xF1,0x67,0xD3);


MIDL_DEFINE_GUID(IID, IID_IAcadDatabasePreferences,0x41A5D923,0x4AB8,0x48DD,0xB2,0x4D,0xFB,0xAF,0xE9,0x4B,0xA6,0x83);


MIDL_DEFINE_GUID(IID, IID_IAcadFileDependencies,0xDA84BC48,0xA8C9,0x45CC,0xB0,0x42,0x07,0xB8,0xC9,0x5C,0xD0,0xE4);


MIDL_DEFINE_GUID(IID, IID_IAcadFileDependency,0xAB7F29F6,0x3436,0x434F,0x8F,0x92,0x9D,0x3C,0x1E,0xD2,0xD3,0xDF);


MIDL_DEFINE_GUID(IID, IID_IAcadSummaryInfo,0x95D1CD9E,0x63E7,0x4860,0x9B,0xE2,0x8F,0x68,0x40,0x47,0xE1,0x02);


MIDL_DEFINE_GUID(IID, IID_IAcadIdPair,0x1033C7F9,0x2D77,0x449D,0x8E,0xA2,0xBD,0x61,0xDA,0x1C,0x9B,0xCB);


MIDL_DEFINE_GUID(IID, IID_IAcadAttributeReference,0x090EF3DE,0xE74D,0x44c0,0x8B,0x8B,0x89,0xD0,0xA7,0x9F,0xBE,0x52);


MIDL_DEFINE_GUID(IID, IID_IAcadObjectEvents,0x5195F20D,0x9F99,0x43C4,0x9A,0x6A,0x19,0x83,0x55,0xA9,0x20,0xED);


MIDL_DEFINE_GUID(IID, IID_IAcadRasterImage,0x1334DA0A,0xAFF4,0x4E2A,0x85,0x40,0x53,0x13,0xAA,0x8A,0x47,0xE4);


MIDL_DEFINE_GUID(IID, IID_IAcadSortentsTable,0x04C4F44E,0x99B7,0x490B,0x88,0x23,0xF6,0x8E,0xD4,0x5A,0x48,0x7B);


MIDL_DEFINE_GUID(IID, IID_IAcadTableStyle,0x65AFF703,0x323D,0x4562,0xB2,0x35,0xCC,0x43,0x96,0x6A,0x79,0x22);


MIDL_DEFINE_GUID(IID, IID_IAcadOle,0x5A90AA1A,0x8525,0x49B7,0x9F,0x44,0x62,0xE6,0xA9,0x58,0xDE,0x82);


MIDL_DEFINE_GUID(IID, IID_IAcadTable,0x62AE6596,0x74E9,0x4fc1,0x9F,0x31,0xCB,0x95,0x67,0xE5,0x50,0xF9);


MIDL_DEFINE_GUID(IID, IID_IAcadDynamicBlockReferenceProperty,0x671D7077,0x2C99,0x4D21,0xA5,0xD3,0xA5,0x00,0x1F,0x1B,0x8F,0x12);


MIDL_DEFINE_GUID(IID, IID_IAcadDimRadialLarge,0xF2B4D571,0xC206,0x4e19,0xB1,0xC0,0x55,0xC9,0x5B,0xED,0x66,0x9C);


MIDL_DEFINE_GUID(IID, IID_IAcadDimArcLength,0x2E0ED9F5,0x20D4,0x45d5,0x92,0x41,0x93,0xE3,0xB1,0xBF,0x56,0xD3);


MIDL_DEFINE_GUID(IID, IID_IAcadSection,0x3BF84F02,0xEA6E,0x4B36,0x87,0xD7,0xF9,0x07,0x0D,0xDA,0x96,0x57);


MIDL_DEFINE_GUID(IID, IID_IAcadSectionSettings,0xBD245AB1,0xA6D8,0x4F1F,0x9D,0x6E,0xED,0x76,0xAB,0x36,0x15,0xF9);


MIDL_DEFINE_GUID(IID, IID_IAcadSectionTypeSettings,0x2F52131D,0x45D6,0x4302,0x99,0x3D,0xAD,0xA4,0x13,0x44,0x3F,0xD7);


MIDL_DEFINE_GUID(IID, IID_IAcadSurface,0xDB31BDE0,0x6DD6,0x4FDF,0xA2,0x89,0x21,0x4E,0xEA,0x6C,0x00,0x72);


MIDL_DEFINE_GUID(IID, IID_IAcadPlaneSurface,0xFFCCA3F9,0x8BB7,0x4693,0xB7,0xF7,0x07,0xEF,0xDF,0x4D,0xE8,0xA9);


MIDL_DEFINE_GUID(IID, IID_IAcadExtrudedSurface,0x91D470C0,0xCAB6,0x49F8,0xB1,0x3B,0x83,0xD5,0x35,0x27,0x93,0x3A);


MIDL_DEFINE_GUID(IID, IID_IAcadRevolvedSurface,0x2AA6DCC2,0xC242,0x49CB,0xA5,0x76,0x54,0x5E,0x4F,0x50,0x07,0x22);


MIDL_DEFINE_GUID(IID, IID_IAcadSweptSurface,0xA1E46554,0xB62E,0x4CEB,0xA9,0xB8,0x8C,0x9B,0xC7,0xE8,0x25,0x2D);


MIDL_DEFINE_GUID(IID, IID_IAcadLoftedSurface,0x9A580AC7,0xFD1D,0x4D94,0xA6,0x68,0xB0,0x07,0x45,0xFD,0xB1,0x53);


MIDL_DEFINE_GUID(IID, IID_IAcadHelix,0x7480DD11,0xB890,0x41B3,0xBD,0x1A,0x56,0x2D,0x51,0x90,0xDD,0xC2);


MIDL_DEFINE_GUID(IID, IID_IAcadSectionManager,0x47495992,0x2633,0x4FA4,0x8B,0x0F,0x21,0x3F,0x0C,0x2D,0x20,0xA5);


MIDL_DEFINE_GUID(IID, IID_IAcadMaterials,0x6B7DDA98,0xB483,0x40F8,0x90,0x5C,0x2D,0xF1,0x0E,0x93,0x60,0x21);


MIDL_DEFINE_GUID(IID, IID_IAcadMaterial,0x4D24EA66,0xA2B3,0x4129,0x83,0x67,0x81,0xD9,0x3B,0x44,0xBE,0x07);


MIDL_DEFINE_GUID(IID, IID_IAcadUnderlay,0xD076BB70,0x1090,0x4438,0x99,0x22,0x3F,0xD9,0x1B,0xA4,0xBB,0x4A);


MIDL_DEFINE_GUID(IID, IID_IAcadMLeader,0xA2F0013E,0xACE4,0x41c5,0x90,0x15,0x37,0x58,0x76,0x63,0xDD,0x30);


MIDL_DEFINE_GUID(IID, IID_IAcadMLeaderStyle,0x9E7B3D0B,0x36F8,0x444E,0x89,0xA7,0x32,0x4B,0x3E,0x87,0x7B,0xDC);


MIDL_DEFINE_GUID(IID, IID_IAcadSubEntity,0x70991FC5,0xF814,0x45a8,0xBB,0x15,0xBC,0x70,0x3A,0xB5,0xBF,0x63);


MIDL_DEFINE_GUID(IID, IID_IAcadMLeaderLeader,0xD0AC8EBF,0x1F76,0x43ef,0x97,0x48,0xD7,0xEE,0x52,0xAA,0xBE,0x25);


MIDL_DEFINE_GUID(IID, IID_IAcadDwfUnderlay,0xA095BF5E,0xB1A5,0x413f,0xA6,0xEA,0x6E,0x05,0x7C,0x63,0xCA,0x59);


MIDL_DEFINE_GUID(IID, IID_IAcadSubEntSolidFace,0x9D76FD22,0xF78B,0x40b5,0x94,0xA3,0xB8,0xC0,0xAB,0x17,0xA1,0xE2);


MIDL_DEFINE_GUID(IID, IID_IAcadSubEntSolidEdge,0xEA82FD79,0x6DE0,0x445e,0xAB,0xFB,0x54,0x1E,0x52,0xC9,0x1B,0xB5);


MIDL_DEFINE_GUID(IID, IID_IAcadSubEntSolidVertex,0x45CF6C7D,0x7191,0x420a,0x98,0x81,0x09,0x04,0x2D,0xD6,0x18,0xED);


MIDL_DEFINE_GUID(IID, IID_IAcadWipeout,0x977345B6,0xA313,0x4f2e,0xA4,0xEE,0x1C,0x2B,0xB3,0xC2,0xFE,0x0E);


MIDL_DEFINE_GUID(IID, IID_IOdaLineType,0xA3D0151B,0xA26A,0x4803,0xBF,0x89,0x37,0xC5,0x25,0xD0,0x58,0xEE);


MIDL_DEFINE_GUID(IID, IID_IOdaBlock,0xD288082B,0xEC5B,0x4B26,0xA9,0x83,0x3A,0xAD,0x6F,0x98,0x0D,0x6C);


MIDL_DEFINE_GUID(IID, IID_IOdaMLineStyles,0xEAB07C99,0xABCA,0x4880,0x9B,0x1C,0x4F,0xD1,0x3F,0xC3,0xDE,0x3A);


MIDL_DEFINE_GUID(IID, IID_IOdaMLineStyle,0x3A1DC1C0,0xD49D,0x4DC6,0xA9,0x44,0xA1,0x58,0x22,0x7B,0xFF,0x03);


MIDL_DEFINE_GUID(IID, IID_IOdaRasterImage,0xD2F02FB4,0x2990,0x4D58,0x80,0xDC,0x9B,0x75,0x6F,0xC3,0x6F,0xD0);


MIDL_DEFINE_GUID(IID, IID_IOdaOle,0x39614E96,0xFFD9,0x42EA,0x99,0xF0,0xFD,0x7D,0xC4,0x98,0xD9,0xB6);


MIDL_DEFINE_GUID(IID, IID_IOdaLight,0x7BB45F85,0x7771,0x4B5C,0x9D,0x8E,0xEA,0x0E,0x79,0x22,0x84,0x61);


MIDL_DEFINE_GUID(IID, IID_IOdaCamera,0x416400A5,0x8C83,0x49A6,0x9E,0xD3,0xEF,0xF0,0x32,0x2F,0xCF,0xA9);


MIDL_DEFINE_GUID(IID, IID_IOPMPropertyExpander,0xE3CD32AF,0x3A8F,0x49D9,0x9D,0xC5,0x52,0x7E,0x91,0x31,0x89,0x93);


MIDL_DEFINE_GUID(IID, IID_IOPMPropertyExtension,0x9850E632,0x7168,0x452B,0xA2,0x62,0xFC,0x3D,0xCB,0x31,0x38,0x51);


MIDL_DEFINE_GUID(IID, IID_IOdaSpline,0x4EE8DF6D,0x534E,0x4819,0x87,0xAE,0x51,0xFA,0x44,0x8B,0xCD,0x6A);


MIDL_DEFINE_GUID(IID, IID_IAcadHatch2,0x8CF4A451,0xA8A4,0x40C1,0x9E,0xCC,0x26,0xEF,0x09,0x70,0x42,0xD6);


MIDL_DEFINE_GUID(IID, IID_IAcadSectionTypeSettings2,0x5EB52F66,0x908B,0x48c5,0x87,0xD9,0x01,0x80,0xE8,0x1B,0xF6,0x4F);


MIDL_DEFINE_GUID(IID, IID_IOdaPolyfaceMesh,0x88F4A330,0x80BA,0x4593,0x97,0x5B,0xBB,0x2A,0xCD,0xC4,0xE4,0x65);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLine,0x47EFB604,0xEC2A,0x4B93,0x95,0xF4,0x38,0xFD,0x44,0x67,0x7F,0x84);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadObject,0xB4968C4D,0x408D,0x4C54,0x98,0xA5,0xA8,0xA1,0xB1,0xD4,0xB6,0x09);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadEntity,0x324D5B63,0xBF9F,0x4646,0x9D,0x4C,0xC2,0xD7,0x3C,0x54,0x9D,0x8F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimension,0xE666AE52,0x54F6,0x4375,0xBB,0x17,0x87,0x1B,0x61,0x26,0xF6,0xC8);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimRotated,0xE3454AE0,0xF53E,0x4947,0xB4,0xF1,0x5E,0xDD,0xB2,0xB1,0xE9,0x0D);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMText,0xECACECBF,0x1726,0x4DC8,0x8C,0xB6,0x65,0x67,0x16,0x7C,0x51,0xA0);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDatabase,0xDE85B90C,0xB97B,0x49D3,0xBD,0x11,0x5D,0xB4,0xD8,0x9A,0x81,0xF2);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadViewport,0x94476DC0,0xFAD1,0x45A0,0xA4,0x5D,0x4F,0x1E,0xB2,0x57,0x19,0x78);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadViewports,0x95D7B220,0x423E,0x45B7,0x8F,0xBE,0x4F,0x97,0x6C,0x1A,0x4C,0x2C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadText,0x3FDEC519,0x2AC8,0x42C8,0x99,0x9B,0xBA,0xF4,0xF5,0x0F,0x92,0x2C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadTrace,0x9F47494A,0x4B8F,0x445D,0x8B,0x02,0x01,0xC9,0x64,0x3F,0xB0,0x9D);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPolyline,0xC70DB615,0xAC0C,0x47BA,0xB7,0x67,0x76,0xCF,0x94,0x8B,0xF2,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLineTypes,0x2DDBE2B4,0x7F1B,0x451A,0xA3,0xB9,0xA2,0x2C,0xB4,0x4E,0xD9,0xE1);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaLineType,0x5DB2252E,0x74EC,0x4AE3,0x93,0x3D,0x13,0xEA,0xF7,0x69,0x3C,0xE1);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadBlocks,0xB384A7DA,0x7825,0x4CED,0xA7,0x64,0x30,0xC9,0xB2,0x84,0x1B,0x46);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaBlock,0xAF969410,0xDDCE,0x47D1,0x94,0xE8,0xFA,0xE2,0x84,0x9E,0x4F,0x98);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadBlock,0xF8252E86,0x9DC5,0x49B2,0xAE,0x5B,0xFF,0x07,0xB0,0x01,0x6D,0xF7);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadEllipse,0x455DE2BC,0x392F,0x4737,0xA1,0xE0,0x7F,0x93,0x02,0xCE,0xC9,0xCC);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadCircle,0x760F15C8,0xB240,0x4B0A,0x85,0x30,0x09,0xCA,0xCC,0x47,0x74,0x87);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPoint,0x14EB8763,0xAABA,0x46CD,0xB6,0xF7,0x07,0x10,0x34,0xF3,0xD2,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_Acad3DFace,0x31E3726A,0x0CDF,0x4BC3,0xB7,0x52,0x64,0xEF,0x1C,0x40,0x8D,0xC6);


MIDL_DEFINE_GUID(CLSID, CLSID_Acad3DPolyline,0xCCF1B977,0xE10A,0x4475,0x8C,0xDC,0x98,0x67,0xF7,0xAB,0xA6,0xCC);


MIDL_DEFINE_GUID(CLSID, CLSID_Acad3DSolid,0x021A2DCA,0xFBAA,0x4945,0x8E,0x4B,0x16,0xB2,0xF0,0xF0,0x0C,0x51);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadArc,0xA857DD0B,0x0C50,0x4C93,0x81,0x8F,0x05,0xF9,0x7F,0x4C,0x2F,0x88);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadAttribute,0x8E93EBD5,0xE061,0x41D8,0x93,0x87,0x3F,0xC1,0x05,0x35,0xF7,0x11);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLeader,0x182F38CB,0x1EDE,0x4372,0x89,0x12,0xB2,0x3F,0xFB,0xC7,0x51,0x3F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMLeader,0x7B994469,0x0E2B,0x4E73,0x98,0x3E,0x1D,0xD8,0x4C,0xC2,0x9B,0xBD);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMLeaderStyle,0xABBD2AD2,0x5E03,0x44B2,0x8C,0x27,0x7E,0xD3,0x64,0x5F,0x62,0x2F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadTolerance,0x7FDA25CA,0xFF59,0x4ACE,0xB4,0x5A,0xE5,0x73,0xC6,0xAE,0xFE,0x9B);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadBlockReference,0xDA3D9A40,0xC234,0x43E3,0x8B,0x2E,0xFE,0xAA,0x1C,0x78,0x25,0xFC);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDim3PointAngular,0x8F6E385E,0x9412,0x4C06,0x8B,0x46,0x61,0xF8,0xC6,0x07,0x69,0x1F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimAligned,0x70BA9E31,0xDEDE,0x4992,0xB2,0xEC,0xBB,0x00,0x4F,0x18,0x84,0x42);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadShape,0x785354FB,0xA6D6,0x490D,0x85,0x1F,0xA0,0xD7,0x12,0x56,0x06,0x29);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSolid,0x6FF2A5BC,0x0A5B,0x4188,0xB9,0xF3,0xFE,0xCA,0x6B,0xD3,0x25,0x44);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSpline,0xBECA0155,0x0B5C,0x4413,0x8D,0x31,0xAB,0xD2,0xD3,0xAE,0xF0,0xFA);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimAngular,0xD32E7B7C,0x3E81,0x4AA6,0xBF,0x20,0xD4,0x28,0x89,0xE0,0xE8,0x1E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimDiametric,0x2DD045DD,0x4585,0x403D,0x9B,0xFA,0x6E,0xDD,0x85,0x30,0xDA,0x38);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimOrdinate,0x0184A994,0xC101,0x406E,0x8F,0x3F,0x45,0x4C,0xA8,0xB6,0xAF,0xE3);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimRadial,0x0E5CCC90,0x0886,0x4AAA,0xAD,0x9B,0x59,0xA6,0xF3,0x6B,0x60,0x5F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimRadialLarge,0xF5DF99C2,0x3002,0x4CFD,0x9B,0x64,0x68,0x1F,0x7B,0xF1,0x46,0x4C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimArcLength,0xDF09ADED,0x215C,0x407F,0xAE,0xBA,0x9E,0xEF,0xBB,0x91,0x38,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadXRecord,0xF251EBC7,0xA8E4,0x4959,0xA1,0x43,0xC2,0xA0,0x2E,0x15,0x37,0x30);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadXline,0xFBFAF06B,0x3F69,0x4C18,0xBB,0x72,0x4D,0x58,0x65,0xE4,0x1F,0x37);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadRay,0x6D2606B6,0x43A2,0x43D5,0x82,0xAA,0x74,0xA0,0x10,0x0A,0x2C,0xBE);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimStyle,0xDE5A2136,0xC60F,0x46C5,0xA7,0xF6,0x76,0x64,0xE3,0x0E,0xD5,0x0F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadExternalReference,0xAB17A8DD,0xB957,0x4DBD,0xAF,0x2D,0x18,0xC5,0x06,0xD5,0xCD,0xF3);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMInsertBlock,0x15BB7C16,0x7C18,0x4578,0x80,0x4A,0x0A,0x7D,0x97,0x86,0x3A,0x28);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDimStyles,0xABB3BCC9,0x9030,0x45C0,0x9E,0x09,0x8B,0x85,0xF3,0xEA,0x41,0x22);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadUCS,0xCB2AB03E,0xAC3E,0x45BA,0x8E,0x97,0x4D,0xE1,0xDB,0xD0,0x90,0xEF);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadUCSs,0x9B5BA3E0,0xE92C,0x4DE8,0x89,0x46,0x2B,0x9F,0xED,0xFA,0xF5,0xED);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadView,0xC9A3FA2A,0xD752,0x4DEF,0x85,0x7F,0x91,0x4D,0xD4,0xD2,0xB9,0x8C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadViews,0xD2937F20,0x10F9,0x401A,0x98,0x0F,0x01,0x15,0xF3,0xC3,0x6B,0x7E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadGroup,0x1D436E1D,0x3A54,0x499C,0x82,0xD7,0xDD,0xF7,0xB6,0x5F,0xE3,0x7A);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadGroups,0x4262526D,0x4C72,0x4074,0xB8,0x4E,0x96,0x70,0xAA,0xB8,0xEC,0xFF);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDictionaries,0x1DC7AD0F,0xAF0B,0x47EC,0x87,0xA1,0x74,0xD9,0xA0,0x8D,0x1C,0x94);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDictionary,0x7708F5DC,0xD693,0x4AB9,0xB5,0xD8,0xD3,0x07,0x79,0xE9,0xE5,0x4A);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLayouts,0x0E20E67A,0x007F,0x4D3F,0xBF,0xB1,0xF6,0xDF,0xB5,0xA5,0xE7,0x42);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLayout,0xA582F039,0xC098,0x433E,0xBB,0xF7,0x13,0xA9,0xFE,0xC3,0xF3,0x38);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadTextStyle,0x9F516BA8,0x0803,0x42A6,0x94,0x8A,0xF9,0x38,0x12,0x48,0xBD,0x3E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadTextStyles,0x71584E5C,0x4879,0x4CC4,0x8D,0x51,0xA6,0x77,0xD9,0x92,0xB1,0xAB);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadHatch,0x0D976CEC,0xC2E8,0x497B,0xBB,0x80,0x5A,0xC5,0x80,0x96,0xFE,0x4F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMLine,0xF30DAC25,0xF8DB,0x4053,0x8D,0xC8,0x7A,0xC9,0x15,0x7C,0x40,0x6D);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPolygonMesh,0xEC0C193E,0x5A57,0x4D66,0x94,0x9D,0xEC,0xB2,0xD4,0x6C,0x81,0x62);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPolyfaceMesh,0x29C143D7,0x2A81,0x43A7,0x8C,0x20,0x32,0x8B,0xAE,0xEA,0x20,0x60);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPlotConfiguration,0xECE76D52,0xE70A,0x4E6E,0x99,0x3A,0x45,0x7A,0x6A,0xB2,0xB9,0xF5);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPlotConfigurations,0xC85B9212,0xA328,0x4D73,0x83,0x45,0x14,0x28,0x50,0x63,0x5C,0xEC);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaRasterImage,0x2C004524,0x803F,0x4937,0x9D,0xC5,0x61,0xC2,0xF7,0xC9,0x79,0x07);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadRasterImage,0x24A0D4DB,0x19BA,0x4256,0x90,0x63,0xA1,0xF5,0xC1,0xB2,0xB7,0x09);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadRegion,0x8DD5F421,0x38A3,0x4276,0x88,0x37,0x91,0xEC,0x4D,0x8B,0xAF,0x42);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadRegisteredApplication,0xC2BCC52E,0x23A2,0x43A0,0xB0,0xBE,0x27,0x04,0x62,0x6E,0x6E,0xDE);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadRegisteredApplications,0x95F178E1,0xE469,0x4478,0x98,0x3D,0xB6,0x08,0x66,0x2B,0xB5,0xB1);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPViewport,0xBB3C60F0,0x099C,0x4779,0xBE,0xDC,0x63,0x02,0x01,0x12,0xA3,0xA5);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDatabasePreferences,0xF1E236C0,0xF2BF,0x412D,0x88,0xA0,0x4C,0x3D,0xE7,0x89,0x5D,0xB1);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadHyperlink,0xD7E1C021,0xEBF4,0x4D03,0xAD,0x01,0x45,0x9D,0xBA,0xF2,0xEA,0x38);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadHyperlinks,0x3528026A,0x0B87,0x4A5B,0x91,0x09,0x8C,0xE6,0x17,0xAB,0x94,0x76);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLayer,0x2DEC0E4C,0xE666,0x4AB5,0xAC,0xE8,0xFD,0x0D,0xD2,0x74,0xC8,0xB7);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLayers,0xF4B78DE9,0x8793,0x401B,0xBD,0xC8,0x0F,0x4C,0xCF,0x42,0x76,0xFB);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLWPolyline,0x6BE22C0D,0x01CD,0x439B,0xAF,0x86,0x82,0xCC,0x6A,0xE7,0xB5,0x54);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPaperSpace,0xB9F90258,0x5B03,0x4989,0x8C,0xD9,0xAE,0xB5,0x23,0x38,0x01,0x21);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadModelSpace,0xC840843E,0x6A38,0x47D8,0x89,0xA3,0x0A,0xEC,0xB7,0xAE,0x24,0x2F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadAttributeReference,0x085FB4D8,0xBFE0,0x4E70,0x82,0x09,0xC7,0x6B,0xEA,0x3D,0x49,0xC1);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadAcCmColor,0xA77FF1A8,0x7B7D,0x4CAA,0xAF,0x62,0x82,0x91,0xEE,0x98,0x75,0xAB);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSummaryInfo,0x52F1616B,0xCE3D,0x4673,0x8B,0xEE,0x61,0x03,0x46,0xEA,0x82,0xB6);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadFileDependencies,0x7FDDE507,0xBCBF,0x44B2,0x99,0x9D,0xB8,0x97,0x22,0x7F,0x70,0x7D);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadFileDependency,0xD86353C0,0xD583,0x4CF4,0xA0,0x8A,0x4C,0x76,0x6E,0x15,0xD4,0xA4);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadTable,0x60C9F875,0xFC93,0x4DD5,0x80,0x31,0xB2,0xBF,0x7C,0xB6,0x4D,0x97);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaOle,0x86438079,0xB8FA,0x41E0,0xB4,0x89,0x42,0x5D,0xBF,0xE4,0xCF,0x85);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadTableStyle,0x7BD53B53,0xA33C,0x448D,0xAF,0xE8,0x5B,0xF1,0x63,0x89,0xB1,0xDB);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSortentsTable,0x43F79F31,0xE0E9,0x4FDF,0x80,0xB9,0xA4,0x3D,0x0E,0x6D,0x6B,0x65);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaMLineStyles,0x9CEFD0F2,0xA059,0x4ED3,0xB6,0x33,0xA3,0x72,0x88,0x1E,0xBE,0x72);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaMLineStyle,0x5C9BA7B5,0xB1EF,0x4A01,0x9E,0xA4,0x8C,0xFC,0x81,0x6B,0xEA,0x11);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDynamicBlockReferenceProperty,0xBB08E864,0x3642,0x4F0C,0xAA,0x3C,0xE4,0x0B,0x5A,0xC4,0x59,0xE7);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSection,0x2360306D,0x951A,0x435E,0xB7,0x5C,0x1E,0x95,0x49,0xD6,0xC5,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSurface,0x96E267E3,0x7557,0x471B,0xBF,0xCE,0x5A,0x85,0xB4,0x95,0x93,0x69);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadLoftedSurface,0xE70CB939,0x8560,0x43E4,0x93,0xF5,0xF6,0xDA,0x2F,0x41,0x0A,0x7B);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSweptSurface,0x4819DECD,0xD02C,0x4554,0xA8,0x67,0x96,0x3F,0x68,0x83,0x75,0x2B);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadRevolvedSurface,0xBA4F7475,0x5879,0x41B3,0xBE,0x7A,0x3B,0xB9,0xA3,0xA3,0x16,0x6C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadExtrudedSurface,0xF03335D7,0xC485,0x482C,0x9F,0xA3,0x02,0xDA,0x8A,0x5C,0xE9,0x6F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPlaneSurface,0x17997E94,0xFFAE,0x4C98,0x97,0x5F,0x74,0x9C,0xC0,0x86,0xEB,0x8D);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadHelix,0x118D8DC6,0x7972,0x4DCA,0xB7,0x00,0xAD,0x34,0x0F,0xAA,0xA1,0x5D);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSectionSettings,0xDB10B321,0x2CA9,0x415A,0xB5,0x20,0xBF,0x19,0x0A,0xA5,0xA1,0xFF);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSectionTypeSettings,0x8BCBB13C,0xBC7F,0x480C,0xB1,0x1E,0xE8,0x4F,0x56,0xE6,0xFE,0xBD);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSectionManager,0xEC944318,0x143D,0x4453,0x80,0xA5,0x22,0x94,0xD4,0x35,0xCB,0x1F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMaterial,0xC1BDB028,0x6BD2,0x4AA9,0x97,0xA3,0xE5,0x9C,0x8E,0x9F,0x7C,0xFD);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMaterials,0x61749C8F,0x2A0A,0x4740,0x9E,0xE7,0x9C,0xD5,0xA0,0xA5,0xB6,0xA4);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDwfUnderlay,0xCF2DD2AF,0x5A4C,0x401F,0x8E,0x27,0x36,0xD7,0xA4,0x63,0xF5,0xBE);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadDgnUnderlay,0xDF14032D,0x91B0,0x4A77,0xBD,0x20,0x38,0xD5,0x8E,0xF1,0x61,0x3E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadPdfUnderlay,0x53CA759F,0x9FF0,0x4FE3,0xBA,0x6E,0x7C,0xD7,0x94,0x1F,0xE0,0x55);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadMLeaderLeader,0x04D83CF8,0xF1BC,0x4DAD,0xB8,0x81,0x07,0xDE,0xED,0x70,0x8C,0x12);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSubEntity,0xF422DEA4,0x1AB7,0x4665,0xAB,0x29,0xA3,0xD2,0x52,0xD3,0x5A,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSubEntSolidFace,0xFCE0E55C,0x3A6C,0x4AF3,0xBD,0xCF,0x5F,0x7B,0x91,0x87,0x52,0xD2);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSubEntSolidEdge,0xEA00DF4B,0xCFC3,0x492E,0x83,0x60,0xD8,0xE2,0xE8,0xE8,0x5D,0xF0);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadSubEntSolidVertex,0x112B3967,0xF1D2,0x45EB,0xA8,0xB7,0x62,0x0E,0x89,0xB5,0xAD,0x9F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadWipeout,0x53CD122A,0x4E46,0x4F0D,0x83,0xF4,0xF4,0x86,0xA7,0xFF,0x6C,0xA6);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaLight,0xA11BE472,0x1E0F,0x4184,0xB6,0xCF,0x62,0x49,0x31,0x8F,0x1E,0x05);


MIDL_DEFINE_GUID(CLSID, CLSID_OdaCamera,0x7DE169D1,0xA2A6,0x47AD,0x8C,0x59,0x30,0x04,0x1A,0xFC,0x99,0x34);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif


