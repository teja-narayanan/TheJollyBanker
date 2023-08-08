/*
* Program 5: Jolly Banker
* bstree.cpp
* Implementation file of the BST class that implements typical 
* Binary Search Tree data structure specifically for the Account class
* @author Teja Narayanan
* 12/9/2022
*/
#include "bstree.h"

// No arg constructor
BSTree::BSTree(){
}

// Copy constructor (can use the default since memory is not allocated dynamically)
BSTree::BSTree(const BSTree& tree){

}

// Destructor -- deletes the entire BST
BSTree::~BSTree(){
    DeleteList();
}

// Insert() - Inserts an Account instance into the BST using the acc_id as the key
bool BSTree::Insert(Account* p_account){
    // base case
    if (p_account->id() < 0){
            cerr << "ERROR: Account ID cannot be negative: " << p_account->id() << endl;
            return false;
        }

    else{
        // call for the facade method
        return Insert(p_account, root_);
    }
    return false;
}

// Insert -- Facade method 
bool BSTree::Insert(Account* p_account, Node*& root){
    if(root == nullptr){
        root = new Node;
        root->p_acct = p_account;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    int racctID = root->p_acct->id();
    if(p_account->id() > racctID){
        Insert(p_account, root->right);
    }
    else if(p_account->id() < racctID){
        Insert(p_account, root->left);
    }
    return false;
}

// Retrieve() - retrieve object, first parameter is the ID of the account
// second parameter holds pointer to found object, nullptr if not found
bool BSTree::Retrieve(int acct_num, Account*& p_account) const{
    return Retrieve(acct_num, p_account, root_);
}

// Retrieve() -- facade method
bool BSTree::Retrieve(int acct_num, Account*& p_account, Node* root) const{
    if(root != nullptr){
        if(acct_num == root->p_acct->id()){
            p_account = root->p_acct;
            return true;
        }
        if(acct_num < root->p_acct->id()){
            return Retrieve(acct_num, p_account, root->left);
        }
        else{
            return Retrieve(acct_num, p_account, root->right);
        }
    }
    else{
        return false;
    }
}

// Display() -- displays the contents of a tree to cout; you could also overload
void BSTree::Display() const{
    if(isEmpty()){
        cerr << "ERROR: Account list is empty, looks like your file didn't read in properly. Please try again." << endl;
    }
    Display(root_);
}

// Display() - facade method
void BSTree::Display(Node* root) const{
    if(root == nullptr){
		return;
	}
    Display(root->left);
    cout << *(root->p_acct) << endl;
    Display(root->right);
}

// DeleteList() -- Deletes the entire BST
void BSTree::DeleteList(){
    delete root_;
    root_ = nullptr;
    return;
}

// IsEmpty() -- Checks if the BST is empty
bool BSTree::isEmpty() const{
    return (root_ == nullptr);
}

// operator<< - prints the BST in order
ostream& operator<<(ostream &out, const BSTree& tree){
    tree.Display();
    return out;
}

// Delete() -- Delete object, first parameter is the ID of the account
// second parameter holds pointer to found object, nullptr if not found
bool BSTree::Delete(const int& acc_id, Account*& account){
    // account is not found in the tree
    if(!Retrieve(acc_id, account)){
        return false;
    }
    Node* temp = Delete(acc_id, account, root_);
    if(temp != nullptr){
        return true;
    }
    else{
        return false;
    }
}

// Delete() - facade method
BSTree::Node* BSTree::Delete(const int& acc_id, Account*& account, Node* &root){
    // Empty tree
    if(root == nullptr){
        return root;
    }   
    else if(acc_id < root->p_acct->id()){
        root->left = Delete(acc_id, account, root->left);
    }
    else if(acc_id > root->p_acct->id()){
        root->right = Delete(acc_id, account, root->right);
    }
    else{
        if((root->left == nullptr) && (root->right == nullptr)){
            delete root;
            root = nullptr;
        }
        // One child to the right
        else if(root->left == nullptr){
            Node* temp = root;
            root = root->right;
            delete temp;
            temp = nullptr;
        }
        // One child to the left
        else if(root->right == nullptr){
            Node* temp = root;
            root = root->left;
            delete temp;
            temp = nullptr;
        }
        // 2 children
        else{
            Node* temp = GetMinKey(root->right);
            root->p_acct = temp->p_acct;
            root->right = Delete(acc_id, temp->p_acct, root->right);
        }
    }
    return root;
}

// GetMinKey() -- helper method for Delete
// special case when delete node has two children
BSTree::Node* BSTree::GetMinKey(Node* node){
    Node* current = node;

    while((current != nullptr) && (current->left != nullptr)){
        current = current->left;
    }
    return current;    
}

// operator= -- makes a deep copy of the BSTree
BSTree& BSTree::operator=(const BSTree& tree){
    // check for self-assignment
    if (this == &tree) 
    return *this;

    // clear the current tree
    DeleteList();

    // copy the nodes from the other tree
    root_ = CopyTree(tree.root_);

    return *this;

}

// CopyTree() - makes a deep copy of all the elements of the BSTree into a new BSTree
BSTree::Node* BSTree::CopyTree(Node* node){
    if (node == nullptr) {
        return nullptr;
    }
    
    // create a new node with the same value as the current node
    Node* new_node = new Node();
    new_node->p_acct = node->p_acct;

    // recursively copy the left and right subtrees
    new_node->left = CopyTree(node->left);
    new_node->right = CopyTree(node->right);

    return new_node;
}
