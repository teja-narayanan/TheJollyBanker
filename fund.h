/*
* Program 5: Jolly Banker
* fund.h
* Header file of the Fund class that represents each of the 
* 8 Fund types in the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#ifndef FUND_H_
#define FUND_H_

#include <stdio.h>
#include "transaction.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Fund{
    public:
        // constructor
        Fund(string name);
        // destructor
        ~Fund();

        // getters-setters
        string name() const;
        int balance() const;
        vector<Transaction> transactions();

        // Actions
        bool Deposit(int amount);
        bool Withdraw(int amount);
        bool BalanceCheck(int amount);
        bool Log(Transaction t);
        void PrintFundHistory();
        void PrintHistory();

    private:
        // data members
        string name_;
        int balance_ = 0;
        vector<Transaction> p_transactions_;
};
#endif