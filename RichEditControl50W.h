// By Jim Dunne http://www.topjimmy.net/tjs
// topjimmy@topjimmy.net
// copyright(C)2005
// if you use all or part of this code, please give me credit somewhere :)
#pragma once
// CRichEditControl50W
class CRichEditControl50W : public CWnd
{
	DECLARE_DYNAMIC(CRichEditControl50W)

protected:
	DECLARE_MESSAGE_MAP()
	CHARRANGE m_crRE50W;
	CHARFORMAT2 m_cfRE50W;
	SETTEXTEX m_st50W;

// Constructors
public:
	CRichEditControl50W();
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//virtual BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect,
	//	CWnd* pParentWnd, UINT nID);

// Attributes
	HINSTANCE m_hInstRichEdit50W;      // handle to MSFTEDIT.DLL
	TEXTRANGEW m_trRE50W;	//TextRangeW structure, for Unicode
	LPSTR m_lpszChar;

	void SetSel50W(long nStartChar, long nEndChar);
	BOOL SetDefaultCharFormat50W(DWORD dwMask, COLORREF crTextColor, DWORD dwEffects, LPTSTR szFaceName, LONG yHeight, COLORREF crBackColor);
	void SetTextTo50WControl(CString csText, int nSTFlags, int nSTCodepage);
	void LimitText50W(int nChars);
	void SetOptions50W(WORD wOp, DWORD dwFlags);
	DWORD SetEventMask50W(DWORD dwEventMask);
	void GetTextRange50W(int ncharrMin, int ncharrMax);

	virtual ~CRichEditControl50W();
protected:
};


