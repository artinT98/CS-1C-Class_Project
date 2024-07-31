// BankAccountWrapper.h
#pragma once
#include <memory>
#include <string>
#include <iostream>

//Wrapper Class
class BankAccountWrapper {
    public:
    //Template Constructor (Type Erasure)
    template <typename T> 
    BankAccountWrapper(const T& acc) : account(new BankAccountAdapter<T>(acc)) {} //Binds object to BankAccountAdapter (Then Bound to IBankAccount)

    //Default Constructor
    BankAccountWrapper() : account(nullptr) {}

    // Move Constructor
    BankAccountWrapper(BankAccountWrapper&& other) noexcept = default;

    // Move Assignment Operator
    BankAccountWrapper& operator=(BankAccountWrapper&& other) noexcept = default;

    //BankAccount public functions list.
    void        deposit(double amount)    { account->deposit(amount); }
    void        withdraw(double amount)   { account->withdraw(amount); }
    void        createMonthlyStatement()  { account->createMonthlyStatement(); }
    void        display()           const { account->display(); }
    double      getBalance()        const { return account->getBalance(); }
    std::string getName()           const { return account->getName(); }
    int         getAccountNumber()  const { return account->getAccountNumber(); }

    //Deconstructor
    ~BankAccountWrapper() = default;

    //InterfaceClass
    class IBankAccount {
    public:
        virtual ~IBankAccount() = default;
        virtual void deposit(double amount) = 0;
        virtual void withdraw(double amount) = 0;
        virtual void createMonthlyStatement() = 0;
        virtual void display() const = 0;
        virtual double getBalance() const = 0;
        virtual std::string getName() const = 0;
        virtual int getAccountNumber() const = 0;
    };

    //AdapterClass
    template <typename T>
    class BankAccountAdapter : public IBankAccount {
        T obj; //Copy of object
    public:
        //(Copy) Constructor
        BankAccountAdapter(const T& acc) : obj(acc) {}

        //BankAccountFunctions
        void        deposit(double amount)   override { obj.deposit(amount); }
        void        withdraw(double amount)  override { obj.withdraw(amount); }
        void        createMonthlyStatement() override { obj.createMonthlyStatement(); }
        void        display()          const override { obj.display(); }
        double      getBalance()       const override { return obj.getBalance(); }
        std::string getName()          const override { return obj.getName(); }
        int         getAccountNumber() const override { return obj.getAccountNumber(); }
    };

    std::unique_ptr<IBankAccount> account;
};