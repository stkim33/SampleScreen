#pragma once


// CMyScreenButton
enum E_SCREEN_CH_TYPE
{
	E_SCREEN_1CH = 1,
	E_SCREEN_4CH,
	E_SCREEN_9CH,
	E_SCREEN_16CH,
};

#define WM_SCREENBUTTON_CLIICK WM_USER + 0x2020

class CScreenBtn : public CButton
{
	DECLARE_DYNAMIC(CScreenBtn)

public:
	CScreenBtn();
	virtual ~CScreenBtn();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void SetParam(CWnd* pParam, int nPtz);

public:
	CWnd*		m_pParent;
	int			m_nScreenClick;
};


