
#include "google.h"
#include <easysoap/SOAPSTL.h>

#include "google_xs.h"

const char *GoogleSearch::namespaceURI = "urn:GoogleSearch";
const char *GoogleSearch::defaultEndpoint = "http://api.google.com/search/beta2";

GoogleSearch::GoogleSearch(const char *endpoint)
{
	if (endpoint)
		m_proxy.SetEndpoint(endpoint);
	else
		m_proxy.SetEndpoint(defaultEndpoint);
}

void
GoogleSearch::getCachedPage(
		const std::string&	url,
		std::vector<char>&	result
		)
{
	SOAPMethod method("doGetCachedPage",
			namespaceURI,
			"urn:GoogleSearchAction");

	method.AddParameter("key") << m_key;
	method.AddParameter("url") << url;

	const SOAPResponse& response = m_proxy.Execute(method);

	SOAPSTLBase64 base64(result);
	response.GetReturnValue() >> base64;
}

void
GoogleSearch::spellingSuggestion(
		const std::string&	phrase,
		std::string&		result
		)
{
	SOAPMethod method(
			"doSpellingSuggestion",
			namespaceURI,
			"urn:GoogleSearchAction");

	method.AddParameter("key") << m_key;
	method.AddParameter("phrase") << phrase;

	const SOAPResponse& response = m_proxy.Execute(method);
	response.GetReturnValue() >> result;
}

void
GoogleSearch::search(
		const std::string&	q,
		int					start,
		int					maxResults,
		bool				filter,
		const std::string&	restrict,
		bool				safeSearch,
		const std::string&	lr,
		const std::string&	ie,
		const std::string&	oe,
		Result& result
		)
{
	SOAPMethod method(
			"doGoogleSearch",
			namespaceURI,
			"urn:GoogleSearchAction");

	method.AddParameter("key") << m_key;
	method.AddParameter("q") << q;
	method.AddParameter("start") << start;
	method.AddParameter("maxResults") << maxResults;
	method.AddParameter("filter") << filter;
	method.AddParameter("restrict") << restrict;
	method.AddParameter("safeSearch") << safeSearch;
	method.AddParameter("lr") << lr;
	method.AddParameter("ie") << ie;
	method.AddParameter("oe") << oe;

	const SOAPResponse& response = m_proxy.Execute(method);
	response.GetReturnValue() >> result;
}


