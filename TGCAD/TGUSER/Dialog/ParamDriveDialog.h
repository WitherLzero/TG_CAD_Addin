#pragma once
#include "afxdialogex.h"
#include "../Data/EditNumberOnly.h"

// ParamDriveDialog dialog

class ParamDriveDialog : public TGDialog
{
    DECLARE_DYNAMIC(ParamDriveDialog)

public:
    ParamDriveDialog(CWnd* pParent = nullptr);   // 构造函数
    virtual ~ParamDriveDialog();
    //BOOL OnInitDialog();//初始化Dialog

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PARAM_DRIVE_DIALOG };
#endif

protected:
    // 绑定自定义编辑控件变量
    CEditNumberOnly m_editVal1;
    CEditNumberOnly m_editVal2;
    CEditNumberOnly m_editVal3;
    CEditNumberOnly m_editVal4;
    CEditNumberOnly m_editVal5;

    virtual void DoDataExchange(CDataExchange* pDX); // 绑定控件
    DECLARE_MESSAGE_MAP()

private:
    // ================ 私有变量区 ================
    CBrush m_brushInvalid;   // 红色背景刷，非法输入用
    CBrush m_brushNormal;    // 白色背景刷，正常输入用
    std::set<int> m_invalidEditIDs;  // 存储非法输入框ID集合

    // =============== 功能函数区 =================
    //----- 初始化Dialog功能函数 ------
    //显示 Group Box
    void ShowGroupBox(int index);
    //显示参数名 静态文本
    void ShowParamLabel(int index);
    //显示 参数名 输入框
    void ShowParamEdit(int index);
    // 显示 值 静态文本
    void ShowValLabel(int index);
    //显示 值 输入框（从文件中获取）
    void ShowValEdit(int index);

    ////----- 输入控制功能函数 ------
    //// 单个输入是否合法
    //bool IsInputValid(const CString& strText);
    //// 高亮非法输入框
    //void HighlightInvalidInputs();
    //// 遍历输入框，检查全部，返回整体合法性
    //bool ValidateAllInputs();
    //HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


public:
    // 获取控件ID映射
    int GetControlID(const std::string& itemId);

    // 按钮响应
    virtual void OnBnOK();
    virtual void OnBnCancel();
};
