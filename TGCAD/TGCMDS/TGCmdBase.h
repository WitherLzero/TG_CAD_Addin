#pragma once
#include "../TGCAD_i.h"
#include "../TGManager/TGEventManager.h"

class TGCCmdBase :
	IUnknown,
	public CComObjectRoot,
	public CComCoClass<TGCCmdBase, &CLSID_ASMLOCCommand>
{
protected:
	TGEventManager* m_eventManager;

	ISECommandPtr  m_pSECommand;
	ISEMouseExPtr    m_pSEMouse;

public:
	TGCCmdBase();
	virtual ~TGCCmdBase();

	LPUNKNOWN GetMyUnknown() { return GetUnknown(); }

	void SetCommandsObject(TGEventManager* pCommands) { ASSERT(pCommands); m_eventManager = pCommands; }
	TGEventManager* GetCommandsObject() { ASSERT(m_eventManager); return m_eventManager; }

	virtual HRESULT CreateCommand(TGConstants::seCmdFlag CommandType);

	ISECommandPtr GetCommand() { return m_pSECommand; }

	virtual void UnadviseFromCommandEvents();

	virtual void ReleaseInterfaces();

	BEGIN_COM_MAP(TGCCmdBase)
		COM_INTERFACE_ENTRY(IUnknown)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(TGCCmdBase)

protected:
	template <class IEvents, const IID* piidEvents, const GUID* plibid,
		class XEvents, const CLSID* pClsidEvents>
	class XEventHandler :
		public CComDualImpl<IEvents, piidEvents, plibid>,
		public CComObjectRoot,
		public CComCoClass<XEvents, pClsidEvents>
	{
	public:
		BEGIN_COM_MAP(XEvents)
			COM_INTERFACE_ENTRY_IID(*piidEvents, IEvents)
		END_COM_MAP()
		DECLARE_NOT_AGGREGATABLE(XEvents)
			HRESULT Connect(IUnknown* pUnk)
		{
			HRESULT hr; VERIFY(SUCCEEDED(hr = AtlAdvise(pUnk, this, *piidEvents, &m_dwAdvise))); return hr;
		}
		HRESULT Disconnect(IUnknown* pUnk)
		{
			HRESULT hr; VERIFY(SUCCEEDED(hr = AtlUnadvise(pUnk, *piidEvents, m_dwAdvise))); return hr;
		}

		TGCCmdBase* m_pCommand;
	protected:
		DWORD m_dwAdvise;
	};

	class XCommandEvents : public XEventHandler<ISECommandEvents,
		&__uuidof(ISECommandEvents), &LIBID_SampleAddinLib,
		XCommandEvents, &CLSID_CommandEvents>
	{
	public:
		STDMETHOD(raw_Activate)   (void);

		STDMETHOD(raw_Deactivate) (void);

		STDMETHOD(raw_Terminate)  (void);

		STDMETHOD(raw_Idle)       (long lCount,
			VARIANT_BOOL* pbMore);

		STDMETHOD(raw_KeyDown)    (short* KeyCode,
			short Shift);

		STDMETHOD(raw_KeyPress)   (short* KeyAscii);

		STDMETHOD(raw_KeyUp)      (short* KeyCode,
			short Shift);
	};
	typedef CComObject<XCommandEvents> XCommandEventsObj;
	XCommandEventsObj* m_pCommandEventsObj;

	class XMouseEvents : public XEventHandler<ISEMouseEvents,
		&__uuidof(ISEMouseEvents), &LIBID_SampleAddinLib,
		XMouseEvents, &CLSID_MouseEvents>
	{
	public:
		STDMETHOD(raw_MouseDown)		(short sButton,
			short sShift,
			double dX,
			double dY,
			double dZ,
			LPDISPATCH pWindowDispatch,
			long lKeyPointType,
			LPDISPATCH pGraphicDispatch);

		STDMETHOD(raw_MouseUp)			(short sButton,
			short sShift,
			double dX,
			double dY,
			double dZ,
			LPDISPATCH pWindowDispatch,
			long lKeyPointType,
			LPDISPATCH pGraphicDispatch);

		STDMETHOD(raw_MouseMove)		(short sButton,
			short sShift,
			double dX,
			double dY,
			double dZ,
			LPDISPATCH pWindowDispatch,
			long lKeyPointType,
			LPDISPATCH pGraphicDispatch);

		STDMETHOD(raw_MouseClick)		(short sButton,
			short sShift,
			double dX,
			double dY,
			double dZ,
			LPDISPATCH pWindowDispatch,
			long lKeyPointType,
			LPDISPATCH pGraphicDispatch);

		STDMETHOD(raw_MouseDblClick)	(short sButton,
			short sShift,
			double dX,
			double dY,
			double dZ,
			LPDISPATCH pWindowDispatch,
			long lKeyPointType,
			LPDISPATCH pGraphicDispatch);

		STDMETHOD(raw_MouseDrag)		(short sButton,
			short sShift,
			double dX,
			double dY,
			double dZ,
			LPDISPATCH pWindowDispatch,
			short DragState,
			long lKeyPointType,
			LPDISPATCH pGraphicDispatch);
	};
	typedef CComObject<XMouseEvents> XMouseEventsObj;
	XMouseEventsObj* m_pMouseEventsObj;

	class XLocateFilterEvents : public XEventHandler<ISELocateFilterEvents,
		&__uuidof(ISELocateFilterEvents), &LIBID_SampleAddinLib,
		XLocateFilterEvents, &CLSID_LocateFilterEvents>
	{
	public:
		STDMETHOD(raw_Filter)         (LPDISPATCH pGraphicDispatch,
			VARIANT_BOOL* vbValid);

	};
	typedef CComObject<XLocateFilterEvents> XLocateFilterEventsObj;
	XLocateFilterEventsObj* m_pLocateFilterEventsObj;

	class XWindowEvents : public XEventHandler<ISECommandWindowEvents,
		&__uuidof(ISECommandWindowEvents), &LIBID_SampleAddinLib,
		XWindowEvents, &CLSID_CommandWindowEvents>
	{
	public:
		STDMETHOD(raw_WindowProc) (LPDISPATCH pUnkDoc,
			LPDISPATCH pUnkView,
			UINT nMsg,
			WPARAM wParam,
			LPARAM lParam,
			LRESULT* lResult);
	};
	typedef CComObject<XWindowEvents> XWindowEventsObj;
	XWindowEventsObj* m_pWindowEventsObj;

	STDMETHOD(Activate)  (void) { return S_OK; }

	STDMETHOD(Deactivate)(void) { return S_OK; }

	STDMETHOD(Terminate) (void) { return S_OK; }

	STDMETHOD(Idle)      (long lCount,
		VARIANT_BOOL* pbMore) {
		*pbMore = VARIANT_FALSE; return S_OK;
	};

	STDMETHOD(KeyDown)   (short* KeyCode,
		short Shift) {
		return S_OK;
	}

	STDMETHOD(KeyPress)  (short* KeyAscii) { return S_OK; }

	STDMETHOD(KeyUp)     (short* KeyCode,
		short Shift) {
		return S_OK;
	}

	STDMETHOD(MouseDown)    (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch) {
		return S_OK;
	}

	STDMETHOD(MouseUp)      (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch) {
		return S_OK;
	}

	STDMETHOD(MouseMove)    (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch) {
		return S_OK;
	}

	STDMETHOD(MouseClick)   (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch) {
		return S_OK;
	}

	STDMETHOD(MouseDblClick)(short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch) {
		return S_OK;
	}

	STDMETHOD(MouseDrag)    (short sButton,
		short sShift,
		double dX,
		double dY,
		double dZ,
		LPDISPATCH pWindowDispatch,
		short DragState,
		long lKeyPointType,
		LPDISPATCH pGraphicDispatch) {
		return S_OK;
	}

	STDMETHOD(WindowProc)   (LPDISPATCH pDocDispatch,
		LPDISPATCH pViewDispatch,
		UINT nMsg,
		WPARAM wParam,
		LPARAM lParam,
		LRESULT* lResult) {
		return S_OK;
	}

	STDMETHOD(Filter)       (LPDISPATCH pGraphicDispatch,
		VARIANT_BOOL* vbValid) {
		return S_OK;
	}

	friend class XCommandEvents;
	friend class XMouseEvents;
	friend class XWindowEvents;
	friend class XLocateFilterEvents;
};

typedef CComObject<TGCCmdBase> TGCCmdBaseObj;
typedef CComAggObject<TGCCmdBase> CAggCommandObj;
