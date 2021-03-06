
// AuthTestClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AuthTestClient.h"
#include "AuthTestClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//Globals
LONG	g_ClientCount = 0;

BOOL	g_isActive = false;
LONG64	g_ActiveThreads = 0;
LONG64	g_AuthSec = 0;
LONG64	g_Success = 0;
LONG64	g_Failure = 0;
LONG64	g_Total = 0;
LONG64	g_LastTotal = 0;




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAuthTestClientDlg dialog



CAuthTestClientDlg::CAuthTestClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTHTESTCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAuthTestClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ServerName, m_ServerName);
	DDX_Control(pDX, IDC_Port, m_Port);
	DDX_Control(pDX, IDC_TargetName, m_TargetName);
	DDX_Control(pDX, IDC_PackageName, m_PackageName);
	DDX_Control(pDX, IDC_Basic, m_Basic);
	DDX_Control(pDX, IDC_Advanced, m_Advanced);
	DDX_Control(pDX, IDC_TabCtrl, m_tabctrl);
	DDX_Control(pDX, IDC_Results, m_Results);
	DDX_Control(pDX, IDC_Implicit, m_Implicit);
	DDX_Control(pDX, IDC_Start, m_Start);
	DDX_Control(pDX, IDC_SingleRun, m_Run);
	DDX_Control(pDX, IDC_Stop, m_Stop);
	DDX_Control(pDX, IDC_WorkerThreads, m_WorkerThreads);
	DDX_Control(pDX, IDC_ActiveThreads, m_ActiveThreads);
	DDX_Control(pDX, IDC_AuthSec, m_AuthSec);
	DDX_Control(pDX, IDC_Success, m_Success);
	DDX_Control(pDX, IDC_Failure, m_Failure);
	DDX_Control(pDX, IDC_Total, m_Total);
	DDX_Control(pDX, IDC_StaticWorkerThreads, m_StaticWorkerThreads);
	DDX_Control(pDX, IDC_StaticActiveThreads, m_StaticActiveThreads);
	DDX_Control(pDX, IDC_StaticAuthSec, m_StaticAuthSec);
	DDX_Control(pDX, IDC_StaticSuccess, m_StaticSuccess);
	DDX_Control(pDX, IDC_StaticFailure, m_StaticFailure);
	DDX_Control(pDX, IDC_StaticTotal, m_StaticTotal);
	DDX_Control(pDX, IDC_Username, m_Username);
	DDX_Control(pDX, IDC_Password, m_Password);
	DDX_Control(pDX, IDC_Domain, m_Domain);
	DDX_Control(pDX, IDC_Explicit, m_Explicit);
}

BEGIN_MESSAGE_MAP(CAuthTestClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TabCtrl, &CAuthTestClientDlg::OnSelchangeTabctrl)
	ON_BN_CLICKED(IDC_SingleRun, &CAuthTestClientDlg::OnBnClickedSinglerun)
	ON_BN_CLICKED(IDC_Start, &CAuthTestClientDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_Stop, &CAuthTestClientDlg::OnBnClickedStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Explicit, &CAuthTestClientDlg::OnBnClickedExplicit)
	ON_BN_CLICKED(IDC_Implicit, &CAuthTestClientDlg::OnBnClickedImplicit)
END_MESSAGE_MAP()


// CAuthTestClientDlg message handlers

BOOL CAuthTestClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ServerName.SetWindowTextW(L"");
	m_Port.SetWindowTextW(L"");
	m_TargetName.SetWindowTextW(L"");

	m_PackageName.AddString(L"Negotiate");
	m_PackageName.AddString(L"Kerberos");
	m_PackageName.AddString(L"NTLM");
	m_PackageName.AddString(L"CredSSP");
	m_PackageName.SetCurSel(0);

	m_WorkerThreads.AddString(L"1");
	m_WorkerThreads.AddString(L"2");
	m_WorkerThreads.AddString(L"4");
	m_WorkerThreads.AddString(L"8");
	m_WorkerThreads.AddString(L"16");
	m_WorkerThreads.AddString(L"32");
	m_WorkerThreads.AddString(L"64");
	m_WorkerThreads.AddString(L"128");
	m_WorkerThreads.AddString(L"256");
	m_WorkerThreads.SetCurSel(0);

	m_tabctrl.InsertItem(0, L"Single Run");
	m_tabctrl.InsertItem(1, L"Stress Test");

	m_Basic.SetCheck(BST_CHECKED);
	m_Implicit.SetCheck(BST_CHECKED);
	
	OnBnClickedImplicit();
	SetSingleRun();

	m_Stop.EnableWindow(false);

	//Refresh thread runs every 1 sec
	SetTimer(1, 1000, 0);

	return true;
}

void CAuthTestClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAuthTestClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAuthTestClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAuthTestClientDlg::OnSelchangeTabctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iSelected = m_tabctrl.GetCurSel();

	switch (iSelected)
	{
	case 0:
		SetSingleRun();
		
		break;
	case 1:
		SetStressTest();
		break;
	}

	*pResult = 0;
}

void CAuthTestClientDlg::SetSingleRun()
{
	m_Run.ShowWindow(true);
	m_Start.ShowWindow(false);
	m_Stop.ShowWindow(false);
	m_StaticWorkerThreads.ShowWindow(false);
	m_WorkerThreads.ShowWindow(false);

	m_Results.ShowWindow(true);

	m_StaticActiveThreads.ShowWindow(false);
	m_StaticAuthSec.ShowWindow(false);
	m_StaticSuccess.ShowWindow(false);
	m_StaticFailure.ShowWindow(false);
	m_StaticTotal.ShowWindow(false);

	m_ActiveThreads.ShowWindow(false);
	m_AuthSec.ShowWindow(false);
	m_Success.ShowWindow(false);
	m_Failure.ShowWindow(false);
	m_Total.ShowWindow(false);
}


void CAuthTestClientDlg::SetStressTest()
{
	m_Run.ShowWindow(false);
	m_Start.ShowWindow(true);
	m_Stop.ShowWindow(true);
	m_StaticWorkerThreads.ShowWindow(true);
	m_WorkerThreads.ShowWindow(true);

	m_Results.ShowWindow(false);

	m_StaticActiveThreads.ShowWindow(true);
	m_StaticAuthSec.ShowWindow(true);
	m_StaticSuccess.ShowWindow(true);
	m_StaticFailure.ShowWindow(true);
	m_StaticTotal.ShowWindow(true);

	m_ActiveThreads.ShowWindow(true);
	m_AuthSec.ShowWindow(true);
	m_Success.ShowWindow(true);
	m_Failure.ShowWindow(true);
	m_Total.ShowWindow(true);

}

void CAuthTestClientDlg::OnBnClickedImplicit()
{
	m_Username.EnableWindow(false);
	m_Password.EnableWindow(false);
	m_Domain.EnableWindow(false);
}

void CAuthTestClientDlg::OnBnClickedExplicit()
{
	m_Username.EnableWindow(true);
	m_Password.EnableWindow(true);
	m_Domain.EnableWindow(true);
}


void CAuthTestClientDlg::OnBnClickedSinglerun()
{
	CString StrTemp;

	//parameters to pass to worker thread. The worker thread must free this struct
	THREADSTRUCT * _param = new THREADSTRUCT;

	//current instance of CAuthTestDlg
	_param->_this = this;

	//client ID
	_param->iIndex = InterlockedIncrement(&g_ClientCount);

	//Server Name
	m_ServerName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szServerName, StrTemp);

	//Port
	m_Port.GetWindowTextW(StrTemp);
	_param->iPort = _wtoi(StrTemp);

	//Target Name
	m_TargetName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szTargetName, StrTemp);

	//Package Name
	m_PackageName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szPackageName, StrTemp);

	//Test Type
	if (m_Basic.GetCheck() == BST_CHECKED)
	{
		_param->TestType = Basic;
	}
	else
	{
		_param->TestType = Advanced;
	}

	//Explicit creds
	if (m_Explicit.GetCheck() == BST_CHECKED)
	{

		//Cannot be empty
		if (m_Username.GetWindowTextLengthW() == 0)
		{
			MessageBox(L"Username cannot be empty.");

			return;
		}

		_param->ExplicitCred = true;

		//Username
		m_Username.GetWindowTextW(StrTemp);
		wcscpy_s(_param->szUsername, StrTemp);

		//Password
		m_Password.GetWindowTextW(StrTemp);
		wcscpy_s(_param->szPassword, StrTemp);

		//Domain
		m_Domain.GetWindowTextW(StrTemp);
		wcscpy_s(_param->szDomain, StrTemp);
	}
	else
	{
		_param->ExplicitCred = false;
	}


	//Create Worker Thread
	AfxBeginThread(WorkerThreadSingleRun, _param);

}

UINT CAuthTestClientDlg::WorkerThreadSingleRun(LPVOID _param)
{
	//cast _param into local Param
	THREADSTRUCT * Param = (THREADSTRUCT *)_param;

	ClientConn * pclient = new ClientConn(
		Param->iIndex,
		Param->szServerName,
		Param->iPort,
		Param->szTargetName,
		Param->szPackageName,
		Param->ExplicitCred,
		Param->szUsername,
		Param->szPassword,
		Param->szDomain);

	WCHAR pMessage[200] = {};
	int cbMessage = sizeof(pMessage);

	CString StrTemp;
	Param->_this->m_Results.ResetContent();

	StrTemp.Format(L"Initializing...\n");
	Param->_this->m_Results.AddString(StrTemp);

	//Disable button
	Param->_this->m_Run.EnableWindow(false);

	StrTemp.Format(L"Attempting to connect...\n");
	Param->_this->m_Results.AddString(StrTemp);

	//
	// Connect to the server
	//
	if (!pclient->Connect())
	{
		StrTemp.Format(L"Test Failed. Error %d at Connect -> %s. Aborting.\n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		goto cleanup;
	}
	StrTemp.Format(L"Connected to server: %s\n", pclient->szServerName);
	Param->_this->m_Results.AddString(StrTemp);


	//
	// Initialize
	//
	if (!pclient->Initialize())
	{
		StrTemp.Format(L"Error Initializing. Aborting\n");
		Param->_this->m_Results.AddString(StrTemp);

		goto cleanup;
	}
	

	//
	// Send TestType
	//
	if (!pclient->SendTestType(Param->TestType))
	{
		StrTemp.Format(L"Test Failed. Error %d at SendTestType -> %s. Aborting.\n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		goto cleanup;
	}
	StrTemp.Format(L"TestType sent.\n");
	Param->_this->m_Results.AddString(StrTemp);

	//
	// Send Package Name
	//
	if (!pclient->SendPackageName())
	{
		StrTemp.Format(L"Test Failed. Error %d at SendPackageName -> %s. Aborting.\n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		goto cleanup;
	}
	StrTemp.Format(L"PackageName sent.\n");
	Param->_this->m_Results.AddString(StrTemp);


	//
	// Authenticate
	//

	if (!pclient->Authenticate())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at Authenticate -> %s.\n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		//if Allow delegating fresh credentials
		if (pclient->dwErrorCode == SEC_E_DELEGATION_POLICY &&
			!_wcsicmp(pclient->pkgInfo->Name, L"CredSSP"))
		{
			StrTemp.Format(L"Check CredSSP delegation policy 'Allow delegating fresh credentials'.\n");
			Param->_this->m_Results.AddString(StrTemp);

		}

		//if Allow delegating fresh credentials with NTLM
		if (pclient->dwErrorCode == SEC_E_POLICY_NLTM_ONLY &&
			!_wcsicmp(pclient->pkgInfo->Name, L"CredSSP"))
		{
			StrTemp.Format(L"Check CredSSP delegation policy 'Allow delegating fresh credentials with NTLM-only'.\n");
			Param->_this->m_Results.AddString(StrTemp);

		}


		goto cleanup;
	}
	StrTemp.Format(L"Authentication success.\n");
	Param->_this->m_Results.AddString(StrTemp);


	//
	//Prints the Package selected during authentication, Encryption Algorithm, and key size
	//
	if (!_wcsicmp(pclient->szPackageName, L"CredSSP"))
	{
		StrTemp.Format(L"Package selected: CredSSP over %s\n", pclient->szSelectedPackageName);
		Param->_this->m_Results.AddString(StrTemp);
	}
	else
	{
		StrTemp.Format(L"Package selected: %s\n", pclient->szSelectedPackageName);
		Param->_this->m_Results.AddString(StrTemp);
	}
	StrTemp.Format(L"Encryption Algorithm: %s %d bits.\n", pclient->szEncryptAlgorithmName, pclient->KeySize);
	Param->_this->m_Results.AddString(StrTemp);

	StrTemp.Format(L"Signature Algorithm : %s\n",  pclient->szSignatureAlgorithmName);
	Param->_this->m_Results.AddString(StrTemp);


	//wrap if basic

	if (Param->TestType == Basic)
	{
		StrTemp.Format(L"Basic test completed successfully.\n");
		Param->_this->m_Results.AddString(StrTemp);

		goto cleanup;
	}


	//
	//Obtain the size of signature and the encryption trailer blocks
	//

	if (!pclient->GetContextSizes())
	{
		StrTemp.Format(L"Test Failed. Error 0x%08x at GetContextSizes -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		goto cleanup;
	}

	//
	//Receive an encrypted message from the server and decrypts it
	//

	if (!pclient->SecureReceive(pMessage, cbMessage))
	{
		StrTemp.Format(L"Advanced test failed. Error 0x%08x at SecureReceive -> %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		goto cleanup;
	}

	//
	//verify if the beginning of the decrypted message matches what we expect
	//

	if (wcsncmp(pMessage, L"The time now is", 15) != NULL)
	{
		StrTemp.Format(L"Advanced test Failed. Decrypted message not recognized. Error 0x%08x at %s. \n", pclient->dwErrorCode, pclient->szErrorLocation);
		Param->_this->m_Results.AddString(StrTemp);
		Param->_this->m_Results.AddString(pclient->szErrorMessage);

		goto cleanup;
	}

	StrTemp.Format(L"Impersonation and Encryption success.\n");
	Param->_this->m_Results.AddString(StrTemp);

	StrTemp.Format(L"Advanced test completed successfully.\n");
	Param->_this->m_Results.AddString(StrTemp);

cleanup:

	if (pclient)
		delete pclient;

	//Re-enable button
	Param->_this->m_Run.EnableWindow(true);

	if (Param)
		delete Param;


	return true;
}



void CAuthTestClientDlg::OnBnClickedStart()
{
	CString StrTemp;

	//parameters to pass to worker thread. The worker thread must free this struct
	THREADSTRUCT * _param = new THREADSTRUCT;

	//current instance of CAuthTestDlg
	_param->_this = this;

	//client ID
	_param->iIndex = InterlockedIncrement(&g_ClientCount);

	//Server Name
	m_ServerName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szServerName, StrTemp);

	//Port
	m_Port.GetWindowTextW(StrTemp);
	_param->iPort = _wtoi(StrTemp);

	//Target Name
	m_TargetName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szTargetName, StrTemp);

	//Package Name
	m_PackageName.GetWindowTextW(StrTemp);
	wcscpy_s(_param->szPackageName, StrTemp);

	//Test Type
	if (m_Basic.GetCheck() == BST_CHECKED)
	{
		_param->TestType = Basic;
	}
	else
	{
		_param->TestType = Advanced;
	}

	//Explicit creds
	if (m_Explicit.GetCheck() == BST_CHECKED)
	{

		//Cannot be empty
		if (m_Username.GetWindowTextLengthW() == 0)
		{
			MessageBox(L"Username cannot be empty.");

			return;
		}

		_param->ExplicitCred = true;

		//Username
		m_Username.GetWindowTextW(StrTemp);
		wcscpy_s(_param->szUsername, StrTemp);

		//Password
		m_Password.GetWindowTextW(StrTemp);
		wcscpy_s(_param->szPassword, StrTemp);

		//Domain
		m_Domain.GetWindowTextW(StrTemp);
		wcscpy_s(_param->szDomain, StrTemp);
	}
	else
	{
		_param->ExplicitCred = false;
	}


	g_isActive = true;

	//Disable Start Button
	m_Start.EnableWindow(false);

	//Enable Stop Button
	m_Stop.EnableWindow(true);

	//Create Worker Threads

	int iSel = m_WorkerThreads.GetCurSel();
	m_WorkerThreads.GetLBText(iSel, StrTemp);
	int iWorkerThreads = _ttoi(StrTemp);

	for (int i = 0; i < iWorkerThreads; i++)
	{

		AfxBeginThread(WorkerThreadStressTest, _param);

	}

}

UINT CAuthTestClientDlg::WorkerThreadStressTest(LPVOID _param)
{
	//cast _param into local Param
	THREADSTRUCT * Param = (THREADSTRUCT *)_param;

	WCHAR pMessage[200] = {};
	int cbMessage = sizeof(pMessage);

	InterlockedIncrement64(&g_ActiveThreads);

	ClientConn * pclient = new ClientConn(
		Param->iIndex,
		Param->szServerName,
		Param->iPort,
		Param->szTargetName,
		Param->szPackageName,
		Param->ExplicitCred,
		Param->szUsername,
		Param->szPassword,
		Param->szDomain);


	//
	// Connect to the server
	//

	while (g_isActive && !pclient->Connect())
	{
		InterlockedIncrement64(&g_Total);

		InterlockedIncrement64(&g_Failure);

		Sleep(RetryTimeOut);
	}



	while (g_isActive)
	{
		InterlockedIncrement64(&g_Total);

		
		//
		// Initialize
		//
		if (!pclient->Initialize())
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}


		//
		// Send TestType
		//
		if (!pclient->SendTestType(Param->TestType))
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}

		//
		// Send Package Name
		//
		if (!pclient->SendPackageName())
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}


		//
		// Authenticate
		//
		if (!pclient->Authenticate())
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}



		//
		//wrap if basic
		//

		if (Param->TestType == Basic)
		{
			InterlockedIncrement64(&g_Success);

			continue;
		}


		//
		//Obtain the size of signature and the encryption trailer blocks
		//

		if (!pclient->GetContextSizes())
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}


		//
		//Receive an encrypted message from the server and decrypts it
		//

		if (!pclient->SecureReceive(pMessage, cbMessage))
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}

		//
		//verify if the beginning of the decrypted message matches what we expect
		//

		if (wcsncmp(pMessage, L"The time now is", 15) != NULL)
		{
			InterlockedIncrement64(&g_Failure);

			Sleep(RetryTimeOut);

			continue;
		}


		//Advanced test complete

		InterlockedIncrement64(&g_Success);


	}// loop



	if (pclient)
		delete pclient;


	InterlockedDecrement64(&g_ActiveThreads);


	//the last thread to exit frees Param

	if (g_ActiveThreads == 0)
	{
		//Re-enable button
		Param->_this->m_Start.EnableWindow(true);

		delete Param;
	}

	return true;

}



void CAuthTestClientDlg::OnBnClickedStop()
{
	g_isActive = false;

	//Disable Stop Button
	m_Stop.EnableWindow(false);
}

//
// Refresh Results
//
void CAuthTestClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	CString StrTemp;

	StrTemp.Format(L"%d", g_ActiveThreads);
	m_ActiveThreads.SetWindowTextW(StrTemp);
	
	g_AuthSec = g_Total - g_LastTotal;
	g_LastTotal = g_Total;
	StrTemp.Format(L"%d", g_AuthSec);
	m_AuthSec.SetWindowTextW(StrTemp);
	
	StrTemp.Format(L"%d", g_Success);
	m_Success.SetWindowTextW(StrTemp);

	StrTemp.Format(L"%d", g_Failure);
	m_Failure.SetWindowTextW(StrTemp);

	StrTemp.Format(L"%d", g_Total);
	m_Total.SetWindowTextW(StrTemp);

}




