/****************************************************************************
 * ==> PSS_ErrorLog --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an error log                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ErrorLogH
#define PSS_ErrorLogH

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

// processsoft
#include "ZILog.h"

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
* Error log
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ErrorLog : public ZILog
{
    public:
        PSS_ErrorLog();
        virtual ~PSS_ErrorLog();

        /**
        * Initializes the log
        *@return true on success, otherwise false
        */
        virtual bool InitializeLog();

        /**
        * Clears the log
        */
        virtual void ClearLog();

        /**
        * Adds a line
        *@param line - line to add
        */
        virtual void AddLine(const CString& line);

        /**
        * Gets the line count
        *@return the line count
        */
        virtual std::size_t GetCount() const;

        /**
        * Gets a line at index
        *@param index - index
        *@return the line, empty string if not found or on error
        */
        virtual CString GetLineAt(std::size_t index) const;

        /**
        * Gets the current selection index
        *@return the current selection index
        */
        virtual int GetCurrentSelection() const;

        /**
        * Sets the current selection index
        *@param index - the current selection index
        */
        virtual void SetCurrentSelection(std::size_t index);

        /**
        * Clears the current selection
        */
        virtual void ClearCurrentSelection();

        /**
        * Gets the currently selected line
        *@param[out] line - line content on function ends, will remain unchanged if not found or on error
        *@return the selected index, -1 if no selection or on error
        */
        virtual int GetCurrentItem(CString& s) const;

        /**
        * Gets if the last line is selected
        *@return true on success, otherwise false
        */
        virtual bool SelectLast() const;

        /**
        * Sets the last line as selected
        *@param value - if true, the last line is selected
        */
        virtual void SetSelectLast(bool value = true);

    private:
        CStringArray m_LogArray;
        int          m_CurrentSelection;
};

#endif
