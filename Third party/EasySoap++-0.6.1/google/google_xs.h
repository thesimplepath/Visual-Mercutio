
#ifndef __google_xs_h__
#define __google_xs_h__

//
// these classes tell use how we deserialize the
// google structs.
//

BEGIN_EASYSOAP_NAMESPACE


#ifndef HAVE_PARTIAL_SPECIALIZATION

//
// specify how we de/serialize our array types.
template<>
class SOAPTypeTraits<GoogleSearch::ResultElementArray> : public SOAPArrayTypeTraits
{
};

template<>
class SOAPTypeTraits<GoogleSearch::DirectoryCategoryArray> : public SOAPArrayTypeTraits
{
};
#endif // not HAVE_PARTIAL_SPECIALIZATION

template<>
class SOAPTypeTraits<GoogleSearch::DirectoryCategory>
{
public:
	static const SOAPParameter&
	Deserialize(const SOAPParameter& p, GoogleSearch::DirectoryCategory& v)
	{
		p.GetParameter("fullViewableName")				>> v.fullViewableName;
		p.GetParameter("specialEncoding")				>> v.specialEncoding;

		return p;
	}
};

template<>
class SOAPTypeTraits<GoogleSearch::ResultElement>
{
public:
	static const SOAPParameter&
	Deserialize(const SOAPParameter& p, GoogleSearch::ResultElement& v)
	{
		p.GetParameter("summary")						>> v.summary;
		p.GetParameter("URL")							>> v.URL;
		p.GetParameter("snippet")						>> v.snippet;
		p.GetParameter("title")							>> v.title;
		p.GetParameter("cachedSize")					>> v.cachedSize;
		p.GetParameter("relatedInformationPresent")		>> v.relatedInformationPresent;
		p.GetParameter("hostName")						>> v.hostName;
		p.GetParameter("directoryCategory")				>> v.directoryCategory;
		p.GetParameter("directoryTitle")				>> v.directoryTitle;

		return p;
	}
};

template<>
class SOAPTypeTraits<GoogleSearch::Result>
{
public:
	static const SOAPParameter&
	Deserialize(const SOAPParameter& p, GoogleSearch::Result& v)
	{
		p.GetParameter("documentFiltering")				>> v.documentFiltering;
		p.GetParameter("searchComments")				>> v.searchComments;
		p.GetParameter("estimatedTotalResultsCount")	>> v.estimatedTotalResultsCount;
		p.GetParameter("estimateIsExact")				>> v.estimateIsExact;
		p.GetParameter("resultElements")				>> v.resultElements;
		p.GetParameter("searchQuery")					>> v.searchQuery;
		p.GetParameter("startIndex")					>> v.startIndex;
		p.GetParameter("endIndex")						>> v.endIndex;
		p.GetParameter("searchTips")					>> v.searchTips;
		p.GetParameter("directoryCategories")			>> v.directoryCategories;
		p.GetParameter("searchTime")					>> v.searchTime;

		return p;
	}
};

END_EASYSOAP_NAMESPACE

#endif // __google_xs_h__
