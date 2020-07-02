#pragma once

// CSActiveXPropPage.h : Declaration of the CCSActiveXPropPage property page class.


// CCSActiveXPropPage : See CSActiveXPropPage.cpp for implementation.

class CCSActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCSActiveXPropPage)
	DECLARE_OLECREATE_EX(CCSActiveXPropPage)

// Constructor
public:
	CCSActiveXPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_CSACTIVEX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

