/*
* Program 5: Jolly Banker
* bank.cpp
* Implementation file of the Bank class that defines and performs 
* the 3 main phases of the Jolly Banker application
* @author Teja Narayanan
* 12/9/2022
*/
#include "bank.h"
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// No-arg constructor
Bank::Bank(){

}

// Destructor
Bank::~Bank(){

}

// ReadTransactions(string file_name) -- Function reads in a string of transactions from 
// a file into an in-memory queue. These transactions can open accounts, withdraw funds, 
// deposit funds, transfer funds, or ask for transactional history to be printed for each
// account or by specifc funds
bool Bank::ReadTransactions(string file_name){
    ifstream file;
    string line; // reads each line in the transaction
    // open a file stream
    file.open(file_name);

    // if file not available
    if(!file){
        cout << "Cannot open " << file_name << endl;
        return false;
    }

    // traverse until the end of the given file
    while(!file.eof()){
        // get each line in the file
        getline(file, line);
        if(line.empty()){
            break;
        }

        // parse each line to acquire the components
        istringstream parseLine(line);

        // each line would be syntactically correct
        // get the type and parse it
        char type;
        parseLine >> type;

        // If opening an account
        if((type == 'O') || (type == 'o')){
            int acc_id = 0;
            string last = "";
            string first = "";

            parseLine >> acc_id >> last >> first;
            Transaction t(type, acc_id, last, first, true);
            transactions_.push(t);
        }

        // If depositting or withdrawing amount
        else if((type == 'D') || (type == 'd') || (type == 'W') || (type == 'w')){
            int acc_id;
            int fund_id; 
            int amount;

            parseLine >> acc_id >> fund_id >> amount;
            Transaction t(type, acc_id, fund_id, amount, true);
            transactions_.push(t);
        }
        
        // If transferring amounts
        else if((type == 'T') || (type == 't')){
            int acc_id;
            int fund_id;
            int transfer_acc_id;
            int transfer_fund_id;
            int amount;

            parseLine >> acc_id >> fund_id >> transfer_acc_id >> transfer_fund_id >> amount;
            Transaction t(type, acc_id, fund_id, transfer_acc_id, transfer_fund_id, amount, true);
            transactions_.push(t);
        }
        
        // If printing transaction history by account
        else if((type == 'A') || (type == 'a')){
            int acc_id;
            parseLine >> acc_id;
            Transaction t(type, acc_id, true);
            transactions_.push(t);
        }

        // If printing transaction history by fund for an account
        else if((type == 'F') || (type == 'f')){
            int acc_id;
            int fund_id;
            parseLine >> acc_id >> fund_id;
            Transaction t(type, acc_id, fund_id, true);
            transactions_.push(t);
        }

        // Invalid transaction type
        else{
            cerr << "ERROR: Invalid transaction type!" << endl;
        }
    }
    return false;
}


// ProcessTransactions() -- Function will read from the queue and process the transactions 
// in order and store into Binary Search Tree
bool Bank::ProcessTransactions(){
    // check if queue is not empty
    while(!transactions_.empty()){
        // Make a transaction instance to store the value from queue
        Transaction process = transactions_.front();
        transactions_.pop();

        // If withdrawal type
        if((process.type() == 'W') || (process.type() == 'w')){
            int acc_id = process.accountID();
            int fund_id = process.fundID();
            int amount = process.amount();

            // Make a temp account
            Account* account;

            // check if acc_id exists in the BST
            if(accounts_.Retrieve(acc_id, account)){
                // withdraw amount from account
                account->RemoveFunds(fund_id, amount, process.type(), acc_id, 0, 0);
            }
            // Account ID not found
            else{
                cerr << "ERROR: Account " << acc_id << " not found. Withdrawal refused." << endl;
            }
        }
        
        // If Deposit type
        else if((process.type() == 'D') || (process.type() == 'd')){
            int acc_id = process.accountID();
            int fund_id = process.fundID();
            int amount = process.amount();

            // Make a temp account
            Account* account;

            // check if acc_id exists in the BST
            if(accounts_.Retrieve(acc_id, account)){
                // Deposit amount into account
                account->AddToFund(fund_id, amount, process.type(), acc_id, 0, 0);
            }
            // Error handling
            else{
                cerr << "ERROR: Account " << acc_id << " not found. Deposition refused." << endl;
            }
        }

        // If Transfer type
        else if((process.type() == 'T') || (process.type() == 't')){
            // Check for transfer status
            if(process.Status()){
                int acc_id = process.accountID();
                int fund_id = process.fundID();
                int transfer_acc_id = process.destinyaccountID();
                int transfer_fund_id = process.destinyfundID();
                int amount = process.amount();

                Account* source;
                Account* destination;

                if((accounts_.Retrieve(acc_id, source)) && (accounts_.Retrieve(transfer_acc_id, destination))){
                    if(source->RemoveFunds(fund_id, amount, process.type(), acc_id, transfer_acc_id, transfer_fund_id)){
                        destination->AddToFund(transfer_fund_id, amount, process.type(), transfer_acc_id, acc_id, fund_id);
                    }
                }
                else{
                    if(!accounts_.Retrieve(acc_id, source)){
                        cerr << "ERROR: Account " << acc_id << " not found. Transferal refused." << endl;
                    }
                    else{
                        cerr << "ERROR: Account " << transfer_acc_id << " not found. Transferal refused." << endl;
                    }
                }
            }
        }

        // If Opening an account
        else if((process.type() == 'O') || (process.type() == 'o')){
            Account* account;
            int acc_id = process.accountID();

            // check if acc_id exists in the BST
            if(accounts_.Retrieve(acc_id, account)){
                // handle error
                cerr << "ERROR: Account " << acc_id << " is already open. Transaction refused." << endl;
            }
            // make a new account and insert it into BST
            else{
                Account* ins_account = new Account(process.accountID(), process.firstname(), process.lastname());
                accounts_.Insert(ins_account);
            }
        }

        // If printing transaction history by account
        else if((process.type() == 'A') || (process.type() == 'a')){
            int acc_id = process.accountID();
            Account* account;

            if(accounts_.Retrieve(acc_id, account)){
                account->PrintTransactions();
            }
            else{
                if(process.accountID() <= 0){
                    cerr << "ERROR: Account ID cannot be negative: " << process.accountID() << endl;

                }
                else{
                    cerr << "ERROR: Account " << process.accountID() << " not found. Could not print historical transactions." << endl;
                }
            }
        }

        // If printing transactional history by fund for a given account
        else if((process.type() == 'F') || (process.type() == 'f')){
            int acc_id = process.accountID();
            int fund_id = process.fundID();

            Account* account;
            
            if(accounts_.Retrieve(acc_id, account)){
                account->PrintTransactions(fund_id);
            }
            else{
                cerr << "ERROR: Could not print historical transactions by fund for an invalid account " << process.accountID() << endl;
            }
        }
    }
    return true;
}

// PrintTransactions() -- Once queue has been depleted, this function prints out 
// all open accounts and final balances in those accounts.
void Bank::PrintTransactions(){
    cout << "\nFINAL BALANCES:" << endl;
    accounts_.Display();
}