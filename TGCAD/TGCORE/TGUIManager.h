#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <Shlwapi.h>
#include "../TGHelper/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

#pragma comment(lib, "shlwapi")

struct TGControl;
struct TGGroup;
struct TGTab
{
	wstring s_tabName;
	std::vector<TGGroup> v_group;
};

struct TGGroup
{
	wstring s_groupName;
	std::vector<TGControl> v_ctrl;
};

struct TGCtrlAttr
{
	wstring s_AttrName;
	wstring s_AttrVal;
};

struct TGControl
{
	wstring s_ctrlName;
	std::vector<TGCtrlAttr> v_attr;
};

class TGUIManager
{
public:
	static TGUIManager& getInstance()
	{
		return m_Instance;
	}

private:
	TGUIManager() { m_vecTab.clear(); }
	static TGUIManager m_Instance;

public:
	bool extractData(const wstring& strExtractPath, unsigned long lFileId, const wstring& strFlag);
	bool extractData_new(const wstring& strExtractPath, unsigned long lFileId, const wstring& strFlag);
	std::vector<const XMLAttribute*> getAllAttributes(XMLElement* element);
	std::vector<XMLElement*> getAllChildElement(XMLElement* parent);
	void getRibbonCtrl(XMLElement* rootRibbon);
	void getCtrlAgmData(wstring xmlName);
	void createUserUI(ISEAddInEx2Ptr pAddInEx2, GUID environmentGuid, EnvironmentPtr pEnvironment, CString strCommandPrefix, _bstr_t bstrResourceFilename);
private:
	std::vector<TGTab> m_vecTab;
};



