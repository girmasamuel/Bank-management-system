#ifndef NODE_H
#define NODE_H

#include "./bank_account.h"

class Node {
public:
    BankAccount* account;
    Node* left;
    Node* right;

    Node(BankAccount* acc) {
        account = acc;
        left = NULL;
        right = NULL;
    }
};

#endif