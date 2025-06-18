#pragma once
#include"TGCMDS/TGCmdBase.h"

class TGUserCmd : public TGCCmdBase
{
public:
	TGUserCmd() {}
	~TGUserCmd() {}


public:
	// Activate
	STDMETHODIMP Activate();

	// Terminate
	//STDMETHODIMP Terminate();

	// Mouse click
	STDMETHODIMP MouseClick(short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch);
};



