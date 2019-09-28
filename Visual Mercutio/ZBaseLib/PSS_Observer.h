/****************************************************************************
 * ==> PSS_Observer --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic observer                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObserverH
#define PSS_ObserverH

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

// forward class declarations
class PSS_Subject;
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
* Basic observer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Observer
{
    public:
        virtual ~PSS_Observer();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg) = 0;

        /**
        * Called when the observer is attached to the subject
        *@param pSubject - subject which attached the observer
        */
        virtual void OnSubjectAttaching(PSS_Subject* pSubject);

        /**
        * Called when the observer is detached from the subject
        *@param pSubject - subject which detached the observer
        */
        virtual void OnSubjectDetaching(PSS_Subject* pSubject);

    protected:
        std::vector<PSS_Subject*> m_Subjects;

        PSS_Observer();
};

#endif
