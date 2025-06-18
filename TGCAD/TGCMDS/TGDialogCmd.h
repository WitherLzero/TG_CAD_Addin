#pragma once
#include "../TGCmds/TGCmdBase.h"
#include "../TGDialogs/TGDialog.h"
#include "../TGCADApp.h"
#include "../TGDialogs/TGEdgebar.h"
#include "../TGDialogs/TGEdgebarparent.h"
#include "../TGCore/TGCAD.h"


// 弹窗命令
template<typename T>
class TGCmdDialog : public TGCCmdBase
{
public:
	TGCmdDialog() {
		m_pDialog = nullptr;
		m_bActive = true;
	};
	~TGCmdDialog() = default;

public:
	// 创建界面
	void CreateTGDialog() {
		m_pDialog = new T();
		m_pDialog->Create(m_pDialog->GetDialogIDD(), NULL);
		m_pDialog->ShowWindow(SW_SHOW);
		m_pDialog->CenterWindow();
	};

	// 命令激活
	STDMETHOD(Activate)()
	{
		HRESULT hr = S_OK;
		if (m_bActive) // 命令激活状态才做界面的创建
			CreateTGDialog();
		m_bActive = true; // 刷新状态
		return hr;
	};

	// 命令休眠
	STDMETHOD(Deactivate)()
	{
		HRESULT hr = S_OK;
		m_bActive = false;
		return hr;
	};

	// 命令销毁
	STDMETHOD(Terminate)(void)
	{
		if (nullptr != m_pDialog) {
			m_pDialog->DestroyWindow();
			delete m_pDialog;
			m_pDialog = nullptr;
		}
		return S_OK;
	};

public:
	T* m_pDialog;
	bool m_bActive;
};


// 侧边栏命令
template<typename T>
class TGCmdEdgeBar : public TGCCmdBase
{
public:

	TGCmdEdgeBar() {
		m_pDialog = nullptr;
		m_bActive = true;
	};
	~TGCmdEdgeBar() = default;

public:
	// 创建侧边栏
	void CreateEdgeBar() {

		HRESULT hr = S_OK;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		TGEventManagerObj* eventManager = TGCADApp::GetTGApp()->GetTGAddin()->GetCommands();
		TGDocumentControllerObj* Obj = eventManager->GetDocument(TGEventManager::GetApplicationPtr()->GetActiveDocument());
		TGEdgeBar* edgebar = Obj->GetEdgeBar();
		m_pDialog = new T();

		TGEdgeBarParent* edgebarParent = edgebar->GetEdgeBarParent();
		m_pDialog->Create(m_pDialog->GetDialogIDD(), edgebarParent);

		CRect r;
		HWND hwndParent = edgebarParent->GetSafeHwnd();
		::GetWindowRect(hwndParent, &r);
		m_pDialog->MoveWindow(0, 0, r.right - r.left, r.bottom - r.top);

		m_pDialog->ShowWindow(SW_SHOW);
	};

	// 命令激活
	STDMETHODIMP Activate() {
		HRESULT hr = S_OK;
		if (m_bActive) // 命令激活状态才做界面的创建
			CreateEdgeBar();
		m_bActive = true; //刷新状态
		return hr;
	};

	// 命令休眠
	STDMETHOD(Deactivate)() {
		HRESULT hr = S_OK;
		m_bActive = false;
		return hr;
	};

	// 命令终止
	STDMETHOD(Terminate)() {
		HRESULT hr = S_OK;
		if (m_pDialog != nullptr)
		{
			delete m_pDialog;
			m_pDialog = nullptr;
		}
		return hr;
	};
public:
	T* m_pDialog;
	bool m_bActive;
};
