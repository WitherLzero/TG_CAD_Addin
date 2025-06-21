#pragma once
#include "afxdialogex.h"


// ConfigDialog dialog

class ConfigDialog : public TGDialog
{
	DECLARE_DYNAMIC(ConfigDialog)

public:
	ConfigDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConfigDialog();

	void initConfigList();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_configList;
	virtual BOOL OnInitDialog();
};
