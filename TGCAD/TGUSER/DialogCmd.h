#pragma once
#include "TGCMDS/TGDialogCmd.h"
#include "TGUSER/Dialog/MyDialog.h"

class DialogCmd : public TGCmdDialog<MyDialog>
{
public:
	DialogCmd();
	virtual ~DialogCmd();

	STDMETHODIMP Activate();

	STDMETHODIMP MouseClick(short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch);

	STDMETHODIMP MouseMove(short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch);

	STDMETHOD(MouseDrag)    (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		short DragState,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch);

	STDMETHODIMP Filter(LPDISPATCH pGraphicDispatch,
		VARIANT_BOOL* vbValid);
	STDMETHOD(KeyDown)		(short* KeyCode, short Shift);


};

