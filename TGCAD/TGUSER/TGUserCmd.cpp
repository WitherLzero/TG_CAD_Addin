#include "stdafx.h"
#include "TGUserCmd.h"
#include"TGUSER/Func/Func.h"

STDMETHODIMP_(HRESULT __stdcall) TGUserCmd::Activate()
{
	HRESULT res = S_OK;

	Func::_drawAndModel();

	return res;
}

STDMETHODIMP_(HRESULT __stdcall) TGUserCmd::MouseClick(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	HRESULT res = S_OK;

	AfxMessageBox(L"TGUserCmd::MouseClick");

	return res;
}
