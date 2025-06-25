#pragma once
#include "afxdialogex.h"


// DocumentDialog dialog

class DocumentDialog : public TGDialog
{
	DECLARE_DYNAMIC(DocumentDialog)

public:
	DocumentDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DocumentDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSave();
	afx_msg void OnLoad();
};
