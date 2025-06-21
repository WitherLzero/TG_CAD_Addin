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

void ConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	TGDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_LIST, m_configList);
}


BEGIN_MESSAGE_MAP(ConfigDialog, TGDialog)
END_MESSAGE_MAP()


// ConfigDialog message handlers


BOOL ConfigDialog::OnInitDialog()
{
	TGDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initConfigList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
