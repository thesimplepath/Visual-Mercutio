/****************************************************************************
 * ==> PSS_ProcessIterator -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process iterator                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessIteratorH
#define PSS_ProcessIteratorH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// class name mapping
#ifndef PSS_BaseActivity
    //#define PSS_BaseActivity ZBaseActivity
#endif

// forward class declarations
class PSS_BaseActivity;
class PSS_Activity;
class ZProcess;

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Process iterator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessIterator
{
    public:
        /**
        * Constructor
        *@param pProcess - process
        */
        PSS_ProcessIterator(ZProcess* pProcess = NULL);

        virtual ~PSS_ProcessIterator();

        /**
        * Gets the first base activity
        *@return the first base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetFirstBaseActivity();

        /**
        * Gets the first valid activity
        *@return the first valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetFirstValidActivity();

        /**
        * Gets the first valid base activity
        *@return the first valid base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetFirstValidBaseActivity();

        /**
        * Gets the last base activity
        *@return the last base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetLastBaseActivity();

        /**
        * Gets the last valid activity
        *@return the last valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetLastValidActivity();

        /**
        * Gets the last base activity within the same process
        *@return the last base activity within the same process
        */
        virtual PSS_Activity* GetLastActivityWithinProcess();

        /**
        * Gets the parent activity
        *@param pActivity - activity
        *@return the activity parent process, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetParent(PSS_BaseActivity* pActivity);

        /**
        * Gets the activity parent process
        *@param pActivity - activity
        *@return the activity parent process, NULL if not found or on error
        */
        virtual ZProcess* GetParentProcess(PSS_BaseActivity* pActivity);

        /**
        * Gets the previous valid activity
        *@return the previous valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousValidActivity();

        /**
        * Gets the previous base activity
        *@return the previous base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousBaseActivity();

        /**
        * Gets the previous valid base activity
        *@return the previous valid base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousValidBaseActivity();

        /**
        * Gets the next valid activity
        *@return the next valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextValidActivity();

        /**
        * Gets the next base activity
        *@return the next base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextBaseActivity();

        /**
        * Gets the next valid base activity
        *@return the next valid base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextValidBaseActivity();

        /**
        * Gets the previous process
        *@return the previous process, NULL if not found or on error
        */
        virtual ZProcess* GetPreviousProcess();

        /**
        * Gets the next process
        *@return the next process, NULL if not found or on error
        */
        virtual ZProcess* GetNextProcess();

        /**
        * Starts the iterator using an activity and a process
        *@param pActivity - the activity to iterate
        *@param pProcess - the process
        *@return the next activity
        */
        virtual PSS_BaseActivity* StartIterator(PSS_BaseActivity* pActivity = NULL, ZProcess* pProcess = NULL);

        /**
        * Starts the iterator using an activity name and a process
        *@param activityName - the activity name to iterate
        *@param pProcess - the process
        *@return the next activity
        */
        virtual PSS_BaseActivity* StartIterator(const CString& activityName, ZProcess* pProcess = NULL);

        /**
        * Finds an activity
        *@param activityName - the activity name to search
        *@return the activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* FindActivity(const CString& activityName);

    private:
        PSS_BaseActivity* m_IteratorActivityPointer;
        ZProcess*         m_pProcess;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessIterator(const PSS_ProcessIterator& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProcessIterator& operator = (const PSS_ProcessIterator& other);
};

#endif
