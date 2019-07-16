/****************************************************************************
 * ==> zSctyAll ------------------------------------------------------------*
 ****************************************************************************
 * Description : Include file used to include all security classes          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zSctyAllH
#define zSctyAllH

// processsoft
#include <zScty\zSctyLib.h>

// resources
#include "zScty\zSctyRes.h"

// ***********************************************************
// *
// *  ZASecurityEntity
// *  
// ***********************************************************

#ifndef _Security_h__
#include "zScty\Security.h"
#endif 

// ***********************************************************
// *
// *  ZBKeyEntity, ZBKeyFile
// *
// ***********************************************************

#ifndef _ZBKeyFile_h__
#include "zScty\ZBKeyFile.h"
#endif

/**
* PSS_SecurityCheck
*/
#ifndef PSS_SecurityCheckH
    #include "zScty\PSS_SecurityCheck.h"
#endif

/**
*  PSS_CodeInputDialog
*/
#ifndef PSS_CodeInputDialogH
    #include "zScty\PSS_CodeInputDialog.h"
#endif

/**
*  PSS_StopPrintDialog
*/
#ifndef PSS_StopPrintDialogH
    #include "zScty\PSS_StopPrintDialog.h"
#endif

/**
*  PSS_EvaluationWarnDialog
*/
#ifndef PSS_EvaluationWarnDialogH
    #include "zScty\PSS_EvaluationWarnDialog.h"
#endif

#endif
