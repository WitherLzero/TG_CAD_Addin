#include "stdafx.h"
#include "VariableManager.h"

VariableManager::VariableManager()
{

}


VariableManager::~VariableManager()
{
	m_cache.clear();
	m_varMap.clear();
	m_pDoc = nullptr;
}

bool VariableManager::AttachDoc(AssemblyDocumentPtr pDoc)
{
	if (pDoc == nullptr) return false;
	m_pDoc = pDoc;

	m_pParts = m_pDoc->GetParts();

	return LoadVarsFromModel();
}

bool VariableManager::GetVarNames(std::vector<CString>& outNames) const
{
    outNames.clear();
    for (const auto& var : m_cache)
        outNames.push_back(MakeFullVarId(var.docName, var.varName));
    return true;
}

// 通过变量唯一名查找变量对象并返回其当前值
double VariableManager::GetVarValue(const CString& fullVarId) const
{
    auto it = m_varMap.find(fullVarId);
    if (it != m_varMap.end() && it->second) {
        return it->second->GetValue();
    }
    // 没找到时返回0.0，可根据需要调整为抛异常或返回可选类型
    return 0.0;
}

// 通过变量唯一名修改变量值，自动同步本地显示缓存
bool VariableManager::SetVarValue(const CString& fullVarId, double newValue)
{
    auto it = m_varMap.find(fullVarId);
    if (it != m_varMap.end() && it->second) {
        it->second->PutValue(newValue); // 调用COM接口写入
        // 同步本地显示缓存
        for (auto& mv : m_cache) {
            if (MakeFullVarId(mv.docName, mv.varName).CompareNoCase(fullVarId) == 0) {
                mv.value = newValue;
                break;
            }
        }
        return true;
    }
    return false;
}

// 核心：遍历装配文档和所有零件文档的变量，维护本地缓存与变量指针映射
bool VariableManager::LoadVarsFromModel()
{
    m_cache.clear(); // 清空变量显示缓存
    m_varMap.clear(); // 清空哈希映射（保证同步）
    if (!m_pDoc) return false;

    // 1. 装配文档自身变量
    VariablesPtr pVars = m_pDoc->GetVariables();
    CString asmName = (LPCWSTR)m_pDoc->GetName(); // 用作装配唯一名
    if (pVars) {
        long count = pVars->GetCount();
        for (long i = 1; i <= count; ++i) {
            variablePtr pVar = pVars->Item(i);
            if (pVar) {
                CString varName = CString((wchar_t*)pVar->GetName());
                double val = pVar->GetValue();
                CString fullId = MakeFullVarId(asmName, varName);

                // 维护显示缓存
                m_cache.push_back({ asmName, varName, val });
                // 维护变量名->指针映射
                m_varMap[fullId] = pVar;
            }
        }
    }

    // 2. 遍历所有零件文档，获取其变量
    if (m_pParts) {
        long nParts = m_pParts->GetCount();
        for (long i = 1; i <= nParts; ++i) {
            PartPtr pPart = m_pParts->Item(i);
            PartDocumentPtr pPartDoc = pPart->GetPartDocument();
            if (pPartDoc) {
                CString partName = (LPCWSTR)pPartDoc->GetName(); // 作为零件唯一标识
                VariablesPtr pPartVars = pPartDoc->GetVariables();
                if (pPartVars) {
                    long nVar = pPartVars->GetCount();
                    for (long j = 1; j <= nVar; ++j) {
                        variablePtr pVar = pPartVars->Item(j);
                        if (pVar) {
                            CString varName = CString((wchar_t*)pVar->GetName());
                            double val = pVar->GetValue();
                            CString fullId = MakeFullVarId(partName, varName);

                            // 维护显示缓存
                            m_cache.push_back({ partName, varName, val });
                            // 维护变量名->指针映射
                            m_varMap[fullId] = pVar;
                        }
                    }
                }
            }
        }
    }
    // 返回是否有变量被加载
    return !m_cache.empty();
}



