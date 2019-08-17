/****************************************************************************
 * ==> PSS_Formula ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a formula and its associated manager and schema   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FormulaH
#define PSS_FormulaH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Formula
    //#define PSS_Formula ZAFormula
#endif

// class name mapping
#ifndef PSS_DocumentData
    #define PSS_DocumentData ZDDocumentData
#endif

// forward classes definition
class ZDDocument;
class PSS_DocumentData;
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
* Formula
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Formula : public CObject
{
    DECLARE_SERIAL(PSS_Formula)

    public:
        PSS_Formula();

        /**
        * Constructor
        *@param[in, out] doc - document in which formula should be attached
        *@param formula - formula
        */
        PSS_Formula(ZDDocument& doc, const CString& formula);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Formula(const PSS_Formula& other);

        virtual ~PSS_Formula();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Formula& operator = (const PSS_Formula& other);

        /**
        * Clones the formula
        *@return the cloned formula, NULL on error
        */
        virtual PSS_Formula* Clone() const;

        /**
        * Gets the page
        *@return the page
        */
        virtual inline int GetPage() const;

        /**
        * Sets the page
        *@param value - the page
        */
        virtual inline void SetPage(int value);

        /**
        * Gets the formula
        *@return the formula
        */
        virtual inline const CString GetFormula() const;

        /**
        * Gets the extracted formula
        *@return the extracted formula
        */
        virtual inline const CString GetExtractedFormula() const;

        /**
        * Gets the object name
        *@return the object name
        */
        virtual inline const CString GetObjectName() const;

        /**
        * Gets the resulting object
        *@return the resulting object
        */
        virtual inline PlanFinObject* GetResultObject() const;

        /**
        * Sets the resulting object
        *@param pObject - the resulting object
        */
        virtual inline void SetResultObject(PlanFinObject* pObject);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

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

        /**
        * Scans the formula list to find the object
        *@param doc - document owning the formula list
        *@param formulas - formula list to scan
        */
        static void ConstructObjectPointer(PSS_DocumentData& doc, CObList& formulas);

    private:
        CString        m_Formula;
        CString        m_ExtractedFormula;
        CString        m_ObjectName;
        PlanFinObject* m_pResultObject;
        int            m_Page;
};

//---------------------------------------------------------------------------
// PSS_Formula
//---------------------------------------------------------------------------
int PSS_Formula::GetPage() const
{
    return m_Page;
}
//---------------------------------------------------------------------------
void PSS_Formula::SetPage(int value)
{
    m_Page = value;
}
//---------------------------------------------------------------------------
const CString PSS_Formula::GetFormula() const
{
    return m_Formula;
}
//---------------------------------------------------------------------------
const CString PSS_Formula::GetExtractedFormula() const
{
    return m_ExtractedFormula;
}
//---------------------------------------------------------------------------
const CString PSS_Formula::GetObjectName() const
{
    return m_ObjectName;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_Formula::GetResultObject() const
{
    return m_pResultObject;
}
//---------------------------------------------------------------------------
void PSS_Formula::SetResultObject(PlanFinObject* pObject)
{
    m_pResultObject = pObject;
}
//---------------------------------------------------------------------------

/**
* Formula association
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZAFormulaAssociation : public CObject
{
    DECLARE_SERIAL(ZAFormulaAssociation)

public:
    ZAFormulaAssociation();

    /**
    * Constructor
    *@param name - formula name
    *@param objectNameInitiator - object name initiator
    */
    ZAFormulaAssociation(const CString& name, const CString& objectNameInitiator);

    // Object initiator
    const CString    GetAssociationName() const
    {
        return m_AssociationName;
    };
    void            SetAssociationName(const CString Name)
    {
        m_AssociationName = Name;
    };
    // Object initiator
    const CString    GetObjectNameInitiator() const
    {
        return m_ObjectNameInitiator;
    };
    void            SetObjectNameInitiator(const CString Name)
    {
        m_ObjectNameInitiator = Name;
    };
    // Formula management
    void            AddFormula(PSS_Formula* pFormula);
    void            DeleteFormula(const CString& Name);
    void            DeleteFormula(PSS_Formula* pFormula);
    PSS_Formula*        FindFormula(const CString& Name);
    PSS_Formula*        GetFormulaAt(int Index);
    int                GetCount() const
    {
        return m_lstFormula.GetCount();
    };
    CObList&        GetFormulaList()
    {
        return m_lstFormula;
    };


    PSS_Formula*         FindFormulaFullString(const CString& Formula);

    // Clone the association formula
    ZAFormulaAssociation*    Clone();

    size_t GetFormulaArray(CStringArray& Array);

    // Data
private:
    CString        m_AssociationName;            // The name of the Association
    CString        m_ObjectNameInitiator;    // The field for which the Association is enable
    CObList        m_lstFormula;            // The list for calculation
                                        // This list contains all formula
                                        // necessary to calculate the
                                        // Association

// Implementation
public:
    virtual ~ZAFormulaAssociation();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};


class AFX_EXT_CLASS ZAFormulaAssociationManager : public CObject
{
protected:
    DECLARE_SERIAL(ZAFormulaAssociationManager)
public:
    ZAFormulaAssociationManager();

    void                InitializeFormulaAssociations(PSS_DocumentData& doc);

    void                AddAssociation(ZAFormulaAssociation* pAssociation);
    void                DeleteAssociation(const CString& Name);
    void                DeleteAssociation(ZAFormulaAssociation* pAssociation);
    ZAFormulaAssociation*    FindAssociation(const CString& Name);
    CStringArray&        GetAssociationArray()
    {
        return m_AssociationArrayName;
    };
    CStringArray&        RefreshAssociationArray();


    BOOL                IsEmpty() const
    {
        return m_lstAssociation.IsEmpty();
    };
    int                    GetCount() const
    {
        return m_lstAssociation.GetCount();
    };

    // Assigns the contents of the association manager
    void                AssignContents(const ZAFormulaAssociationManager& ManagerSource);
    // Clone the association manager
    ZAFormulaAssociationManager*    Clone();

    // Current association
    ZAFormulaAssociation*    GetCurrentAssociation() const
    {
        return m_pCurrentAssociation;
    };
    void                    ClearCurrentAssociation()
    {
        m_pCurrentAssociation = NULL;
    };
    void                     SetCurrentAssociation(ZAFormulaAssociation* pCurrent)
    {
        m_pCurrentAssociation = pCurrent;
    };
    void                     SetCurrentAssociation(const CString Name)
    {
        m_pCurrentAssociation = FindAssociation(Name);
    };

    // Implementation
private:
    CObList                    m_lstAssociation;            // The list of Associations
    ZAFormulaAssociation*    m_pCurrentAssociation;
    CStringArray            m_AssociationArrayName;

    // Implementation
public:
    virtual ~ZAFormulaAssociationManager();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};


// Define different type
enum    FormulaSchemaType
{
    UserSchema, SystemSchema
};

class AFX_EXT_CLASS ZAFormulaSchema : public CObject
{
protected:
    DECLARE_SERIAL(ZAFormulaSchema)
public:
    ZAFormulaSchema();
    CObList&    GetFormulaList()
    {
        return m_lstFormula;
    };
    void        SetSchemaName(const CString& sValue)
    {
        m_sSchemaName = sValue;
    };
    void        SetDescription(const CString& sValue)
    {
        m_sDescription = sValue;
    };
    void        SetFormulaSchemaType(const FormulaSchemaType& Value)
    {
        m_FormulaSchemaType = Value;
    };
    BOOL        DeletePageFormulas(int iPage, BOOL bRedistribute = TRUE);
    BOOL        CopyPageFormulas(ZAFormulaSchema*    pFormulaDst, int iPage);
    const CString&    GetSchemaName()
    {
        return m_sSchemaName;
    };
    const CString&    GetDescription()
    {
        return m_sDescription;
    };
    const FormulaSchemaType    GetFormulaSchemaType()
    {
        return m_FormulaSchemaType;
    };
    ZAFormulaSchema*    Clone();

    // Implementation
private:
    CObList        m_lstFormula;        // The list for calculation
                                    // This list contains all formula
                                    // necessary to calculate the
                                    // PLAN Financier
    CString        m_sSchemaName;        // The name of the formula schema

    // Since version 2 of file
    CString        m_sDescription;        // The description of the formula schema
    FormulaSchemaType    m_FormulaSchemaType;    // The type of the formula schema

// Implementation
public:
    virtual ~ZAFormulaSchema();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};




class AFX_EXT_CLASS ZASchemaManager : public CObject
{
protected:
    DECLARE_SERIAL(ZASchemaManager)
public:
    ZASchemaManager();
    ZASchemaManager(const ZASchemaManager &right);
    const ZASchemaManager & operator=(const ZASchemaManager &right);

    void                InitializeSchemaObjectPointer(PSS_DocumentData& doc);

    CObList*            GetFormulaList(const CString& sName);
    CObList*            GetFormulaSchema(const CString& sName);
    BOOL                DeleteFormulaList(const CString& sName);
    BOOL                DeletePageFormulas(const CString& sName, int iPage);
    BOOL                DeletePageFormulas(int iPage);
    BOOL                CopyPageFormulas(const CString& sName, ZASchemaManager& SchemaDst, int iPage);
    CStringArray&        GetFormulaArrayName();
    CStringArray&        GetFormulaUserArrayName();
    CStringArray&        GetFormulaSystemArrayName();
    void                Create(const CString& sName);
    void                CreateStandardEmptySchema();

    BOOL                CopySchema(const CString& sSource, const CString sNew);
    ZASchemaManager*    Clone();

    // Implementation
private:
    CObList        m_lstSchema;        // The list for schema calculation
                                    // This list contains schema with all formula
                                    // necessary to calculate the
                                    // PLAN Financier
    static    CStringArray        m_SchemaNameArray;
    // Implementation
public:
    virtual ~ZASchemaManager();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    void ReadSerializeOldFormat(CArchive& ar);
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif
