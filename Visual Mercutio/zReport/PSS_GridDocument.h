/****************************************************************************
 * ==> PSS_GridDocument ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid document                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridDocumentH
#define PSS_GridDocumentH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping
#ifndef PSS_GridGroup
    #define PSS_GridGroup ZCGridGroup
#endif

// forward class declaration
class ZVGridView;
class PSS_GridGroup;

#ifdef _ZREPORTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Grid document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridDocument : public CGXDocument
{
    GXDECLARE_DYNCREATE(PSS_GridDocument)

    public:
        /**
        * Gets the grid parameter
        *@return the grid parameter
        */
        virtual inline CGXGridParam* GetGridParam();

        /**
        * Sets the new grid parameter
        *@param pParam - the new grid parameter
        */
        virtual bool SetNewGridParam(CGXGridParam* pParam);

        /**
        * Create the grid parameter
        *@return true on success, otherwise false
        */
        virtual inline bool CreateGridParam();

        /**
        * Gets the grid parameter at index
        *@param index - the index
        *@return the grid parameter, NULL if not found or on error
        */
        virtual CGXGridParam* GetGridParam(std::size_t index);

        /**
        * Gets the tab create info at index
        *@param index - the index
        *@return the tab create info, NULL if not found or on error
        */
        virtual CGXTabCreateInfo* GetTabCreateInfo(std::size_t index);

        /**
        * Gets the document at index
        *@param index - the index
        *@return the document, NULL if not found or on error
        */
        virtual PSS_GridDocument* GetDocumentAt(std::size_t index);

        /**
        * Gets the tab window at index
        *@param index - the index
        *@return the tab window, NULL if not found or on error
        */
        virtual CGXTabWnd* GetTabWnd(std::size_t index);

        /**
        * Gets the tab view at index
        *@param index - the index
        *@return the tab view, NULL if not found or on error
        */
        virtual ZVGridView* GetTabView(std::size_t index);

        /**
        * Gets the tab grid core at index
        *@param index - the index
        *@return the tab grid core, NULL if not found or on error
        */
        virtual CGXGridCore* GetTabGridCore(std::size_t index);

        /**
        * Gets the first document view
        *@return the first document view, NULL on error
        */
        virtual ZVGridView* GetFirstView();

        /**
        * Gets the tab name at index
        *@param index - the index
        *@return the tab name, empty string if not found or on error
        */
        virtual const CString GetTabName(std::size_t index);

        /**
        * Sets the tab name at index
        *@param name - the tab name
        *@param index - the index
        */
        virtual void SetTabName(const CString& name, std::size_t index);

        /**
        * Sets the path name
        *@param pPathName - the path name
        *@param addToMRU - if TRUE, the path name will be added to the most recently used file list
        */
        virtual void SetPathName(LPCTSTR pPathName, BOOL addToMRU = TRUE);

        /**
        * Gets the grid tab count
        *@return the grid tab count
        */
        virtual std::size_t GetGridTabCount() const;

        /**
        * Deletes the grid tab at index
        *@param index - the index
        *@return the grid tab, NULL if not found or on error
        */
        virtual bool DeleteGridTab(std::size_t index = 0);

        /**
        * Inserts a grid tab
        *@return true on success, otherwise false
        */
        virtual inline bool InsertNewGridTab();

        /**
        * Inserts a grid tab before the index
        *@param index - the index before which the grid tab should be inserted
        *@return true on success, otherwise false
        */
        virtual inline bool InsertNewGridTabBefore(std::size_t index = 0);

        /**
        * Inserts a grid tab after the index
        *@param index - the index after which the grid tab should be inserted
        *@return true on success, otherwise false
        */
        virtual inline bool InsertNewGridTabAfter(std::size_t index = 0);

        /**
        * Initializes the group controls
        *@param pView - the grid view
        */
        virtual void InitializeGroupControls(ZVGridView* pView);

        /**
        * Inserts a group control
        *@param row - the row
        *@param col - the column
        *@param coveringCells - the covering cell count
        *@param horizontal - if true, the layer will be horizontal instead of vertical
        *@param collapsed - if true, the group is collapsed
        *@param label - the label
        *@param tooltipText - the tooltip text
        */
        virtual void InsertGroupCtrl(ROWCOL         row,
                                     ROWCOL         col,
                                     int            coveringCells,
                                     bool           horizontal,
                                     bool           collapsed,
                                     const CString& label       = _T(""),
                                     const CString& tooltipText = _T(""));

        /**
        * Searches for a group control
        *@param row - the row
        *@param col - the column
        *@return the group control, NULL if not found or on error
        */
        virtual PSS_GridGroup* SearchGroupCtrl(ROWCOL row, ROWCOL col);

        /**
        * Removes all the group controls
        */
        virtual void RemoveAllGroupCtrl();

        /**
        * Deletes the content
        */
        virtual void DeleteContents();

        /**
        * Saves the modified content
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveModified();

        /**
        * Checks if the frame may be closed
        *@param pFrame - the frame which is about to be closed
        *@return TRUE if the frame may be closed, otherwise FALSE
        */
        virtual BOOL CanCloseFrame(CFrameWnd* pFrame);

        /**
        * Updates the frame title
        *@return TRUE if the frame title may change, otherwise FALSE
        *@note This function is normally called when the document name has changed
        */
        virtual BOOL UpdateFrameTitle();

        /**
        * Checks if the grid view can exists
        *@param pView - the view to check
        *@return TRUE if the grid view can exists, otherwise FALSE
        */
        virtual BOOL CanExitGridView(CView* pView);

        /**
        * Gets the frozen row
        *@return the frozen row
        */
        virtual inline ROWCOL GetFrozenRow() const;

        /**
        * Sets the frozen row
        *@param value - the frozen rows
        */
        virtual inline void SetFrozenRow(ROWCOL value);

        /**
        * Gets the frozen column
        *@return the frozen column
        */
        virtual inline ROWCOL GetFrozenCol() const;

        /**
        * Sets the frozen column
        *@param value - the frozen column
        */
        virtual void inline SetFrozenCol(ROWCOL value);

        /**
        * Gets the frozen header row
        *@return the frozen header row
        */
        virtual inline ROWCOL GetFrozenHeaderRow() const;

        /**
        * Sets the frozen header row
        *@param value - the frozen header row
        */
        virtual inline void SetFrozenHeaderRow(ROWCOL value);

        /**
        * Gets the frozen header column
        *@return the frozen header column
        */
        virtual inline ROWCOL GetFrozenHeaderCol() const;

        /**
        * Sets the frozen header column
        *@param value - the frozen header column
        */
        virtual inline void SetFrozenHeaderCol(ROWCOL value);

        /**
        * Sets the path name in the base class
        *@param pPathName - the path name
        *@param addToMRU - if TRUE, the path name will be added to the most recently used file list
        */
        virtual void BaseClassSetPathName(LPCTSTR pPathName, BOOL addToMRU = TRUE);

        /**
        * Called when a document is opened
        *@param pPathName - the document path name
        *@return TRUE if document may be opened, otherwise FALSE
        */
        virtual BOOL OnOpenDocument(LPCTSTR pPathName);

        /**
        * Called when a document is saved
        *@param pPathName - the document path name
        *@return TRUE if document may be saved, otherwise FALSE
        */
        virtual BOOL OnSaveDocument(LPCTSTR pPathName);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        PSS_GridDocument();
        virtual ~PSS_GridDocument();

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_GridDocument)
        virtual BOOL OnNewDocument();
        virtual void WorkBookSerialize(CArchive& ar);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_GridDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Inserts a new grid tab at index
        *@param insert - insert index
        *@return true on success, otherwise false
        */
        virtual bool InsertNewGridTabAt(std::size_t insert = 0);

    private:
        typedef CCArray_T <PSS_GridGroup*, PSS_GridGroup*> IGridGroupSet;
        typedef Iterator_T<PSS_GridGroup*>                 IGridGroupIterator;

        IGridGroupSet m_GroupCtrlSet;
        CGXGridParam* m_pParam;
        ROWCOL        m_FrozenRow;
        ROWCOL        m_FrozenCol;
        ROWCOL        m_FrozenHeaderRow;
        ROWCOL        m_FrozenHeaderCol;
};

//---------------------------------------------------------------------------
// PSS_GridDocument
//---------------------------------------------------------------------------
CGXGridParam* PSS_GridDocument::GetGridParam()
{
    return m_pParam;
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::CreateGridParam()
{
    return SetNewGridParam(new CGXGridParam());
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::InsertNewGridTab()
{
    return InsertNewGridTabAt(GetGridTabCount() - 1);
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::InsertNewGridTabBefore(std::size_t index)
{
    return InsertNewGridTabAt(index);
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::InsertNewGridTabAfter(std::size_t index)
{
    return InsertNewGridTabAt(index + 1);
}
//---------------------------------------------------------------------------
ROWCOL PSS_GridDocument::GetFrozenRow() const
{
    return m_FrozenRow;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::SetFrozenRow(ROWCOL value)
{
    m_FrozenRow = value;
}
//---------------------------------------------------------------------------
ROWCOL PSS_GridDocument::GetFrozenCol() const
{
    return m_FrozenCol;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::SetFrozenCol(ROWCOL value)
{
    m_FrozenCol = value;
}
//---------------------------------------------------------------------------
ROWCOL PSS_GridDocument::GetFrozenHeaderRow() const
{
    return m_FrozenHeaderRow;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::SetFrozenHeaderRow(ROWCOL value)
{
    m_FrozenHeaderRow = value;
}
//---------------------------------------------------------------------------
ROWCOL PSS_GridDocument::GetFrozenHeaderCol() const
{
    return m_FrozenHeaderCol;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::SetFrozenHeaderCol(ROWCOL value)
{
    m_FrozenHeaderCol = value;
}
//---------------------------------------------------------------------------

#endif
