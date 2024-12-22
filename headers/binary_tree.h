#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <fstream>

#include "./node.h"
#include "./bank_account.h"

class BinaryTree {
public:
    Node* root;
	BinaryTree();
    void insertNode(BankAccount* account);
 	void inorderTraversal(Node* node, std::ofstream& file);
    void inorderTraversalHead(std::ofstream& file);
    Node* searchNode(int accountNumber);
	void removeNode(float accountNumber);
	Node* removeNodeHelper(Node* node, int accountNumber);
    Node* findMinNode(Node* node);
    Node* findMaxNode(Node* node);
};

#endif