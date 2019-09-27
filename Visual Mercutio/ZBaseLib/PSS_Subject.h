/****************************************************************************
 * ==> PSS_Subject ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic subject                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SubjectH
#define PSS_SubjectH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <vector>

// forward declaration
class PSS_Observer;
class PSS_ObserverMsg;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic subject
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Subject
{
    public:
        virtual ~PSS_Subject();

        /**
        * Attaches an observer to the subject
        *@param pObserver - observer to attach to the subject
        */
        virtual void AttachObserver(PSS_Observer* pObserver);

        /**
        * Detaches an observer from the subject
        *@param pObserver - observer to detach from the subject
        */
        virtual void DetachObserver(PSS_Observer* pObserver);

        /**
        * Detaches all the observers from the subject
        */
        virtual void DetachAllObservers();

        /**
        * Notifies all the observers attached to the subject about a message
        *@param pMsg - message
        */
        virtual void NotifyAllObservers(PSS_ObserverMsg* pMsg);

    protected:
        PSS_Subject();

    private:
        std::vector<PSS_Observer*> m_Observers;
};

#endif
