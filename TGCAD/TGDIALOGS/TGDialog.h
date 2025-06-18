#pragma once
#include "afxdialogex.h"

// 弹窗界面
class TGDialog : public CDialog
{
public:
	TGDialog(CWnd* pParent = nullptr);
	TGDialog(UINT nIDTemplate, CWnd* pParent = nullptr);

public:

	// 设置/获取弹窗ID
	void SetDialogIDD(UINT nIDD);
	UINT GetDialogIDD();

protected:

	// OK 
	virtual void OnOK();
	// Cancel
	virtual void OnCancel();

private:
	UINT m_nIDD;
};
