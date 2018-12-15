// ZBModelSet.h: interface for the ZBModelSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBMODELSET_H__24F292B5_AB9D_467B_95F4_D08B6C192958__INCLUDED_)
#define AFX_ZBMODELSET_H__24F292B5_AB9D_467B_95F4_D08B6C192958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ProcGraphModelMdl.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBModelSet : public CObject
{
    DECLARE_SERIAL( ZBModelSet )

public:

    ZBModelSet();
    virtual ~ZBModelSet();

    size_t                    GetModelCount    () const;

    ZDProcessGraphModelMdl*    GetModelAt        ( size_t Index );
    ZDProcessGraphModelMdl*    FindModel        ( const CString Name );

    int                        FindModelIndex    ( ZDProcessGraphModelMdl* pModel );

    bool                    AddModel        ( ZDProcessGraphModelMdl* pModel );
    bool                    RemoveModel        ( ZDProcessGraphModelMdl* pModel );
    bool                    RemoveModelAt    ( size_t Index );

    void                    RemoveAllModel    ();
    void                    DeleteAllModel    ();

    ZBModelSet*                Clone            ();

    // Serializes the unit manager
    virtual void Serialize( CArchive& ar );

private:

    CObArray m_Set;
};

inline size_t ZBModelSet::GetModelCount() const
{
    return (size_t)m_Set.GetSize();
}

#endif // !defined(AFX_ZBMODELSET_H__24F292B5_AB9D_467B_95F4_D08B6C192958__INCLUDED_)