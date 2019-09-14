/****************************************************************************
 * ==> PSS_Drop ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a base class for drop operations                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DropH
#define PSS_DropH

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

/**
* Base class for drop operations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Drop
{
    public:
        PSS_Drop();
        virtual ~PSS_Drop();

        /**
        * Checks if the drop may be accepted
        *@return true if the drop may be accepted, otherwise false
        */
        virtual bool AcceptDrop() const = 0;

        /**
        * Drops an item
        *@param pObj - object to drop
        *@param pt - drop point in pixels
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, CPoint pt) = 0;

        /**
        * Checks if the item may be droped
        *@param pObj - object to drop
        *@param pt - drop point in pixels
        *@return true if the item may be dropped, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, CPoint pt) = 0;
};

#endif
