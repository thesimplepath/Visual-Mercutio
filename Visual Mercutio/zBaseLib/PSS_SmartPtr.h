/****************************************************************************
 * ==> PSS_SmartPtr --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several smart pointer implementations             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SmartPtrH
#define PSS_SmartPtrH

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

// disable the warning nb 4284 (return type for 'identifier::operator ->' isn't a UDT or reference to a UDT)
#pragma warning(disable : 4284)

/**
* Generic smart pointer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_SmartPtr
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_SmartPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_SmartPtr(const PSS_SmartPtr& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline void operator = (const PSS_SmartPtr& other);

        /**
        * Access operator
        *@return owned pointer
        */
        inline       T* const operator -> ();
        inline const T* const operator -> () const;

        /**
        * Access operator
        *@return owned pointer
        */
        inline       T& operator * ();
        inline const T& operator * () const;

        /**
        * Gets the owned pointer
        *@returnt he owned pointer
        */
        virtual inline       T* const GetPtr();
        virtual inline const T* const GetPtr() const;

        /**
        * Checks if owned pointer is NULL
        *@return TRUE if owned pointer is NULL, otherwise FALSE
        */
        virtual inline BOOL IsNull() const;

        /**
        * Throws a  memory exception if owned pointer is NULL
        */
        virtual inline void ThrowMemoryExceptionIfNull() const;

        /**
        * Swaps the content of two pointers (for sorting, etc)
        *@param other - other pointer to swap with
        */
        virtual inline void Swap(PSS_SmartPtr& other);

    protected:
        T* m_pPtr;
};

//---------------------------------------------------------------------------
// PSS_SmartPtr
//---------------------------------------------------------------------------
template<class T>
PSS_SmartPtr<T>::PSS_SmartPtr(T* pPtr) :
    m_pPtr(pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_SmartPtr<T>::PSS_SmartPtr(const PSS_SmartPtr<T>& other) :
    m_pPtr(other.m_pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
void PSS_SmartPtr<T>::operator = (const PSS_SmartPtr<T>& other)
{
    m_pPtr = other.m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
T* const PSS_SmartPtr<T>::operator -> ()
{
    return m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
const T* const PSS_SmartPtr<T>::operator -> () const
{
    return m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
T& PSS_SmartPtr<T>::operator * ()
{
    return *m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
const T& PSS_SmartPtr<T>::operator * () const
{
    return *m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
T* const PSS_SmartPtr<T>::GetPtr()
{
    return m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
const T* const PSS_SmartPtr<T>::GetPtr() const
{
    return m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
BOOL PSS_SmartPtr<T>::IsNull() const
{
    return (!m_pPtr);
}
//---------------------------------------------------------------------------
template<class T>
inline BOOL IsNull(const PSS_SmartPtr<T>& p)
{
    return (!p.GetPtr());
}
//---------------------------------------------------------------------------
template<class T>
void PSS_SmartPtr<T>::ThrowMemoryExceptionIfNull() const
{
    if (IsNull())
        AfxThrowMemoryException();
}
//---------------------------------------------------------------------------
template<class T>
inline void ThrowMemoryExceptionIfNull(const PSS_SmartPtr<T>& p)
{
    if (IsNull(p))
        AfxThrowMemoryException();
}
//---------------------------------------------------------------------------
template<class T>
inline void ThrowMemoryExceptionIfNull(T* pP)
{
    if (!pP)
        AfxThrowMemoryException();
}
//---------------------------------------------------------------------------
template<class T>
void PSS_SmartPtr<T>::Swap(PSS_SmartPtr<T>& other)
{
    T* pPtr      = other.m_pPtr;
    other.m_pPtr = m_pPtr;
    m_pPtr       = pPtr;
}
//---------------------------------------------------------------------------

/**
* Safe smart pointer, deletes the owning pointer at destruction
*@note WARNING! Copy operator is weird, it changes right-hand operand (makes it NULL actually)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_SafeSmartPtr : public PSS_SmartPtr<T>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_SafeSmartPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_SafeSmartPtr(PSS_SafeSmartPtr& other);

        virtual inline ~PSS_SafeSmartPtr();

        /**
        * Copy operator
        *@param pOther - other object to own to copy from
        *@return copy of itself
        */
        inline void operator = (T* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline void operator = (PSS_SafeSmartPtr& other);
};

//---------------------------------------------------------------------------
// PSS_SafeSmartPtr
//---------------------------------------------------------------------------
template<class T>
PSS_SafeSmartPtr<T>::PSS_SafeSmartPtr(T* pPtr) :
    PSS_SmartPtr<T>(pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_SafeSmartPtr<T>::PSS_SafeSmartPtr(PSS_SafeSmartPtr& other) :
    PSS_SmartPtr<T>(T)
{
    if (&other == this)
        return;

    other.m_pPtr = NULL;
}
//---------------------------------------------------------------------------
template<class T>
PSS_SafeSmartPtr<T>::~PSS_SafeSmartPtr()
{
    if (m_pPtr)
        delete m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_SafeSmartPtr<T>::operator = (T* pOther)
{
    if (pOther == m_pPtr)
        return;

    if (m_pPtr)
        delete m_pPtr;

    m_pPtr = pOther;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_SafeSmartPtr<T>::operator = (PSS_SafeSmartPtr& other)
{
    if (&other == this)
        return;

    if (m_pPtr)
        delete m_pPtr;

    m_pPtr       = other.m_pPtr;
    other.m_pPtr = NULL;
}
//---------------------------------------------------------------------------

/**
* Smart array of objects
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_SafeArray : public PSS_SmartPtr<T>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_SafeArray(T* pPtr = NULL);

        /**
        * Constructor
        *@param count - array count to reserve
        */
        inline PSS_SafeArray(int count);

        virtual inline ~PSS_SafeArray();

        /**
        * Access operator
        *@param index - index
        *@return owned pointer
        */
        inline       T& operator[] (int index);
        inline const T& operator[] (int index) const;

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SafeArray(const PSS_SafeArray& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        void operator = (const PSS_SafeArray& other);
};

//---------------------------------------------------------------------------
// PSS_SafeArray
//---------------------------------------------------------------------------
template<class T>
PSS_SafeArray<T>::PSS_SafeArray(T* pPtr) :
    PSS_SmartPtr<T>(pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_SafeArray<T>::PSS_SafeArray(int count) :
    PSS_SmartPtr<T>(new T[count])
{}
//---------------------------------------------------------------------------
template<class T>
PSS_SafeArray<T>::PSS_SafeArray(const PSS_SafeArray& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
template<class T>
PSS_SafeArray<T>::~PSS_SafeArray()
{
    if (m_pPtr)
        delete[] m_pPtr;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_SafeArray<T>::operator = (const PSS_SafeArray& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
template<class T>
T& PSS_SafeArray<T>::operator [] (int index)
{
    return m_pPtr[index];
}
//---------------------------------------------------------------------------
template<class T>
const T& PSS_SafeArray<T>::operator [] (int index) const
{
    return m_pPtr[i];
}
//---------------------------------------------------------------------------

/**
* Duplicatable smart array of objects, used for holding safe pointer to cloneable object
*@note Object must have a copy constructor, it will be used to create new object. For that reason,
*      the PSS_DuplSmartPtr class implements a copy constructor and a copy operator. The class
*      CANNOT handle inheritance trees, use PSS_CloneSmartPtr for that purpose
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_DuplSmartPtr : public PSS_SafeSmartPtr<T>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_DuplSmartPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_DuplSmartPtr(const PSS_DuplSmartPtr& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline PSS_DuplSmartPtr& operator = (const PSS_DuplSmartPtr& other);

        /**
        * Copy operator
        *@param pOther - other object to own to copy from
        *@return copy of itself
        */
        inline void operator = (T* pOther);
};

//---------------------------------------------------------------------------
// PSS_DuplSmartPtr
//---------------------------------------------------------------------------
template<class T>
PSS_DuplSmartPtr<T>::PSS_DuplSmartPtr(T* pPtr) :
    PSS_SafeSmartPtr<T>(pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_DuplSmartPtr<T>::PSS_DuplSmartPtr(const PSS_DuplSmartPtr& other) :
    PSS_SafeSmartPtr<T>(NULL)
{
    if (other.m_pPtr)
        m_pPtr = new T(*other.m_pPtr);
}
//---------------------------------------------------------------------------
template<class T>
PSS_DuplSmartPtr<T>& PSS_DuplSmartPtr<T>::operator = (const PSS_DuplSmartPtr& other)
{
    if (this != &other)
    {
        if (m_pPtr)
            delete m_pPtr;

        if (other.m_pPtr)
            m_pPtr = NULL;
        else
            m_pPtr = new T(*other.m_pPtr);
    }

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_DuplSmartPtr<T>::operator = (T* pOther)
{
    if (pOther == m_pPtr)
        return;

    if (m_pPtr)
        delete m_pPtr;

    m_pPtr = pOther;
}
//---------------------------------------------------------------------------

/**
* Clonable smart array of objects, used for holding safe pointer to cloneable object
*@note Object must have a clone function, it will be used to create new object. For that reason,
*      the PSS_CloneSmartPtr class implements a copy constructor and a copy operator. The
*      class can hold pointer inheritance trees members
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_CloneSmartPtr : public PSS_SafeSmartPtr<T>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_CloneSmartPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_CloneSmartPtr(const PSS_CloneSmartPtr& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline PSS_CloneSmartPtr& operator = (const PSS_CloneSmartPtr& other);

        /**
        * Copy operator
        *@param pOther - other object to own to copy from
        *@return copy of itself
        */
        inline void operator = (T* pOther);
};

//---------------------------------------------------------------------------
// PSS_CloneSmartPtr
//---------------------------------------------------------------------------
template<class T>
PSS_CloneSmartPtr<T>::PSS_CloneSmartPtr(T* pPtr) :
    PSS_SafeSmartPtr<T>(pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_CloneSmartPtr<T>::PSS_CloneSmartPtr(const PSS_CloneSmartPtr& other) :
    PSS_SafeSmartPtr<T>(NULL)
{
    if (other.m_pPtr)
        m_pPtr = other.m_pPtr->Clone();
}
//---------------------------------------------------------------------------
template<class T>
PSS_CloneSmartPtr<T>& PSS_CloneSmartPtr<T>::operator = (const PSS_CloneSmartPtr<T>& other)
{
    if (this != &other)
    {
        if (m_pPtr)
            delete m_pPtr;

        if (!other.m_pPtr)
            m_pPtr = NULL;
        else
            m_pPtr = other.m_pPtr->Clone();
    }

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_CloneSmartPtr<T>::operator = (T* pOther)
{
    if (pOther == m_pPtr)
        return;

    delete m_pPtr;
    m_pPtr = pOther;
}
//---------------------------------------------------------------------------

/**
* Recommended (but NOT required) base for clonabe classes
*/
template<class T>
T* CloneMe(const T& other)
{
    return new T(other);
}

/**
* Clonabe interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_Clonable
{
    public:
        virtual inline ~PSS_Clonable();

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        *@note This must be declared in every child: { return CloneMe(this); }
        */
        virtual PSS_Clonable* Clone() const = 0;
};

//---------------------------------------------------------------------------
// PSS_Clonable
//---------------------------------------------------------------------------
PSS_Clonable::~PSS_Clonable()
{}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Alternative MACRO (Yack!) for clonability
//---------------------------------------------------------------------------
#define DECLARE_CLONABLE(T) public: virtual T* Clone() const { return (T*)::CloneMe(*this); }
//---------------------------------------------------------------------------

/**
* Basic multi-reference smart pointer
*@note This is really a smart pointer. It implements garbage collection by usage counting.
*      Template parameter COUNT means class int-like for reference counting. It may be int,
*      like in PSS_MultiRefSmartPtr, or some optimized for multiply allocations class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T, class U>
class PSS_BaseMultiRefSmartPtr : public PSS_SmartPtr<T>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_BaseMultiRefSmartPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_BaseMultiRefSmartPtr(const PSS_BaseMultiRefSmartPtr& other);

        virtual inline ~PSS_BaseMultiRefSmartPtr();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        inline PSS_BaseMultiRefSmartPtr& operator = (const PSS_BaseMultiRefSmartPtr& other);

        /**
        * Copy operator
        *@param pOther - other pointer to object to own to copy from
        *@return copy of itself
        */
        inline void operator = (T* pOther);

        /**
        * Equality operator
        *@param other - other object to compare with
        *@return true if objects are equals, otherwise false
        */
        inline bool operator == (const PSS_BaseMultiRefSmartPtr& other) const;

        /**
        * Difference operator
        *@param other - other object to compare with
        *@return true if objects aren't equals, otherwise false
        */
        inline bool operator != (const PSS_BaseMultiRefSmartPtr& other) const;

        /**
        * Swaps the content of two pointers (for sorting, etc)
        *@param other - other pointer to swap with
        */
        virtual inline void Swap(PSS_BaseMultiRefSmartPtr& other);

        /**
        * Check if this smart pointer contains the last known instance of the object to own
        *@return true if this smart pointer contains the last known instance of the object to own, otherwise false
        */
        virtual inline bool IsLastOne() const;

        /**
        * Check if this smart pointer contains an object shared with other smart pointers
        *@return true if this smart pointer contains an object shared with other smart pointers, otherwise false
        */
        virtual inline bool IsShared() const;

    protected:
        /**
        * Copies the smart pointer content
        *@param other - other pointer to copy from
        */
        virtual void Copy(const PSS_BaseMultiRefSmartPtr& other);

        /**
        * Builds a copy of the smart pointer
        *@param pPtr - other pointer to build from
        */
        virtual void Construct(T* pPtr);

        /**
        * Deletes the smart pointer content
        */
        virtual void Delete();

    protected:
        U* m_pRefCount;
};

//---------------------------------------------------------------------------
// PSS_BaseMultiRefSmartPtr
//---------------------------------------------------------------------------
template<class T, class U>
PSS_BaseMultiRefSmartPtr<T, U>::PSS_BaseMultiRefSmartPtr(T* pPtr)
{
    Construct(pPtr);
}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_BaseMultiRefSmartPtr<T, U>::PSS_BaseMultiRefSmartPtr(const PSS_BaseMultiRefSmartPtr<T, U>& other)
{
    Copy(other);
}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_BaseMultiRefSmartPtr<T, U>::~PSS_BaseMultiRefSmartPtr()
{
    Delete();
}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_BaseMultiRefSmartPtr<T, U>& PSS_BaseMultiRefSmartPtr<T, U>::operator = (const PSS_BaseMultiRefSmartPtr<T, U>& other)
{
    if (this != &other)
    {
        Delete();
        Copy(other);
    }

    return *this;
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_BaseMultiRefSmartPtr<T, U>::operator = (T* pOther)
{
    if (m_pPtr == pOther)
        return;

    Delete();
    Construct(pOther);
}
//---------------------------------------------------------------------------
template<class T, class U>
bool PSS_BaseMultiRefSmartPtr<T, U>::operator == (const PSS_BaseMultiRefSmartPtr<T, U>& other) const
{
    return (m_pPtr == other.m_pPtr);
}
//---------------------------------------------------------------------------
template<class T, class U>
bool PSS_BaseMultiRefSmartPtr<T, U>::operator != (const PSS_BaseMultiRefSmartPtr<T, U>& other) const
{
    return (m_pPtr != t.m_pPtr);
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_BaseMultiRefSmartPtr<T, U>::Swap(PSS_BaseMultiRefSmartPtr<T, U>& other)
{
    PSS_SmartPtr<T>::Swap(other);
    U* pRefCount      = other.m_pRefCount;
    other.m_pRefCount = m_pRefCount;
    m_pRefCount       = pRefCount;
}
//---------------------------------------------------------------------------
template<class T, class U>
bool PSS_BaseMultiRefSmartPtr<T, U>::IsLastOne() const
{
    return (m_pRefCount && (*m_pRefCount == 1));
}
//---------------------------------------------------------------------------
template<class T, class U>
bool PSS_BaseMultiRefSmartPtr<T, U>::IsShared() const
{
    return (m_pRefCount && (*m_pRefCount > 1));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_BaseMultiRefSmartPtr<T, U>::Copy(const PSS_BaseMultiRefSmartPtr<T, U>& other)
{
    m_pPtr      = other.m_pPtr;
    m_pRefCount = other.m_pRefCount;

    if (m_pRefCount)
    {
        PSS_Assert(m_pPtr);
        ++*m_pRefCount;
    }
    else
        PSS_Assert(!m_pPtr);

    return;
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_BaseMultiRefSmartPtr<T, U>::Construct(T* pPtr)
{
    m_pPtr      = pPtr;
    m_pRefCount = NULL;

    if (m_pPtr)
    {
        m_pRefCount = new U(1);
        ::ThrowMemoryExceptionIfNull(m_pRefCount);
    }

    return;
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_BaseMultiRefSmartPtr<T, U>::Delete()
{
    if (!m_pRefCount)
    {
        PSS_Assert(!m_pPtr);
        return;
    }

    PSS_Assert(m_pPtr);

    if (--*m_pRefCount == 0)
    {
        delete m_pRefCount;
        m_pRefCount = NULL;
        
        delete m_pPtr;
        m_pPtr = NULL;
    }

    return;
}
//---------------------------------------------------------------------------

/**
* Multi-reference smart pointer using an integer as a simple counter
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_MultiRefSmartPtr : public PSS_BaseMultiRefSmartPtr<T, int>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        PSS_MultiRefSmartPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MultiRefSmartPtr(const PSS_MultiRefSmartPtr& other);

        virtual inline ~PSS_MultiRefSmartPtr();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_MultiRefSmartPtr& operator = (const PSS_MultiRefSmartPtr& other);

        /**
        * Copy operator
        *@param pOther - other object to own to copy from
        *@return copy of itself
        */
        void operator = (T* pOther);
};

//---------------------------------------------------------------------------
// PSS_MultiRefSmartPtr
//---------------------------------------------------------------------------
template<class T>
PSS_MultiRefSmartPtr<T>::PSS_MultiRefSmartPtr(T* pPtr) :
    PSS_BaseMultiRefSmartPtr<T, int>(pPtr)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_MultiRefSmartPtr<T>::PSS_MultiRefSmartPtr(const PSS_MultiRefSmartPtr<T>& other) :
    PSS_BaseMultiRefSmartPtr<T, int>(other)
{}
//---------------------------------------------------------------------------
template<class T>
PSS_MultiRefSmartPtr<T>::~PSS_MultiRefSmartPtr()
{}
//---------------------------------------------------------------------------
template<class T>
PSS_MultiRefSmartPtr<T>& PSS_MultiRefSmartPtr<T>::operator = (const PSS_MultiRefSmartPtr<T>& other)
{
    PSS_BaseMultiRefSmartPtr<T, int>::operator = (other);
    return *this;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_MultiRefSmartPtr<T>::operator = (T* pOther)
{
    PSS_BaseMultiRefSmartPtr<T, int>::operator = (pPtr);
}
//---------------------------------------------------------------------------

/**
* Counter multi-reference smart pointer interface, it's a counting pointer variant
*@note This smart pointer is most effective but it has significant limitation:
*      - The class it points to (or the root class of the hierarchy) must implement
*        reference counting itself
*      - The simplest way to do this is to derive it from ZReferenceCounterBase. The
*        catch is that you cannot have it in multiple derivation several times, and,
*        the worst, you must be the author of this class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ReferenceCounterBase
{
    public:
        inline PSS_ReferenceCounterBase();

        /**
        * Adds a reference to the object
        */
        virtual inline void AddReference();

        /**
        * Removes a reference from the object
        *@return the new count
        */
        virtual inline int RemoveReference();

        /**
        * Gets the reference count
        *@return the reference count
        */
        virtual inline int GetReferenceCount() const;

    private:
        int m_Counter;
};

//---------------------------------------------------------------------------
// PSS_ReferenceCounterBase
//---------------------------------------------------------------------------
PSS_ReferenceCounterBase::PSS_ReferenceCounterBase() :
    m_Counter(1)
{}
//---------------------------------------------------------------------------
void PSS_ReferenceCounterBase::AddReference()
{
    ++m_Counter;
}
//---------------------------------------------------------------------------
int PSS_ReferenceCounterBase::RemoveReference()
{
    return --m_Counter;
}
//---------------------------------------------------------------------------
int PSS_ReferenceCounterBase::GetReferenceCount() const
{
    return m_Counter;
}
//---------------------------------------------------------------------------

/**
* Counter multi-reference smart pointer, it's a counting pointer variant
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_CounterMultiRefPtr : public PSS_SmartPtr<T>
{
    public:
        /**
        * Constructor
        *@param pPtr - pointer to object to own, can be NULL
        */
        inline PSS_CounterMultiRefPtr(T* pPtr = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_CounterMultiRefPtr(const PSS_CounterMultiRefPtr& other);

        virtual inline ~PSS_CounterMultiRefPtr();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline PSS_CounterMultiRefPtr& operator = (const PSS_CounterMultiRefPtr& other);

        /**
        * Copy operator
        *@param pOther - other pointer to object to own to copy from
        *@return copy of itself
        */
        inline void operator = (T* pOther);

        /**
        * Equality operator
        *@param other - other object to compare with
        *@return true if objects are equals, otherwise false
        */
        inline bool operator == (const PSS_CounterMultiRefPtr& other) const;

        /**
        * Difference operator
        *@param other - other object to compare with
        *@return true if objects aren't equals, otherwise false
        */
        inline bool operator != (const PSS_CounterMultiRefPtr& other) const;

        /**
        * Swaps the content of two pointers (for sorting, etc)
        *@param other - other pointer to swap with
        */
        virtual inline void Swap(PSS_CounterMultiRefPtr& other);

        /**
        * Check if this smart pointer contains the last known instance of the object to own
        *@return true if this smart pointer contains the last known instance of the object to own, otherwise false
        */
        virtual inline bool IsLastOne() const;

        /**
        * Check if this smart pointer contains an object shared with other smart pointers
        *@return true if this smart pointer contains an object shared with other smart pointers, otherwise false
        */
        virtual inline bool IsShared() const;

    protected:
        /**
        * Copies the smart pointer content
        *@param other - other pointer to copy from
        */
        virtual inline void Copy(const PSS_CounterMultiRefPtr& other);

        /**
        * Builds a copy of the smart pointer
        *@param pPtr - other pointer to build from
        */
        virtual inline void Construct(T* pPtr);

        /**
        * Deletes the smart pointer content
        */
        virtual inline void Delete();
};

//---------------------------------------------------------------------------
// PSS_CounterMultiRefPtr
//---------------------------------------------------------------------------
template<class T>
PSS_CounterMultiRefPtr<T>::PSS_CounterMultiRefPtr(T* pPtr)
{
    Construct(pPtr);
}
//---------------------------------------------------------------------------
template<class T>
PSS_CounterMultiRefPtr<T>::PSS_CounterMultiRefPtr(const PSS_CounterMultiRefPtr& other)
{
    Copy(other);
}
//---------------------------------------------------------------------------
template<class T>
PSS_CounterMultiRefPtr<T>::~PSS_CounterMultiRefPtr()
{
    Delete();
}
//---------------------------------------------------------------------------
template<class T>
PSS_CounterMultiRefPtr<T>& PSS_CounterMultiRefPtr<T>::operator = (const PSS_CounterMultiRefPtr& other)
{
    if (this != &other)
    {
        Delete();
        Copy(other);
    }

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_CounterMultiRefPtr<T>::operator = (T* pOther)
{
    if (m_pPtr == pOther)
        return;

    Delete();
    Construct(pPtr);
}
//---------------------------------------------------------------------------
template<class T>
bool PSS_CounterMultiRefPtr<T>::operator == (const PSS_CounterMultiRefPtr& other) const
{
    return (m_pPtr == other.m_pPtr);
}
//---------------------------------------------------------------------------
template<class T>
bool PSS_CounterMultiRefPtr<T>::operator != (const PSS_CounterMultiRefPtr& other) const
{
    return (m_pPtr != other.m_pPtr);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_CounterMultiRefPtr<T>::Swap(PSS_CounterMultiRefPtr& other)
{
    PSS_SmartPtr<T>::Swap(other);
}
//---------------------------------------------------------------------------
template<class T>
bool PSS_CounterMultiRefPtr<T>::IsLastOne() const
{
    return (m_pPtr && (m_pPtr->GetReferenceCount() == 1));
}
//---------------------------------------------------------------------------
template<class T>
bool PSS_CounterMultiRefPtr<T>::IsShared() const
{
    return (m_pPtr && (m_pPtr->GetReferenceCount() > 1));
}
//---------------------------------------------------------------------------
template<class T>
void PSS_CounterMultiRefPtr<T>::Copy(const PSS_CounterMultiRefPtr& other)
{
    m_pPtr = other.m_pPtr;

    if (m_pPtr)
        m_pPtr->AddReference();

    return;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_CounterMultiRefPtr<T>::Construct(T* pPtr)
{
    m_pPtr = pPtr;
    return;
}
//---------------------------------------------------------------------------
template<class T>
void PSS_CounterMultiRefPtr<T>::Delete()
{
    if (!m_pPtr)
        return;

    if (!m_pPtr->RemoveReference())
    {
        delete m_pPtr;
        m_pPtr = NULL;
    }

    return;
}
//---------------------------------------------------------------------------

/**
* Stores a smart pointer
*@param ar - archive
*@param pointer - pointer
*/
template<class T>
inline void StoreSmartPtr(CArchive& ar, const T& pointer)
{
    ar << pointer.GetPtr();
}

/**
* Loads a smart pointer
*@param ar - archive
*@param pointer - pointer
*@param pDataType - data type
*/
template<class T, class U>
inline void LoadSmartPtr(CArchive& ar, T& pointer, U* pDataType)
{
    pointer   = NULL;
    pDataType = NULL;

    ar >> pDataType;

    pointer = pDataType;
}

/**
* Smart pointer array without GOOD copy operations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_RefArgArray : public CArray<T, T&>
{
    public:
        /**
        * Access operator
        *@param index - index
        *@return owned object
        */
              T& operator [] (int index);
        const T& operator [] (int index) const;

        /**
        * Gets item at index
        *@param index - index
        *@return owned object
        */
        const T& GetAt(int index) const;
};

//---------------------------------------------------------------------------
// PSS_RefArgArray
//---------------------------------------------------------------------------
template<class T>
T& PSS_RefArgArray<T>::operator [] (int index)
{
    return ElementAt(index);
}
//---------------------------------------------------------------------------
template<class T>
const T& PSS_RefArgArray<T>::operator [] (int index) const
{
    return GetAt(i);
}
//---------------------------------------------------------------------------
template<class T>
const T& PSS_RefArgArray<T>::GetAt(int index) const
{
    return const_cast<PSS_RefArgArray*>(this)->ElementAt(index);
}
//---------------------------------------------------------------------------

/**
* Generic smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T, class U>
class PSS_GenSmartPtrArray : public PSS_RefArgArray<T>
{
    typedef PSS_RefArgArray<T> inherited;

    public:
        inline PSS_GenSmartPtrArray();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_GenSmartPtrArray(const PSS_GenSmartPtrArray& other);

        virtual inline ~PSS_GenSmartPtrArray();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline PSS_GenSmartPtrArray& operator = (const PSS_GenSmartPtrArray& other);

        /**
        * Copy and increment operator
        *@param other - other object to copy and increment from
        *@return copy of itself
        */
        inline PSS_GenSmartPtrArray& operator += (const PSS_GenSmartPtrArray& other);

        /**
        * Adds a pointer
        *@param pPtr - pointer to add
        *@return new array count
        */
        virtual inline int Add(U* pPtr);

        /**
        * Adds a smart pointer
        *@param other - smart pointer to add
        *@return new array count
        */
        virtual inline void Add(const PSS_GenSmartPtrArray& other);

        /**
        * Sets a pointer at index and grows the array
        *@param index - index
        *@param pPtr - pointer to add
        */
        virtual inline void SetAtGrow(int index, U* pPtr);

        /**
        * Sets a pointer at index
        *@param index - index
        *@param pPtr - pointer to add
        */
        virtual inline void SetAt(int index, U* pPtr);

        /**
        * Inserts a pointer at index
        *@param index - index
        *@param pPtr - pointer to add
        */
        virtual inline void InsertAt(int index, U* pPtr);

        /**
        * Swaps the content of two pointers (for sorting, etc)
        *@param i - index to swap
        *@param j - index to swap with
        */
        virtual inline void Swap(int i, int j);

    private:
        /**
        * Copies the array content
        *@param other - other smart pointer to copy from
        */
        virtual void CopyArray(const PSS_GenSmartPtrArray& other);
};

//---------------------------------------------------------------------------
// PSS_GenSmartPtrArray
//---------------------------------------------------------------------------
template<class T, class U>
PSS_GenSmartPtrArray<T, U>::PSS_GenSmartPtrArray()
{}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_GenSmartPtrArray<T, U>::PSS_GenSmartPtrArray(const PSS_GenSmartPtrArray<T, U>& other)
{
    CopyArray(other);
}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_GenSmartPtrArray<T, U>::~PSS_GenSmartPtrArray()
{}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_GenSmartPtrArray<T, U>& PSS_GenSmartPtrArray<T, U>::operator = (const PSS_GenSmartPtrArray<T, U>& other)
{
    RemoveAll();
    CopyArray(other);

    return *this;
}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_GenSmartPtrArray<T, U>& PSS_GenSmartPtrArray<T, U>::operator += (const PSS_GenSmartPtrArray<T, U>& other)
{
    CopyArray(other);
    return *this;
}
//---------------------------------------------------------------------------
template<class T, class U>
int PSS_GenSmartPtrArray<T, U>::Add(U* pPtr)
{
    return inherited::Add(T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_GenSmartPtrArray<T, U>::Add(const PSS_GenSmartPtrArray<T, U>& other)
{
    CopyArray(other);
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_GenSmartPtrArray<T, U>::SetAtGrow(int index, U* pPtr)
{
    inherited::SetAtGrow(index, T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_GenSmartPtrArray<T, U>::SetAt(int index, U* pPtr)
{
    inherited::SetAt(index, T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_GenSmartPtrArray<T, U>::InsertAt(int index, U* pPtr)
{
    inherited::InsertAt(index, T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_GenSmartPtrArray<T, U>::Swap(int i, int j)
{
    PSS_Assert(i >= 0 && i < GetSize());
    PSS_Assert(j >= 0 && j < GetSize());
    PSS_Assert(i != j);

    ElementAt(i).Swap(ElementAt(j));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_GenSmartPtrArray<T, U>::CopyArray(const PSS_GenSmartPtrArray<T, U>& other)
{
    const int n = other.GetSize();
    const int s = GetSize();

    SetSize(s + n);

    for (int i = 0; i < n; ++i)
        ElementAt(i + s) = const_cast<PSS_GenSmartPtrArray&>(other).ElementAt(i);
}
//---------------------------------------------------------------------------

/**
* Array of smart pointer with GOOD copy operations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T, class U>
class PSS_CopySmartPtrArray : public PSS_GenSmartPtrArray<T, U>
{
    public:
        /**
        * Adds a pointer
        *@param pointer - pointer to add
        *@return new array count
        */
        virtual inline int Add(T& pointer);

        /**
        * Adds a pointer
        *@param pPtr - pointer to add
        *@return new array count
        */
        virtual inline int Add(U* pPtr);

        /**
        * Sets a pointer at index
        *@param index - index
        *@param pointer - pointer to add
        */
        virtual inline void SetAtGrow(int index, T& pointer);

        /**
        * Sets a pointer at index
        *@param index - index
        *@param pPtr - pointer to add
        */
        virtual inline void SetAtGrow(int index, U* pPtr);

        /**
        * Inserts a pointer at index
        *@param index - index
        *@param pointer - pointer to add
        */
        virtual inline void SetAt(int index, T& pointer);

        /**
        * Inserts a pointer at index
        *@param index - index
        *@param pPtr - pointer to add
        */
        virtual inline void SetAt(int index, U* pPtr);

        /**
        * Inserts a pointer at index
        *@param index - index
        *@param pointer - pointer to add
        */
        virtual inline void InsertAt(int index, T& pointer);

        /**
        * Inserts a pointer at index
        *@param index - index
        *@param pPtr - pointer to add
        */
        virtual inline void InsertAt(int index, U* pPtr);
};

//---------------------------------------------------------------------------
// PSS_CopySmartPtrArray
//---------------------------------------------------------------------------
template<class T, class U>
int PSS_CopySmartPtrArray<T, U>::Add(T& pointer)
{
    return inherited::Add(pointer);
}
//---------------------------------------------------------------------------
template<class T, class U>
int PSS_CopySmartPtrArray<T, U>::Add(U* pPtr)
{
    return inherited::Add(T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_CopySmartPtrArray<T, U>::SetAtGrow(int index, T& pointer)
{
    inherited::SetAtGrow(index, pointer);
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_CopySmartPtrArray<T, U>::SetAtGrow(int index, U* pPtr)
{
    inherited::SetAtGrow(index, T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_CopySmartPtrArray<T, U>::SetAt(int index, T& pointer)
{
    inherited::SetAt(index, pointer);
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_CopySmartPtrArray<T, U>::SetAt(int index, U* pPtr)
{
    inherited::SetAt(index, T(pPtr));
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_CopySmartPtrArray<T, U>::InsertAt(int index, T& pointer)
{
    inherited::InsertAt(index, pointer);
}
//---------------------------------------------------------------------------
template<class T, class U>
void PSS_CopySmartPtrArray<T, U>::InsertAt(int index, U* pPtr)
{
    inherited::InsertAt(index, T(pPtr));
}
//---------------------------------------------------------------------------

/**
* Smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_SmartPtrArray : public PSS_GenSmartPtrArray<PSS_SmartPtr<T>, T>
{};

/**
* Safe smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_SafeSmartPtrArray : public PSS_GenSmartPtrArray<PSS_SafeSmartPtr<T>, T>
{};

/**
* Duplicatable smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_DuplSmartPtrArray : public PSS_GenSmartPtrArray<PSS_DuplSmartPtr<T>, T>
{};

/**
* Clonable smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_CloneSmartPtrArray : public PSS_GenSmartPtrArray<PSS_CloneSmartPtr<T>, T>
{};

/**
* Basic multiple reference smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T, class U>
class PSS_BaseMultiRefSmartPtrArray : public PSS_CopySmartPtrArray<PSS_BaseMultiRefSmartPtr<T, U>, T>
{};

/**
* Multiple reference smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_MultiRefSmartPtrArray : public PSS_CopySmartPtrArray<PSS_MultiRefSmartPtr<T>, T>
{};

/**
* Counter multiple reference smart pointer array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class PSS_CounterMultiRefPtrArray : public PSS_CopySmartPtrArray<PSS_CounterMultiRefPtr<T>, T>
{};

/**
* Deep copy array
*@param a1 - first array to copy
*@param a2 - second array to copy
*/
template<class T>
int DeepCopyArray(T& a1, const T& a2)
{
    const int max = a2.GetSize();

    a1.RemoveAll();

    if (max > 0)
    {
        a1.SetSize(max);

        for (int i = 0; i < max; ++i)
            a1[i] = a2[i]->Clone();
    }

    return imax;
}

/**
* Serializes the array
*@param arr - first array to copy
*@param pPtr - pointer
*@param ar - archive
*@param version - version
*/
template<class T, class U>
void SerializeArray(T& arr, U* pPtr, CArchive& ar, int version)
{
    // throw exception if wrong version
    SerializeVersion(ar, version, TRUE);

    long n;

    if (ar.IsStoring())
    {
        n = arr.GetSize();
        ar << n;

        for (int i = 0 ; i < n; ++i)
            StoreSmartPtr(ar, arr.ElementAt(i));
    }
    else
    {
        arr.RemoveAll();

        ar >> n;
        arr.SetSize(n);

        for (int i = 0; i < n; ++i)
        {
            LoadSmartPtr(ar, arr.ElementAt(i), (U*)NULL);

            if (arr.ElementAt(i).IsNull())
                ::AfxThrowArchiveException(CArchiveException::badSchema, ar.m_strFileName);
        }
    }
}

/**
* Smart pointer comparer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T, class U>
class PSS_SmartPrtComparer
{
    public:
        inline PSS_SmartPrtComparer();

        /**
        * Compares the smart pointers
        *@param arr - array
        *@param i - first smart pointer index to compare
        *@param j - second smart pointer index to compare with
        *@return < 0 if first smart pointer is smaller than second, > 0 if first smart pointer is higher than second,
        *        0 if smart pointers are equals
        */
        virtual inline int Compare(T& arr, int i, int j) const;

    private:
        U m_RealComparer;
};

//---------------------------------------------------------------------------
// PSS_CopySmartPtrArray
//---------------------------------------------------------------------------
template<class T, class U>
PSS_SmartPrtComparer<T, U>::PSS_SmartPrtComparer()
{}
//---------------------------------------------------------------------------
template<class T, class U>
int PSS_SmartPrtComparer<T, U>::Compare(T& arr, int i, int j) const
{
    return m_RealComparer.Compare(*(arr[i]), *(arr[j]));
}
//---------------------------------------------------------------------------

/**
* Sorts the array
*@param arr - array
*@param comparer - comparer
*/
template<class T, class U>
void SortSmartPrtArray(T& arr, U& comparer)
{
    if (arr.GetSize() > 1)
    {
        PSS_SmartPrtComparer<T, U> comp;
        CWizArrSort< T, PSS_SmartPrtComparer<T, U> > sorter(arr, comp);
        sorter.Sort();
    }
}

/**
* Serializes the version
*@param ar - archive
*@param version - version
*@param throwEx - if TRUE, exception will be thrown on error
*@return the version
*/
inline int SerializeVersion(CArchive& ar, const int version, BOOL throwEx = TRUE)
{
    WORD v = version;

    if (ar.IsStoring())
    {
        ar << v;
        return version;
    }
    else
    {
        ar >> v;

        if (throwEx && version != v)
            ::AfxThrowArchiveException(CArchiveException::badSchema, ar.m_strFileName);

        return v;
    }
}

/**
* Multi pointer
*@note Warning!!! class TYPE must have default constructor !!!
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template <class T, class U>
class PSS_BaseMultiPtr
{
    public:
        inline PSS_BaseMultiPtr();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_BaseMultiPtr(const PSS_BaseMultiPtr& other);

        virtual inline ~PSS_BaseMultiPtr();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline PSS_BaseMultiPtr& operator = (const PSS_BaseMultiPtr& other);

        /**
        * Access operator
        *@return owned pointer
        */
        inline       T* operator -> ();
        inline const T* operator -> () const;

        /**
        * Access operator
        *@return owned pointer
        */
        inline       T& operator * ();
        inline const T& operator * () const;

        /**
        * Gets the owned pointer
        *@returnt he owned pointer
        */
        virtual inline       T* GetPtr();
        virtual inline const T* GetPtr() const;

    protected:
        U* m_pObject;

        /**
        * Constructor
        *@param pObject - object to own
        */
        PSS_BaseMultiPtr(U* pObject);

        /**
        * Initializes the pointer
        *@param pointer - pointer
        */
        void Init(const PSS_BaseMultiPtr& pointer);

        /**
        * Cleans up the pointer
        */
        void CleanUp();
};

//---------------------------------------------------------------------------
// PSS_BaseMultiPtr
//---------------------------------------------------------------------------
template <class T, class U>
PSS_BaseMultiPtr<T, U>::PSS_BaseMultiPtr() :
    m_pObject(new U)
{}
//---------------------------------------------------------------------------
template <class T, class U>
PSS_BaseMultiPtr<T, U>::PSS_BaseMultiPtr(U* pObject) :
    m_pObject(pObject)
{}
//---------------------------------------------------------------------------
template <class T, class U>
PSS_BaseMultiPtr<T, U>::PSS_BaseMultiPtr(const PSS_BaseMultiPtr<T, U>& other) :
    m_pObject(NULL)
{
    Init(other);
}
//---------------------------------------------------------------------------
template <class T, class U>
PSS_BaseMultiPtr<T, U>::~PSS_BaseMultiPtr()
{
    CleanUp();
}
//---------------------------------------------------------------------------
template <class T, class U>
PSS_BaseMultiPtr<T, U>& PSS_BaseMultiPtr<T, U>::operator = (const PSS_BaseMultiPtr<T, U>& other)
{
    CleanUp();
    Init(other);

    return *this;
}
//---------------------------------------------------------------------------
template <class T, class U>
T* PSS_BaseMultiPtr<T, U>::operator -> ()
{
    return &(m_pObject->Data);
}
//---------------------------------------------------------------------------
template <class T, class U>
const T* PSS_BaseMultiPtr<T, U>::operator -> () const
{
    return &(m_pObject->Data);
}
//---------------------------------------------------------------------------
template <class T, class U>
T& PSS_BaseMultiPtr<T, U>::operator * ()
{
    return m_pObject->Data;
}
//---------------------------------------------------------------------------
template <class T, class U>
const T& PSS_BaseMultiPtr<T, U>::operator * () const
{
    return m_pObject->Data;
}
//---------------------------------------------------------------------------
template <class T, class U>
T* PSS_BaseMultiPtr<T, U>::GetPtr()
{
    return &(m_pObject->Data);
}
//---------------------------------------------------------------------------
template <class T, class U>
const T* PSS_BaseMultiPtr<T, U>::GetPtr() const
{
    return &(m_pObject->Data);
}
//---------------------------------------------------------------------------
template <class T, class U>
void PSS_BaseMultiPtr<T, U>::Init(const PSS_BaseMultiPtr<T, U>& pointer)
{
    if (!pointer.m_pObject)
        m_pObject = new U;
    else
    {
        m_pObject = other.m_pObject;
        ++other.m_pObject->Counter;
    }
}
//---------------------------------------------------------------------------
template <class T, class U>
void PSS_BaseMultiPtr<T, U>::CleanUp()
{
    if (!m_pObject)
        return;

    if (m_pObject->Counter <= 1)
    {
        delete m_pObject;
        m_pObject = NULL;
    }
    else
        --m_pObject->Counter;
}
//---------------------------------------------------------------------------

/**
* Simple container type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template <class T>
class PSS_SimpleCntType
{
    public:
        T   m_Data;
        int m_Counter;

        inline PSS_SimpleCntType();
        virtual inline ~PSS_SimpleCntType();
};

//---------------------------------------------------------------------------
// PSS_SimpleCntType
//---------------------------------------------------------------------------
template <class T>
PSS_SimpleCntType<T>::PSS_SimpleCntType() :
    m_Counter(1)
{}
//---------------------------------------------------------------------------
template <class T>
PSS_SimpleCntType<T>::~PSS_SimpleCntType()
{
    m_Counter = -1;
}
//---------------------------------------------------------------------------

/**
* Multi-pointer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template <class T>
class PSS_MultiPtr : public PSS_BaseMultiPtr< T, PSS_SimpleCntType<T> >
{
    public:
        PSS_MultiPtr();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_MultiPtr& operator = (const PSS_MultiPtr& other);
};

//---------------------------------------------------------------------------
// PSS_MultiPtr
//---------------------------------------------------------------------------
template <class T>
PSS_MultiPtr<T>::PSS_MultiPtr()
{}
//---------------------------------------------------------------------------
template <class T>
PSS_MultiPtr<T>& PSS_MultiPtr<T>::operator = (const PSS_MultiPtr<T>& other)
{
    PSS_BaseMultiPtr< T, PSS_SimpleCntType<T> >::operator = (other);
    return *this;
}
//---------------------------------------------------------------------------

// re-enable the warning disabled in the header file
#pragma warning (default: 4284)

#endif
