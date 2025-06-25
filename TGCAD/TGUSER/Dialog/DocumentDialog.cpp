// DocumentDialog.cpp : implementation file
//

#include "pch.h"
#include "stdafx.h"
#include "TGCADApp.h"
#include "afxdialogex.h"
#include "DocumentDialog.h"
#include <afxdlgs.h>

#include "TGUSER/ConfigCmd.h"


// DocumentDialog dialog

IMPLEMENT_DYNAMIC(DocumentDialog, TGDialog)

DocumentDialog::DocumentDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_DOC_DIALOG, pParent)
{

}

DocumentDialog::~DocumentDialog()
{
}

void DocumentDialog::DoDataExchange(CDataExchange* pDX)
{
	TGDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DocumentDialog, TGDialog)
	ON_BN_CLICKED(IDC_SAVE, &DocumentDialog::OnSave)
	ON_BN_CLICKED(IDC_LOAD, &DocumentDialog::OnLoad)
END_MESSAGE_MAP()


// DocumentDialog message handlers


void DocumentDialog::OnSave()
{
	// TODO: Add your control notification handler code here
	// 1. 保存当前文档
	AssemblyDocumentPtr pAssem = TGCADApp::GetApplication()->GetActiveDocument();
	if (!pAssem) {
		AfxMessageBox(_T("请先打开或新建一个装配文档！"));
		return;
	}
	pAssem->Save();

	// 2. 参数绑定保存
	DataManager* pDataManager = TGCADApp::GetTGApp()->GetDataManager();
	if (pDataManager && pDataManager->GetBindingCount() > 0) {
		if (pDataManager->SaveConfigForDoc(pAssem)) {
			AfxMessageBox(_T("参数绑定关系保存成功！"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			AfxMessageBox(_T("参数绑定关系保存失败！"), MB_OK | MB_ICONERROR);
		}
	}

	AfxMessageBox(_T("文档保存完成！"), MB_OK | MB_ICONINFORMATION);
}


void DocumentDialog::OnLoad()
{
	// TODO: Add your control notification handler code here
    DocumentsPtr pDocs = TGCADApp::GetApplication()->GetDocuments();
    if (!pDocs) {
        AfxMessageBox(_T("ERROR!"), MB_OK | MB_ICONERROR);
        return;
    }

    // 1. 检查当前是否已有打开的装配文档
    AssemblyDocumentPtr pAsmDoc = nullptr;
    ApplicationPtr pApp = TGCADApp::GetApplication();
    if (pApp) {
        pAsmDoc = pApp->GetActiveDocument();
    }

    if (!pAsmDoc) {
        // 没有则弹出打开对话框
        CString defaultDir = _T("");
        CString title = _T("请选择要打开的装配文档");
        _variant_t optionFlags = TGConstants::GetFileOpenOptions::DisableReadOnly;
        pAsmDoc = pDocs->OpenWithFileOpenDialog((LPCWSTR)defaultDir, (LPCWSTR)title, optionFlags);
        if (!pAsmDoc) {
            AfxMessageBox(_T("未能打开装配文档，操作取消。"), MB_OK | MB_ICONWARNING);
            return;
        }
        AfxMessageBox(_T("装配文档打开成功！"), MB_OK | MB_ICONINFORMATION);
    }

    CString fullPath = (LPCWSTR)pAsmDoc->GetFullName();
    CString docDir = (LPCWSTR)pAsmDoc->GetPath();

    // 2. 询问是否加载参数配置文件
    int result = AfxMessageBox(_T("是否需要加载该文档的参数配置文件？"), MB_OKCANCEL | MB_ICONQUESTION);
    if (result != IDOK) {
        AfxMessageBox(_T("已完成装配文档加载。"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    // 3. 弹出文件对话框，默认定位到装配文档目录
    CString configFile;
    
    CString filter = _T("配置文件 (*.txt)|*.txt||");
    CFileDialog fileDlg(TRUE, _T("txt"), _T("param_mapping.txt"), OFN_FILEMUSTEXIST, filter, nullptr);

        // 用CString的GetBuffer安全设置初始目录
    TCHAR buf[MAX_PATH] = { 0 };
    _tcscpy_s(buf, MAX_PATH, docDir); // MAX_PATH安全
    fileDlg.m_ofn.lpstrInitialDir = buf;
    fileDlg.m_ofn.lpstrTitle = _T("请选择要加载的参数配置文件");

    if (fileDlg.DoModal() == IDOK) {
        configFile = fileDlg.GetPathName();
    }
    else {
        AfxMessageBox(_T("未选择参数配置文件，操作取消。"), MB_OK | MB_ICONWARNING);
        return;
    }
   

    // 4. 加载配置
    DataManager* pDataManager = TGCADApp::GetTGApp()->GetDataManager();
    if (pDataManager && pDataManager->LoadFromFile(configFile)) {
        AfxMessageBox(_T("参数绑定配置加载成功！"), MB_OK | MB_ICONINFORMATION);

    }
    else {
        AfxMessageBox(_T("加载参数配置文件失败！"), MB_OK | MB_ICONERROR);
    }
}
