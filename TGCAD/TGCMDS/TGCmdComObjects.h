#pragma once

/*
	1. 该文件是命令类的Com对象头文件
	2. 一个Com对象对应一个命令按钮
*/

#include "../TGCmds/TGDialogCmd.h"
#include "../Demo/TGPopupDialog.h"
#include "../Demo/TGEdgebarDialog.h"
#include "../Demo/TGUserCmdPopup.h"
#include "../Demo/TGUserCmdEdgebar.h"
#include "../TGUSER/DialogCmd.h"
#include "../TGUSER/TGUserCmd.h"
#include "../TGUSER/SaveCmd.h"


// 弹窗命令Com对象 - 只需要弹出界面
typedef CComObject<TGCmdDialog<TGPopupDialog>> TGCmdDialogObj;

// 边栏命令Com对象- 需要弹出侧边栏
typedef CComObject<TGCmdEdgeBar<TGEdgebarDialog>> TGCmdEdgeBarObj;

// 用户自定义边栏命令Com对象 - 用户需要处理其他事件，则自定义Cmd
typedef CComObject<TGUserCmdEdgebar> TGCmdUserEdgebarObj;

// 用户自定义弹窗命令Com对象 - 用户需要处理其他事件，则自定义Cmd
typedef CComObject<TGUserCmdPopup> TGCmdUserCmdPopupObj;

// my Cmd
typedef CComObject<DialogCmd> DialogCmdObj;

typedef CComObject<TGUserCmd> TGCmdUserCmdObj;

typedef CComObject<SaveCmd> SaveCmdObj;