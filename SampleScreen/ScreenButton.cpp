// MyScreenButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ScreenButton.h"


// CMyScreenButton

IMPLEMENT_DYNAMIC(CScreenBtn, CWnd)

CScreenBtn::CScreenBtn()
{

}

CScreenBtn::~CScreenBtn()
{
}


BEGIN_MESSAGE_MAP(CScreenBtn, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMyPTZButton 메시지 처리기입니다.

void CScreenBtn::SetParam(CWnd* pParent, int nPtz)
{
	m_pParent = pParent;
	m_nScreenClick = nPtz;
}

void CScreenBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_pParent != NULL)
		m_pParent->SendMessage(WM_SCREENBUTTON_CLIICK, m_nScreenClick, (LPARAM)0);

	CButton::OnLButtonDown(nFlags, point);
}

void CScreenBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pParent != NULL)
		m_pParent->SendMessage(WM_SCREENBUTTON_CLIICK, m_nScreenClick, (LPARAM)1);

	CButton::OnLButtonUp(nFlags, point);
}

// CMyScreenButton 메시지 처리기입니다.


