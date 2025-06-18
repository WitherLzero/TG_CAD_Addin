#include "stdafx.h"
#include "TGEdgeBarParent.h"

TGEdgeBarParent::TGEdgeBarParent()
{
}

TGEdgeBarParent::~TGEdgeBarParent()
{
}


BEGIN_MESSAGE_MAP(TGEdgeBarParent, CWnd)
	//{{AFX_MSG_MAP(CEdgeBarParent)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void TGEdgeBarParent::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CWnd *pChild = GetWindow( GW_CHILD );

	while( pChild )
	{
		pChild->MoveWindow(0, 0, cx, cy);
		pChild = pChild->GetWindow( GW_HWNDNEXT );
	}
}