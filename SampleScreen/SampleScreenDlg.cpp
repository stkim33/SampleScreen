
// SampleScreenDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SampleScreen.h"
#include "SampleScreenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSampleScreenDlg ��ȭ ����



CSampleScreenDlg::CSampleScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pClickScreen = NULL;
	m_index = E_SCREEN_16CH;

	int aa;

}

void CSampleScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_ScreenBase);
	DDX_Control(pDX, IDC_BUTTON1, m_CtrlScreenBtn.m_Screen_1Ch);
	DDX_Control(pDX, IDC_BUTTON2, m_CtrlScreenBtn.m_Screen_4Ch);
	DDX_Control(pDX, IDC_BUTTON3, m_CtrlScreenBtn.m_Screen_9Ch);
	DDX_Control(pDX, IDC_BUTTON4, m_CtrlScreenBtn.m_Screen_16Ch);
}

BEGIN_MESSAGE_MAP(CSampleScreenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(ON_SCREEN_DOWN, OnScreenMsg)
	ON_MESSAGE(ON_SCREEN_DOUBLE_DOWN, OnDoubleClickMsg)
	ON_MESSAGE(WM_SCREENBUTTON_CLIICK, OnScreenBtnClick)

	ON_BN_CLICKED(IDC_BUTTON_CH_LEFT, &CSampleScreenDlg::OnBnClickedButtonChLeft)
	ON_BN_CLICKED(IDC_BUTTON_CH_RIGHT, &CSampleScreenDlg::OnBnClickedButtonChRight)
	ON_WM_DESTROY()


	
END_MESSAGE_MAP()


// CSampleScreenDlg �޽��� ó����

BOOL CSampleScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.


	m_CtrlScreenBtn.m_Screen_1Ch.SetParam(this, E_SCREEN_1CH);
	m_CtrlScreenBtn.m_Screen_4Ch.SetParam(this, E_SCREEN_4CH);
	m_CtrlScreenBtn.m_Screen_9Ch.SetParam(this, E_SCREEN_9CH);
	m_CtrlScreenBtn.m_Screen_16Ch.SetParam(this, E_SCREEN_16CH);

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ScreenBase.ModifyStyle(0, WS_CLIPCHILDREN);
	m_ScreenBase.SetParam(this);
	m_ScreenBase.ScreenInit();
	m_pClickScreen = m_ScreenBase.ScreenChange(m_index);


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSampleScreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSampleScreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSampleScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CSampleScreenDlg::OnScreenMsg(WPARAM wParam, LPARAM lParam)						//��ũ���� Ŭ��������
{	
	m_pClickScreen = (CScreenView*)wParam;
	m_ScreenBase.OnClickMsg(m_pClickScreen);

	return 0;
}


LRESULT CSampleScreenDlg::OnDoubleClickMsg(WPARAM wParam, LPARAM lParam)				//��ũ���� ���� Ŭ��������
{
	m_pClickScreen = (CScreenView*)wParam;

	if (m_pClickScreen->m_bDClink)
		m_pClickScreen = m_ScreenBase.BigScreen(m_pClickScreen);
	else
	{
		m_ScreenBase.ScreenChange(m_index);
		m_ScreenBase.OnClickMsg(m_pClickScreen);
	}
	m_ScreenBase.Invalidate();
	return 0;
}


void CSampleScreenDlg::OnBnClickedButtonChLeft()
{
	if(!m_ScreenBase.IsMinPageScreenCheck())
		m_ScreenBase.GetJumpPage(m_index, E_SCREEN_PREV);
}


void CSampleScreenDlg::OnBnClickedButtonChRight()
{
	if(!m_ScreenBase.IsMaxPageScreenCheck(m_index))
		m_ScreenBase.GetJumpPage(m_index, E_SCREEN_NEXT);

}


void CSampleScreenDlg::OnDestroy()
{
	m_ScreenBase.ScreenDelete();
	CDialogEx::OnDestroy();


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


LRESULT CSampleScreenDlg::OnScreenBtnClick(WPARAM wParam, LPARAM lParam)
{
	E_SCREEN_CH_TYPE e_Type = (E_SCREEN_CH_TYPE)wParam;
	m_ScreenBase.ScreenDataInit();

	switch (e_Type)
	{
		case E_SCREEN_1CH:			m_index = E_SCREEN_1CH;				break;
		case E_SCREEN_4CH:			m_index = E_SCREEN_4CH;				break;
		case E_SCREEN_9CH:			m_index = E_SCREEN_9CH;				break;
		case E_SCREEN_16CH:			m_index = E_SCREEN_16CH;			break;
	}

	m_pClickScreen = m_ScreenBase.ScreenChange(m_index);
	m_ScreenBase.Invalidate();
	return 0;
}