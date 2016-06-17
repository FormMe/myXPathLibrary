#include "XPath.h"
#include <string>


XPath::XPath(std::string filename) :
	XMLDoc(filename),
	searchType(First),
	rootInd(0),
	fin(filename) {}

vector<string> XPath::Find(string command)
{
	if (!fin)
		throw invalid_argument("Can`t open file");
	ParseCommand(command);

	//��������� ������ ������ xml 
	if (roots.front().second == First)
	{
		if (XMLDoc.GetRootNode()->GetNodeName() != roots.front().first)
			return result;
		roots.pop();
	}
	if (XMLDoc.GetRootNode()->GetNodeName() == roots.front().first)
		resultNodes.push(XMLDoc.GetRootNode());

	searchableNodes.push(XMLDoc.GetRootNode());

	while (!roots.empty())
	{
		if (!SearchNode(roots.front()))	return result;
		roots.pop();
	}

	//�������������� � xml


	return result;
}

void XPath::ParseCommand(string command)
{
	auto foundedPos = 0;		//���������� ������� ������ ������� �����
	if (command[0] == '/')
	{
		++foundedPos;
		if (command[1] == '/')
		{
			++foundedPos;
			searchType = Deep;
		}
	}
	auto prevPos = foundedPos;
	for (; foundedPos < command.size(); ++foundedPos)
	{
		prevPos = foundedPos;							//�������� �� ���� ������ ������
		foundedPos = command.find('/', foundedPos);
		if (foundedPos == std::string::npos) break;

		auto header = string(command, prevPos, foundedPos - prevPos);
		auto root = make_pair(header, searchType);
		roots.push(root);								//���������� ������ ������

		auto st = command[foundedPos + 1] != '/';		//���������� ������� ������ ��� ���������� �����
		if (!st) ++foundedPos;
		searchType = static_cast<SearchType>(st);
	}

	auto textStartPos = command.find('[', prevPos);		//���������� ����� �� ����� �� �������� ��������
	if (textStartPos != std::string::npos)				//������: element[value]	
	{
		++textStartPos;
		auto textEndPos = command.find(']', prevPos);
		textToFind = string(command, textStartPos, textEndPos - textStartPos);
	}
	else
	{
		textStartPos = command.size();
	}
	auto elemToFind = make_pair(string(command, prevPos, textStartPos - prevPos), searchType);
	roots.push(elemToFind);							//��������� ������� �������
}

bool XPath::SearchNode(const root &curRoot)
{
	while (!searchableNodes.empty())
	{
		CheckChildren(searchableNodes.front(), curRoot);
		searchableNodes.pop();
	}
	if (resultNodes.empty()) return false;
	swap(resultNodes, searchableNodes);
	return true;
}

void XPath::CheckChildren(XMLNode *node, const root &curRoot)
{
	for (auto NodePtr = node->GetFirstChild(); NodePtr != nullptr; NodePtr = node->GetNextChild())
	{
		if (NodePtr->GetNodeName() == curRoot.first)
			resultNodes.push(NodePtr);
		if (curRoot.second == Deep)
			searchableNodes.push(NodePtr);
	}

}