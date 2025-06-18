#pragma once
#include "afxdialogex.h"

class TGPopupDialog : public TGDialog
{
	DECLARE_DYNAMIC(TGPopupDialog)

public:
	TGPopupDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TGPopupDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POPUPDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestButton1();
	afx_msg void OnTestButton2();
	virtual void OnOK();
	virtual void OnCancel();
};

