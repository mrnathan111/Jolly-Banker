//Nathan Koplitz
#include "BSTree.h"

BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    Empty(root); //Calls the empty method to delete tree
}

bool BSTree::insert(Account* act)
{
    auto newNode = new Node();
    if (act == nullptr) //if trying to add null account
    {
        return false;
    }
    int newID = act->getID();
    newNode->pAcct = act;
    auto curNode = root;
    auto prevNode = root;
    if (root == nullptr) //if empty tree
    {
        root = newNode;
        return true;
    }
    else //if NOT empty tree
    {
        curNode = root;
        while (curNode != nullptr)
        {
            prevNode = curNode;
            if (curNode->pAcct->getID() == newID)  //if curNode iD == newID    return false
            {
                cout << "You are trying to open an already existing account" << endl;
                return false;           
            }
            else if (curNode->pAcct->getID() > newID)  //if curNode iD > newID   curNode => leftChild
                curNode = curNode->left;
            else                                        //if curNode iD < newID   curNode => rightChild
                curNode = curNode->right;
        }
        if (prevNode->pAcct->getID() > newID) //if newAccount is < current Parent, insert newAccount as left child to parent node
        {
            prevNode->left = newNode;
            return true;
        }
        else //if newAccount is > current Parent, insert newAccount as right child to parent node
        {
            prevNode->right = newNode;
            return true;
        }
    }
    return false;
}

Account* BSTree::Retrieve(const int &iD, Node* curNode) const //Only should be called on nodes that DO exist in BST. Returns the node w/ desired accountID
{
    if (curNode == nullptr || curNode->pAcct->getID() == iD)
        return curNode->pAcct; //The root being the desired account OR null
    if (curNode->pAcct->getID() < iD)
        return Retrieve(iD, curNode->right);
    return Retrieve(iD, curNode->left);
}

bool BSTree::Search(const int &iD, Node* curNode) const //Returns T if found, F if not
{
    if (curNode == nullptr)
        return false; //desired ID not found OR root is nullptr
    else if (curNode->pAcct->getID() == iD) //if the root or the current Node IS the same accountID, return that the actNum is present
            return true;
    else
    {
        if (curNode->pAcct->getID() > iD)
            return Search(iD, curNode->left);
        else
            return Search(iD, curNode->right);
    }
}

void BSTree::Display(Node* curNode) const //Prints all the AccountID's in order
{
    if (curNode == nullptr)
        return;
    Display(curNode->left);
    cout << curNode->pAcct->getID() << endl;
    Display(curNode->right);
}

void BSTree::recPrintAct(Node* curNode) //Recursively Prints the accounts balances
{
    if (curNode == nullptr)
        return;
    recPrintAct(curNode->left);
    curNode->pAcct->printActBalance();
    recPrintAct(curNode->right);

}

void BSTree::Empty(Node* curNode) //Deletes all the nodes and sets to nullptr. No memory leaks
{
 	if(curNode == nullptr) 
		return;
	if(curNode->left != nullptr)
		Empty(curNode->left);
	if(curNode->right != nullptr)
		Empty(curNode->right);
    delete curNode->pAcct;
    curNode->pAcct = nullptr;
	delete curNode;
    curNode = nullptr;
	return;
}

bool BSTree::isEmpty() const //Checks if tree is empty
{
    if (root == nullptr)
        return true;
    else
        return false;
}