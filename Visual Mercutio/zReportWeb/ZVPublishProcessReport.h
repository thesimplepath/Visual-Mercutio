// ******************************************************************************************************
// *                                    Classe ZVPublishProcessReport                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 1er mars 2006 - Création de la nouvelle classe ZVPublishProcessReport.                *
// ******************************************************************************************************
// * Cette classe effectue la publication du rapport processus en tant que pages Internet.                *
// ******************************************************************************************************

#if !defined(AFX_ZVPUBLISHPROCESSREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHPROCESSREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

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

#include "PSS_Constants.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphPage.h"

#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"

#include "zModelWeb\PSS_PublishModelGenerateDialog.h"

#include "zWeb\PSS_HtmlFile.h"

#include "zProperty\PSS_PropertyAttributes.h"

#ifdef _ZREPORTWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// ******************************************************************************************************
// *                          Classes utilisées pour la gestion interne des données                        *
// ******************************************************************************************************

class AFX_EXT_CLASS _ZVSymbolEntity : public CObject
{
public:

    _ZVSymbolEntity();
    _ZVSymbolEntity(int            Ref,
                    CString        Name,
                    CString        Description);

    ~_ZVSymbolEntity();

    void            SetRef(int Ref);
    int                GetRef();

    void            SetName(CString Name);
    CString            GetName();

    void            SetDescription(CString Description);
    CString            GetDescription();

private:

    int                nRef;

    CString            m_Name;
    CString            m_Description;
};

class AFX_EXT_CLASS _ZVSymbolContainer
{
public:

    _ZVSymbolContainer();
    ~_ZVSymbolContainer();

    void AddSymbol(_ZVSymbolEntity* SymbolEntity);
    void RemoveAll();
    void Sort();

    _ZVSymbolEntity* GetAt(POSITION Pos);

    POSITION GetHeadPosition();
    POSITION GetTailPosition();
    POSITION GetPrevPosition();
    POSITION GetNextPosition();

private:

    // JMR-MODIF - Le 13 juin 2006 - Ajout de la fonction WashString.
    CString WashString(CString EntryString);

private:

    CObList        m_SymbolList;
    POSITION    m_Pos;
};

// ******************************************************************************************************
// *                                     Classe ZVPublishProcessReport                                    *
// ******************************************************************************************************
class AFX_EXT_CLASS ZVPublishProcessReport
{
public:

    ZVPublishProcessReport(PSS_ProcessGraphModelMdlBP* pModel = NULL,
                           PSS_PropertyAttributes*     pPropAttributes = NULL);

    virtual ~ZVPublishProcessReport();

    bool Publish(CString Directory);

private:

    bool CreateFileSystem(CString Directory, PSS_ProcessGraphModelMdlBP* m_StartRootModel = NULL);

    CString GenerateFileName(CString Directory, CString ProcessName);

    PSS_Symbol* FindSymbol(const CString SymbolName, PSS_ProcessGraphModelMdlBP* m_StartRootModel = NULL);
    PSS_LinkSymbol* FindLinkSymbol(const CString SymbolName, PSS_ProcessGraphModelMdlBP* m_StartRootModel = NULL);

    void CreateReport(PSS_ProcessSymbolBP* m_pProcessSymbol);
    void GeneratePageFile(CString Name, CString Description);
    void GenerateSection(PSS_Properties::IPropertySet& PropSet);
    void GenerateHTMLPageHead(CString Title);
    void GenerateHTMLPageFoot();
    void GenerateHTMLTableHead();
    void GenerateHTMLTableFoot();

    // JMR-MODIF - Le 18 avril 2007 - Suppression du 3ème paramètre.
    void GenerateHTMLReportTitle(CString DomainName, CString Title);

    void GenerateHTMLSymbolTitle(int NbRef, CString Title, CString ObjectType, COLORREF ColorTitle);
    void GenerateHTMLSymbolTitle(int NbRef, CString Title, COLORREF ColorTitle);
    void GenerateHTMLSectionTitle(CString Title);
    void GenerateHTMLSectionLine(CString NbRef, CString Title, CString Description);
    void GenerateBlackLine();
    void GenerateSeparation();

    void WriteLine(CString Text);
    void WriteLine(int nID);

    void ResetDatas();

private:

    PSS_PropertyAttributes*            m_pPropAttributes;

    PSS_ProcessGraphModelMdl*            m_pRootModel;

    PSS_HtmlFile                      HtmlFile;

    PSS_PublishModelGenerateDialog    m_FileGenerateWindow;

    _ZVSymbolContainer                m_StartContainer;
    _ZVSymbolContainer                m_StopContainer;
    _ZVSymbolContainer                m_ProcedureContainer;

    // JMR-MODIF - Le 31 mai 2006 - Ajout de la variable m_DoorContainer.
    _ZVSymbolContainer                m_DoorContainer;
};

#endif
