
// SampleScreenDlg.h : 헤더 파일
//

#pragma once

#include "ScreenView.h"
#include "ScreenHead.h"
#include "Screenbase.h"
#include "ScreenButton.h"
// CSampleScreenDlg 대화 상자

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



// 생성입니다.
public:
	CSampleScreenDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SampleScreen_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


public:
	CScreenbase				m_ScreenBase;
	CScreenView*			m_pClickScreen;				//현재 클릭된 스크린
	CScreenHead*			m_pClickScreenTitleBar;
	int						m_index;
	SCREEN_BTN				m_CtrlScreenBtn;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
