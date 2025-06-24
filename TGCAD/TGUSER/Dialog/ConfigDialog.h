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
	CEdit m_paramEdit;
	CComboBox m_varCombo;
	int m_nEditSelIdx;
	virtual BOOL OnInitDialog();

private:
	//local manager pointers
	DataManager* pDataManager; 
	VariableManager* pVarManager;
	BindingList tempList;
public:
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnModify();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnListItemClick(NMHDR* pNMHDR, LRESULT* pResult);

};
