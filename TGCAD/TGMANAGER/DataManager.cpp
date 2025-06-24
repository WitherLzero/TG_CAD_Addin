#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager()
{
    // 测试性初始化，实际开发时应移除
    /*m_bindings.push_back({ _T("固定板长度"), _T("A") });
    m_bindings.push_back({ _T("侧板宽度"),  _T("B") });
    m_bindings.push_back({ _T("螺钉直径"), _T("C") });
    m_bindings.push_back({ _T("轴承高度"), _T("D") });
    m_bindings.push_back({ _T("轮直径"), _T("E") });*/
    m_bindings.push_back({ _T("Fixed plate length"), _T("A") });
    m_bindings.push_back({ _T("Side plate width"),  _T("B") });
    m_bindings.push_back({ _T("Screw diameter"), _T("C") });
    m_bindings.push_back({ _T("Bearing height"), _T("D") });
    m_bindings.push_back({ _T("Wheel diameter"), _T("E") });

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
    return false;
}

bool DataManager::UpdateBinding(const CString& paramName, const CString& newVarName)
{
    return false;
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
