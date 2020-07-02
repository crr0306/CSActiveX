// CSActiveXPropPage.cpp : Implementation of the CCSActiveXPropPage property page class.

#include "stdafx.h"
#include "CSActiveX.h"
#include "CSActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCSActiveXPropPage, COlePropertyPage)

// Message map

BEGIN_MESSAGE_MAP(CCSActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCSActiveXPropPage, "CSACTIVEX.CSActiveXPropPage.1",
	0xfbf02df, 0xd184, 0x4618, 0x9c, 0x27, 0x94, 0x34, 0x43, 0x4, 0x44, 0x48)

// CCSActiveXPropPage::CCSActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCSActiveXPropPage

BOOL CCSActiveXPropPage::CCSActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CSACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CCSActiveXPropPage::CCSActiveXPropPage - Constructor

CCSActiveXPropPage::CCSActiveXPropPage() :
	COlePropertyPage(IDD, IDS_CSACTIVEX_PPG_CAPTION)
{
}

// CCSActiveXPropPage::DoDataExchange - Moves data between page and properties

void CCSActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CCSActiveXPropPage message handlers
