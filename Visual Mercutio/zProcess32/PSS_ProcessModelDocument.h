/****************************************************************************
 * ==> PSS_ProcessModelDocument --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model document                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessModelDocumentH
#define PSS_ProcessModelDocumentH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_ProcessModelTree.h"

/**
* Process model document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ProcessModelDocument : public PSS_ProcessModelTree, public PSS_Observer
{
    DECLARE_DYNCREATE(PSS_ProcessModelDocument)

    public:
        PSS_ProcessModelDocument();
        virtual ~PSS_ProcessModelDocument();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessModelDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
