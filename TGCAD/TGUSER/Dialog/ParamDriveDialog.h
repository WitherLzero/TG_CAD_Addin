#pragma once
#include "afxdialogex.h"


// ParamDriveDialog dialog

class ParamDriveDialog : public TGDialog
{
	DECLARE_DYNAMIC(ParamDriveDialog)

public:
	ParamDriveDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ParamDriveDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAM_DRIVE_DIALOG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	//CListCtrl m_configList;
	//virtual BOOL OnInitDialog();

	//获取控件ID
	int GetControlID(const std::string& itemId);
	//更新控件数量，控制为5个
	void UpdateVisibleControlsByParamCount();

	//对应确定和取消按键的操作
	virtual void OnBnOK();
	virtual void OnBnCancel();
};
