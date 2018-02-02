// MemDC.cpp : implementation file

#include "stdafx.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



    // constructor sets up the memory DC
ZUMemoryDC::ZUMemoryDC(CDC* pDC) 
 : CDC()
{
    ASSERT(pDC != NULL);

    m_pDC = pDC;
    m_pOldBitmap = NULL;
#ifndef WCE_NO_PRINTING
    m_bMemDC = !pDC->IsPrinting();
#else
    m_bMemDC = FALSE;
#endif
          
    if (m_bMemDC)    // Create a Memory DC
    {
        pDC->GetClipBox(&m_rect);
        CreateCompatibleDC(pDC);
        m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
        m_pOldBitmap = SelectObject(&m_bitmap);
#ifndef _WIN32_WCE
        SetWindowOrg(m_rect.left, m_rect.top);
#endif
    }
    else        // Make a copy of the relevent parts of the current DC for printing
    {
#ifndef WCE_NO_PRINTING
        m_bPrinting = pDC->m_bPrinting;
#endif
        m_hDC       = pDC->m_hDC;
        m_hAttribDC = pDC->m_hAttribDC;
    }
}
    
    // Destructor copies the contents of the mem DC to the original DC
ZUMemoryDC::~ZUMemoryDC()
{
    if (m_bMemDC) 
    {    
        // Copy the offscreen bitmap onto the screen.
        m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                      this, m_rect.left, m_rect.top, SRCCOPY);

        //Swap back the original bitmap.
        SelectObject(m_pOldBitmap);

		m_bitmap.DeleteObject();
    } else {
        // All we need to do is replace the DC with an illegal value,
        // this keeps us from accidently deleting the handles associated with
        // the CDC that was passed to the constructor.
        m_hDC = m_hAttribDC = NULL;
    }
}
