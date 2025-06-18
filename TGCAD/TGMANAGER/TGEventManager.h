#pragma once

#include "../TGCADApp.h"
#include "../TGCAD_i.h"

class TGDocumentController;
typedef CComObject<TGDocumentController> TGDocumentControllerObj;
typedef CTypedPtrMap<CMapPtrToPtr, LPDISPATCH, CComObject<TGDocumentController>*> CMapSEDocDispatchToMyDoc;

class TGEventManager :
	public CComObjectRoot,
	public CComCoClass<TGEventManager, &CLSID_Commands>
{
protected:

	static ApplicationPtr m_pApplication;
	static ISEAddInExPtr    m_pSEAddIn;
	CMapSEDocDispatchToMyDoc m_pDocuments;

public:
	TGEventManager();
	~TGEventManager();

	static ISEAddInPtr GetAddIn() { return m_pSEAddIn; }
	static ApplicationPtr GetApplicationPtr() { return m_pApplication; }

	HRESULT SetAddInObject(AddIn* pSolidEdgeAddIn, BOOL bWithEvents = TRUE);
	HRESULT SetApplicationObject(LPDISPATCH pApplicationDispatch, BOOL bWithEvents = TRUE);

	HRESULT UnadviseFromEvents();

	HRESULT CreateDocumentController(LPDISPATCH pSEDocumentDispatch,TGDocumentControllerObj** ppDocumentController = NULL);

	HRESULT DestroyDocumentController(LPDISPATCH pSEDOcumentDispatch);

	HRESULT DestroyAllDocumentControllers();

	TGDocumentControllerObj* GetDocument(LPDISPATCH pSEDocumentDispatch);

	BEGIN_COM_MAP(TGEventManager)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(TGEventManager)

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

		TGEventManager* m_pCommands;

	protected:
		DWORD m_dwAdvise;
	};

	class XShortCutMenuEvents : public XEventHandler<ISEShortCutMenuEvents,
		&__uuidof(ISEShortCutMenuEvents), &LIBID_SampleAddinLib,
		XShortCutMenuEvents, &CLSID_ADDINShortCutMenuEvents>
	{
	public:
		STDMETHOD(raw_BuildMenu)         (BSTR bstrEnvironmentCatid,
			enum ShortCutMenuContextConstants Context,
			LPDISPATCH pGraphicDispatch,
			SAFEARRAY** pMenuStrings,
			SAFEARRAY** pCommandIDs);
	};
	typedef CComObject<XShortCutMenuEvents> XShortCutMenuEventsObj;
	XShortCutMenuEventsObj* m_pShortCutMenuEventsObj;

	class XAddInEvents : public XEventHandler<ISEAddInEvents,
		&__uuidof(ISEAddInEvents), &LIBID_SampleAddinLib,
		XAddInEvents, &CLSID_ASMLOCAddInEvents>
	{
	public:

		STDMETHOD(raw_OnCommand)         (long nCmdID);

		STDMETHOD(raw_OnCommandHelp)     (long hFrameWnd,
			long uHelpCommand,
			long nCmdID);

		STDMETHOD(raw_OnCommandUpdateUI) (long nCmdID,
			long* lCmdFlags,
			BSTR* MenuItemText,
			long* nIDBitmap);
	};
	typedef CComObject<XAddInEvents> XAddInEventsObj;

	XAddInEventsObj* m_pAddInEventsObj;

	class XAddInEventsEx : public XEventHandler<ISEAddInEventsEx,
		&__uuidof(ISEAddInEventsEx), &LIBID_SampleAddinLib,
		XAddInEventsEx, &CLSID_ASMLOCAddInEventsEx>
	{
	public:
		STDMETHOD(raw_OnCommand)         (long nCmdID);

		STDMETHOD(raw_OnCommandHelp)     (long hFrameWnd,
			long uHelpCommand,
			long nCmdID);

		STDMETHOD(raw_OnCommandUpdateUI) (long nCmdID,
			long* lCmdFlags,
			BSTR* MenuItemText,
			long* nIDBitmap);

		STDMETHOD(raw_OnCommandOnLineHelp) (long uHelpCommand,
			long nCmdID,
			BSTR* HelpURL);
	};
	typedef CComObject<XAddInEventsEx> XAddInEventsExObj;

	XAddInEventsExObj* m_pAddInEventsExObj;

	class XAddInEventsEx2 : public XEventHandler<ISEAddInEventsEx2,
		&__uuidof(ISEAddInEventsEx2), &LIBID_SampleAddinLib,
		XAddInEventsEx2, &CLSID_ASMLOCAddInEventsEx2>
	{
	public:
		STDMETHOD(raw_OnCommand)         (long nCmdID,
			ShortCutMenuContextConstants Context,
			DocumentTypeConstants ActiveDocumentType,
			LPDISPATCH pActiveDocument,
			LPDISPATCH pActiveWindow,
			LPDISPATCH pActiveSelectSet);

		STDMETHOD(raw_OnCommandHelp)     (long hFrameWnd,
			long uHelpCommand,
			long nCmdID);

		STDMETHOD(raw_OnCommandUpdateUI) (long nCmdID,
			ShortCutMenuContextConstants Context,
			DocumentTypeConstants ActiveDocumentType,
			LPDISPATCH pActiveDocument,
			LPDISPATCH pActiveWindow,
			LPDISPATCH pActiveSelectSet,
			long* lCmdFlags,
			BSTR* MenuItemText,
			long* nIDBitmap);

		STDMETHOD(raw_OnCommandOnLineHelp) (long uHelpCommand,
			long nCmdID,
			BSTR* HelpURL);
	};
	typedef CComObject<XAddInEventsEx2> XAddInEventsEx2Obj;

	XAddInEventsEx2Obj* m_pAddInEventsEx2Obj;

	class XApplicationEvents : public XEventHandler<ISEApplicationEvents,
		&__uuidof(ISEApplicationEvents), &LIBID_SampleAddinLib,
		XApplicationEvents, &CLSID_ASMLOCApplicationEvents>
	{
	public:
		STDMETHOD(raw_AfterActiveDocumentChange)   (LPDISPATCH theDocument);

		STDMETHOD(raw_AfterCommandRun)             (long theCommandID);

		STDMETHOD(raw_AfterDocumentOpen)           (LPDISPATCH theDocument);

		STDMETHOD(raw_AfterDocumentPrint)          (LPDISPATCH theDocument,
			long hDC,
			double* ModelToDC,
			long* Rect);

		STDMETHOD(raw_AfterDocumentSave)           (LPDISPATCH theDocument);

		STDMETHOD(raw_AfterEnvironmentActivate)    (LPDISPATCH theEnvironment);

		STDMETHOD(raw_AfterNewDocumentOpen)        (LPDISPATCH theDocument);

		STDMETHOD(raw_AfterNewWindow)              (LPDISPATCH theWindow);

		STDMETHOD(raw_AfterWindowActivate)         (LPDISPATCH theWindow);

		STDMETHOD(raw_BeforeCommandRun)            (long theCommandID);

		STDMETHOD(raw_BeforeDocumentClose)         (LPDISPATCH theDocument);

		STDMETHOD(raw_BeforeDocumentPrint)         (LPDISPATCH theDocument,
			long hDC,
			double* ModelToDC,
			long* Rect);

		STDMETHOD(raw_BeforeEnvironmentDeactivate) (LPDISPATCH theEnvironment);

		STDMETHOD(raw_BeforeWindowDeactivate)      (LPDISPATCH theWindow);

		STDMETHOD(raw_BeforeQuit)                  (void);

		STDMETHOD(raw_BeforeDocumentSave)          (LPDISPATCH theDocument);
	};
	typedef CComObject<XApplicationEvents> XApplicationEventsObj;
	XApplicationEventsObj* m_pApplicationEventsObj;

	class XApplicationEventsEx : public XEventHandler<ISEApplicationEventsEx,
		&__uuidof(ISEApplicationEventsEx), &LIBID_SampleAddinLib,
		XApplicationEventsEx, &CLSID_ASMLOCApplicationEventsEx>
	{
	public:
		STDMETHOD(raw_OnCommandUpdateUI)				(long CommandID,
			long* CommandFlags,
			BSTR* MenuItemText);
	};
	typedef CComObject<XApplicationEventsEx> XApplicationEventsExObj;
	XApplicationEventsExObj* m_pApplicationEventsExObj;

	class XAddInEdgeBarEvents : public XEventHandler<ISEAddInEdgeBarEvents,
		&__uuidof(ISEAddInEdgeBarEvents), &LIBID_SampleAddinLib,
		XAddInEdgeBarEvents, &CLSID_ASMLOCAddInEdgeBarEvents>
	{
	public:
		STDMETHOD(raw_AddPage)				(LPDISPATCH theDocument);

		STDMETHOD(raw_RemovePage)			(LPDISPATCH theDocument);

		STDMETHOD(raw_IsPageDisplayable)	(IDispatch* theDocument,
			BSTR EnvironmentCatID,
			VARIANT_BOOL* vbIsPageDisplayable);
	};
	typedef CComObject<XAddInEdgeBarEvents> XAddInEdgeBarEventsObj;
	XAddInEdgeBarEventsObj* m_pAddInEdgeBarEventsObj;

	class XSaveAsTranslatorEvents : public XEventHandler<ISEAddInSaveAsTranslatorEvents,
		&__uuidof(ISEAddInSaveAsTranslatorEvents), &LIBID_SampleAddinLib,
		XSaveAsTranslatorEvents, &CLSID_ADDINSaveAsTranslatorEvents>
	{
	public:
		STDMETHOD(raw_OnOptions)			(LPDISPATCH theDocument, BSTR FilenameExtension);
		STDMETHOD(raw_OnOptionsUpdateUI)	(LPDISPATCH theDocument, BSTR FilenameExtension, long* Flags);
		STDMETHOD(raw_OnSaveAs)			(LPDISPATCH theDocument, BSTR SaveAsFilename, long* hResult);
	};
	typedef CComObject<XSaveAsTranslatorEvents> XSaveAsTranslatorEventsObj;
	XSaveAsTranslatorEventsObj* m_pXSaveAsTranslatorEventsObj;

public:

	friend class XAddInEvents;
	friend class XAddInEventsEx;
};
typedef CComObject<TGEventManager> TGEventManagerObj;

class TGEdgeBar;
class TGDocumentController :
	public CComObjectRoot,
	public CComCoClass<ADDINDocument, &CLSID_ADDINDocument>
{
public:
	TGDocumentController();
	~TGDocumentController();

	TGEdgeBar* GetEdgeBar() { return m_pEdgeBar; }

	HRESULT SetDocumentObject(LPDISPATCH pDocumentDispatch);
	IDispatchPtr GetDocument(void) { return m_pDocument; }

	void SetCommandsObject(TGEventManager* pCommands) { ASSERT(pCommands); m_pCommands = pCommands; }
	TGEventManager* GetCommandsObject() { ASSERT(m_pCommands); return m_pCommands; }

	HRESULT CreateEdgeBarPage();
	HRESULT RemoveEdgeBarPage();
	void DestroyEdgeBar();

	BEGIN_COM_MAP(TGDocumentController)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(TGDocumentController)
protected:

	IDispatchPtr  m_pDocument;

	TGEventManager* m_pCommands;

	TGEdgeBar* m_pEdgeBar;

};
