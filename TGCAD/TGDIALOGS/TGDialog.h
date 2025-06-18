#pragma once
#include "afxdialogex.h"

// ��������
class TGDialog : public CDialog
{
public:
	TGDialog(CWnd* pParent = nullptr);
	TGDialog(UINT nIDTemplate, CWnd* pParent = nullptr);

public:

	// ����/��ȡ����ID
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
