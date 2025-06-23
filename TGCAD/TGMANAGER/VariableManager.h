#pragma once
#include "stdafx.h"
#include "vector"


struct ModelVariable
{
	CString name;
	double value;
};

typedef std::vector<ModelVariable> VarList;

class VariableManager
{
public:
	VariableManager();
	~VariableManager();

	// 绑定到当前文档
	bool AttachDoc(AssemblyDocumentPtr pDoc);

	// 获取当前变量表中所有变量名
	bool GetVarNames(std::vector<CString>& outNames) const;


	bool GetVarValue(const CString& varName, double& outValue) const;

	bool SetVarValue(const CString& varName, double newValue);




private:
	AssemblyDocumentPtr m_pDoc;
	VariablesPtr m_pVars;
	VarList m_cache;

	bool LoadVarsFromModel();
};

