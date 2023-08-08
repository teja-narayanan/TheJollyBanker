/*
* Program 5: Jolly Banker
* fund.cpp
* Implementation file of the Fund class that represents each
* of the 8 Funds in the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#include <stdio.h>
#include "fund.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Constructor
Fund::Fund(string name){
    name_ = name;
    balance_ = 0;
}

// Destructor
Fund::~Fund(){

}

string Fund::name() const{
    return name_;
}


int Fund::balance() const{
    return balance_;
}

vector<Transaction> Fund::transactions(){
    return p_transactions_;
}

// Deposit() - deposits the given amount into the balance
bool Fund::Deposit(int amount){
    if(amount >= 0){
        balance_ += amount;
        return true;
    }
    return false;
}

// Withdraw() - withdraws the given amount if it is a valid amount
// between 0 and the balance
bool Fund::Withdraw(int amount){
    if(amount >= 0 && amount <= balance_){
        balance_ -= amount;
        return true;
    }
    return false;
}

// checks if fund has sufficient amount
bool Fund::BalanceCheck(int amount){
    if(balance_ >= amount){
        return true;
    }
    return false;
}

// Log() - adds the fund details into a transaction vector
bool Fund::Log(Transaction t){
    p_transactions_.push_back(t);
    return true;
}

// PrintFundHistory() - prints the history by fund for each fund
void Fund::PrintFundHistory(){
    for(unsigned int i = 0; i < p_transactions_.size(); i++){
        cout << " " << p_transactions_[i];
    }

}

// PrintHistory() - prints the vector for each fund
void Fund::PrintHistory(){
    if(p_transactions_.size() == 0){
        return;
    }
    else{
        cout << name() << ": $" << balance() << endl;
        for(unsigned int i = 0; i < p_transactions_.size(); i++){
            cout << " " << p_transactions_[i];
        }
    }
}
