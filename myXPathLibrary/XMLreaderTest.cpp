#include "XPath.h"
#include <iostream>
int main(int argc, char* argv[])
{
	XPath x = XPath("AAA.xml");
	auto result = x.Find("//recipe//d");
	for (auto res : result)
		cout << res.c_str() << endl;

	//// pass the xml file name to constructr. Each 
	//// object is closely coupled to an xml file. Constructor reads the xml file 
	//// Creates the DOM structure in memory and release the xml file.
	//	XMLRdr XMLDoc("boby.xml");
	//	try
	//	{	
	//	// returns the number of node objects  created.
	//		int iObjCnt = XMLNode::GetObjectCnt();
	//		if(iObjCnt == 0)
	//			return 1;
	//		cout<<"\nNumber of Node objects "<<iObjCnt<<"\n";
	//	}
	//	catch(...)
	//	{
	//		cout<<"Exception";
	//	}
	//		
	//
	//
	//	// returns a pointer to root node.
	//		XMLNode * NodePtr = XMLDoc.GetRootNode();
	//
	//	// Returns a pointer to first child node of the node NodePtr is poiting to.
	//		XMLNode *NodePtr2  = NodePtr->GetFirstChild();       
	//
	//		while(NodePtr2 != NULL)
	//		{
	//			string sEname = NodePtr2->GetNodeName();
	//			cout<<sEname.c_str();
	//
	//	// Returns element value for the tag phone		
	//			string sVal = NodePtr2->GetElementValue("phone");  		
	//			cout<<"\tPhone\t:"<<sVal.c_str()<<"\n";
	//
	//	// returns pointer to next child node. This function can be
	//	// Used to traverse through all the child nodes of a particular node.
	//			NodePtr2 = NodePtr->GetNextChild();
	//		}
	//	// reset´the variable used to traverse. Call this function if you are going to
	//	// parse throgh the xml file again and again.
	//		XMLDoc.ResetReading(); 
	//
	//	// Explicit call to delete the dom structure. (Called again in desstructor);
	//		XMLDoc.DeleteAll();
	//
	//
	system("pause");
	return 0;
}

