/****************************************************************************
 * ==> PSS_ObjectUtility ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an object utility                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObjectUtilityH
#define PSS_ObjectUtilityH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// forward class declaration
class PlanFinObject;

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
* Object utility
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ObjectUtility
{
    public:
        PSS_ObjectUtility();
        virtual ~PSS_ObjectUtility();

        /**
        * Gets the field description
        *@param pObj - class object
        *@return the field description
        */
        static const CString GetFieldTypeDescription(PlanFinObject* pObj);

        /**
        * Gets the field description
        *@param className - class name
        *@return the field description
        */
        static const CString GetFieldTypeDescription(const CString& className);

        /**
        * Gets the class name
        *@param pObj - class object
        *@return the class name
        */
        static const CString GetClassName(PlanFinObject* pObj);

        /**
        * Gets the bitmap class name
        *@return the bitmap class name
        */
        static UINT GetBitmapClass(const CString& className);

        /**
        * Builds a specific object by passing the class name
        *@param className - class name
        *@return the built object
        */
        static PlanFinObject* BuildObject(const CString& className);

        /**
        * Gets the class name array
        *@return the class name array
        */
        static inline const CStringArray& GetClassNameArray();

        /**
        * Gets the edition class name array
        *@return the edition class name array
        */
        static inline const CStringArray& GetEditionClassNameArray();

        /**
        * Initializes all the definitions
        *@param iniFileName - ini file name
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL InitializeDefinition(const CString& iniFileName);

        /**
        * Loads the definition field
        *@param iniFileName - ini file name
        *@param fieldKey - field key
        *@return the definition field, empty string if not found or on error
        */
        static CString LoadFieldDefinition(const CString& iniFileName, const CString& fieldKey);

        /**
        * Gets the class name identifier
        *@return the class name identifier
        */
        static std::size_t GetClassNameID(PlanFinObject* pObj);

        /**
        * Releases the resources
        */
        static void Release();

    protected:
        /**
        * Gets the general field description from the ini file
        *@param pKey - key to get
        *@return the field description
        */
        static const CString GetFieldTypeDescriptionIniFile(const char* pKey);

    private:
        /**
        * Object definition
        */
        class IObjectDefinition : public CObject
        {
            public:
                CString m_Key;
                CString m_Description;

                typedef CObject inherited;

                /**
                * Constructor
                *@param key - key
                *@param description - description
                */
                IObjectDefinition(const CString& key, const CString& description);

                virtual ~IObjectDefinition();
        };

        static const UINT         m_ClassResourceIDArrary[21];
        static const UINT         m_EditionClassResourceIDArrary[17];
        static const UINT         m_ClassResourceBitmapIDArrary[18];
        static       CStringArray m_ClassNameArray;
        static       CStringArray m_EditionClassNameArray;
        static       CObArray     m_FieldTypeDescriptionArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ObjectUtility(const PSS_ObjectUtility& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ObjectUtility& operator = (const PSS_ObjectUtility& other);

        /**
        * Loads the resource
        *@note Because the resource cannot be loaded at the class construction, do it later
        */
        static void LoadResource();

        /**
        * Checks if the resources were loaded
        *@return true if the resources were loadedm, otherwise false
        */
        static inline bool ResourceNotLoaded();
};

//---------------------------------------------------------------------------
// PSS_ObjectUtility
//---------------------------------------------------------------------------
const CStringArray& PSS_ObjectUtility::GetClassNameArray()
{
    // was resource loaded?
    if (ResourceNotLoaded())
        LoadResource();

    return m_ClassNameArray;
}
//---------------------------------------------------------------------------
const CStringArray& PSS_ObjectUtility::GetEditionClassNameArray()
{
    // was resource loaded?
    if (ResourceNotLoaded())
        LoadResource();

    return m_EditionClassNameArray;
}
//---------------------------------------------------------------------------
bool PSS_ObjectUtility::ResourceNotLoaded()
{
    return (m_ClassNameArray.GetSize() <= 0);
}
//---------------------------------------------------------------------------

#endif
