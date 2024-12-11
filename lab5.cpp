#include <iostream>
#include <string>
using namespace std;

class Customer
{
 private:
    string name;
    string surname;
    unsigned age;
    unsigned passport;
    unsigned phone;

 public:
    Customer(                                   //Конструктор
        string name1 = " ",
        string surname1 = " ",
        unsigned age1 = 0,
        unsigned passport1 = 0,
        long phone1 = 0
    )
    {
        name = name1;
        surname = surname1;
        age = age1;
        passport = passport1;
        phone = phone1;
    }

//~Customer();                             //Деструктор

    string getName() const{                  //функции для вывода данных
        return (this->name); 
        }
    string getSurName() const{
        return (this->surname); 
        }
    unsigned getAge() const{
        return this->phone;
        }
    unsigned getPassword() const{
        return this->phone;
        }
    long getPhone() const{
        return this->phone;
        }

};

class Transaction
{
private:
    string sendCard;
    string addresCard;
    int sum;
    int operation;

public:
    Transaction(
        string sendCard1 = "0",
        string addresCard1 = "0",
        int sum1 = 0,
        int operation1 = 0
    )
    {
        sendCard = sendCard1;
        addresCard = addresCard1;
        sum = sum1;
        operation = operation1;
    }
~Transaction();
};


class BankAccount: public Customer
{
private:
    string cardNum;
    string cvv;
    
    
public:
    double balance;

    BankAccount(                             //Конструктор
        const Customer& customer = Customer(),
        string cardNum1 = "0",
        string cvv1 = "0",
        double balance1 = 0.0
    ) : Customer(customer)
    {
        cardNum = cardNum1;
        cvv = cvv1;
        balance = balance1;
    }

    //~BankAccount();                     //Деструктор

    BankAccount& operator+= (double plus)
    {
        balance += plus;
        return *this;
    }

    BankAccount& operator-= (double minus)
    {
        balance += minus;
        return *this;
    }    
};

class SavingsAccount : public BankAccount
{
private:
    double percent;
public:
    SavingsAccount(
        const Customer& customer = Customer(),
        string cardNum1 = "0",                
        string cvv1 = "0",
        double balance1 = 0.0,
        double percent1 = 0.01        
    ) : BankAccount(customer, cardNum1, cvv1, balance1)
    {
        percent = percent1; 
    } 

    ~SavingsAccount();

    void addMoney(double plus)                    // + деньги за вклад
    {
        *this += plus;
    }

    void addMoney()                              // + деньги за вклад
    {
        double presBalance = balance;
        double a = presBalance * percent;
        *this += a;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double checkBalance;
public:
    CheckingAccount(
    const Customer& customer = Customer(),
    string cardNum1 = "0",
    string cvv1 = "0",
    double balance1 = 0.0,
    double checkBalance1 = 0.0    
    ) : BankAccount(customer, cardNum1, cvv1, balance1)
    {
        checkBalance = checkBalance1;
    }

    ~CheckingAccount();

    void addCheckMoney(double plus)             //Прибавление денег на расчетный счет
    {
        *this += plus;
    }
    void dimCheckMoney(double minus)           //Списание денег с расчетного счета
    {
        *this -= minus;
    }
};


int main()
{
    cout << "Bank system is active\n";

    //create customer:
    string name, surname;
    cout << "name: ";
    cin >> name;
    cout << "surname: ";
    cin >> surname;
    unsigned int age, passport;
    cout << "age: ";
    cin >> age;
    cout << "passport: ";
    cin >> passport;

    Customer person(name, surname, age, passport);

    //account create
    BankAccount* account = nullptr;
    int res;
    do
    {
        cout << "\nBanking system menu:\n";
        cout << "1. Create bank account\n";
        cout << "2. Create savings account\n";
        cout << "3. Create checking account\n";
        cout << "4. exit\n";
        cin >> res;
        switch (res){
            case 1:
            {
                string card;
                double money;
                cout << "Enter your card number: \n";
                cin >> card;
                cout << "Enter initial balance: \n";
                cin >> money;
                account = new BankAccount(person, card, "123", money);
                cout << "Acc created!\n";
                cout << "Your initial cvv: 123\n";
                break;
            }
            case 2:
            {
                string card;
                double money;
                cout << "Enter your card number: ";
                cin >> card;
                cout << "Enter initial balance: ";
                cin >> money;
                account = new SavingsAccount(person, card , "123", money, 0.15);
                cout << "Acc created!\n";
                cout << "Your initial cvv: 123\n";
                cout << "Your initial percent: 0.15\n";
                break;
            }
            case 3:
            {
                string card;
                double money, bal;
                cout << "Enter your card number: \n";
                cin >> card;
                cout << "Enter initial balance: ";
                cin >> money;
                cout << "Enter bank balance for comparison: ";
                cin >> bal;            
                account = new CheckingAccount(person, card , "123", money, bal);
                cout << "Acc created!\n";
                cout << "Your initial cvv: 123\n";
                break;
            }
            case 4:
            {
                break;
            }
        }
    } while (res !=4);
    
    if (account == nullptr) {
        cout << "Acc error :(\n";
        return 0;
    }

    //menu
    do {
        cout << "\nBanking menu:\n";
        cout << "1. Plus money\n";
        cout << "2. Dim money\n";
        cout << "3. Exit\n";
        cin >> res;

        switch (res) 
        {
            case 1: 
            {
                cout << "Enter the top-up amount: ";
                double amount;
                cin >> amount;
                if (amount > 0)
                {
                    *account += amount;
                    cout << "success replenishment!\n";
                } else {
                    cout << "invalid replenishment!\n";
                }
                break;
            }
            case 2: 
            {
                cout << "Enter amount to withdraw: ";
                double amount;
                cin >> amount;
                if (amount > 0)
                {
                    *account -= amount;
                    cout << "success removal!\n";
                } else {
                    cout << "invalid removal!\n";
                }
                break;
            }
            case 3:
            {
                break;
            }
        }
    }
    while (res != 3);
    return 0;
}