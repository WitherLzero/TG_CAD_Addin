#pragma once
#include "../TGManager/TGEventManager.h"

class TGEdgeBarParent;
class TGEdgeBar
{
public:
	TGEdgeBar();
	~TGEdgeBar();

	HRESULT CreateEdgeBar(TGDocumentController* pedgebartstDoc);
	void DeleteEdgeBar( );

	TGEdgeBarParent* GetEdgeBarParent() { return m_pDialog; }

private:
	TGDocumentController* m_pEdgeBarDoc;
	TGEdgeBarParent* m_pDialog;
	CWnd m_hWndEdgeBarPage;

};

