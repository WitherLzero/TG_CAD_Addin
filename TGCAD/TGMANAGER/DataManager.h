#pragma once
#include<vector>
#include<string>
#include<fstream>
#include <sstream>
#include <algorithm>
#include <atlstr.h> // CString

struct ParamVarBinding
{
	CString paramName;  // defined by users
	CString varName;    // get from doc's var Table
};

typedef std::vector<ParamVarBinding> BindingList; 

class DataManager
{
public:
    DataManager();
    // 绑定管理
    bool AddBinding(const CString& paramName, const CString& varName);   // 新增映射（自动校验唯一性）
    bool RemoveBinding(const CString& paramName);                             // 按参数名删除
    bool UpdateBinding(const CString& oldParamName, const CString& newParamName); // 更新绑定
    void ClearBindings();                                                     // 清空全部

    // 查找&检查
    bool IsParamNameExist(const CString& paramName) const;                    // 检查参数名是否已存在
    bool IsVarNameBound(const CString& varName) const;              // 检查变量是否被绑定
    int  GetBindingCount() const;                                             // 获取绑定数量
    bool GetVarNameByParam(const CString& paramName, CString& outVarName) const; // 查询

    // 获取全部
    const BindingList& GetAllBindings() const { return m_bindings; }
    void SetAllBindings(const BindingList& binds) { m_bindings = binds; }

    // 文件持久化
    bool SaveConfigForDoc(AssemblyDocumentPtr pAssemDoc);
    bool SaveToFile(const CString& filePath) const;      // 保存到文件
    bool LoadFromFile(const CString& filePath);          // 从文件加载

    static CString GetDefaultConfigPath();               // 获取保存路径

private:

    BindingList m_bindings;
    ParamVarBinding data[5];

    // 帮助方法
    int FindIndexByParamName(const CString& paramName) const;
    int FindIndexByVarName(const CString& varName) const;
};

