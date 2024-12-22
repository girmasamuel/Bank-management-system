#include "../headers/transaction_stack.h"
#include <iostream>


stack_node* start = nullptr; // Initialize to nullptr

// Function to create a new transaction and push it onto the stack.
Transaction* record_transaction(const std::string& type, double amount) {
    Transaction* newTransaction = new Transaction{type, amount, nullptr};
    return newTransaction;
}

// Function to push a transaction onto the stack for a specific account.
void append_history(long long acc_number, const std::string& type, double amount) {
    Transaction* newTransaction = record_transaction(type, amount);
    stack_node* current = start;
    stack_node* previous = nullptr;

    while (current != nullptr && current->acc_number != acc_number) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr && current->acc_number == acc_number) {
        // Account found, push onto existing stack
        newTransaction->next = current->transaction;
        current->transaction = newTransaction;
    } 
    else {
        // Account not found, create a new node
        stack_node* newNode = new stack_node{acc_number, newTransaction, current};
        if (previous == nullptr) {
            start = newNode;
        } else {
            previous->next = newNode;
        }
    }
}


// Function to print the transaction history for a specific account.
void print_transaction_history(long long acc_number) {
    stack_node* current = start;
    while (current != nullptr) {
        if (current->acc_number == acc_number) {
            Transaction* transaction = current->transaction;
            if (transaction == nullptr) {
                std::cout << "No transactions for this account.\n";
                return;
            }
            while (transaction != nullptr) {
                std::cout << "Type: " << transaction->type << "\tAmount: $" << transaction->amount << "\n";
                Transaction* next = transaction->next;
                delete transaction; // Free memory
                transaction = next;
            }
            return;
        }
        current = current->next;
    }
    std::cout << "Account not found.\n";
}


// Function to free all allocated memory.  Crucial to prevent leaks!
void freeMemory() {
    stack_node* current = start;
    stack_node* next;
    while (current != nullptr) {
        next = current->next;
        Transaction* transaction = current->transaction;
        while (transaction != nullptr) {
            Transaction* temp = transaction;
            transaction = transaction->next;
            delete temp;
        }
        delete current;
        current = next;
    }
    start = nullptr;
}