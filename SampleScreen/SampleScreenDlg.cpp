
// SampleScreenDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SampleScreen.h"
#include "SampleScreenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSampleScreenDlg 대화 상자



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


// CSampleScreenDlg 메시지 처리기

BOOL CSampleScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	m_CtrlScreenBtn.m_Screen_1Ch.SetParam(this, E_SCREEN_1CH);
	m_CtrlScreenBtn.m_Screen_4Ch.SetParam(this, E_SCREEN_4CH);
	m_CtrlScreenBtn.m_Screen_9Ch.SetParam(this, E_SCREEN_9CH);
	m_CtrlScreenBtn.m_Screen_16Ch.SetParam(this, E_SCREEN_16CH);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ScreenBase.ModifyStyle(0, WS_CLIPCHILDREN);
	m_ScreenBase.SetParam(this);
	m_ScreenBase.ScreenInit();
	m_pClickScreen = m_ScreenBase.ScreenChange(m_index);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSampleScreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSampleScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CSampleScreenDlg::OnScreenMsg(WPARAM wParam, LPARAM lParam)						//스크린을 클릭했을때
{	
	m_pClickScreen = (CScreenView*)wParam;
	m_ScreenBase.OnClickMsg(m_pClickScreen);

	return 0;
}


LRESULT CSampleScreenDlg::OnDoubleClickMsg(WPARAM wParam, LPARAM lParam)				//스크린을 더블 클릭했을때
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


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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