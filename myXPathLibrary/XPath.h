#pragma once

#include "XMLreader.h"
#include <vector>
#include <fstream>
#include <queue>


class XPath
{
	enum SearchType{Deep, First};
	typedef pair<string, SearchType> root;

public:
	XPath(string filename);

	vector<string> Find(string command);

private:
	queue<root> roots;
	queue<XMLNode *> searchableNodes;
	queue<XMLNode *> resultNodes;
	string textToFind;
	SearchType searchType;
	ifstream fin;
	XMLRdr XMLDoc;
	vector<string> result;
	int rootInd;
	
	void ParseCommand(string command);	
	bool SearchNode(const root &curRoot);
	void CheckChildren(XMLNode *node, const root &curRoot);
};

