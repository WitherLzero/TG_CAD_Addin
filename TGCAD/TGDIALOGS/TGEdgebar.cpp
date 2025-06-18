#include "stdafx.h"
#include "TGEdgeBar.h"
#include "../TGCADApp.h"
#include "../TGCore/TGCAD.h"
#include "TGEdgebarparent.h"

TGEdgeBar::TGEdgeBar()
{
	m_pEdgeBarDoc = NULL;
	m_pDialog = NULL;
}

TGEdgeBar::~TGEdgeBar()
{
	DeleteEdgeBar();
}

HRESULT TGEdgeBar::CreateEdgeBar(TGDocumentController* pEdgeBarDoc)
{
	ASSERT( pEdgeBarDoc );
	HRESULT hr = NO_ERROR;
	ISolidEdgeBarPtr pBar = GetAddInPtr();
	if( NULL != pBar )
	{
		m_pEdgeBarDoc = pEdgeBarDoc;
		HWND hWndBarPage = 0;
		try
		{
			CString sEdgeBarTip;
			sEdgeBarTip.LoadString(IDS_MODELINGCHECKBAR);
			_bstr_t bstrEdgeBarTip = sEdgeBarTip;
			ISolidEdgeBarExPtr pBarEx = pBar;
			if(NULL != pBarEx)
			{
				TCHAR ResourceFilename[MAX_PATH];
				GetModuleFileName(hMyInstance(), ResourceFilename, sizeof(ResourceFilename));
				hWndBarPage = (HWND)pBarEx->AddPageEx(m_pEdgeBarDoc->GetDocument(), ResourceFilename, IDB_EDGEBAR, bstrEdgeBarTip, 2);
			}
			else
			{
				hWndBarPage = (HWND)pBar->AddPage(m_pEdgeBarDoc->GetDocument(), (long)hMyInstance(), IDB_EDGEBAR, bstrEdgeBarTip, 2);
			}
		}
		catch( _com_error &e )
		{
			hr = e.Error();
		}

		if(hWndBarPage)
		{
			BOOL bRc = FALSE;
			RECT r;
			::GetWindowRect(hWndBarPage, &r);
			BOOL bAttached = m_hWndEdgeBarPage.Attach(hWndBarPage);
			if(bAttached)
			{
				m_pDialog = new TGEdgeBarParent;
				m_pDialog->CreateEx(0, _T("STATIC"), NULL, WS_VISIBLE | WS_CHILD,
					0, 0, r.right - r.left, r.bottom - r.top,
					m_hWndEdgeBarPage, NULL, NULL);	
			try
			{
				pBar->SetActivePage(m_pEdgeBarDoc->GetDocument(), (long)hWndBarPage, 0);
			}
			catch (_com_error &e)
			{
				HRESULT hr = e.Error();
			}
			m_pDialog->ShowWindow(SW_SHOW);
			}		
		}
	}
	else
	{
		hr = E_FAIL;
	}
	return hr;
}

void TGEdgeBar::DeleteEdgeBar()
{
	HWND hWndBarPage = m_hWndEdgeBarPage.Detach();
	if (hWndBarPage)
	{
		ISolidEdgeBarExPtr pBar = GetAddInPtr();
		if (pBar != NULL)
		{
			try
			{
				pBar->RemovePage(m_pEdgeBarDoc->GetDocument(), (long)hWndBarPage, 0);
			}
			catch (_com_error& e)
			{
				HRESULT hr = e.Error();
			}
		}
	}
	delete m_pDialog;
	m_pDialog = NULL;
}
