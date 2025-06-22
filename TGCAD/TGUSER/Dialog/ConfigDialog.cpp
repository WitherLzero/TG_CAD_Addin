// ConfigDialog.cpp : implementation file
//

#include "pch.h"
#include "stdafx.h"
#include "TGCADApp.h"
#include "afxdialogex.h"
#include "ConfigDialog.h"


// ConfigDialog dialog

IMPLEMENT_DYNAMIC(ConfigDialog, TGDialog)

ConfigDialog::ConfigDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_CONFIG_DIALOG, pParent)
{
	pDataManager = TGCADApp::GetTGApp()->GetDataManager();
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::initConfigList()
{
	//m_configList.ModifyStyle(0，LVS_REPORT);
	m_configList.ModifyStyle(0, LVS_REPORT);

	m_configList.SetExtendedStyle(m_configList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_configList.InsertColumn(0, _T("No."), LVCFMT_LEFT, 100);
	m_configList.InsertColumn(1, _T("Parameter"), LVCFMT_LEFT, 250);
	m_configList.InsertColumn(2, _T("Variable"), LVCFMT_LEFT, 250);
}

void ConfigDialog::refreshConfigList()
{
	m_configList.DeleteAllItems();
	if (!pDataManager) {
		return;
	}
	const auto& binds = pDataManager->GetAllBindings();

	for (int i = 0; i < (int)binds.size(); ++i) {
		const auto& b = binds[i];
		CString idxStr;
		idxStr.Format(_T("%d"), i + 1);
		int nItem = m_configList.InsertItem(i, idxStr);
		m_configList.SetItemText(nItem, 1, b.paramName);
		m_configList.SetItemText(nItem, 2, b.varName);

	}
}

void ConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	TGDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_LIST, m_configList);
	DDX_Control(pDX, IDC_PARAM_EDIT, m_paramEdit);
	DDX_Control(pDX, IDC_VAR_COMBO, m_varCombo);
}


BEGIN_MESSAGE_MAP(ConfigDialog, TGDialog)
END_MESSAGE_MAP()


// ConfigDialog message handlers


BOOL ConfigDialog::OnInitDialog()
{
	TGDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initConfigList();
	refreshConfigList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
