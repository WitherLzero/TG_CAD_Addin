#include "stdafx.h"
#include "TGEdgebarDialog.h"
#include "../TGCADApp.h"

IMPLEMENT_DYNAMIC(TGEdgebarDialog, TGDialog)

TGEdgebarDialog::TGEdgebarDialog(CWnd* pParent)
	: TGDialog(TGEdgebarDialog::IDD, pParent)
{

}

TGEdgebarDialog::~TGEdgebarDialog()
{
}

void TGEdgebarDialog::DoDataExchange(CDataExchange* pDX)
{
	TGDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TGEdgebarDialog, TGDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &TGEdgebarDialog::OnEdgeBar)
END_MESSAGE_MAP()

void TGEdgebarDialog::OnSize(UINT nType, int cx, int cy)
{
	TGDialog::OnSize(nType, cx, cy);
}

void TGEdgebarDialog::OnEdgeBar()
{
	AfxMessageBox(L"Click EdgeBar---Command");
	TGCADApp::GetApplication()->AbortCommand(false);
}


void TGEdgebarDialog::OnOK()
{
	TGDialog::OnOK();
}


void TGEdgebarDialog::OnCancel()
{
	TGDialog::OnCancel();
}
