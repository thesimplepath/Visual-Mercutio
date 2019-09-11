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
    #define PSS_Formula ZAFormula
#endif
#ifndef PSS_FormulaAssociation
    #define PSS_FormulaAssociation ZAFormulaAssociation
#endif
#ifndef PSS_FormulaAssociationManager
    #define PSS_FormulaAssociationManager ZAFormulaAssociationManager
#endif
#ifndef PSS_FormulaSchema
    #define PSS_FormulaSchema ZAFormulaSchema
#endif
#ifndef PSS_SchemaManager
    #define PSS_SchemaManager ZASchemaManager
#endif

// class name mapping
#ifndef PSS_DocumentData
    #define PSS_DocumentData ZDDocumentData
#endif
#ifndef PSS_PlanFinObject
    #define PSS_PlanFinObject PlanFinObject
#endif

// forward classes definition
class ZDDocument;
class PSS_DocumentData;
class PSS_PlanFinObject;

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
        virtual inline PSS_PlanFinObject* GetResultObject() const;

        /**
        * Sets the resulting object
        *@param pObject - the resulting object
        */
        virtual inline void SetResultObject(PSS_PlanFinObject* pObject);

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
        CString            m_Formula;
        CString            m_ExtractedFormula;
        CString            m_ObjectName;
        PSS_PlanFinObject* m_pResultObject;
        int                m_Page;
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
PSS_PlanFinObject* PSS_Formula::GetResultObject() const
{
    return m_pResultObject;
}
//---------------------------------------------------------------------------
void PSS_Formula::SetResultObject(PSS_PlanFinObject* pObject)
{
    m_pResultObject = pObject;
}
//---------------------------------------------------------------------------

/**
* Formula association
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FormulaAssociation : public CObject
{
    DECLARE_SERIAL(PSS_FormulaAssociation)

    public:
        PSS_FormulaAssociation();

        /**
        * Constructor
        *@param name - formula name
        *@param objectNameInitiator - object name initiator
        */
        PSS_FormulaAssociation(const CString& name, const CString& objectNameInitiator);

        virtual ~PSS_FormulaAssociation();

        /**
        * Clones the formula association
        *@return the cloned formula association, NULL on error
        */
        PSS_FormulaAssociation* Clone() const;

        /**
        * Gets the association name
        *@return the association name
        */
        virtual inline const CString GetAssociationName() const;

        /**
        * Sets the association name
        *@param name - the association name
        */
        virtual inline void SetAssociationName(const CString& name);

        /**
        * Gets the object name initiator
        *@return the object name initiator
        */
        virtual inline const CString GetObjectNameInitiator() const;

        /**
        * Sets the object name initiator
        *@param name - the object name initiator
        */
        virtual inline void SetObjectNameInitiator(const CString& name);

        /**
        * Gets the formula count
        *@return the formula count
        */
        virtual inline int GetCount() const;

        /**
        * Gets the formulas
        *@return the formulas
        */
        virtual inline CObList& GetFormulas();

        /**
        * Adds a formula
        *@param pFormula - formula to add
        */
        virtual void AddFormula(PSS_Formula* pFormula);

        /**
        * Deletes a formula
        *@param name - formula name to delete
        */
        virtual void DeleteFormula(const CString& Name);

        /**
        * Deletes a formula
        *@param pFormula - formula to delete
        */
        virtual void DeleteFormula(PSS_Formula* pFormula);

        /**
        * Gets a formula at index
        *@param index - index
        *@return formula, NULL if not found or on error
        */
        virtual PSS_Formula* GetFormulaAt(int Index);

        /**
        * Finds a formula
        *@param name - formula name to find
        *@return formula, NULL if not found or on error
        */
        virtual PSS_Formula* FindFormula(const CString& name);

        /**
        * Finds a formula using its full string
        *@param formula - formula full string
        *@return formula, NULL if not found or on error
        */
        virtual PSS_Formula* FindFormulaFullString(const CString& formula);

        /**
        * Gets a formula array
        *@param[in, out] formulaArray - the array to populate with formulas, populated array on function ends
        *@return number of formulas in the array
        */
        virtual std::size_t GetFormulaArray(CStringArray& formulaArray);

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

    private:
        CString m_AssociationName;
        CString m_ObjectNameInitiator;
        CObList m_Formulas;
};

//---------------------------------------------------------------------------
// PSS_FormulaAssociation
//---------------------------------------------------------------------------
const CString PSS_FormulaAssociation::GetAssociationName() const
{
    return m_AssociationName;
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociation::SetAssociationName(const CString& name)
{
    m_AssociationName = name;
}
//---------------------------------------------------------------------------
const CString PSS_FormulaAssociation::GetObjectNameInitiator() const
{
    return m_ObjectNameInitiator;
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociation::SetObjectNameInitiator(const CString& name)
{
    m_ObjectNameInitiator = name;
}
//---------------------------------------------------------------------------
int PSS_FormulaAssociation::GetCount() const
{
    return m_Formulas.GetCount();
}
//---------------------------------------------------------------------------
CObList& PSS_FormulaAssociation::GetFormulas()
{
    return m_Formulas;
}
//---------------------------------------------------------------------------

/**
* Formula association manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FormulaAssociationManager : public CObject
{
    DECLARE_SERIAL(PSS_FormulaAssociationManager)

    public:
        PSS_FormulaAssociationManager();
        virtual ~PSS_FormulaAssociationManager();

        /**
        * Clones the association manager
        *@return the cloned association manager, NULL on error
        */
        PSS_FormulaAssociationManager* Clone() const;

        /**
        * Initializes the formula association
        *@param doc - document
        */
        virtual void InitializeFormulaAssociations(PSS_DocumentData& doc);

        /**
        * Adds a formula association
        *@param pAssociation - formula association
        */
        virtual void AddAssociation(PSS_FormulaAssociation* pAssociation);

        /**
        * Deletes a formula association
        *@param name - formula association name to delete
        */
        virtual void DeleteAssociation(const CString& name);

        /**
        * Deletes a formula association
        *@param pAssociation - formula association to delete
        */
        virtual void DeleteAssociation(PSS_FormulaAssociation* pAssociation);

        /**
        * Finds a formula association
        *@param name - formula association name to find
        *@return the formula association, NULL if not found or on error
        */
        virtual PSS_FormulaAssociation* FindAssociation(const CString& name);

        /**
        * Refreshes the association array
        *@return the association array
        */
        virtual CStringArray& RefreshAssociationArray();

        /**
        * Assigns the association manager content
        *@param managerSource - source manager to assign from
        */
        virtual void AssignContents(const PSS_FormulaAssociationManager& managerSource);

        /**
        * Gets the formula association array
        *@return the formula association array
        */
        virtual inline CStringArray& GetAssociationArray();

        /**
        * Checks if the association manager is empty
        *@return TRUE if the association manager is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets the association count
        *@return the association count
        */
        virtual inline int GetCount() const;

        /**
        * Gets the current association
        *@return the current association, NULL if no association or on error
        */
        virtual inline PSS_FormulaAssociation* GetCurrentAssociation() const;

        /**
        * Sets the current association
        *@param pCurrent - the current association to set
        */
        virtual inline void SetCurrentAssociation(PSS_FormulaAssociation* pCurrent);

        /**
        * Sets the current association
        *@param name - the current association name to set
        */
        virtual inline void SetCurrentAssociation(const CString& name);

        /**
        * Clears the current association
        */
        virtual inline void ClearCurrentAssociation();

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

    private:
        CObList                 m_Associations;
        PSS_FormulaAssociation* m_pCurrentAssociation;
        CStringArray            m_AssociationArrayName;
};

//---------------------------------------------------------------------------
// PSS_FormulaAssociationManager
//---------------------------------------------------------------------------
CStringArray& PSS_FormulaAssociationManager::GetAssociationArray()
{
    return m_AssociationArrayName;
}
//---------------------------------------------------------------------------
BOOL PSS_FormulaAssociationManager::IsEmpty() const
{
    return m_Associations.IsEmpty();
}
//---------------------------------------------------------------------------
int PSS_FormulaAssociationManager::GetCount() const
{
    return m_Associations.GetCount();
}
//---------------------------------------------------------------------------
PSS_FormulaAssociation* PSS_FormulaAssociationManager::GetCurrentAssociation() const
{
    return m_pCurrentAssociation;
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::SetCurrentAssociation(PSS_FormulaAssociation* pCurrent)
{
    m_pCurrentAssociation = pCurrent;
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::SetCurrentAssociation(const CString& name)
{
    m_pCurrentAssociation = FindAssociation(name);
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::ClearCurrentAssociation()
{
    m_pCurrentAssociation = NULL;
}
//---------------------------------------------------------------------------

/**
* Formula association manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FormulaSchema : public CObject
{
    DECLARE_SERIAL(PSS_FormulaSchema)

    public:
        /**
        * Formula schema type
        */
        enum IEType
        {
            IE_T_User,
            IE_T_System
        };

        PSS_FormulaSchema();

        virtual ~PSS_FormulaSchema();

        /**
        * Clones the formula schema
        *@return the cloned formula schema, NULL on error
        */
        virtual PSS_FormulaSchema* Clone() const;

        /**
        * Gets the formula list
        *@return the formula list
        */
        virtual inline CObList& GetFormulaList();

        /**
        * Gets the schema name
        *@return the schema name
        */
        virtual inline const CString& GetSchemaName() const;

        /**
        * Sets the schema name
        *@param value - the schema name
        */
        virtual inline void SetSchemaName(const CString& value);

        /**
        * Gets the description
        *@return the description
        */
        virtual inline const CString& GetDescription() const;

        /**
        * Sets the schema description
        *@param value - the schema description
        */
        virtual inline void SetDescription(const CString& value);

        /**
        * Gets the formula schema type
        *@return the formula schema type
        */
        virtual inline const IEType GetFormulaSchemaType() const;

        /**
        * Sets the schema formula type
        *@param value - the schema formula type
        */
        virtual inline void SetFormulaSchemaType(IEType value);

        /**
        * Deletes the page formulas
        *@param page - the page index
        *@param redistribute - if TRUE, the formulas will be redistributed on the page
        */
        virtual BOOL DeletePageFormulas(int page, BOOL redistribute = TRUE);

        /**
        * Copies the page formulas
        *@param pFormulaDst - the destination formula
        *@param page - the page number
        */
        virtual BOOL CopyPageFormulas(PSS_FormulaSchema* pFormulaDst, int page);

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

    private:
        IEType  m_FormulaSchemaType;
        CObList m_Formulas;
        CString m_SchemaName;
        CString m_Description;
};

//---------------------------------------------------------------------------
// PSS_FormulaSchema
//---------------------------------------------------------------------------
CObList& PSS_FormulaSchema::GetFormulaList()
{
    return m_Formulas;
}
//---------------------------------------------------------------------------
const CString& PSS_FormulaSchema::GetSchemaName() const
{
    return m_SchemaName;
}
//---------------------------------------------------------------------------
void PSS_FormulaSchema::SetSchemaName(const CString& value)
{
    m_SchemaName = value;
}
//---------------------------------------------------------------------------
const CString& PSS_FormulaSchema::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_FormulaSchema::SetDescription(const CString& value)
{
    m_Description = value;
}
//---------------------------------------------------------------------------
const PSS_FormulaSchema::IEType PSS_FormulaSchema::GetFormulaSchemaType() const
{
    return m_FormulaSchemaType;
}
//---------------------------------------------------------------------------
void PSS_FormulaSchema::SetFormulaSchemaType(IEType value)
{
    m_FormulaSchemaType = value;
}
//---------------------------------------------------------------------------

/**
* Schema manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SchemaManager : public CObject
{
    DECLARE_SERIAL(PSS_SchemaManager)

    public:
        PSS_SchemaManager();

        PSS_SchemaManager(const PSS_SchemaManager& other);

        virtual ~PSS_SchemaManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        const PSS_SchemaManager & operator = (const PSS_SchemaManager& other);

        /**
        * Clones the schema manager
        *@return the cloned schema manager, NULL on error
        */
        PSS_SchemaManager* Clone() const;

        /**
        * Creates a schema manager
        *@param name - name
        */
        void Create(const CString& name);

        /**
        * Creates a standard empty schema manager
        */
        void CreateStandardEmptySchema();

        /**
        * Initializes the schema object pointer
        *@param doc - document
        */
        void InitializeSchemaObjectPointer(PSS_DocumentData& doc);

        /**
        * Copies the schema
        *@param source - source
        *@param newManager - new manager
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CopySchema(const CString& source, const CString newManager);

        /**
        * Gets the formula list
        *@param name - name
        *@return the formula list
        */
        CObList* GetFormulaList(const CString& name);

        /**
        * Gets the formula schemas
        *@param name - name
        *@return the formula schemas
        */
        CObList* GetFormulaSchema(const CString& name);

        /**
        * Deletes the formula list
        *@param name - name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL DeleteFormulaList(const CString& name);

        /**
        * Deletes a formula on a page
        *@param name - formula name
        *@param page - page index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL DeletePageFormulas(const CString& name, int page);

        /**
        * Deletes all formulas on a page
        *@param page - page index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL DeletePageFormulas(int page);

        /**
        * Copies all the formulas on a page
        *@param name - name
        *@param schemaDst - destination schema manager to copy from
        *@param page - page index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CopyPageFormulas(const CString& name, PSS_SchemaManager& schemaDst, int page);

        /**
        * Gets the formulas name array
        *@return the formula name array
        */
        CStringArray& GetFormulaArrayName();

        /**
        * Gets the formulas user name array
        *@return the formula user name array
        */
        CStringArray& GetFormulaUserArrayName();

        /**
        * Gets the formulas system name array
        *@return the formula system name array
        */
        CStringArray& GetFormulaSystemArrayName();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Read old format during a serialization
        *@param ar - archive
        */
        void ReadSerializeOldFormat(CArchive& ar);

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

    private:
        static CStringArray m_SchemaNameArray;
        CObList             m_Schemas;
};

#endif
