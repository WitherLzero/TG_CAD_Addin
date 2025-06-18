#pragma once
#include"TGCMDS/TGCmdBase.h"

class SaveCmd  : public TGCCmdBase
{
	public:
		SaveCmd() {}
		~SaveCmd() {}


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

