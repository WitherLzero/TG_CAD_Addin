#include "stdafx.h"
#include "TGCmdBase.h"

TGCCmdBase::TGCCmdBase()
{
	m_eventManager = NULL;
	m_pCommandEventsObj = NULL;
	m_pMouseEventsObj = NULL;
	m_pWindowEventsObj = NULL;
	m_pLocateFilterEventsObj = NULL;
}

TGCCmdBase::~TGCCmdBase()
{
	UnadviseFromCommandEvents();
	ReleaseInterfaces();

	C_RELEASE(m_pCommandEventsObj);

	C_RELEASE(m_pMouseEventsObj);

	C_RELEASE(m_pWindowEventsObj);

	C_RELEASE(m_pLocateFilterEventsObj);
}

HRESULT TGCCmdBase::CreateCommand(TGConstants::seCmdFlag CommandType)
{
	HRESULT hr = S_OK;

	m_pSECommand = m_eventManager->GetApplicationPtr()->CreateCommand(CommandType);

	XCommandEventsObj::CreateInstance(&m_pCommandEventsObj);
	if (m_pCommandEventsObj)
	{
		m_pCommandEventsObj->AddRef();
		hr = m_pCommandEventsObj->Connect(m_pSECommand);
		m_pCommandEventsObj->m_pCommand = this;
	}
	else
	{
		hr = E_OUTOFMEMORY;
	}

	if (SUCCEEDED(hr))
	{
		if (TGConstants::seNoDeactivate == CommandType)
		{
			m_pSEMouse = m_pSECommand->GetMouse();

			XMouseEventsObj::CreateInstance(&m_pMouseEventsObj);
			if (m_pMouseEventsObj)
			{
				m_pMouseEventsObj->AddRef();
				hr = m_pMouseEventsObj->Connect(m_pSEMouse);
				m_pMouseEventsObj->m_pCommand = this;
			}
			else
			{
				hr = E_OUTOFMEMORY;
			}

			if (SUCCEEDED(hr))
			{
				XWindowEventsObj::CreateInstance(&m_pWindowEventsObj);
				if (m_pWindowEventsObj)
				{
					m_pWindowEventsObj->AddRef();
					hr = m_pWindowEventsObj->Connect(m_pSECommand->GetWindow());
					m_pWindowEventsObj->m_pCommand = this;
				}
				else
				{
					hr = E_OUTOFMEMORY;
				}
			}

			XLocateFilterEventsObj::CreateInstance(&m_pLocateFilterEventsObj);
			if (m_pLocateFilterEventsObj)
			{
				m_pLocateFilterEventsObj->AddRef();
				hr = m_pLocateFilterEventsObj->Connect(m_pSEMouse);
				m_pLocateFilterEventsObj->m_pCommand = this;
			}
			else
			{
				hr = E_OUTOFMEMORY;
			}
		}
	}

	return hr;
}

void TGCCmdBase::UnadviseFromCommandEvents()
{
	if (NULL != m_pMouseEventsObj && NULL != m_pSEMouse)
	{
		m_pMouseEventsObj->Disconnect(m_pSEMouse);
	}

	if (NULL != m_pWindowEventsObj && NULL != m_pSECommand)
	{
		IUnknownPtr pWindow = m_pSECommand->GetWindow();
		if (pWindow)
		{
			m_pWindowEventsObj->Disconnect(pWindow);
		}
	}

	if (NULL != m_pLocateFilterEventsObj && NULL != m_pSEMouse)
	{
		m_pLocateFilterEventsObj->Disconnect(m_pSEMouse);
	}

	if (NULL != m_pCommandEventsObj && NULL != m_pSECommand)
	{
		m_pCommandEventsObj->Disconnect(m_pSECommand);
	}
}

void TGCCmdBase::ReleaseInterfaces()
{
	m_pSECommand = NULL;
	m_pSEMouse = NULL;
}

HRESULT TGCCmdBase::XCommandEvents::raw_Activate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->Activate();

	return hr;
}

HRESULT TGCCmdBase::XCommandEvents::raw_Deactivate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->Deactivate();

	return hr;
}

HRESULT TGCCmdBase::XCommandEvents::raw_Terminate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	m_pCommand->UnadviseFromCommandEvents();
	hr = m_pCommand->Terminate();
	m_pCommand->ReleaseInterfaces();
	LPUNKNOWN pMyUnknown = NULL;

	pMyUnknown = m_pCommand->GetMyUnknown();
	if (pMyUnknown)
	{
		pMyUnknown->Release();
	}

	return hr;
}

HRESULT TGCCmdBase::XCommandEvents::raw_Idle(long lCount, VARIANT_BOOL* pbMore)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->Idle(lCount, pbMore);

	return hr;
}

HRESULT TGCCmdBase::XCommandEvents::raw_KeyDown(short* KeyCode, short Shift)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->KeyDown(KeyCode, Shift);

	return hr;
}

HRESULT TGCCmdBase::XCommandEvents::raw_KeyPress(short* KeyAscii)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->KeyPress(KeyAscii);

	return hr;
}

HRESULT TGCCmdBase::XCommandEvents::raw_KeyUp(short* KeyCode, short Shift)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->KeyUp(KeyCode, Shift);

	return hr;
}

HRESULT TGCCmdBase::XMouseEvents::raw_MouseDown(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->MouseDown(sButton, sShift, dX, dY, dZ, pWindowDispatch, lKeyPointType, pGraphicDispatch);

	return hr;
}

HRESULT TGCCmdBase::XMouseEvents::raw_MouseUp(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->MouseUp(sButton, sShift, dX, dY, dZ, pWindowDispatch, lKeyPointType, pGraphicDispatch);

	return hr;
}

HRESULT TGCCmdBase::XMouseEvents::raw_MouseMove(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->MouseMove(sButton, sShift, dX, dY, dZ, pWindowDispatch, lKeyPointType, pGraphicDispatch);

	return hr;
}

HRESULT TGCCmdBase::XMouseEvents::raw_MouseClick(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->MouseClick(sButton, sShift, dX, dY, dZ, pWindowDispatch, lKeyPointType, pGraphicDispatch);

	return hr;
}

HRESULT TGCCmdBase::XMouseEvents::raw_MouseDblClick(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->MouseDblClick(sButton, sShift, dX, dY, dZ, pWindowDispatch, lKeyPointType, pGraphicDispatch);

	return hr;
}

HRESULT TGCCmdBase::XMouseEvents::raw_MouseDrag(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, short DragState, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->MouseDrag(sButton, sShift, dX, dY, dZ, pWindowDispatch, DragState, lKeyPointType, pGraphicDispatch);

	return hr;
}

HRESULT TGCCmdBase::XWindowEvents::raw_WindowProc(LPDISPATCH pUnkDoc, LPDISPATCH pUnkView, UINT nMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->WindowProc(pUnkDoc, pUnkView, nMsg, wParam, lParam, lResult);

	return hr;
}

HRESULT TGCCmdBase::XLocateFilterEvents::raw_Filter(LPDISPATCH pGraphicDispatch, VARIANT_BOOL* vbValid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;

	hr = m_pCommand->Filter(pGraphicDispatch, vbValid);

	return hr;
}
