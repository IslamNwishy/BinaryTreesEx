#ifndef BinaryTree_H
#define BinaryTree_H
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 5
//Filename: BinaryTree.h


template<class KeyType, class DataType>
class BinaryTree {

public:

	//Constructor and Destructor
	BinaryTree();
	~BinaryTree();

	//Public Functions
	bool Insert(const KeyType &, const DataType &);
	bool Empty();
	bool Search(const KeyType &) const;
	DataType Retrive(const KeyType&);
	void Traverse();
	void Traverse( ofstream&);
	void PreOrder();
	void LevelOrder();
	bool Remove(const KeyType&);
	bool Update(const KeyType&, const DataType&);
	void DeleteTree();
	void ReverseRetrive(const DataType&);


private:

	//Tree Node
	class TreeNode {
	public:
		KeyType key;
		DataType data;
		TreeNode *Right;
		TreeNode *Left;
	};

	typedef TreeNode* Node;
	Node Root;

	//Private Functions
	bool Insert2(Node&, const KeyType&, const DataType&);
	bool Search2(Node&, const KeyType&) const;
	DataType Retrive2(Node&, const KeyType&) const;
	void Traverse2(Node&) const;
	void Traverse2(Node&, ofstream&);
	void PreOrder2(Node&) const;
	void LevelOrder2(Node&);
	bool PrintLevel(Node&, int);
	bool PrintLevel2(Node&, int, ofstream&);
	bool Remove2(const KeyType&);
	bool FindParent(Node&, Node&, const KeyType&);
	void FindMin(Node&, Node&);
	void FindMax(Node&, Node&);
	bool Update2 (Node&, const KeyType&, const DataType&);
	void DeleteTree2(Node&);
	void ReverseRetrive2(Node&, const DataType&);



};
#endif // !BinaryTree_H

