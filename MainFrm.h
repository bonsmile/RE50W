// MainFrm.h : interface of the CMainFrame class
// By Jim Dunne http://www.topjimmy.net/tjs
// topjimmy@topjimmy.net
// copyright(C)2005
// if you use all or part of this code, please give me credit somewhere :)


#pragma once

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:
	void CMainFrame::PrintStringTo50WControl();

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CString m_csMessage;
	CHARRANGE m_crStatus;
	CRichEditControl50W m_REControl50W;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void CMainFrame::OnUpdatePopupCopy(CCmdUI* pCmdUI); 
	afx_msg void CMainFrame::OnPopupCopy(); 
	afx_msg void CMainFrame::OnPopupCut(); 
	afx_msg void CMainFrame::OnPopupUndo();
	afx_msg void CMainFrame::OnUpdatePopupUndo(CCmdUI* pCmdUI); 
	afx_msg void CMainFrame::OnPopupPaste(); 
	afx_msg void CMainFrame::OnPopupStatusSelectall();
	afx_msg void CMainFrame::OnPopupCleartext();
	afx_msg void CMainFrame::OnUpdatePopupCleartext(CCmdUI* pCmdUI); 
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


