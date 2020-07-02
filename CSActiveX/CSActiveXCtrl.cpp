// CSActiveXCtrl.cpp : Implementation of the CCSActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "CSActiveX.h"
#include "CSActiveXCtrl.h"
#include "CSActiveXPropPage.h"
#include "afxdialogex.h"

 
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include<string>

#include <windows.h>
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")

#pragma comment(lib, "comsupp.lib")

using namespace std;

typedef struct tagIPInfo
{
	char ip[30];
}IPInfo;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCSActiveXCtrl, COleControl)

// Message map

BEGIN_MESSAGE_MAP(CCSActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CCSActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CCSActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CCSActiveXCtrl, "WriteInfo", dispidWriteInfo, WriteInfo, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCSActiveXCtrl, "GetMAC", dispidGetMAC, GetMAC, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CCSActiveXCtrl, COleControl)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCSActiveXCtrl, 1)
	PROPPAGEID(CCSActiveXPropPage::guid)
END_PROPPAGEIDS(CCSActiveXCtrl)


//安全接口
BEGIN_INTERFACE_MAP(CCSActiveXCtrl, COleControl)
	INTERFACE_PART(CCSActiveXCtrl, IID_IObjectSafety, ObjSafe)
END_INTERFACE_MAP()




// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCSActiveXCtrl, "CSACTIVEX.CSActiveXCtrl.1",
	0x324d4786, 0xe4c9, 0x4dd0, 0x85, 0xc7, 0x15, 0xcc, 0x1f, 0xb8, 0x8c, 0x12)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CCSActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)

// Interface IDs

const IID IID_DCSActiveX = { 0x2BCAA157, 0xB490, 0x40EB, { 0xAC, 0xCD, 0x2C, 0x30, 0x97, 0x5A, 0x2E, 0x26 } };
const IID IID_DCSActiveXEvents = { 0x44268DEF, 0x72A, 0x4246, { 0x92, 0x15, 0x5, 0x6, 0xCF, 0xC9, 0x42, 0xEB } };

// Control type information

static const DWORD _dwCSActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCSActiveXCtrl, IDS_CSACTIVEX, _dwCSActiveXOleMisc)

// CCSActiveXCtrl::CCSActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCSActiveXCtrl

BOOL CCSActiveXCtrl::CCSActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CSACTIVEX,
			IDB_CSACTIVEX,
			afxRegApartmentThreading,
			_dwCSActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CCSActiveXCtrl::CCSActiveXCtrl - Constructor

CCSActiveXCtrl::CCSActiveXCtrl()
{
	InitializeIIDs(&IID_DCSActiveX, &IID_DCSActiveXEvents);
	// TODO: Initialize your control's instance data here.
}

// CCSActiveXCtrl::~CCSActiveXCtrl - Destructor

CCSActiveXCtrl::~CCSActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

// CCSActiveXCtrl::OnDraw - Drawing function

void CCSActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CCSActiveXCtrl::DoPropExchange - Persistence support

void CCSActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}


// CCSActiveXCtrl::OnResetState - Reset control to default state

void CCSActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


// CCSActiveXCtrl::AboutBox - Display an "About" box to the user

void CCSActiveXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_CSACTIVEX);
	dlgAbout.DoModal();
}


// CCSActiveXCtrl message handlers


//向注册表中写数据
LONG CCSActiveXCtrl::WriteInfo(LPCTSTR key, LPCTSTR value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HKEY hSubKey;//创建注册后的句柄
 
	CString str;

	str = _T("Software\\YhTech\\ClientInfo\\");
 		
		// 创建键
		if (RegCreateKey(HKEY_CURRENT_USER, str, &hSubKey) == ERROR_SUCCESS)//创建路径
		{
			// 设置键值
			if (ERROR_SUCCESS != RegSetValueEx(
												hSubKey,
												key,//值名
												0,
												REG_SZ,//类型
												(LPBYTE)(LPCSTR)value,			
												(lstrlen(value) + 1)*sizeof(LPCTSTR))//长度									
												)
			{
				RegCloseKey(hSubKey); //关闭注册表
				return 0;//写入失败
			}
			else{
			
				RegCloseKey(hSubKey); //关闭注册表
				return 1;//写入成功
			}
		}		
 
}

//ip地址和MAC
/*格式转化：先用CString.format转化，再直接使用 "+" 连接字符串*/
BSTR CCSActiveXCtrl::GetMAC()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString cs;//最后的mac
	CString c;//代表mac中某个字符
	CString temp;//代表一个整个MAC地址
	CString t;//过滤mac
	CString t1;
	CString t2;
	BSTR ct;//mac+ip
	LPTSTR ch = _T("000000000000");
	//char*转换成CString
	t.Format(_T("%s"), ch);
 
	//MessageBox(t);
 
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();

	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);

	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	


	//如果函数返回的是ERROR_BUFFER_OVERFLOW
	//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
	//这也是说明为什么stSize既是一个输入量也是一个输出量
	//释放原来的内存空间
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{	
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	
	
	if (ERROR_SUCCESS == nRel)
	{
		//可能有多网卡,因此通过循环去判断
		while (pIpAdapterInfo)
		{
			//修改将temp复原；
			temp = _T("");
			//mac：每次取一个16进制数，逐渐连接起来;
			//此for用于取得一个完整的mac
			for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
			{
				
				//printf("%02X-", pIpAdapterInfo->Address[i]);
				/*先转化为16进制，再连接*/
				/*先排除0，之后随便取出一个mac*/
				
				c.Format(_T("%0x"), (BSTR)pIpAdapterInfo->Address[i]);
				temp = temp + c;

			}
			//得到一个整的MAC判断是否
			//屏蔽
			t2 = temp;
			t1.Format(_T("%s"), temp);
			//MessageBox(t1);
			
			/*不区分大小写比较两个字符串，相等时返回0，大于时返回1，小于时返回-1
			*/
			if (t1.CompareNoCase(t) != 0)
			{
				cs = t2;
				break;
		
			}
			pIpAdapterInfo = pIpAdapterInfo->Next;

		}
	}
	
			 
			//for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
			//{
			//	if (i < pIpAdapterInfo->AddressLength - 1)
			//	{
			//		/*先转化为16进制，再连接*/
			//		c.Format(_T("%02x"), (BSTR)pIpAdapterInfo->Address[i]);
			//		cs = cs+c ;
			//	 
			//	}
			//	else
			//	{
			//		 
			//		c.Format(_T("%02x"), (BSTR)pIpAdapterInfo->Address[i]);
			//		cs =cs+c;
			//	 
			//	}
			//}
	//}
	//获取ip，且转化为ip的网络格式
	
	IPInfo* ips=NULL;
	TCHAR ip[1024] = { NULL };
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	char hostname[256];
	ret = gethostname(hostname, sizeof(hostname));
	gethostname(hostname, 256);
	HOSTENT* host = gethostbyname(hostname);
	char *i= inet_ntoa(*((struct in_addr *)host->h_addr_list[0]));//此处获得本机IP
	 
	int   nLen = strlen(i) + 1;
	int   nwLen = MultiByteToWideChar(CP_ACP, 0, i, nLen, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, i, (int)(strlen(i)+1), ip, nwLen);
	CString p;
	p.Format(_T("%s"),ip);
	cs = cs +_T("#=#")+ p;
	WSACleanup();
	//	delete p;
	///*	delete i;
	//	delete host;
	//	delete hostname;
	//	delete ip;
	//	delete ips;*/
	
	//将CString转化为BSTR
	ct = cs.AllocSysString();
	return  ct;

}


//2016.6.18--新增安全性
ULONG FAR EXPORT  CCSActiveXCtrl::XObjSafe::AddRef()
{
	METHOD_PROLOGUE(CCSActiveXCtrl, ObjSafe);
	return pThis->ExternalAddRef();
}


ULONG FAR EXPORT  CCSActiveXCtrl::XObjSafe::Release()
{
	METHOD_PROLOGUE(CCSActiveXCtrl, ObjSafe);
	return pThis->ExternalRelease();
}


HRESULT FAR EXPORT  CCSActiveXCtrl::XObjSafe::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CCSActiveXCtrl, ObjSafe);
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}


const DWORD dwSupportedBits = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;

const DWORD dwNotSupportedBits = ~dwSupportedBits;


//.............................................................................

// CStopLiteCtrl::XObjSafe::GetInterfaceSafetyOptions

// Allows Container to query what interfaces are safe for what. We're

// optimizing significantly by ignoring which interface the caller is

// asking for.


HRESULT STDMETHODCALLTYPE CCSActiveXCtrl::XObjSafe::GetInterfaceSafetyOptions(

												REFIID riid,

												DWORD __RPC_FAR *pdwSupportedOptions,

												DWORD __RPC_FAR *pdwEnabledOptions)

{

	METHOD_PROLOGUE(CCSActiveXCtrl, ObjSafe);

	HRESULT retval = ResultFromScode(S_OK);

	// does interface exist?

	IUnknown FAR* punkInterface;

	retval = pThis->ExternalQueryInterface(&riid,

		(void * *)&punkInterface);

	if (retval != E_NOINTERFACE) { // interface exists

		punkInterface->Release(); // release it--just checking!

	}


	// we support both kinds of safety and have always both set,

	// regardless of interface

	*pdwSupportedOptions = *pdwEnabledOptions = dwSupportedBits;

	return retval; // E_NOINTERFACE if QI failed

}


/////////////////////////////////////////////////////////////////////////////

// CStopLiteCtrl::XObjSafe::SetInterfaceSafetyOptions

// Since we're always safe, this is a no-brainer--but we do check to make

// sure the interface requested exists and that the options we're asked to

// set exist and are set on (we don't support unsafe mode).


HRESULT STDMETHODCALLTYPE CCSActiveXCtrl::XObjSafe::SetInterfaceSafetyOptions(

												REFIID riid,

												DWORD dwOptionSetMask,

												DWORD dwEnabledOptions)

{

	METHOD_PROLOGUE(CCSActiveXCtrl, ObjSafe);

	// does interface exist?

	IUnknown FAR* punkInterface;

	pThis->ExternalQueryInterface(&riid, (void * *)&punkInterface);

	if (punkInterface) 
	{ // interface exists
		punkInterface->Release(); // release it--just checking!
	}


	else
	{ // interface doesn't exist
		return ResultFromScode(E_NOINTERFACE);
	}


	// can't set bits we don't support
	if (dwOptionSetMask & dwNotSupportedBits) 
	{
		return ResultFromScode(E_FAIL);
	}


	// can't set bits we do support to zero
	dwEnabledOptions &= dwSupportedBits;


	// (we already know there are no extra bits in mask )
	if ((dwOptionSetMask & dwEnabledOptions) != dwOptionSetMask) 
	{
		return ResultFromScode(E_FAIL);
	}


	// don't need to change anything since we're always safe
	return ResultFromScode(S_OK);
}

