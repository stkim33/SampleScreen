#pragma once
#include "afxwin.h"

// CScreenDlg ��ȭ �����Դϴ�.

#define ON_SCREEN_DOWN			1012
#define ON_SCREEN_DOUBLE_DOWN	1013

class CScreenView : public CDialog
{
	DECLARE_DYNAMIC(CScreenView)

public:
	CScreenView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScreenView();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREEN_VIEW};
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()


public:
	BOOL				m_bConnector;
	CWnd*				m_pParent;
	void*				m_pSocket;
	CString				m_strConnectip;
	BOOL				m_bDClink;
	CString				m_strNumber;
	int					m_nNumber;

private:
	HANDLE				m_hThread;
	BOOL				m_bExit;
	CStatic				*m_pStatic;
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

public:
	void SetParam(CWnd* pParent,void* pParam,int nDevice);
	void Close();
	
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
