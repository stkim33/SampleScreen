
// SampleScreen.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSampleScreenApp:
// �� Ŭ������ ������ ���ؼ��� SampleScreen.cpp�� �����Ͻʽÿ�.
//

class CSampleScreenApp : public CWinApp
{
public:
	CSampleScreenApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSampleScreenApp theApp;