#include "bank.h"
#include <iostream>

int main(){
    Bank jolly_banker;
    // jolly_banker.ReadTransactions("dimpsey_negative_2.txt");
    // jolly_banker.ReadTransactions("test.txt");
    jolly_banker.ReadTransactions("bank_trans_in.txt");
    jolly_banker.ProcessTransactions();
    jolly_banker.PrintTransactions();
}

// int main(int argc, char* argv[]){
//     if(argc != 2){
//         cout << "Invalid argument entered. Could not process Jolly Banker, please try again." << endl;
//     }
//     string file_name = argv[1];
//     Bank jolly_banker;
//     jolly_banker.ReadTransactions(file_name);
//     jolly_banker.ProcessTransactions();
//     jolly_banker.PrintTransactions();
// }