/*
* Program 5: Jolly Banker
* transaction.cpp
* Implementation file of the Transaction class that represents a transaction
* in the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#include <iostream>
#include <vector>
#include <string>
#include "transaction.h"
using namespace std;

// Constructor
Transaction::Transaction(){

}

// Destructor
Transaction::~Transaction(){

}

// While opening an account
Transaction::Transaction(char type, int acc_id, string last, string first, bool s){
    type_ = type;
    acc_id_ = acc_id;
    last_ = last;
    first_ = first;
    success_ = s;
}

// Depositting or Withdrawing
Transaction::Transaction(char type, int acc_id, int fund_id, int amount, bool s){
    type_ = type;
    acc_id_ = acc_id;
    fund_id_ = fund_id;
    amount_ = amount;
    success_ = s;
}

// Transferring assets
Transaction::Transaction(char type, int acc_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, bool s){
    type_ = type;
    acc_id_ = acc_id;
    fund_id_ = fund_id;
    destiny_acc_id_ = transfer_acc_id;
    destiny_fund_id_ = transfer_fund_id;
    amount_ = amount;
    success_ = s;
}

// Print by client account
Transaction::Transaction(char type, int acc_id, bool s){
    type_ = type;
    acc_id_ = acc_id;
    success_ = s;
}

// Print by fund for a client account
Transaction::Transaction(char type, int acc_id, int fund_id, bool s){
    type_ = type;
    acc_id_ = acc_id;
    fund_id_ = fund_id;
    success_ = s;
}


// getters-setters
char Transaction::type() const{
    return type_;
}

int Transaction::accountID() const{
    return acc_id_;
}

int Transaction::fundID() const{
    return fund_id_;
}

string Transaction::firstname() const{
    return first_;
}
string Transaction::lastname() const{
    return last_;
}

int Transaction::destinyaccountID() const{
    return destiny_acc_id_;
}

int Transaction::destinyfundID() const{
    return destiny_fund_id_;
}

int Transaction::amount() const{
    return amount_;
}

// Status() - returns the success status of a transaction
bool Transaction::Status() const{
    return success_;
}

ostream& operator<<(ostream& stream, const Transaction& t){
    // all passing scenarios
    if(t.Status()){
        // Deposit and Withdraw
        if((t.type() == 'D') || (t.type() == 'd') || (t.type() == 'W') || (t.type() == 'w')){
            stream << " " << t.type() << " " << t.accountID() << " " << t.fundID() << " " << t.amount();
        }
        // Transferring assets
        else if((t.type() == 'T') || (t.type() == 't')){
            // cout << "Entering T" << endl;
            stream << " " << t.type() << " " << t.accountID() << " " << t.fundID() 
            << " " << t.destinyaccountID() << " " << t.destinyfundID() << " " << t.amount();
        }
        else if(t.type() == 'O' || t.type() == 'o'){
            stream << "Opened an account for " << t.accountID() << endl;
        }
        else{
            stream << " " << t.type() << " is an invalid transaction type.";
        }
    }
    // Failure scenarios
    else{
        if((t.type() == 'D') || (t.type() == 'd')){
            stream << " " << t.type() << " " << t.accountID() << " " << t.fundID() << " " << t.amount() << " (Failed)";
        }
        else if ((t.type() == 'W') || (t.type() == 'w')){
            stream << " " << t.type() << " " << t.accountID() << " " << t.fundID() << " " << t.amount() << " (Failed)";
        }
        else if((t.type() == 'T') || (t.type() == 't')){
            stream << " " << t.type() << " " << t.accountID() << " " << t.fundID() 
            << " " << t.destinyaccountID() << " " << t.destinyfundID() << " " << t.amount() << " (Failed)";
        }
        else if((t.type() == 'O') || (t.type() == 'o')){
            stream << "Account " << t.accountID()  << " already exists" << endl;
        }
        else{
            stream << " " << t.type() << " is an invalid transaction type.";
        }
    }
    return stream << endl;
}