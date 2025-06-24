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
	ApplicationPtr pApp = TGCADApp::GetApplication();
	AssemblyDocumentPtr pAssem = pApp->GetActiveDocument();
	pDataManager = TGCADApp::GetTGApp()->GetDataManager();
	pVarManager = TGCADApp::GetTGApp()->GetVarManager();
	if (pVarManager) {
		pVarManager->AttachDoc(pAssem);
	}
	tempList = pDataManager->GetAllBindings();
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

void ConfigDialog::refreshVarCombo()
{
	m_varCombo.ResetContent();
	std::vector<CString> varNames;
	if (pVarManager)
		pVarManager->GetVarNames(varNames);
	for (const auto& v : varNames)
		m_varCombo.AddString(v);

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
	ON_BN_CLICKED(IDC_ADD, &ConfigDialog::OnAdd)
END_MESSAGE_MAP()


// ConfigDialog message handlers


BOOL ConfigDialog::OnInitDialog()
{
	TGDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initConfigList();
	refreshConfigList();
	refreshVarCombo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void ConfigDialog::OnAdd()
{	
	// TODO: Add your control notification handler code here
	CString paramName, varName;

	// 获取窗口所输入的参数名和选择的变量
	m_paramEdit.GetWindowTextW(paramName);
	int sel = m_varCombo.GetCurSel();

	if (sel == CB_ERR) {
		AfxMessageBox(_T("请选择需要绑定的变量！"));
		return;
	}
	
	m_varCombo.GetLBText(sel, varName);

	// 校验
	if (paramName.IsEmpty()) {
		AfxMessageBox(_T("请输入参数名！"));
		return;
	}
	if (pDataManager->IsParamNameExist(paramName)) {
		AfxMessageBox(_T("参数名已存在！"));
		return;
	}
	if (pDataManager->IsVarNameBound(varName)) {
		AfxMessageBox(_T("该变量已被绑定！"));
		return;
	}

	// 添加
	if (!pDataManager->AddBinding(paramName, varName)) {
		AfxMessageBox(_T("添加失败！"));
		return;
	}

	// 刷新
	refreshConfigList();

}


void ConfigDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	TGDialog::OnOK();
}


void ConfigDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if (pDataManager) {
		pDataManager->SetAllBindings(tempList);
	}
	TGDialog::OnCancel();
}
