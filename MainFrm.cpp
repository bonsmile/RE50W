// MainFrm.cpp : implementation of the CMainFrame class
// By Jim Dunne http://www.topjimmy.net/tjs
// topjimmy@topjimmy.net
// copyright(C)2005
// if you use all or part of this code, please give me credit somewhere :)

#include "stdafx.h"
#include "RE50W.h"
#include "RichEditControl50W.h"
//#include <AFXPRIV.H>

#include "MainFrm.h"
#include ".\mainfrm.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_EDIT_COPY, OnPopupCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdatePopupCopy)

	ON_COMMAND(ID_EDIT_CUT, OnPopupCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdatePopupCopy)

	ON_COMMAND(ID_EDIT_PASTE, OnPopupPaste)

	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnPopupCleartext)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdatePopupCleartext)

	ON_COMMAND(ID_EDIT_SELECT_ALL, OnPopupStatusSelectall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdatePopupCleartext)

	ON_COMMAND(ID_EDIT_UNDO, OnPopupUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdatePopupUndo)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Set Options for the Rich Edit Control 
	DWORD w_RichEd = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_MULTILINE;

	//Create Rich Edit Control to fill view
	if (!m_REControl50W.Create(w_RichEd, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Send Initialization messages to the window
	m_REControl50W.LimitText50W(-1);	//Set the control to accept the maximum amount of text

	DWORD REOptions = (ECO_AUTOVSCROLL | ECO_AUTOHSCROLL | ECO_NOHIDESEL | ECO_SAVESEL | ECO_SELECTIONBAR);

	//Set other options
	m_REControl50W.SetOptions50W(	
		ECOOP_OR,	//The type of operation
		REOptions );	//Options

	//Set the contol to automatically detect URLs
	m_REControl50W.SendMessage( EM_AUTOURLDETECT, TRUE, 0);  

	//Set the event masks for the rich edit control
	m_REControl50W.SetEventMask50W(
		ENM_SELCHANGE | ENM_LINK	//New event mask for the rich edit control
		);

	//Set the default character formatting...see RichEditControl50W.cpp for function definition
	m_REControl50W.SetDefaultCharFormat50W(	
		CFM_COLOR | CFM_BOLD | CFM_SIZE | CFM_FACE | CFM_BACKCOLOR,	//Mask options 
		RGB(0,0,0),			//Text Color	
		!CFE_BOLD,			//Text Effects
		"Trebuchet MS",		//Font name
		200,				//Font yHeight
		RGB(255,255,255));	//Font background color

	//Text for RE Control Example, has to be in RTF format
	m_csMessage = "{\\rtf1 RE50W by Jim Dunne Copyright (C) 2005\\par http://www.topjimmy.net/tjs \\par {\\field{\\*\\fldinst{HYPERLINK mailto:jim@dunnes.net }}{\\fldrslt{\\cf1\\ul jim@dunnes.net}}}}";

	m_REControl50W.SetSel50W(-1, -1);

	m_REControl50W.SetTextTo50WControl(m_csMessage,	//Write the text in m_csMessage to the RE Control 
		ST_SELECTION,	//	SETTEXT flags value
		1200);			//	SETTEXT codepage value

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	//Need ENLINK structure in order to mine the contents of lParam
	ENLINK  *p_enRE50W;	 
	//Put contents of lParam into ENLINK structure
	p_enRE50W = (ENLINK *)lParam;	

	//If ENLINK exists and the message sent was left mouse button up..
	if(p_enRE50W && p_enRE50W->msg == WM_LBUTTONUP)
	{
		m_REControl50W.GetTextRange50W(p_enRE50W->chrg.cpMin, p_enRE50W->chrg.cpMax);

		//Call ShellExecute to perform default action based on the type of hyperlink
		ShellExecute(m_hWnd, "Open", m_REControl50W.m_lpszChar, NULL, NULL, SW_MAXIMIZE);
	}

	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_REControl50W.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// Let the Rich Edit Control have first crack at the command
	if (m_REControl50W.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_REPOPUP))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x , point.y , AfxGetMainWnd());
	}
}
void CMainFrame::OnPopupCopy() 
{
    m_REControl50W.SendMessage(WM_COPY, 0, 0);
}

void CMainFrame::OnUpdatePopupCopy(CCmdUI* pCmdUI) 
{
    //	Activate the "Copy" menu item if there is a selection
	m_REControl50W.SendMessage(EM_EXGETSEL, 0, (LPARAM)&m_crStatus); 
	//	CHARRANGE m_crStatus declared in MainFrame.h
	pCmdUI->Enable(m_crStatus.cpMin != m_crStatus.cpMax);  
}
void CMainFrame::OnPopupCut() 
{
	m_REControl50W.SendMessage(WM_CUT, 0, 0);	
}

void CMainFrame::OnPopupUndo() 
{
    m_REControl50W.SendMessage(WM_UNDO, 0, 0);
}

void CMainFrame::OnUpdatePopupUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((m_REControl50W.SendMessage(EM_CANUNDO, 0, 0)) != 0);
}

DWORD CALLBACK EditStreamOutCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	HANDLE hFile = (HANDLE)dwCookie;
	DWORD NumberOfBytesWritten;
	if (!WriteFile(hFile, pbBuff, cb, &NumberOfBytesWritten, NULL))
	{
		//handle errors
		return 1;
		// or perhaps return GetLastError();
	}
	*pcb = NumberOfBytesWritten;
	return 0;
}

void CMainFrame::OnPopupPaste() 
{
	HANDLE hFile = CreateFileW(L"C:/test.html", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//handle errors
	}
	// https://devblogs.microsoft.com/math-in-office/richedit-html-support/
	EDITSTREAM es;
	es.dwCookie = (DWORD_PTR)hFile;
	es.pfnCallback = EditStreamOutCallback;
	//m_REControl50W.StreamOut(0x00100000 | 0x0008, es);
	m_REControl50W.SendMessage(EM_STREAMOUT, 0x00100000 | 0x0008, (LPARAM)&es);

    //m_REControl50W.SendMessage(WM_PASTE, 0, 0);
	CloseHandle(hFile);
}

void CMainFrame::OnPopupStatusSelectall() 
{
	m_crStatus.cpMin = 0;
	m_crStatus.cpMax = -1;
    m_REControl50W.SendMessage(EM_EXSETSEL,0, (LPARAM)&m_crStatus);
}

void CMainFrame::OnUpdatePopupCleartext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_REControl50W.SendMessage(WM_GETTEXTLENGTH, NULL, NULL) != 0);
}

void CMainFrame::OnPopupCleartext() 
{
	OnPopupStatusSelectall();
    m_REControl50W.SendMessage(WM_CLEAR, 0, 0);
}

