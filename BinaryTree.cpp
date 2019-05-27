#include "BinaryTree.h"
using namespace std;

//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 5
//Filename: BinaryTree.cpp


//Constructor
template<class KeyType, class DataType>
BinaryTree<KeyType, DataType>::BinaryTree() {
	Root = NULL;
}

//Destructor
template<class KeyType, class DataType>
BinaryTree<KeyType, DataType>::~BinaryTree() {
	DeleteTree();
	delete Root;
}

//Public Insert Function returns true if it manages to insert the element
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Insert(const KeyType& Key, const DataType& Data) {
	return Insert2(Root, Key, Data);
}

//Private Insert Function that does the process
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Insert2(Node& aRoot, const KeyType& Key, const DataType& Data) {

	//If the node is empty, insert the data and return true
	if (aRoot == NULL) {
		aRoot = new TreeNode;
		aRoot->key = Key;
		aRoot->data = Data;
		aRoot->Right = NULL;
		aRoot->Left = NULL;
		return true;
	}
	else if (Key == aRoot->key) //if the node is equal to the key one but full return false
		return false;
	else if (Key < aRoot->key)	//if the node is greater then the key go left
		Insert2(aRoot->Left, Key, Data);
	else						//if the node is less than the key go right
		Insert2(aRoot->Right, Key, Data);
}

//Returns true if the Root is empty
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Empty()
{
	if (Root == NULL)
		return true;
	else
		return false;
}


//Public Search Function returns true if the process is completed
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Search(const KeyType& Key) const {
	return Search2(Root, Key);
}


//private search function that actually does the process
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Search2(Node& aRoot, const KeyType& Key) const
{
	if (aRoot == NULL)				//if the root is empty return false
		return false;
	else if (Key == aRoot->key)		//if the key is the node's key then you find the element
		return true;
	else if (Key < aRoot->key)		//if the node is greater than the key go left
		Search2(aRoot->Left, Key);
	else							//if the node is less than the key go right
		Search2(aRoot->Right, Key);
}

//Public Retrieve funtion that takes a key and returns its data from the tree
template<class KeyType, class DataType>
DataType BinaryTree<KeyType, DataType>::Retrive(const KeyType& Key)
{
	return Retrive2(Root, Key);
}

//Private Retrieve function that actually does the process
template<class KeyType, class DataType>
DataType BinaryTree<KeyType, DataType>::Retrive2(Node& aRoot, const KeyType& Key) const
{
	if (aRoot == NULL)						//if the node is null then the element doesn't exist
		return NULL;
	else if (Key == aRoot->key)				//if the key is the node's key then you found the element and return its data
		return aRoot->data;
	else if (Key < aRoot->key)				//if the key is smaller than the node go left
		Retrive2(aRoot->Left, Key);
	else									//if the key is  greater than the node go right
		Retrive2(aRoot->Right, Key);
}

//calls the funciton that traverses the tree and outputs it to the screen
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::Traverse()
{
	Traverse2(Root);
}

//Calls the function that traverses the tree and outputs it to a file (Overloaded)
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::Traverse(ofstream& output)
{
	Traverse2(Root,output);
}

//Traverses the tree in order and outputs its values to the screen
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::Traverse2(Node& aRoot) const
{
	if (aRoot != NULL) {
		Traverse2(aRoot->Left);
		cout << aRoot->key<<"\t\t" <<aRoot->data << endl;
		Traverse2(aRoot->Right);
	}
		
}

//Traverses the tree in level order
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::Traverse2(Node& aRoot, ofstream& output) 
{
	if (aRoot == NULL) //if the tree is empty return
		return;
	for (int lvl = 1; PrintLevel2(aRoot, lvl, output); lvl++) //printout level by level
		cout << endl;
}


//prints out a level
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::PrintLevel2(Node& aRoot, int lvl,ofstream& output) {
	if (aRoot == NULL) //if a node is empty return false
		return false;
	
	if (lvl == 1) { //if it is the desired level output it
		output << endl << aRoot->key << ',' << aRoot->data;
		return true;
	}

	//look at the left and right nodes of the level
	bool left = PrintLevel2(aRoot->Left, lvl - 1,output);
	bool right = PrintLevel2(aRoot->Right, lvl - 1,output);

	return (left || right);
}

//Public function that calls a private function to traverse the tree in preorder
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::PreOrder()
{
	PreOrder2(Root);
}

//private function that traverses the tree in preorder and outputs its values to the screen
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::PreOrder2(Node& aRoot) const
{
	if (aRoot != NULL) {
		cout << aRoot->key << "\t\t" << aRoot->data << endl;
		PreOrder2(aRoot->Left);
		PreOrder2(aRoot->Right);
		
	}
}

//public function that calls another function to traverse the tree in levelorder
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::LevelOrder()
{
	LevelOrder2(Root);
}

//private function that traverses and prints out the nodes to the screen in levelorder
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::LevelOrder2(Node& aRoot)
{
	if (aRoot == NULL)
		return;
	for (int lvl = 1; PrintLevel(aRoot, lvl); lvl++)
		cout << endl;

}

//Check PrintLevel2()
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::PrintLevel(Node& aRoot, int lvl) {
	if (aRoot == NULL)
		return false;
	if (lvl == 1) {
		cout << aRoot->key << "\t\t";
		return true;
	}
	bool left = PrintLevel(aRoot->Left, lvl - 1);
	bool right = PrintLevel(aRoot->Right, lvl - 1);

	return (left || right);
}


//Public function that takes a key to remove it
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Remove(const KeyType& Key)
{
	return Remove2(Key);
}

//private function that takes a key and removes it
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Remove2(const KeyType& Key)
{
	Node Child = new TreeNode;
	Child = Root;
	Node Parent = new TreeNode;
	Parent = NULL;

	if (!FindParent(Parent, Child, Key))				//Find the parent of the key and name the key node child
		return false;									//if you can't return false
	
	if (Child->Right != NULL && Child->Left != NULL) {	//if the child has 2 childern
		Node SX = new TreeNode;
		Parent = Child;
		SX = Child->Right;								//find its inorder successor
		FindMin(SX, Parent);

		Child->data = SX->data;							//Switch the contents of Child with the successor
		Child->key = SX->key;
		if (Parent->Right == SX)						//Make its parent point at Null;
			Parent->Right = NULL;
		else
			Parent->Left = NULL;

		Child = SX;										//Make the child point at the successor
	}

	else {												//if the child has 1 or no childern
		Node S = new TreeNode;
		if (Child->Right != NULL)						//Make the successor point at the exisitnig child, if any.
			S = Child->Right;
		else
			S = Child->Left;

		if (Parent == NULL) {							//if the node in question is the root
			if (S == NULL)								//if it has no childern make the root =null
				Root = NULL;
			else
				Root = S;								//if it has a child make the root point to that child
		}
		else {											//if it is not the root
			if (Parent->Right == Child)					//if its the right child of the parent, make the parent right pointer point to S
				Parent->Right = S;
			else
				Parent->Left = S;						//if its the left child of the parent, make the parent left pointer point to S
		}
	}
	delete Child;										//delete the child now that it is isolated

	
}

//Find the parent of a certain Child that has a given key
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::FindParent(Node& Parent, Node& Child, const KeyType& Key)
{
	bool found = false;
	while (!found && Child != NULL) {
		if (Key < Child->key) {
			Parent = Child;
			Child = Child->Left;
		}
		else if (Key > Child->key) {
			Parent = Child;
			Child = Child->Right;
		}
		else
			found = true;
	}
	return found;
}

//Find the minimum node starting from a given child
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::FindMin(Node& Child, Node& Parent)
{

	while (Child->Left != NULL) {
			Parent = Child;
			Child = Child->Left;
	}
	if (Child->Right != NULL) {
		Parent = Child;
		Child = Child->Right;
		FindMin(Child, Parent);
	}
	
}

//find the maximaum node starting from a given node
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::FindMax(Node& Child, Node& Parent)
{
	while (Child->Right != NULL) {
		Parent = Child;
		Child = Child->Right;
	}
}

//public function that updates a certain entry
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Update(const KeyType& Key, const DataType& Data)
{
	return Update2(Root, Key, Data);
}

//Searches and updates a certain entry if found
template<class KeyType, class DataType>
bool BinaryTree<KeyType, DataType>::Update2 (Node& aRoot, const KeyType& Key, const DataType& Data)
{
	if (aRoot == NULL)
		return false;
	else if (Key == aRoot->key)
		aRoot->data = Data;
	else if (Key < aRoot->key)
		Update2(aRoot->Left, Key,Data);
	else
		Update2(aRoot->Right, Key,Data);
	return true;

}

//calls a function deletes the whole tree and then sets Root to NULL
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::DeleteTree()
{
	DeleteTree2(Root);
	Root = NULL;
}

//Traverses the tree and deletes each node
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::DeleteTree2(Node& aRoot)
{
	if (aRoot == NULL)
		return;
	
	DeleteTree2(aRoot->Right);
	DeleteTree2(aRoot->Left);

	delete aRoot;
}


//a public function that finds a key based on its data
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::ReverseRetrive(const DataType& data)
{
	ReverseRetrive2(Root, data);
}

//traverses the whole tree and if the data is <= the given data it outputs it to the screen
template<class KeyType, class DataType>
void BinaryTree<KeyType, DataType>::ReverseRetrive2(Node& aRoot, const DataType& Data)
{
	if (aRoot != NULL) {
		if (aRoot->data >= Data)
			cout << aRoot->key << endl;
		ReverseRetrive2(aRoot->Left, Data);
		ReverseRetrive2(aRoot->Right, Data);

	}

}



