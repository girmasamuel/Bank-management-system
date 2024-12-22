#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

class BankAccount {
public:
    long long accountNumber;
    std::string accountHolderName;
    double balance;

    //constructor
    BankAccount(int number, std::string name, double initialBalance) {
        accountNumber = number;
        accountHolderName = name;
        balance = initialBalance;
    }
};

#endif