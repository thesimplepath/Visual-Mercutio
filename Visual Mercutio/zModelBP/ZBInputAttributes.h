// ZBInputAttributes.h: interface for the ZBInputAttribute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBInputAttributes_H__30293825_AA01_4900_B87E_808BA14EE11B__INCLUDED_)
#define AFX_ZBInputAttributes_H__30293825_AA01_4900_B87E_808BA14EE11B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


class AFX_EXT_CLASS ZBInputAttribute : public CObject  
{
    DECLARE_SERIAL(ZBInputAttribute)
public:
    ZBInputAttribute();
    virtual ~ZBInputAttribute();

    /* Copy constructor. */
    ZBInputAttribute(const ZBInputAttribute& src);
    /* Assignment operator. */
    ZBInputAttribute& operator=(const ZBInputAttribute& src);
    /* Equal operatior */
    BOOL operator == (const ZBInputAttribute& Rule);
    /* Not Equal operatior */
    BOOL operator != (const ZBInputAttribute& Rule);
    /* Create a duplicate copy of this object. */
    virtual ZBInputAttribute* Dup() const;

    // Member accessors.
    int GetCategoryID() const;
    void SetCategoryID( int value );

    int GetItemID() const;
    void SetItemID( int value );

    int GetSymbolRef() const;
    void SetSymbolRef( int value );

    CString GetDefaultValue() const;
    void SetDefaultValue( CString value );

    int GetFlag() const;
    void SetFlag( int value );

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);


private:
    int m_CategoryID;
    int m_ItemID;
    int m_SymbolRef;
    CString m_DefaultValue;
    int m_Flag;
};


inline int ZBInputAttribute::GetCategoryID() const 
{
    return m_CategoryID;
}
inline void ZBInputAttribute::SetCategoryID( int value )
{
    m_CategoryID = value;
}


inline int ZBInputAttribute::GetItemID() const 
{
    return m_ItemID;
}
inline void ZBInputAttribute::SetItemID( int value )
{
    m_ItemID = value;
}


inline int ZBInputAttribute::GetSymbolRef() const 
{
    return m_SymbolRef;
}
inline void ZBInputAttribute::SetSymbolRef( int value )
{
    m_SymbolRef = value;
}


inline CString ZBInputAttribute::GetDefaultValue() const 
{
    return m_DefaultValue;
}
inline void ZBInputAttribute::SetDefaultValue( CString value )
{
    m_DefaultValue = value;
}


inline int ZBInputAttribute::GetFlag() const 
{
    return m_Flag;
}
inline void ZBInputAttribute::SetFlag( int value )
{
    m_Flag = value;
}



inline BOOL ZBInputAttribute::operator == (const ZBInputAttribute& Rule)
{
      return (Rule.GetCategoryID() == this->GetCategoryID() &&
            Rule.GetItemID() == this->GetItemID());
}

inline BOOL ZBInputAttribute::operator != (const ZBInputAttribute& Rule)
{
      return (Rule.GetCategoryID() != this->GetCategoryID() ||
            Rule.GetItemID() != this->GetItemID());
}





/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;


///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBInputAttributeSet | An array of ZBInputAttribute pointers.
//@iex typedef CCArray_T<ZBInputAttribute*,ZBInputAttribute*> ZBInputAttributeSet;
typedef CCArray_T<ZBInputAttribute*,ZBInputAttribute*> ZBInputAttributeSet;

//@type ZBInputAttribute | An iterator for ZBInputAttributeSet collections.
//@iex typedef Iterator_T<ZBInputAttribute*> ZBInputAttributeIterator;
typedef Iterator_T<ZBInputAttribute*> ZBInputAttributeIterator;




class AFX_EXT_CLASS ZBInputAttributeManager : public CObject
{
    DECLARE_SERIAL(ZBInputAttributeManager)

public:
    ZBInputAttributeManager();
    virtual ~ZBInputAttributeManager();
    /* Copy constructor. */
    ZBInputAttributeManager(const ZBInputAttributeManager& src);
    /* Assignment operator. */
    ZBInputAttributeManager& operator=(const ZBInputAttributeManager& src);
    /* Create a duplicate copy of this object. */
    virtual ZBInputAttributeManager* Dup() const;

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    ZBInputAttributeSet& GetInputAttributeSet()
    {
        return m_Set;
    };
    void DeleteAllInputAttributes();
    
    ZBInputAttribute* GetInputAttributeAt( size_t Index )
    {
        if (Index < GetInputAttributeCount())
            return m_Set.GetAt( Index );
        return NULL;
    };
    size_t GetInputAttributeCount() const
    {
        return m_Set.GetSize();
    };

    void AddInputAttribute( ZBInputAttribute* pInputAttribute, bool ReplaceExisting = true );
    bool Exist( ZBInputAttribute* pInputAttribute );
    bool DeleteInputAttribute( ZBInputAttribute* pInputAttribute );
    ZBInputAttribute* FindInputAttribute( int CategoryID, int ItemID, int SymbolRef );

private:
    void ReplaceInputAttribute( ZBInputAttribute* pInputAttribute );

private:
    ZBInputAttributeSet m_Set;

};

#endif // !defined(AFX_ZBInputAttributes_H__30293825_AA01_4900_B87E_808BA14EE11B__INCLUDED_)



