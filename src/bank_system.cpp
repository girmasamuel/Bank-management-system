//standard libraries
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <filesystem>


//local libararies
#include "../headers/bank_system.h"
#include "../headers/binary_tree.h"
#include "../headers/graphics.h"
#include "../headers/transaction_stack.h"


//data base/filessystem in our case/ path
std::filesystem::path account_path = std::filesystem::path("../database")/"accounts.txt";
std::filesystem::path accountNo_path = std::filesystem::path("../database")/"account_numbers.txt";

BankAccountManagementSystem::BankAccountManagementSystem(){
    binaryTree = BinaryTree();
    loadAccountsFromFile();
};

int BankAccountManagementSystem::countWordsInStream(std::istringstream &iss){
    std::streampos originalPos = iss.tellg();
    std::string word;
    int wordCount = 0;

    while (iss >> word)
    {
    wordCount++;
    }

    // Reset the stream position to the original position
    iss.clear();
    iss.seekg(originalPos);

    return wordCount;
}

void BankAccountManagementSystem::loadAccountsFromFile() {
    std::ifstream file(account_path);      
    if (file.is_open()) {
        std::string line;
        std::getline(file,line);
        while (getline(file, line)) {
            std::istringstream iss(line);
            int accountNumber;
            std::string hold;
            std::string accountHolderName,sbalance;
            double balance;
            iss>>hold;
            std::istringstream(hold) >> accountNumber;
            
            if(countWordsInStream(iss)>=3){
                std::string firstName, lastName;
                iss>>firstName;
                iss>>lastName;
                accountHolderName = firstName +" "+ lastName;
                accountHolderName=accountHolderName;
            }
            else{
                iss >> accountHolderName;
            }
            iss>> sbalance;
            std::istringstream(sbalance) >> balance;
            BankAccount* account = new BankAccount(accountNumber, accountHolderName, balance);
            binaryTree.insertNode(account);
        }
        file.close();
        std::cout << "Accounts loaded from file successfully.\n";
    } else {
        std::cout << "Error: Unable to open file.\n";
    }
}

void BankAccountManagementSystem::saveAccountsToFile() {
        std::ofstream file(account_path);
        if (file.is_open()){
            binaryTree.inorderTraversalHead(file);
            file.close();
        }
         else {
            std::cout << "Error: Unable to open file.\n";
        }
}
//................................new
long long generateAccountNumber() {
  long long nextAccountNumber;
  std::ifstream inputFile(accountNo_path); // Read last account number from file

  if (inputFile.is_open()) {
    inputFile >> nextAccountNumber;
    inputFile.close();
  } else {
    nextAccountNumber = 10000; // Start at 1000 if the file doesn't exist
  }
  nextAccountNumber++;
  std::ofstream outputFile(accountNo_path); // Write the updated account number
  if (outputFile.is_open()) {
    outputFile << nextAccountNumber;
    outputFile.close();
  } else {
    std::cerr << "Error writing account number to file!" << std::endl;
  }

  return nextAccountNumber;
}
//................................

void BankAccountManagementSystem::createAccount() {
    int accountNumber; 
    std::string accountHolderName;
    double initialBalance;

    accountNumber = generateAccountNumber();
    std::cout << "Enter Account Holder Name: ";
    std::cin.ignore(100,'\n');
    std::getline(std::cin, accountHolderName);
    std::cout << "Enter Initial Balance: ";
    std::cin>>initialBalance;
    
    BankAccount* account = new BankAccount(accountNumber, accountHolderName, initialBalance);
    binaryTree.insertNode(account);
    append_history(accountNumber,"Initial deposit",initialBalance);
    
    clear_console();
    std::cout<< "Account created successfully.\n";
    delay_time(3);
    dash_board();
    std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
    std::cout<< "The account number is: "<< accountNumber<<std::endl;
    std::cout<< "The account holder name is: "<< accountHolderName<<std::endl;
    std::cout<< "The account initial balance is: "<< initialBalance<<std::endl;
    std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
    
}

//function to deposit to bank account
void BankAccountManagementSystem::deposit() {
    int accountNumber;
    double amount;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    Node* node= binaryTree.searchNode(accountNumber);
    if (node != NULL)
        {
        std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
        std::cout << "The account holder name is: " << node->account->accountHolderName<<std::endl;
        std::cout << "Enter Amount to Deposit: ";
        std::cin >> amount;
        append_history(accountNumber,"deposit",amount);
        node->account->balance += amount;
        std::cout << "Deposit successful. New balance: " << node->account->balance<<std::endl;
        std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
    } else {
        std::cout << "Account not found.\n";
    }
}

//function to withdraw balace from account
void BankAccountManagementSystem::withdraw() {
    int accountNumber;
    double amount;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    
    Node* node=binaryTree.searchNode(accountNumber);
    std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
    if (node != NULL) {
        std::cout<<"Account holder name is: "<< node->account->accountHolderName<<std::endl;
        std::cout<<"Account balance is: "<< node->account->balance<<std::endl;
        std::cout << "Enter Amount to Withdraw: ";
        std::cin >> amount;
        if (node->account->balance >= amount) {
            node->account->balance -= amount;
            std::cout << "Withdrawal successful. New balance: " << node->account->balance << std::endl;
            append_history(accountNumber,"withdraw",amount);
        }
        else {
            std::cout << "Insufficient balance.\n";
        }
    std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
    } else {
        std::cout << "Account not found.\n";
    }
}

void BankAccountManagementSystem::displayBalance() {
    int accountNumber;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    Node* node=binaryTree.searchNode(accountNumber);
    if (node != NULL) {
        std::cout<<YELLOW+"---------------------------------------------------------------------------------------------\n"+BLUE;
        std::cout << "Account Number: " << node->account->accountNumber << std::endl;
        std::cout << "Account Holder: " << node->account->accountHolderName << std::endl;
        std::cout << "Balance: " << node->account->balance << std::endl;
        std::cout << "Transaction history: \n"+GREEN;
        print_transaction_history(accountNumber);
        std::cout<<YELLOW+"---------------------------------------------------------------------------------------------\n"+BLUE;
    } else {
        std::cout << "Account not found." << std::endl;
	}
}
void BankAccountManagementSystem::removeAccount(){
    int accountNumber;
    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;
    Node *node = binaryTree.searchNode(accountNumber);
    std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
    if(node!=NULL){
        std::cout << "Account holder: " << node->account->accountHolderName;
        binaryTree.removeNode(accountNumber);
        std::cout<< " has been removed successfully." << std::endl;
    }
    else{
        std::cout<<"Account Number not Found"<<std::endl;
    }
    std::cout<<YELLOW+"--------------------------------------------------\n"+BLUE;
}