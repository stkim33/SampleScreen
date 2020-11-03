// ScreenDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ScreenView.h"
#include "SampleScreen.h"
#include "SampleScreenDlg.h"

IMPLEMENT_DYNAMIC(CScreenView, CDialog)

CScreenView::CScreenView(CWnd* pParent /*=NULL*/)
: CDialog(IDD_SCREEN_VIEW, pParent)
{
	m_bDClink = FALSE;
}

CScreenView::~CScreenView()
{
	m_bExit = TRUE;
	
}

void CScreenView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC1, m_st_Number);
	

}

BEGIN_MESSAGE_MAP(CScreenView, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CScreenDlg �޽��� ó�����Դϴ�.

void CScreenView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC memDC;
	CBitmap bitmap, *pOldBitmap = NULL;
	CRect rcDlg;
	CString strFileName;

	GetClientRect(&rcDlg);
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rcDlg.right, rcDlg.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.FillSolidRect(&rcDlg, RGB(255, 255, 255));
	memDC.DrawText(m_strNumber, rcDlg, DT_SINGLELINE| DT_CENTER | DT_VCENTER);

	dc.BitBlt(0, 0, rcDlg.right, rcDlg.bottom, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

}

void CScreenView::SetParam(CWnd* pParent, void* pParam, int nDevice)
{
	m_pParent = pParent;
	m_pSocket = pParam;
	m_nNumber = nDevice;
	m_strNumber.Format("%d", nDevice);
}

void CScreenView::OnLButtonDown(UINT nFlags, CPoint point)	
{	
	m_pParent->SendMessage(ON_SCREEN_DOWN,(WPARAM)this);
	CDialog::OnLButtonDown(nFlags, point);
}

void CScreenView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	if (m_bDClink)	m_bDClink = false;
	else			m_bDClink = true;
	m_pParent->SendMessage(ON_SCREEN_DOUBLE_DOWN, (WPARAM)this);
	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CScreenView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE/*CDialog::OnEraseBkgnd(pDC)*/;
}

void CScreenView::Close()																		
{
	
}

void CScreenView::OnDestroy()
{
	CDialog::OnDestroy();
	delete m_pStatic;
}


BOOL CScreenView::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}	




BOOL CScreenView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
