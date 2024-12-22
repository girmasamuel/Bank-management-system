#include <iostream>

//local dependecies
#include "./headers/transaction_stack.h"
#include "./headers/graphics.h"
#include "./headers/bank_system.h"

using namespace std;



int main(){
    char option;
    BankAccountManagementSystem system;

    while(true){
        dash_board();
        cout << RED+"[1]"+BLUE+" Create Account\n";
        cout << RED+"[2]"+BLUE+" Deposit\n";
        cout << RED+"[3]"+BLUE+" Withdraw\n";
        cout << RED+"[4]"+BLUE+" Display Balance\n";
        cout << RED+"[5]"+BLUE+" Remove Account\n";
        cout << RED+"[6]"+BLUE+" Exit\n";

        cout << "\nEnter your choice "+RED+"(1-6)"+BLUE+": ";
        cin >> option;
        
        if(option == '1'){
            dash_board();
            system.createAccount();
            system.saveAccountsToFile();
            navigation_option();      
        }
        else if (option == '2'){
            dash_board();
            system.deposit();
            system.saveAccountsToFile();
            navigation_option();
            
        }
        else if(option == '3'){
            dash_board();
            system.withdraw();
            system.saveAccountsToFile();
            navigation_option();   
        }

        else if(option == '4'){
            dash_board();
            system.displayBalance();
            navigation_option();
           
        }
        else if(option == '5'){
            dash_board();
            system.removeAccount();
            system.saveAccountsToFile();
            navigation_option();
        }
        else if(option == '6'){
            cout << "Exiting..." << endl;
            freeMemory();
            exit(0);    
        }
        else{
            cout << "Invalid choice. Please try again!" << endl;
        }   
    }
    return 0;
}