// CSActiveX.cpp : Implementation of CCSActiveXApp and DLL registration.

#include "stdafx.h"
#include "CSActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCSActiveXApp theApp;

const GUID CDECL _tlid = { 0xCF8862A3, 0x93B7, 0x4318, { 0xB8, 0x20, 0x36, 0xB8, 0xF3, 0xC7, 0x28, 0x7D } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CCSActiveXApp::InitInstance - DLL initialization

BOOL CCSActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CCSActiveXApp::ExitInstance - DLL termination

int CCSActiveXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
