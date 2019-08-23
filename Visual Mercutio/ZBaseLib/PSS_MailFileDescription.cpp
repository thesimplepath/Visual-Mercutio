/****************************************************************************
 * ==> PSS_MailFileDescription ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail file description                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MailFileDescription.h"

//---------------------------------------------------------------------------
// PSS_MailFileDescription 
//---------------------------------------------------------------------------
PSS_MailFileDescription::PSS_MailFileDescription() :
    m_MapiFileDesc(NULL),
    m_AttachementType(PSS_File::IE_AT_InsertedFile)
{}
//---------------------------------------------------------------------------
PSS_MailFileDescription::PSS_MailFileDescription(CStringArray& fileList, PSS_File::IEAttachementType attachType) :
    m_MapiFileDesc(NULL),
    m_AttachementType(attachType)
{
    Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
PSS_MailFileDescription::PSS_MailFileDescription(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType) :
    m_MapiFileDesc(NULL),
    m_AttachementType(PSS_File::IE_AT_InsertedFile)
{
    Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
PSS_MailFileDescription::~PSS_MailFileDescription()
{
    if (m_MapiFileDesc)
        delete[] m_MapiFileDesc;
}
//---------------------------------------------------------------------------
void PSS_MailFileDescription::Fill(CStringArray& fileList, PSS_File::IEAttachementType attachType)
{
    RemoveAllFiles();

    for (register int i = 0; i < fileList.GetSize(); ++i)
        AddFile(fileList[i]);
}
//---------------------------------------------------------------------------
void PSS_MailFileDescription::Fill(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType)
{
    RemoveAllFiles();

    for (register size_t i = 0; i < fileList.GetCount(); ++i)
        AddFile(*fileList.GetAt(i));
}
//---------------------------------------------------------------------------
BOOL PSS_MailFileDescription::AddFile(PSS_File& file, PSS_File::IEAttachementType attachType)
{
    SetAttachementType(file.GetAttachementType());
    return (m_FileArray.Add(file.GetCompleteFileName()) >= 0);
}
//---------------------------------------------------------------------------
MapiFileDesc* PSS_MailFileDescription::GetMapiFileDesc()
{
    if (m_MapiFileDesc)
        delete[] m_MapiFileDesc;
      
    m_MapiFileDesc = new FAR MapiFileDesc[GetCount()];
      
    for (register int i = 0; i < m_FileArray.GetSize(); ++i)
    {
        std::memset(lpMapiFileDesc(&m_MapiFileDesc[i]), 0, sizeof(MapiFileDesc));
        m_MapiFileDesc[i].nPosition    = ULONG(-1);
        m_MapiFileDesc[i].lpszPathName = (char*)((const char*)m_FileArray[i]);
    }

    return m_MapiFileDesc;
}
//---------------------------------------------------------------------------
const CString& PSS_MailFileDescription::GetHyperLinkText()
{
    m_HyperLinkText.Empty();

    for (register int i = 0; i < m_FileArray.GetSize(); ++i)
    {
        m_HyperLinkText += "\n";
        m_HyperLinkText += "<file://" + m_FileArray[i];
        m_HyperLinkText += ">";
    }

    m_HyperLinkText += "\n";

    return m_HyperLinkText;
}
//---------------------------------------------------------------------------
