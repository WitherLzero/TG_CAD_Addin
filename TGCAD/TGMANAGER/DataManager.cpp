#include "stdafx.h"
#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h> // 跨平台的目录检查
#include <windows.h>  // 用于CreateDirectory

DataManager::DataManager()
{
    // 测试性初始化，实际开发时应移除
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
// 跨平台的目录存在检查
bool DirectoryExists(const CString& path)
{
    DWORD attrib = GetFileAttributes(path);
    return (attrib != INVALID_FILE_ATTRIBUTES &&
        (attrib & FILE_ATTRIBUTE_DIRECTORY));
}

// 创建目录（如果不存在）
void EnsureConfigDirectoryExists()
{
    CString configDir = _T("CONFIG");
    if (!DirectoryExists(configDir))
    {
        CreateDirectory(configDir, NULL);
    }
}

CString DataManager::GetDefaultConfigPath()
{
    CString configDir = _T("CONFIG");
    if (!DirectoryExists(configDir)) {
        CreateDirectory(configDir, NULL);
    }
    return configDir + _T("\\param_mapping.txt");
}

bool DataManager::SaveToFile(const CString& filePath) const
{
    EnsureConfigDirectoryExists();

    CStringA utf8Path(filePath);
    std::ofstream outFile(utf8Path, std::ios::out);
    if (!outFile.is_open()) {
        return false;
    }

    // 写入文件头
    outFile << "# Param-Variable Mapping File\n";
    outFile << "# Format: paramName=varName\n\n";

    // 写入所有绑定关系
    for (const auto& binding : m_bindings) {
        CStringA utf8Param(binding.paramName);
        CStringA utf8Var(binding.varName);
        outFile << utf8Param << "=" << utf8Var << "\n";
    }

    outFile.close();
    return true;
}

bool DataManager::LoadFromFile(const CString& filePath)
{
    CStringA utf8Path(filePath);
    std::ifstream inFile(utf8Path, std::ios::in);
    if (!inFile.is_open()) {
        return false;
    }

    m_bindings.clear(); // 清空现有绑定

    std::string line;
    while (std::getline(inFile, line)) {
        // 跳过空行和注释
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // 解析param=var格式
        size_t equalPos = line.find('=');
        if (equalPos != std::string::npos) {
            std::string paramStr = line.substr(0, equalPos);
            std::string varStr = line.substr(equalPos + 1);

            // 转换为CString并添加绑定
            m_bindings.push_back({
                CString(paramStr.c_str()),
                CString(varStr.c_str())
                });
        }
    }

    inFile.close();
    return true;
}