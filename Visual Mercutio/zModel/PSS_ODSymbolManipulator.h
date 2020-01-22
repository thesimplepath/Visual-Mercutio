/****************************************************************************
 * ==> PSS_ODSymbolManipulator ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to manipulate the Objective View symbols *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ODSymbolManipulatorH
#define PSS_ODSymbolManipulatorH

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

// class name mapping
#ifndef PSS_SymbolEdit
    #define PSS_SymbolEdit ZBSymbolEdit
#endif
#ifndef PSS_SymbolLabel
    #define PSS_SymbolLabel ZBSymbolLabel
#endif

// forward class declaration
class PSS_SymbolEdit;
class PSS_SymbolLabel;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Helper to manipulate the Objective View symbols
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ODSymbolManipulator
{
    public:
        PSS_ODSymbolManipulator();
        virtual ~PSS_ODSymbolManipulator();

        /**
        * Creates an edit text
        *@param pSymbol - the symbol for which an edit text should be created
        *@param areaName - the area name
        *@param editName - the edit name
        *@param pParent - the symbol parent, can be NULL
        *@return the symbol edit, NULL on error
        */
        static PSS_SymbolEdit* CreateEditText(CODComponent*  pSymbol,
                                              const CString& areaName,
                                              const CString& editName,
                                              CODComponent*  pParent = NULL);

        /**
        * Creates an edit text and replaces the existing one
        *@param pSymbol - the symbol for which an edit text should be created
        *@param editName - the edit name
        *@param pParent - the symbol parent, can be NULL
        *@return the symbol edit, NULL on error
        */
        static PSS_SymbolEdit* CreateAndReplaceEditText(CODComponent* pSymbol, const CString& editName, CODComponent* pParent = NULL);

        /**
        * Creates a label text and replaces the existing one
        *@param pSymbol - the symbol for which an label text should be created
        *@param editName - the edit name
        *@param notifyParent - if true, the parent will be notified on change
        *@param pParent - the symbol parent, can be NULL
        *@return the symbol label, NULL on error
        */
        static PSS_SymbolLabel* CreateAndReplaceLabelText(CODComponent*  pSymbol,
                                                          const CString& editName,
                                                          bool           notifyParent,
                                                          CODComponent*  pParent = NULL);

        /**
        * Removes a component from a symbol
        *@param pSymbol - the symbol containing the component to symbol
        *@param componentName - the component name to remove
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL RemoveSymbol(CODComponent* pSymbol, const CString& componentName);

        /**
        * Removes a component from a symbol
        *@param pSymbol - the symbol containing the component to symbol
        *@param pComponent - the component to remove
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL RemoveSymbol(CODComponent* pSymbol, CODComponent* pComponent);

        /**
        * Finds a component in a symbol
        *@param pSymbol - the symbol containing the component to find
        *@param componentName - the component name to find
        *@return the found component, NULL if not found or on error
        */
        static CODComponent* FindSymbol(CODComponent* pSymbol, const CString& componentName);

        /**
        * Finds a component in symbol children
        *@param pSymbol - the symbol to find
        *@param componentName - the component name to find
        *@return the found component, NULL if not found or on error
        */
        static CODComponent* FindSymbolInChild(CODComponent* pSymbol, const CString& componentName);

        /**
        * Finds a label
        *@param pSymbol - the symbol containing the label to find
        *@param labelName - the label name
        *@return the found label, NULL if not found or on error
        */
        static CODComponent* FindLabel(CODSymbolComponent* pSymbol, const CString& labelName);

        /**
        * Matches the symbol area name with another symbol
        *@param pSymbol - the symbol to match
        *@param pSrcSymbol - the symbol to match with
        */
        static void MatchSymbolAreaName(CODComponent* pSymbol, CODComponent* pSrcSymbol);

        /**
        * Matches the symbol area name in a child with another symbol
        *@param pSymbol - the symbol to match
        *@param pSrcSymbol - the symbol to match with
        */
        static void MatchSymbolAreaNameInChild(CODComponent* pSymbol, CODComponent* pSrcSymbol);

        /**
        * Checks if a symbol is visible
        *@param pSymbol - the symbol
        *@param symbolName - the symbol name
        *@return TRUE if the symbol is visible, otherwise FALSE
        */
        static BOOL IsSymbolVisible(CODComponent* pSymbol, const CString& symbolName);

        /**
        * Sets a symbol as visible
        *@param pSymbol - the symbol
        *@param symbolName - the symbol name
        *@param visible - if TRUE, the symbol is visible
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL SetSymbolVisible(CODComponent* pSymbol, const CString& symbolName, BOOL visible);

        /**
        * Changes the component line color
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeComponentLineColor(CODComponent* pSymbol, COLORREF color);

        /**
        * Changes the component line width
        *@param pSymbol - the symbol component to modify
        *@param width - the line width
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeComponentLineWidth(CODComponent* pSymbol, int width);

        /**
        * Changes the component line color and width
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@param width - the line width
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeComponentLineColorWidth(CODComponent* pSymbol, COLORREF color, int width);

        /**
        * Changes the line color
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@param symbolName - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLineColor(CODComponent* pSymbol, COLORREF color, const CString& symbolName = _T(""));

        /**
        * Changes the line width
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@param symbolName - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLineWidth(CODComponent* pSymbol, int width, const CString& symbolName = _T(""));

        /**
        * Changes the label line width
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@param labelName - the symbol label name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLabelLineWidth(CODSymbolComponent* pSymbol, int width, const CString& labelName = _T(""));

        /**
        * Changes the line style
        *@param pSymbol - the symbol component to modify
        *@param style - the line style
        *@param symbolName - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLineStyle(CODComponent* pSymbol, int style, const CString& symbolName = _T(""));

        /**
        * Sets the label text as italic
        *@param pSymbol - the symbol component to modify
        *@param doSetTextItalic - if TRUE, the label text will be shown as italic
        *@param labelName - the label name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL SetLabelItalic(CODSymbolComponent* pSymbol, BOOL doSetTextItalic, const CString& labelName = _T(""));

        /**
        * Changes the label text color
        *@param pSymbol - the symbol component to modify
        *@param color - the label text color
        *@param labelName - the label name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLabelTextColor(CODSymbolComponent* pSymbol, COLORREF color, const CString& labelName = _T(""));

        /**
        * Sets the text as italic
        *@param pSymbol - the symbol component to modify
        *@param doSetTextItalic - if TRUE, the text will be shown as italic
        *@param symbolName - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL SetTextItalic(CODComponent* pSymbol, BOOL doSetTextItalic, const CString& symbolName = _T(""));

        /**
        * Changes the text color
        *@param pSymbol - the symbol component to modify
        *@param color - the text color
        *@param symbolName - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeTextColor(CODComponent* pSymbol, COLORREF color, const CString& symbolName = _T(""));

        /**
        * Gets the text color
        *@param pSymbol - the symbol component for which the text color should be get
        *@return the text color
        */
        static COLORREF GetTextColor(CODComponent* pSymbol, const CString& symbolName = _T(""));

        /**
        * Changes the label line color
        *@param pSymbol - the symbol component to modify
        *@param color - the text color
        *@param labelName - the label name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLabelLineColor(CODSymbolComponent* pSymbol, COLORREF color, const CString& labelName = _T(""));

        /**
        * Changes the line color and width
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@param width - the line width
        *@param SymbolName - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLineColorWidth(CODComponent* pSymbol, COLORREF color, int width, const CString& symbolName = _T(""));

        /**
        * Changes the label line color and width
        *@param pSymbol - the symbol component to modify
        *@param color - the line color
        *@param width - the line width
        *@param labelName - the label name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeLabelLineColorWidth(CODSymbolComponent* pSymbol,
                                              COLORREF            color,
                                              int                 width,
                                              const CString&      labelName = _T(""));

        /**
        * Applies a format from an object
        *@param pSymbol - the symbol component to which the format should be applied
        *@param pObject - the source object
        *@param font - if true, the font properties should be copied
        *@param fill - if true, the fill properties should be copied
        *@param line - if true, the line properties should be copied
        */
        static void ApplyFormatFromObject(CODComponent* pSymbol,
                                          CODComponent& object,
                                          bool          font = true,
                                          bool          fill = true,
                                          bool          line = true);

        /**
        * Copies the symbol style
        *@param pSrcSymbol - the source symbol to copy from
        *@param pDstSymbol - the destination symbol to copy to
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL CopySymbolStyle(CODComponent* pSrcSymbol, CODComponent* pDstSymbol);

        /**
        * Keeps only the symbol of type
        *@param[in, out] nodes - the nodes to filter, the filtered nodes on function ends
        *@param pClass - the class type to filter
        *@return the found symbol count
        */
        static std::size_t KeepOnlySymbolsISA(CODNodeArray& nodes, const CRuntimeClass* pClass);

        /**
        * Keeps only the link symbol of type
        *@param[in, out] edges - the edges to filter, the filtered edges on function ends
        *@param pClass - the class type to filter
        *@return the found symbol count
        */
        static std::size_t KeepOnlyLinksISA(CODEdgeArray& edges, const CRuntimeClass* pClass);

        /**
        * Checks if a type of symbol can be found in a node array
        *@param nodes - the nodes to search in
        *@param pClass - the type to find
        *@return true if the type can be found in the node array, otherwise false
        */
        static bool HasSymbolsISA(const CODNodeArray& nodes, const CRuntimeClass* pClass);

        /**
        * Checks if a type of link symbol can be found in a edge array
        *@param edges - the edges to search in
        *@param pClass - the type to find
        *@return true if the type can be found in the node array, otherwise false
        */
        static bool HasLinksISA(const CODEdgeArray& edges, const CRuntimeClass* pClass);

        /**
        * Keeps the following symbol by port name
        *@param portName - the port name
        *@param[in, out] nodes - the nodes to filter, the filtered nodes on function ends
        *@return the number of remaining symbols
        */
        static std::size_t KeepFollowingSymbolsByPortName(const CString& portName, CODNodeArray& nodes);

        /**
        * Checks if a symbol is followed by a port name
        *@param pSymbol - the symbol to check
        *@param portName - the port name
        *@return true if the symbol is followed by the port name, otherwise false
        */
        static bool IsSymbolFollowingByPortName(CODSymbolComponent* pSymbol, const CString& portName);

        /**
        * Finds all the ports matching with the name
        *@param pSymbol - the symbol component containing the ports
        *@param portName - the port name to find
        *@param[out] ports - the found ports
        *@return the found ports count
        */
        static std::size_t GetPortName(CODSymbolComponent* pSymbol, const CString& portName, CODPortSet& ports);

        /**
        * Gets all the following symbols attached to a port
        *@param port - the port
        *@param[out] set - the symbols
        *@return the found symbol count
        */
        static std::size_t GetPortFollowingSymbols(CODPortComponent& port, CODComponentSet& set);
};

#endif
