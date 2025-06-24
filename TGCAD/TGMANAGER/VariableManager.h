#pragma once
#include "stdafx.h"
#include "vector"


struct ModelVariable
{
	CString name;//A B C 系统里的变量名
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
	
	//通过变量名获取对应值
	double GetVarValue(const CString& varName) const;

	//修改变量对应值
	bool SetVarValue(const CString& varName, double newValue);

private:



private:
	AssemblyDocumentPtr m_pDoc;
	VariablesPtr m_pVars;
	VarList m_cache;

	bool LoadVarsFromModel();
};

