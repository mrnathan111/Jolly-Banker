//Nathan Koplitz
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account
{
    friend class Bank;
private:
    int balanceFunds[10]; //array to keep the amount of money each fund has. Each accountt has one
    string fundNames[10]; //Array of strings, each index corresponds to the fund Name. i.e. 0 = "Money Market".
    vector<string> history[10]; //A 10 element array of vector<string>. In each array element (fund), stores strings of transaction history
    string firstName;
    string lastName;
    int accountID = 0;
public:
    Account(int actNumber, string fN, string lN); //Creates the account, opens account with info, and sets fundNames to correct fund Name in each element
    bool Withdrawal(const int fundNum, const int amount); //Withdraws from account. Return T/F
    void Deposit(const int amount, const int fundNum); //Deposits money into fund
   
    bool Transfer(const int sFund, Account* rAct, const int rFund, const int amt); //Transfers money from 1 account to another using withdraw down below
    bool WithdDuringTransf(const int fundNum, const int amount); //Doesn't store withdraw in history. Only transfer 

    void recordTrans(string trans, int fundN); //Sends string transaction to history array of vectors

    void printAccount() const; //prints the account history
    void printActFund(const int fundN) const; //prints the fund of an accounts history
    void printActBalance() const; //Prints the account balances

    string getFirstName();
    void setFirstName(string fN);
    string getLastName();
    void setLastName(string lN);
    int getID();
    void setID(int iD);
};