// ZBWorkspaceFileEntity.h: interface for the ZBWorkspaceFileEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWORKSPACEFILEENTITY_H__D0AD894D_7827_44C4_90DC_EE82005CFD7B__INCLUDED_)
#define AFX_ZBWORKSPACEFILEENTITY_H__D0AD894D_7827_44C4_90DC_EE82005CFD7B__INCLUDED_

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



#include "ZBWorkspaceEntity.h"
// File
#include "PSS_File.h"


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



class AFX_EXT_CLASS ZBWorkspaceFileEntity : public ZBWorkspaceEntity  
{
    DECLARE_SERIAL(ZBWorkspaceFileEntity)
public:
    ZBWorkspaceFileEntity(const CString Name = "", ZBWorkspaceEntity* pParent = NULL);
    virtual ~ZBWorkspaceFileEntity();

    virtual bool HasFilename() const
    {
        return (const_cast<PSS_File&>(m_File).GetCompleteFileName().IsEmpty()) ? false : true;
    };

    virtual CString GetFilename() const
    {
        return const_cast<PSS_File&>(m_File).GetCompleteFileName();
    };
    virtual CString GetFileTitle() const
    {
        return const_cast<PSS_File&>(m_File).GetFileName();
    };
    virtual CString GetFilePath() const
    {
        return const_cast<PSS_File&>(m_File).GetFilePath();
    };
    virtual CString GetFileExt() const
    {
        return const_cast<PSS_File&>(m_File).GetFileExt();
    };
    virtual void SetFilename( const CString value )
    {
        m_File.SetCompleteFileName( value );
    };
    virtual HICON GetFilenameIcon() const;

    virtual bool OpenFile();

    virtual bool DisplayProperties();


    // Serialization mechanism
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    PSS_File m_File;
};

#endif // !defined(AFX_ZBWORKSPACEFILEENTITY_H__D0AD894D_7827_44C4_90DC_EE82005CFD7B__INCLUDED_)
