// formula.h : interface of the ZAFormula class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(__FORMULA_H)
#define __FORMULA_H

#ifdef _AFXEXT
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif



/////////////////////////////////////////////////////////////////////////
// Forward definition
class ZDDocument;
class PSS_DocumentData;
class PlanFinObject;


#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZAFormula : public CObject
{
protected:
    DECLARE_SERIAL(ZAFormula)
public:
    ZAFormula();
    ZAFormula( ZDDocument& Doc, const CString& str );
    ZAFormula(const ZAFormula &right);
    //    Make a clone of the object.
    ZAFormula* Clone();
    const ZAFormula & operator=(const ZAFormula &right);
    // Formula page
    int        GetPage() { return m_iPage; };
    void    SetPage( int iValue ) { m_iPage = iValue; };
    
    const CString     GetFormula() const { return m_sFormula; };

    const CString    GetObjectName() const { return m_sObjectName; };
    
    PlanFinObject*    GetResultObjectPointer() const { return m_ResultObject; };

    // Scans the formula list to find object pointer
    static void ConstructObjectPointer(PSS_DocumentData& doc, CObList& lstFormula);
    
// Implementation
public:
    CString            m_sFormula;
    CString            m_sExtractedFormula;
    CString            m_sObjectName;
    PlanFinObject*    m_ResultObject;
    int                m_iPage;
// Implementation
public:
    virtual ~ZAFormula();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};



class AFX_EXT_CLASS ZAFormulaAssociation    : public CObject
{
protected:
    DECLARE_SERIAL(ZAFormulaAssociation)
public:
    ZAFormulaAssociation();
    ZAFormulaAssociation( const CString Name, const CString ObjectNameInitiator );
    
    // Object initiator
    const CString    GetAssociationName() const { return m_AssociationName; };
    void            SetAssociationName( const CString Name ) { m_AssociationName = Name; };
    // Object initiator
    const CString    GetObjectNameInitiator() const { return m_ObjectNameInitiator; };
    void            SetObjectNameInitiator( const CString Name ) { m_ObjectNameInitiator = Name; };
    // Formula management
    void            AddFormula( ZAFormula* pFormula );
    void            DeleteFormula( const CString& Name );
    void            DeleteFormula( ZAFormula* pFormula );
    ZAFormula*        FindFormula( const CString& Name );
    ZAFormula*        GetFormulaAt( int Index );
    int                GetCount() const { return m_lstFormula.GetCount(); };
    CObList&        GetFormulaList() { return m_lstFormula; };
    

    ZAFormula*         FindFormulaFullString( const CString& Formula );
    
    // Clone the association formula
    ZAFormulaAssociation*    Clone();
    
    size_t GetFormulaArray( CStringArray& Array );
    
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
    
    void                AddAssociation( ZAFormulaAssociation* pAssociation );
    void                DeleteAssociation( const CString& Name );
    void                DeleteAssociation( ZAFormulaAssociation* pAssociation );
    ZAFormulaAssociation*    FindAssociation( const CString& Name );
    CStringArray&        GetAssociationArray() { return m_AssociationArrayName; };
    CStringArray&        RefreshAssociationArray();
    
    
    BOOL                IsEmpty() const { return m_lstAssociation.IsEmpty(); };
    int                    GetCount() const { return m_lstAssociation.GetCount(); };
    
    // Assigns the contents of the association manager
    void                AssignContents( const ZAFormulaAssociationManager& ManagerSource );
    // Clone the association manager
    ZAFormulaAssociationManager*    Clone();

    // Current association
    ZAFormulaAssociation*    GetCurrentAssociation() const { return m_pCurrentAssociation; };
    void                    ClearCurrentAssociation() { m_pCurrentAssociation = NULL; };
    void                     SetCurrentAssociation( ZAFormulaAssociation* pCurrent ) { m_pCurrentAssociation = pCurrent; };
    void                     SetCurrentAssociation( const CString Name ) { m_pCurrentAssociation = FindAssociation( Name ); };

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
enum    FormulaSchemaType{ UserSchema, SystemSchema };

class AFX_EXT_CLASS ZAFormulaSchema : public CObject
{
protected:
    DECLARE_SERIAL(ZAFormulaSchema)
public:
    ZAFormulaSchema();
    CObList&    GetFormulaList(){ return m_lstFormula; };
    void        SetSchemaName( const CString& sValue ){ m_sSchemaName = sValue; };
    void        SetDescription( const CString& sValue ){ m_sDescription = sValue; };
    void        SetFormulaSchemaType( const FormulaSchemaType& Value ){ m_FormulaSchemaType = Value; };
    BOOL        DeletePageFormulas( int iPage, BOOL bRedistribute = TRUE );
    BOOL        CopyPageFormulas( ZAFormulaSchema*    pFormulaDst, int iPage );
    const CString&    GetSchemaName(){ return m_sSchemaName; };
    const CString&    GetDescription(){ return m_sDescription; };
    const FormulaSchemaType    GetFormulaSchemaType(){ return m_FormulaSchemaType; };
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
    
    CObList*            GetFormulaList( const CString& sName );
    CObList*            GetFormulaSchema( const CString& sName );
    BOOL                DeleteFormulaList( const CString& sName );
    BOOL                DeletePageFormulas( const CString& sName, int iPage );
    BOOL                DeletePageFormulas( int iPage );
    BOOL                CopyPageFormulas( const CString& sName, ZASchemaManager& SchemaDst, int iPage );
    CStringArray&        GetFormulaArrayName();
    CStringArray&        GetFormulaUserArrayName();
    CStringArray&        GetFormulaSystemArrayName();
    void                Create( const CString& sName );
    void                CreateStandardEmptySchema();
    
    BOOL                CopySchema( const CString& sSource, const CString sNew );
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



#endif // __FORMULA_H
