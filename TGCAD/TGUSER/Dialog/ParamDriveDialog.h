#pragma once
#include "afxdialogex.h"
#include "../../TGMANAGER/CEditNumberOnlyManager.h"
#include "../../TGDIALOGS/TGDialog.h"
#include "../../TGMANAGER/DataManager.h"
#include "../../TGMANAGER/VariableManager.h"

// ParamDriveDialog dialog

class ParamDriveDialog : public TGDialog
{
    DECLARE_DYNAMIC(ParamDriveDialog)

public:
    ParamDriveDialog(CWnd* pParent = nullptr);   // 构造函数
    virtual ~ParamDriveDialog();
    BOOL OnInitDialog();//初始化Dialog
	void HideControls(int nID); //隐藏所有控件
	void ShowControls(int nID); //依据数量显示当前的所有控件

    DataManager* pDataManager;
    VariableManager* pVarManager;

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PARAM_DRIVE_DIALOG };
#endif

protected:
    // 绑定自定义编辑控件变量
    CEditNumberOnlyManager m_editVal1;
    CEditNumberOnlyManager m_editVal2;
    CEditNumberOnlyManager m_editVal3;
    CEditNumberOnlyManager m_editVal4;
    CEditNumberOnlyManager m_editVal5;


    virtual void DoDataExchange(CDataExchange* pDX); // 绑定控件
    DECLARE_MESSAGE_MAP()

    // =============== 功能函数区 =================
private:
    // 
    //===== 初始化Dialog功能函数 ===== 
    // ---隐藏控件-
    void HideGroupBox(int index);
    void HideParamLabel(int index);
    void HideParamEdit(int index);
    void HideValLabel(int index);
    void HideValEdit(int index);
    void HideUnitLabel(int index);
    // ---显示控件---
    //显示 Group Box
    void ShowGroupBox(int index);
    //显示参数名静态文本
    void ShowParamLabel(int index);
    //显示参数名输入框
    void ShowParamEdit(int index);
    // 显示值静态文本
    void ShowValLabel(int index);
    //显示值输入框
    void ShowValEdit(int index);
    //显示单位mm静态文本
    void ShowUnitLabel(int index);

    
    //----- 更改参数功能函数 ------
    double GetEditDoubleValue(int nID);

public:
    // 获取控件ID映射
    int GetControlID(const std::string& itemId);

    // 按钮响应
    virtual void OnBnOK();
};
