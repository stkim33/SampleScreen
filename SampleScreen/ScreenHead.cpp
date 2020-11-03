// ScreenTitleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "SampleScreen.h"
#include "ScreenHead.h"
#include "ScreenView.h"


// CScreenTitleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CScreenHead, CDialogEx)

CScreenHead::CScreenHead(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCREEN_HEAD, pParent)
{

}

CScreenHead::~CScreenHead()
{
}

void CScreenHead::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScreenHead, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CScreenTitleDlg 메시지 처리기입니다.


BOOL CScreenHead::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return false;//CDialogEx::OnEraseBkgnd(pDC);
}

void CScreenHead::SetParam(void* pData, int nDevice)
{
	m_pScreen = pData;
	m_strNumber.Format("%d", nDevice);
}
void CScreenHead::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CDC memDC;
	CBitmap bitmap, *pOldBitmap = NULL;
	CRect rcDlg;
	CString strFileName;

	GetClientRect(&rcDlg);
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rcDlg.right, rcDlg.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.FillSolidRect(&rcDlg, RGB(255, 255, 255));

	CPen pen;
	CPen* oldPen;

	memDC.DrawText("Title : ", rcDlg, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	memDC.DrawText(m_strNumber + " 번 ", CRect(50,0, rcDlg.Width(), rcDlg.Height()), DT_SINGLELINE | DT_VCENTER);

	dc.BitBlt(0, 0, rcDlg.right, rcDlg.bottom, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


void CScreenHead::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonDblClk(nFlags, point);
	//m_pParent->SendMessage(ON_SCREEN_DOWN, (WPARAM)this);
}


void CScreenHead::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonDown(nFlags, point);
}
