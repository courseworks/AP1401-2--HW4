# Advanced Programming - HW4
<p  align="center"> <b>Homework 4 - Spring 2023 Semester <br> Deadline: Wednesday Ordibehesht 13st - 11:59 pm</b> </p>

# 1. cpp
The purpose of this homework is to design a banking system. There are two `.h` files, one for **account** information and one for **banking system**.

## account.h
The first class is `Account`; It has a member variable called `balance` to store the balance of the account, and two functions called deposit, withdraw, and get_balance using the following API:
- `balance`: The current amount of money in the account.
- `withdraw`: Take money out of your account, either by cash or transferring.
- `deposit`: Put money into your account.
- Add a vector of transactions to keep track of the account's history.
- Implement a member function to add a transaction to this vector.
- Some functions should be constant.
- Some functions should be virtual.
- Arguments should be optimized (using const reference (&) instead of copying).
- The move constructor moves the balance value of the object into the new
- object being constructed, and sets the balance value of the other object to zero, and also avoids the need to allocate new memory for the balance value when copying Account objects.
- Add a destructor to free any dynamically allocated memory, if any.

**Question:** Why should ~Account() be virtual?

```cpp
class Account {
public:
    Account(double balance = 0);
    ~Account();
    Account(const Account&);
    Account(Account&&);
    Account& operator=(const Account&);
    Account& operator=(Account&&);

    void deposit(double amount);
    bool withdraw(double amount);
    double get_balance();

    std::vector<Transaction> transactions_;

private:
    double balance_;
};
```
## SavingAccount
The next class is SavingAccount class that inherits from the Account class. Saving
accounts has an interest rate and the interest should be added to the main
balance. It has a member variable `interestRate` to store the rate,
`withdrawCounts` to limit the number of withdraws from the account per month,
and add_interest to add the interest to the balance.
- This class inherits from the Account class and some functions should
override previous functions.
- Saving Account: This type of account has an interest rate (for example 1%
per year).
- withdraw counts: The account holder may withdraw money 3 times from
the account per month.
- withdraw: It’s a little different from Account’s withdraw. If the user tries to
withdraw more than 3 times, it should throw an error. Should also log
transactions.
- add interest: To change the interest rate.
- Some functions should be virtual.
- Arguments should be optimized (using const reference (&) instead of
copying).
- Add a destructor to free any dynamically allocated memory, if any.

```cpp

class SavingsAccount {
public:
    SavingsAccount(double balance = 0, double interest_rate = 0.01);
    ~SavingsAccount();
    SavingsAccount(const SavingsAccount&);
    SavingsAccount(SavingsAccount&&);
    SavingsAccount& operator=(const SavingsAccount&);
    SavingsAccount& operator=(SavingsAccount&&);
    void addInterest();
    bool withdraw(double amount);

private:
    double interestRate;
    size_t withdrawCounts;
};
```

## CheckingAccount
The next class is the CheckingAccount class that mimics a normal account used for
day-to-day payments. It has a fee variable that every time the account holder
withdraws money, it deducts a little bit more from the balance for the bank fee.

- This class inherits from the Account class and some functions should override previous functions.
- `CheckingAccount`: The account you use for daily basis.
- `withdraw`: It’s a little different from Account’s withdraw. It also deducts
money per transaction (withdraw/deposit). Transactions should be logged.
- Deduct fee:
- Some functions should be virtual.
- Arguments should be optimized (using const reference (&) instead of
copying).
- Add a destructor to free any dynamically allocated memory, if any.
```cpp
class CheckingAccount {
public:
    CheckingAccount(double balance = 0, double fee = 1);
    ~CheckingAccount();
    CheckingAccount(const CheckingAccount&);
    CheckingAccount(CheckingAccount&&);
    CheckingAccount& operator=(const CheckingAccount&);
    CheckingAccount& operator=(CheckingAccount&&);
    bool withdraw(double amount);
private:
    double fee;
};
```
**Question**: Can you make the withdraw function of CheckingAccount const?

## CreditAccount
The next class is `CreditAccount` to create a credit account. Credit account allows the account holder to withdraw money more than the current balance, but has to pay back by the end of the month.
- This class inherits from the `Account` class and some functions should override previous functions.
- `CreditAccount`: The account holder can take more than the account’s balance, but has to pay back later.
- `withdraw`: It’s a little different from Account’s withdraw. It may also allow
the account holder to withdraw more money. For example if the balance is 1000 and the maximum credit (credit_limit) is 500, the account holder may withdraw up to 1500 but the debt will be 500 (should pay back 500 to the bank later). The credit limit should be updated (like if they use 200 out of 500, the credit limit should be 300 until they pay back)
- `payDebt`: If the debt is zero and the account holder tries to pay back, it should throw an error. If the debt is not zero, it should reset debt to 0 and credit back to the first value (for example 500).
- Some functions should be virtual.
- Some functions should be const.
- Arguments should be optimized (using const reference (&) instead of copying).
- Add a destructor to free any dynamically allocated memory, if any.

```cpp
class CreditAccount {
public:
    CreditAccount(double balance = 0, double credit_limit = 500);
    ~CreditAccount();
    CreditAccount(const CreditAccount& other);
    CreditAccount(CreditAccount&& other);
    bool withdraw(double amount);
    double getCreditLimit();
    double getInterestRate();
    double getDebt();
    void payDebt();

private:
    double creditLimit;
    double debt;
};
```

## Transaction

The `Transaction` class logs the history of transactions. It saves the amount of money transferred between two accounts:

```cpp
class Transaction {
public:
    Transaction(const std::string& from, const std::string& to, double amount, const std::string& currency);

    std::string getFrom();
    std::string getTo();
    double getAmount();
    std::string getCurrency();

private:
    std::string from;
    std::string to;
    double amount;
    std::string currency;
};
```
- Some functions should be const.

## Currency

Currency class includes multiple currencies (USD, EUR, GBP, etc.) and the exchange rate.

- `Currency` is the type of money used, like US Dollar, Euro, etc.
- `echangeRate`: The rate to convert another currency to US Dollar.
- `name`: The name of the currency.
- Some functions can be const.
```cpp
class Currency {
public:
    Currency(const std::string& name, double exchange_rate);
    ~Currency();
    std::string getName();
    double getExchangeRate();

private:
    std::string name;
    double exchangeRate;
};
```
## Customer
Now we need declare the `Customer` class, we want this class to have a series of functions like password authentication, add_acount which creates a new saving/credit/banking type accounts based on the currency specified. Use unordered maps to link the currencies to each account like the code provided below.

- `Customer`: Saves customer’s information like username, password, and linked accounts.
- `authenticate`: Validates if the password is correct.
- `addAccount`: To create or link an account (Saving, Checking, Credit) to the customer.
- `getAccounts`: Returns the accounts linked to that customer
- Some functions should be const.
```cpp
class Customer {
public:
    Customer(const std::string& name, const std::string& password);
    Customer(const Customer& other);
    Customer(Customer&& other);
    Customer& operator=(const Customer& other);
    Customer& operator=(Customer&& other);
    ~Customer();
    bool authenticate(const std::string& password);
    void addAccount(Account* account, const Currency& currency);
    std::vector<Account*>& getAccounts(const Currency& currency);

private:
    std::string name;
    std::string password;

    std::unordered_map<const Currency*, std::vector<Account*>> accounts;
};
```
## BankingSystem
Last but not least, we need to implement the `BankingSystem`.
Push back each currency value similar to the code provided.
Have other functions like `addCustomers` which saves each account into the customers list as a pointer.
Have a transfer function to transfer money between accounts and account for currency changes.
Implement another function for converting currencies.

```cpp
class BankingSystem {
public:
    BankingSystem();
    ~BankingSystem();
    BankingSystem(const BankingSystem& other);
    BankingSystem(BankingSystem&& other);
    BankingSystem& operator=(const BankingSystem& other);
    BankingSystem& operator=(BankingSystem&& other);
    void addCustomer(Customer* customer);
    bool transfer(Customer* sender, Account* sender_account,
                  Customer* receiver, Account* receiver_account,
                  double amount, const Currency& currency);
    double convert(double amount, const Currency& from_currency,
                   const Currency& to_currency) const;

private:
    std::vector<Customer*> customers_;
    std::vector<Currency> currencies_;
};
```

# 2. درﺑﺎره ﺟﻨﮓ ﺳﺘﺎرﮔﺎن

## ۲. ۱ ﻣﻘﺪﻣﻪ

در این تمرین قصد داریم وب سایتی برای فیلم جنگ ستارگان بسازیم.

## ۲. ۲ وب ﮔﺎه

وب ﮔﺎﻫﯽ ﮐﻪ ﭘﯿﺎده ﺳﺎزی ﻣﯽﮐﻨﯿﺪ، از ﺷﻤﺎی زﯾﺮ ﭘﯿﺮوی ﻣﯽﮐﻨﺪ. در اﯾﻦ ﺷﻤﺎ ﯾﮏ ﻋﮑﺲ ﭘﺲ زﻣﯿﻨﻪ وﺟﻮد داﺷﺘﻪ و ﻣﺤﺘﻮا در ﻗﺎﻟﺐ ﯾﮏ ﻣﺴﺘﻄﯿﻞ ﺑﺎ ﭘﺲ زﻣﯿﻨﻪ ﺷﻔﺎف روی آن ﻧﻤﺎﯾﺶ داده ﻣﯽ ﺷﻮد. در ﻧﻈﺮ داﺷﺘﻪ ﺑﺎﺷﯿﺪ ﮐﻪ ﻋﮑﺲ ﭘﺲ زﻣﯿﻨﻪ ﻣﯽ ﺑﺎﯾﺴﺖ ﺗﻤﺎم ﺻﻔﺤﻪ را ﭘﻮﺷﺎﻧﺪه ﺑﺎﺷﺪ و در ﺻﻮرﺗﯽ ﮐﻪ از ﺻﻔﺤﻪ ﺑﺰرﮔﺘﺮ ﺑﺎﺷﺪ **ﻧﺒﺎﯾﺪ** ﺑﺎﻋﺚ اﯾﺠﺎد scrollbar ﮔﺮدد. ﺑﺮای اﯾﻨﮑﻪ ﭘﻮﺷﺶ ﺻﻔﺤﻪ ﮐﺎﻓﯽ ﺑﺎﺷﺪ از ﻋﮑﺲ ﻫﺎﯾﯽ ﺑﺎ وﺿﻮح ﺑﺎﻻ (ﻣﺜﻼ 1028 ×1920 ) اﺳﺘﻔﺎده ﮐﻨﯿﺪ. در ﺷﺮاﯾﻄﯽ ﮐﻪ اﺑﻌﺎد ﺻﻔﺤﻪ ﻧﻤﺎﯾﺶ ﮐﻮﭼﮑﺘﺮ از وﺿﻮح ﻋﮑﺲ ﺑﺎﺷﺪ، ﻣﯽ ﺑﺎﯾﺴﺖ ﻗﺴﻤﺘﯽ از وﺳﻂ ﻋﮑﺲ ﻧﻤﺎﯾﺶ داده ﺷﻮد. ﺑﺮای ﺗﺼﻮﯾﺮ ﭘﺲ زﻣﯿﻨﻪ ﺣﺘﻤﺎ از ﻋﮑﺲ اﺳﺘﻔﺎده ﮐﻨﯿﺪ، ﺑﺮای ﻣﺜﺎل ﻣﯽ ﺗﻮاﻧﯿﺪ

از[ اﯾﻨﺠﺎ](https://unsplash.com/s/photos/starwars) اﺳﺘﻔﺎده ﮐﻨﯿﺪ.

![](resources/Aspose.Words.5beb3cff-3782-42d9-88c8-ba0a913d156f.001.png)

ﺷﮑﻞ ۱: ﻃﺮاﺣﯽ ﺳﻄﺢ ﺑﺎﻻ

ﻣﺴﺘﻄﯿﻞ ﻣﯿﺎﻧﯽ ﺗﻤﺎﻣﯽ ﻣﺤﺘﻮﯾﺎت ﻗﺎﺑﻞ ﻧﻤﺎﯾﺶ ﺷﻤﺎ را ﻣﯽ ﺑﺎﯾﺴﺖ ﺷﺎﻣﻞ ﺷﻮد. اﯾﻦ ﻣﺴﺘﻄﯿﻞ ﻣﯽ‌ﺑﺎﯾﺴﺖ ﺗﻨﻬﺎ ﺑﻪ اﻧﺪازه ﻣﺤﺘﻮﯾﺎت ﺑﺎﺷﺪ اﻣﺎ ﺑﺮای ﻧﻤﺎﯾﺶ زﯾﺒﺎﺗﺮ ﺑﺮای آن padding در ﻧﻈﺮ ﺑﮕﯿﺮﯾﺪ.

### ۲. ۲. ۱ ﻣﺤﺘﻮﯾﺎت

<a name="_page1_x62.36_y456.75"></a>آﻧﭽﻪ ﻣﯽ ﺑﺎﯾﺴﺖ ﻧﻤﺎﯾﺶ دﻫﯿﺪ اﻃﻼﻋﺎت ﻓﯿﻠﻢ ﻫﺎی ۱ ﺗﺎ ۶ ﺟﻨﮓ ﺳﺘﺎرﮔﺎن از ﺗﺎرﻧﻤﺎی زﯾﺮ اﺳﺖ:

<https://swapi.dev/>

ﺗﻮﺟﻪ داﺷﺘﻪ ﺑﺎﺷﯿﺪ ﺗﺮﺗﯿﺐ ﻧﻤﺎﯾﺶ ﻣﯽ ﺑﺎﯾﺴﺖ ﺑﻪ ﺷﺮح زﯾﺮ ﺑﺎﺷﺪ:

[https://swapi.dev/api/films/4 ](https://swapi.dev/api/films/4)[https://swapi.dev/api/films/5 ](https://swapi.dev/api/films/5)[https://swapi.dev/api/films/ 6](https://swapi.dev/api/films/6) [https://swapi.dev/api/films/1 ](https://swapi.dev/api/films/1)[https://swapi.dev/api/films/2 ](https://swapi.dev/api/films/2)<https://swapi.dev/api/films/3>

ﺑﺮای ﻫﺮ ﯾﮏ از اﯾﻦ ﻓﯿﻠﻢ ﻫﺎ اﻃﻼﻋﺎت زﯾﺮ ﻣﯽ ﺑﺎﯾﺴﺖ ﻧﻤﺎﯾﺶ داده ﺷﻮد:

- title
- episode_id
- release_date

و ﺳﺎﺧﺘﺎر اﻃﻼﻋﺎت اﯾﻦ ﻓﯿﻠﻢ ﻫﺎ ﻧﯿﺰ ﺑﻪ ﺷﺮح زﯾﺮ اﺳﺖ:
```json
{
"title": "Revenge of the Sith",
"episode_id": 3,
"opening_crawl": "...", 
"director": "George Lucas",
"producer": "Rick McCallum",
"release_date": "2005-05-19",
"characters": [ ... ],
"planets": [ ... ],
"https://swapi.dev/api/starships/2/",

"starships": [

"https://swapi.dev/api/starships/2/",
    ...,
],
"vehicles": [ ... ],
"species": [ ... ],
"created": "2014-12-20T18:49:38.403000Z",
"edited": "2014-12-20T20:47:52.073000Z",
"url": "https://swapi.dev/api/films/6/"
}
```

ﻫﻤﺎﻧﻄﻮر ﮐﻪ ﺳﺎﺧﺘﺎر اﻃﻼﻋﺎت ﻧﻤﻮﻧﻪ ﻧﯿﺰ ﻣﺸﺨﺺ اﺳﺖ ﺑﺮای ﻫﺮ ﻓﯿﻠﻢ ﻟﯿﺴﺘﯽ از ﮐﺸﺘﯽ ﻫﺎی ﻓﻀﺎﯾﯽ اﺳﺘﻔﺎده ﺷﺪه در آن ﻗﺴﻤﺖ وﺟﻮد دارد. ﺑﺮای ﻫﺮ ﻓﯿﻠﻢ دﮐﻤﻪ ای ﺑﺎ ﻧﺎم Starship وﺟﻮد دارد ﮐﻪ ﺑﺎ اﺳﺘﻔﺎده از آن اﻃﻼﻋﺎت ﮐﺸﺘﯽ ﻫﺎی ﻓﻀﺎﯾﯽ آن ﻗﺴﻤﺖ ﻧﻤﺎﯾﺶ داده ﻣﯽ ﺷﻮد. ﺑﺮای ﭘﯿﺎده ﺳﺎزی اﯾﻦ ﻗﺴﻤﺖ ﺟﺪﯾﺪ ﻣﯽ ﺑﺎﯾﺴﺖ ﻟﯿﺴﺖ ﻓﯿﻠﻢ ﻫﺎ ﺣﺬف ﺷﻮد. ﺷﻤﺎ ﻣﯽ ﺑﺎﯾﺴﺖ ﺑﺮای ﻫﺮ ﯾﮏ از اﯾﻦ ﮐﺸﺘﯽ ﻫﺎی ﻓﻀﺎﯾﯽ ﺑﻪ ﻟﯿﻨﮑﯽ ﮐﻪ داده ﺷﺪه اﺳﺖ ﺗﻘﺎﺿﺎ داده و ﻧﺎم آن را اﺳﺘﺨﺮاج ﮐﺮده و در اﯾﻦ ﻗﺴﻤﺖ ﺟﺪﯾﺪ ﻧﻤﺎﯾﺶ دﻫﯿﺪ. ﮐﺎرﺑﺮ ﻣﯽ ﺗﻮاﻧﺪ از ﻟﯿﺴﺖ اﯾﻦ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎ ﯾﮑﯽ را اﻧﺘﺨﺎب ﮐﺮده و ﺟﺰﺋﯿﺎت آن را ﺑﺒﯿﻨﺪ. اﮔﺮ ﺑﺨﻮاﻫﯿﻢ دﻗﯿﻘﺘﺮ ﺻﺤﺒﺖ ﮐﻨﯿﻢ ﻟﯿﺴﺖﺷﺎﻣﻞﻧﺎمﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎاﺳﺖﮐﻪﺑﺎﮐﻠﯿﮏﺑﺮرویﻫﺮﯾﮏاﻃﻼﻋﺎتﺟﺰﺋﯽآنﺷﺎﻣﻞﻣﺪل،ﺳﺎزﻧﺪه،ﺧﺪﻣﻪوﺗﻌﺪادﻣﺴﺎﻓﺮان ﻧﻤﺎﯾﺎن ﻣﯽﮔﺮدد. ﺑﺮای ﻧﻤﻮﻧﻪ داده ای ﮐﻪ ﺷﻤﺎ ﺑﺮای ﯾﮏ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ درﯾﺎﻓﺖ ﻣﯽﮐﻨﯿﺪ در اداﻣﻪ آورده ﺷﺪه اﺳﺖ. در اﯾﻦ ﻗﺴﻤﺖ

ﻫﻢ اﻃﻼﻋﺎت ﻗﺒﻠﯽ ﺣﺬف ﺷﺪه و اﻃﻼﻋﺎت ﺟﺪﯾﺪ ﻧﻤﺎﯾﺶ داده ﻣﯽ ﺷﻮﻧﺪ.
```json
{
    "name": "Imperial shuttle",
    "model": "Lambda-class T-4a shuttle",
    "manufacturer": "Sienar Fleet Systems",
    "cost_in_credits": "240000",
    "length": "20",
    "max_atmosphering_speed": "850",
    "crew": "6",
    "passengers": "20",
    "cargo_capacity": "80000",
    "consumables": "2 months",
    "hyperdrive_rating": "1.0",
    "MGLT": "50",
    "starship_class": "Armed government transport",
    "pilots": [
        "http://swapi.dev/api/people/1/",
        "http://swapi.dev/api/people/13/",
        "http://swapi.dev/api/people/14/"
    ],
    "films": [
        "http://swapi.dev/api/films/2/",
        "http://swapi.dev/api/films/3/"
    ],
    "created": "2014-12-15T13:04:47.235000Z",
    "edited": "2014-12-20T21:23:49.900000Z",
    "url": "http://swapi.dev/api/starships/22/''
}
```

در ﺻﻮرﺗﯽ ﮐﻪ ﻗﺴﻤﺖ ﻓﯿﻠﻢ ﻫﺎ ﻧﯿﺰ دارای اﻃﻼﻋﺎت ﺑﺎﺷﺪ ﻣﯽ ﺑﺎﯾﺴﺖ ﻧﺎم ﻓﯿﻠﻢ ﻫﺎ ذﮐﺮ ﺷﻮد. دﻗﺖ ﮐﻨﯿﺪ ﺑﺮای اﯾﻦ اﻣﺮ ﻧﯿﺎز ﺑﻪ ﯾﮏ ﺗﻘﺎﺿﺎی ﺟﺪاﮔﺎﻧﻪ ﺑﺮای ﻓﯿﻠﻢ دارﯾﺪ. ﺳﺎﺧﺘﺎرURLﻫﺎ در اﯾﻨﺠﺎ ﺑﺴﯿﺎر ﺳﺎده ﻣﯽ ﺑﺎﺷﻨﺪ وﻟﯽ در ﺟﻬﺖ ﺗﺎﮐﯿﺪ در ﻗﺴﻤﺖ زﯾﺮ آن ﻫﺎ را ﻣﺮور
ﮐﺮده اﯾﻢ:

- https://swapi.dev/api/starships/<id>
- https://swapi.dev/api/films/<id>

در ﻧﻈﺮ داﺷﺘﻪ ﺑﺎﺷﯿﺪ در ﻗﺴﻤﺖ ﻟﯿﺴﺖ ﮐﺸﺘﯽ ﻫﺎی ﻓﻀﺎﯾﯽ ﻧﯿﺎز ﺑﻪ دﮐﻤﻪ ﺑﺎزﮔﺸﺖ ﺑﻪ ﻗﺴﻤﺖ ﻟﯿﺴﺖ ﻓﯿﻠﻢ ﻫﺎ دارﯾﻢ.

## ۲. ۳ ﺻﻔﺤﻪ ﮔﺬاری

ﻓﺮض ﮐﻨﯿﺪ ﻟﯿﺴﺖ ﺑﻠﻨﺪی از آﯾﺘﻢ ﻫﺎ در اﺧﺘﯿﺎر ﺷﻤﺎ ﻗﺮار ﮔﺮﻓﺘﻪ اﺳﺖ، در ﺻﻔﺤﻪ ﮔﺬاری اﯾﻦ ﻟﯿﺴﺖ را ﺑﻪ ﺻﻔﺤﺎﺗﯽ ﻣﯽ ﺷﮑﺎﻧﯿﺪ ﮐﻪ در ﻫﺮ ﺻﻔﺤﻪ ﺗﻌﺪاد ﻣﺸﺨﺼﯽ از اﻃﻼﻋﺎت وﺟﻮد دارﻧﺪ. ﮐﺎرﺑﺮان ﺑﻪ ﺟﺎی ﮐﺎرﮐﺮدن ﺑﺎ ﻟﯿﺴﺖ ﺑﻠﻨﺪی از آﯾﺘﻢ ﻫﺎ ﺑﺎ ﺻﻔﺤﺎﺗﯽ ﻣﻮاﺟﻪ ﻫﺴﺘﻨﺪ ﮐﻪ ﺗﻌﺪاد ﻣﺸﺨﺼﯽ از آﯾﺘﻢ ﻫﺎ را در ﺑﺮ ﮔﺮﻓﺘﻪ اﻧﺪ. ﮐﺎرﺑﺮ ﻣﯽ ﺗﻮاﻧﺪ از ﻗﺒﻞ در راﺑﻄﻪ ﺑﺎ ﺗﻌﺪاد ﮐﻞ ﺻﻔﺤﺎت اﻃﻼع داﺷﺘﻪ ﺑﺎﺷﺪ و ﻣﯽ ﺗﻮاﻧﺪ ﭼﻨﯿﻦ اﻃﻼﻋﯽ ﻧﯿﺰ ﺑﻪ او داده ﻧﺸﻮد. ﻫﻤﺎﻧﻄﻮر ﮐﻪ اداﻣﻪ ﻫﻢ ﺑﯿﺎن ﻣﯽ ﺷﻮد ﭼﮕﻮﻧﮕﯽ ﭘﯿﺎده ﺳﺎزی اﯾﻦ ﻣﻮﺿﻮع ﺑﻪ ﺧﻮد ﺷﻤﺎ واﺑﺴﺘﻪ اﺳﺖ. ﺟﺰﺋﯿﺎت ﭘﯿﺎده ﺳﺎزی اﯾﻦ ﻗﺴﻤﺖ ﮐﺎﻣﻼ ﺑﺮﻋﻬﺪه ﺧﻮدﺗﺎن ﻣﯽ ﺑﺎﺷﺪ. ﻣﯽ ﺗﻮاﻧﯿﺪ ﻟﯿﺴﺖ ﺗﻤﺎم ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎ را در اﺑﺘﺪا ﺳﺎﺧﺘﻪ و در اداﻣﻪ ﺻﻔﺤﻪ ﮔﺬاری را ﮐﺎﻣﻼ در ﺳﻤﺖ ﮐﻼﯾﻨﺖ اﻧﺠﺎم دﻫﯿﺪ ﯾﺎ ﻣﯽ ﺗﻮاﻧﯿﺪ در ﻫﺮ ﺑﺎر ﺗﻐﯿﯿﺮ ﺻﻔﺤﻪ ﻟﯿﺴﺖ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎ را درﯾﺎﻓﺖ ﮐﻨﯿﺪ. در ﻧﻈﺮ داﺷﺘﻪ ﺑﺎﺷﯿﺪ ﮐﻪ ﺗﻤﺎﻣﯽ ﻓﺮآﯾﻨﺪ ﻣﯽ ﺑﺎﯾﺴﺖ ﭘﻮﯾﺎ ﺑﻮده ﺑﺎﺷﺪ و ﻫﯿﭻ ﭼﯿﺰ ﺑﻪ ﺻﻮرﺗﯽ دﺳﺘﯽ در ﮐﺪﺗﺎن وارد ﻧﺸﺪه ﺑﺎﺷﺪ، ﺑﻪ ﻃﻮر دﻗﯿﻖ ﺗﺮ ﺑﺎ ﺗﻐﯿﯿﺮ ﺗﻌﺪاد ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎ ﻣﯽ ﺑﺎﯾﺴﺖ ﻫﻤﭽﻨﺎن ﺑﺮﻧﺎﻣﻪ ﺷﻤﺎ ﺑﻪ ﻃﻮر ﺻﺤﯿﺢ ﺑﻪ ﻓﻌﺎﻟﯿﺖ ﺧﻮد اداﻣﻪ دﻫﺪ. ﺑﻪ ﻃﻮر ﻣﺜﺎل ﻓﺮض ﮐﻨﯿﺪ در ﻣﺠﻤﻮع ۲۶ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ وﺟﻮد دارﻧﺪ. ﯾﮏ راه ﺑﺮای ﭘﯿﺎده ﺳﺎزی ﺻﻔﺤﻪ ﮔﺬاری ﺑﻪ اﯾﻦ ﺗﺮﺗﯿﺐ ﺧﻮاﻫﺪ

ﺑﻮد.

۱. ﮔﺮﻓﺘﻦ ﺗﻤﺎﻣﯽ اﻃﻼﻋﺎت ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎی ﻣﻮﺟﻮد

۲. ﻧﻤﺎﯾﺶ ۱۰ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ در ﻫﺮ ﺻﻔﺤﻪ، ﺑﻪ اﯾﻦ ﺗﺮﺗﯿﺐ دو ﺻﻔﺤﻪ ﺑﺎ ۱۰ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ و ﯾﮏ ﺻﻔﺤﻪ ﺑﺎ ۶ ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﺧﻮاﻫﯿﻢ

داﺷﺖ.

۳. ﭘﯿﺎده ﺳﺎزی دﮐﻤﻪ ﻫﺎﯾﯽ ﺑﺮای ﺟﺎﺑﺠﺎﯾﯽ ﺑﯿﻦ ﺻﻔﺤﺎت

## ۲. ۴ ﮔﺎم ﺑﻪ ﮔﺎم

در اﯾﻦ ﻗﺴﻤﺖ ﻗﺼﺪ دارﯾﻢ ﺟﺮﯾﺎن ﮐﺎر ﮐﺮدن ﺑﺎ اﯾﻦ وب ﮔﺎه را ﻣﺮور ﻧﻤﺎﯾﯿﻢ. در اوﻟﯿﻦ ﮔﺎم ﮐﺎرﺑﺮ ﺑﺎ ﻟﯿﺴﺖ ﺷﺶ ﻓﯿﻠﻢ ﺟﻨﮓ ﺳﺘﺎرﮔﺎن رو ﺑﻪ رو ﻣﯽ ﺷﻮد ﮐﻪ ﺷﺎﻣﻞ ﻧﺎم، ﺷﻤﺎره ﻗﺴﻤﺖ و ﺗﺎرﯾﺦ اﻧﺘﺸﺎر ﻫﺴﺘﻨﺪ. ﮐﺎرﺑﺮ ﻣﯽ ﺗﻮاﻧﺪ روی دﮐﻤﻪ ﮐﺸﺘﯽ ﻫﺎی ﻓﻀﺎﯾﯽ ﮐﻠﯿﮏ ﮐﺮده و ﻟﯿﺴﺖ آن ﻫﺎ را ﻣﺸﺎﻫﺪه ﮐﻨﺪ. اﯾﻦ ﻟﯿﺴﺖ ﺷﺎﻣﻞ ﻧﺎم ﮐﺸﺘﯽ ﻫﺎی ﻓﻀﺎﯾﯽ اﺳﺖ ﮐﻪ ﺑﺎ ﮐﻠﯿﮏ ﺑﺮ روی ﻫﺮ ﯾﮏ از آن ﻫﺎ ﺟﺰﺋﯿﺎت آن ﻫﺎ ﻧﻤﺎﯾﺶ داده ﻣﯽ ﺷﻮد.

## ۲. ۵ ﻧﮑﺎت ﭘﯿﺎده ﺳﺎزی

- آﻧﭽﻪ در ﺷﻤﺎ آورده ﺷﺪه اﺳﺖ ﺑﺮای ﻓﻬﻢ ﺑﻬﺘﺮ ﺷﻤﺎ ﻣﯽ ﺑﺎﺷﺪ ﺑﻨﺎﺑﺮاﯾﻦ ﺳﻌﯽ ﮐﻨﯿﺪ ﺗﺎ ﺣﺪ اﻣﮑﺎن وب ﺳﺎﯾﺖ را ﮔﻮﯾﺎ ﻃﺮاﺣﯽ ﮐﻨﯿﺪ.
- ﺑﺮایﮐﺪﻫﺎﯾﺘﺎنازﮐﺎﻣﻨﺖاﺳﺘﻔﺎدهﮐﻨﯿﺪ. ﺗﻮﺿﯿﺢﮐﺎرﮐﺮدﺑﻼک ﻫﺎی css اﺟﺒﺎریﻣﯽ ﺑﺎﺷﺪ. ﺗﻮاﺑﻌﯽوﻗﻄﻌﺎتﮐﺪﺟﺎوااﺳﮑﺮﯾﭙﺖ ﻧﯿﺰ ﻣﯽ ﺑﺎﯾﺴﺖ ﺣﺪاﻗﻞ ﯾﮏ ﺧﻂ ﮐﺎﻣﻨﺖ داﺷﺘﻪ ﺑﺎﺷﻨﺪ.
- ﮐﺎﻣﻨﺖ ﻓﺎرﺳﯽ ﯾﺎ اﻧﮕﻠﯿﺴﯽ ﻣﻮردی ﻧﺪارد اﻣﺎ از ﻓﯿﻨﮕﻠﯿﺶ (!) ﻧﻮﺷﺘﻦ ﭘﺮﻫﯿﺰ ﮐﻨﯿﺪ.
- اﺳﺘﻔﺎده از ﮐﺘﺎﺑﺨﺎﻧﻪ ﻫﺎ و ﻓﺮﯾﻢ ورک ﻫﺎ در ﭘﺮوژه ﻣﺠﺎز **ﻧﻤﯽ ﺑﺎﺷﺪ**.
- از آﻧﺠﺎﯾﯽ ﮐﻪ اﯾﻦ ﭘﺮوژه در ﻗﺎﻟﺐ **اﻣﺘﺤﺎن ﻣﯿﺎﻧﺘﺮم** ﻣﯽ ﺑﺎﺷﺪ از ﺗﻐﯿﯿﺮ دادن ﺻﻮرت ﻣﺴﺎﻟﻪ ﯾﺎ اﻧﺠﺎم ﻣﻮارد ﺧﺎرج از ﻣﻮارد ﻣﻄﺮح ﺷﺪه ﺧﻮدداری ﮐﻨﯿﺪ.

## ۲. ۶ ﭘﺮﺳﺶ ﻫﺎی ﻣﺘﺪاول

**ﭘﺮﺳﺶ** ﻣﻨﻈﻮرﺗﺎن از اﯾﻦ ﮐﻪ “درﺻﻮرﺗﯽ ﮐﻪ اﺑﻌﺎد ﺻﻔﺤﻪ ﻣﻨﺎﺳﺐ ﻧﺒﺎﺷﺪ ﻋﮑﺲ در وﺳﻂ زوم ﺷﻮد ﭼﯿﺴﺖ؟” ﻣﮕﺮ ﻗﺮار ﻧﯿﺴﺖ ﻋﮑﺲ ﻣﺎ ﮐﻞ ﺻﻔﺤﻪ رو ﺑﭙﻮﺷﺎﻧﺪ و ﻣﺘﻨﺎﺳﺐ ﺑﺎ ﺗﻐﯿﯿﺮات ﺻﻔﺤﻪ اﻧﺪازه اش ﻧﯿﺰ ﺗﻐﯿﯿﺮ ﮐﻨﺪ؟

**ﭘﺎﺳﺦ** ﺑﺒﯿﻨﯿﺪ ﻋﮑﺴﯽ ﮐﻪ اﻧﺘﺨﺎب ﻣﯽﮐﻨﯿﺪ ﻗﺎﻋﺪﺗﺎ ﯾﮏ اﻧﺪازه ﻣﺸﺨﺼﯽ دارد ﮐﻪ اﮔﺮ در ﺻﻔﺤﻪ ﺟﺎ ﻧﺸﻮد ﺑﻪ اﺟﺒﺎر ﻣﯽ ﺑﺎﯾﺴﺖ ﻗﺴﻤﺘﯽ از آن را ﻧﻤﺎﯾﺶ دﻫﯿﺪ، ﻣﻨﻈﻮر ﻣﻦ اﯾﻦ ﺑﻮد ﮐﻪ اﯾﻦ ﻗﺴﻤﺖ از وﺳﻂ ﻋﮑﺲ ﺑﺮﯾﺪه ﺷﺪه ﺑﺎﺷﺪ.

**ﭘﺮﺳﺶ** ﺑﺮای اﻃﻼﻋﺎﺗﯽ ﮐﻪ داﺧﻞ ﻣﺴﺘﻄﯿﻞ ﻣﯿﺎﻧﯽ ﻗﺎﺑﻞ ﻧﻤﺎﯾﺶ اﺳﺖ، اﺑﺘﺪا ﺑﺎﯾﺪ ﻫﻤﻪ ﺳﻔﯿﻨﻪ ﻫﺎ در ﺳﻤﺖ ﭼﭗ ﺻﻔﺤﻪ ﻣﺸﺨﺺ ﺑﺎﺷﻨﺪ، ﺳﻤﺖ راﺳﺖ اﻃﻼﻋﺎت ﻫﺮ ﺳﻔﯿﻨﻪ اﻧﺘﺨﺎﺑﯽ ﺑﺎﺷﺪ؟ ﯾﺎ ﻓﺮﻣﺘﯽ ﮐﻪ اﯾﻦ ﻫﺎ ﻣﯿﺘﻮﻧﻦ ﻗﺮار ﺑﮕﯿﺮﻧﺪ ﺧﯿﻠﯽ ﻣﻬﻢ ﻧﯿﺴﺖ؟

**ﭘﺎﺳﺦ** ﻓﺮﻣﺖ ﮐﻠﯽ ﺑﻪ اﯾﻦ ﺷﮑﻞ اﺳﺖ اﻣﺎ ﻫﺮ ﺗﻐﯿﯿﺮی در اﯾﻦ ﻗﺴﻤﺖ ﻣﻤﮑﻦ اﺳﺖ.

**ﭘﺮﺳﺶ** ﻫﻨﺪل ﮐﺮدن Not Found 404ﻫﺎی api ﭼﻄﻮری ﺑﺎﯾﺪ ﺑﺎﺷﺪ؟

**ﭘﺎﺳﺦ** در ﺣﺎﻟﺖ اﺟﺒﺎری ﺷﻤﺎ ﺑﺎ ﭼﻨﯿﻦ ﭼﯿﺰی ﺑﺮﺧﻮد ﻧﻤﯽﮐﻨﯿﺪ ﭼﺮا ﮐﻪ ﻫﻤﯿﺸﻪ از ﻟﯿﻨﮏ ﻫﺎی ﻣﻌﺘﺒﺮ اﺳﺘﻔﺎده ﮐﺮده و ﺷﻨﺎﺳﻪ ﻓﯿﻠﻢ ﻫﺎ

ﻧﯿﺰ در ﮐﺪ ﻧﻮﺷﺘﻪ ﺷﺪه اﺳﺖ.

**ﭘﺮﺳﺶ** ﮐﺪﻫﺎی js و html در ﭼﻪ ﺣﺪ ﮐﺎﻣﻨﺖ ﻻزم دارﻧﺪ؟ اﮔﺮ اﺳﻢ ﻣﺘﻐﯿﺮﻫﺎ و ﻣﺘﺪﻫﺎ ﮔﻮﯾﺎ ﺑﺎﺷﻨﺪ ﺑﺎز ﻫﻢ ﻻزم اﺳﺖ؟

**ﭘﺎﺳﺦ** در راﺑﻄﻪ ﺑﺎ html ﺗﻨﻬﺎ ﻧﯿﺎز اﺳﺖ ﮐﻪ ﻗﺴﻤﺖ ﻫﺎی ﮐﻠﯽ را ﻣﻌﺮﻓﯽ ﮐﻨﯿﺪ، ﺑﻪ ﻃﻮر ﻣﺜﺎل ﻣﺸﺨﺺ ﮐﻨﯿﺪ از اﯾﻦ ﺑﺨﺶ ﺑﺮای ﻟﯿﺴﺖ ﮐﺮدن ﮐﺸﺘﯽ ﻓﻀﺎﯾﯽ ﻫﺎ اﺳﺘﻔﺎده ﺧﻮاﻫﯿﺪ ﮐﺮد. در راﺑﻄﻪ js در ﺻﻮرﺗﯽ ﮐﻪ از ﻧﺎم ﻫﺎی ﻣﻨﺎﺳﺐ ﺑﺮای ﺗﻮاﺑﻊ و ﻣﺘﻐﯿﺮﻫﺎی اﺳﺘﻔﺎده

ﮐﻨﯿﺪ ﮐﻔﺎﯾﺖ ﺧﻮاﻫﺪ ﮐﺮد. در راﺑﻄﻪ ﺑﺎ css ﻫﻤﺎﻧﻄﻮر ﮐﻪ ﺑﯿﺎن ﺷﺪ ﺗﻮﺿﯿﺢ ﺑﻼک ﻫﺎ اﺟﺒﺎری ﻣﯽ ﺑﺎﺷﺪ. ﺑﻪ ﻃﻮر ﻣﺜﺎل اﯾﻦ ﺑﻼک ﻗﺼﺪ دارد ﻋﮑﺲ ﭘﺲ زﻣﯿﻨﻪ ﺑﺎ ﮐﻪ ﺑﺎ background# ﻣﺸﺨﺺ ﺷﺪه اﺳﺖ را در ﺗﻤﺎم ﺻﺤﻔﻪ ﻧﻤﺎﯾﺶ داده و در وﺳﻂ ﻗﺮار
دﻫﺪ.

<center>
    <img src="resorces/../resources/Aspose.Words.5beb3cff-3782-42d9-88c8-ba0a913d156f.006.png" />
</center>

#
- All of your cpp files and dfolders should be in the cpp folder and the front-end files should be in the front folder.
- Send assignments to my email address before the deadline.
- After the deadline, the assignment will push to the repository. in the students number folder. (example: 12345678)
- create a pull request to the repository.

<h2 align="center"> Good Luck </h2>
