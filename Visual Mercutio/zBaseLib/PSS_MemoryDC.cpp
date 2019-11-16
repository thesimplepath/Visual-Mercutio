/****************************************************************************
 * ==> PSS_MemoryDC --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a memory device context                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MemoryDC.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_MemoryDC
//---------------------------------------------------------------------------
PSS_MemoryDC::PSS_MemoryDC(CDC* pDC) :
    CDC(),
    m_pDC(pDC),
    m_pOldBitmap(NULL),
    m_MemDC(FALSE)
{
    ASSERT(m_pDC);

    #ifndef WCE_NO_PRINTING
        m_MemDC = !pDC->IsPrinting();
    #endif

    // create a memory DC
    if (m_MemDC)
    {
        pDC->GetClipBox(&m_Rect);
        CreateCompatibleDC(pDC);
        m_Bitmap.CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height());
        m_pOldBitmap = SelectObject(&m_Bitmap);

        #ifndef _WIN32_WCE
            SetWindowOrg(m_Rect.left, m_Rect.top);
        #endif
    }
    else
    {
        // make a copy of the relevent parts of the current DC for printing
        m_hDC       = pDC->m_hDC;
        m_hAttribDC = pDC->m_hAttribDC;

        #ifndef WCE_NO_PRINTING
            m_bPrinting = pDC->m_bPrinting;
        #endif
    }
}
//---------------------------------------------------------------------------
PSS_MemoryDC::~PSS_MemoryDC()
{
    if (m_MemDC)
    {    
        // copy the offscreen bitmap onto the screen
        m_pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), this, m_Rect.left, m_Rect.top, SRCCOPY);

        // swap back the original bitmap
        SelectObject(m_pOldBitmap);

        m_Bitmap.DeleteObject();
    }
    else
        // replace the DC with an illegal value, this will prevent to accidently deleting the handles
        // associated with the CDC that was passed to the constructor
        m_hDC = m_hAttribDC = NULL;
}
//---------------------------------------------------------------------------
