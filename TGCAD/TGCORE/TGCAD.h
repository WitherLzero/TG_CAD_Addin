#pragma once

#include "../resource.h"       
#include "../TGCmds/TGCmdBase.h"
#include "../SDK/include/tgcatids.h"

using namespace TGFramework;

#define COM_TYPELIBINTERFACE_ENTRY(x)\
	{&__uuidof(x), \
	offsetofclass(x, _ComMapClass), \
	_ATL_SIMPLEMAPENTRY},

//[TGTemple]请将此处的GUID替换为用户自己的GUID
DEFINE_GUID(CLSID_TGAddIn, 0x593a4974,0xd1d5,0x45c5,0xa7,0x4f,0x72,0x30,0x06,0x66,0xc2,0x9f);

class TGCAD :
	public ISolidEdgeAddIn,
	public CComObjectRoot,
	public ISupportErrorInfo,
	public CComCoClass<TGCAD, &CLSID_TGAddIn>
{
public:
	TGCAD()
	{
		m_vGUID.push_back(CATID_TGAssembly);
		m_vGUID.push_back(CATID_TGDraft);
		m_vGUID.push_back(CATID_TGPart);
		m_vGUID.push_back(CATID_TGDMPart);
		m_vGUID.push_back(CATID_TGSheetMetal);
		m_vGUID.push_back(CATID_TGDMSheetMetal);

		m_pCommands = NULL;
	}

	~TGCAD()
	{
		m_pCommands = NULL;
	}
	DECLARE_REGISTRY_RESOURCEID(IDR_NEX3DMODELINGTOOL)

	BEGIN_COM_MAP(TGCAD)
		COM_TYPELIBINTERFACE_ENTRY(ISolidEdgeAddIn)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(TGCAD)
	END_CONNECTION_POINT_MAP()


	// ISupportErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	// ISolidEdgeAddin
	STDMETHOD(raw_OnConnection)(THIS_ IDispatch* pAppDispatch, SeConnectMode ConnectMode, TGFramework::AddIn* pUnkAddIn);
	STDMETHOD(raw_OnConnectToEnvironment)(BSTR EnvironmentCatid, LPDISPATCH pEnvironment, VARIANT_BOOL bFirstTime);
	STDMETHOD(raw_OnDisconnection)(THIS_ SeDisconnectMode DisconnectMode);

	ApplicationPtr GetApplication();
	TGEventManagerObj* GetCommands()
	{
		return m_pCommands;
	}

private:
	HRESULT CreateRibbon(GUID environmentGuid, EnvironmentPtr pEnvironment, VARIANT_BOOL bFirstTime);

private:
	std::vector<GUID> m_vGUID;
	ApplicationPtr m_pApplication;

protected:
	TGEventManagerObj* m_pCommands;
};

