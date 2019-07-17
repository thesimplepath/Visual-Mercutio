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

/**
* PSS_KeyEntity, PSS_KeyFile
*/
#ifndef PSS_KeyFileH
    #include "zScty\PSS_KeyFile.h"
#endif

/**
*  PSS_SecurityEntity, PSS_Security
*/
#ifndef PSS_SecurityH
    #include "zScty\PSS_Security.h"
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
