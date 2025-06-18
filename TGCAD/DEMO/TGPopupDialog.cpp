#include "pch.h"
#include "stdafx.h"
#include "../TGCADApp.h"
#include "afxdialogex.h"
#include "TGPopupDialog.h"

IMPLEMENT_DYNAMIC(TGPopupDialog, TGDialog)

TGPopupDialog::TGPopupDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_POPUPDIALOG, pParent)
{

}

TGPopupDialog::~TGPopupDialog()
{
}

void TGPopupDialog::DoDataExchange(CDataExchange* pDX)
{
	TGDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(TGPopupDialog, TGDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &TGPopupDialog::OnTestButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TGPopupDialog::OnTestButton2)
END_MESSAGE_MAP()

void TGPopupDialog::OnTestButton1()
{
	AfxMessageBox(L"Click Button1");
}

void TGPopupDialog::OnTestButton2()
{
	AfxMessageBox(L"Click Button2");
}

void TGPopupDialog::OnOK()
{
	TGDialog::OnOK();
}

void TGPopupDialog::OnCancel()
{
	TGDialog::OnCancel();
}



