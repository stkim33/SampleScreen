#pragma once
#include "ScreenView.h"
#include "ScreenHead.h"
// CScreenbase
#pragma  pack(push,1)
typedef struct Position
{
	int nX;
	int nY;
}Position;
#pragma pack(pop)

enum E_SCREEN_PAGE_TYPE
{
	E_SCREEN_NEXT = 1,
	E_SCREEN_PREV
};

class CScreenbase : public CWnd
{
	DECLARE_DYNAMIC(CScreenbase)

public:
	CScreenbase();
	virtual ~CScreenbase();

private:
	struct PositionData
	{
		CScreenHead* pScreenHead;
		CScreenView* pScreenView;
		Position	pos;
		int			nScreenindex;

		PositionData(void)
		{
			pScreenHead = NULL;
			pScreenView	= NULL;
			nScreenindex=0;
		}
	};

protected:
	DECLARE_MESSAGE_MAP()
public:
	CList<PositionData*>	m_listScreen;
	CWnd*					m_pParent;
	PositionData*			m_pClick;
	int						m_nStartIndex;
	int						m_nStartPage;

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	void			ScreenInit();
	void			ScreenDataInit();
	void			SetParam(CWnd* pParent);

public:
	CScreenView*	ScreenChange(int);
	void			ScreenDelete();
	CScreenView*	BigScreen(CScreenView*);

public:
	int				GetJumpPage(int nScreenindex, E_SCREEN_PAGE_TYPE ePage);
	HWND			GetScreenHwnd(int index);
	void			OnClickMsg(CScreenView*);

public:
	bool IsMaxPageScreenCheck(int);
	bool IsMinPageScreenCheck();

};
