
// UpdateVersion.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUpdateVersionApp:
// �йش����ʵ�֣������ UpdateVersion.cpp
//

class CUpdateVersionApp : public CWinApp
{
public:
	CUpdateVersionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUpdateVersionApp theApp;