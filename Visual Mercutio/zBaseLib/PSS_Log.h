/****************************************************************************
 * ==> PSS_Log -------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a logger                                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogH
#define PSS_LogH

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
* Logger
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Log
{
    public:
        PSS_Log();
        virtual ~PSS_Log();

        /**
        * Initializes the log
        *@return true on success, otherwise false
        */
        virtual bool InitializeLog() = 0;

        /**
        * Clears the log
        */
        virtual void ClearLog() = 0;

        /**
        * Adds a line
        *@param line - line to add
        */
        virtual void AddLine(const CString& line) = 0;

        /**
        * Gets the line count
        *@return the line count
        */
        virtual std::size_t GetCount() const = 0;

        /**
        * Gets the line at index
        *@param index - index
        *@return the line, empty string on error or if not found
        */
        virtual CString GetLineAt(std::size_t Index) const = 0;

        /**
        * Gets the current selection
        *@return the currently selected index
        */
        virtual int GetCurrentSelection() const = 0;

        /**
        * Sets the current selection
        *@param index - the selected line index
        */
        virtual void SetCurrentSelection(std::size_t index) = 0;

        /**
        * Clears the current selection
        */
        virtual void ClearCurrentSelection() = 0;

        /**
        * Gets the current item
        *@param[out] str - string containing the item text
        *@return the current item index
        */
        virtual int GetCurrentItem(CString& str) const = 0;

        /**
        * Checks if in debug mode
        *@return true if in debug mode, otherwise false
        */
        virtual bool IsInDebugMode() const = 0;

        /**
        * Sets as in debug mode
        *@param value - if true, the logger is in debug mode
        */
        virtual void SetDebugMode(bool value = true) = 0;

        /**
        * Gets if the last line should be selected
        *@return true if the last line should be selected, otherwise false
        */
        virtual bool SelectLast() const = 0;

        /**
        * Sets if the last line should be selected
        *@param value - if true, the last line will be selected
        */
        virtual void SetSelectLast(bool value = true) = 0;
};

#endif
