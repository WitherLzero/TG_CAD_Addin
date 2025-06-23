// ParamDriveDialog.cpp : implementation file
//

//#include "pch.h"
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
    m_brushInvalid.CreateSolidBrush(RGB(255, 200, 200)); // 红色
    m_brushNormal.CreateSolidBrush(RGB(255, 255, 255));  // 白色
}

ParamDriveDialog::~ParamDriveDialog()
{
}

//初始化对话框，需要获取参数组数量
//BOOL ParamDriveDialog::OnInitDialog()
//{
//    TGDialog::OnInitDialog();
//
//    int paramNum = parameterData::getInstance().getCount();
//
//    if (paramNum <= 0) {
//        AfxMessageBox(L"请先完成参数配置！");
//        EndDialog(IDCANCEL);
//        return FALSE;  // 中断初始化
//    }
//
//    const int maxGroup = 5;
//    if (paramNum > maxGroup)
//        paramNum = maxGroup;
//
//    for (int i = 1; i <= paramNum; ++i) {
//        ShowGroupBox(i);
//        ShowParamLabel(i);
//        ShowParamEdit(i);
//        ShowValLabel(i);
//        ShowValEdit(i);
//    }
//
//    return TRUE;
//}

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


//确定按钮
void ParamDriveDialog::OnBnOK() {

    /*if (!ValidateAllInputs())
    {
        HighlightInvalidInputs();
        AfxMessageBox(_T("存在非法输入，已高亮显示。只允许输入数字和一个小数点"));
        return;
    }*/
    //保存修改数据，在数据管理类实现
    /*SaveAllInputs();*/
    TGDialog::OnOK();
}


void ParamDriveDialog::OnBnCancel() {
    TGDialog::OnCancel();
}


//======== 初始化Dialog的功能函数 ========
////显示 Group Box
//void ParamDriveDialog::ShowGroupBox(int index)
//{
//    CString idStr;
//    idStr.Format(_T("IDC_PARAM_GROUP%d"), index);
//    CT2A asciiStr(idStr);  // 转换为 const char*
//    int nID = GetControlID(std::string(asciiStr));
//
//    if (CWnd* pGroup = GetDlgItem(nID))
//        pGroup->ShowWindow(TRUE);
//}
////显示静态参数文本
//void ParamDriveDialog::ShowParamLabel(int index)
//{
//    CString idStr;
//    idStr.Format(_T("IDC_STATIC_PARAM%d"), index);
//    CT2A asciiStr(idStr);  // 转换为 const char*
//    int nID = GetControlID(std::string(asciiStr));
//
//    if (CWnd* pLabel = GetDlgItem(nID))
//        pLabel->ShowWindow(TRUE);
//}
//显示 参数名 输入框
//void ParamDriveDialog::ShowParamEdit(int index)
//{
//    CString idStr;
//    idStr.Format(_T("IDC_EDIT_PARAM%d"), index);
//    CT2A asciiStr(idStr);  // 转换为 const char*
//    int nID = GetControlID(std::string(asciiStr));
//
//    CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(nID));
//    if (pEdit) {
//        pEdit->ShowWindow(TRUE);
//        pEdit->SetWindowTextW(parameterData::getInstance().getParameter(index - 1));
//    }
//}
////显示 值 静态文本
//void ParamDriveDialog::ShowValLabel(int index)
//{
//    CString idStr;
//    idStr.Format(_T("IDC_STATIC_VAL%d"), index);
//    CT2A asciiStr(idStr);  // 转换为 const char*
//    int nID = GetControlID(std::string(asciiStr));
//
//    if (CWnd* pLabel = GetDlgItem(nID))
//        pLabel->ShowWindow(TRUE);
//}
//显示值输入框
//void ParamDriveDialog::ShowValEdit(int index)
//{
//    CString idStr;
//    idStr.Format(_T("IDC_EDIT_VAL%d"), index);
//    CT2A asciiStr(idStr);  // 转换为 const char*
//    int nID = GetControlID(std::string(asciiStr));
//
//    CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(nID));
//    if (pEdit) {
//        pEdit->ShowWindow(TRUE);
//
//        double val = parameterData::getInstance().getVariableValue(index - 1);
//        CString valStr = Func::DoubleToCString(val);
//        pEdit->SetWindowTextW(valStr);
//    }
//}


//======== 控制值输入功能函数 ========
// 检查单个输入是否合法
//bool ParamDriveDialog::IsInputValid(const CString& strText)
//{
//    int dotCount = 0;
//    for (int j = 0; j < strText.GetLength(); ++j)
//    {
//        if (strText[j] == '.')
//        {
//            if (++dotCount > 1)
//                return false;
//        }
//        else if (!isdigit(static_cast<unsigned char>(strText[j])))
//        {
//            return false;
//        }
//    }
//    return true;
//}
//遍历并校验全部输入框，返回整体合法性（需要先实现数据管理类）
//bool ParamDriveDialog::ValidateAllInputs()
//{
//    int paramNum = parameterData::getInstance().getCount();
//    m_invalidEditIDs.clear();
//    bool overallValid = true;
//
//    for (int i = 1; i <= paramNum; ++i)
//    {
//        CString idStr;
//        idStr.Format(_T("IDC_EDIT_VAL%d"), i);
//        int nID = GetControlID(std::string(CT2A(idStr)));
//        if (nID == -1) continue;
//
//        CString strText;
//        GetDlgItemText(nID, strText);
//
//        if (!IsInputValid(strText))
//        {
//            m_invalidEditIDs.insert(nID);
//            overallValid = false;
//        }
//        else
//        {
//            double value = _tstof(strText);
//            parameterData::getInstance().setVariableValue(value, i - 1);
//            parameterData::getInstance().updatePtr(i - 1);
//        }
//    }
//
//    return overallValid;
//}
 // 触发重绘，OnCtlColor自动变色
//void ParamDriveDialog::HighlightInvalidInputs()
//{
//    Invalidate();
//}
// 重写 OnCtlColor 函数来改变控件背景颜色
//HBRUSH ParamDriveDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//    int ctrlID = pWnd->GetDlgCtrlID();
//
//    // 判断该控件ID是否在非法输入集合中
//    if (m_invalidEditIDs.find(ctrlID) != m_invalidEditIDs.end())
//    {
//        // 设置背景颜色为红色
//        pDC->SetBkColor(RGB(255, 200, 200));
//
//        // 返回你事先准备好的红色画刷，控件背景会显示成红色
//        return m_brushInvalid;
//    }