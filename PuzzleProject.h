
// PuzzleProject.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPuzzleProjectApp:
// �� Ŭ������ ������ ���ؼ��� PuzzleProject.cpp�� �����Ͻʽÿ�.
//

class CPuzzleProjectApp : public CWinApp
{
public:
	CPuzzleProjectApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPuzzleProjectApp theApp;