/****************************************************************************
 * ==> PSS_SearchSymbolLogLine ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a search symbol log line                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SearchSymbolLogLine.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SearchSymbolLogLine
//---------------------------------------------------------------------------
PSS_SearchSymbolLogLine::PSS_SearchSymbolLogLine() :
    PSS_GenericSymbolErrorLine()
{}
//---------------------------------------------------------------------------
PSS_SearchSymbolLogLine::PSS_SearchSymbolLogLine(const CString& symbolName,
                                                 const CString& symbolPath,
                                                 const CString& message) :
    PSS_GenericSymbolErrorLine(message, symbolName, symbolPath, -1, 2)
{}
//---------------------------------------------------------------------------
PSS_SearchSymbolLogLine::PSS_SearchSymbolLogLine(const CString& symbolName,
                                                 const CString& symbolPath,
                                                 UINT           messageID) :
    PSS_GenericSymbolErrorLine(messageID, symbolName, symbolPath, -1, 2)
{}
//---------------------------------------------------------------------------
PSS_SearchSymbolLogLine::~PSS_SearchSymbolLogLine()
{}
//---------------------------------------------------------------------------
