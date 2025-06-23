#include "stdafx.h"
#include "CEditNumberOnlyManager.h"

BEGIN_MESSAGE_MAP(CEditNumberOnlyManager, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

void CEditNumberOnlyManager::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar >= '0' && nChar <= '9') {
        CEdit::OnChar(nChar, nRepCnt, nFlags);
        return;
    }

    if (nChar == '.') {
        CString strText;
        GetWindowText(strText);
        if (strText.Find('.') == -1) {
            CEdit::OnChar(nChar, nRepCnt, nFlags);
        }
        return;
    }

    if (nChar == VK_BACK || nChar == VK_DELETE || nChar == VK_LEFT || nChar == VK_RIGHT) {
        CEdit::OnChar(nChar, nRepCnt, nFlags);
        return;
    }
}
