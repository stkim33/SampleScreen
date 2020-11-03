
// SampleScreenDlg.h : ��� ����
//

#pragma once

#include "ScreenView.h"
#include "ScreenHead.h"
#include "Screenbase.h"
#include "ScreenButton.h"
// CSampleScreenDlg ��ȭ ����

#define MAX_SCREEN_CNT		16
class CSampleScreenDlg : public CDialogEx
{

	struct SCREEN_BTN
	{
		CScreenBtn m_Screen_1Ch;
		CScreenBtn m_Screen_4Ch;
		CScreenBtn m_Screen_9Ch;
		CScreenBtn m_Screen_16Ch;
	};



// �����Դϴ�.
public:
	CSampleScreenDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SampleScreen_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


public:
	CScreenbase				m_ScreenBase;
	CScreenView*			m_pClickScreen;				//���� Ŭ���� ��ũ��
	CScreenHead*			m_pClickScreenTitleBar;
	int						m_index;
	SCREEN_BTN				m_CtrlScreenBtn;

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	LRESULT OnScreenMsg(WPARAM wParam, LPARAM lParam);
	LRESULT OnClickMsg(WPARAM wParam, LPARAM lParam);
	LRESULT OnDoubleClickMsg(WPARAM wParam, LPARAM lParam);
	LRESULT	OnScreenBtnClick(WPARAM wParam, LPARAM lParam);


	afx_msg void OnBnClickedButtonChLeft();
	afx_msg void OnBnClickedButtonChRight();
	afx_msg void OnDestroy();
};
