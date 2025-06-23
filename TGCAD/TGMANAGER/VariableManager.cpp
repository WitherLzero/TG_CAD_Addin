#include "stdafx.h"
#include "VariableManager.h"

VariableManager::VariableManager()
{
	m_cache.push_back({ _T("A"), 123.45 });
	m_cache.push_back({ _T("B"), 678.90 });
	m_cache.push_back({ _T("C"), 111.22 });
}


VariableManager::~VariableManager()
{
	m_cache.clear();
	m_pVars = nullptr;
	m_pDoc = nullptr;
}

double VariableManager::GetVarValue(const CString& varName) const
{
	for (const auto& var : m_cache)
	{
		if (var.name.CompareNoCase(varName) == 0)  // 忽略大小写对比
		{
			return var.value;
		}
	}

	// 没找到，返回默认值（可以改为抛异常或错误日志）
	return 0.0;
}

bool VariableManager::AttachDoc(AssemblyDocumentPtr pDoc)
{
	if (pDoc == nullptr) return false;
	m_pDoc = pDoc;

	m_pVars = m_pDoc->GetVariables();

	return LoadVarsFromModel();
}

bool VariableManager::GetVarNames(std::vector<CString>& outNames) const
{
	outNames.clear();
	for (const auto& var : m_cache)
		outNames.push_back(var.name);
	return true;
}

bool VariableManager::LoadVarsFromModel()
{
	/*m_cache.clear();
	if (!m_pVars) return false;

	int nCnt = m_pVars->GetCount();

	for (int i = 1; i <= nCnt; ++i) {
		variablePtr pVar = m_pVars->Item(i);
		_bstr_t bstrName = pVar->GetName();
		double value = pVar->GetValue();

		CString name = CString((wchar_t*)bstrName);
		m_cache.push_back({ name,value });
	}*/

	return true;
}
