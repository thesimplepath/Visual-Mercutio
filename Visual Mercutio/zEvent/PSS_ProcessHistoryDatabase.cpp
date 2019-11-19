/****************************************************************************
 * ==> PSS_ProcessHistoryDatabase ------------------------------------------*
 ****************************************************************************
 * Description : Provides a process history database                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ProcessHistoryDatabase.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ProcessHistoryDatabase
//---------------------------------------------------------------------------
PSS_ProcessHistoryDatabase::PSS_ProcessHistoryDatabase(const CString& fileName, IEType type) :
    m_pProcessHistoDAO(NULL),
    m_Type(type),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_ProcessHistoryDatabase::PSS_ProcessHistoryDatabase(const PSS_ProcessHistoryDatabase& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ProcessHistoryDatabase::~PSS_ProcessHistoryDatabase()
{
    switch (m_Type)
    {
        case IE_DT_DAO:
            if (m_pProcessHistoDAO)
            {
                m_pProcessHistoDAO->Close();
                delete m_pProcessHistoDAO;
            }

            break;

        case IE_DT_ODBC:
            // not yet implemented
            break;
    }
}
//---------------------------------------------------------------------------
const PSS_ProcessHistoryDatabase& PSS_ProcessHistoryDatabase::operator = (const PSS_ProcessHistoryDatabase& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDatabase::Create(const CString& fileName, IEType type)
{
    m_FileName = fileName;
    m_Type     = type;

    return Initialize();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDatabase::Initialize()
{
    if (m_FileName.IsEmpty())
        return FALSE;

    switch (m_Type)
    {
        case IE_DT_DAO:
            m_pProcessHistoDAO = new PSS_ProcessHistoryDAODatabase(m_FileName);
            break;

        case IE_DT_ODBC:
            // not yet implemented
            THROW("NOT IMPLEMENTED");
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDatabase::AppendEventToHistoric(const PSS_ActivityEvent& activityEvent)
{
    switch (m_Type)
    {
        case IE_DT_DAO:
            if (m_pProcessHistoDAO)
                return m_pProcessHistoDAO->AppendEventToHistoric(activityEvent);

            break;

        case IE_DT_ODBC:
            // not yet implemented
            THROW("NOT IMPLEMENTED");
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessHistoryDatabase::Close()
{
    switch (m_Type)
    {
        case IE_DT_DAO:
            if (m_pProcessHistoDAO)
                return m_pProcessHistoDAO->Close();

            break;

        case IE_DT_ODBC:
            // not yet implemented
            THROW("NOT IMPLEMENTED");
    }

    return FALSE;
}
//---------------------------------------------------------------------------
