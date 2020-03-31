/****************************************************************************
 * ==> PSS_BasicSymbolVisitor ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol interface which can navigate through     *
 *               other symbol classes and visit them                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicSymbolVisitor.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_BasicSymbolVisitor
//---------------------------------------------------------------------------
PSS_BasicSymbolVisitor::PSS_BasicSymbolVisitor() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_BasicSymbolVisitor::~PSS_BasicSymbolVisitor()
{}
//---------------------------------------------------------------------------
