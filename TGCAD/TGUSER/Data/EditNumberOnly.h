#pragma once
#include <afxwin.h>

class CEditNumberOnly : public CEdit
{
public:
    CEditNumberOnly() = default;
    virtual ~CEditNumberOnly() = default;

protected:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP()
};
