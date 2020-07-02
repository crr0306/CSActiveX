

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jun 28 10:41:33 2016
 */
/* Compiler settings for CSActiveX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_CSActiveXLib,0xCF8862A3,0x93B7,0x4318,0xB8,0x20,0x36,0xB8,0xF3,0xC7,0x28,0x7D);


MIDL_DEFINE_GUID(IID, DIID__DCSActiveX,0x2BCAA157,0xB490,0x40EB,0xAC,0xCD,0x2C,0x30,0x97,0x5A,0x2E,0x26);


MIDL_DEFINE_GUID(IID, DIID__DCSActiveXEvents,0x44268DEF,0x072A,0x4246,0x92,0x15,0x05,0x06,0xCF,0xC9,0x42,0xEB);


MIDL_DEFINE_GUID(CLSID, CLSID_CSActiveX,0x324D4786,0xE4C9,0x4DD0,0x85,0xC7,0x15,0xCC,0x1F,0xB8,0x8C,0x12);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



