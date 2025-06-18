#pragma once
#include <iostream>
#include <mutex>

#include "TGCmdBase.h"

class TGCmdManager
{
public:
	~TGCmdManager() {};

	static TGCmdManager* Instance();
	void Destroy();
	void InsertCommand(const long CommandId, TGCCmdBase* instance);
	void CallCommand(const long CommandId);
	void InitCommandMap();
	void ClearCommandInstance();

private:
	TGCmdManager() {};
	static void Initialize();

private:
	std::map<long, TGCCmdBase*> m_CommandMap;
	static std::once_flag m_Init_flag;
	static TGCmdManager* m_Instance;
};