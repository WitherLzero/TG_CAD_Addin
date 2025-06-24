#include "stdafx.h"
#include "VariableManager.h"

VariableManager::VariableManager()
{

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

	// 没找到，返回默认值
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
	m_cache.clear(); // 清空缓存

	if (!m_pDoc)
		return false;

	VariablesPtr pVars = m_pDoc->GetVariables();
	if (!pVars)
		return false;

	long count = pVars->GetCount();
	for (long i = 1; i <= count; ++i)
	{
		variablePtr pVar = pVars->Item(i);
		if (pVar)
		{
			_bstr_t bstrName = pVar->GetName();  // 获取变量名
			double val = pVar->GetValue();       // 获取变量值

			CString name = (wchar_t*)bstrName;

			ModelVariable mv;
			mv.name = name;
			mv.value = val;

			m_cache.push_back(mv);
		}
	}

	return !m_cache.empty();
}


bool VariableManager::SetVarValue(const CString& varName, double newValue)
{
	if (!m_pVars) {
		return false;
	}
	long count = m_pVars->GetCount();
	for (long i = 1; i <= count; ++i)
	{
		variablePtr pVar = m_pVars->Item(i);
		if (!pVar)
			continue;

		CString name = CString((wchar_t*)pVar->GetName());

		if (name.CompareNoCase(varName) == 0)
		{
			//设置新值
			pVar->PutValue(newValue);

			// 更新m_cache
			for (auto& var : m_cache)
			{
				if (var.name.CompareNoCase(varName) == 0)
				{
					var.value = newValue;
					break;
				}
			}

			return true;
		}
	}
	return false;
}
