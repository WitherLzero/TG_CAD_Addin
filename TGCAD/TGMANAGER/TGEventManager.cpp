#include "stdafx.h"
#include "TGEventManager.h"
#include "../resource.h"
#include "../TGHelper/util.h"
#include "htmlhelp.h"


#include "../TGCore/TGCAD.h"
#include "../SDK/include/tgcatids.h"
#include "../MyCommands.h"
#include "../TGDialogs/TGEdgebar.h"
#include "../TGCmds/TGCmdManager.h"

ISEAddInExPtr TGEventManager::m_pSEAddIn = NULL;
ApplicationPtr TGEventManager::m_pApplication = NULL;;

AddInPtr GetAddInPtr() { return TGEventManager::GetAddIn(); }
ApplicationPtr GetApplicationPtr() { return TGEventManager::GetApplicationPtr(); }

TGEventManager::TGEventManager()
{
	m_pApplication = NULL;

	m_pSEAddIn = NULL;

	m_pApplicationEventsObj = NULL;

	m_pApplicationEventsExObj = NULL;

	m_pAddInEventsObj = NULL;
	m_pAddInEventsExObj = NULL;
	m_pAddInEventsEx2Obj = NULL;

	m_pShortCutMenuEventsObj = NULL;

	m_pAddInEdgeBarEventsObj = NULL;

	m_pXSaveAsTranslatorEventsObj = NULL;
}

TGEventManager::~TGEventManager()
{
	m_pApplication = NULL;

	m_pSEAddIn = NULL;

	DestroyAllDocumentControllers();
}

HRESULT TGEventManager::SetApplicationObject(LPDISPATCH pApplicationDispatch,
	BOOL bWithEvents)
{
	ASSERT(pApplicationDispatch);

	HRESULT hr = NOERROR;

	m_pApplication = pApplicationDispatch;

	if (bWithEvents)
	{
		XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
		if (m_pApplicationEventsObj)
		{
			m_pApplicationEventsObj->AddRef();
			hr = m_pApplicationEventsObj->Connect(m_pApplication);
			m_pApplicationEventsObj->m_pCommands = this;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		XApplicationEventsExObj::CreateInstance(&m_pApplicationEventsExObj);
		if (m_pApplicationEventsExObj)
		{
			m_pApplicationEventsExObj->AddRef();
			hr = m_pApplicationEventsExObj->Connect(m_pApplication);
			m_pApplicationEventsExObj->m_pCommands = this;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		XShortCutMenuEventsObj::CreateInstance(&m_pShortCutMenuEventsObj);

		if (m_pShortCutMenuEventsObj)
		{
			m_pShortCutMenuEventsObj->AddRef();
			hr = m_pShortCutMenuEventsObj->Connect(m_pApplication);
			m_pShortCutMenuEventsObj->m_pCommands = this;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}
	}

	return hr;
}

HRESULT TGEventManager::UnadviseFromEvents()
{
	HRESULT hr = NOERROR;

	if (NULL != m_pAddInEventsObj)
	{
		hr = m_pAddInEventsObj->Disconnect(m_pSEAddIn);
		m_pAddInEventsObj->Release();
		m_pAddInEventsObj = NULL;
	}

	if (NULL != m_pAddInEventsExObj)
	{
		hr = m_pAddInEventsExObj->Disconnect(m_pSEAddIn);
		m_pAddInEventsExObj->Release();
		m_pAddInEventsExObj = NULL;
	}

	if (NULL != m_pAddInEventsEx2Obj)
	{
		hr = m_pAddInEventsEx2Obj->Disconnect(m_pSEAddIn);
		m_pAddInEventsEx2Obj->Release();
		m_pAddInEventsEx2Obj = NULL;
	}

	if (NULL != m_pApplicationEventsObj)
	{
		hr = m_pApplicationEventsObj->Disconnect(m_pApplication);
		m_pApplicationEventsObj->Release();
		m_pApplicationEventsObj = NULL;
	}

	if (NULL != m_pApplicationEventsExObj)
	{
		hr = m_pApplicationEventsExObj->Disconnect(m_pApplication);
		m_pApplicationEventsExObj->Release();
		m_pApplicationEventsExObj = NULL;
	}

	if (NULL != m_pShortCutMenuEventsObj)
	{
		hr = m_pShortCutMenuEventsObj->Disconnect(m_pApplication);
		m_pShortCutMenuEventsObj->Release();
		m_pShortCutMenuEventsObj = NULL;
	}

	if (NULL != m_pAddInEdgeBarEventsObj)
	{
		hr = m_pAddInEdgeBarEventsObj->Disconnect(m_pSEAddIn);
		m_pAddInEdgeBarEventsObj->Release();
		m_pAddInEdgeBarEventsObj = NULL;
	}

	if (NULL != m_pXSaveAsTranslatorEventsObj)
	{
		hr = m_pXSaveAsTranslatorEventsObj->Disconnect(m_pSEAddIn);
		m_pXSaveAsTranslatorEventsObj->Release();
		m_pXSaveAsTranslatorEventsObj = NULL;
	}

	return hr;
}

HRESULT TGEventManager::SetAddInObject(AddIn* pSolidEdgeAddIn, BOOL bWithEvents)
{
	ASSERT(pSolidEdgeAddIn);

	HRESULT hr = NOERROR;

	m_pSEAddIn = pSolidEdgeAddIn;

	if (bWithEvents)
	{
		XAddInEventsEx2Obj::CreateInstance(&m_pAddInEventsEx2Obj);
		if (m_pAddInEventsEx2Obj)
		{
			m_pAddInEventsEx2Obj->AddRef();
			hr = m_pAddInEventsEx2Obj->Connect(m_pSEAddIn->GetAddInEvents());
			m_pAddInEventsEx2Obj->m_pCommands = this;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		XAddInEventsExObj::CreateInstance(&m_pAddInEventsExObj);
		if (m_pAddInEventsExObj)
		{
			m_pAddInEventsExObj->AddRef();
			hr = m_pAddInEventsExObj->Connect(m_pSEAddIn->GetAddInEvents());
			m_pAddInEventsExObj->m_pCommands = this;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		XAddInEventsObj::CreateInstance(&m_pAddInEventsObj);
		if (m_pAddInEventsObj)
		{
			m_pAddInEventsObj->AddRef();
			hr = m_pAddInEventsObj->Connect(m_pSEAddIn->GetAddInEvents());
			m_pAddInEventsObj->m_pCommands = this;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		XAddInEdgeBarEventsObj::CreateInstance(&m_pAddInEdgeBarEventsObj);
		if (m_pAddInEdgeBarEventsObj)
		{

			m_pAddInEdgeBarEventsObj->AddRef();
			hr = m_pAddInEdgeBarEventsObj->Connect(m_pSEAddIn->GetAddInEdgeBarEvents());
			if (SUCCEEDED(hr))
			{
				m_pAddInEdgeBarEventsObj->m_pCommands = this;
			}
			else
			{
				m_pAddInEdgeBarEventsObj->Release();
				m_pAddInEdgeBarEventsObj = NULL;
			}
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		ISEAddInSaveAsTranslatorPtr pSaveAsTranslator = m_pSEAddIn;
		if (pSaveAsTranslator)
		{
			XSaveAsTranslatorEventsObj::CreateInstance(&m_pXSaveAsTranslatorEventsObj);
			if (m_pXSaveAsTranslatorEventsObj)
			{
				m_pXSaveAsTranslatorEventsObj->AddRef();
				hr = m_pXSaveAsTranslatorEventsObj->Connect(pSaveAsTranslator->GetAddInSaveAsTranslatorEvents());
				if (SUCCEEDED(hr))
				{
					m_pXSaveAsTranslatorEventsObj->m_pCommands = this;
				}
				else
				{
					m_pXSaveAsTranslatorEventsObj->Release();
					m_pXSaveAsTranslatorEventsObj = NULL;
				}
			}
			else
			{
				hr = E_OUTOFMEMORY;
			}
		}
	}

	return hr;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterActiveDocumentChange(LPDISPATCH theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterDocumentOpen(LPDISPATCH theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterDocumentPrint(LPDISPATCH theDocument,
	long hDC,
	double* ModelToDC,
	long* Rect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterDocumentSave(LPDISPATCH theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterEnvironmentActivate(LPDISPATCH theEnvironment)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterNewDocumentOpen(LPDISPATCH theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterNewWindow(LPDISPATCH theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterWindowActivate(LPDISPATCH theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeCommandRun(long lCommandID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_AfterCommandRun(long lCommandID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeDocumentClose(LPDISPATCH theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeDocumentPrint(LPDISPATCH theDocument,
	long hDC,
	double* ModelToDC,
	long* Rect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeEnvironmentDeactivate(LPDISPATCH theEnvironment)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeWindowDeactivate(LPDISPATCH theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeQuit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT TGEventManager::XApplicationEvents::raw_BeforeDocumentSave(LPDISPATCH theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

static int s_RadioState = 0;
static int s_CheckState = 0;

HRESULT TGEventManager::XApplicationEventsEx::raw_OnCommandUpdateUI(long CommandID, long* CommandFlags, BSTR* MenuItemText)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (25010 == CommandID && s_CheckState)
	{
		*CommandFlags = 4;

		*MenuItemText = SysAllocString(L"Nex3DModelingTool Add-in turns the place line command off whenever the Nex3DModelingTool checkbox is checked.");
	}
	else if (25010 == CommandID && !s_CheckState)
	{
		*CommandFlags |= TGConstants::seCmdActive_ChangeText;
	}
	else if (45024 == CommandID && s_CheckState)
	{
		*CommandFlags = 4;

		*MenuItemText = SysAllocString(L"Nex3DModelingTool Add-in turns the place line command off whenever the Nex3DModelingTool checkbox is checked.");
	}
	else if (45024 == CommandID && !s_CheckState)
	{
		*CommandFlags |= TGConstants::seCmdActive_ChangeText;
	}

	return S_OK;
}

HRESULT TGEventManager::XShortCutMenuEvents::raw_BuildMenu(BSTR bstrEnvironmentCatid,
	enum ShortCutMenuContextConstants Context,
	LPDISPATCH pGraphicDispatch,
	SAFEARRAY** MenuStrings,
	SAFEARRAY** CommandIDs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HRESULT hr = NOERROR;
	CComSafeArray<BSTR> saCommandStrings;
	hr = saCommandStrings.Create();
	if (SUCCEEDED(hr))
	{
		CComSafeArray<long> saCommandIDs;
		hr = saCommandIDs.Create();

		if (SUCCEEDED(hr))
		{
			CString sCmdString;
			sCmdString.LoadString(IDS_SHORTCUT_CMD);

			saCommandStrings.Add(sCmdString.AllocSysString());

			saCommandIDs.Add(GetLocTestShortCutMenuCmdId());

			*MenuStrings = saCommandStrings;

			saCommandStrings.Detach();

			*CommandIDs = saCommandIDs;

			saCommandIDs.Detach();
		}
	}
	return (hr);
}

SAFEARRAY* pRefKey1 = 0;

void SetRefKey(SAFEARRAY* pRefKey) { pRefKey1 = pRefKey; }

HRESULT TGEventManager::XAddInEventsEx2::raw_OnCommand(long nCmdID,
	ShortCutMenuContextConstants Context,
	DocumentTypeConstants ActiveDocumentType,
	LPDISPATCH pActiveDocument,
	LPDISPATCH pActiveWindow,
	LPDISPATCH pActiveSelectSet)
{
	if (m_pCommands->m_pAddInEventsObj)
	{
		return m_pCommands->m_pAddInEventsObj->raw_OnCommand(nCmdID);
	}
	return E_UNEXPECTED;
}

HRESULT TGEventManager::XAddInEventsEx2::raw_OnCommandHelp(long hFrameWnd,
	long uHelpCommand,
	long nCmdID)
{
	if (m_pCommands->m_pAddInEventsObj)
	{
		return m_pCommands->m_pAddInEventsObj->raw_OnCommandHelp(hFrameWnd, uHelpCommand, nCmdID);
	}

	return E_UNEXPECTED;
}

HRESULT TGEventManager::XAddInEventsEx2::raw_OnCommandUpdateUI(long nCmdID,
	ShortCutMenuContextConstants Context,
	DocumentTypeConstants ActiveDocumentType,
	LPDISPATCH pActiveDocument,
	LPDISPATCH pActiveWindow,
	LPDISPATCH pActiveSelectSet,
	long* lCmdFlags,
	BSTR* MenuItemText,
	long* nIDBitmap)
{
	if (m_pCommands->m_pAddInEventsObj)
	{
		return m_pCommands->m_pAddInEventsObj->raw_OnCommandUpdateUI(nCmdID, lCmdFlags, MenuItemText, nIDBitmap);
	}

	return E_UNEXPECTED;
}

HRESULT TGEventManager::XAddInEventsEx2::raw_OnCommandOnLineHelp(long uHelpCommand,
	long nCmdID,
	BSTR* HelpURL)
{
	if (m_pCommands->m_pAddInEventsExObj)
	{
		return m_pCommands->m_pAddInEventsExObj->raw_OnCommandOnLineHelp(uHelpCommand, nCmdID, HelpURL);
	}

	return S_OK;
}

HRESULT TGEventManager::XAddInEventsEx::raw_OnCommand(long nCmdID)
{
	if (m_pCommands->m_pAddInEventsObj)
	{
		return m_pCommands->m_pAddInEventsObj->raw_OnCommand(nCmdID);
	}

	return E_UNEXPECTED;
}

HRESULT TGEventManager::XAddInEventsEx::raw_OnCommandHelp(long hFrameWnd,
	long uHelpCommand,
	long nCmdID)
{
	if (m_pCommands->m_pAddInEventsObj)
	{
		return m_pCommands->m_pAddInEventsObj->raw_OnCommandHelp(hFrameWnd, uHelpCommand, nCmdID);
	}

	return E_UNEXPECTED;
}

HRESULT TGEventManager::XAddInEventsEx::raw_OnCommandUpdateUI(long nCmdID,
	long* lCmdFlags,
	BSTR* MenuItemText,
	long* nIDBitmap)
{
	if (m_pCommands->m_pAddInEventsObj)
	{
		return m_pCommands->m_pAddInEventsObj->raw_OnCommandUpdateUI(nCmdID, lCmdFlags, MenuItemText, nIDBitmap);
	}

	return E_UNEXPECTED;
}

HRESULT TGEventManager::XAddInEventsEx::raw_OnCommandOnLineHelp(long uHelpCommand,
	long nCmdID,
	BSTR* HelpURL)
{
	*HelpURL = SysAllocString(L"www.newdimchina.com");
	return S_OK;
}

HRESULT TGEventManager::XAddInEvents::raw_OnCommand(long nCmdID)
{
	HRESULT hr = S_OK;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		TGCmdManager::Instance()->CallCommand(nCmdID);
	}
	catch (_com_error& e)
	{
		hr = e.Error(); 
	}

	return hr;
}

static DWORD ConvertCommandIDToHelpID(long nCmdID, CString& strTopic)
{
	switch (nCmdID)
	{
	case 0:
	case 1:
	{
		break;
	}
	case 2:
	{
		break;
	}
	default:
	{
		break;
	}
	}
	return((DWORD)nCmdID);
}

HRESULT TGEventManager::XAddInEvents::raw_OnCommandHelp(long hFrameWnd,
	long uHelpCommand,
	long nCmdID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_FALSE;
	HWND hHelpWnd = 0;
	CString strHelpPath;
	TCHAR tcsFileName[1024] = { 0 };
	DWORD dwError = GetModuleFileName(hMyInstance(), tcsFileName, sizeof(tcsFileName) / sizeof(*tcsFileName));
	if (dwError)
	{
		strHelpPath = tcsFileName;

		strHelpPath.MakeLower();

		strHelpPath.Replace(_T("Nex3DModelingTool.dll"), _T("Nex3DModelingToolhelp.chm"));
	}

	if (-1 == nCmdID)
	{

	}
	else
	{
		DWORD dwHelpID = 0;
		long uHtmlHelpCommand;

		switch (uHelpCommand)
		{
		case HELP_CONTEXT:
		{
			CString strTopic;

			uHtmlHelpCommand = HH_HELP_CONTEXT;

			dwHelpID = ConvertCommandIDToHelpID(nCmdID, strTopic);

			if (!strTopic.IsEmpty())
			{
				strHelpPath += "::/";
				strHelpPath += strTopic;

				dwHelpID = 0;
			}
			break;
		}
		case HELP_FINDER:
		{
			uHtmlHelpCommand = HH_DISPLAY_TOPIC;
			break;
		}
		default:
		{
			uHtmlHelpCommand = HH_DISPLAY_TOPIC;
			break;
		}
		}
	}

	if (hHelpWnd)
	{
		hr = S_OK;
	}

	return(hr);
}

HRESULT TGEventManager::XAddInEvents::raw_OnCommandUpdateUI(long nCmdID,
	long* lCmdFlags,
	BSTR* MenuItemText,
	long* nIDBitmap)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*lCmdFlags = TGConstants::seCmdActive_Enabled;

	if (2 == nCmdID)
	{
		if (s_RadioState)
		{
			*lCmdFlags |= TGConstants::seCmdActive_Checked;
		}
	}
	else if (3 == nCmdID)
	{
		if (s_CheckState)
		{
			*lCmdFlags |= TGConstants::seCmdActive_Checked;
		}
	}

	return S_OK;
}

HRESULT TGEventManager::XAddInEdgeBarEvents::raw_AddPage(LPDISPATCH pSEDocumentDispatch)
{
	HRESULT hr = S_OK;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TGDocumentControllerObj* pMyDoc;
	m_pCommands->CreateDocumentController(pSEDocumentDispatch,&pMyDoc);

	if (NULL != pMyDoc)
	{
		pMyDoc->CreateEdgeBarPage();
		pMyDoc->Release();
	}
	return hr;
}

HRESULT TGEventManager::XAddInEdgeBarEvents::raw_RemovePage(LPDISPATCH pSEDocumentDispatch)
{
	HRESULT hr = S_OK;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TGDocumentControllerObj* pDoc = NULL;
	BOOL bAlreadyThere = m_pCommands->m_pDocuments.Lookup(pSEDocumentDispatch, pDoc);
	if (pDoc)
	{
		pDoc->RemoveEdgeBarPage();
	}
	m_pCommands->DestroyDocumentController(pSEDocumentDispatch);
	return hr;
}

HRESULT TGEventManager::XAddInEdgeBarEvents::raw_IsPageDisplayable(IDispatch* pSEDocumentDispatch,
	BSTR EnvironmentCatID,
	VARIANT_BOOL* vbIsPageDisplayable)
{
	HRESULT hr = S_OK;
	*vbIsPageDisplayable = VARIANT_TRUE;
	return hr;
}

HRESULT TGEventManager::CreateDocumentController(LPDISPATCH pSEDocumentDispatch, TGDocumentControllerObj** ppDocumentController)
{
	HRESULT hr = NOERROR;

	TGDocumentControllerObj* pDoc = NULL;

	TGDocumentControllerObj* myDocumentController = *ppDocumentController;

	BOOL bAlreadyThere = m_pDocuments.Lookup(pSEDocumentDispatch, pDoc);

	if (FALSE == bAlreadyThere)
	{
		TGDocumentControllerObj::CreateInstance(&pDoc);
		if (pDoc)
		{
			pDoc->AddRef();
			pDoc->SetCommandsObject(this);
			pDoc->SetDocumentObject(pSEDocumentDispatch);

			m_pDocuments.SetAt(pSEDocumentDispatch, pDoc);
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}
	}

	if (ppDocumentController)
	{
		*ppDocumentController = pDoc;
		(*ppDocumentController)->AddRef();
	}

	return hr;
}

HRESULT TGEventManager::DestroyDocumentController(LPDISPATCH pSEDocumentDispatch)
{
	HRESULT hr = NOERROR;

	TGDocumentControllerObj* pDoc = NULL;

	BOOL bDocExists = m_pDocuments.Lookup(pSEDocumentDispatch, pDoc);

	if (bDocExists)
	{
		m_pDocuments.RemoveKey(pSEDocumentDispatch);

		C_RELEASE(pDoc);
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}

HRESULT TGEventManager::DestroyAllDocumentControllers()
{
	HRESULT hr = NOERROR;

	POSITION pos = m_pDocuments.GetStartPosition();

	while (NULL != pos)
	{
		LPDISPATCH pDocDispatch = NULL;
		TGDocumentControllerObj* pDoc = NULL;

		m_pDocuments.GetNextAssoc(pos, pDocDispatch, pDoc);

		C_RELEASE(pDoc)
	}

	m_pDocuments.RemoveAll();

	return hr;
}

TGDocumentControllerObj* TGEventManager::GetDocument(LPDISPATCH pDocDispatch)
{
	TGDocumentControllerObj* pDoc = NULL;

	BOOL bDocExists = m_pDocuments.Lookup(pDocDispatch, pDoc);

	if (NULL != pDoc)
	{
		pDoc->AddRef();
	}

	return pDoc;
}

HRESULT TGEventManager::XSaveAsTranslatorEvents::raw_OnOptions(LPDISPATCH theDocument, BSTR FilenameExtension)
{
	HRESULT hr = S_OK;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	AfxMessageBox(_T("This is just an example. I don't really have any options."), MB_OK);

	return hr;
}

HRESULT TGEventManager::XSaveAsTranslatorEvents::raw_OnOptionsUpdateUI(LPDISPATCH theDocument, BSTR FilenameExtension, long* Flags)
{
	HRESULT hr = S_OK;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (wcscmp(FilenameExtension, L"*.x_t"))
	{
		*Flags = 1;
	}

	return hr;
}

HRESULT TGEventManager::XSaveAsTranslatorEvents::raw_OnSaveAs(LPDISPATCH theDocument, BSTR SaveAsFilename, long* hResult)
{
	HRESULT hr = S_OK;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (hResult)
	{
		*hResult = NOERROR;

		PartDocumentPtr pPartDoc = theDocument;
		if (pPartDoc)
		{
			try
			{
				pPartDoc->SaveAs(SaveAsFilename);
			}
			catch (_com_error& e)
			{
				*hResult = e.Error();
			}
		}
		else
		{
			*hResult = E_INVALIDARG;
		}
	}
	return hr;
}

TGDocumentController::TGDocumentController()
{
	m_pDocument = NULL;
	m_pCommands = NULL;
	m_pEdgeBar = NULL;
}

TGDocumentController::~TGDocumentController()
{
	DestroyEdgeBar();
}

HRESULT TGDocumentController::SetDocumentObject(LPDISPATCH pDocumentDispatch)
{
	ASSERT(pDocumentDispatch);

	HRESULT hr = NOERROR;

	m_pDocument = pDocumentDispatch;

	return hr;
}

HRESULT TGDocumentController::CreateEdgeBarPage()
{
	HRESULT hr = NOERROR;

	if (m_pEdgeBar)
	{
		delete m_pEdgeBar;
		m_pEdgeBar = NULL;
	}

	m_pEdgeBar = new TGEdgeBar;

	if (m_pEdgeBar)
	{
		m_pEdgeBar->CreateEdgeBar(this);
	}
	else
	{
		hr = E_OUTOFMEMORY;
	}

	return hr;
}

void TGDocumentController::DestroyEdgeBar()
{
	if (m_pEdgeBar)
	{
		delete m_pEdgeBar;
		m_pEdgeBar = NULL;
	}
}

HRESULT TGDocumentController::RemoveEdgeBarPage()
{
	HRESULT hr = NOERROR;

	if (m_pEdgeBar)
	{
		DestroyEdgeBar();
	}
	return hr;
}
