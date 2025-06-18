#include "stdafx.h"
#include "TGDialog.h"
#include "../TGCADApp.h"


TGDialog::TGDialog(CWnd* pParent)
{
}

TGDialog::TGDialog(UINT nIDTemplate, CWnd* pParent)
	:m_nIDD(nIDTemplate), CDialog(nIDTemplate, pParent)
{
}

void TGDialog::SetDialogIDD(UINT nIDD)
{
	m_nIDD = nIDD;
}

UINT TGDialog::GetDialogIDD()
{
	return m_nIDD;
}

void TGDialog::OnOK()
{
	// ʹ��esc��ʽ
	TGCADApp::GetApplication()->AbortCommand(false);
}

void TGDialog::OnCancel()
{
	TGCADApp::GetApplication()->AbortCommand(false);
}