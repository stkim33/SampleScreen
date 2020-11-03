// MyScreenButton.cpp : ���� �����Դϴ�.
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

// CMyPTZButton �޽��� ó�����Դϴ�.

void CScreenBtn::SetParam(CWnd* pParent, int nPtz)
{
	m_pParent = pParent;
	m_nScreenClick = nPtz;
}

void CScreenBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (m_pParent != NULL)
		m_pParent->SendMessage(WM_SCREENBUTTON_CLIICK, m_nScreenClick, (LPARAM)0);

	CButton::OnLButtonDown(nFlags, point);
}

void CScreenBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_pParent != NULL)
		m_pParent->SendMessage(WM_SCREENBUTTON_CLIICK, m_nScreenClick, (LPARAM)1);

	CButton::OnLButtonUp(nFlags, point);
}

// CMyScreenButton �޽��� ó�����Դϴ�.


