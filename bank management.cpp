#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount
{
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount()
    {
        cout << "\nAccount Number : " << accNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs." << balance << endl;
    }

    int getAccNo()
    {
        return accNo;
    }

    float getBalance()
    {
        return balance;
    }

    void deposit(float amt)
    {
        balance += amt;
    }

    void withdraw(float amt)
    {
        if (amt <= balance)
            balance -= amt;
        else
            cout << "\nInsufficient Balance!\n";
    }
};

void createNewAccount()
{
    BankAccount acc;
    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    file.write((char*)&acc, sizeof(acc));

    file.close();
    cout << "\nAccount Created Successfully!\n";
}

void displayAccount()
{
    int accNo;
    BankAccount acc;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() == accNo)
        {
            acc.showAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

void depositMoney()
{
    int accNo;
    float amount;
    BankAccount acc;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() == accNo)
        {
            acc.deposit(amount);

            file.seekp(-sizeof(acc), ios::cur);
            file.write((char*)&acc, sizeof(acc));

            found = true;
            cout << "\nAmount Deposited Successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

void withdrawMoney()
{
    int accNo;
    float amount;
    BankAccount acc;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&acc, sizeof(acc)))
    {
        if (acc.getAccNo() == accNo)
        {
            acc.withdraw(amount);

            file.seekp(-sizeof(acc), ios::cur);
            file.write((char*)&acc, sizeof(acc));

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            displayAccount();
            break;

        case 5:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while (choice != 5);

    return 0;
}