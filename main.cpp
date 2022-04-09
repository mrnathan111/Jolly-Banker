//Nathan Koplitz
#include "Bank.h"

int main()
{
    Bank bank1("BankTransIn.txt"); //Creates Bank, reads text file of transactions into Queue. 
    bank1.processQ(); //Processes all the transactions and prints the accounts balances
    return 0;
}