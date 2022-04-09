//Nathan Koplitz
#pragma once
#include "Account.h"
#include "BSTree.h"
#include <queue>
#include <fstream>

class Bank
{
private:
    BSTree accountTree; //Binary Search Tree that holds all the accounts
    queue<string> queueOfTrans; //Queue of strings that stores each line of input. Each line(string) is a transaction
public:
    Bank(string fileName); //Reads from a textfile of transactions and pushes every line of textFile to the queue
    void processQ(); //Sends queue to processCopyQ so that Queue does not get emptied from popping. Only a copy does
    void processCopyQ(queue <string> q); //Processes all the transactions, then prints the history of all the accounts.
};