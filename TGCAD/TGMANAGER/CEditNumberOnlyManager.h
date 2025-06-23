#pragma once
#include <afxwin.h>

class CEditNumberOnlyManager : public CEdit
{
public:
    CEditNumberOnlyManager() = default;
    virtual ~CEditNumberOnlyManager() = default;

protected:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP()

};
