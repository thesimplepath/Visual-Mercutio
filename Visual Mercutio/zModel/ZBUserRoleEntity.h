// ZBUserRoleEntity.h: interface for the ZBUserRoleEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUserRoleEntity_H__D0AD894D_7827_44C4_90DC_EE82005CFD7B__INCLUDED_)
#define AFX_ZBUserRoleEntity_H__D0AD894D_7827_44C4_90DC_EE82005CFD7B__INCLUDED_

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



#include "ZBUserEntity.h"


#ifdef _ZMODELEXPORT
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



class AFX_EXT_CLASS ZBUserRoleEntity : public ZBUserEntity  
{
    DECLARE_SERIAL(ZBUserRoleEntity)
public:
    ZBUserRoleEntity(const CString Name = "", const CString Description = "", ZBUserEntity* pParent = NULL);
    virtual ~ZBUserRoleEntity();

    /* Copy constructor. */
    ZBUserRoleEntity(const ZBUserRoleEntity& src);
    /* Assignment operator. */
    ZBUserRoleEntity& operator=(const ZBUserRoleEntity& src);
    /* Create a duplicate copy of this object. */
    virtual ZBUserEntity* Clone() const;

    virtual bool DisplayProperties();


    // Serialization mechanism
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
};

#endif // !defined(AFX_ZBUserRoleEntity_H__D0AD894D_7827_44C4_90DC_EE82005CFD7B__INCLUDED_)
