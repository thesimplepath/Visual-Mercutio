/****************************************************************************
 * ==> PSS_SymbolEntity ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol entity                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolEntity.h"

// processsoft
#include "PSS_Symbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_SymbolEntity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SymbolEntity
//---------------------------------------------------------------------------
PSS_SymbolEntity::PSS_SymbolEntity() :
    CObject(),
    m_pSymbol(NULL)
{}
//---------------------------------------------------------------------------
PSS_SymbolEntity::PSS_SymbolEntity( const PSS_SymbolEntity& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SymbolEntity::~PSS_SymbolEntity()
{}
//---------------------------------------------------------------------------
const PSS_SymbolEntity& PSS_SymbolEntity::operator = (const PSS_SymbolEntity& other)
{
    m_SymbolStamp = other.m_SymbolStamp;
    m_pSymbol     = static_cast<PSS_Symbol*>(other.m_pSymbol->Dup());

    m_Image.CopyImage(const_cast<SECJpeg*>(&(other.m_Image)));

    return *this;
}
//---------------------------------------------------------------------------
PSS_SymbolEntity* PSS_SymbolEntity::Clone()
{
    return new PSS_SymbolEntity(*this);
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEntity::ReadFromFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    // create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = NULL;
    loadArchive.m_bForceFlat = FALSE;

    TRY
    {
        Serialize(loadArchive);
    }
    CATCH (CArchiveException, e)
    {
        loadArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    // close the archive
    loadArchive.Close();
    file.Close();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEntity::WriteToFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    // write the new stamp
    if (!file.Open(fileName, CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;

    // create the archive
    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);

    saveArchive.m_pDocument  = NULL;
    saveArchive.m_bForceFlat = FALSE;

    TRY
    {
        Serialize(saveArchive);
    }
    CATCH (CArchiveException, e)
    {
        saveArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    saveArchive.Flush();

    // close the file and the archive
    saveArchive.Close();
    file.Close();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_SymbolStamp;
        ar << m_pSymbol;
    }
    else
    {
        ar >> m_SymbolStamp;
        ar >> m_pSymbol;
    }

    m_Image.Serialize(ar);
}
//---------------------------------------------------------------------------
