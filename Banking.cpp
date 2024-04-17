#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string holderName;
    double balance;

public:
    BankAccount(string accNum, string name) : accountNumber(accNum), holderName(name), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        cout << "\nDeposited: $" << amount << " Successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance)
            cout << "\nInsufficient Balance!\n";
        else {
            balance -= amount;
            cout << "\nWithdrawn: $" << amount << " Successfully.\n";
        }
    }

    void displayBalance() {
        cout << "\nCurrent Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    string getHolderName() {
        return holderName;
    }

    string getAccountNumber() {
        return accountNumber;
    }
};

class Bank {
private:
    vector<BankAccount> accounts;

public:
    void addAccount(string accNum, string name) {
        BankAccount newAccount(accNum, name);
        accounts.push_back(newAccount);
        cout << "\nAccount created successfully for " << name << endl;
    }

    BankAccount* findAccount(string accNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNum)
                return &account;
        }
        return nullptr;
    }
};

int main() {
    Bank bank;

    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 10); 
    #endif
    cout << "Welcome to Our Bank\n";
    cout << "-------------------\n";
    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 15); 
    #endif

    string accNum, name; // Moved outside switch statement

    while (true) {
        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 14); 
        #endif
        cout << "\nMenu:\n";
        cout << "1. Add New Customer\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 15); 
        #endif
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);
                bank.addAccount(accNum, name);
                break;
            case 2: {
                double amount;
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                BankAccount* acc = bank.findAccount(accNum);
                if (acc != nullptr) {
                    cout << "Enter amount to deposit: $";
                    cin >> amount;
                    acc->deposit(amount);
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 3: {
                double amount;
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                BankAccount* acc = bank.findAccount(accNum);
                if (acc != nullptr) {
                    cout << "Enter amount to withdraw: $";
                    cin >> amount;
                    acc->withdraw(amount);
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 4: {
                cout << "\nEnter Account Number: ";
                cin >> accNum;
                BankAccount* acc = bank.findAccount(accNum);
                if (acc != nullptr) {
                    acc->displayBalance();
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 5:
                cout << "Thank you for banking with us. Goodbye!\n";
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
