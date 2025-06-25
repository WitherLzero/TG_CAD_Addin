#pragma once
#include "stdafx.h"
#include <vector>
#include <unordered_map>

// 单个变量的描述与缓存（用于界面显示和查找唯一变量）
struct ModelVariable
{
	CString docName;     // 所属文档/零件名称
	CString varName;     // 变量名
	double  value;       // 变量值
};

typedef std::vector<ModelVariable> VarList;

// CString 哈希与等于操作（用于unordered_map做key）
struct CStringHash {
	size_t operator()(const CString& str) const {
		return std::hash<std::wstring>()((LPCWSTR)str);
	}
};
struct CStringEqual {
	bool operator()(const CString& a, const CString& b) const {
		return a.CompareNoCase(b) == 0;
	}
};

// 变量唯一标识 => 变量COM对象的映射表
typedef std::unordered_map<CString, variablePtr, CStringHash, CStringEqual> VarPtrMap;

class VariableManager
{
public:
	VariableManager();
	~VariableManager();

	// 绑定到当前文档
	bool AttachDoc(AssemblyDocumentPtr pDoc);

	// 获取当前变量表中所有变量名
	bool GetVarNames(std::vector<CString>& outNames) const;
	
	// 通过变量名获取对应值
	double GetVarValue(const CString& varName) const;

	// 修改变量对应值
	bool SetVarValue(const CString& varName, double newValue);


private:
	// 数据成员
	AssemblyDocumentPtr m_pDoc;    // 当前装配文档
	PartsPtr            m_pParts;  // 装配下所有零件集合
	VarList             m_cache;   // 变量信息缓存（用于界面显示）
	VarPtrMap           m_varMap;  // 变量唯一名->变量指针 映射表（高效查找&写入）

	bool LoadVarsFromModel();

	// 生成变量唯一标识（推荐：文档名::变量名）
	CString MakeFullVarId(const CString& docName, const CString& varName) const {
		return docName + _T("::") + varName;
	}
};

