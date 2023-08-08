/*
* Program 5: Jolly Banker
* bstree.h
* Header file of the BST class that designs a typical Binary Search Tree
* data structure specifically for the Account class
* @author Teja Narayanan
* 12/9/2022
*/
#ifndef BSTree_h
#define BSTree_h
#include "account.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class BSTree {
friend ostream& operator<<(ostream &out, const BSTree& tree);

public:
    // Constructor 
    BSTree();
    BSTree(const BSTree& tree);
    ~BSTree();
 
    // Actions
    bool Insert(Account* p_account);
    void DeleteList();
    bool Delete(const int& acc_id, Account*& account);
    bool Retrieve(int acct_ID, Account*& p_account) const;
    void Display() const;
    bool isEmpty() const;
    int Size() const;

    // Assignment operator overload
    BSTree& operator=(const BSTree& tree);

private:
    // Node class
    struct Node{
        Account* p_acct;
        Node* right;
        Node* left;
    };
    // data members
    Node* root_ = nullptr;

    // helper methods
    bool Retrieve(int acct_ID, Account*& p_account, Node* root) const;
    bool Insert(Account* p_account, Node* &root);
    Node* Delete(const int& acc_id, Account*& account, Node* &root);
    void Display(Node* root) const;
    void DeleteList(Node* root);
    Node* GetMinKey(Node* node);
    Node* CopyTree(Node* node);
};
#endif