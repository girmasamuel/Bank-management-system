#ifndef BANK_ACCOUNT_MANAGEMENT_SYSTEM_H
#define BANK_ACCOUNT_MANAGEMENT_SYSTEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "./binary_tree.h"


class BankAccountManagementSystem {
private:
    BinaryTree binaryTree;

public:
    BankAccountManagementSystem();
    int countWordsInStream(std::istringstream &iss);
    void loadAccountsFromFile();
    void saveAccountsToFile();
    void createAccount();
    void updateAcccount();
    void deposit();
    void withdraw();
    void displayBalance();
    void removeAccount(); 
};

#endif