
class TGEdgeBarParent : public CWnd
{
public:
	TGEdgeBarParent();
	virtual ~TGEdgeBarParent();

protected:
	//{{AFX_MSG(CEdgeBarParent)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

