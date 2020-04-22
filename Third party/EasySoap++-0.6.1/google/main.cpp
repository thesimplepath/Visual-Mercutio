
#include <iostream>
#include "google.h"

//
// Quick little demo program to try out
// our GoogleSearch class.
//

void
usage(const char * prog)
{
	std::cout
		<< "Usage: " << prog << " <query>" << std::endl
		<< "Where:" << std::endl
		<< "\t<query> is your search string." << std::endl << std::endl
		<< "Set GOOGLE_KEY environment to your Google account key." << std::endl
		<< "Register for your Google account key at "
		<< "http://www.google.com/apis/" << std::endl << std::endl
		;
}

int
main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		usage(argv[0]);
		return 1;
	}

	const char *googleKey = "pZx7rRyMp14zwsWLG4eus06MVmc4XiTK";
	const char *query = argv[1];

	try
	{
		GoogleSearch google;

		//
		// set the key up one time so
		// we don't have to pass it in
		// with each query.
		if (!googleKey)
		{
			std::cout << "GOOGLE_KEY environment variable not set." << std::endl;
			usage(argv[0]);
			return 1;
		}
		google.setKey(googleKey);

		//
		// Do our search.
		GoogleSearch::Result result;
		google.search(query, 0, 10,
				false, "", false, "",
				"latin1", "latin1", result);

		//
		// Print out a summary of the results
		std::cout << "Found an estimated " << result.estimatedTotalResultsCount
			<< " results in " << result.searchTime << " second(s)." << std::endl
			<< "Search comments: " << result.searchComments << std::endl
			<< "Search tips: " << result.searchTips << std::endl
			;

		//
		// Print info on the hits.
		for (GoogleSearch::ResultElementArray::iterator el = result.resultElements.begin();
				el != result.resultElements.end(); ++el)
		{
			std::cout << "Title: " << el->title << std::endl
				<< "Snippet: " << el->snippet << std::endl
				<< "URL: " << el->URL << std::endl
				<< std::endl
				;
		}
	}
	catch (SOAPException& sex)
	{
		std::cerr << "Caught SOAP exception: "
			<< sex.What().Str() << std::endl;
		return 1;
	}

	return 0;
}
