#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Account {
public:
    string name;
    string accountNumber;
    double balance;

    Account(string n, string accNum) : name(n), accountNumber(accNum), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        logTransaction("Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            logTransaction("Withdraw", amount);
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    void logTransaction(const string& type, double amount) {
        ofstream transactionFile("transactions.txt", ios::app);
        transactionFile << accountNumber << " " << type << " " << amount << " " << balance << endl;
        transactionFile.close();
    }

    void viewTransactions() {
        ifstream transactionFile("transactions.txt");
        string line;
        cout << "Transaction History for Account: " << accountNumber << endl;
        while (getline(transactionFile, line)) {
            if (line.find(accountNumber) != string::npos) {
                cout << line << endl;
            }
        }
        transactionFile.close();
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount() {
        string name, accountNumber;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter account number: ";
        cin >> accountNumber;
        accounts.emplace_back(name, accountNumber);
        cout << "Account created successfully!" << endl;
    }

    Account* findAccount(const string& accountNumber) {
        for (auto& account : accounts) {
            if (account.accountNumber == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void deposit() {
        string accountNumber;
        double amount;
        cout << "Enter account number: ";
        cin >> accountNumber;
        Account* account = findAccount(accountNumber);
        if (account) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            account->deposit(amount);
            cout << "Deposit successful!" << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdraw() {
        string accountNumber;
        double amount;
        cout << "Enter account number: ";
        cin >> accountNumber;
        Account* account = findAccount(accountNumber);
        if (account) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            account->withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void viewTransactions() {
        string accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;
        Account* account = findAccount(accountNumber);
        if (account) {
            account->viewTransactions();
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\nBank Management System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. View Transactions" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.deposit();
                break;
            case 3:
                bank.withdraw();
                break;
            case 4:
                bank.viewTransactions();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}