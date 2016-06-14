
#define _CRT_SECURE_NO_WARNINGS
#include "XMLreader.h"

int XMLNode::iObjCnt;

XMLNode::XMLNode(string sName, XMLNode * Parent)
{
	iObjCnt++; // No of objects created.
	NodeCtr = 0;
	ParentNode = Parent;
	sNodeName = sName;
}

void XMLNode::DeleteAll()
{
	for (XMLNodeMapIter TmpItr = XMLChildNodes.begin(); TmpItr != XMLChildNodes.end(); ++TmpItr)
	{
		if (TmpItr->second != NULL)
		{
			if ((TmpItr->second->GetChildNodeCnt() != 0))
				TmpItr->second->DeleteAll();
			delete TmpItr->second;

		}
	}
	XMLChildNodes.clear(); // clear all ointers.
	XMLChildElements.clear(); // Clear all elements and vales
}

void XMLNode::ResetReading()
{
	for (XMLNodeMapIter TmpItr = XMLChildNodes.begin(); TmpItr != XMLChildNodes.end(); TmpItr++)
	{
		if (TmpItr->second != NULL)
		{
			if ((TmpItr->second->GetChildNodeCnt() != 0))
				TmpItr->second->ResetReading();
			ResetNodeCntr();

		}
	}
}

long XMLNode::GetChildNodeCnt()
{
	return XMLChildNodes.size();
}

string XMLNode::GetElementValue(string sName) // Getelement value
{
	return XMLChildElements[sName];
}


XMLNode * XMLNode::GetFirstChild()
{
	NodeCtr = 0;
	return XMLChildNodes[NodeCtr++];
}


XMLNode * XMLNode::GetNextChild()
{
	return XMLChildNodes[NodeCtr++];
}


XMLNode * XMLNode::AddChildNode(string sName)
{
	static int iTmp;
	XMLNode * Tmp = new XMLNode(sName, this);
	XMLChildNodes[NodeCtr++] = Tmp;
	iTmp++;

	return Tmp;
}


void XMLNode::AddElementVal(string sKey, string sval)
{
	XMLChildElements[sKey] = sval;
}

XMLRdr::XMLRdr(string sFileName)
{
	sDocName = sFileName;
	XMLRootNode = NULL;
	XMLTraverse = NULL;
	if (ReadFile() == false)
		cout << "Unable to open file";
	else
		cout << "File opened successfuly";
}


bool XMLRdr::ReadFile()
{
	FILE *fp = fopen(sDocName.c_str(), "r+");
	if (fp == NULL)
		return false;
	char buf[1000];
	while (fgets(buf, 1000, fp))
	{
		string sTmp = buf;
		sTmp = EatupWhiteSpace(sTmp);
		if (ProcessString(sTmp) == false)
		{
			XMLRootNode->DeleteAll();
			return false;
		}
	}
	if (XMLTraverse != NULL)
		return false;
	fclose(fp);
	return true;
}


string XMLRdr::EatupWhiteSpace(string sInput)
{
	int iStart = sInput.find_first_not_of(" \t\n");
	int iEnd = sInput.find_last_not_of(" \t\n");
	if (iStart == -1) // No non-spaces
		return "";

	return std::string(sInput, iStart, iEnd - iStart + 1);
}


bool XMLRdr::ProcessString(string sInput)
{
	if (sInput[0] != '<')
		return false;
	switch (sInput[1])
	{
	case '?':
	case '!':
		return true;
	case '/':
	{
		if (XMLTraverse == NULL)
			return false;
		XMLTraverse->ResetNodeCntr();
		XMLTraverse = XMLTraverse->GetParentNode();
	}
	break;
	default:
	{
		sInput = sInput.substr(1);
		int iTmp = sInput.find_first_of("<");

		if (iTmp != -1)//not a node .But an element 
		{
			iTmp = sInput.find_first_of(" \t>"); //ignore atributes. if any.
			string sKey = sInput.substr(0, iTmp);
			iTmp = sInput.find_first_of(">");
			sInput = sInput.substr(iTmp + 1);
			iTmp = sInput.find_first_of("<");
			string sVal = sInput.substr(0, iTmp);
			XMLTraverse->AddElementVal(sKey, sVal);
		}
		else
		{
			iTmp = sInput.find_first_of(" \t>");
			string sNodeName = sInput.substr(0, iTmp);
			if (XMLRootNode == NULL)
			{
				XMLRootNode = new XMLNode(sNodeName.c_str(), NULL);
				XMLTraverse = XMLRootNode;
			}
			else
			{
				XMLTraverse = XMLTraverse->AddChildNode(sNodeName);
			}

		}
		break;
	}
	}
	return true;
}

XMLRdr::~XMLRdr()
{

	if ((XMLRootNode == NULL) || (XMLNode::GetObjectCnt() == 0))
		return;
	DeleteAll();
	if (XMLRootNode != NULL)
		delete XMLRootNode;

	if (!XMLNode::GetObjectCnt())
		cout << "\nAll Node Objects deleted";
}

string XMLRdr::GetDocName()
{
	return sDocName;
}

string XMLRdr::GetRootName()
{
	return sRootName;
}

XMLNode * XMLRdr::GetRootNode()
{
	return XMLRootNode;
}