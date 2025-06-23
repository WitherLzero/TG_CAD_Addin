#include "stdafx.h"
#include "EditNumberOnly.h"

BEGIN_MESSAGE_MAP(CEditNumberOnly, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

void CEditNumberOnly::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
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

    MessageBeep(MB_OK);
}
