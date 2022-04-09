//Nathan Koplitz
#pragma once
#include "Account.h"

class BSTree
{
    friend class Bank;
private:
    struct Node
    {
        Account *pAcct; //Each node holds an account
        Node *right = nullptr;
        Node *left = nullptr;
    };
    Node* root;
public:
    BSTree();
    ~BSTree();

    bool insert(Account* act); //Inserts a Node with a new Account in the BST
    Account* Retrieve(const int &iD, Node* curNode) const; //Returns an account in the BST
    bool Search(const int &iD, Node* curNode) const; //Returns T/F if an account is found in the BST
    void Display(Node* curNode) const; //Displays contents of the BST (Bank) to cout
    void Empty(Node* curNode); //Deletes the tree and sets to nullptr
    bool isEmpty() const; //Returns T/F if tree is empty or not
    void recPrintAct(Node* curNode); //Recursively prints the account balances.

};