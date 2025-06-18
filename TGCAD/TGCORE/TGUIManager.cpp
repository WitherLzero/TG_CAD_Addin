#include "stdafx.h"
#include "TGUIManager.h"
#include "../resource.h"
#include "../SDK/include/tgcatids.h"
#include "../TGHelper/character.h"
#include "../MyCommands.h"
#include <comdef.h>

TGUIManager TGUIManager::m_Instance = TGUIManager();

bool TGUIManager::extractData(const wstring& strExtractPath, unsigned long lFileId, const wstring& strFlag)
{
	HMODULE hModule = GetModuleHandle(L"TGCAD.dll");
	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(lFileId), strFlag.c_str());
	DWORD dwResSize = SizeofResource(hModule, hResource);
	HGLOBAL hResData = LoadResource(hModule, hResource);
	// Checking
	if (hResData != NULL && dwResSize != 0)
	{
		// Ensure the lpData is NULL
		LPVOID lpData = NULL;
		// Obtain the string pointer from the loaded resource handle
		lpData = LockResource(hResData);

		// Save the current read data into a file
		HANDLE hFile = CreateFile(strExtractPath.c_str(),
			GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD        dwByteWrite = 0;
		// Check the return handle value
		if (NULL != hFile && INVALID_HANDLE_VALUE != hFile)
		{
			// Move the file pointer to the begin of the file
			SetFilePointer(hFile, 0, 0, FILE_BEGIN);
			// Write the read data into a temp file
			WriteFile(hFile,
				(LPBYTE)lpData,
				dwResSize,
				&dwByteWrite,
				NULL);

			// Close the current open data file
			if (NULL != hFile) {
				CloseHandle(hFile);
			}
			hFile = NULL;
			FreeResource(hResData);
			return true;
		}
		FreeResource(hResData);
	}
	FreeResource(hResData);
	return false;
}

bool TGUIManager::extractData_new(const wstring& strExtractPath, unsigned long lFileId, const wstring& strFlag)
{
	for (size_t i = 0; i < 3; i++)
	{
		::DeleteFile(strExtractPath.c_str());
		if (extractData(strExtractPath, lFileId, strFlag) && ::PathFileExists(strExtractPath.c_str()))
		{
			return true;
		}

		Sleep(500);
	}
	return false;
}

std::vector<const XMLAttribute*> TGUIManager::getAllAttributes(XMLElement* element)
{
	std::vector<const XMLAttribute*> vecAttribute;
	if (element != nullptr)
	{
		const XMLAttribute* attribute = element->FirstAttribute();
		while (attribute != nullptr)
		{
			vecAttribute.push_back(attribute);
			attribute = attribute->Next();
		}
	}
	return vecAttribute;
}

std::vector<XMLElement*> TGUIManager::getAllChildElement(XMLElement* parent)
{
	std::vector<XMLElement*> vecElement;
	for (XMLElement* elem = parent->FirstChildElement();elem != NULL; elem = elem->NextSiblingElement())
		vecElement.push_back(elem);
	return vecElement;
}

void TGUIManager::getRibbonCtrl(XMLElement* rootRibbon)
{
	std::vector<XMLElement*> vecTab = getAllChildElement(rootRibbon);
	for (int iTab = 0; iTab < vecTab.size(); iTab++)
	{
		TGTab tab;
		tab.s_tabName = TEXT_UTF8_TO_WCHAR(vecTab[iTab]->Attribute("name"));
		std::vector<XMLElement*> vecGroup = getAllChildElement(vecTab[iTab]);
		for (int iGroup = 0; iGroup < vecGroup.size(); iGroup++)
		{
			TGGroup group;
			group.s_groupName = TEXT_UTF8_TO_WCHAR(vecGroup[iGroup]->Attribute("name"));
			std::vector<XMLElement*> vecCtrl = getAllChildElement(vecGroup[iGroup]);
			for (int iCtrl = 0; iCtrl < vecCtrl.size(); iCtrl++)
			{
				TGControl control;
				control.s_ctrlName = TEXT_UTF8_TO_WCHAR(vecCtrl[iCtrl]->Name());
				std::vector<const XMLAttribute*> vecAttribute = getAllAttributes(vecCtrl[iCtrl]);
				for (int iAttr = 0; iAttr < vecAttribute.size(); iAttr++)
				{
					TGCtrlAttr attribute;
					attribute.s_AttrName = TEXT_UTF8_TO_WCHAR(vecAttribute[iAttr]->Name());
					attribute.s_AttrVal = TEXT_UTF8_TO_WCHAR(vecAttribute[iAttr]->Value());
					control.v_attr.push_back(attribute);
				}
				group.v_ctrl.push_back(control);
			}
			tab.v_group.push_back(group);
		}
		m_vecTab.push_back(tab);
	}
}

void TGUIManager::getCtrlAgmData(wstring xmlName)
{
	TCHAR szTemp[MAX_PATH] = { 0 };
	GetTempPath(MAX_PATH, szTemp);
	wstring strTemp(szTemp);
	wstring strAgm = strTemp + xmlName;
	if (extractData_new(strAgm, IDR_XML2, L"XML"))
	{
		auto pXmlDoc = std::make_shared<tinyxml2::XMLDocument>();
		if (!pXmlDoc->LoadFile(TEXT_ALWAYS_CHAR(strAgm.c_str())))
		{
			XMLElement* rootRibbon = pXmlDoc->RootElement();
			if (rootRibbon == nullptr)
				throw std::exception("XML�ļ�Ϊ��");
			getRibbonCtrl(rootRibbon);
			::DeleteFile(strAgm.c_str());
		}
		else
		{
			throw std::exception("����XML�ļ�ʧ��");
		}
	}
	else
	{
		throw std::exception("����Դ�ļ�����ȡXML��Դʧ��");
	}
}

void TGUIManager::createUserUI(ISEAddInEx2Ptr pAddInEx2, GUID environmentGuid, EnvironmentPtr pEnvironment, CString strCommandPrefix, _bstr_t bstrResourceFilename)
{
	m_vecTab.clear();
	wstring xmlName = L"TGPDMRibbon.xml";
	getCtrlAgmData(xmlName);
	
	std::vector<MY_COMMAND_INFO> vecCommandInfo;
	for (int iTab = 0; iTab < m_vecTab.size(); iTab++)
	{
		for (int iGroup = 0; iGroup < m_vecTab[iTab].v_group.size(); iGroup++)
		{
			for (int iCtrl = 0; iCtrl < m_vecTab[iTab].v_group[iGroup].v_ctrl.size(); iCtrl++)
			{
				TGControl control = m_vecTab[iTab].v_group[iGroup].v_ctrl[iCtrl];
				MY_COMMAND_INFO commandInfo;
				commandInfo.iCategory = m_vecTab[iTab].s_tabName.c_str();
				commandInfo.iGroup = m_vecTab[iTab].v_group[iGroup].s_groupName.c_str();
				commandInfo.iCommand = _ttoi(control.v_attr[0].s_AttrVal.c_str());
				commandInfo.iString = control.v_attr[1].s_AttrVal.c_str();
				commandInfo.iImage = _ttoi(control.v_attr[2].s_AttrVal.c_str());
				commandInfo.buttonStyle = (SeButtonStyle)_ttoi(control.v_attr[3].s_AttrVal.c_str());
				vecCommandInfo.push_back(commandInfo);
			}
		}
	}
	if (vecCommandInfo.empty())
	{
		throw std::exception("XML��δ�ҵ��κοؼ�");
	}

	MY_ENVIRONMENT_INFO MyEnvironment = { environmentGuid, vecCommandInfo.data(), vecCommandInfo.size() };
	// Add the commands to the environment.
	for (int iCommand = 0; iCommand < MyEnvironment.nCommands; iCommand++)
	{
		MY_COMMAND_INFO pCommandInfo = MyEnvironment.pCommands[iCommand];
		UINT commandId = pCommandInfo.iCommand;
		_bstr_t bstrCategory(pCommandInfo.iCategory);
		CString szLocalized = pCommandInfo.iString;

		// Prepend the non-localized prefix.
		CString szCommandString = strCommandPrefix;
		szCommandString.AppendFormat(L"_Command%d", pCommandInfo.iCommand);
		szCommandString.Append(L"\n");
		szCommandString.Append(szLocalized);
		szCommandString.Append(L"\n");
		szCommandString.Append(szLocalized);


		CComSafeArray<BSTR> saCmdStrings(1);
		CComSafeArray<long> saCmdIDs(1);
		CComSafeArray<long> saTab1Group1CommandButtonStyles(1);

		// Populate arrays.
		HRESULT hr = S_OK;
		hr = saCmdStrings.SetAt((long)0, szCommandString.AllocSysString());
		hr = saCmdIDs.SetAt((long)0, pCommandInfo.iCommand);
		hr = saTab1Group1CommandButtonStyles.SetAt((long)0, seButtonIconAndCaption);

		hr = pAddInEx2->SetAddInInfoEx2(
			bstrResourceFilename,			// ResourceFilename
			pEnvironment->CATID,			// EnvironmentCatID
			bstrCategory,					// CategoryName (Ribbon Tab Name)
			pCommandInfo.iImage,			// IDColorBitmapMedium
			-1,								// IDColorBitmapLarge
			-1,								// IDMonochromeBitmapMedium
			-1,								// IDMonochromeBitmapLarge
			1,								// NumberOfCommands
			saCmdStrings.GetSafeArrayPtr(),	// CommandNames
			saCmdIDs.GetSafeArrayPtr(),		// CommandIDs
			saTab1Group1CommandButtonStyles.GetSafeArrayPtr());
		{
			CComBSTR bstrCommandBarName;

			bstrCommandBarName.AppendBSTR(bstrCategory);
			bstrCommandBarName.Append(L"\n");

			// Load group from string resource.
			CComBSTR bstrGroup = pCommandInfo.iGroup;
			bstrCommandBarName.Append(bstrGroup.m_str);
			CommandBarButtonPtr pButton = pAddInEx2->AddCommandBarButton(pEnvironment->CATID, bstrCommandBarName.m_str, pCommandInfo.iCommand);
			if (pButton)
			{
				pButton->Style = pCommandInfo.buttonStyle;
			}
		}
	}
}





