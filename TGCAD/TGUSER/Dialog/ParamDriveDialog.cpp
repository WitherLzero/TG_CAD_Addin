// ParamDriveDialog.cpp : implementation file
//

//#include "pch.h"
#include "stdafx.h"
#include "TGCADApp.h"
#include "afxdialogex.h"
#include "ParamDriveDialog.h"
#include <unordered_map>


// ParamDriveDialog dialog

IMPLEMENT_DYNAMIC(ParamDriveDialog, TGDialog)

ParamDriveDialog::ParamDriveDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_PARAM_DRIVE_DIALOG, pParent)
{

}

ParamDriveDialog::~ParamDriveDialog()
{
}

void ParamDriveDialog::DoDataExchange(CDataExchange* pDX)
{
    /*TGDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CONFIG_LIST, m_configList);*/
}

BEGIN_MESSAGE_MAP(ParamDriveDialog, TGDialog)
    ON_BN_CLICKED(IDOK, &ParamDriveDialog::OnBnOK)
    ON_BN_CLICKED(IDCANCEL, &ParamDriveDialog::OnBnCancel)
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

//需要先实现参数类和参数管理方法
//void ParamDriveDialog::UpdateVisibleControlsByParamCount()
//{
//    const int maxGroup = 5;
//    int paramCount = parameterData::getInstance().getCount();
//
//    if (paramCount > maxGroup)
//        paramCount = maxGroup;
//
//    for (int i = 1; i <= maxGroup; ++i)
//    {
//        // 控件ID字符串拼接
//        CString idStr;
//
//        // Group
//        idStr.Format(_T("IDC_PARAM_GROUP%d"), i);
//        int idGroup = GetControlID(std::string(CT2A(idStr)));
//        if (CWnd* p = GetDlgItem(idGroup))
//            p->ShowWindow(i <= paramCount ? SW_SHOW : SW_HIDE);
//
//        // Param Label
//        idStr.Format(_T("IDC_STATIC_PARAM%d"), i);
//        int idParamLabel = GetControlID(std::string(CT2A(idStr)));
//        if (CWnd* p = GetDlgItem(idParamLabel))
//            p->ShowWindow(i <= paramCount ? SW_SHOW : SW_HIDE);
//
//        // Param Edit
//        idStr.Format(_T("IDC_EDIT_PARAM%d"), i);
//        int idParamEdit = GetControlID(std::string(CT2A(idStr)));
//        if (CWnd* p = GetDlgItem(idParamEdit))
//            p->ShowWindow(i <= paramCount ? SW_SHOW : SW_HIDE);
//
//        // Val Label
//        idStr.Format(_T("IDC_STATIC_VAL%d"), i);
//        int idValLabel = GetControlID(std::string(CT2A(idStr)));
//        if (CWnd* p = GetDlgItem(idValLabel))
//            p->ShowWindow(i <= paramCount ? SW_SHOW : SW_HIDE);
//
//        // Val Edit
//        idStr.Format(_T("IDC_EDIT_VAL%d"), i);
//        int idValEdit = GetControlID(std::string(CT2A(idStr)));
//        if (CWnd* p = GetDlgItem(idValEdit))
//            p->ShowWindow(i <= paramCount ? SW_SHOW : SW_HIDE);
//    }
//}


void ParamDriveDialog::OnBnOK() {
    TGDialog::OnOK();
}


void ParamDriveDialog::OnBnCancel() {
    TGDialog::OnCancel();
}


// ParamDriveDialog message handlers


//BOOL ParamDriveDialog::OnInitDialog()
//{
//	TGDialog::OnInitDialog();
//
//	// TODO:  Add extra initialization here
//	/*initConfigList();*/
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// EXCEPTION: OCX Property Pages should return FALSE
//}
