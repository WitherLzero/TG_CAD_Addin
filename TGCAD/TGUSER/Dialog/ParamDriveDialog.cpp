// ParamDriveDialog.cpp : implementation file
//

//#include "pch.h"
#include "stdafx.h"
#include "TGCADApp.h"
#include "afxdialogex.h"
#include "ParamDriveDialog.h"


// ParamDriveDialog dialog

IMPLEMENT_DYNAMIC(ParamDriveDialog, TGDialog)

ParamDriveDialog::ParamDriveDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_PARAM_DRIVE_DIALOG, pParent)
{
}

ParamDriveDialog::~ParamDriveDialog()
{
}

void ParamDriveDialog::initConfigList()
{
	////m_configList.ModifyStyle(0£¬LVS_REPORT);
	//m_configList.ModifyStyle(0, LVS_REPORT);

	//m_configList.SetExtendedStyle(m_configList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//m_configList.InsertColumn(0, _T("No."), LVCFMT_LEFT, 100);
	//m_configList.InsertColumn(1, _T("Parameter"), LVCFMT_LEFT, 250);
	//m_configList.InsertColumn(2, _T("Variable"), LVCFMT_LEFT, 250);
}

void ParamDriveDialog::DoDataExchange(CDataExchange* pDX)
{
	/*TGDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_LIST, m_configList);*/
}


BEGIN_MESSAGE_MAP(ParamDriveDialog, TGDialog)
END_MESSAGE_MAP()


// ParamDriveDialog message handlers


BOOL ParamDriveDialog::OnInitDialog()
{
	TGDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initConfigList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
