// Screenbase.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SampleScreen.h"
#include "Screenbase.h"
#include "SampleScreenDlg.h"

// CScreenbase

IMPLEMENT_DYNAMIC(CScreenbase, CWnd)

CScreenbase::CScreenbase()
{
	m_pClick=NULL;
	m_nStartIndex = 0;
	m_nStartPage = 1;
}

CScreenbase::~CScreenbase()
{
}

BEGIN_MESSAGE_MAP(CScreenbase, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CScreenbase::SetParam(CWnd* pParent)
{
	m_pParent=pParent;
}

void CScreenbase::ScreenInit()
{
	PositionData*	pScreenData = NULL;
	CString strFormat;

	/* 스크린 초기화 */
	for (int i = 0; i < MAX_SCREEN_CNT; i++)
	{
		//new
		pScreenData = new PositionData;
		pScreenData->pScreenView = new CScreenView;
		pScreenData->pScreenHead = new CScreenHead;
		
		//pMain
		pScreenData->pScreenView->SetParam(m_pParent, this, i + 1);
		pScreenData->pScreenHead->SetParam(m_pParent, i + 1);

		//Create
		pScreenData->pScreenView->Create(IDD_SCREEN_VIEW, this);
		pScreenData->pScreenHead->Create(IDD_SCREEN_HEAD, this);

		//add
		m_listScreen.AddTail(pScreenData);
	}
}

void CScreenbase::ScreenDataInit()
{
	m_nStartIndex = 0;
	m_nStartPage = 1;
}
CScreenView* CScreenbase::ScreenChange(int nScreenindex)
{
	CRect Rect;
	GetClientRect(&Rect);
	int nScreenNum=0;

	CSampleScreenDlg* pMain= (CSampleScreenDlg*)m_pParent;
	PositionData*	pScreenData = NULL;

	
	/* 이전 스크린 닫기*/
	if(nScreenindex*nScreenindex < m_listScreen.GetCount())
	{
		int nIndex=nScreenindex*nScreenindex;
		while (nIndex != m_listScreen.GetCount())
		{
			pScreenData = m_listScreen.GetAt(m_listScreen.FindIndex(nIndex++));
			pScreenData->pScreenView->ShowWindow(SW_HIDE);
			pScreenData->pScreenHead->ShowWindow(SW_HIDE);

			if (pScreenData->pScreenView->m_bConnector)
				pScreenData->pScreenView->Close();

			pScreenData = NULL;
		}
	}
	
	if (m_pClick != NULL)
	{
		/*더블 클릭 한 것 초기화 */
		m_pClick->pScreenView->m_bDClink = false;

		/* 숨긴 스크린에 포커스가 있으면 */
		if (m_pClick->pScreenView->m_nNumber > nScreenindex * nScreenindex)
			m_pClick = NULL;
	}
		
	/*  스크린 열기 */
	CString strFormat;
	int nView = 0;
	for(int i=0;i<nScreenindex;i++)
	{
		for(int j=0;j<nScreenindex;j++)
		{	
			if (m_nStartIndex + nView >= MAX_SCREEN_CNT)
				break;

			//Find
			pScreenData=m_listScreen.GetAt(m_listScreen.FindIndex(m_nStartIndex + nView));
			
			//All HIDE
			pScreenData->pScreenView->ShowWindow(SW_HIDE);
			pScreenData->pScreenHead->ShowWindow(SW_HIDE);
		
			//UPDATE
			pScreenData->nScreenindex=nScreenindex;
			pScreenData->pos.nX=j;
			pScreenData->pos.nY=i;
			

			//Screen-View
			pScreenData->pScreenView->MoveWindow((Rect.Width()/(nScreenindex))*j+3,
			(Rect.Height()/(nScreenindex))*i+3 + (SCREEN_TITLE_BAR_HEAGHT - 10),
				(Rect.Width()/nScreenindex)+(6*-1), 
				(Rect.Height()/nScreenindex)+(6*-1) - (SCREEN_TITLE_BAR_HEAGHT - 10));

			//Screen-TitleBar
			pScreenData->pScreenHead->MoveWindow((Rect.Width() / (nScreenindex))*j + 3,
				(Rect.Height() / (nScreenindex))*i + 3,
				(Rect.Width() / nScreenindex) + (6 * -1),
				(Rect.Height() / nScreenindex) + (6 * -1) - ((Rect.Height() / nScreenindex) - (6 * -1) - SCREEN_TITLE_BAR_HEAGHT));

			//ALL SHOW
			pScreenData->pScreenHead->ShowWindow(SW_SHOW);
			pScreenData->pScreenView->ShowWindow(SW_SHOW);
			
			nView++;
		}	
	}


	//PAGE UPDATE
	double dPageNum = (double)MAX_SCREEN_CNT / (double)(nScreenindex*nScreenindex);
	CString str;
	str.Format("%02d  /  %02.0f", m_nStartPage, ceil(dPageNum)); //ceil (올림) , floor (반올림/내림)
	pMain->GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(str);

	return 	pScreenData->pScreenView;
}

int CScreenbase::GetJumpPage(int nScreenindex, E_SCREEN_PAGE_TYPE ePage)
{
	CRect Rect, ViewRect;
	GetClientRect(&Rect);

	CSampleScreenDlg* pMain = (CSampleScreenDlg*)m_pParent;
	PositionData*	pScreenData = NULL;
	
	switch(ePage)
	{
		//-> Next
		case E_SCREEN_NEXT :	
			m_nStartPage++;	
			m_nStartIndex += nScreenindex * nScreenindex;	break;

		//-> Prev
		case E_SCREEN_PREV :	
			m_nStartPage--;	
			m_nStartIndex -= nScreenindex * nScreenindex;	break;
	}
	

	/*모든 스크린 숨기기*/
	for (int j = 0; j < MAX_SCREEN_CNT; j++)
	{
		pScreenData = m_listScreen.GetAt(m_listScreen.FindIndex(j));
		pScreenData->pScreenView->ShowWindow(SW_HIDE);
		pScreenData->pScreenHead->ShowWindow(SW_HIDE);
	}

	//포커스(초록색 테두리) 삭제 조건
	if (m_pClick != NULL)
	{
		//PREV
		if(ePage == E_SCREEN_PREV)
		{
			if(m_pClick->pScreenView->m_nNumber < nScreenindex * nScreenindex)
				m_pClick = NULL;
			else
			{
				
				pScreenData = m_listScreen.GetAt(m_listScreen.FindIndex(m_pClick->pScreenView->m_nNumber - (nScreenindex * nScreenindex) - 1));
				m_pClick = pScreenData;
				m_pClick->pScreenView->m_bDClink = false;
			}
		//NEXT
		}else if (ePage == E_SCREEN_NEXT)
		{
			if (m_pClick->pScreenView->m_nNumber + (nScreenindex * nScreenindex) <= MAX_SCREEN_CNT)
			{
				pScreenData = m_listScreen.GetAt(m_listScreen.FindIndex(m_pClick->pScreenView->m_nNumber + (nScreenindex * nScreenindex) - 1));
				m_pClick = pScreenData;
				m_pClick->pScreenView->m_bDClink = false;
			}
			else
				m_pClick = NULL;
		}
	}
	
	/*  스크린 열기 */
	int nView = 0;
	for (int i = 0; i<nScreenindex; i++)
	{
		for (int j = 0; j<nScreenindex; j++)
		{
			if (m_nStartIndex + nView >= MAX_SCREEN_CNT || m_nStartIndex < 0)
				break;

			//Screen-View
			pScreenData = m_listScreen.GetAt(m_listScreen.FindIndex(m_nStartIndex + nView));
			pScreenData->nScreenindex = nScreenindex;
			pScreenData->pos.nX = j;
			pScreenData->pos.nY = i;
			pScreenData->pScreenView->MoveWindow((Rect.Width() / (nScreenindex))*j + 3,
				(Rect.Height() / (nScreenindex))*i + 3 + (SCREEN_TITLE_BAR_HEAGHT - 10),
				(Rect.Width() / nScreenindex) + (6 * -1),
				(Rect.Height() / nScreenindex) + (6 * -1) - (SCREEN_TITLE_BAR_HEAGHT - 10));

			//Screen-TitleBar

			pScreenData->pScreenHead->MoveWindow((Rect.Width() / (nScreenindex))*j + 3,
				(Rect.Height() / (nScreenindex))*i + 3,
				(Rect.Width() / nScreenindex) + (6 * -1),
				(Rect.Height() / nScreenindex) + (6 * -1) - ((Rect.Height() / nScreenindex) - (6 * -1) - SCREEN_TITLE_BAR_HEAGHT));

			//ALL SHOW
			pScreenData->pScreenHead->ShowWindow(SW_SHOW);
			pScreenData->pScreenView->ShowWindow(SW_SHOW);
			nView++;
		}
	}

	double dPageNum = (double)MAX_SCREEN_CNT / (double)(nScreenindex*nScreenindex);
	CString str;

	str.Format("%02d  /  %02.0f", m_nStartPage, ceil(dPageNum)); //ceil (올림) , floor (반올림/내림)
	pMain->GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(str);

	Invalidate();
	return 0;
}

HWND CScreenbase::GetScreenHwnd(int index)
{
	PositionData*	pScreenData = NULL;
	pScreenData = m_listScreen.GetAt(m_listScreen.FindIndex(index));
	if (pScreenData == NULL)	AfxMessageBox(_T("ScreenData == NULL"));

	return pScreenData->pScreenView->m_hWnd;
}


CScreenView* CScreenbase::BigScreen(CScreenView* pScreenView)
{
	POSITION pos;
	pos = m_listScreen.GetHeadPosition();
	PositionData* pClient = NULL;

	CRect Rect;
	GetClientRect(&Rect);

	while (pos != NULL)
	{
		pClient = m_listScreen.GetNext(pos);
		if (pClient->pScreenView == pScreenView)
		{
			//Click Pointer 
			m_pClick = pClient;

		
			pClient->pScreenView->ShowWindow(SW_HIDE);
		
			//All Over MoveWindow
			m_pClick->pScreenView->MoveWindow(3, SCREEN_TITLE_BAR_HEAGHT - 7, Rect.Width() - 6, Rect.Height() - (SCREEN_TITLE_BAR_HEAGHT - 5));
			m_pClick->pScreenHead->MoveWindow(3, 3, Rect.Width() - 6, SCREEN_TITLE_BAR_HEAGHT - 12);
			pClient->pScreenView->ShowWindow(SW_SHOW);
		}
		else
		{
			pClient->pScreenView->ShowWindow(SW_HIDE);
			pClient->pScreenHead->ShowWindow(SW_HIDE);
		}
	}
	return m_pClick->pScreenView;
}

void CScreenbase::ScreenDelete()
{
	POSITION pos;
	pos=m_listScreen.GetHeadPosition();
	PositionData* pClient=NULL;

	while(pos !=NULL)
	{
		pClient=m_listScreen.GetNext(pos);
		if(pClient !=NULL)
		{
			pClient->pScreenView->Close();
			pClient->pScreenView->DestroyWindow();

			delete pClient->pScreenView;
			pClient->pScreenView=NULL;

			delete pClient->pScreenHead;
			pClient->pScreenHead = NULL;

			delete pClient;
			pClient=NULL;
		}
	}
	m_listScreen.RemoveAll();
}

void CScreenbase::OnClickMsg(CScreenView* pScreenView)
{
	POSITION pos;
	pos=m_listScreen.GetHeadPosition();
	PositionData* pClient=NULL;

	while(pos !=NULL)
	{
		pClient=m_listScreen.GetNext(pos);
		if(pClient->pScreenView == pScreenView)
		{
			m_pClick=pClient;
			Invalidate();
		}
	}
}

BOOL CScreenbase::OnEraseBkgnd(CDC* pDC)
{
	return FALSE/*CWnd::OnEraseBkgnd(pDC)*/;
}


bool CScreenbase::IsMaxPageScreenCheck(int nIndex)
{
	double dPageNum = (double)MAX_SCREEN_CNT / (double)(nIndex*nIndex);
	if (m_nStartPage < dPageNum)
		return false;
	else
		return true;
}

bool CScreenbase::IsMinPageScreenCheck()
{
	if (m_nStartPage > 1)
		return false;
	else
		return true;
}

void CScreenbase::OnPaint()
{
	CPaintDC dc(this);

	CRect rcDlg;

	CDC memDC;
	CBitmap bitmap, *pOldBitmap = NULL;

	GetClientRect(&rcDlg);

	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rcDlg.right, rcDlg.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.FillSolidRect(&rcDlg, RGB(255, 255, 255));

	CPen pen;
	CPen* oldPen;

	pen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	oldPen = memDC.SelectObject(&pen);


	if (m_pClick != NULL)
	{
		if (m_pClick->pScreenView->m_bDClink)
		{
			memDC.MoveTo(0, 0);
			memDC.LineTo((rcDlg.Width()), 0);
			memDC.LineTo((rcDlg.Width()), (rcDlg.Height()));
			memDC.LineTo(0, (rcDlg.Height()));
			memDC.LineTo(0, 0);
		}
		else
		{
			memDC.MoveTo((rcDlg.Width() / m_pClick->nScreenindex)*m_pClick->pos.nX, (rcDlg.Height() / m_pClick->nScreenindex)*m_pClick->pos.nY);
			memDC.LineTo((rcDlg.Width() / m_pClick->nScreenindex)*(m_pClick->pos.nX + 1), (rcDlg.Height() / m_pClick->nScreenindex)*m_pClick->pos.nY);
			memDC.LineTo((rcDlg.Width() / m_pClick->nScreenindex)*(m_pClick->pos.nX + 1), (rcDlg.Height() / m_pClick->nScreenindex)*(m_pClick->pos.nY + 1));
			memDC.LineTo((rcDlg.Width() / m_pClick->nScreenindex)*m_pClick->pos.nX, (rcDlg.Height() / m_pClick->nScreenindex)*(m_pClick->pos.nY + 1));
			memDC.LineTo((rcDlg.Width() / m_pClick->nScreenindex)*m_pClick->pos.nX, (rcDlg.Height() / m_pClick->nScreenindex)*m_pClick->pos.nY);
		}
	}


	memDC.SelectObject(oldPen);
	pen.DeleteObject();
	dc.BitBlt(0, 0, rcDlg.right, rcDlg.bottom, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

}