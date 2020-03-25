/****************************************************************************
 * ==> PSS_IStreamGrid -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input stream grid                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_IStreamGrid.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_IStreamGrid
//---------------------------------------------------------------------------
PSS_IStreamGrid::PSS_IStreamGrid(CGXGridCore* pGridCore) :
    PSS_IOSGrid(pGridCore)
{}
//---------------------------------------------------------------------------
PSS_IStreamGrid::~PSS_IStreamGrid()
{}
//---------------------------------------------------------------------------
