// ParamDriveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TGCADApp.h"
#include "afxdialogex.h"
#include "ParamDriveDialog.h"
#include "../Func/Func.h"
#include <unordered_map>


// ParamDriveDialog dialog

IMPLEMENT_DYNAMIC(ParamDriveDialog, TGDialog)

ParamDriveDialog::ParamDriveDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_PARAM_DRIVE_DIALOG, pParent)
{
    ApplicationPtr pApp = TGCADApp::GetApplication();
    AssemblyDocumentPtr pAssem = pApp->GetActiveDocument();
    pDataManager = TGCADApp::GetTGApp()->GetDataManager();
    pVarManager = TGCADApp::GetTGApp()->GetVarManager();
    if (pVarManager) {
        pVarManager->AttachDoc(pAssem);
    }
}

ParamDriveDialog::~ParamDriveDialog()
{
}

//初始化对话框，需要获取参数组数量
BOOL ParamDriveDialog::OnInitDialog()
{
    TGDialog::OnInitDialog();

    int paramNum = pDataManager->GetBindingCount();

    const int maxGroup = 5;
    if (paramNum > maxGroup)
        paramNum = maxGroup;

    for (int i = 1; i <= paramNum; ++i) {
        ShowGroupBox(i);
        ShowParamLabel(i);
        ShowParamEdit(i);
        ShowValLabel(i);
        ShowValEdit(i);
    }

    return TRUE;
}

void ParamDriveDialog::DoDataExchange(CDataExchange* pDX)
{
    TGDialog::DoDataExchange(pDX);

    // 绑定编辑框控件ID和自定义类成员变量
    DDX_Control(pDX, IDC_EDIT_VAL1, m_editVal1);
    DDX_Control(pDX, IDC_EDIT_VAL2, m_editVal2);
    DDX_Control(pDX, IDC_EDIT_VAL3, m_editVal3);
    DDX_Control(pDX, IDC_EDIT_VAL4, m_editVal4);
    DDX_Control(pDX, IDC_EDIT_VAL5, m_editVal5);
}

BEGIN_MESSAGE_MAP(ParamDriveDialog, TGDialog)
    ON_BN_CLICKED(IDOK, &ParamDriveDialog::OnBnOK)
END_MESSAGE_MAP()


//获取控件ID的函数
int ParamDriveDialog::GetControlID(const std::string& itemId) {
    static const std::unordered_map<std::string, int> controlIDMap = {
        // GroupBox
        {"IDC_PARAM_GROUP1", IDC_PARAM_GROUP1},
        {"IDC_PARAM_GROUP2", IDC_PARAM_GROUP2},
        {"IDC_PARAM_GROUP3", IDC_PARAM_GROUP3},
        {"IDC_PARAM_GROUP4", IDC_PARAM_GROUP4},
        {"IDC_PARAM_GROUP5", IDC_PARAM_GROUP5},

        // Static Param Labels
        {"IDC_STATIC_PARAM1", IDC_STATIC_PARAM1},
        {"IDC_STATIC_PARAM2", IDC_STATIC_PARAM2},
        {"IDC_STATIC_PARAM3", IDC_STATIC_PARAM3},
        {"IDC_STATIC_PARAM4", IDC_STATIC_PARAM4},
        {"IDC_STATIC_PARAM5", IDC_STATIC_PARAM5},

        // Edit Param
        {"IDC_EDIT_PARAM1", IDC_EDIT_PARAM1},
        {"IDC_EDIT_PARAM2", IDC_EDIT_PARAM2},
        {"IDC_EDIT_PARAM3", IDC_EDIT_PARAM3},
        {"IDC_EDIT_PARAM4", IDC_EDIT_PARAM4},
        {"IDC_EDIT_PARAM5", IDC_EDIT_PARAM5},

        // Static Value Labels
        {"IDC_STATIC_VAL1", IDC_STATIC_VAL1},
        {"IDC_STATIC_VAL2", IDC_STATIC_VAL2},
        {"IDC_STATIC_VAL3", IDC_STATIC_VAL3},
        {"IDC_STATIC_VAL4", IDC_STATIC_VAL4},
        {"IDC_STATIC_VAL5", IDC_STATIC_VAL5},

        // Edit Value
        {"IDC_EDIT_VAL1", IDC_EDIT_VAL1},
        {"IDC_EDIT_VAL2", IDC_EDIT_VAL2},
        {"IDC_EDIT_VAL3", IDC_EDIT_VAL3},
        {"IDC_EDIT_VAL4", IDC_EDIT_VAL4},
        {"IDC_EDIT_VAL5", IDC_EDIT_VAL5}
    };

    auto it = controlIDMap.find(itemId);
    if (it != controlIDMap.end()) {
        return it->second;
    }
    else {
        return -1; // ID 未找到
    }
}


//确定按钮
void ParamDriveDialog::OnBnOK() {

    //保存修改数据，在数据管理类实现
    /*SaveAllInputs();*/

    TGDialog::OnOK();
}


//======== 初始化Dialog的功能函数 ========
//显示 Group Box
void ParamDriveDialog::ShowGroupBox(int index)
{
    CString idStr;
    idStr.Format(_T("IDC_PARAM_GROUP%d"), index);
    CT2A asciiStr(idStr);  // 转换为 const char*
    int nID = GetControlID(std::string(asciiStr));

    if (CWnd* pGroup = GetDlgItem(nID))
        pGroup->ShowWindow(TRUE);
}
//显示静态参数文本
void ParamDriveDialog::ShowParamLabel(int index)
{
    CString idStr;
    idStr.Format(_T("IDC_STATIC_PARAM%d"), index);
    CT2A asciiStr(idStr);  // 转换为 const char*
    int nID = GetControlID(std::string(asciiStr));

    if (CWnd* pLabel = GetDlgItem(nID))
        pLabel->ShowWindow(TRUE);
}
//显示参数名输入框
void ParamDriveDialog::ShowParamEdit(int index)
{
    CString idStr;
    idStr.Format(_T("IDC_EDIT_PARAM%d"), index);
    CT2A asciiStr(idStr);  // 转换为 const char*
    int nID = GetControlID(std::string(asciiStr));

    CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(nID));
    if (pEdit) {
        pEdit->ShowWindow(TRUE);
        //获取设置的参数名称
        pEdit->SetWindowTextW(pDataManager->GetAllBindings()[index-1].paramName);
    }
}
//显示值静态文本
void ParamDriveDialog::ShowValLabel(int index)
{
    CString idStr;
    idStr.Format(_T("IDC_STATIC_VAL%d"), index);
    CT2A asciiStr(idStr);  // 转换为 const char*
    int nID = GetControlID(std::string(asciiStr));

    if (CWnd* pLabel = GetDlgItem(nID))
        pLabel->ShowWindow(TRUE);
}

//显示值输入框
void ParamDriveDialog::ShowValEdit(int index)
{
    CString idStr;
    idStr.Format(_T("IDC_EDIT_VAL%d"), index);
    CT2A asciiStr(idStr);
    int nID = GetControlID(std::string(asciiStr));

    if (CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(nID)))
    {
        pEdit->ShowWindow(TRUE);

        CString varName = pDataManager->GetAllBindings()[index - 1].varName;
        double val = pVarManager->GetVarValue(varName);


        CString valStr = Func::DoubleToCString(val);
        pEdit->SetWindowTextW(valStr);
    }
}
