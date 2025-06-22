#pragma once
#include "afxdialogex.h"


// ConfigDialog dialog

class ConfigDialog : public TGDialog
{
	DECLARE_DYNAMIC(ConfigDialog)

public:
	ConfigDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConfigDialog();


public:   
	// assistant functions
	void initConfigList();
	void refreshVarCombo();
	void refreshConfigList();

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
	CEdit m_paramEdit;
	CComboBox m_varCombo;


private:
	DataManager* pDataManager; //local manager pointers
};
