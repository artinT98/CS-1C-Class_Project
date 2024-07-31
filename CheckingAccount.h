#include "BankAccount.h"

#pragma once

//Description:
/****************************************************/
/*               CheckingAccount                    */
/* ServiceChargeChecking    NoServiceChargeChecking */
/*                           HighInterestCheckign   */
/****************************************************/

//Class is Abstract
//Base & Derived Class
//  BankAccount -> CheckingAccount -> ServiceChargeeChecking & NoServiceChargeChecking
class CheckingAccount : public BankAccount {
public:
    //Constructor
    CheckingAccount(double bal, const std::string& accName, int accNum)
        : BankAccount(bal, accName, accNum) {}

    //Deconstructor
    virtual ~CheckingAccount() {} // or virtual ~CheckingAccount() override = default;


    virtual void writeCheck(double amount) = 0;  // Pure virtual
};

/****************************************************************************************************************/

//DerivedClass
//  BankAccount-> CheckingAccount -> ServiceChargeChecking
class ServiceChargeChecking : public CheckingAccount {
    const int MAX_CHECKS = 10;
    int checksWritten = 0;

public:
    //Constructor
    ServiceChargeChecking(double bal, const std::string& accName, int accNum)
        : CheckingAccount(bal, accName, accNum) {}

    //Deconstructor
    ~ServiceChargeChecking() {}

    int getChecksWritten() const { return checksWritten; }

    //Write Check (Override CheckingAccount)
    void writeCheck(double amount) override {
        if (checksWritten < MAX_CHECKS) {
            if (getBalance() >= amount) {
                deposit(-amount);
                ++checksWritten;
                std::cout << "Check written for: " << amount << "\n";
            } else {
                std::cout << "Insufficient funds\n";
            }
        } else {
            std::cout << "Check limit reached\n";
        }
    }

    //Withdraw (Override BankAccount)
    void withdraw(double amount) {
        if (getBalance() >= amount) {
            deposit(-amount);
        } else {
            std::cout << "Insufficient funds\n";
        }
    }

    //MonthlyStatement (Override BankAccount)
    void createMonthlyStatement() {
        std::cout << "Creating monthly statement for ServiceChargeChecking\n";
        display();
        checksWritten = 0; // Reset checks count
    }
};

/****************************************************************************************************************/

//Base & Derived Class
//  CheckingAccount -> NoServiceChargeChecking -> HighInterestChecking
class NoServiceChargeChecking : public CheckingAccount {
protected:
    double interestRate;
    double minimumBalance;

public:
    // Constructor
    NoServiceChargeChecking(double bal, const std::string& accName, int accNum)
    : CheckingAccount(bal, accName, accNum) {
            interestRate = 0.01; // Default average interest rate for a checking account
            minimumBalance = 100.0; // Default minimum balance
    }

    // Destructor
    ~NoServiceChargeChecking() {}

    //Write Check (Override CheckingAccount)
    void writeCheck(double amount) {
        if (getBalance() >= amount) {
            deposit(-amount);
            std::cout << "Check written for: " << amount << "\n";
        } else {
            std::cout << "Insufficient funds\n";
        }
    }

    //Withdraw (Override BankAccount)
    void withdraw(double amount) {
        if (getBalance() - amount >= minimumBalance) {
            deposit(-amount);
        } else {
            std::cout << "Insufficient funds or below minimum balance\n";
        }
    }

    //AddInterest()
    void addInterest() {
        deposit(getBalance() * interestRate);
    }

    //MonthlyStatement (Override BankAccount)
    void createMonthlyStatement() {
        addInterest();
        std::cout << "Creating monthly statement for NoServiceChargeChecking\n";
        display();
    }
};

/****************************************************************************************************************/

//Derived Class
//  CheckingAccount -> NoServiceChargeChecking -> HighInterestChecking
class HighInterestChecking : public NoServiceChargeChecking {
public:
    //Constructor
    HighInterestChecking(double bal, const std::string& accName, int accNum)
        : NoServiceChargeChecking(bal, accName, accNum) {
            interestRate = 0.025; // Higher interest rate for high-interest checking account
            minimumBalance = 500.0; // Higher minimum balance
        }

    //Deconstructor
    ~HighInterestChecking() {}

    //MonthlyStatement (Override BankAccount)
    void createMonthlyStatement() {
        addInterest();
        std::cout << "Creating monthly statement for HighInterestChecking\n";
        display();
    }
};
