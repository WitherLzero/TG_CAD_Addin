#pragma once
#include "../TGCmds/TGDialogCmd.h"
#include "TGPopupDialog.h"

class TGUserCmdPopup : public TGCmdDialog<TGPopupDialog>
{
public:
	TGUserCmdPopup();
	virtual ~TGUserCmdPopup();

	STDMETHODIMP Activate();

	STDMETHODIMP MouseClick (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch);

	STDMETHODIMP MouseMove  (short sButton,
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
	STDMETHOD(KeyDown)		(short* KeyCode,short Shift);
};



