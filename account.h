/*
* Program 5: Jolly Banker
* account.h
* Header file of the Account class that represents a client account 
* in the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
#include <vector>
#include "transaction.h"
#include "fund.h"
using namespace std;

const int FUND_MAX = 8;

// for the special linked accounts
const int MONEY_MARKET = 0;
const int PRIME_MONEY_MARKET = 1;
const int LONG_TERM_BOND= 2;
const int SHORT_TERM_BOND = 3;


class Account{
    friend ostream& operator<<(ostream& stream, const Account& a);
    public:
        // Constructors
        Account();
        Account(const Account& account);
        Account(unsigned int acc_id, string first, string last);
        ~Account();

        // getters-setters
        string firstname() const;
        string lastname() const;
        int id() const;


        // Actions
        bool AddToFund(int fund_id, int amount, char type, int src_acc, int dest_acc, int dest_fund);
        bool RemoveFunds(int fund_id, int amount, char type, int src_acc, int dest_acc, int dest_fund);

        bool RemoveFromMultipleFunds(int primary, int secondary, int amount);
        void PrintTransactions();
        void PrintTransactions(int fund_id);

        // operator overloads
        Account& operator=(const Account& account);
        
        bool operator==(const Account& a) const;
        bool operator!=(const Account& a) const;
        bool operator<(const Account& a) const;
        bool operator>(const Account& a) const;


    private:
        // data members
        string last_;
        string first_;
        int acc_id_ = 0;
        Fund* funds[FUND_MAX];    
        vector<Transaction> p_transactions_;    

        // helper data members
        vector<string> list_ {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", 
                                "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund"};
        string list(int id) const;

};
#endif