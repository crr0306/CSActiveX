#pragma once
#include <ObjSafe.h>
// CSActiveXCtrl.h : Declaration of the CCSActiveXCtrl ActiveX Control class.


// CCSActiveXCtrl : See CSActiveXCtrl.cpp for implementation.

class CCSActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCSActiveXCtrl)

// Constructor
public:
	CCSActiveXCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CCSActiveXCtrl();

	DECLARE_OLECREATE_EX(CCSActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCSActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCSActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCSActiveXCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

//接口安全性
	// Interface map for IObjectSafety
	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety);
		STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) (
														REFIID riid,
														DWORD __RPC_FAR *pdwSupportedOptions,
														DWORD __RPC_FAR *pdwEnabledOptions
														);
		STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) (
														REFIID riid,
														DWORD dwOptionSetMask,
														DWORD dwEnabledOptions
														);
	END_INTERFACE_PART(ObjSafe);

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidGetMAC = 2L,
		dispidWriteInfo = 1L
	};
protected:
	LONG WriteInfo(LPCTSTR key, LPCTSTR value);
	BSTR GetMAC();
};

