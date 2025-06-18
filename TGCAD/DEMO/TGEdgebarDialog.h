#pragma once
#include "afxcmn.h"
#include <afxdialogex.h>
#include "../resource.h"

class TGEdgebarDialog : public TGDialog
{
	DECLARE_DYNAMIC(TGEdgebarDialog)

public:
	TGEdgebarDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~TGEdgebarDialog();

	// Dialog Data
	enum { IDD = IDD_EDGEBARDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEdgeBar();
	virtual void OnOK();
	virtual void OnCancel();
};
