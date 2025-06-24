#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager()
{
    // 测试性初始化，实际开发时应移除
    m_bindings.push_back({ _T("Length"), _T("A") });
    m_bindings.push_back({ _T("Width"),  _T("B") });
    m_bindings.push_back({ _T("Height"), _T("C") });
}

bool DataManager::AddBinding(const CString& paramName, const CString& varName)
{
    if (IsParamNameExist(paramName) || IsVarNameBound(varName)) {
        return false;
    }
    m_bindings.push_back({ paramName,varName });
    return true;
}

bool DataManager::RemoveBinding(const CString& paramName)
{
    int idx = FindIndexByParamName(paramName);
    if (idx == -1) {
        return false;
    }
    m_bindings.erase(m_bindings.begin() + idx);
    return false;
}

bool DataManager::UpdateBinding(const CString& oldName, const CString& newName)
{
    int idx = FindIndexByParamName(oldName);
    if (idx == -1) {
        return false;
    }
    m_bindings[idx].paramName = newName;
    return true;
}

void DataManager::ClearBindings()
{
    m_bindings.clear();
}

bool DataManager::IsParamNameExist(const CString& paramName) const
{
    return FindIndexByParamName(paramName) != -1;
}

bool DataManager::IsVarNameBound(const CString& varName) const
{
    return FindIndexByVarName(varName) != -1;
}

int DataManager::GetBindingCount() const
{
    return static_cast<int>(m_bindings.size());
}

bool DataManager::GetVarNameByParam(const CString& paramName, CString& outVarName) const
{
    int idx = FindIndexByParamName(paramName);
    if (idx == -1) return false;
    outVarName = m_bindings[idx].varName;
    return true;
}

int DataManager::FindIndexByParamName(const CString& paramName) const
{
    for (size_t i = 0; i < m_bindings.size(); ++i) {
        if (m_bindings[i].paramName == paramName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int DataManager::FindIndexByVarName(const CString& varName) const
{
    for (size_t i = 0; i < m_bindings.size(); ++i) {
        if (m_bindings[i].varName == varName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
