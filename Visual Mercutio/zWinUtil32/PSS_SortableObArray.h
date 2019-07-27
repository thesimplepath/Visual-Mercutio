/****************************************************************************
 * ==> PSS_SortableObArray -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a sortable (and typed sortable) object array      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SortableObArrayH
#define PSS_SortableObArrayH

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

#ifdef _ZWINUTIL32EXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Sortable object array
*@author Dominique Aigroz, Jean-Milost Reymond
*@note This class is using the Shell Sort. Basically it does a bunch of smaller insertion sorts than insertion sorts
*      the whole thing. Insertion sorting is much faster on a list that is already mostly sorted
*@note Because GetSize() is called to retrieve the number of elements, you should call SetSize() with the number of
*      valid elements. An alternative is shown in the implemented sort function
*/
class AFX_EXT_CLASS PSS_SortableObArray : public CObArray
{
    public:
        /**
        * Sorts the objects
        *@param pFirst - first object to compare
        *@param pSecond - second object to compare with
        *@note CompareFunc is expected to return a positive integer if pFirstObj follows the pSecondObj
        *      one (is greater than)
        */
        void Sort(int(*CompareFunc)(CObject* pFirst, CObject* pSecond));

        /**
        * Sorts the objects since a start position
        *@param startPos - sort start position
        *@param elements - number of elements to sort
        *@param pFirst - first object to compare
        *@param pSecond - second object to compare with
        *@note CompareFunc is expected to return a positive integer if pFirstObj follows the pSecondObj
        *      one (is greater than)
        */
        void Sort(int startPos, int elements, int(*CompareFunc)(CObject* pFirst, CObject* pSecond));
};

/**
* Typed sortable object array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T>
class AFX_EXT_CLASS PSS_TypedSortableObArray : public PSS_SortableObArray
{
    public:
        /**
        * Assignment in array operator
        *@param index - index
        */
        T operator[](int index) const;

        /**
        * Assignment in array operator
        *@param index - index
        */
        T& operator[](int index);

        /**
        * Gets an object at index
        *@param index - index
        *@return object, NULL if not found or on error
        */
        T GetAt(int index) const;

        /**
        * Gets an element at index
        *@param index - index
        *@return element, empty element if not found or on error
        */
        T& ElementAt(int index);

        /**
        * Sets an object at index
        *@param pObj - object to set
        */
        void SetAt(int index, T pObj);

        /**
        * Inserts an object at index
        *@param pPtr - object pointer to set
        */
        void SetAtGrow(int index, T newElement);

        /**
        * Adds an object
        *@param pObj - new object to add
        */
        int Add(T pObj);

        /**
        * Appends objects
        *@param src - source object array to append
        */
        int Append(const CTypedPtrArray<PSS_SortableObArray, T>& src);

        /**
        * Copies objects
        *@param src - source object array to copy
        */
        void Copy(const CTypedPtrArray<PSS_SortableObArray, T>& src);

        /**
        * Inserts an object at index
        *@param index - index
        *@param pObj - new object to insert
        *@param count - number of times the object should be inserted
        */
        void InsertAt(int index, T pObj, int count = 1);

        /**
        * Inserts objects at index
        *@param startIndex - start index
        *@param pNewArray - array containing new objects to insert
        */
        void InsertAt(int startIndex, PSS_TypedSortableObArray<T>* pNewArray);

        /**
        * Sorts the objects
        *@param pFirst - first object to compare
        *@param pSecond - second object to compare with
        *@note CompareFunc is expected to return a positive integer if pFirstObj follows the pSecondObj
        *      one (is greater than)
        */
        void Sort(int(*CompareFunc)(T pFirstObj, T pSecondObj));

        /**
        * Sorts the objects since a start position
        *@param startPos - sort start position
        *@param elements - number of elements to sort
        *@param pFirst - first object to compare
        *@param pSecond - second object to compare with
        *@note CompareFunc is expected to return a positive integer if pFirstObj follows the pSecondObj
        *      one (is greater than)
        */
        void Sort(int startPos, int elements, int(*CompareFunc)(T pFirstObj, T pSecondObj));
};

//---------------------------------------------------------------------------
// PSS_TypedSortableObArray
//---------------------------------------------------------------------------
template<class T>
T PSS_TypedSortableObArray<T>::operator[](int index) const
{
    return T(PSS_SortableObArray::operator[](index));
}
//---------------------------------------------------------------------------
template<class T>
T& PSS_TypedSortableObArray<T>::operator[](int index)
{
    return (TYPE&)CSortableObArray::operator[](index);
}
//---------------------------------------------------------------------------
template<class T>
T PSS_TypedSortableObArray<T>::GetAt(int index) const
{
    return T(CSortableObArray::GetAt(nIndex));
}
//---------------------------------------------------------------------------
template<class T>
T& PSS_TypedSortableObArray<T>::ElementAt(int index)
{
    return (TYPE&)CSortableObArray::ElementAt(nIndex);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::SetAt(int index, T pObj)
{
    CSortableObArray::SetAt(index, pObj);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::SetAtGrow(int index, T newElement)
{
    CSortableObArray::SetAtGrow(index, newElement);
}
//---------------------------------------------------------------------------
template<class T>
int PSS_TypedSortableObArray<T>::Add(T pObj)
{
    return CSortableObArray::Add(pObj);
}
//---------------------------------------------------------------------------
template<class T>
int PSS_TypedSortableObArray<T>::Append(const CTypedPtrArray<PSS_SortableObArray, T>& src)
{
    return CSortableObArray::Append(src);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::Copy(const CTypedPtrArray<PSS_SortableObArray, T>& src)
{
    CSortableObArray::Copy(src);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::InsertAt(int index, T pObj, int count)
{
    CSortableObArray::InsertAt(index, pObj, count);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::InsertAt(int startIndex, PSS_TypedSortableObArray<T>* pNewArray)
{
    CSortableObArray::InsertAt(startIndex, pNewArray);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::Sort(int(*CompareFunc)(T pFirstObj, T pSecondObj))
{
    CSortableObArray::Sort((int(*)(CObject*, CObject*))CompareFunc);
}
//---------------------------------------------------------------------------
template<class T>
void PSS_TypedSortableObArray<T>::Sort(int startPos, int elements, int(*CompareFunc)(T pFirstObj, T pSecondObj))
{
    CSortableObArray::Sort(startPos, elements, (int(*)(CObject*, CObject*))CompareFunc);
}
//---------------------------------------------------------------------------

#endif
