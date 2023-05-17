// RE50W.h : main header file for the RE50W application
// By Jim Dunne http://www.topjimmy.net/tjs
// topjimmy@topjimmy.net
// copyright(C)2005
// if you use all or part of this code, please give me credit somewhere :)
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CRE50WApp:
// See RE50W.cpp for the implementation of this class
//

class CRE50WApp : public CWinApp
{
public:
	CRE50WApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual void OnFinalRelease();
};

extern CRE50WApp theApp;