#include "stdafx.h"
#include "ConfigCmd.h"

#include "TGHELPER/util.h"
#include "resource.h"

ConfigCmd::ConfigCmd()
{
}

ConfigCmd::~ConfigCmd()
{
}

STDMETHODIMP_(HRESULT __stdcall) ConfigCmd::Activate()
{
	using namespace TGConstants;

	HRESULT hr = S_OK;

	try
	{
		if (m_pSEMouse)
		{
			m_pSEMouse->put_ScaleMode(1);
			m_pSEMouse->put_WindowTypes(1);

			m_pSEMouse->put_EnabledDrag(VARIANT_TRUE);
			m_pSEMouse->put_EnabledMove(VARIANT_TRUE);
			m_pSEMouse->AddToLocateFilter(seLocateFace);

			m_pSEMouse->AddToLocateFilter(seLocateEdge);
			m_pSEMouse->AddToLocateFilter(seLocateVertex);
			m_pSEMouse->AddToLocateFilter(seLocateLine2d);
			m_pSEMouse->AddToLocateFilter(seLocateCircle2d);
			m_pSEMouse->AddToLocateFilter(seLocateCoordinateSystem);
		}
		CreateTGDialog();
	}
	catch (_com_error& e)
	{
		hr = e.Error();
	}

	return hr;
}

STDMETHODIMP_(HRESULT __stdcall) ConfigCmd::MouseClick(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	HRESULT hr = NOERROR;
	AfxMessageBox(L"MouseClick");
	return hr;
}

STDMETHODIMP_(HRESULT __stdcall) ConfigCmd::MouseMove(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	HRESULT hr = NOERROR;
	return hr;
}

STDMETHODIMP_(HRESULT __stdcall) ConfigCmd::MouseDrag(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, short DragState, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	HRESULT hr = NOERROR;
	return hr;
}

STDMETHODIMP_(HRESULT __stdcall) ConfigCmd::Filter(LPDISPATCH pGraphicDispatch, VARIANT_BOOL* vbValid)
{
	HRESULT hr = NOERROR;
	return hr;
}

STDMETHODIMP_(HRESULT __stdcall) ConfigCmd::KeyDown(short* KeyCode, short Shift)
{
	HRESULT hr = NOERROR;
	if (0xd == *KeyCode)
	{
		return S_OK;
	}
	else if (0x53 == *KeyCode) // The 's' key
	{
		return S_OK;
	}
	else if (0x48 == *KeyCode) // The 'h' key
	{
		return S_OK;
	}
	else if (0x52 == *KeyCode) // The 'r' key
	{
		return S_OK;
	}
	else if (0x41 == *KeyCode) // The 'a' key
	{
		return S_OK;
	}
	else if (0x47 == *KeyCode) // The 'g' key
	{
		return S_OK;
	}
	return S_OK;
}