#if !defined(AFX_SMARTPOINTER_H__714480E6_B09B_11D2_A8B1_0000E8D38C7A__INCLUDED_)
#define AFX_SMARTPOINTER_H__714480E6_B09B_11D2_A8B1_0000E8D38C7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#pragma warning(disable : 4284)


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


/////////////////////////////////////////////////////////////////////////////
// class ZSmartPtr
template<class TYPE>
class ZSmartPtr
{
public:
// Constructor:
	ZSmartPtr (TYPE *ptr = NULL)
		: m_ptr (ptr) {}
	ZSmartPtr (const ZSmartPtr& T)
		: m_ptr (T.m_ptr) { }
public:
// Operations:
	// Access to pointer to actual data:
	// Non-const access
	TYPE* const			GetPtr() 			{ return m_ptr; }
	TYPE* const			operator->()		{ return m_ptr; }
	TYPE& 				operator*() 		{ return *m_ptr;}

	// Const access
	const TYPE*	const	GetPtr()	const 	{ return m_ptr;	}
	const TYPE*	const	operator->()const	{ return m_ptr;	}
	const TYPE& 		operator*()	const	{ return *m_ptr;}

	BOOL IsNull()					const   { return (m_ptr == NULL); }
	void ThrowMemoryExceptionIfNull() const { if (IsNull()) AfxThrowMemoryException(); }

	// Swap between two pointers (for sorting etc)
	void	Swap(ZSmartPtr& T)
		{
		TYPE*	ptr = T.m_ptr;
		T.m_ptr		= m_ptr;
		m_ptr		= ptr;
		}
	void operator=(const ZSmartPtr& T)
		{ m_ptr  = T.m_ptr; }

protected:
// Members:
	TYPE*	m_ptr;
};
//*****************************************************************
template<class TYPE>
inline BOOL IsNull(const ZSmartPtr<TYPE>& p)
{
	return (p.GetPtr() == NULL);
}
//*****************************************************************
template<class TYPE>
inline void ThrowMemoryExceptionIfNull(const ZSmartPtr<TYPE>& p)
{
	if (IsNull(p))
		AfxThrowMemoryException();
}
//*****************************************************************
template<class TYPE>
inline void ThrowMemoryExceptionIfNull(TYPE *p)
{
	if (p == NULL)
		AfxThrowMemoryException();
}
//*****************************************************************
/////////////////////////////////////////////////////////////////////////////
// Class ZSafeSmartPtr - knows to delete pointer at destructor
// WARNING! Copy operator is weird - it changes right-hand
// operand (makes it NULL actually.
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class ZSafeSmartPtr : public ZSmartPtr<TYPE>
{
public:
// Constructor:
	ZSafeSmartPtr (TYPE *ptr = NULL)
		: ZSmartPtr<TYPE> (ptr) {}
// Copy Constructor:
	ZSafeSmartPtr(ZSafeSmartPtr& T)
		: ZSmartPtr<TYPE> (T) 
		{
		if (&T != this)
			T.m_ptr = NULL;
		}
// Destructor:
	~ZSafeSmartPtr() { delete m_ptr; }
public:
// Operations:
	void operator=(TYPE* new_ptr)
		{
		if (new_ptr != m_ptr)
			{
			delete m_ptr;
			m_ptr = new_ptr;
			}
		}
	void operator=(ZSafeSmartPtr& T)
		{
		if (&T != this)
			{
			delete m_ptr;
			m_ptr = T.m_ptr;
			T.m_ptr = NULL;
			}
		}
};
/////////////////////////////////////////////////////////////////////////////
// Class ZSafeArray - array of objects
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class ZSafeArray : public ZSmartPtr<TYPE>
{
public:
// Constructors:
	ZSafeArray (TYPE *ptr = NULL)
		: ZSmartPtr<TYPE> (ptr) {}
	ZSafeArray (int nCount)
		: ZSmartPtr<TYPE> (new TYPE [nCount]) {}

// Destructor:
	~ZSafeArray() { delete[] m_ptr; }

public:
// Operations:
	TYPE& 			operator[] (int i) 		 { return m_ptr[i]; }
	const TYPE& 	operator[] (int i) const { return m_ptr[i]; }
private:
	// No copy semantics
	void operator=(const ZSafeArray& T);
	ZSafeArray(const ZSafeArray& T);
};
/////////////////////////////////////////////////////////////////////////////
// class ZDuplSmartPtr
// Class for holding safe pointer to clonable object
// ###########################################################
// ##	Object must have copy constructor					##
// ##	Copiing implemented by creating new object			##
// ##	via copy constructor.								##
// ##	So class ZDuplSmartPtr has copy constructor and		##
// ##	copy operator.										##
// ##   Class CANNOT handle inheritance trees!				##
// ##   Use ZCloneSmartPtr for this.						##
// ###########################################################
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class ZDuplSmartPtr : public ZSafeSmartPtr<TYPE>
{
public:
// Constructors:
	ZDuplSmartPtr (TYPE *ptr = NULL) 
		: ZSafeSmartPtr<TYPE> (ptr) {}
// Copy constructor
	ZDuplSmartPtr (const ZDuplSmartPtr& T) 
		: ZSafeSmartPtr<TYPE> (NULL) 
		{
		if(T.m_ptr != NULL)
			m_ptr = new TYPE(*(T.m_ptr));
		}
public:
	// Copy operators
	ZDuplSmartPtr& operator=(const ZDuplSmartPtr& T)
		{
		if (this != &T)
			{
			delete m_ptr;
			if (T.m_ptr == NULL)
				m_ptr = NULL;
			else
				m_ptr = new TYPE(*(T.m_ptr));
			}
		return *this;
		}
	void operator=(TYPE* new_ptr)
		{
		if (new_ptr != m_ptr)
			{
			delete m_ptr;
			m_ptr = new_ptr;
			}
		}
};
///////////////////////////////////////////////////////////////////
// class ZCloneSmartPtr
// Class for holding safe pointer to clonable object
// ###########################################################
// ##	Object must have Clone function						##
// ##	Copiing implemented by creating new object			##
// ##	via clone function. 								##
// ##	So class ZCloneSmartPtr has copy constructor and	##
// ##	copy operator.										##
// ##	Differs from class ZDuplSmartPtr that it can hold 	##
// ##   pointer to inheritance tree members					##
// ###########################################################
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class ZCloneSmartPtr : public ZSafeSmartPtr<TYPE>
{
public:
// Constructors:
	ZCloneSmartPtr (TYPE *ptr = NULL) 
		: ZSafeSmartPtr<TYPE> (ptr) {}
// Copy constructor
	ZCloneSmartPtr (const ZCloneSmartPtr& T) 
		: ZSafeSmartPtr<TYPE> (NULL) 
		{
		if (T.m_ptr != NULL)
			m_ptr = T.m_ptr->Clone();
		}
public:
	// Copy operator
	ZCloneSmartPtr& operator=(const ZCloneSmartPtr& T)
		{
		if (this != &T)
			{
			delete m_ptr;
			if (T.m_ptr == NULL)
				m_ptr = NULL;
			else
				m_ptr = T.m_ptr->Clone();
			}
		return *this;
		}
	void operator=(TYPE* new_ptr)
		{
		if (new_ptr != m_ptr)
			{
			delete m_ptr;
			m_ptr = new_ptr;
			}
		}
};
/////////////////////////////////////////////////////////////////////////////
// Recommended (but NOT required) base for clonabe classes.
template<class TYPE>
TYPE* CloneMe(const TYPE& p)
{
	return new TYPE(p);
}
/////////////////////////////////////////////////////////////////////////////
class ZClonable 
{
	public:
		virtual ~ZClonable() {}
		virtual ZClonable* Clone() const = 0;
		/*	This must be in every son!: { return CloneMe(this); } */
};
/////////////////////////////////////////////////////////////////////////////
// Alternative MACRO (Yack!) for clonability
#define DECLARE_CLONABLE(TYPE) public: virtual TYPE* Clone() const { return (TYPE *)::CloneMe(*this); }
/////////////////////////////////////////////////////////////////////////////
// class ZBaseMultiRefSmartPtr
// This is really smart pointer.
// It implements garbage collection by usage counting.
// Template parameter COUNT means class int-like for
// reference counting. It may be int, like in 
// ZMultiRefSmartPtr, or some optimized for multiply
// allocations class.
///////////////////////////////////////////////////////////////////
template<class TYPE,class COUNT>
class ZBaseMultiRefSmartPtr : public ZSmartPtr<TYPE>
{
public:
	// Copy Constructor:
	ZBaseMultiRefSmartPtr(const ZBaseMultiRefSmartPtr& T)
		{ Copy(T);}
	// Default constructor:
	ZBaseMultiRefSmartPtr(TYPE* ptr = NULL)
		{ Construct (ptr); }
	// Destructor:
	~ZBaseMultiRefSmartPtr() { Delete(); }

	ZBaseMultiRefSmartPtr& operator=(const ZBaseMultiRefSmartPtr& T)
		{
		if (this != &T)	{ Delete();	Copy(T); }
		return *this;
		}
	void operator=(TYPE* ptr)
		{
		if (m_ptr == ptr) return;
		Delete(); Construct (ptr);
		}
	// Swap between two pointers (for sorting etc)
	void	Swap(ZBaseMultiRefSmartPtr& T)
		{
		ZSmartPtr<TYPE>::Swap(T);
		COUNT* pRefCount = T.m_pRefCount;
		T.m_pRefCount	 = m_pRefCount;
		m_pRefCount		 = pRefCount;
		}
	bool operator==(const 	ZBaseMultiRefSmartPtr& t) const
		{ return (m_ptr == t.m_ptr); }
	bool operator!=(const 	ZBaseMultiRefSmartPtr& t) const
		{ return (m_ptr != t.m_ptr); }

	bool IsLastOne ()	const { return (m_pRefCount && (*m_pRefCount == 1)); }
	bool IsShared()		const { return (m_pRefCount && (*m_pRefCount > 1)); }
protected:
// Implementation
	void Copy(const ZBaseMultiRefSmartPtr& T)
		{
		m_ptr		= T.m_ptr;
		m_pRefCount = T.m_pRefCount;
		if (m_pRefCount != NULL)
			{
			ASSERT(m_ptr != NULL);
			++*m_pRefCount;
			}
		else
			{ ASSERT(m_ptr == NULL); }
		return;
		}
	void Construct(TYPE* ptr)
		{
		m_ptr = ptr;
		m_pRefCount = NULL;
		if (m_ptr != NULL)
			{
			m_pRefCount = new COUNT(1);
			::ThrowMemoryExceptionIfNull(m_pRefCount);
			}
		return;
		}
	void Delete()
		{
		if (m_pRefCount ==NULL)
			{ ASSERT(m_ptr == NULL); return; }
		ASSERT(m_ptr != NULL);
		if(--*m_pRefCount==0)
			{
			delete m_pRefCount;	m_pRefCount = NULL;
			delete m_ptr;		m_ptr		= NULL;
			}
		return;
		}
protected:
// Data members:
	COUNT* m_pRefCount; // reference counter
};
///////////////////////////////////////////////////////////////////
// class ZMultiRefSmartPtr - derived from ZBaseMultiRefSmartPtr
// with int as simple counter.
template<class TYPE>
class ZMultiRefSmartPtr : public ZBaseMultiRefSmartPtr<TYPE,int>
{
public:
	// Constructors:
	ZMultiRefSmartPtr(const ZMultiRefSmartPtr& T)
		: ZBaseMultiRefSmartPtr<TYPE,int>(T)	{}
	ZMultiRefSmartPtr(TYPE* ptr = NULL)
		: ZBaseMultiRefSmartPtr<TYPE,int>(ptr){}
	~ZMultiRefSmartPtr() {}
	// Copy operators:
	ZMultiRefSmartPtr& operator=(const ZMultiRefSmartPtr& T)
		{
		ZBaseMultiRefSmartPtr<TYPE,int>::operator=(T);
		return *this;
		}
	void operator=(TYPE* ptr)
		{
		ZBaseMultiRefSmartPtr<TYPE,int>::operator=(ptr);
		}
};
///////////////////////////////////////////////////////////////////
// class ZCounterMultiRefPtr
// Variant of reference counting pointer.
// This is one most effective but it has significant limitation:
// The class it points to (or the root class of the hierarchy)
// must implement reference counting itself. The simplest way to
// do this is to derive it from ZReferenceCounterBase. 
// The catch is that you cannot have it in multiple derivation
// several times, and, the worst, you must be the author of this 
// class.
///////////////////////////////////////////////////////////////////
class ZReferenceCounterBase
{
public:
	// Construction:
	ZReferenceCounterBase() : m_Counter(1) {}
	// Interface for ZCounterMultiRefPtr
	// Adds a reference to the object
	void	AddReference() { m_Counter++; }
	// Removes a reference to the object and returns new count.
	int		RemoveReference() { return --m_Counter; }
	int		GetReferenceCount() const { return m_Counter; }
private:
	int	m_Counter;
};


template<class TYPE>
class ZCounterMultiRefPtr : public ZSmartPtr<TYPE>
{
public:
	// Copy Constructor:
	ZCounterMultiRefPtr(const ZCounterMultiRefPtr& T)
		{ Copy(T);}
	// Default constructor:
	ZCounterMultiRefPtr(TYPE* ptr = NULL)
		{ Construct (ptr); }
	// Destructor:
	~ZCounterMultiRefPtr() { Delete(); }

	ZCounterMultiRefPtr& operator=(const ZCounterMultiRefPtr& T)
		{
		if (this != &T)	{ Delete();	Copy(T); }
		return *this;
		}
	void operator=(TYPE* ptr)
		{
		if (m_ptr == ptr) return;
		Delete(); Construct (ptr);
		}
	// Swap between two pointers (for sorting etc)
	void	Swap(ZCounterMultiRefPtr& T)
		{ ZSmartPtr<TYPE>::Swap(T); }
	bool operator==(const 	ZCounterMultiRefPtr& t) const
		{ return (m_ptr == t.m_ptr); }
	bool operator!=(const 	ZCounterMultiRefPtr& t) const
		{ return (m_ptr != t.m_ptr); }

	bool IsLastOne ()	const { return (m_ptr && (m_ptr->GetReferenceCount() == 1)); }
	bool IsShared()		const { return (m_ptr && (m_ptr->GetReferenceCount() > 1)); }
protected:
// Implementation
	void Copy(const ZCounterMultiRefPtr& T)
		{
		m_ptr		= T.m_ptr;
		if (m_ptr != NULL)
			m_ptr->AddReference();
		return;
		}
	void Construct(TYPE* ptr)
		{
		m_ptr = ptr;
		return;
		}
	void Delete()
		{
		if (m_ptr == NULL)
			return;
		if(m_ptr->RemoveReference() == 0)
			{
			delete	m_ptr;		
			m_ptr	= NULL;
			}
		return;
		}
};

///////////////////////////////////////////////////////////////////
//#pragma warning(default : 4284)
///////////////////////////////////////////////////////////////////


// Archiving functions

///////////////////////////////////////////////////////////////////
template<class POINTER_TYPE>
inline void StoreSmartPtr (CArchive& ar, const POINTER_TYPE& Pointer)
{
	ar << Pointer.GetPtr();
}

///////////////////////////////////////////////////////////////////
template<class POINTER_TYPE, class DATA_TYPE>
inline void LoadSmartPtr (CArchive& ar, POINTER_TYPE& Pointer, DATA_TYPE* p)
{
	Pointer = NULL;
	p		= NULL;
	ar >> p;
	Pointer = p;
}






///////////////////////////////////////////////////////////////////
// Array of smart pointers without GOOD copy operations.
//--------------------------------------------------------
template<class TYPE>
class ZRefArgArray : public CArray<TYPE, TYPE&>
{
public:
	const TYPE& GetAt(int i) const 
		{ return const_cast<ZRefArgArray*>(this)->ElementAt(i); }
	TYPE& operator[](int i)
		{ return ElementAt(i); }
	const TYPE& operator[](int i) const 
		{ return GetAt(i); }
};
//--------------------------------------------------------
template<class POINTER_TYPE, class TYPE>
class ZGenSmartPtrArray : public ZRefArgArray<POINTER_TYPE>
{
typedef ZRefArgArray<POINTER_TYPE> PARENT;
public:
	// Constructor
	ZGenSmartPtrArray() {}
	// Destructor
	~ZGenSmartPtrArray() {}
	// Add elements
	int Add(TYPE* ptr)
		{ return PARENT::Add(POINTER_TYPE(ptr)); }
	void SetAtGrow(int i, TYPE* ptr)
		{ PARENT::SetAtGrow(i,POINTER_TYPE(ptr)); }
	void SetAt(int i, TYPE* ptr)
		{ PARENT::SetAt(i,POINTER_TYPE(ptr)); }
	void InsertAt(int i, TYPE* ptr)
		{ PARENT::InsertAt(i,POINTER_TYPE(ptr)); }
	void Add(const ZGenSmartPtrArray& A)
		{ CopyArray(A);	}
	// Swapping (for sorting etc.)
	void Swap(int i, int j)
		{
		ASSERT(i >= 0 && i < GetSize());
		ASSERT(j >= 0 && j < GetSize());
		ASSERT(i != j);
		ElementAt(i).Swap(ElementAt(j));
		}

	ZGenSmartPtrArray(const ZGenSmartPtrArray& A)
		{ CopyArray(A);	}
	ZGenSmartPtrArray& operator=(const ZGenSmartPtrArray& A)
		{ RemoveAll(); CopyArray(A); return *this; }
	ZGenSmartPtrArray& operator+=(const ZGenSmartPtrArray& A)
		{ CopyArray(A);	return *this; }
private:
	void CopyArray(const ZGenSmartPtrArray& A)
		{
		const int n = A.GetSize();
		const int s = GetSize();
		SetSize(s + n);
		for (INDEX i = 0; i < n; i++)
			ElementAt(i + s) = 
				const_cast<ZGenSmartPtrArray&>(A).ElementAt(i);
		}
};
//--------------------------------------------------------
// Array of smart pointers with GOOD copy operations.
template<class POINTER_TYPE, class TYPE>
class ZCopySmartPtrArray : public ZGenSmartPtrArray<POINTER_TYPE,TYPE>
{
public:
	int Add(POINTER_TYPE& e)
		{ return PARENT::Add(e); }
	void SetAtGrow(int i, POINTER_TYPE& e)
		{ PARENT::SetAtGrow(i,e); }
	void SetAt(int i, POINTER_TYPE& e)
		{ PARENT::SetAt(i,e); }
	void InsertAt(int i, POINTER_TYPE& e)
		{ PARENT::InsertAt(i,e); }
	int Add(TYPE* ptr)
		{ return PARENT::Add(POINTER_TYPE(ptr)); }
	void SetAtGrow(int i, TYPE* ptr)
		{ PARENT::SetAtGrow(i,POINTER_TYPE(ptr)); }
	void SetAt(int i, TYPE* ptr)
		{ PARENT::SetAt(i,POINTER_TYPE(ptr)); }
	void InsertAt(int i, TYPE* ptr)
		{ PARENT::InsertAt(i,POINTER_TYPE(ptr)); }
};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class ZSmartPtrArray : 
	public ZGenSmartPtrArray<ZSmartPtr<TYPE> , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class ZSafeSmartPtrArray : 
	public ZGenSmartPtrArray<ZSafeSmartPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class ZDuplSmartPtrArray : 
	public ZGenSmartPtrArray<ZDuplSmartPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class ZCloneSmartPtrArray : 
	public ZGenSmartPtrArray<ZCloneSmartPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE,class COUNT>
class ZBaseMultiRefSmartPtrArray : 
	public ZCopySmartPtrArray<ZBaseMultiRefSmartPtr<TYPE,COUNT>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class ZMultiRefSmartPtrArray : 
	public ZCopySmartPtrArray<ZMultiRefSmartPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class ZCounterMultiRefPtrArray : 
	public ZCopySmartPtrArray<ZCounterMultiRefPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class ARRAY>
inline int DeepCopyArray (ARRAY& a1, const ARRAY& a2)
{
	const int imax = a2.GetSize();
	a1.RemoveAll();
	if(imax > 0)
		{
		a1.SetSize(imax);
		for (INDEX i = 0; i < imax; i++)
			a1[i] = a2[i]->Clone();
		}
	return imax;
}
///////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////
template<class ARRAY_TYPE, class TYPE>
void SerializeArray(ARRAY_TYPE& Arr, TYPE* /*null*/, CArchive& ar, int VERSION)
{
	SerializeVersion(ar,VERSION, TRUE); // Throws exception if wrong version
	long n;
	if (ar.IsStoring())
		{
		n = Arr.GetSize();
		ar << n;
		for (INDEX i = 0 ; i < n; i++)
			StoreSmartPtr(ar, Arr.ElementAt(i));
		}	
	else
		{
		ar >> n;
		Arr.RemoveAll();
		Arr.SetSize(n);
		for (INDEX i = 0; i < n; i++)
			{
			LoadSmartPtr(ar, Arr.ElementAt(i), (TYPE*)NULL);
			if (Arr.ElementAt(i).IsNull())
				{ 
				ASSERT(0); 
				AfxThrowArchiveException(CArchiveException::badSchema,ar.m_strFileName);
				}
			}
		}
}
///////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
template<class ARRAY_TYPE, class COMPARE_TYPE>
class ZSmartPrtComparer
{
public:
	ZSmartPrtComparer() {}

	int	Compare(ARRAY_TYPE& arr, int i, int j) const
		{
		return m_cRealComparer.Compare(*(arr[i]),*(arr[j]));
		}
private:
	COMPARE_TYPE	m_cRealComparer;
};
/////////////////////////////////////////////////////////////////////////////
// The function for sorting the array
template<class ARRAY_TYPE, class COMPARE_TYPE>
void SortSmartPrtArray(ARRAY_TYPE& Arr, COMPARE_TYPE& Comparer)
{
	if (Arr.GetSize() > 1)
		{
		ZSmartPrtComparer<ARRAY_TYPE,COMPARE_TYPE> comp;
		CWizArrSort<ARRAY_TYPE,ZSmartPrtComparer<ARRAY_TYPE,COMPARE_TYPE> > Sorter(Arr, comp);
		Sorter.Sort();
		}
}
/////////////////////////////////////////////////////////////////////////////



inline int SerializeVersion(CArchive& ar, const int VERSION, BOOL bThrowEx = TRUE)
{
	WORD version = VERSION;
	if (ar.IsStoring())
		{
		ar << version;
		return VERSION;
		}
	else
		{
		ar >> version;
		if (bThrowEx && VERSION != version)
			{
			ASSERT(0);
			AfxThrowArchiveException(CArchiveException::badSchema,ar.m_strFileName);
			}
		return version;
		}
}



/////////////////////////////////////////////////////////////////////////////
// Warning!!! class TYPE must have default constructor !!!
// class ZMultiPtr
template <class TYPE, class CNT_TYPE>
class ZBaseMultiPtr
{
public:
// Constructors:
	ZBaseMultiPtr ()  : m_pObject (new CNT_TYPE) {}
	ZBaseMultiPtr (const ZBaseMultiPtr& T) : m_pObject (NULL)
		{ Init (T); }
// Destructor:
	~ZBaseMultiPtr () { CleanUp(); }
public:
	ZBaseMultiPtr& operator=(const ZBaseMultiPtr& T);
//		{ CleanUp(); Init (T); return *this; }
// Operations:
	TYPE*		GetPtr() 	  { return &(m_pObject->Data); }
	TYPE* 		operator->() 	  { return &(m_pObject->Data); }
	const TYPE*	GetPtr() const 	  { return &(m_pObject->Data); }
	const TYPE* 	operator->()const { return &(m_pObject->Data); }

	TYPE& 		operator*() 	  { return m_pObject->Data; }
	const TYPE& 	operator*()const  { return m_pObject->Data; }
protected:
// Implementation:
	void Init(const ZBaseMultiPtr& T);
	void CleanUp();
protected:
// Members:
	CNT_TYPE*	m_pObject;
protected:
	// Constructor for derived classes
	ZBaseMultiPtr (CNT_TYPE*	m_pObject) 
		: m_pObject (m_pObject) 
			{}
};

/////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class SIMPLE_CNT_TYPE
{
public:
	TYPE	Data;
	int	Counter;
	// Constructor:

	SIMPLE_CNT_TYPE() : Counter(1) {}
	~SIMPLE_CNT_TYPE() { Counter = -1; }
};
/////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class ZMultiPtr : public ZBaseMultiPtr<TYPE, SIMPLE_CNT_TYPE<TYPE> >
{
public: // Copy constructor is compiler-generated
	ZMultiPtr() {}
	ZMultiPtr& operator=(const ZMultiPtr& T)
		{ ZBaseMultiPtr<TYPE, SIMPLE_CNT_TYPE<TYPE> >::operator=(T); return *this; }
};

/////////////////////////////////////////////////////////////////////////////
template <class TYPE,class CNT_TYPE>
ZBaseMultiPtr<TYPE,CNT_TYPE>& ZBaseMultiPtr<TYPE,CNT_TYPE>::operator=(const ZBaseMultiPtr& T)
{ 
	CleanUp(); 
	Init (T); 
	return *this; 
}

template <class TYPE,class CNT_TYPE>
inline void ZBaseMultiPtr<TYPE,CNT_TYPE>::Init(const ZBaseMultiPtr& T)
{
	if (T.m_pObject == NULL)
		m_pObject = new CNT_TYPE;
	else
		{
		m_pObject = T.m_pObject;
		T.m_pObject->Counter++;
		}
}

template <class TYPE,class CNT_TYPE>
inline void ZBaseMultiPtr<TYPE,CNT_TYPE>::CleanUp()
{
	if (m_pObject != NULL)
		{
		if (m_pObject->Counter <= 1)
			{
			delete m_pObject;
			m_pObject = NULL;
			}
		else
			m_pObject->Counter--;
		}
}
/////////////////////////////////////////////////////////////////////////////



#endif 