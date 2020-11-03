#pragma once


#define ON_SCREEN_DOWN				1012
#define ON_SCREEN_DOUBLE_DOWN		1013
#define SCREEN_TITLE_BAR_HEAGHT		40

class CScreenHead: public CDialogEx
{
	DECLARE_DYNAMIC(CScreenHead)

public:
	CScreenHead(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScreenHead();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREEN_HEAD};
#endif

private:
	void*		m_pScreen;
	CString		m_strNumber;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	void SetParam(void* pData, int nDevice);
};
