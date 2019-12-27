/****************************************************************************
 * ==> PSS_ModelSet --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a model set                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelSetH
#define PSS_ModelSetH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_ModelSet
    #define PSS_ModelSet ZBModelSet
#endif

// processsoft
#include "PSS_ProcessGraphModelMdl.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Model set
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelSet : public CObject
{
    DECLARE_SERIAL(PSS_ModelSet)

    public:
        PSS_ModelSet();
        virtual ~PSS_ModelSet();

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_ModelSet* Clone();

        /**
        * Gets the model count
        *@return the model count
        */
        virtual inline std::size_t GetModelCount() const;

        /**
        * Gets the model at index
        *@param index - the index
        *@return the model at index, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* GetModelAt(std::size_t index);

        /**
        * Finds a model
        *@param name - the model name to find
        *@return the model, NULL if not found or on error
        */
        virtual PSS_ProcessGraphModelMdl* FindModel(const CString& name);

        /**
        * Finds a model index
        *@param pModel - the model to find
        *@return the model index, -1 if not found or on error
        */
        virtual int FindModelIndex(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Adds a model
        *@param pModel - the model to add
        *@return true on success, otherwise false
        */
        virtual bool AddModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Removes a model
        *@param pModel - the model to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Removes a model at index
        *@param index - the model index to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveModelAt(std::size_t index);

        /**
        * Removes all the models (but don't delete them from memory)
        */
        virtual void RemoveAllModel();

        /**
        * Deletes all the models
        */
        virtual void DeleteAllModel();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CObArray m_Set;
};

//---------------------------------------------------------------------------
// PSS_ModelSet
//---------------------------------------------------------------------------
std::size_t PSS_ModelSet::GetModelCount() const
{
    return std::size_t(m_Set.GetSize());
}
//---------------------------------------------------------------------------

#endif
