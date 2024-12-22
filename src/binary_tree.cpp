#include "../headers/binary_tree.h"
#include "../headers/node.h"
#include "../headers/bank_account.h"
#include <iomanip>

BinaryTree::BinaryTree() {
    root = NULL;
};

void BinaryTree::insertNode(BankAccount* account){
    Node* newNode = new Node(account);
    if (root == NULL){
        root = newNode;
    }
    else {
        Node* current = root;
        Node* parent;
        while (true) {
            parent = current;
            if (account->accountNumber < current->account->accountNumber) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return;
                }
            }
            else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return;
                }
            }
        }
    }
};

void BinaryTree::inorderTraversal(Node* node, std::ofstream& file) {
    if (node == NULL) {
        return;
    }
    inorderTraversal(node->left, file);
    file <<std::setw(20)<<std::left<<node->account->accountNumber<<std::setw(30)<<std::left
    <<node->account->accountHolderName<<std::setw(30)<<std::left
    <<node->account->balance<<std::endl;
    inorderTraversal(node->right, file);
}


void BinaryTree::inorderTraversalHead(std::ofstream& file) {
    file <<std::setw(20)<<std::left<<"Account Number" <<std::setw(30) <<std::left << "Name" <<std::setw(30) <<std::left<< "Balance" <<std::endl;
    inorderTraversal(root, file);
}

Node* BinaryTree::searchNode(int accountNumber) {
    Node* current = root;
    while (current != NULL) {
        if (current->account->accountNumber == accountNumber) {
            return current;
        }
        if (accountNumber < current->account->accountNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}

void BinaryTree::removeNode(float accountNumber) {
    root = removeNodeHelper(root, accountNumber);
}

Node* BinaryTree::removeNodeHelper(Node* node, int accountNumber) {
    if (node == NULL) {
        return node;
    }

    if (accountNumber < node->account->accountNumber) {
        node->left = removeNodeHelper(node->left, accountNumber);
    }
    else if (accountNumber > node->account->accountNumber) {
        node->right = removeNodeHelper(node->right, accountNumber);
    }
    else {
        if (node->left == NULL) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        Node* temp = findMinNode(node->right);
        if (temp==NULL){
            temp= findMaxNode(node->left);
        }
        node->account = temp->account;
        delete temp;
    }
    return node;
}

Node* BinaryTree::findMinNode(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

 Node* BinaryTree::findMaxNode(Node* node){
	while(node->right!= NULL){
		node=node->right;
	}
	return node;
};
