// MyDialog.cpp : implementation file
//

#include "pch.h"
#include "stdafx.h"
#include "TGCADApp.h"
#include "afxdialogex.h"
#include "MyDialog.h"

#include "TGUSER/Func/Func.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, TGDialog)

MyDialog::MyDialog(CWnd* pParent /*=nullptr*/)
	: TGDialog(IDD_MY_DIALOG, pParent)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	TGDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	ON_BN_CLICKED(IDC_DRAW_MODEL, &MyDialog::OnDrawAndModel)
	ON_BN_CLICKED(IDC_DRAFT, &MyDialog::OnCreateDraft)
END_MESSAGE_MAP()


// MyDialog message handlers


void MyDialog::OnDrawAndModel()
{
	// TODO: Add your control notification handler code here
	Func::_drawAndModel();
	AfxMessageBox(L"Draw and Model completed!");
}

void MyDialog::OnCreateDraft()
{
	// TODO: Add your control notification handler code here
	Func::_createDraft();
	AfxMessageBox(L"Create Draft completed!");
}

void MyDialog::OnOK()
{
	TGDialog::OnOK();
}

void MyDialog::OnCancel()
{
	TGDialog::OnCancel();
}





