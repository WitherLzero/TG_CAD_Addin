#include "stdafx.h"
#include "TGCmdManager.h"
#include "../TGCADApp.h"
#include "../TGCore/TGCAD.h"
#include "TGCmdComObjects.h"

#include <atlbase.h>

#define INITCMDCOM(x,y)     x* y = nullptr;\
x::CreateInstance(&y);\
y->AddRef();\

std::once_flag TGCmdManager::m_Init_flag;
TGCmdManager* TGCmdManager::m_Instance;

TGCmdManager* TGCmdManager::Instance()
{
    std::call_once(m_Init_flag, &TGCmdManager::Initialize);
    return m_Instance;
}

void TGCmdManager::Initialize() 
{
    m_Instance = new TGCmdManager();
}

void TGCmdManager::Destroy()
{
    if (m_Instance != nullptr)
    {
        ClearCommandInstance();
        delete m_Instance;
    }
}

void TGCmdManager::ClearCommandInstance()
{
    for (const auto& pair : m_CommandMap) 
    {
        LPUNKNOWN pMyUnknown = NULL;
        pMyUnknown = pair.second->GetMyUnknown();
        if (pMyUnknown)
        {
            pMyUnknown->Release();
        }
    }
}

void TGCmdManager::InsertCommand(const long CommandId, TGCCmdBase* Cmd)
{
    m_CommandMap.insert(std::make_pair(CommandId,Cmd));
}

//[TGTemple]此处为用户自定义命令实例化与实例化自定义命令和CommandID关联处
//[TGTemple]1.请实例化自定义界面实例
//[TGTemple]2.请将实例化自定义界面与关联的CommandID放入Map容器
void TGCmdManager::InitCommandMap()
{
    INITCMDCOM(DialogCmdObj, DialogCommand);
    INITCMDCOM(SaveCmdObj, SaveCommand);


;
    InsertCommand(0, DialogCommand);
    InsertCommand(1, SaveCommand);

}

void TGCmdManager::CallCommand(const long CommandId)
{
    auto iterator = m_CommandMap.find(CommandId);
    if (iterator != m_CommandMap.end())
    {
        TGCAD* pAddin = TGCADApp::GetTGApp()->GetTGAddin();
        if (!pAddin)
            return;
        auto CmdBase = iterator->second;
        CmdBase->AddRef();
        CmdBase->SetCommandsObject(pAddin->GetCommands());
        HRESULT hr = CmdBase->CreateCommand(TGConstants::seNoDeactivate);
        if (SUCCEEDED(hr))
        {
            CmdBase->GetCommand()->Start();
        }
    }
}

