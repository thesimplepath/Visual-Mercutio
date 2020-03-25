/****************************************************************************
 * ==> PSS_IOStreamGrid ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a input/output stream grid                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_IOStreamGrid.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_IOStreamGrid
//---------------------------------------------------------------------------
PSS_IOStreamGrid::PSS_IOStreamGrid(CGXGridCore* pGridCore) :
    PSS_IStreamGrid(pGridCore),
    PSS_OStreamGrid(pGridCore)
{}
//---------------------------------------------------------------------------
PSS_IOStreamGrid::~PSS_IOStreamGrid()
{}
//---------------------------------------------------------------------------
