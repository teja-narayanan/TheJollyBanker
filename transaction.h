/*
* Program 5: Jolly Banker
* transaction.h
* Header file of the Transaction class that represents a transaction
* in the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction{
    friend ostream& operator<<(ostream& stream, const Transaction& t);
    public:
        // Constructor-destructor
        Transaction();
        ~Transaction();

        // While opening an account
        Transaction(char type, int acc_id, string last, string first, bool s);

        // Depositting or Withdrawing
        Transaction(char type, int acc_id, int fund_id, int amount, bool s);

        // Transferring assets
        Transaction(char type, int acc_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, bool s);

        // Print by client account
        Transaction(char type, int acc_id, bool s);

        // Print by fund for a client account
        Transaction(char type, int acc_id, int fund_id, bool s);


        // getters-setters
        char type() const;
        int accountID() const;
        int fundID() const;
        // string fund(int fund_id) const;
        string firstname() const;
        string lastname() const;
        int destinyaccountID() const;
        int destinyfundID() const;
        int amount() const;

        // Actions
        bool Status() const;

    private:
        // data members
        char type_;
        int acc_id_;
        string last_;
        string first_;
        int fund_id_;

        int destiny_acc_id_;
        int destiny_fund_id_;
        
        int amount_;
        bool success_;
};
#endif