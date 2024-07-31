#include "BankAccount.h"

#pragma once

/************************************/
/*          Savings Account         */
/*         HighInterestSavings      */
/************************************/

//Base & Derived Class
//  BankAccount -> SavingsAccount
class SavingsAccount : public BankAccount {
protected:
    double interestRate;

public:
    // Constructor
    SavingsAccount(double bal, const std::string& accName, int accNum)
    : BankAccount(bal, accName, accNum) {
        interestRate = 0.0175;
    }

    // Destructor
    virtual ~SavingsAccount() {}

    //Withdraw (Override BankAccount)
    void withdraw(double amount) {
        if (getBalance() >= amount) {
            deposit(-amount);
        } else {
            std::cout << "Insufficient funds\n";
        }
    }

    //AddInterest()
    virtual void addInterest() {
        deposit(getBalance() * interestRate);
    }

    //MonthlyStatement (Override BankAccount)
    void createMonthlyStatement() {
        addInterest();
        std::cout << "Creating monthly statement for SavingsAccount\n";
        display();
    }
};

/****************************************************************************************************************/

class HighInterestSavings : public SavingsAccount {
    double minimumBalance;

public:
    // Constructor
    HighInterestSavings(double bal, const std::string& accName, int accNum)
    : SavingsAccount(bal, accName, accNum) {
            minimumBalance = 1000;
            interestRate = 3.5;
        }

    // Destructor
    ~HighInterestSavings() {}

    //Withdraw (Override BankAccount & SavingsAccount)
    void withdraw(double amount) override {
        if (getBalance() - amount >= minimumBalance) {
            deposit(-amount);
        } else {
            std::cout << "Insufficient funds or below minimum balance\n";
        }
    }
};

