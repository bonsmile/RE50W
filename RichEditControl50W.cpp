// RichEditControl50W.cpp : implementation file
// By Jim Dunne http://www.topjimmy.net/tjs
// topjimmy@topjimmy.net
// copyright(C)2005
// if you use all or part of this code, please give me credit somewhere :)
#include "stdafx.h"
//#include "RE50W.h"
#include "RichEditControl50W.h"
#include ".\richeditcontrol50w.h"

// CRichEditControl50W
IMPLEMENT_DYNAMIC(CRichEditControl50W, CWnd)
CRichEditControl50W::CRichEditControl50W()
{
}

CRichEditControl50W::~CRichEditControl50W()
{
	//Free the MSFTEDIT.DLL library
	if(m_hInstRichEdit50W)
		FreeLibrary(m_hInstRichEdit50W);
}

BEGIN_MESSAGE_MAP(CRichEditControl50W, CWnd)
END_MESSAGE_MAP()

BOOL CRichEditControl50W::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	//Load the MSFTEDIT.DLL library
	m_hInstRichEdit50W = LoadLibrary("RICHED20_custom.DLL");
	if (!m_hInstRichEdit50W)
	{
		AfxMessageBox("MSFTEDIT.DLL Didn't Load");
		return(0);
	}

	CWnd* pWnd = this;
	return pWnd->Create("RichEdit60W", NULL, dwStyle, rect, pParentWnd, nID);
}

void CRichEditControl50W::SetSel50W(long nStartChar, long nEndChar)
{
	m_crRE50W.cpMin = nStartChar;
	m_crRE50W.cpMax = nEndChar;
	SendMessage(EM_EXSETSEL, 0, (LPARAM)&m_crRE50W);
}

BOOL CRichEditControl50W::SetDefaultCharFormat50W(DWORD dwMask, COLORREF crTextColor, DWORD dwEffects, LPTSTR  szFaceName, LONG yHeight, COLORREF crBackColor)
{	//Set the text defaults.  CHARFORMAT2 m_cfStatus is declared in RichEditControl50W.h
	m_cfRE50W.cbSize = sizeof(CHARFORMAT2);
	m_cfRE50W.dwMask = dwMask ;
	m_cfRE50W.crTextColor = crTextColor;
	m_cfRE50W.dwEffects = dwEffects;
	::lstrcpy(m_cfRE50W.szFaceName, szFaceName);
	m_cfRE50W.yHeight = yHeight;
	m_cfRE50W.crBackColor = crBackColor;

	return (BOOL) SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&m_cfRE50W);
}

void CRichEditControl50W::SetTextTo50WControl(CString csText, int nSTFlags, int nSTCodepage)
{	//Set the options. SETTEXTEX m_st50W declared in RichEditControl50W.h
	m_st50W.codepage = nSTCodepage;	
	m_st50W.flags = nSTFlags;
	SendMessage(EM_SETTEXTEX, (WPARAM)&m_st50W, (LPARAM)(LPCTSTR)csText);
}
void CRichEditControl50W::LimitText50W(int nChars)
{
	SendMessage(EM_LIMITTEXT, nChars, 0);
}

void CRichEditControl50W::SetOptions50W(WORD wOp, DWORD dwFlags)
{
	SendMessage(EM_SETOPTIONS, (WPARAM)wOp, (LPARAM)dwFlags);
}

DWORD CRichEditControl50W::SetEventMask50W(DWORD dwEventMask)
{
	return (DWORD)SendMessage(EM_SETEVENTMASK, 0, dwEventMask);
}

void CRichEditControl50W::GetTextRange50W(int ncharrMin, int ncharrMax)
{
	//Set the CHARRANGE for the trRE50W = the characters sent by ENLINK 
	m_trRE50W.chrg.cpMin = ncharrMin;
	m_trRE50W.chrg.cpMax = ncharrMax;

	//Set the size of the character buffers, + 1 for null character
	int nLength = int((m_trRE50W.chrg.cpMax - m_trRE50W.chrg.cpMin +1));

	//create an ANSI buffer and a Unicode (Wide Character) buffer
	m_lpszChar = new CHAR[nLength];
	LPWSTR lpszWChar = new WCHAR[nLength];

	//Set the trRE50W LPWSTR character buffer = Unicode buffer
	m_trRE50W.lpstrText = lpszWChar;

	//Get the Unicode text
	SendMessage(EM_GETTEXTRANGE, 0,  (LPARAM) &m_trRE50W);  

	// Convert the Unicode RTF text to ANSI.
	WideCharToMultiByte(CP_ACP, 0, lpszWChar, -1, m_lpszChar, nLength, NULL, NULL);

	//Release buffer memory
	delete lpszWChar;

	return;
}

