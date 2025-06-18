#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "SDK/include/tgcatids.h"

// Define the command IDs
enum MyCommandId
{
	
	idSave1,
	idSave2,
	idSave3,
	idFolder,
	idMonitor,
	idBox,
	idCamera,
	idPhotograph,
	idFavorites,
	idPrinter,
	idTools,
	idCommandPrompt,
	idNotepad,
	idHelp,
	idSearch,
	idQuestion,
	idCheckbox1,
	idCheckbox2,
	idCheckbox3,
	idRadiobutton1,
	idRadiobutton2,
	idRadiobutton3,
	idBoundingBox,
	idBoxes,
	idGdiPlus,

	//NDS CAD ADD
	idLogout,
	idExport,
	idDataMgr,
	idCustomPage,
	idCustomCommand
};


typedef struct MY_COMMAND_INFO_
{
	CString			iCategory;//Ribbon Tab Name
	CString			iGroup;//Group name
	UINT			iCommand;//Command id
	CString			iString;//Command name
	UINT			iImage;//Command image
	SeButtonStyle	buttonStyle;
} MY_COMMAND_INFO, *PMY_COMMAND_INFO;

typedef struct MY_ENVIRONMENT_INFO_
{
	GUID				environmentGuid;
	MY_COMMAND_INFO*	pCommands;
	UINT				nCommands;
} MY_ENVIRONMENT_INFO, *PMY_ENVIRONMENT_INFO;



