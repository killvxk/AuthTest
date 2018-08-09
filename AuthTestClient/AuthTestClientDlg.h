
// AuthTestClientDlg.h : header file
//

#pragma once


// CAuthTestClientDlg dialog
class CAuthTestClientDlg : public CDialogEx
{
// Construction
public:
	CAuthTestClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTHTESTCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void CAuthTestClientDlg::SetSingleRun();
	void CAuthTestClientDlg::SetStressTest();

	static UINT CAuthTestClientDlg::WorkerThreadSingleRun(LPVOID _param);
	static UINT CAuthTestClientDlg::WorkerThreadStressTest(LPVOID _param);

	//static void CAuthTestDlg::PrintOutput(BOOL fVerbose, CString StrTemp,LPVOID _param, ClientConn * pclient);

	//struct with params to WorkerThread
	typedef struct THREADSTRUCT
	{
		CAuthTestClientDlg * _this;
		int		iIndex;
		WCHAR	szServerName[255];
		int		iPort;
		WCHAR	szTargetName[255];
		WCHAR	szPackageName[40];
		TestType TestType;
	} THREADSTRUCT;

	afx_msg void OnSelchangeTabctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSinglerun();

	CEdit		m_ServerName;
	CEdit		m_Port;
	CEdit		m_TargetName;
	CComboBox	m_PackageName;
	CTabCtrl	m_tabctrl;
	CButton		m_Basic;
	CButton		m_Advanced;
	CButton		m_Implicit;
	CListBox	m_Results;
	
	CButton m_Start;
	CButton m_Run;
	CButton m_Stop;
	CComboBox m_WorkerThreads;

	afx_msg void OnBnClickedStart();

	CStatic m_ActiveThreads;
	CStatic m_AuthSec;
	CStatic m_Success;
	CStatic m_Failure;
	CStatic m_Total;
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_StaticWorkerThreads;
	CStatic m_StaticActiveThreads;
	CStatic m_StaticAuthSec;
	CStatic m_StaticSuccess;
	CStatic m_StaticFailure;
	CStatic m_StaticTotal;
	CEdit m_Username;
	CEdit m_Password;
	CEdit m_Domain;
	afx_msg void OnBnClickedExplicit();
	afx_msg void OnBnClickedImplicit();
};
