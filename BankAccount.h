#include <iostream>
#include <string>

#pragma once

//Description:
/********************************************************/
/*                      BankAccount                     */
/* CheckingAccount   CertificateOfDepost SavingsAccount */
/********************************************************/

//Class is Abstract
//Base Class 
class BankAccount {
    private:
        double balance;
        std::string name;
        int accountNumber;

    public:
        //Constructor
        BankAccount(double bal, const std::string& accName, int accNum)
        : balance(bal), name(accName), accountNumber(accNum) {}

        //Deconstructor
        virtual ~BankAccount() {}

        //Getters()
        double getBalance() const { return balance; }
        std::string getName() const { return name; }
        int getAccountNumber() const { return accountNumber; }

        //Deposit()
        void deposit(double amount) { balance += amount; }

        //Pure Virtuals
        virtual void withdraw(double amount) = 0;  // Pure virtual
        virtual void createMonthlyStatement() = 0; // Pure virtual

        //Display()
        virtual void display() const { std::cout
                  << "Name: " << name << "\n"
                  << "Account Number: " << accountNumber << "\n"
                  << "Balance: " << balance << "\n\n";
        }
};