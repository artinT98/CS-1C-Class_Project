#include "BankAccount.h"

#pragma once

//DerivedClass
//  BankAccount-> CertificateOfDeposit
class CertificateOfDeposit : public BankAccount {
    double interestRate;
    int maturityMonths;
    int currentMonth;

public:
    // Constructor
    CertificateOfDeposit(double bal, const std::string& accName, int accNum)
        : BankAccount(bal, accName, accNum), interestRate(0.0175), maturityMonths(6), currentMonth(0) {}

    // Destructor
    ~CertificateOfDeposit() {}

    //Withdraw (Override BankAccount)
    void withdraw(double amount) override {
        if (currentMonth >= maturityMonths) {
            if (getBalance() >= amount) {
                deposit(-amount);
            } else {
                std::cout << "Insufficient funds\n";
            }
        } else {
            std::cout << "Cannot withdraw before maturity\n";
        }
    }

    //AddInterest()
    void addInterest() {
        deposit(getBalance() * interestRate);
    }

    //MonthlyStatement (Override BankAccount)
    void createMonthlyStatement() override {
        if (currentMonth < maturityMonths) {
            addInterest();
        }
        currentMonth++;
        std::cout << "Creating monthly statement for CertificateOfDeposit\n";
        display();
    }
};
