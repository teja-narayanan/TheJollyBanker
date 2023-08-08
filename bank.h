/*
* Program 5: Jolly Banker
* bank.h
* Header file of the Bank class that defines the 3 main phases of 
* the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#ifndef BANK_H_
#define BANK_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <queue>
#include "bstree.h"
#include "account.h"
#include "transaction.h"

using namespace std;

class Bank{
    public:
        // Constructors
        Bank();
        ~Bank();

        // Actions
        bool ReadTransactions(string file_name);
        bool ProcessTransactions();
        void PrintTransactions();
    
    private:
        // data members
        BSTree accounts_;
        queue<Transaction> transactions_; 
};
#endif