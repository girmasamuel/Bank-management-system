#ifndef TRANSACTION_STACK_H
#define TRANSACTION_STACK_H

#include <string>
#include "bank_account.h"

//transaction stack history for each account
struct Transaction {
    std::string type;
    double amount;
    std::string time;
    Transaction* next;
};

//linked list for stroring each account transaction stack
struct stack_node{
    long long acc_number;
    Transaction* transaction;
    stack_node* next;
};

//Transaction* record_transaction(std::string type);
void print_transaction_history(long long acc_number);
void append_history(long long acc_number, const std::string& type, double amount);


#endif