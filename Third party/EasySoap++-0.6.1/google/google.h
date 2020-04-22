
#ifndef __google_h__
#define __google_h__

#include <vector>
#include <string>
#include <easysoap/SOAP.h>

USING_EASYSOAP_NAMESPACE

class GoogleSearch
{
private:
	static const char *namespaceURI;
	static const char *defaultEndpoint;

	//
	// not going to need these
	GoogleSearch(const GoogleSearch&);
	GoogleSearch& operator=(const GoogleSearch&);

	//
	// a proxy for handling our requests.
	SOAPProxy		m_proxy;
	std::string		m_key;

public:

	//
	// define the structs returned by google
	typedef struct {
		std::string				fullViewableName;
		std::string				specialEncoding;
	} DirectoryCategory ;

	typedef struct {
		std::string				summary;
		std::string				URL;
		std::string				snippet;
		std::string				title;
		std::string				cachedSize;
		bool					relatedInformationPresent;
		std::string				hostName;
		DirectoryCategory		directoryCategory;
		std::string				directoryTitle;
	} ResultElement ;

	typedef std::vector<ResultElement>		ResultElementArray;
	typedef std::vector<DirectoryCategory>	DirectoryCategoryArray;

	typedef struct {
		bool					documentFiltering;
		std::string				searchComments;
		int						estimatedTotalResultsCount;
		bool					estimateIsExact;
		ResultElementArray		resultElements;
		std::string				searchQuery;
		int						startIndex;
		int						endIndex;
		std::string				searchTips;
		DirectoryCategoryArray	directoryCategories;
		double					searchTime;
	} Result;

	//
	// constructor
	GoogleSearch(const char *endpoint = 0);

	//
	// setup our login key.
	void setKey(const std::string& key) { m_key = key; }

	//
	// define the google methods
	void getCachedPage(
			const std::string&	url,
			std::vector<char>&	result
			);

	void spellingSuggestion(
			const std::string&	phrase,
			std::string&		result
			);

	void search(
			const std::string&	q,
			int					start,
			int					maxResults,
			bool				filter,
			const std::string&	restrict,
			bool				safeSearch,
			const std::string&	lr,
			const std::string&	ie,
			const std::string&	oe,
			Result&				result
			);
};

#endif // __google_h__
