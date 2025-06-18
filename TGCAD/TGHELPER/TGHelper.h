#pragma once

#include <vector>

class TGHelper
{
public:
	TGHelper();
	virtual ~TGHelper();

public:

	static bool IsCurActiveDocIsTemp();
	static CString GetCurActiveDocName();
	static CString GetCurActiveDocFullPath();
	static DocumentTypeConstants GetCurActiveDocType();
	static bool CurActiveDocTypeIsAsm();
	static bool CurActiveDocTypeIsPar();
	static bool CurActiveDocTypeIsDft();
	static bool CurActiveDocTypeIsPsm();

	static bool FileNameIsAsm(const CString& fileNamePath);
	static bool FileNameIsPar(const CString& fileNamePath);
	static bool FileNameIsDft(const CString& fileNamePath);
	static bool FileNameIsCfg(const CString& fileNamePath);
	static bool FileNameIsPsm(const CString& fileNamePath);

	static TGFramework::SolidEdgeDocumentPtr GetCurActiveDoc();
	static bool SaveAsCurActiveDocToJpg(const CString& jpgFilePath);
	static bool SaveAsActiveWindowToJpg(ApplicationPtr AppPtr, const CString& jpgFilePath, bool bFitView = true);

	static bool OpenFile(const CString& filePath);
	static bool CloseFile(const CString& filePath);
	static bool CloseCurActiveFile();

	static bool SaveCurActiveDocToFilePath(const CString& saveFilePath);

	static bool GetAllCurOpenDocs(std::vector<CString>& getFiles);

	static bool DocIsDirty(const CString& fileNamePath);

	static bool QuitCAD();

	static HWND GetCADHwnd();

	static bool ExportCurActiveDoc(const CString& exportDocFileNamePath);


	static bool CallCadCommand(long cmdId);
};