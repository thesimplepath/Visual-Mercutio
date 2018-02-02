// ******************************************************************************************************
// *										   Classe ZUReportNavigation								*
// ******************************************************************************************************
// * JMR-MODIF - Le 29 juin 2005 - Création de la nouvelle classe ZVPublishReport.						*
// * Cette classe gère la navigation dans les symboles du document.										*
// ******************************************************************************************************

#include "stdafx.h"
#include ".\ZUReportNavigation.h"

ZUReportNavigation::ZUReportNavigation()
{
}

ZUReportNavigation::~ZUReportNavigation()
{
}

// ******************************************************************************************************
// *							  Fonctions protégées de la classe ZUReportNavigation					*
// ******************************************************************************************************

// Cette fonction permet de remplir les données du fichier contenant la page du rapport.
void ZUReportNavigation::GeneratePageFile(CString Name, CString Description)
{
	if (!m_pModel)
		return;

	m_UnitName = Name;

	// Génération de l'en-tête de page.
	HtmlFile << "<HTML>\n<HEAD>\n<TITLE>";
	HtmlFile << Name;
	HtmlFile << "</TITLE>\n<META http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n";
	HtmlFile << "</HEAD>\n<BODY>\n<TABLE width=\"75%\" border=\"1\">\n";

	// Génération du corps de la page.
	HtmlFile << "<TR>\n\t<TD colSpan=\"3\">\n\t\t";
	HtmlFile << "<P align=\"center\">\n\t\t<FONT size=\"5\"><FONT face=\"Arial\"></FONT></FONT>\n\t\t<B><FONT face=\"Arial\" size=\"5\">";
	HtmlFile << Name;
	HtmlFile << "</FONT></B>\n\t\t<FONT size=\"5\"><FONT face=\"Arial\"></FONT></FONT>\n\t\t</P>\n\t</TD>\n</TR>\n";

	HtmlFile << "<TR>\n\t<TD colSpan=\"3\">\n\t\t<FONT face=\"Arial\"></FONT>\n\t\t<FONT face=\"Arial\">";
	HtmlFile << Description;
	HtmlFile << "</FONT>\n\t\t<FONT face=\"Arial\"></FONT>\n\t</TD>\n</TR>\n";

	HtmlFile << "<TR>\n\t<TD bgColor=\"#ff9966\" colSpan=\"3\" rowSpan=\"1\">\n\t\t";
	HtmlFile << "<P align=\"center\">\n\t\t<FONT size=\"5\"><FONT face=\"Arial\"></FONT></FONT>\n\t\t<FONT face=\"Arial\" color=\"#ffffff\" size=\"5\"><STRONG>";
	HtmlFile << "Synthèse";
	HtmlFile << "</STRONG></FONT>\n\t\t<FONT size=\"5\"><FONT face=\"Arial\"><STRONG></STRONG></FONT></FONT>\n\t\t</P>\n\t</TD>\n</TR>\n";

	HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" colSpan=\"1\" rowSpan=\"1\"><FONT face=\"Arial\" color=\"#ffffff\" size=\"4\"><STRONG>";
	HtmlFile << "Domaine/Thème";
	HtmlFile << "</STRONG></FONT></TD>\n\t<TD bgColor=\"#999999\"><FONT face=\"Arial\" color=\"#ffffff\" size=\"4\"><STRONG>";
	HtmlFile << "Processus";
	HtmlFile << "</STRONG></FONT></TD>\n\t<TD bgColor=\"#999999\"><FONT face=\"Arial\" color=\"#ffffff\" size=\"4\"><STRONG>";
	HtmlFile << "Procédure";
	HtmlFile << "</STRONG></FONT></TD>\n</TR>\n";

	PublishProc = PUBLISH_HEADERS;
	m_pRootModel = m_pModel;
	m_pModel->AcceptVisitor( *this );

	if (m_ShowDetails)
	{
		PublishProc = PUBLISH_DETAILS;
		m_pRootModel = m_pModel;
		m_pModel->AcceptVisitor( *this );
	}

	// Génération de la fin de la page.
	HtmlFile << "</TABLE>\n</BODY>\n</HTML>\n";
}

// Cette fonction permet d'ajouter la section de processus.
bool ZUReportNavigation::CreateProcess()
{
	if (m_pPreviousProcess == NULL)
		return true;

	m_First = true;

	// Deux lignes vides avant l'en-tête.
	HtmlFile << "<TR>\n\t<TD colSpan=\"3\"></TD>\n</TR>\n";
	HtmlFile << "<TR>\n\t<TD colSpan=\"3\"></TD>\n</TR>\n";

	// Create the header
	HtmlFile << "<TR>\n\t<TD bgColor=\"#ff9966\"><FONT face=\"Arial\"><STRONG>";
	HtmlFile << m_DomainName;
	HtmlFile << "</STRONG></FONT></TD>\n\t<TD bgColor=\"#999999\"><FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
	HtmlFile << "Processus";
	HtmlFile << "</STRONG></FONT></TD>\n\t<TD bgColor=\"#ff9966\"><FONT face=\"Arial\"><STRONG>";
	HtmlFile << m_CurrentProcessName;
	HtmlFile << "</STRONG></FONT></TD>\n</TR>\n";

	// Une ligne vide à la fin de la section.
	HtmlFile << "<TR>\n\t<TD colSpan=\"3\"></TD>\n</TR>\n";

	CODNodeArray Nodes;

	if (reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)m_pPreviousProcess)->GetChildModel())->GetBPStartSymbols( Nodes, false ) > 0)
		StartSection( Nodes );

	return true;
}

// Cette fonction génère la sous-section du processus.
bool ZUReportNavigation::StartSection( CODNodeArray& Nodes )
{
	for (size_t nNodeIdx = 0; nNodeIdx < (size_t)Nodes.GetSize(); ++nNodeIdx)
	{
		IODNode* pINode = Nodes.GetAt(nNodeIdx);
		ZBBPStartSymbol* pStart = static_cast<ZBBPStartSymbol*>(pINode);

		if (!pStart)
			continue;

		// Check if for the same unit
		if (pStart->GetUnitName() != m_UnitName)
			continue;

		// Create the section
		HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
		HtmlFile << pStart->GetSymbolReferenceNumberStr();
		HtmlFile << "</FONT></TD>\n\t<TD bgColor=\"#999999\"><FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
		HtmlFile << "Point Start";
		HtmlFile << "</STRONG></FONT></TD>\n\t<TD><FONT face=\"Arial\">";
		HtmlFile << pStart->GetSymbolName();
		HtmlFile << "</FONT></TD>\n</TR>\n";

		HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
		HtmlFile << "Description";
		HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
		HtmlFile << pStart->GetSymbolComment();
		HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
		HtmlFile << " ";
		HtmlFile << "</FONT></TD>\n</TR>\n";

		if (m_IncludeDeliverables)
		{
			// Retreive all leaving down deliverables
			CODEdgeArray Edges;

			if (pStart->GetEdgesLeaving( Edges ) > 0)
			{
				ZBDeliverableLinkSymbol* pDeliverable = NULL;
				for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
				{
					IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
					pDeliverable = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

					// Check if null and continue if the case
					if (!pDeliverable)
						continue;
				}

				if (pDeliverable)
				{
					HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
					HtmlFile << pDeliverable->GetSymbolReferenceNumberStr();
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << pDeliverable->GetSymbolName();
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << " ";
					HtmlFile << "</FONT></TD>\n</TR>\n";
				}
			}
		}
	}

	// Une ligne vide à la fin de la section.
	HtmlFile << "<TR>\n\t<TD colSpan=\"3\"></TD>\n</TR>\n";

	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPDoorSymbol.
bool ZUReportNavigation::OnDoorSymbol( ZBBPDoorSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPPageSymbol.
bool ZUReportNavigation::OnPageSymbol( ZBBPPageSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcedureSymbol.
bool ZUReportNavigation::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
	// Only for the specific unit
	// Check if for the same unit
	bool Error;

	CString UnitName = pSymbol->RetreiveUnitName( pSymbol->GetUnitGUID(), Error );

	if (m_UnitName == UnitName)
	{
		switch (PublishProc)
		{
			case PUBLISH_HEADERS:
			{
				HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\" height=\"21\"><FONT face=\"Arial\">";
				HtmlFile << m_DomainName;
				HtmlFile << "</FONT></TD>\n\t<TD bgColor=\"#0099ff\" height=\"21\"><FONT face=\"Arial\">";
				HtmlFile << m_CurrentProcessName;
				HtmlFile << "</FONT></TD>\n\t<TD height=\"21\"><FONT face=\"Arial\">";
				HtmlFile << pSymbol->GetSymbolName();
				HtmlFile << "</FONT></TD>\n</TR>\n";

				break;
			}

			case PUBLISH_DETAILS:
			{
				// If not yet displayed, display the process section
				if (m_First == false)
				{
					CreateProcess();
				}

				// Display the section
				HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
				HtmlFile << pSymbol->GetSymbolReferenceNumberStr();
				HtmlFile << "</FONT></TD>\n\t<TD bgColor=\"#999999\"><FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
				HtmlFile << "Procédure";
				HtmlFile << "</STRONG></FONT></TD>\n\t<TD><FONT face=\"Arial\">";
				HtmlFile << pSymbol->GetSymbolName();
				HtmlFile << "</FONT></TD>\n</TR>\n";

				HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
				HtmlFile << "Description";
				HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
				HtmlFile << pSymbol->GetSymbolComment();
				HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
				HtmlFile << " ";
				HtmlFile << "</FONT></TD>\n</TR>\n";

				if (m_IncludeDeliverables)
				{
					HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
					HtmlFile << "Liste des livrables en entrée";
					HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

					// Retreive all entering up deliverables
					CODEdgeArray Edges;

					if (pSymbol->GetEnteringUpDeliverable( Edges ) > 0)
					{
						for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
						{
							IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
							ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

							// Check if null and continue if the case
							if (!pComp)
								continue;

							// Display the reference number and the deliverable name
							HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolReferenceNumberStr();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolName();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << " ";
							HtmlFile << "</FONT></TD>\n</TR>\n";
						}
					}

					HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
					HtmlFile << "Liste des livrables latéraux en sortie";
					HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

					// Retreive all leaving right deliverables
					if (pSymbol->GetEdgesLeaving_Right( Edges ) > 0)
					{
						for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
						{
							IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
							ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

							// Check if null and continue if the case
							if (!pComp)
								continue;

							// Display the reference number and the deliverable name
							HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolReferenceNumberStr();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolName();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << " ";
							HtmlFile << "</FONT></TD>\n</TR>\n";
						}
					}

					// Retreive all leaving left deliverables
					if (pSymbol->GetEdgesLeaving_Left( Edges ) > 0)
					{
						for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
						{
							IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
							ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

							// Check if null and continue if the case
							if (!pComp)
								continue;

							// Display the reference number and the deliverable name
							HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolReferenceNumberStr();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolName();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << " ";
							HtmlFile << "</FONT></TD>\n</TR>\n";
						}
					}

					HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" height=\"21\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
					HtmlFile << "Liste des livrables latéraux en entrée";
					HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

					// Retreive all entering right deliverables
					if (pSymbol->GetEdgesEntering_Right( Edges ) > 0)
					{
						for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
						{
							IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
							ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

							// Check if null and continue if the case
							if (!pComp)
								continue;

							// Display the reference number and the deliverable name
							HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolReferenceNumberStr();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolName();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << " ";
							HtmlFile << "</FONT></TD>\n</TR>\n";
						}
					}

					// Retreive all entering left deliverables
					if (pSymbol->GetEdgesEntering_Left( Edges ) > 0)
					{
						for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
						{
							IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
							ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

							// Check if null and continue if the case
							if (!pComp)
								continue;

							// Display the reference number and the deliverable name
							HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolReferenceNumberStr();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolName();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << " ";
							HtmlFile << "</FONT></TD>\n</TR>\n";
						}
					}
				}

				// Rules, decisions, tasks, etc.
				CString s;

				HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" height=\"21\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
				HtmlFile << "Liste des règles";
				HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

				// Build the next lines with the 
				// rules themselves, at least one empty line
				int Count = max( pSymbol->GetRuleCount(), 1);

				for (int i = 0; i < Count; ++i)
				{
					s.Format( "Règle %d", i+1 );

					HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
					HtmlFile << s;
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << pSymbol->GetRuleAt(i);
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << " ";
					HtmlFile << "</FONT></TD>\n</TR>\n";
				}

				HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
				HtmlFile << "Liste des tâches";
				HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

				// Build the next lines with the 
				// tasks themselves, at least one empty line
				Count = max( pSymbol->GetTaskCount(), 1);

				for (i = 0; i < Count; ++i)
				{
					s.Format( "Tâche %d", i+1 );

					HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
					HtmlFile << s;
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << pSymbol->GetTaskAt(i);
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << " ";
					HtmlFile << "</FONT></TD>\n</TR>\n";
				}

				HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
				HtmlFile << "Liste des décisions";
				HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

				// Build the next lines with the 
				// decisions themselves, at least one empty line
				Count = max( pSymbol->GetDecisionCount(), 1);

				for (i = 0; i < Count; ++i)
				{
					s.Format( "Décision %d", i+1 );

					HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
					HtmlFile << s;
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << pSymbol->GetDecisionAt(i);
					HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
					HtmlFile << " ";
					HtmlFile << "</FONT></TD>\n</TR>\n";
				}

				if (m_IncludeDeliverables)
				{
					HtmlFile << "<TR>\n\t<TD bgColor=\"#999999\" colSpan=\"3\">\n\t\t<FONT face=\"Arial\" color=\"#ffffff\"><STRONG>";
					HtmlFile << "Liste des livrables en sortie";
					HtmlFile << "</STRONG></FONT>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t\t<STRONG><FONT color=\"#ffffff\"><FONT face=\"Arial\"></FONT></FONT></STRONG>\n\t</TD>\n</TR>\n";

					// Retreive all leaving down deliverables
					CODEdgeArray Edges;

					if (pSymbol->GetEdgesLeaving_Down( Edges ) > 0)
					{
						for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
						{
							IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
							ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

							// Check if null and continue if the case
							if (!pComp)
								continue;

							// Display the reference number and the deliverable name
							HtmlFile << "<TR>\n\t<TD bgColor=\"#0099ff\"><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolReferenceNumberStr();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << pComp->GetSymbolName();
							HtmlFile << "</FONT></TD>\n\t<TD><FONT face=\"Arial\">";
							HtmlFile << " ";
							HtmlFile << "</FONT></TD>\n</TR>\n";
						}
					}
				}

				break;
			}
		}
	}

	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcessSymbol.
bool ZUReportNavigation::OnProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
	switch (PublishProc)
	{
		case PUBLISH_HEADERS:
		{
			m_CurrentProcessName = pSymbol->GetSymbolName();

			ZDProcessGraphModelMdl* pOwnerModel = (ZDProcessGraphModelMdl*)pSymbol->GetOwnerModel();
			if (pOwnerModel)
			{
				ZDProcessGraphPage*	pPage = m_pRootModel->FindModelPage( pOwnerModel, true );

				if (pPage)
					m_DomainName = pPage->GetPageName();
				else
					m_DomainName = "Not found";
			}

			break;
		}

		case PUBLISH_DETAILS:
		{
			m_pPreviousProcess = pSymbol;
			m_CurrentProcessName = pSymbol->GetSymbolName();

			ZDProcessGraphModelMdl* pOwnerModel = (ZDProcessGraphModelMdl*)pSymbol->GetOwnerModel();

			if (pOwnerModel)
			{
				ZDProcessGraphPage*	pPage = m_pRootModel->FindModelPage( pOwnerModel, true );

				if (pPage)
					m_DomainName = pPage->GetPageName();
				else
					m_DomainName = "Not found";
			}

			m_First = false;

			break;
		}
	}

	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPStartSymbol.
bool ZUReportNavigation::OnStartSymbol( ZBBPStartSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPStopSymbol.
bool ZUReportNavigation::OnStopSymbol( ZBBPStopSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBDeliverableLinkSymbol.
bool ZUReportNavigation::OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBSymbol.
bool ZUReportNavigation::OnSymbol( ZBSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBLinkSymbol.
bool ZUReportNavigation::OnLink( ZBLinkSymbol* pLink )
{
	return true;
}

// Cette fonction est la fonction principale de navigation. Elle appelle les sous-fonction par rapport à l'objet visité.
bool ZUReportNavigation::Visit( CODComponent& Symbol )
{
	CODComponent* pSymbol = &Symbol;

	if ( ISA ( pSymbol, ZBBPProcedureSymbol ) )
		return OnProcedureSymbol( dynamic_cast<ZBBPProcedureSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBDeliverableLinkSymbol ) )
		return OnDeliverableLinkSymbol( dynamic_cast<ZBDeliverableLinkSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBBPDoorSymbol ) )
		return OnDoorSymbol( dynamic_cast<ZBBPDoorSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBBPPageSymbol ) )
		return OnPageSymbol( dynamic_cast<ZBBPPageSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBBPProcessSymbol ) )
		return OnProcessSymbol( dynamic_cast<ZBBPProcessSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBBPStartSymbol ) )
		return OnStartSymbol( dynamic_cast<ZBBPStartSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBBPStopSymbol ) )
		return OnStopSymbol( dynamic_cast<ZBBPStopSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBSymbol ) )
		return OnSymbol( dynamic_cast<ZBSymbol*>(&Symbol) );
	else
	if ( ISA ( pSymbol, ZBLinkSymbol ) )
		return OnLink( dynamic_cast<ZBLinkSymbol*>(&Symbol) );

	// Not a right symbol or not necessary to visit
	return false;
}
