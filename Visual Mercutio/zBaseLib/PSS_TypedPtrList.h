/****************************************************************************
 * ==> PSS_TypedPtrList ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a typed pointer list                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TypedPtrListH
#define PSS_TypedPtrListH

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

// mfc
#include <afxtempl.h>

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
* Typed pointer list
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<class T, class U>
class AFX_EXT_CLASS PSS_TypedPtrList : public CTypedPtrList<T, U>
{
    public:
        /**
        * Constructor
        *@param blockSize - block size
        */
        inline PSS_TypedPtrList(int blockSize = 10);

        virtual inline ~PSS_TypedPtrList();

        /**
        * Destroys the pointer list content
        */
        virtual void Destroy()
        {
            POSITION pPos = GetHeadPosition();

            while (pPos)
            {
                U pNode = GetNext(pPos);
                delete pNode;
            }

            RemoveAll();
        }
};

//---------------------------------------------------------------------------
// PSS_TypedPtrList
//---------------------------------------------------------------------------
template<class T, class U>
PSS_TypedPtrList<T, U>::PSS_TypedPtrList(int blockSize) :
    CTypedPtrList<T, U>(blockSize)
{}
//---------------------------------------------------------------------------
template<class T, class U>
PSS_TypedPtrList<T, U>::~PSS_TypedPtrList()
{
    PSS_TypedPtrList::Destroy();
}
//---------------------------------------------------------------------------

#endif
