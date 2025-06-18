#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "TGCAD_i.h"


class TGCAD;
class TGCADApp : public CWinApp
{
public:
	TGCADApp();

public:
	virtual BOOL InitInstance();
	int ExitInstance();

public:
	static TGCADApp* GetTGApp();
	TGCAD* GetTGAddin();
	void SetTGAddin(TGCAD* pAddin);
	static ApplicationPtr GetApplication();

private:
	TGCAD* m_pTGAddin;
};


