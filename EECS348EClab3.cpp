#include <iostream>
#include <string>
//class for Account
class Account {
public:
    std::string accountNumber;
    std::string accountHolder;
    double balance;
    //constructor
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    void displayDetails() const { //definition for display details for account
        std::cout << "Account Details for Account (ID: " << accountNumber << "):" << std::endl;
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }

    void deposit(double amount) { //function definition for deposit
        if (amount > 0){
            balance += amount;
        } else {
            std::cout << "Please enter in a valid amount" << std::endl;
        }
    }

    virtual void withdraw(double amount) { //function definition for withdraw (will soon be taken over by the two with)
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient amount." << std::endl;
        }
    }
};
//class for the savings account that derives off of the base class Account
class SavingsAccount : public Account {
public:
    double interestRate;
    //constructor
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void withdraw(double amount) override { //withdraw function for SavingsAccount that overrides the Account class
        const double minBalance = 25.0; //just made up a random minBalance (I don't think its specified in the instructions)
        if (balance - amount >= minBalance) {
            balance -= amount;
        } else {
            std::cout << "Invalid funds, as you surpassed the minimum balance with this withdraw" << std::endl;
        }
    }
};
//class for CurrentAccount that is inherited from Account
class CurrentAccount : public Account {
public:
    double overdraftLimit;
    //constructor
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override { //withdraw function that overrides the account withdraw
        if (balance - amount >= -overdraftLimit) {
            balance -= amount;
        } else {
            std::cout << "Exceeded overdraft limit. Cannot withdraw $" << amount << "." << std::endl;
        }
    }
};
//function for operator overloading "+" when it is between a CurrentAccount and a SavingsAccount
CurrentAccount operator+(CurrentAccount& current, SavingsAccount& savings) {
    double transfer = 300.0; //I put 300 here because that is what the example had in the main
    if (savings.balance >= transfer) {
        savings.balance -= transfer;
        current.balance += transfer;
    } else {
        std::cout << "Cannot transfer $300 dollars from current to savings" << std::endl;
    }
    return current;
}
//operator overloading << for when it is printing out details on the SavingsAccount
std::ostream& operator<<(std::ostream& os, const SavingsAccount& acc) {
    os << "Account Details for Savings Account (ID: " << acc.accountNumber << "):" << std::endl;
    os << "Account Holder: " << acc.accountHolder << std::endl;
    os << "Balance: $" << acc.balance << std::endl;
    os << "Interest Rate: " << acc.interestRate*100 << "%" << std::endl;
    return os;
}
//operator overloading << for when it is printing out details on the CurrentAccount
std::ostream& operator<<(std::ostream& os, const CurrentAccount& acc) {
    os << "Account Details for Savings Account (ID: " << acc.accountNumber << "):" << std::endl;
    os << "Account Holder: " << acc.accountHolder << std::endl;
    os << "Balance: $" << acc.balance << std::endl;
    os << "Overdraft Limit: $" << acc.overdraftLimit << std::endl;
    return os;
}
//the main function (for testing out this program)
int main(){
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    std::cout << savings << std::endl;
    std::cout << current << std::endl;

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << "Account Details after deposit and withdrawal:" << std::endl;
    std::cout << savings << std::endl;
    std::cout << current << std::endl;

    current = current + savings;
    std::cout << "Account Details after transfer:" << std::endl;
    std::cout << savings << std::endl;
    std::cout << current << std::endl;

    return 0;
}