// SortableObArray.h
/////////////////////////////////////////////////////////////////////

#if !defined(SORTABLEOBARRAY_H_INCLUDED)
#define SORTABLEOBARRAY_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#ifdef _ZWINUTIL32EXPORT
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


class AFX_EXT_CLASS CSortableObArray : public CObArray
{
public:
    void Sort(int(*CompareFunc)(CObject* pFirst, CObject* pSecond));
    void Sort(int iStartPos, int iElements, int(*CompareFunc)(CObject* pFirst, CObject* pSecond));
};


template< class TYPE >
class AFX_EXT_CLASS CTypedSortableObArray : public CSortableObArray
{
public:
    // Accessing elements
    TYPE GetAt(int nIndex) const
    { return (TYPE)CSortableObArray::GetAt(nIndex); }
    TYPE& ElementAt(int nIndex)
    { return (TYPE&)CSortableObArray::ElementAt(nIndex); }
    void SetAt(int nIndex, TYPE ptr)
    { CSortableObArray::SetAt(nIndex, ptr); }
    
    // Potentially growing the array
    void SetAtGrow(int nIndex, TYPE newElement)
    { CSortableObArray::SetAtGrow(nIndex, newElement); }
    int Add(TYPE newElement)
    { return CSortableObArray::Add(newElement); }
    int Append(const CTypedPtrArray< CSortableObArray, TYPE >& src)
    { return CSortableObArray::Append(src); }
    void Copy(const CTypedPtrArray< CSortableObArray, TYPE >& src)
    { CSortableObArray::Copy(src); }
    
    // Operations that move elements around
    void InsertAt(int nIndex, TYPE newElement, int nCount = 1)
    { CSortableObArray::InsertAt(nIndex, newElement, nCount); }
    void InsertAt(int nStartIndex, CTypedSortableObArray< TYPE >* pNewArray)
    { CSortableObArray::InsertAt(nStartIndex, pNewArray); }
    
    // overloaded operator helpers
    TYPE operator[](int nIndex) const
    { return (TYPE)CSortableObArray::operator[](nIndex); }
    TYPE& operator[](int nIndex)
    { return (TYPE&)CSortableObArray::operator[](nIndex); }
    
    void Sort( int(*CompareFunc)(TYPE pFirstObj, TYPE pSecondObj) )
    { CSortableObArray::Sort((int(*)(CObject*,CObject*))CompareFunc); }
    void Sort( int iStartPos, int iElements, int(*CompareFunc)(TYPE pFirstObj, TYPE pSecondObj) )
    { CSortableObArray::Sort(iStartPos, iElements, (int(*)(CObject*,CObject*))CompareFunc); }
};


#endif // !defined(SORTABLEOBARRAY_H_INCLUDED)
