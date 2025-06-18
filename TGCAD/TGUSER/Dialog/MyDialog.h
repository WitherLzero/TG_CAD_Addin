#pragma once
#include "afxdialogex.h"


// MyDialog dialog
class MyDialog : public TGDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawAndModel();
	afx_msg void OnCreateDraft();
	virtual void OnOK();
	virtual void OnCancel();
};
