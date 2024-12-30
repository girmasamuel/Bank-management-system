#include "../headers/transaction_stack.h"
#include <iostream>
#include <iomanip>

//geting time
std::string setDate(){
    time_t now = time(0);
    tm* current_time = localtime(&now);
    int year =  1900 + current_time->tm_year;
    int month = 1 + current_time->tm_mon;
    int day = current_time->tm_mday;
    int hour = current_time->tm_hour;
    int minute = current_time->tm_min;
    int second = current_time->tm_sec;

    std::string Date = "Date:  "+std::to_string(year)+"/"+std::to_string(month)+"/"+std::to_string(day);
    std::string Time = "Time:  "+std::to_string(hour)+":"+std::to_string(minute)+":"+std::to_string(second);
    
    return Date+"   "+Time;
}

stack_node* start = nullptr; // Initialize to nullptr

// Function to create a new transaction and push it onto the stack.
Transaction* record_transaction(const std::string& type, double amount) {
    Transaction* newTransaction = new Transaction{type, amount,setDate(), nullptr};
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
                std::cout << "Type: " <<std::left<<std::setw(15)<<transaction->type<<"\t|   Amount: $" << transaction->amount << "\t"<< transaction->time << "\n";
                Transaction* next = transaction->next;
                transaction = next;
            }
            return;
        }
        current = current->next;
    }
    std::cout << "Account not found.\n";
}
