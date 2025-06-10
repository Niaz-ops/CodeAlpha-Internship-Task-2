#include <iostream>
#include <vector>
#include <string>
using namespace std;

// **********Transaction Class**********
class Transaction {
public:
    string type;
    double amount;
    string dateTime;
    int fromAccount;
    int toAccount;

Transaction (string t, double a, string dt, int from = -1, int to = -1 )
: type(t), amount(a), dateTime(dt), fromAccount(from), toAccount(to){}

void printTransaction(){
    cout<<dateTime<<" - "<<type<<" : "<<amount;
    if(type == "Transfer"){
        cout<<"From # "<<fromAccount<<" ToAccount # "<<toAccount;
    }
    cout<<endl;
}
};

// **********Account Class**********

class Account{
    public:
    int accountNo;
    string accountType;
    double balance;
    vector<Transaction>transactions;

    Account(int num, string type, double bal)
    : accountNo(num),accountType(type),balance(bal){}
    void deposit(double amount){
        balance += amount;
        transactions.push_back(Transaction("Deposit ", amount, "2025- 05- 16"));
    }
        bool withDraw(double amount){
            if(balance >= amount){
                balance -= amount;
                transactions.push_back(Transaction("withDraw ", amount, "2025-05-16"));
                return true;
            }
            else{
                cout<<"Low balance!"<<endl;
                return false;
            }
        }
    
    bool transfer(Account *to, double amount){
        if(withDraw(amount)){
            to->deposit(amount);
            transactions.push_back(Transaction("Transfer ", amount, "2025- 05- 16", accountNo, to->accountNo));
            return true;
        }
        return false;
    }
    void viewAccountDetails(){
        cout<<"Account # "<<accountNo<<" ( "<<accountType<<" ) "<<endl;
        cout << "Balance : " << balance <<" $ " << "\n";
        cout << "Transactions : \n";
        for (size_t i = 0; i < transactions.size(); ++i) {
        transactions[i].printTransaction();
        }
    }
};

// **********Customer Class**********

class Customer {
    public:
    int Id; 
    string name;
    string address;
    string phoneNumber;
    vector<Account*> accounts;

    Customer (int id, string n, string a, string p)
    : Id(id), name(n), address(a), phoneNumber(p){}

    void addAccount(Account* account) {
        accounts.push_back(account);
        cout<<endl;
    }

    void viewAccounts() {
        cout << "Customer : " << name << " (ID : " << Id << ")"<<endl;
        for(size_t i= 0; i < accounts.size(); i++){
            accounts[i]->viewAccountDetails();
        }
    }
};

//********** Class Banking Services ********** 

class BankingServices{
    private:
    int nextCustomerId = 1;
    int nextAccountNumber = 1000;
    public:
    vector<Customer*> customers;
    vector<Account*> accounts;

    Customer* createCustomer(string name, string address, string phone){
        Customer* c = new Customer(nextCustomerId++, name, address, phone);
        customers.push_back(c);
        return c;
    }
     Account* createAccount(Customer* customer, string type, double initialDeposit) {
        Account* acc = new Account(nextAccountNumber++, type, initialDeposit);
        customer->addAccount(acc);
        accounts.push_back(acc);
        return acc;
    }
    void deposit(Account* account, double amount) {
        account->deposit(amount);
    }
    void withDraw(Account* account, double amount) {
        account->withDraw(amount);
    }

    void transfer(Account* from, Account* to, double amount) {
        from->transfer(to, amount);
    }
    Account* findAccount(int accNumber) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->accountNo == accNumber)
            return accounts[i];
    }
    return nullptr;
}
};

//********** Main Function **********

int main(){
    BankingServices bank;
    cout<<" ****** Create Customer ***** "<<endl;
    string name, address, phone;
    cout<<"Enter Name of customer : ";
    getline(cin, name);
    cout<<"Enter Address of customer : ";
    getline(cin, address);
    cout<<"Enter Phone number of customer : ";
    getline(cin, phone);
    Customer* customer = bank.createCustomer(name, address, phone);

    cout << "\n==== Create Account ====\n";
    string accType;
    double initialDeposit;
    cout << "Enter account type (Savings/Current): ";
    getline(cin, accType);
    cout << "Enter initial deposit: ";
    cin >> initialDeposit;
    Account* acc = bank.createAccount(customer, accType, initialDeposit);
    
    int choice;
    do{
        cout<<"\n==== Banking Menu ====\n";
        cout<<"1. Deposit"<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. Transfer"<<endl;
        cout<<"4. View Account"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        if (choice == 1) {
            double amount;
            cout << "Enter deposit amount: ";
            cin >> amount;
            Account* acc = bank.createAccount(customer, "Savings", 0);
        }
        else if (choice == 2) {
            double amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            bank.withDraw(acc, amount);
        }
        else if (choice == 3) {
            int toAccNum;
            double amount;
            cout << "Enter recipient account number: ";
            cin >> toAccNum;
            Account* toAcc = bank.findAccount(toAccNum);
            if (toAcc) {
                cout << "Enter amount to transfer: ";
                cin >> amount;
                bank.transfer(acc, toAcc, amount);
            } else {
                cout << "Account not found.\n";
            }
        }
        else if (choice == 4) {
            customer->viewAccounts();
        }

    }while (choice != 5);
    cout<<"Thank you for using Banking Application!"<<endl;
    return 0;
}