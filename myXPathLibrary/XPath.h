#pragma once

#include "XMLreader.h"
#include <vector>


class XPath
{
	enum SearchType{All, First};
	typedef pair<string, SearchType> root;

public:
	XPath(string filename);
	~XPath();

	vector<string> Find(string command);

private:
	vector<root> roots;
	string elemToFind;
	string textToFind;
	XMLRdr XMLDoc;

	void ParseCommand(string command);
	XMLNode * SelectChildNode(root parent);


};

