/*
* Program 5: Jolly Banker
* account.cpp
* Implementation file of the Account class that represents a client account 
* in the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#include "account.h"
#include "transaction.h"
#include <string>
#include <vector>
using namespace std;

// No arg constructor
Account::Account(){

}

// Copy constructor (since memory is dynamically allocated)
// Can use the default copy constructor
Account::Account(const Account& account){

}

// Main constructor that creates an account with an unique ID,
// first name, and last name
Account::Account(unsigned int acc_id, string first, string last){
    acc_id_ = acc_id;
    first_ = first;
    last_ = last;
    Transaction t('O', acc_id, last, first, true);
    p_transactions_.push_back(t);

    funds[0] = new Fund("Money Market");
    funds[1] = new Fund("Prime Money Market");
    funds[2] = new Fund("Long-Term Bond");
    funds[3] = new Fund("Short-Term Bond");
    funds[4] = new Fund("500 Index Fund");
    funds[5] = new Fund("Capital Value Fund");
    funds[6] = new Fund("Growth Equity Fund");
    funds[7] = new Fund("Growth Index Fund");
}

// Destructor (uses the default)
Account::~Account(){

}

// getters-setters
string Account::firstname() const{
    return first_;
}

string Account::lastname() const{
    return last_;
}

int Account::id() const{
    return acc_id_;
}

// private function - used in PrintTransaction(int fund_id) routine
string Account::list(int id) const{
    return list_.at(id);    
}

// Actions

// AddToFund() - Deposits amount in this account's desired fund
bool Account::AddToFund(int fund_id, int amount, char type, int src_acc, int dest_acc, int dest_fund){
    // Error handling for fund ID
    if(fund_id > 7 || fund_id < 0){
        cerr << "ERROR: Cannot Deposit/Transfer " << amount << " to Account: " << src_acc << " Fund: " << fund_id << ". " << "Fund ID is invalid." << endl;
        return false;
    }

    // If Deposit transaction type
    if(type != 'T'){
        // check for amount's validity
        if(amount >= 0){
            funds[fund_id]->Deposit(amount);
            Transaction t('D', acc_id_, fund_id, amount, true);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            return true;
        }
        // invalid amount
        else{
            cerr << "ERROR: Unable to Deposit " << amount << " to Account: " << first_ << " " << last_ << " " << list_[fund_id] << " (Account: " << acc_id_ << ")" << endl;
            Transaction t('D', acc_id_, fund_id, amount, false);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            // cerr << t;
            return false;
        }
    }
    // If Transfer transaction type
    else{
        if(dest_fund > 7 || dest_fund < 0){
            cerr << "ERROR: Account " << dest_acc << " Fund ID "  << dest_fund << " is invalid. Transferal failed." << endl;
            return false;
        }

        if(amount >= 0){
            funds[fund_id]->Deposit(amount);
            Transaction t('T', dest_acc, dest_fund, src_acc, fund_id,  amount, true);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            return true;
        }
        else{
            cerr << "ERROR: Unable to transfer " << amount << " from Account: " << acc_id_ << " " << list_[fund_id] << " to Account: " << dest_acc << " " << list_[dest_fund] << endl;
            Transaction t('T', dest_acc, dest_fund, src_acc, fund_id,  amount, false);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            // cerr << t;
            return false;
        }
    }
}


// RemoveFunds() - Withdraw amount from this account's desired fund ID
bool Account::RemoveFunds(int fund_id, int amount, char type, int src_acc, int dest_acc, int dest_fund){

    // Error handling for Fund ID
    if(fund_id > 7 || fund_id < 0){
        cerr << "ERROR: Cannot Withdraw/Transfer " << amount << " from account: " << src_acc << " fund: " << fund_id << ". " << "Fund ID is invalid." << endl;
        return false;
    }    

    // If Withdraw transaction type
    if(type != 'T'){
        // check for amount's validity
        if((amount >= 0) && (amount <= funds[fund_id]->balance())){
            Transaction t('W', acc_id_, fund_id, amount, true);
            funds[fund_id]->Withdraw(amount);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            return true;
        }

        // Special case for each of the linked funds
        else if((fund_id == MONEY_MARKET) && (amount >= 0 ) && (amount <= funds[MONEY_MARKET]->balance() + funds[PRIME_MONEY_MARKET]->balance())){
            return RemoveFromMultipleFunds(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
        }

        else if((fund_id == PRIME_MONEY_MARKET) && (amount >= 0 ) &&  (amount <= funds[MONEY_MARKET]->balance() + funds[PRIME_MONEY_MARKET]->balance())){
            return RemoveFromMultipleFunds(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
        }

        else if((fund_id == LONG_TERM_BOND) && (amount >= 0 ) &&  (amount <= funds[LONG_TERM_BOND]->balance() + funds[SHORT_TERM_BOND]->balance())){
            return RemoveFromMultipleFunds(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
        }

        else if((fund_id == SHORT_TERM_BOND) && (amount >= 0 ) && (amount <= funds[SHORT_TERM_BOND]->balance() + funds[LONG_TERM_BOND]->balance())){
            return RemoveFromMultipleFunds(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
        }
        // invalid amount
        else{
            cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << first_ << " " << last_ << " " << list_[fund_id] << " (Account: " << acc_id_ << ")" << endl; // This is the change I made
            Transaction t('W', acc_id_, fund_id, amount, false);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            // cerr << t;
            return false;
        }
    }
    // If Transfer transaction type
    else{
        if(dest_fund > 7 || dest_fund < 0){
            cerr << "ERROR: Account " << dest_acc << " Fund ID "  << dest_fund << " is invalid. Transferal failed." << endl;
            return false;
        }

        if((amount >= 0) && (amount <= funds[fund_id]->balance())){
            Transaction t('T', acc_id_, fund_id, dest_acc, dest_fund, amount, true);
            funds[fund_id]->Withdraw(amount);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            return true;
        }
        // Special case for each of the linked funds
        else if((fund_id == MONEY_MARKET) && (amount >= 0) && (amount <= funds[MONEY_MARKET]->balance() + funds[PRIME_MONEY_MARKET]->balance())){
            return RemoveFromMultipleFunds(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
        }

        else if((fund_id == PRIME_MONEY_MARKET) && (amount >= 0) && (amount <= funds[MONEY_MARKET]->balance() + funds[PRIME_MONEY_MARKET]->balance())){
            return RemoveFromMultipleFunds(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
        }

        else if((fund_id == LONG_TERM_BOND) && (amount >= 0) && (amount <= funds[LONG_TERM_BOND]->balance() + funds[SHORT_TERM_BOND]->balance())){
            return RemoveFromMultipleFunds(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
        }

        else if((fund_id == SHORT_TERM_BOND) && (amount >= 0) && (amount <= funds[SHORT_TERM_BOND]->balance() + funds[LONG_TERM_BOND]->balance())){
            return RemoveFromMultipleFunds(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
        }
        else{
            cerr << "ERROR: Unable to transfer " << amount << " from Account: " << acc_id_ << " " << list_[fund_id] << " to Account: " << dest_acc << " " << list_[dest_fund] << endl;
            Transaction t('T', acc_id_, fund_id, dest_acc, dest_fund, amount, false);
            funds[fund_id]->Log(t);
            p_transactions_.push_back(t);
            return false;
        }
    }
}

// RemoveFromMultipleFunds() - Helper method for withdrawing from linked accounts 
// -- Money Market and Prime Money Market, Long-Term Bond and Short-Term Bond
bool Account::RemoveFromMultipleFunds(int primary, int secondary, int amount){
    int remove_amount = amount;
    int balance = funds[primary]->balance();
    remove_amount -= balance;
    
    funds[primary]->Withdraw(balance);
    Transaction t('W', acc_id_, primary, balance, true);
    p_transactions_.push_back(t);
    funds[primary]->Log(t);

    funds[secondary]->Withdraw(remove_amount);
    Transaction w('W', acc_id_, secondary, remove_amount, true);
    p_transactions_.push_back(w);
    funds[secondary]->Log(w);
    return true;
}

// PrintTransactions() -- Prints all historical transactions by account
// Corresponds to 'A' Transaction type from the input file
void Account::PrintTransactions(){
    cout << "\nTransaction History for " << first_ << " " << last_ << " by fund." << endl;
    for(int i = 0; i < FUND_MAX; i++){
        funds[i]->PrintHistory();
    }
}

// PrintTransactions(int fund_id) -- Overloaded funtion 
// Prints all historical transactions by fund for any given account
// Corresponds to 'F' Transaction type from the input file
void Account::PrintTransactions(int fund_id){
    // Error handling for fund ID

    if(fund_id > 7 || fund_id < 0){
        cerr << "ERROR: Cannot Print Transactions by fund. Fund ID cannot be " << fund_id << endl;
    }
    else{
        cout << "\nTransaction History for " << first_ << " " << last_ << " " << funds[fund_id]->name() << ": $" << funds[fund_id]->balance() << endl;
        for(Transaction t: funds[fund_id]->transactions()){
            cout << " " << t;
        }
    }
}

// operator<< -- overloaded to be complete and consistent with the class design
ostream& operator<<(ostream& stream, const Account& a){
    stream << a.firstname() << " " << a.lastname() << " Account ID: " << a.id() << endl;
    for(int i = 0; i < FUND_MAX; i++){
        stream << "    " << a.funds[i]->name() << ": " << "$" << a.funds[i]->balance() << endl;
    }
    return stream;
}

// operator= -- overloaded to be complete and consistent with the class design
Account& Account::operator=(const Account& account){
    if(this == &account){
	return *this;
    }
    return *this;
}

// operator== -- overloaded to be complete and consistent with the class design
bool Account::operator==(const Account &a) const{
    return (acc_id_ == a.id());
}

// operator!= -- overloaded to be complete and consistent with the class design
bool Account::operator!=(const Account &a) const{
    return !(acc_id_ == a.id());
}

// operator< -- overloaded to be complete and consistent with the class design
bool Account::operator<(const Account &a) const{
    return (acc_id_ < a.id());
}

// operator> -- overloaded to be complete and consistent with the class design
bool Account::operator>(const Account &a) const{
    return (acc_id_ > a.id());
}