#include "stdafx.h"
#include "SaveCmd.h"
#include"TGUSER/Func/Func.h"

STDMETHODIMP_(HRESULT __stdcall) SaveCmd::Activate()
{
	HRESULT res = S_OK;

	Func::_save();

	return res;
}

STDMETHODIMP_(HRESULT __stdcall) SaveCmd::MouseClick(short sButton, short sShift, double dX, double dY, double dZ, LPDISPATCH pWindowDispatch, long lKeyPointType, LPDISPATCH pGraphicDispatch)
{
	HRESULT res = S_OK;

	AfxMessageBox(L"TGUserCmd::MouseClick");

	return res;
}
